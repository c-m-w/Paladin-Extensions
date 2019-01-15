/// Functionality.hpp

#pragma once

namespace PX::Functionality
{
	PX_SDK auto bCancelInstallation = false;
	PX_SDK auto uProgress = 0u;
	PX_SDK bool bExtensionAccess[ PX_EXTENSION_MAX ];
	PX_SDK auto bTerminating = false;
	PX_SDK auto bLoggedIn = false;
	PX_SDK auto iLoginStatus = -1;
	PX_SDK str_t strInstallDirectory;
	void PX_API Install( );
	void PX_API Rollback( );
	void PX_API Uninstall( );
}
