#pragma once

#define SPACES_PER_TAB 4

class CConfiguration;

extern CConfiguration cfg;

class CConfiguration 
{
	std::string strPath;
	
public:
	nlohmann::json jsGlobalConfiguration;
	nlohmann::json jsConfiguration;
	
	void LoadConfiguration( std::string );
	void SaveConfiguration( std::string );
	CConfiguration( );
};
