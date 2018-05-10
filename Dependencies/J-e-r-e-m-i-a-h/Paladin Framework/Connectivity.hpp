#pragma once
#define CURL_STATICLIB
#include <curl/curl.h>
#include "../Framework.hpp"

namespace Paladin
{
	class CConnectivity;
	extern CConnectivity con;
	
	class CConnectivity
	{
		enum EConnectionCodes
		{
			INVALID_HASH = -1,
			ESTABLISHING_FAILURE,
			BANNED,
			IDENTITY_MISMATCH,
			INACTIVE_PREMIUM,
			STAFF_SUCCESS,
			SUCCESS
		}
		
		int GetUniqueID( )
		{
#define UNLEN 256
			wchar_t wchUsername[ UNLEN + 1 ];
			GetUserName( wchUsername, new DWORD { UNLEN + 1 } );

			SYSTEM_INFO sysnfo;
			GetSystemInfo( &sysnfo );

			return int( wchUsername ) * sysnfo.dwActiveProcessorMask + sysnfo.dwNumberOfProcessors;
		}

		std::string strPostFields;
		void InitializeData( bool bSendDLL, int iExtension ) // bSendDLL will determine whether you'd like to send the DLL or just DLL initialization information (e.g. signatures)
		{
			std::ifstream ifRegistration( XOR( "registration.key" ) );
			std::string strUserID;
			std::getline( ifRegistration, strUserID );
			std::string strSecretKey;
			std::getline( ifRegistration, strSecretKey );

			std::string strEncryptionKey = enc.Hash_SHA3_256( std::to_string( std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) / 10 ).c_str( ) ).substr( 0, 32 );
			strPostFields = enc.Hash_SHA3_256( enc.Encrypt( XOR( "file" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( std::to_string( !bSendDLL ), strEncryptionKey ) // user_id
							//+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "uid" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( std::to_string( GetUniqueID( ) ), strEncryptionKey ) // unique_id
							//+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "sk" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( strSecretKey, strEncryptionKey ) // secret_key
							//+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "dll" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( std::to_string( bSendDLL ), strEncryptionKey ) // bool if requested to send dll
							+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "ext" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( std::stoi( iExtension ), strEncryptionKey ); // requested extension

		}
		void InitializeData( ) // used only for verification of authenticity
		{
			std::ifstream ifRegistration( XOR( "registration.key" ) );
			std::string strUserID;
			std::getline( ifRegistration, strUserID );
			std::string strSecretKey;
			std::getline( ifRegistration, strSecretKey );

			strPostFields = enc.Hash_SHA3_256( enc.Encrypt( XOR( "id" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( strUserID, strEncryptionKey ) // user_id
							+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "uid" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( std::to_string( GetUniqueID( ) ), strEncryptionKey ) // unique_id
							+ XOR( "&" ) + enc.Hash_SHA3_256( enc.Encrypt( XOR( "sk" ), strEncryptionKey ) + strEncryptionKey ) + XOR( "=" ) + enc.Encrypt( strSecretKey, strEncryptionKey ) // secret_key
		}

		void *pvDLL;
		static unsigned WriteCallback( void *pvContent, unsigned uSize, unsigned uNumOfMembers, void *pvUserP )
		{
			static_cast< std::string * >( pvUserP )->append( static_cast< char * >( pvContent ), uSize * uNumOfMembers );
			return uSize * uNumOfMembers;
		};
		int ConnectToServer( )
		{
			curl_global_init( CURL_GLOBAL_ALL );
			void *pvCurl = curl_easy_init( );
			curl_easy_setopt( pvCurl, CURLOPT_URL, XOR( "https://paladin.rip/auth.php" ) );
			curl_easy_setopt( pvCurl, CURLOPT_POSTFIELDS, strPostFields.c_str( ) );

			curl_easy_setopt( pvCurl, CURLOPT_WRITEFUNCTION, WriteCallback );
			std::string strResponseBuffer;
			curl_easy_setopt( pvCurl, CURLOPT_WRITEDATA, &strResponseBuffer );
			curl_easy_perform( pvCurl );
			curl_easy_cleanup( pvCurl );
			if ( strResponseBuffer.length( ) )
				return std::stoi( strResponseBuffer );
			else
				return ESTABLISHING_FAILURE;
		}

	public:
		int Authenticate( bool bSendDLL, std::string strExtension )
		{
			InitializeData( bSendDLL, std::string strExtension );
			return ConnectToServer( );
		}
		int Authenticate( ) // used only for heartbeat
		{
			InitializeData( );
			return ConnectToServer( );
		}
		bool Heartbeat( )
		{
			std::atomic< bool > bReturn;

			std::thread tHeartbeat( [ &bReturn ]
			{
				do
				{
					auto iReturnCode = con.Authenticate( );
					if ( !( iReturnCode == STAFF_SUCCESS || iReturnCode == SUCCESS ) )
					{
						bReturn = true;
						std::terminate( );
						return;
					}
					std::this_thread::sleep_for( std::chrono::seconds( 15 ) );
				} while ( true );
			} );
			std::this_thread::sleep_for( std::chrono::seconds( 7 ) );

			do
			{
				if ( Authenticate( ) != 0 )
				{
					bReturn = true;
					std::terminate( );
					break;
				}
				std::this_thread::sleep_for( std::chrono::seconds( 15 ) );
			} while ( true );

			if ( bReturn )
				std::terminate( );
		}
	};

	CConnectivity con;
}
