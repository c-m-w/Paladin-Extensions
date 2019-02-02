/// Entry Manager.hpp

#pragma once

#if !defined NO_ENTRY and !defined STD_ENTRY and !defined WIN_ENTRY and !defined DLL_ENTRY
	#pragma message( "fatal error ENTRY1: No automatic entry creation method defined. Use '#define WIN_ENTRY' or '#define DLL_ENTRY' when including the framework to use automatic entry creation. Use '#define NO_ENTRY' to disable automatic entry management." )
#elif defined NO_ENTRY and !defined STD_ENTRY and !defined WIN_ENTRY and !defined DLL_ENTRY
	#if defined _DEBUG and !defined ACKNOWLEDGED_ENTRY_WARNING_1
		#pragma message( "warning ENTRY1: You must manage console output yourself. Use '#define ACKNOWLEDGED_ENTRY_WARNING_1' to disable this warning." )
	#endif
#elif defined STD_ENTRY and !defined WIN_ENTRY and !defined DLL_ENTRY
	// main code here
#elif !defined STD_ENTRY and defined WIN_ENTRY and !defined DLL_ENTRY
	
	// windows code here
#elif !defined STD_ENTRY and !defined WIN_ENTRY and defined DLL_ENTRY
	///when we're injected, we should get the region of memory that we are in order to clear it when we unload
	// dll code here
#else
	#pragma message( "fatal error ENTRY2: Too many automatic entry creation methods defined." )
#endif
