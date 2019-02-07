/// Cryptography.inl

#pragma once



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
		_Log.Log( EPrefix::ERROR, ELocation::CRYPTOGRAPHY, XOR( "Invalid cipher text passed to decrypt." ) );
		return false;
	}

	return !strOut.empty( );
}
