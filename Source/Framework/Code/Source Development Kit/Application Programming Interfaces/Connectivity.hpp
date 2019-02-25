/// Connectivity.hpp

#pragma once

class CConnectivity: public IBase
{
public:

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

	struct illegal_post_data_character_t
	{
		char chCharacter;
		std::string strReplacement;

		illegal_post_data_character_t( char _chCharacter, const std::string &_strReplacement );

		void ValidateString( std::string &strToValidate );
	};

	constexpr static auto MAX_RETRIES = 3;
	constexpr static auto MAX_TIMEOUT = 15;
	constexpr static auto IDENTIFIER_LENGTH = 16;

	static inline std::string strScriptLocator;
	static inline std::vector< illegal_post_data_character_t > vecIllegalCharacters;
	static inline std::string strPostDataIdentifiers[ POST_DATA_MAX ];

	bool Initialize( ) override;
	void Uninitialize( ) override;

	static void ValidateString( std::string &strToValidate );

	[ [ nodiscard ] ] std::string GenerateIdentifier( EPostData _Identifier );
	[ [ nodiscard ] ] std::string ProcessValue( const std::string &strValue );
	template< typename _t > [ [ nodiscard ] ] bool SetConnectionParameter( CURLoption _Option, _t _Value );
	void ResetConnection( );
	[ [ nodiscard ] ] bool TryConnection( std::string &strOut, std::string *pErrorBuffer, int iRetries = 0 );

	std::string strCurrentPostData;
	bool bPostDataSet[ POST_DATA_MAX ];
	CURL *hInstance;

public:

	enum EAction
	{
		GET_PROTOCOL,
		LOGIN,
		GET_DATA,
		GET_SHELLCODE,
		GET_LIBRARY,
		GET_HASHES,
		GET_INFORMATION,
		BAN,
		GET_RESOURCE_HASH,
		GET_RESOURCES,
		ACTION_MAX
	};

	CConnectivity( ) = default;

	void AddPostData( EPostData _Identifier, const std::string &strValue );
	bool Request( EAction _Action, std::string &strOut );
} inline _Connection;

using EPostData = CConnectivity::EPostData;
using EAction = CConnectivity::EAction;

#include "Connectivity.inl"
