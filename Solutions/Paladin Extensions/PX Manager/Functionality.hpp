/// Functionality.hpp

#pragma once

namespace Manager
{
	extensions_t PX_API RetrieveExtensionInformation( );
	std::string* PX_API RetrieveLaunchInformation( );
	std::string PX_API RequestExtensionInformation( unsigned uExtensionID );
}
