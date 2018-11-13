/// Analysis Protection.hpp

#pragma once

// TODO: replace all WinAPI functions in solution with NT functions since we have a neat API for it now

namespace PX::AnalysisProtection
{
	/** \brief Calls common AnalysisProtection functions */
	/** \return false analysis can occur */
	bool PX_API CheckForAnalysis( );
	/** \brief Calls common AnalysisProtection functions, including those for external processes */	   
	/** \param hExtensionThreads Array of threads to check */
	/** \param zExtensionThreads Size of thread array */
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \return false analysis can occur */
	bool PX_API CheckForAnalysisEx( HANDLE hExtensionContainer = nullptr, _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads = nullptr, std::size_t zExtensionThreads = 0u );
	/** \brief Calls all AnalysisProtection functions, including those for external processes */
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \param hExtensionThreads Array of threads to check */
	/** \param zExtensionThreads Size of thread array */
	/** \return false analysis can occur */
	bool PX_API CheckForAllAnalysis( HANDLE hExtensionContainer = nullptr, _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads = nullptr, std::size_t zExtensionThreads = 0u );

	namespace DebuggerPrevention
	{
		/** \brief Forcefully deletes PX data and shuts down */
		PX_END void PX_API Destroy( const HANDLE &hExtensionContainer = nullptr ) PX_NOX;
		/** \brief Sets HideThreadFromDebugger flag so that debuggers cannot see thread */
		/** \param hTargetThread Target to set the HideThreadFromDebugger flag */
		/** \return false if setting failed */
		bool PX_API HideThreadFromDebugger( HANDLE hTargetThread = GetCurrentThread( ) );
	}

	namespace DebuggerDetection
	{
		/** \brief Checks presence of debugger */
		/** \param hTargetProcess Target to check presence of remote debugger */
		/** \return false if debugger found */
		bool PX_API DebuggerPresenceEx( HANDLE hTargetProcess = GetCurrentProcess( ) );
		/** \brief Checks presence of debugger (calls EX) */
		/** \return false if debugger found */
		bool PX_API DebuggerPresence( );
		/** \brief Forces an exception at usermode & kernel level and checks how it was caught in order to evaluate the presence of a debugger\n */
		/** \return false if debugger catch occurred */
		bool PX_API ExternalExceptionHandlingPresence( );
		/** \brief Checks for the presence of software breakpoints */
		/** \return false if breakpoints exist */
		bool PX_API SoftwareBreakpointPresence( );
		/** \brief Checks for the presence of hardware breakpoints in specified threads */
		/** \param hExtensionThreads Array of threads to check */
		/** \param zExtensionThreads Size of thread array */
		/** \return false if breakpoints exist */
		bool PX_API HardwareBreakpointPresenceEx( _In_reads_( zExtensionThreads ) HANDLE *hExtensionThreads = nullptr, std::size_t zExtensionThreads = 0u );
	}

	namespace AnalysisSoftwareDetection
	{
		/** \brief Checks if analysis tools are installed\n
			Slow, only needs to be called once per instance */
		/** \return false if one tool from list is found to be installed */
		bool PX_API AnalysisToolsInstalled( );
		/** \brief Checks if analysis tools are running */
		/** \return false if one tool from list is found running */
		bool PX_API AnalysisToolsRunning( );
	}

	namespace DumpPrevention
	{
		/** \brief Replaces the marked image base address to change where dumpers begin writing memory */
		/** \return false if replace failed */
		bool PX_API ReplaceImageBase( ) PX_NOX;
	}

	namespace Emulation
	{
		namespace Tempo
		{ }

		namespace Turing
		{ }
	}
}

#if defined PX_USE_NAMESPACES
using namespace PX::AnalysisProtection;
using namespace PX::AnalysisProtection::DebuggerPrevention;
using namespace PX::AnalysisProtection::DebuggerDetection;
using namespace PX::AnalysisProtection::AnalysisSoftwareDetection;
using namespace PX::AnalysisProtection::DumpPrevention;
using namespace PX::AnalysisProtection::Emulation;
using namespace PX::AnalysisProtection::Emulation::Tempo;
using namespace PX::AnalysisProtection::Emulation::Turing;
#endif
