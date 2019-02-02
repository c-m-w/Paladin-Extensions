/// Filesystem.hpp

#pragma once

/** \brief Manages local disk files and provides utilties for doing so. */
class CFilesystem: public IBase
{
private:

	bool Initialize( ) override;

	struct working_directory_t
	{
		std::string strWorkingDirectory;
		std::stack< std::string > _DirectoryStack;

		working_directory_t( ) = default;
		void StoreCurrentWorkingDirectory( );
		void RestoreWorkingDirectory( );
	};

	std::map< DWORD, working_directory_t > _ThreadDirectories { };

public:

	void Shutdown( ) override;

	/** \brief Checks whether or not a directory is present. */
	/** \param strDirectory Complete directory. */
	/** \return Whether or not the directory exists. */
	[ [ nodiscard ] ] static bool CheckAbsoluteDirectoryValidity( const std::string& strDirectory );
	/** \brief Checks whether or not a file exists. */
	/** \param strFile Complete path of a file. */
	/** \return Whether or not the file exists. */
	[ [ nodiscard ] ] static bool CheckAbsoluteFileValidity( const std::string& strFile );
	[ [ nodiscard ] ] static bool GetAbsoluteDirectoryContents( const std::string& strDirectory, bool bFiles, bool bFolders, std::vector< std::string >& vecOut );
	[ [ nodiscard ] ] static bool GetFoldersInAbsoluteDirectory( const std::string& strDirectory, std::vector< std::string >& vecOut );
	[ [ nodiscard ] ] static bool GetFilesInAbsoluteDirectory( const std::string& strDirectory, std::vector< std::string >& vecOut, const std::string& strExtension = std::string( ) );
	/** \brief Reads data from a file. */
	/** \param strFilename Full path of the file to be read. */
	/** \param strOut Output for the data of the file to be stored. */
	/** \param bDecode Whether or not to Base64 decode the file data. */
	/** \return Whether or not file reading was successful. */
	[ [ nodiscard ] ] static bool ReadAbsoluteFile( const std::string& strFilename, std::string& strOut, bool bDecode = true );
	/** \brief Writes data to a file. */
	/** \param strFilename Full path of the file to be written to. */
	/** \param strData Data to be written to the file. */
	/** \param bEncode Whether or not the Base64 encode the file data. */
	/** \return Whether or not writing to the file was successful. */
	static bool WriteAbsoluteFile( const std::string& strFilename, const std::string& strData, bool bEncode = true );
	/** \brief Adds data to the end of a file. */
	/** \param strFilename Full path of the file to be written to. */
	/** \param strData Data to be added to the end of the file. */
	/** \param bEncode Whether or not the file should be Base64 decoded to be read and\n
				encoded when written. */
	/** \return Whether or not reading and writing to the file was successful. */
	static bool AddToAbsoluteFile( const std::string& strFilename, const std::string& strData, bool bEncode = true );
	static bool HideAbsolutePath( const std::string& strPath );
	/** \brief Ensures that a directory has proper slashes to be concatenated. */
	/** \param strDirectory Directory string to be formatted. */
	static void FormatDirectory( std::string& strDirectory );
	/** \brief Gets the folder where data is stored in \appdata\roaming\ */
	/** \return Appdata directory where data is stored. */
	[ [ nodiscard ] ] static std::string GetAppdataDirectory( );
	/** \brief Gets the directory where the current executable is located. */
	/** \return Current executable directory. */
	[ [ nodiscard ] ] static std::string GetExecutableDirectory( );

