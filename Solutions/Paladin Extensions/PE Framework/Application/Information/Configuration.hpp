/// Configuration.hpp

#pragma once

namespace Paladin
{
	class CConfiguration
	{
		std::string strPath;

	public:
		nlohmann::json jsGlobalConfiguration;
		nlohmann::json jsConfiguration;

		CConfiguration( );

		void LoadConfiguration( std::string );
		void SaveConfiguration( std::string );
		void DeleteConfiguration( std::string );
	} extern *cfg;
}
