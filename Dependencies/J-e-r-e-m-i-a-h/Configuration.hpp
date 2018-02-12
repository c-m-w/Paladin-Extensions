#pragma once

#define SPACES_PER_TAB 4

class CConfiguration;

extern CConfiguration cfg;

class CConfiguration 
{
	std::wstring wstrPath { };
	
public:
	nlohmann::json jsConfiguration { };
	
	void LoadConfiguration( std::wstring );
	void SaveConfiguration( std::wstring );
	CConfiguration( );
};