	/** \brief Checks whether or not a directory exists. */
	/** \param strDirectory Directory name, relative to current working directory. */
	/** \return Whether or not the directory exists. */
	[ [ nodiscard ] ] bool CheckDirectoryValidity( const std::string& strDirectory );
	/** \brief Checks whether or not a file exists. */
	/** \param strFile File name, relative to current working directory. */
	/** \return Whether or not the file exists. */
	[ [ nodiscard ] ] bool CheckFileValidity( const std::string& strFile );
	/** \brief Stores the current working directory to be restored at a later time. */
	void StoreCurrentWorkingDirectory( );
	/** \brief Restores the current working directory that was most recently stored. */
	void RestoreWorkingDirectory( );
	/** \brief Gets the directory where Paladin is installed. */
	/** \param strOut Buffer for the directory to be saved to. */
	/** \return Whether or not obtaining the directory was successful. */
	[ [ nodiscard ] ] bool GetInstallDirectory( std::string& strOut );
	[ [ nodiscard ] ] working_directory_t& GetThreadDirectories( );
	/** \brief Gets the current working directory. */
	/** \return Current working directory. */
	[ [ nodiscard ] ] std::string& GetWorkingDirectory( );
	/** \brief Changes the current directory. */
	/** \param strNew New absolute directory. */
	/** \param zSubDirectories Amount of sub directories within the absolute directory. */
	/** \param ... Sub directories within the absolute directory */
	void ChangeWorkingDirectory( std::string strNew, std::size_t zSubDirectories = 0u, ... );
	/** \brief Converts a relative file to an absolute path. */
	/** \param strFile Relative filename/path to be converted. */
	/** \return Absolute file path. */
	[ [ nodiscard ] ] std::string FileToPath( const std::string& strFile );
	/** \brief Reads a file's data into a buffer. */
	/** \param strFilename Name of the file, relative to the current working directory. */
	/** \param strOut Output for the file contents/ */
	/** \param bDecode Whether or not to Base64 decode the file's contents. */
	/** \return Whether or not reading the file was successful. */
	[ [ nodiscard ] ] bool ReadFile( const std::string& strFilename, std::string& strOut, bool bDecode = true );
	/** \brief Writes data to a file. */
	/** \param strFilename Name of the file to be written to, relative to the current working directory. */
	/** \param strData Data to be written to the file. */
	/** \param bEncode Whether or not to Base64 encode the data written to the file. */
	/** \return Whether or not writing to the file was successful. */
	bool WriteFile( const std::string& strFilename, const std::string& strData, bool bEncode = true );
	/** \brief Adds data to the end of a file. */
	/** \param strFilename Name of the file, relative to the current working directory. */
	/** \param strData Data to be added to the end of the file. */
	/** \param bEncode Whether or not to Base64 decode the file when read, and Base64 encode the contents\n
						when written back to the file. */
	/** \return Whether or not reading and writing to the specified file was successful. */
	bool AddToFile( const std::string& strFilename, const std::string& strData, bool bEncode = true );
	[ [ nodiscard ] ] static bool GetDirectoryContents( const std::string& strDirectory, bool bFiles, bool bFolders, std::vector< std::string >& vecOut );
	[ [ nodiscard ] ] static bool GetFoldersInDirectory( const std::string& strDirectory, std::vector< std::string >& vecOut );
	[ [ nodiscard ] ] static bool GetFilesInDirectory( const std::string& strDirectory, std::vector< std::string >& vecOut, const std::string& strExtension = std::string( ) );
	bool HidePath( const std::string& strPath );

	/** \brief Path of the Paladin data folder from \appdata\roaming\ */
	static std::string strRelativeAppdataDirectory;
	/** \brief Directory of log files relative to the Paladin data folder in appdata. */
	static std::string strLogDirectory;
	/** \brief Name of the cookie file which stores information pertaining to connection to the site.\n
				The file is stored in the data folder in appdata. */
	static std::string strCookieFile;
	/** \brief Name of the data file which stores the install directory.\n
				The file is stored in the data folder in appdata. */
	static std::string strDataFile;
	/** \brief Name of the licence file which stores information about the user's credentials.\n
				The file is stored in the data folder in appdata. */
	static std::string strLicenseFile;
} inline _Filesystem;
