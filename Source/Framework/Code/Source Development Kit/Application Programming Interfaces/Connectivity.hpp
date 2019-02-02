/// Connectivity.hpp

#pragma once

class CConnectivity: public IBase
{
private:

	struct illegal_post_data_character_t
	{
		char chCharacter;
		std::string strReplacement;

		illegal_post_data_character_t( char _chCharacter, const std::string& _strReplacement );

		void ValidateString( std::string& strToValidate );
	};

	constexpr static auto MAX_RETRIES = 5;
	constexpr static auto MAX_TIMEOUT = 7;
	std::vector< illegal_post_data_character_t > vecIllegalCharacters;

	bool Initialize( ) override;

	template< typename _t > bool SetConnectionParameter( CURLoption _Option, _t _Value );

	CURL *hConnection;

public:

	struct post_data_t
	{
		std::string strIdentifier, strValue;

		post_data_t( const std::string& _strIdentifier, const std::string& _strValue );

		std::string FormatString( bool bLast );
	};

	CConnectivity( ) = default;

	void Shutdown( ) override;

	bool Request( const std::string& strUniformResourceLocator, std::initializer_list< post_data_t > initData, std::string& strOut, int iRetries = 0 );
} inline _Connection;

using post_data_t = CConnectivity::post_data_t;

#include "Connectivity.inl"
