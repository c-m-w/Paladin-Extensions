/// System Information.hpp

#pragma once

namespace PX
{
	namespace sys
	{
		enum
		{
			SYS_CPU, SYS_GPU, SYS_DISPLAY, SYS_OS, SYS_BOARD, SYS_MAX
		};

		PX_SDK std::wstring wstrSystemParts[ SYS_MAX ];
		PX_SDK std::wstring wstrInstallUSBName;
		PX_SDK std::deque< std::wstring > dqApps;

		/** \brief Puts system info into info variables. */
		void GetSystemInfo( );
	}
}
