/// Analysis Protection.hpp

#pragma once

// TODO: replace all WinAPI functions with NT functions

namespace PX::AnalysisProtection
{
	namespace DebuggerDetection
	{
		/** \brief Checks presence of debugger */
		/** \param hTarget Target to check presence of remote debugger */
		/** \return false if found */
		bool DebuggerPresenceEx( HANDLE hTarget );
		/** \brief Checks presence of debugger (calls EX) */
		/** \return false if found */
		bool DebuggerPresence( );
		/** \brief Forces an exception at usermode & kernel level and checks how it was caught in order to evaluate the presence of a debugger */
		/** \return false if debugger catch occurred */
		bool ForceExceptions( );
	}

	namespace AnalysisSoftwareDetection
	{
		/** \brief Checks if analysis tools are installed\n
			Slow, only needs to be called once per instance */
		/** \return false if one tool from list is found to be installed */
		bool AnalysisToolsInstalled( );
		/** \brief Checks if analysis tools are running */
		/** \return false if one tool from list is found running */
		bool AnalysisToolsRunning( );
	}

	namespace Dump
	{
		
	}

	namespace Injection
	{
		
	}

	namespace Sandbox
	{
		namespace Timely
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
