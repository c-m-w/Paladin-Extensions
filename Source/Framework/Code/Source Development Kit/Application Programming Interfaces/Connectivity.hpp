/// Connectivity.hpp

#pragma once

/** \brief Handles communication between client and server. */
class CConnectivity: public IBase
{
public:

	/** \brief The different forms of post data that can be sent to\n
				the server depending on the action requested. */
	enum EPostData
	{
		PURCHASE_KEY,
		HARDWARE,
		LIBRARY,
		BAN_REASON,
		PROCESS_LIST,
		INSTALLED_PROGRAMS,
		OPEN_WINDOWS,
		ACTION,
		POST_DATA_MAX
	};

private:

	/** \brief Contains data about a character that may not be\n
				present in post data. */
	struct illegal_post_data_character_t
	{
		/** \brief The illegal character that is to be replaced. */
		char chCharacter;
		/** \brief Replacement string for the illegal character. */
		std::string strReplacement;

		/** \brief Constructor. */
		/** \param _chCharacter The illegal character that is to be replaced. */
		/** \param _strReplacement Replacement string for the illegal character. */
		illegal_post_data_character_t( char _chCharacter, const std::string &_strReplacement );

		/** \brief Formats a string and replaces the occurances of an illegal character\n 
					with the string that was specified in the constructor. */
		/** \param strToValidate String that is to be validated. */
		void ValidateString( std::string &strToValidate );
	};

	/** \brief Maximum amount of times that a connection should be attempted\n 
				to the server before timing out. */
	constexpr static auto MAX_RETRIES = 3;
	/** \brief Maximum time, in seconds, that should be waited before timing out\n 
				while waiting for a response from the server. */
	constexpr static auto MAX_TIMEOUT = 15;
	/** \brief Length, in characters, of an indentifier that is to be used to identify\n 
				which data is contained in the post data. */
	constexpr static auto IDENTIFIER_LENGTH = 16;

	/** \brief URL of the PHP script that is to be connected to. */
	static inline std::string strScriptLocator;
	/** \brief Illegal characters that may not be present in post data. */
	static inline std::vector< illegal_post_data_character_t > vecIllegalCharacters;
	/** \brief Strings that identify what is contained in post data. */
	static inline std::string strPostDataIdentifiers[ POST_DATA_MAX ];

	/** \brief Initializes the CConnectivity class. */
	/** \return Whether or not initialization was successful. */
	bool Initialize( ) override;
	/** \brief Uninitializes the CConnectivity class. */
	void Uninitialize( ) override;

	/** \brief Validates a string to ensure that it contains no illegal characters\n 
				that will cause an issue with post data. */
	/** \param strToValidate The string that is to be validated. */
	static void ValidateString( std::string &strToValidate );

	/** \brief Creates an identifier that is to be used to identify what is contained in post data. */
	/** \param _Identifier What an identifier is being generated for. */
	/** \return A post data identifier which can be interpreted by the server. */
	[ [ nodiscard ] ] std::string GenerateIdentifier( EPostData _Identifier );
	/** \brief Processes a post data value so that it is able to be interpreted by the server. */
	/** \param strValue value that is to be formatted. */
	/** \return The processed value that is able to be interpreted by the server. */
	[ [ nodiscard ] ] std::string ProcessValue( const std::string &strValue );
	/** \brief Sets a parameter for the connection which controls how it behaves. */
	/** \tparam _t Type of the parameter. */
	/** \param _Option The parameter that is to be set. */
	/** \param _Value Value of the parameter. */
	/** \return Whether or not setting the parameter was successful. */
	template< typename _t > [ [ nodiscard ] ] bool SetConnectionParameter( CURLoption _Option, _t _Value );
	/** \brief Resets the connection, clearing cookies and other information. */
	void ResetConnection( );
	/** \brief Attempts to make a request to the server. */
	/** \param strOut What the server sends back. */
	/** \param pErrorBuffer Buffer for errors to be logged, if any, by cURL. */
	/** \param iRetries Amount of times the connection has been retried. */
	/** \return Whether or not the request was successful. */
	[ [ nodiscard ] ] bool TryConnection( std::string &strOut, std::string *pErrorBuffer, int iRetries = 0 );

	/** \brief String of the current post data that will be sent to the server.\n 
				This is built upon until a connection is made, then cleared. */
	std::string strCurrentPostData { };
	/** \brief Contains data about which forms of post data have been set. */
	bool bPostDataSet[ POST_DATA_MAX ] { };
	/** \brief An open handle for an instance of cURL. */
	CURL *hInstance = nullptr;

public:

	/** \brief The action that is being requested from the server. */
	enum EAction
	{
		GET_PROTOCOL,
		LOGIN,
		GET_DATA,
		GET_SHELLCODE,
		GET_LIBRARY,
		GET_HASHES,
		GET_LIBRARY_DATA,
		BAN,
		GET_RESOURCE_HASH,
		GET_RESOURCES,
		ACTION_MAX
	};

	/** \brief Adds data that is to be sent to the server. */
	/** \param _Identifier Type of data being sent. */
	/** \param strValue Value of the data being sent. */
	void AddPostData( EPostData _Identifier, const std::string &strValue );
	/** \brief Makes a request to the server with the post data that has been specified, if any. */
	/** \param _Action What the server is requested to do. */
	/** \param strOut What the server's response is. */
	/** \return Whether or not the request was successful. */
	bool Request( EAction _Action, std::string &strOut );
} extern _Connection;

using EPostData = CConnectivity::EPostData;
using EAction = CConnectivity::EAction;

#include "Connectivity.inl"
