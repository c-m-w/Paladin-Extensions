/// Connectivity.cpp

#include "../PX Framework.hpp"

namespace PX
{
	namespace Net
	{
		static size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
		{
			static_cast< std::string* >( userp )->append( static_cast< char* >( contents ), size * nmemb );
			return size * nmemb;
		}

		std::string PX_API GeneratePostData( std::deque< Types::post_data_t > dqPostData )
		{
			std::string strFormattedData { };
			for each( auto pdPostData in dqPostData )
			{
				if ( !strFormattedData.empty( ) )
					strFormattedData += "&";
				strFormattedData += pdPostData.strIdentifier + "=" + pdPostData.strValue;
				//strFormattedData += Cryptography::CreateIdentifier( pdPostData.strIdentifier ) + "=" + Cryptography::Encrypt( pdPostData.strValue );
			}
			return strFormattedData;
		}

		bool PX_API InitializeConnection( )
		{
			return !curl_global_init( CURL_GLOBAL_ALL ) && ( pConnection = curl_easy_init( ) );
		}

		void PX_API CleanupConnection( )
		{
			return curl_easy_cleanup( pConnection );
		}

		std::string PX_API Request( std::string strSite, std::deque< Types::post_data_t > dqPostData )
		{
			std::string strResponseBuffer, strPostDataBuffer = GeneratePostData( dqPostData );
			auto szPostDataBuffer = strPostDataBuffer.c_str( );
			curl_easy_setopt( pConnection, CURLOPT_URL, strSite.c_str( ) );
			curl_easy_setopt( pConnection, CURLOPT_POST, 1l );
			curl_easy_setopt( pConnection, CURLOPT_POSTFIELDS, szPostDataBuffer );
			curl_easy_setopt( pConnection, CURLOPT_FOLLOWLOCATION, 1l );
			curl_easy_setopt( pConnection, CURLOPT_WRITEFUNCTION, WriteCallback );
			curl_easy_setopt( pConnection, CURLOPT_WRITEDATA, &strResponseBuffer );
			curl_easy_perform( pConnection );
			return strResponseBuffer;
		}
	}
}
