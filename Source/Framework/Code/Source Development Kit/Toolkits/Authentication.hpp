/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	/** \brief Maximum length, in characters, of a\n 
				hardware device. */
	constexpr static auto MAX_HARDWARE_LENGTH = 100;
	/** \brief The string that is returned when no other data was received\n
				from a request to the server. */
	inline const static auto NO_OTHER_DATA = ENC( "none" );

	/** \brief Whether or not the user has been logged in. */
	bool bLoggedIn = false;

	/** \brief Retrieves and formats hardware in a way that the server can interpret. */
	/** \param strOut Output that contains hardware information that is to be sent to the server. */
	/** \return Whether or not obtaining hardware and formatting it was successful. */
	bool GetHardware( std::string &strOut );
	/** \brief Gets the purchase key that the user entered when the license file was\n 
				originally created. */
	/** \param strOut Output for the purchase key that was read from the license file. */
	/** \return Whether or not obtaining the purchase key was successful. */
	bool GetPurchaseKey( std::string &strOut );
	/** \brief Safely removes all Paladin data from the client PC. */
	/** \return Where uninstallation failed; 0 if successful */
	int Uninstall( );
	/** \brief Calls Uninstall( ) and terminates all Paladin programs then forcefully shuts down the computer. */
	__declspec( noreturn ) void UnsafeUninstall( );

public:

	/** \brief Codes that can be returned from the server when sending a request. */
	enum ELoginCode
	{
		CONNECTION_ERROR,
		SERVER_ERROR,
		BANNED,
		INVALID_KEY,
		INVALID_HARDWARE,
		SUCCESS,
		STAFF_SUCCESS
	};

	/** \brief Enumeration for each of the libraries that can be requested / information for them. */
	enum ELibrary
	{
		CLIENT,
		CSGOX,
		PUBX,
		RSIXX,
		RUSTX,
		MAX_LIBRARY
	};

	/** \brief Length, in characters, of a purchase key from the website. */
	constexpr static auto PURCHASE_KEY_LENGTH = 12;

#if defined _DEBUG

	/** \brief Unique hashes of executable PE headers to ensure that the process that is being injected to is valid. */
	const static inline std::string strExecutableHashes[ MAX_LIBRARY ]
	{
		{ },
		{ ENC( "8d8a9cd233b8362698f03f0295199db708cabb14" ) },
		{ },
		{ },
		{ }
	};

	/** \brief Creates the data for the shellcode file that is on the server. */
	/** \return JSON encoded shellcode data. This can be directly pasted into\n
					the file on the site. */
	[ [ nodiscard ] ] static std::string CreateShellcodeFile( );
	/** \brief Creates the contents of the data file that is used for general\n
				data such as signatures and offsets required for runtime. */
	/** \return JSON encoded data. This can be directly pasted into\n
					the file on the site. */
	[ [ nodiscard ] ] static std::string CreateDataFile( );
	/** \brief Creates the file for storing hashes of PE headers that\n
				is used to validate a process's identity. */
	/** \return JSON encoded hash data. This can be directly pasted into\n
					the file on the site.*/
	[ [ nodiscard ] ] static std::string CreateHashFile( );

#endif

	/** \brief Creates a license file for the user. */
	/** \param strPurchaseKey Any purchase key that was obtained from the website\n 
				after purchasing a product. The user can use any purchase key from\n 
				any product to create the license file. */
	/** \return Whether or not the file was created successfully. */
	bool CreateLicenseFile( std::string strPurchaseKey );
	/** \brief Bans the user from the website and from using any software of Paladin Extensions.\n 
				This can be called at any time as long as the license file has been created.\n 
				There will be information such as programs installed, programs open and windows\n 
				open uploaded to the server.\n 
				All of the ban information will be recorded in the most recent log. */
	/** \param strReason Reason for ban. */
	/** \return Whether or not the ban was successful.\n 
				This can fail if the license file has not been created or if gathering ban\n 
				information failed.*/
	bool Ban( const std::string &strReason );
	/** \brief Logs the user in and begins a PHP cookie session to be able to request\n 
				data from the website. */
	/** \return The status of the login. */
	[ [ nodiscard ] ] ELoginCode Login( );
	/** \brief Requests required data for runtime from the server. The user must be logged\n 
				in before this function is called or it will fail. */
	/** \return Whether or not requesting and obtaining the data was successful. */
	bool RequestData( std::string *pNewestInsertInvertedFunctionTable, std::ptrdiff_t *pNewestInsertInvertedFunctionTableOffset, std::string *pNewestInvertedFunctionTable,
					  std::ptrdiff_t *pNewestInvertedFunctionTableOffset, std::string *pBackupInsertInvertedFunctionTable, std::ptrdiff_t *pBackupInsertInvertedFunctionTableOffset,
					  std::ptrdiff_t *pBackupInvertedFunctionTableOffset, std::string *pResortInsertInvertedFunctionTable, std::ptrdiff_t *pResortInsertInvertedFunctionTableOffset,
					  std::ptrdiff_t *pResortWindows10InvertedFunctionTableOffset, std::ptrdiff_t *pResortPreviousWindowsInvertedFunctionTableOffset );
	/** \brief Requests shellcode from the server that is required for loading images\n 
				into memory. */
	/** \return Whether or not requesting and obtaining the shellcode was successful. */
	bool RequestShellcode( unsigned char **pThreadEnvironment, unsigned char **pLoadLibraryExWrapper, unsigned char **pRelocateImageBase, unsigned char **pLoadDependencies,
						   std::size_t *pThreadEnvironmentSize, std::size_t *pLoadLibraryExWrapperSize, std::size_t *pRelocateImageBaseSize, std::size_t *pLoadDependenciesSize );
	/** \brief Requests a library from the server. This library is to then be\n 
				loaded into memory in either the local or a remote process. */
	/** \param _Library Enumeration of the library that is to be requested. */
	/** \param strOut Raw data output for the library. */
	/** \return Whether or not requesting and obtaining the library was successful. */
	bool RequestLibrary( ELibrary _Library, std::string &strOut );
	bool RequestLibraryData( ELibrary _Library, std::string& strOut );
	/** \brief Compares the hash of an executable to one that is obtained from the server. */
	/** \param _ExecutableHash Enumeration of the library which the hash belongs to. */
	/** \param strCurrent Current hash that is to be compared. */
	/** \return Whether or not the hashes were successfully requested and obtained from the server\n 
					and whether or not the hashes were the same. */
	bool CompareHash( ELibrary _ExecutableHash, const std::string &strCurrent );
	/** \brief Attempts to uninstall all of the data that was installed by Paladin Extensions software,\n 
				including the current executable. Communicates with server that uninstall was attempted. */
	/** \return Whether or not uninstalling was successful. */
	bool AttemptUninstall( bool bUnsafe = false );
} extern _Authentication;

using ELoginCode = CAuthentication::ELoginCode;
using ELibrary = CAuthentication::ELibrary;
