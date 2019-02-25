/// Authentication.hpp

#pragma once

class CAuthentication
{
private:

	constexpr static auto MAX_HARDWARE_LENGTH = 100;
	inline const static auto NO_OTHER_DATA = ENC( "none" );

	bool bLoggedIn = false;

	bool GetHardware( std::string &strOut );
	bool GetPurchaseKey( std::string &strOut );
	__declspec( noreturn ) void UnsafeUninstall( );
	bool Uninstall( );

public:

	enum ERequestCode
	{
		CONNECTION_ERROR,
		SERVER_ERROR,
		BANNED,
		INVALID_KEY,
		INVALID_HARDWARE,
		SUCCESS,
		STAFF_SUCCESS
	};

	enum ELibrary
	{
		CLIENT,
		CSGOX,
		PUBX,
		RSIXX,
		RUSTX,
		MAX_LIBRARY
	};

	constexpr static auto PURCHASE_KEY_LENGTH = 12;

#if defined _DEBUG

	const static inline std::string strExecutableHashes[ MAX_LIBRARY ]
	{
		{ },
		{ ENC( "8d8a9cd233b8362698f03f0295199db708cabb14" ) },
		{ },
		{ },
		{ }
	};

	[ [ nodiscard ] ] static std::string CreateShellcodeFile( );
	[ [ nodiscard ] ] static std::string CreateDataFile( );
	[ [ nodiscard ] ] static std::string CreateHashFile( );

#endif

	bool CreateLicenseFile( std::string strPurchaseKey );
	bool Ban( const std::string &strReason );
	[ [ nodiscard ] ] ERequestCode Login( );
	bool RequestData( std::string *pNewestInsertInvertedFunctionTable, std::ptrdiff_t *pNewestInsertInvertedFunctionTableOffset, std::string *pNewestInvertedFunctionTable,
					  std::ptrdiff_t *pNewestInvertedFunctionTableOffset, std::string *pBackupInsertInvertedFunctionTable, std::ptrdiff_t *pBackupInsertInvertedFunctionTableOffset,
					  std::ptrdiff_t *pBackupInvertedFunctionTableOffset, std::string *pResortInsertInvertedFunctionTable, std::ptrdiff_t *pResortInsertInvertedFunctionTableOffset,
					  std::ptrdiff_t *pResortWindows10InvertedFunctionTableOffset, std::ptrdiff_t *pResortPreviousWindowsInvertedFunctionTableOffset );
	bool RequestShellcode( unsigned char **pThreadEnvironment, unsigned char **pLoadLibraryExWrapper, unsigned char **pRelocateImageBase, unsigned char **pLoadDependencies,
						   std::size_t *pThreadEnvironmentSize, std::size_t *pLoadLibraryExWrapperSize, std::size_t *pRelocateImageBaseSize, std::size_t *pLoadDependenciesSize );
	bool RequestLibrary( ELibrary _Library, std::string &strOut );
	bool CompareHash( ELibrary _ExecutableHash, const std::string &strCurrent );
	bool AttemptUninstall( );
} inline _Authentication;

using ELoginCode = CAuthentication::ERequestCode;
using ELibrary = CAuthentication::ELibrary;
