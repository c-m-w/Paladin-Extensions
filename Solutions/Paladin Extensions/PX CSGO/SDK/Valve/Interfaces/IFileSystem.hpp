#pragma once

class CUtlBuffer;
class KeyValues;
class IFileList;
class IThreadPool;
class CMemoryFileBacking;

typedef void *FileHandle_t;
typedef void *FileCacheHandle_t;
typedef int FileFindHandle_t;
typedef void ( *FileSystemLoggingFunc_t )( const char *, const char * );
typedef void *( *FSAllocFunc_t )( const char *, unsigned );
typedef int WaitForResourcesHandle_t;
typedef unsigned int PathTypeQuery_t;

enum FileSystemSeek_t
{
	FILESYSTEM_SEEK_HEAD = SEEK_SET,
	FILESYSTEM_SEEK_CURRENT = SEEK_CUR,
	FILESYSTEM_SEEK_TAIL = SEEK_END,
};

enum SearchPathAdd_t
{
	PATH_ADD_TO_HEAD,		// First path searched
	PATH_ADD_TO_TAIL,		// Last path searched
};

enum FilesystemMountRetval_t
{
	FILESYSTEM_MOUNT_OK = 0,
	FILESYSTEM_MOUNT_FAILED,
};

enum PathTypeFilter_t
{
	FILTER_NONE = 0,	// no filtering, all search path types match
	FILTER_CULLPACK = 1,	// pack based search paths are culled (maps and zips)
	FILTER_CULLNONPACK = 2,	// non-pack based search paths are culled
};

abstract_class IBaseFileSystem
{
public:

	virtual int Read( void *pOutput, int size, FileHandle_t file ) = 0;
	virtual int Write( void const *pInput, int size, FileHandle_t file ) = 0;

	// if pathID is NULL, all paths will be searched for the file
	virtual FileHandle_t Open( const char *pFileName, const char *pOptions, const char *pathID = 0 ) = 0;
	virtual void Close( FileHandle_t file ) = 0;

	virtual void Seek( FileHandle_t file, int pos, FileSystemSeek_t seekType ) = 0;
	virtual unsigned int Tell( FileHandle_t file ) = 0;
	virtual unsigned int Size( FileHandle_t file ) = 0;
	virtual unsigned int Size( const char *pFileName, const char *pPathID = 0 ) = 0;

	virtual void Flush( FileHandle_t file ) = 0;
	virtual bool Precache( const char *pFileName, const char *pPathID = 0 ) = 0;

	virtual bool FileExists( const char *pFileName, const char *pPathID = 0 ) = 0;
	virtual bool IsFileWritable( char const *pFileName, const char *pPathID = 0 ) = 0;
	virtual bool SetFileWritable( char const *pFileName, bool writable, const char *pPathID = 0 ) = 0;

	virtual long GetFileTime( const char *pFileName, const char *pPathID = 0 ) = 0;

	//--------------------------------------------------------
	// Reads/writes files to utlbuffers. Use this for optimal read performance when doing open/read/close
	//--------------------------------------------------------
	virtual bool ReadFile( const char *pFileName, const char *pPath, CUtlBuffer &buf, int nMaxBytes = 0, int nStartingByte = 0, FSAllocFunc_t pfnAlloc = NULL ) = 0;
	virtual bool WriteFile( const char *pFileName, const char *pPath, CUtlBuffer &buf ) = 0;
	virtual bool UnzipFile( const char *pFileName, const char *pPath, const char *pDestination ) = 0;
};

#define FILESYSTEM_INTERFACE_VERSION            "VFileSystem017"

// modified a bit because I didn't want to include everything, but should be aligned right
class IFileSystem: public IAppSystem, public IBaseFileSystem
{
public:

	virtual bool IsSteam( ) const = 0;
	virtual FilesystemMountRetval_t MountSteamContent( int nExtraAppId = -1 ) = 0;
	virtual void AddSearchPath( const char *pPath, const char *pathID, SearchPathAdd_t addType = PATH_ADD_TO_TAIL ) = 0;
	virtual bool RemoveSearchPath( const char *pPath, const char *pathID = 0 ) = 0;
	virtual void RemoveAllSearchPaths( void ) = 0;
	virtual void RemoveSearchPaths( const char *szPathID ) = 0;
	virtual void MarkPathIDByRequestOnly( const char *pPathID, bool bRequestOnly ) = 0;
	virtual const char *RelativePathToFullPath( const char *pFileName, const char *pPathID, char *pLocalPath, int localPathBufferSize, PathTypeFilter_t pathFilter = FILTER_NONE, PathTypeQuery_t *pPathType = NULL ) = 0;
	virtual int GetSearchPath( const char *pathID, bool bGetPackFiles, char *pPath, int nMaxLen ) = 0;
	virtual bool AddPackFile( const char *fullpath, const char *pathID ) = 0;
	virtual void RemoveFile( char const *pRelativePath, const char *pathID = 0 ) = 0;
	virtual bool RenameFile( char const *pOldPath, char const *pNewPath, const char *pathID = 0 ) = 0;
	virtual void CreateDirHierarchy( const char *path, const char *pathID = 0 ) = 0;
	virtual bool IsDirectory( const char *pFileName, const char *pathID = 0 ) = 0;
	virtual void FileTimeToString( char *pStrip, int maxCharsIncludingTerminator, long fileTime ) = 0;
	virtual void SetBufferSize( FileHandle_t file, unsigned nBytes ) = 0;
	virtual bool IsOk( FileHandle_t file ) = 0;
	virtual bool EndOfFile( FileHandle_t file ) = 0;
	virtual char *ReadLine( char *pOutput, int maxChars, FileHandle_t file ) = 0;
	virtual int FPrintf( FileHandle_t file, char *pFormat, ... ) = 0;
	virtual void pad0( void ) = 0;
	virtual void pad1( void ) = 0;
	virtual const char *FindFirst( const char *pWildCard, FileFindHandle_t *pHandle ) = 0;
	virtual const char *FindNext( FileFindHandle_t handle ) = 0;
	virtual bool FindIsDirectory( FileFindHandle_t handle ) = 0;
	virtual void FindClose( FileFindHandle_t handle ) = 0;
	virtual const char *FindFirstEx( const char *pWildCard, const char *pPathID, FileFindHandle_t *pHandle ) = 0;
	virtual const char *GetLocalPath( const char *pFileName, char *pLocalPath, int localPathBufferSize ) = 0;
	virtual bool FullPathToRelativePath( const char *pFullpath, char *pRelative, int maxlen ) = 0;

#undef GetCurrentDirectory

	virtual bool GetCurrentDirectory( char *pDirectory, int maxlen ) = 0;

	virtual void pad2( void ) = 0;
	virtual bool String( const FileNameHandle_t &handle, char *buf, int buflen ) = 0;
};
