/// PX Debug Injector.cpp

#include "PX Precompiled.hpp"
#include "PX Debug Injector.hpp"

const std::wstring wstrApplication = LR"(csgo.exe)";
//const std::wstring wstrLibraryPath = LR"(C:\Users\Cole\Documents\GitHub\Paladin\Solutions\Paladin Extensions\Debug\PX CSGO.dll)";
const std::wstring wstrLibraryPath = LR"(C:\Users\Jeremiah\Desktop\Test\Debug\Test.dll)";

int main( )
{
	const auto fnGetFileData = [ ]( wcstr_t szPathToFile ) -> std::string
	{
		auto pResource = _wfopen( szPathToFile, PX_XOR( L"r" ) );
		px_assert( pResource );

		fseek( pResource, 0, SEEK_END );
		const auto lSize = ftell( pResource );
		rewind( pResource );

		std::string strData;
		strData.resize( lSize );
		fread( &strData[ 0 ], 1, lSize, pResource );

		fclose( pResource );
		return strData;
	};

	PVOID buf = &fnGetFileData( wstrLibraryPath.c_str( ) )[ 0 ];

	if ( !PX::sys::LoadRawLibraryEx( buf, wstrApplication, new injection_info_t( ) ) )
	//if ( !PX::sys::LoadLibraryEx( wstrApplication, wstrLibraryPath ) )
	{
		std::wcout << "Loading library " << wstrLibraryPath.substr( wstrLibraryPath.find_last_of( L'\\' ) + 1 ) << " into process " << wstrApplication << " failed." << std::endl;
		std::cout << "Error code: 0x" << std::hex << GetLastError( ) << std::endl;
		system( "pause" );
	}
}
