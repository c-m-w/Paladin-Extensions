/// Functionality.hpp

#pragma once

namespace Manager
{
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
	/**	\return Login status. */
	ELogin PX_API Login( );
	extensions_t PX_API RetrieveExtensionInformation( );
	std::string* PX_API RetrieveLaunchInformation( );
	std::string PX_API AssembleExtension( unsigned uExtension );
}
