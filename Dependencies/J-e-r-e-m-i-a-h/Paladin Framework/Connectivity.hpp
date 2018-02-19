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
		void InitializeData( bool bSendDLL )
		{
			std::ifstream ifRegistration( "registration.key" );
			std::string strUserID;
			std::getline( ifRegistration, strUserID );
			std::string strSecretKey;
			std::getline( ifRegistration, strSecretKey );

			std::string strEncryptionKey = enc.Hash_SHA3_256( std::to_string( std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) / 10 ).c_str( ) ).substr( 0, 32 );
			strPostFields = enc.Hash_SHA3_256( enc.Encrypt( "id", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( strUserID, strEncryptionKey )
				+ "&" + enc.Hash_SHA3_256( enc.Encrypt( "uid", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( std::to_string( GetUniqueID( ) ), strEncryptionKey )
				+ "&" + enc.Hash_SHA3_256( enc.Encrypt( "sk", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( strSecretKey, strEncryptionKey )
				+ "&" + enc.Hash_SHA3_256( enc.Encrypt( "dll", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( std::to_string( bSendDLL ), strEncryptionKey );
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
			curl_easy_setopt( pvCurl, CURLOPT_URL, "https://paladin.rip/auth.php" );
			curl_easy_setopt( pvCurl, CURLOPT_POSTFIELDS, strPostFields.c_str( ) );

			curl_easy_setopt( pvCurl, CURLOPT_WRITEFUNCTION, WriteCallback );
			std::string strResponseBuffer;
			curl_easy_setopt( pvCurl, CURLOPT_WRITEDATA, &strResponseBuffer );
			curl_easy_perform( pvCurl );
			curl_easy_cleanup( pvCurl );
			if ( strResponseBuffer.length( ) == 1 )
				return std::stoi( strResponseBuffer );
			else
			{
				pvDLL = new const char * { strResponseBuffer.c_str( ) }; // TODO decrypt DLL
				return 0;
			}
		}

	public:
		int Authenticate( bool bSendDLL )
		{
			InitializeData( bSendDLL );
			return ConnectToServer( );
		}
		bool Heartbeat( )
		{
			std::atomic< bool > bReturn;

			std::thread tHeartbeat( [ &bReturn ]
			{
				do
				{
					if ( con.Authenticate( false ) != 0 )
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
				if ( Authenticate( false ) != 0 )
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
