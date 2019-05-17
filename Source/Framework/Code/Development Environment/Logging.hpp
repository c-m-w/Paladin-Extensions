/// Logging.hpp

#pragma once

/** \brief Contains tools to record events during runtime to assist in debugging errors. */
class CLogging: public IBase
{
public:

	/** \brief Errors which cause the logging system to be unable to write to a file.\n
				These are instead presented to the user through message boxes.\n
				The error code should be in the title of the message box. */
	enum EUnloggableError
	{
		ERROR_UNITIALIZED_LOG,
		ERROR_FORMAT_VA_FAILED,
		ERROR_CANNOT_WRITE_LOG,
		ERROR_MAX
	};

	/** \brief Prefixes for events to be logged which convey severity of the event. */
	enum EPrefix
	{
		INFO,
		DEBUG,
		SUCCESS,
		WARNING,
		ERROR,
		PREFIX_MAX
	};

	/** \brief Locations where events may be logged. */
	enum ELocation
	{
		FILESYSTEM,
		CRYPTOGRAPHY,
		CONNECTIVITY,
		RESOURCE_MANAGER,
		WINDOW,
		DRAWING,
		AUTHENTICATION,
		SYSTEM_UTILITIES,
		MEMORY_MANAGER,
		HOOKING,
		APPLICATION,
		LOCATION_MAX
	};

private:

	/** \brief The time interval that should elapse before writing the log buffer\n
				to file. */
	constexpr static auto WRITE_INTERVAL = 5000ui64; // ms
	/** \brief Maximum length of a log. */
	constexpr static auto MAX_LOG_LENGTH = 1024u;
	/** \brief Length of the buffer for formatting time. */
	constexpr static auto TIME_STRING_LENGTH = 32u;

	/** \brief Initializes the CLogging class. */
	/** \return Whether or not initialization was successful. */
	bool Initialize( ) override;
	/** \brief Uninitializes the CLogging class. */
	void Uninitialize( ) override;

	/** \brief Converts time since epoch to something that is legible. */
	/** \param strFormat Format for the time string. */
	/** \return Formatted time string. */
	[ [ nodiscard ] ] std::string FormatTime( const std::string &strFormat );
	/** \brief Gets the date for the beginning of a log session. */
	/** \return Current date. */
	[ [ nodiscard ] ] std::string GetDatestamp( );
	/** \brief Gets the current time in hours:minutes:seconds. */
	/** \return Current time in hours:minutes:seconds. */
	[ [ nodiscard ] ] std::string GetTimestamp( );
	/** \brief Gets the filename of the current log file. */
	/** \return Filename of the current log file. */
	[ [ nodiscard ] ] std::string GetCurrentLogFile( );
	[ [ nodiscard ] ] std::string GetLogEncryptionKey( );
	[ [ nodiscard ] ] std::string GetLogInitializationVector( );
	/** \brief Writes the log buffer to file. */
	void WriteToFile( );
	/** \brief Checks to see if the required amount of time has elapsed to write the\n
				log buffer to file. */
	void TestWriteToFile( );
	/** \brief Writes the header of the log including the date of log begin\n
				to file. */
	void BeginLog( );
	/** \brief Writes the footer of the log to file as well as the rest of the buffer. */
	void EndLog( );

	/** \brief Date or time to be displayed if the format cannot be processed. */
	const static inline std::string strErrorTime = ENC( "Error Retrieving Date/Time" );
	/** \brief Time for displaying the date. */
	const static inline std::string strDateFormat = ENC( "%B %e, 20%g" );
	/** \brief Format for displaying the time. */
	const static inline std::string strTimeFormat = ENC( "%H:%M:%S" );
	/** \brief Format for the log file name. */
	const static inline std::string strLogFileFormat = ENC( "%Y.%m.%d" );
	/** \brief Prefix text for each of the statuses. */
	const static inline std::string strStatusPrefixes[ PREFIX_MAX ]
	{
		ENC( "[Info]\t" ),
		ENC( "[Debug]\t" ),
		ENC( "[Success]" ),
		ENC( "[Warning]" ),
		ENC( "[Error]\t" )
	};
	/** \brief Locations where events can be logged which correspond with their enumerations in ELocation. */
	const static inline std::string strLocations[ LOCATION_MAX ]
	{
		ENC( "[Filesystem]\t" ),
		ENC( "[Cryptography]\t" ),
		ENC( "[Connectivity]\t" ),
		ENC( "[Resources]\t" ),
		ENC( "[Window]\t" ),
		ENC( "[Drawing]\t" ),
		ENC( "[Auth]\t\t" ),
		ENC( "[System]\t" ),
		ENC( "[Memory]\t" ),
		ENC( "[Hooking]\t" ),
		ENC( "[Application]\t" )
	};
	/** \brief The timestamp of the last time that the buffer was written to file. */
	Utilities::moment_t mmtLastLogWrite { };
	/** \brief Buffer to store the events in queue to be written to file. */
	std::string strBuffer { };

public:

	/** \brief Logs an event to the buffer. */
	/** \param _Prefix Prefix to denote the severity or status of the event. */
	/** \param _Location Where the event occurred. */
	/** \param strLog Text to be logged. */
	void Log( EPrefix _Prefix, ELocation _Location, const std::string &strLog );
	/** \brief Logs an event to the buffer. */
	/** \param _Prefix Prefix to denote the severity or status of the event. */
	/** \param _Location Where the event occurred. */
	/** \param szFormat Text to be logged. */
	/** \param ... Other parameters which may give detail to the event. */
	void __cdecl Log( EPrefix _Prefix, ELocation _Location, const char *szFormat, ... );
	/** \brief Creates a messagebox notifying the user of an error which cannot be\n
				written to the log file for whatever reason. The error code will be\n
				displayed in the title of the messagebox. */
	/** \param _ErrorCode Code to indicate what went wrong. */
	void HandleUnloggableError( EUnloggableError _ErrorCode );

protected:
	friend class CAuthentication;
	bool bUnsafeUninstalling = false;
} inline _Log;

using EUnloggableError = CLogging::EUnloggableError;
using EPrefix = CLogging::EPrefix;
using ELocation = CLogging::ELocation;
