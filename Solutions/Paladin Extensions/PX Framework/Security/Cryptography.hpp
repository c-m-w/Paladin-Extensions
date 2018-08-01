/// Encryption.hpp

#pragma once

namespace PX
{
	namespace Cryptography
	{
		/** \brief Stores the encryption key, which is generated in Initialize( ).\n Used in encryption and decryption functions. */
		PX_SDK std::string strEncryptionKey { };
		/** \brief Stores the initialization vector, which is generated in Initialize( ).\n Used in encryption and decryption functions. */
		PX_SDK std::string strInitializationVector { };

		/** \brief Generates an encryption key and initialization vector for use with encryption.\n Call before using any cryption functions. */
		/**	\return true - Successfully generated key and vector\n false - Did not successfully generate key and vector. */
		bool PX_API Initialize( );
		/** \brief Hashes text. */
		/**	\param strPlainText Text to be hashed. */
		/**	\return Hash of the text. */
		std::string PX_API GenerateHash( const std::string& strPlainText );
		/** \brief Base64 encodes or decodes text. */
		/**	\tparam _t Either CryptoPP::Base64Decoder or CryptoPP::Base64Encoder, depending on if you wish to encode or decode text. */
		/**	\param strSubject Text to encode or decode. */
		/**	\return Processed text. */
		template< typename _t > std::string PX_API Base64( const std::string& strSubject );
		/** \brief Encrypts or decrypts text with AES-256-CBC style.\n Requires Initialize( ) be called beforehand. */
		/**	\tparam _t Either CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption or CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption, depending on if you wish to encrypt or decrypt text. */
		/**	\param strPlainText Text to encrypt or decrypt. */
		/**	\return Processed text. */
		template< typename _t > std::string PX_API AES256CBC( const std::string& strPlainText );
		/** \brief Encrypts and Base64 encodes text.\n Requires Initialize( ) be called beforehand. */
		/**	\param strPlainText Plain text to encrypt and encode. */
		/**	\return Encrypted and encoded text. */
		std::string PX_API Encrypt( const std::string& strPlainText );
		/** \brief Base64 decodes and decrypts text.\n Requires Initialize( ) be called beforehand. */
		/**	\param strCipherText Cipher text to decode and decrypt. */
		/**	\return Decoded and decrypted text. */
		std::string PX_API Decrypt( const std::string& strCipherText );
	}

	namespace XOR
	{
		constexpr int PX_API LinearCongruentialGenerator( int iRounds )
		{
			return 1013904223 + 1664525 * ( iRounds > 0 ? LinearCongruentialGenerator( iRounds - 1 )
											: ( __TIME__[ 7 ] - '0' ) * 1 + ( __TIME__[ 6 ] - '0' ) * 10 + ( __TIME__[ 4 ] - '0' ) * 60 +
											( __TIME__[ 3 ] - '0' ) * 600 + ( __TIME__[ 1 ] - '0' ) * 3600 + ( __TIME__[ 0 ] - '0' ) * 36000
											& 0xFFFFFFFF );
		}
	}
}

#include "Cryptography.inl"