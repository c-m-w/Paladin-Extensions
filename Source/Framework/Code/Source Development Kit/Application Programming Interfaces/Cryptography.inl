/// Cryptography.inl

#pragma once

template< typename _t /*= CryptoPP::SHA1*/ > std::string CCryptography::GenerateHash( const std::string& strBytes )
{
	unsigned char bOutput[ CryptoPP::SHA1::DIGESTSIZE ] { };
	std::string strOutput { };
	CryptoPP::HexEncoder hHash { };

	_t( ).CalculateDigest( bOutput, reinterpret_cast< unsigned char* >( const_cast< char* >( strBytes.c_str( ) ) ), strBytes.length( ) );
	hHash.Attach( new CryptoPP::StringSink( strOutput ) );
	hHash.Put( bOutput, sizeof( unsigned char[ CryptoPP::SHA1::DIGESTSIZE ] ) );
	hHash.MessageEnd( );
	std::transform( strOutput.begin( ), strOutput.end( ), strOutput.begin( ), tolower );

	return strOutput;
}

template< typename _t > bool CCryptography::Crypt( const std::string &strIn, std::string &strOut, std::string strKey, std::string strInitVector )
{
	if ( strIn.empty( ) )
		return false;

	try
	{
		_t _Cryption( reinterpret_cast< unsigned char* >( const_cast< char* >( strKey.c_str( ) ) ),
					  strKey.length( ), reinterpret_cast< unsigned char* >( const_cast< char* >( strInitVector.c_str( ) ) ) );
		CryptoPP::StringSource( strIn, true, new CryptoPP::StreamTransformationFilter( _Cryption, new CryptoPP::StringSink( strOut ) ) );
	}
	catch ( CryptoPP::InvalidCiphertext & )
	{
		_Log.Log( EPrefix::ERROR, ELocation::CRYPTOGRAPHY, ENC( "Invalid cipher text passed to decrypt." ) );
		return false;
	}

	return !strOut.empty( );
}
