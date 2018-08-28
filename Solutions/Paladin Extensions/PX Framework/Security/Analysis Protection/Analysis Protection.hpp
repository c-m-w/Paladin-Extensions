/// Analysis Protection.hpp

#pragma once

// TODO: replace all WinAPI functions with NT functions

namespace PX::AnalysisProtection
{
	namespace Debug
	{
		/** \brief Checks presence of remote debugger using WinAPI */
		/** \param hTarget Target to check presence of remote debugger */
		/** \return true if found */
		bool RemoteDebuggerPresence( HANDLE hTarget = GetCurrentProcess( ) );


	}

	namespace Analysis
	{
		/** \brief Checks if analysis tools are installed\n
			Slow, only needs to be called once per instance */
		/** \return true if one tool from list is found to be installed */
		bool AnalysisToolsInstalled( );
		/** \brief Checks if analysis tools are running */
		/** \return true if one tool from list is found running */
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

	bool CheckAll( );
}

#if defined PX_USE_NAMESPACES
using namespace PX::AP;
#endif
