/// Cryptography.inl

#pragma once

template< typename _t > bool CCryptography::Base64( const std::string &strSubject, std::string &strOut )
{
	if ( strSubject.empty( ) )
		return false;

	_t _Coder;
	_Coder.Put( reinterpret_cast< unsigned char* >( const_cast< char* >( strSubject.c_str( ) ) ), strSubject.size( ) );
	_Coder.MessageEnd( );

	strOut.clear( );
	const auto uSize = unsigned( _Coder.MaxRetrievable( ) );
	strOut.resize( uSize );
	_Coder.Get( reinterpret_cast< unsigned char* >( &strOut[ 0 ] ), uSize );
	return !strOut.empty( );
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
		_Log.Log( EPrefix::ERROR, ELocation::CRYPTOGRAPHY, XOR( "Invalid cipher text passed to decrypt." ) );
		return false;
	}

	return !strOut.empty( );
}
