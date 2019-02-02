/// Cryptography.inl

#pragma once

template< typename _t > bool CCryptography::Base64( const std::string &strSubject, std::string& strOut )
{
	_t _Coder;
	_Coder.Put( reinterpret_cast< unsigned char* >( const_cast< char* >( strSubject.c_str( ) ) ), strSubject.size( ) );
	_Coder.MessageEnd( );

	strOut.clear( );
	const auto uSize = unsigned( _Coder.MaxRetrievable( ) );
	strOut.resize( uSize );
	_Coder.Get( reinterpret_cast< unsigned char* >( &strOut[ 0 ] ), uSize );
	return strProcessedText;
}

template< typename _t > bool CCryptography::Crypt( const std::string &strPlainText, std::string& strOut )
{
	_t _Cryption( reinterpret_cast< unsigned char* >( const_cast< char* >( strEncryptionKey ).c_str( ) ),
				  strEncryptionKey.length( ), reinterpret_cast< unsigned char* >( const_cast< char* >( strInitializationVector.c_str( ) ) ) );
	const auto _FormatString = CryptoPP::StringSink( strOutput );
	const auto _StreamTransform = CryptoPP::StreamTransformationFilter( _Cryption, &_FormatString )
	CryptoPP::StringSource( strPlainText, true, &_StreamTransform );
	return strOutput;
}
