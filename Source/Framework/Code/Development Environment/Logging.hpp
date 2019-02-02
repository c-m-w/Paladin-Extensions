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
		PREFIX_INFO,
		PREFIX_DEBUG,
		PREFIX_SUCCESS,
		PREFIX_WARNING,
		PREFIX_ERROR,
		PREFIX_MAX
	};

	/** \brief Locations where events may be logged. */
	enum ELocation
	{
		LOCATION_CONNECTIVITY,
		LOCATION_FILESYSTEM,
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

	bool Initialize( ) override;

	/** \brief Converts time since epoch to something that is legible. */
	/** \param strFormat Format for the time string. */
	/** \return Formatted time string. */
	[ [ nodiscard ] ] std::string FormatTime( const std::string& strFormat );
	/** \brief Gets the date for the beginning of a log session. */
	/** \return Current date. */
	[ [ nodiscard ] ] std::string GetDatestamp( );
	/** \brief Gets the current time in hours:minutes:seconds. */
	/** \return Current time in hours:minutes:seconds. */
	[ [ nodiscard ] ] std::string GetTimestamp( );
	/** \brief Gets the filename of the current log file. */
	/** \return Filename of the current log file. */
	[ [ nodiscard ] ] std::string GetCurrentLogFile( );
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
	std::string strErrorTime;
	/** \brief Time for displaying the date. */
	std::string strDateFormat;
	/** \brief Format for displaying the time. */
	std::string strTimeFormat;
	/** \brief Format for the log file name. */
	std::string strLogFileFormat;
	/** \brief Error message for the message box when ErrorPopup( ) is called. */
	std::string strErrorMessage;
	/** \brief The timestamp of the last time that the buffer was written to file. */
	Utilities::moment_t mmtLastLogWrite;
	/** \brief Buffer to store the events in queue to be written to file. */
	std::string strBuffer;
	/** \brief Error messages for errors that are unable to be written to the log file.\n
				They will appear in the title of error message boxes. */
	std::string strUnloggableErrorTitles[ ERROR_MAX ] { };
	/** \brief Prefix text for each of the statuses. */
	std::string strStatusPrefixes[ PREFIX_MAX ] { };
	/** \brief Locations where events can be logged which correspond with their enumerations in ELocation. */
	std::string strLocations[ LOCATION_MAX ] { };

public:

	CLogging( ) = default;

	void Shutdown( ) override;

	/** \brief Logs an event to the buffer. */
	/** \param _Prefix Prefix to denote the severity or status of the event. */
	/** \param _Location Where the event occurred. */
	/** \param strLog Text to be logged. */
	void Log( EPrefix _Prefix, ELocation _Location, const std::string& strLog );
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
	void ErrorPopup( EUnloggableError _ErrorCode );
} inline _Log;

using EUnloggableError = CLogging::EUnloggableError;
using EPrefix = CLogging::EPrefix;
using ELocation = CLogging::ELocation;
