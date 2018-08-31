/// PX Debug Injector.cpp

#include "PX Debug Injector.hpp"

const std::wstring wstrApplication = LR"(csgo.exe)";
const std::wstring wstrLibraryPath = LR"(C:\Users\Cole\Documents\GitHub\Paladin\Solutions\Paladin Extensions\Debug\PX CSGO.dll)";

int main( )
{
	if ( !PX::sys::LoadLibraryEx( wstrApplication, wstrLibraryPath ) )
	{
		std::wcout << "Loading library " << wstrLibraryPath.substr( wstrLibraryPath.find_last_of( L'\\' ) ) << " into process " << wstrApplication << " failed." << std::endl;
		std::cout << "Error code: 0x" << std::hex << GetLastError( ) << std::endl;
		system( "pause" );
	}
}
