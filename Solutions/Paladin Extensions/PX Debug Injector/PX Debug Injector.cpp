/// PX Debug Injector.cpp

#include "PX Precompiled.hpp"
#include "PX Debug Injector.hpp"

const wstr_t wstrApplication = LR"(csgo.exe)";
const wstr_t wstrLibraryPath = LR"(C:\Users\Cole\Documents\GitHub\Paladin-Extensions\Solutions\Paladin Extensions\Debug\PX CSGO.dll)";

int main( )
{
	if ( !PX::sys::LoadLibraryEx( wstrApplication, wstrLibraryPath ) )
	{
		std::wcout << "Loading library " << wstrLibraryPath.substr( wstrLibraryPath.find_last_of( L'\\' ) + 1 ) << " into process " << wstrApplication << " failed." << std::endl;
		std::cout << "Error code: 0x" << std::hex << GetLastError( ) << std::endl;
		system( "pause" );
	}
}
