/// Connectivity.hpp

#pragma once

namespace PX::Net
{
	PX_SDK Types::str_t strUserIDIdentifier		= PX_XOR( "id" );
	PX_SDK Types::str_t strExtensionIdentifier	= PX_XOR( "ext" );
	PX_SDK Types::str_t strFileIdentifier		= PX_XOR( "file" );
	PX_SDK Types::str_t strHardwareIdentifier	= PX_XOR( "hw" );
	PX_SDK Types::str_t strSecretKeyIdentifier	= PX_XOR( "sk" );
	PX_SDK Types::str_t strUniqueIDIdentifier	= PX_XOR( "uid" );
	
	PX_SDK Types::str_t strLoginURL		= PX_XOR( "https://www.paladin.rip/auth/auth.php/" );
	PX_SDK Types::str_t strKeyURL		= PX_XOR( "https://www.paladin.rip/auth/key.php/" );
	PX_SDK Types::str_t strDownloadURL	= PX_XOR( "https://www.paladin.rip/auth/download.php/" );

	/** \brief Pointer where the connection information is stored. */
	PX_SDK CURL* pConnection = nullptr;

	/** \brief Formats passed post data into a string that can be used as post data in a connection. */
	/**	\param dqPostData All of the elements that are to be included in the formatted data. */
	/**	\return Formatted post data string. */
	Types::str_t PX_API GeneratePostData( const Types::post_data_t& dqPostData );
	/** \brief Attempts to initialize cURL. */
	/**	\return true - Initialization was successful.\n false - Initialization was not successful. */
	bool PX_API InitializeConnection( );
	/** \brief Shuts cURL down to clean up the connection pointer.\n Call this when you are done doing anything with connectivity. */
	void PX_API CleanupConnection( );
	/** \brief Makes a request to a site. */
	/**	\param strSite Site to make the request to.	*/
	/** \param dqPostData Post data to send to the site. */
	/**	\return What the site sends back from the request. */
	Types::str_t PX_API Request( const Types::str_t& strSite, const Types::post_data_t& dqPostData );

	Types::str_t PX_API RequestExtension( unsigned uGameID, bool bInformation );

	/** \brief Login status received from server after login attempt. */
	enum ELogin
	{
		/** \brief Licence file is invalid and cannot be parsed. */
		LOGIN_INVALID_LICENSE_FILE,
		/** \brief Cannot establish a connection with the server, or there has been an internal error. */
		LOGIN_CONNECTION_FAILURE,
		/** \brief Hash of the manager is invalid compared to the server's. */
		LOGIN_INVALID_HASH,
		/** \brief User has been banned and may not use the application. */
		LOGIN_BANNED,
		/** \brief User's hardware does not match previous records. */
		LOGIN_HARDWARE_MISMATCH,
		/** \brief User does not currently have a subscription to an extension. */
		LOGIN_INACTIVE_PREMIUM,
		/** \brief User has successfully logged in. */
		LOGIN_SUCCESS,
		/** \brief User is staff and has successfully logged in. */
		LOGIN_STAFF_SUCCESS
	};
	
	/** \brief Logs in using the credentials in the license file. */
	/** \param bHasExtension Which extensions the user has access to. */
	/**	\return Login status. */
	ELogin PX_API Login( bool* bHasExtension = nullptr );
	Types::str_t PX_API RequestExtensionInformation( unsigned uExtension );
}

#if defined PX_USE_NAMESPACES
using namespace PX::Net;
#endif
