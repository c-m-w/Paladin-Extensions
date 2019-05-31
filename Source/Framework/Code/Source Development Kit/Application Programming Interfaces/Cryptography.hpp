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
	std::string strEncryptionKey { };
	/** \brief Initialization vector for encryption. */
	std::string strInitializationVector { };
	std::string strProtocol { };
	/** \brief Last time that an encryption key was generated. */
	Utilities::moment_t mmtLastGenerationTime = 0ui64;

public:

	using encrypt_t = CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption;
	using decrypt_t = CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption;

	/** \brief Size of encryption key in bytes. */
	constexpr static auto ENCRYPTION_KEY_SIZE = 32;
	/** \brief Size of initialization vector in bytes. */
	constexpr static auto INITIALIZATION_VECTOR_SIZE = 16;
	/** \brief Encryption key that is to be used to encrypt things such as licence files. */
	inline static std::string strStaticEncryptionKey = ENC( "ExgrEV9yIlF3xgocqy53ipLAwFHuDznk" );
	/** \brief Initialization vector that is to be used to encrypt things such as licence files. */
	inline static std::string strStaticInitializationVector = ENC( "4ZNqNqIaJqZqPJS1" );

	/** \brief Computes a hash of an array of bytes. */
	/**	\param strBytes Text to be hashed. */
	/**	\return Hash of the text. */
	template< typename _t = CryptoPP::SHA1 > [ [ nodiscard ] ] std::string GenerateHash( const std::string & strBytes );
	[ [nodiscard] ] unsigned GenerateNumericHash( const std::string& strBytes );
	[ [nodiscard] ] unsigned GenerateNumericHash( const void* pData, std::size_t zSize );
	bool Encode( const std::string &strSubject, std::string &strOut );
	bool Decode( const std::string &strEncoded, std::string &strOut );
	/** \brief Encrypts or decrypts text with AES-256-CBC style.\n Requires InitializeEncryption( ) be called beforehand. */
	/**	\tparam _t Either CryptoPP::CBC_Mode< CryptoPP::AES >::Encryption or CryptoPP::CBC_Mode< CryptoPP::AES >::Decryption, depending on if you wish to encrypt or decrypt text. */
	/**	\param strIn Text to encrypt or decrypt. */
	/**	\param strOut Output buffer for the encrypted or decrypted text. */
	/**	\return Whether or not processing the text was successful. */
	template< typename _t > static bool Crypt( const std::string &strIn, std::string &strOut, std::string strKey, std::string strInitVector );
	bool Encrypt( const std::string &strPlainText, std::string &strCipher, std::string strKey = std::string( ), std::string strInitVector = std::string( ) );
	bool Decrypt( const std::string &strCipher, std::string &strPlainText, std::string strKey = std::string( ), std::string strInitVector = std::string( ) );
} extern _Cryptography;

using encrypt_t = CCryptography::encrypt_t;
using decrypt_t = CCryptography::decrypt_t;

#include "Cryptography.inl"
