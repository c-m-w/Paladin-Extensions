/// Connectivity.cpp

#include "../PX Framework.hpp"

namespace PX::Net
{
	std::string strCookieFile = PX_XOR( R"(\cookie.pxcon)" );

	static size_t WriteCallback( void *contents, size_t size, size_t nmemb, void *userp )
	{
		static_cast< std::string* >( userp )->append( static_cast< char* >( contents ), size * nmemb );
		return size * nmemb;
	}

	std::string PX_API GeneratePostData( const post_data_t& dqPostData )
	{
		std::string strFormattedData { };
		for each ( auto pdPostData in dqPostData )
		{
			if ( !strFormattedData.empty( ) )
				strFormattedData += PX_XOR( "&" );
			//strFormattedData += pdPostData.strIdentifier + "=" + pdPostData.strValue;
			const auto strEncryptedValue = Cryptography::Encrypt( pdPostData.strValue );
			// Substr it to length - 1 to remove the \n
			strFormattedData += Cryptography::GenerateIdentifier( pdPostData.strIdentifier ) + PX_XOR( "=" ) + strEncryptedValue.substr( 0, strEncryptedValue.length( ) - 1 );
		}
		// Post data doesn't like plus symbols.
		std::replace( strFormattedData.begin( ), strFormattedData.end( ), '+', ' ' );
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

	std::string PX_API Request( const std::string& _strSite, const post_data_t& dqPostData )
	{
		const static auto szAppdata = getenv( PX_XOR( "APPDATA" ) );
		const static auto strCookieDirectory = szAppdata + strCookieFile;
		std::string strResponseBuffer, strPostDataBuffer = GeneratePostData( dqPostData );

		px_assert(	CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_URL, _strSite.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POST, 1L )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_POSTFIELDS, strPostDataBuffer.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_FOLLOWLOCATION, 1L )
					/// The cookie jar and file do not contain anything stored in the session, only information about the session.
					/// Information stored in $_SESSION is not accessible client side, only server side.
					/// http://php.net/manual/en/intro.session.php
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIESESSION, true )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEFILE, strCookieDirectory.c_str( ) )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_COOKIEJAR, strCookieDirectory.c_str( ) )
		            && CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEFUNCTION, WriteCallback )
					&& CURLE_OK == curl_easy_setopt( pConnection, CURLOPT_WRITEDATA, &strResponseBuffer )
		            && CURLE_OK == curl_easy_perform( pConnection ) );

		return strResponseBuffer;
	}

	std::string PX_API RequestFile( unsigned uGameID, bool bInformation )
	{
		post_data_t dqPostData;
		dqPostData.emplace_back( strExtensionIdentifier, std::to_string( uGameID ) );
		dqPostData.emplace_back( strFileIdentifier, bInformation ? PX_XOR( "1" ) : PX_XOR( "0" ) );

		return Request( strDownloadURL, dqPostData );
	}
}
