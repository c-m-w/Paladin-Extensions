/// Analysis Protection.hpp

#pragma once

// TODO: replace all WinAPI functions with NT functions

namespace PX::AnalysisProtection
{
	/** \brief Calls common AnalysisProtection functions */
	/** \return false analysis can occur */
	bool PX_API CheckForAnalysis( );
	/** \brief Calls common AnalysisProtection functions, including those for external processes */	   
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \return false analysis can occur */
	bool PX_API CheckForAnalysisEx( HANDLE hExtensionContainer, _In_reads_( zExtensionThreads ) HANDLE* hExtensionThreads, std::size_t zExtensionThreads );
	/** \brief Calls all AnalysisProtection functions, including those for external processes */
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \return false analysis can occur */
	bool PX_API CheckForAllAnalysis( HANDLE hExtensionContainer = nullptr, _In_reads_( zExtensionThreads ) HANDLE* hExtensionThreads = nullptr, std::size_t zExtensionThreads = 0u );

	namespace DebuggerPrevention
	{
		/** \brief Forcefully deletes PX data and shuts down */
		PX_END void PX_API Destroy( const HANDLE& hExtensionContainer = nullptr ) PX_NOX;
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
		/** \brief Forces an exception at usermode & kernel level and checks how it was caught in order to evaluate the presence of a debugger */
		/** \return false if debugger catch occurred */
		bool PX_API ForceExceptions( );
		// i forgot what I was doing here, but it felt important so i'm leaving it until i remember.
		// /** \brief a */
		// /** \return */
		// bool PX_API Check
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
		
	}

	namespace Injection
	{
		
	}

	namespace Emulation
	{

	}

	namespace Sandbox
	{
		namespace Tempo
		{
			
		}

		namespace Turing
		{
			
		}
	}
}

#if defined PX_USE_NAMESPACES
using namespace PX::AnalysisProtection;
using namespace PX::AnalysisProtection::DebuggerPrevention;
using namespace PX::AnalysisProtection::DebuggerDetection;
using namespace PX::AnalysisProtection::AnalysisSoftwareDetection;
using namespace PX::AnalysisProtection::DumpPrevention;
using namespace PX::AnalysisProtection::Injection;
using namespace PX::AnalysisProtection::Sandbox;
using namespace PX::AnalysisProtection::Emulation;
using namespace PX::AnalysisProtection::Sandbox::Tempo;
using namespace PX::AnalysisProtection::Sandbox::Turing;
#endif
