#include "Framework.hpp"

CConfiguration cfg;

void CConfiguration::LoadConfiguration( std::wstring wstrConfig )
{
	std::ifstream fFile( wstrPath + wstrConfig + std::wstring( L".json" ) );

	try fFile >> jsConfiguration;
	catch ( nlohmann::detail::parse_error &ex )	// TODO: Formatting Errors
	catch ( nlohmann::json::type_error &ex )	// TODO: Missing Variables 

	fFile.close( );	
}	

void CConfiguration::SaveConfiguration( std::wstring wstrConfig )	
{
	std::ofstream fFile( wstrPath + wstrConfig, std::ofstream::trunc );
	fFile << jsConfiguration.dump( SPACES_PER_TAB );
	fFile.close( );	
}	

CConfiguration::CConfiguration( )	
{
	wchar_t wchTemp[ MAX_PATH ];
	GetModuleFileName( nullptr, wchTemp, MAX_PATH );
	wstrPath = std::wstring( wchTemp ).substr( 0, std::wstring( wchTemp ).find_last_of( L"/\\" ) + 1 ) + L"Configurations\\";
	
	std::ifstream fFile( wstrPath + L"global.json" );
	try fFile >> jsGlobalConfiguration;
	catch ( nlohmann::detail::parse_error &ex )	// TODO: Formatting Errors
	catch ( nlohmann::json::type_error &ex )	// TODO: Missing Variables
	
	LoadConfiguration( jsGlobalConfiguration[ "Default Configuration" ] );
	fFile.close( );
}
