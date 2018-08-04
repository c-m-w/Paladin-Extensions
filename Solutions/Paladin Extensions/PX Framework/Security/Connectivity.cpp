/// Connectivity.cpp

#include "../PX Framework.hpp"

namespace PX::Net
{
	static size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
	{
		static_cast< std::string* >( userp )->append( static_cast< char* >( contents ), size * nmemb );
		return size * nmemb;
	}

	std::string PX_API GeneratePostData( const std::deque< Net::post_data_t >& dqPostData )
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
		return curl_global_init( CURL_GLOBAL_ALL ) == CURLE_OK && ( pConnection = curl_easy_init( ) ) != nullptr;
	}

	void PX_API CleanupConnection( )
	{
		return curl_easy_cleanup( pConnection );
	}

	std::string PX_API Request( const std::string& _strSite, const std::deque< Net::post_data_t >& dqPostData )
	{
		std::string strResponseBuffer, strPostDataBuffer = GeneratePostData( dqPostData );

		dbg::Assert(	CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_URL, _strSite.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POST, 1L )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POSTFIELDS, strPostDataBuffer.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_FOLLOWLOCATION, 1L )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEFUNCTION, WriteCallback )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEDATA, &strResponseBuffer )
		            && CURLE_OK == curl_easy_perform( pConnection ) );

		return strResponseBuffer;
	}
}
