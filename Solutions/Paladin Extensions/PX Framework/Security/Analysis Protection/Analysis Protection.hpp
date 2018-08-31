/// Analysis Protection.hpp

#pragma once

// TODO: replace all WinAPI functions with NT functions

namespace PX::AnalysisProtection
{
	/** \brief Calls common AnalysisProtection functions */
	/** \return false analysis can occur */
	PX_INL bool PX_API CheckForAnalysis( );
	/** \brief Calls common AnalysisProtection functions, including those for external processes */	   
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \return false analysis can occur */
	PX_INL bool PX_API CheckForAnalysisEx( HANDLE hExtensionContainer );
	/** \brief Calls all AnalysisProtection functions, including those for external processes */
	/** \param hExtensionContainer Target of extension container to check for analysis */
	/** \return false analysis can occur */
	PX_INL bool PX_API CheckForAllAnalysis( HANDLE hExtensionContainer );

	namespace DebuggerDetection
	{
		/** \brief Checks presence of debugger */
		/** \param hTarget Target to check presence of remote debugger */
		/** \return false if found */
		PX_INL bool PX_API DebuggerPresenceEx( HANDLE hTarget );
		/** \brief Checks presence of debugger (calls EX) */
		/** \return false if found */
		PX_INL bool PX_API DebuggerPresence( );
		/** \brief Checks presence of debugger by setting up SEH and calling interrupt[ 0x2D ]  */
		/** \return false if debugger catch occurred */
		PX_INL bool PX_API Interrupt0x2D( );
		/** \brief Forces an exception at usermode & kernel level and checks how it was caught in order to evaluate the presence of a debugger */
		/** \return false if debugger catch occurred */
		PX_INL bool PX_API ForceExceptions( );
	}

	namespace AnalysisSoftwareDetection
	{
		/** \brief Checks if analysis tools are installed\n
			Slow, only needs to be called once per instance */
		/** \return false if one tool from list is found to be installed */
		PX_INL bool PX_API AnalysisToolsInstalled( );
		/** \brief Checks if analysis tools are running */
		/** \return false if one tool from list is found running */
		PX_INL bool PX_API AnalysisToolsRunning( );
	}

	namespace Dump
	{
		
	}

	namespace Injection
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

	namespace Emulation
	{
		
	}
}

#if defined PX_USE_NAMESPACES
using namespace PX::AnalysisProtection;
#endif
