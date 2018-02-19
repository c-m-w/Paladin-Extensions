#pragma once
#include "Framework.hpp"
#include <Windows.h>
namespace Paladin
{
	class CConnectivity;
	extern CConnectivity con;

	class CConnectivity
	{
		int GetUniqueID( )
		{
			DWORD dwUsernameBufferSize = UNLEN + 1;
			wchar_t wchUsername[ dwBufferSize ];
			GetUserName( wchBuffer, &dwBufferSize );

			SYSTEM_INFO sysnfo;
			GetSystemInfo( &sysnfo );

			return reinterpret_cast< int >( static_cast< double >( wchUsername ) * double( sysnfo.dwActiveProcessorMask + sysnfo.dwNumberOfProcessors ) );
		}
		std::string strPostFields;
		void *pvDLL;
		void Initialize( )
		{
			std::ifstream ifRegistration( "registration.key" );
			std::string strUserID;
			std::getline( ifRegistration, strUserID );
			std::string strSecretKey;
			std::getline( ifRegistration, strSecretKey );

			std::string strEncryptionKey = enc.Hash_SHA_256( std::to_string( std::chrono::duration_cast< std::chrono::seconds >( std::chrono::system_clock::now( ).time_since_epoch( ) ).count( ) / 10 ).c_str( ) ).substr( 0, 32 );
			strPostData = enc.Hash_SHA3_256( enc.Encrypt( "id", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( strUserID, strEncryptionKey )
				+ "&" + enc.Hash_SHA3_256( enc.Encrypt( "uid", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( std::to_string( GetUniqueID ), strEncryptionKey )
				+ "&" + enc.Hash_SHA3_256( enc.Encrypt( "sk", strEncryptionKey ) + strEncryptionKey ) + "=" + enc.Encrypt( strSecretKey, strEncryptionKey );
		}
		int Connect( )
		{
			curl_global_init( CURL_GLOBAL_ALL );
			void *pvCurl = curl_easy_init( );
			curl_easy_setopt( pvCurl, CURLOPT_URL, "https://paladin.rip/auth.php" );
			curl_easy_setopt( pvCurl, CURLOPT_POSTFIELDS, strPostFields.c_str( ) );
			{
				static size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
				{
					static_cast< std::string * >( userp )->append( static_cast< char * >( contents ), size * nmemb );
					return size * nmemb;
				}
				curl_easy_setopt( pvCurl, CURLOPT_WRITEFUNCTION, WriteCallback );
			}
			curl_easy_setopt( pvCurl, CURLOPT_WRITEDATA, &strResponseBuffer );
			curl_easy_perform( pvCurl );
			curl_easy_cleanup( pvCurl );
			if ( strResponseBuffer.length( ) == 1 ) 
				return std::stoi( strResponseBuffer );
			else
			{
				pvDLL = new const char *{ strResponseBuffer.c_str( ) };
				return 0;
			}
		}
	public:
		int Authenticate( )
		{
			// Connect to server and pass information ( UserID, SecretKey, UniqueID )
			Initialize( );
			Connect( );
		}
		bool Heartbeat( )
		{
			// Call authenticate and confirm with check based on threading
		}
	};

	CConnectivity con;
}
