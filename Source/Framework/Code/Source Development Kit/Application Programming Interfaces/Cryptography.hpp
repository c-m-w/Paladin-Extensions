/// Cryptography.hpp

#pragma once

/** \brief Provides tools for processing what is communicated through connectivity. */
class CCryptography: public IBase
{
protected:

	constexpr static auto GENERATION_INTERVAL = 3600000ui64; // 1 hour in milliseconds

	bool Initialize( ) override;
	void Uninitialize( ) override;

	/** \brief Key to encrypt / decrypt with. */
	std::string strEncryptionKey;
	/** \brief Initialization vector for encryption. */
	std::string strInitializationVector;
	/** \brief Last time that an encryption key was generated. */
	Utilities::moment_t mmtLastGenerationTime;

public:

	using encode_t = CryptoPP::Base64Encoder;
	using decode_t = CryptoPP::Base64Decoder;
	using encrypt_t = CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption;
	using decrypt_t = CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption;

	/** \brief Size of encryption key in bytes. */
	constexpr static auto ENCRYPTION_KEY_SIZE = 32;
	/** \brief Size of initialization vector in bytes. */
	constexpr static auto INITIALIZATION_VECTOR_SIZE = 16;

	CCryptography( ) = default;

	/** \brief Computes a hash of an array of bytes. */
	/**	\param strBytes Text to be hashed. */
	/**	\return Hash of the text. */
	std::string GenerateHash( const std::string &strBytes );
	/** \brief Base64 encodes or decodes text. */
	/**	\tparam _t Either CryptoPP::Base64Decoder or CryptoPP::Base64Encoder, depending on if you wish to encode or decode text. */
	/**	\param strSubject Text to encode or decode. */
	/**	\param strOut Output buffer for the encoded or decoded text. */
	/**	\return Whether or not encoding or decoding the text was sucessful. */
	template< typename _t > bool Base64( const std::string &strSubject, std::string &strOut );
	/** \brief Encrypts or decrypts text with AES-256-CBC style.\n Requires InitializeEncryption( ) be called beforehand. */
	/**	\tparam _t Either CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption or CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption, depending on if you wish to encrypt or decrypt text. */
	/**	\param strIn Text to encrypt or decrypt. */
	/**	\param strOut Output buffer for the encrypted or decrypted text. */
	/**	\return Whether or not processing the text was successful. */
	template< typename _t > bool Crypt( const std::string &strIn, std::string &strOut );
	bool Encrypt( const std::string& strPlainText, std::string& strCipher );
	bool Decrypt( const std::string& strCipher, std::string& strPlainText );
} inline _Cryptography;

using encode_t = CCryptography::encode_t;
using decode_t = CCryptography::decode_t;
using encrypt_t = CCryptography::encrypt_t;
using decrypt_t = CCryptography::decrypt_t;

#include "Cryptography.inl"
