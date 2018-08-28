/// Analysis Protection.hpp

#pragma once

void bob( );

namespace PX::AnalysisProtection
{
	namespace Debug
	{
		
	}

	namespace Analysis
	{
		bool AnalysisToolsInstalled( );
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
