/// PX Debug Injector.cpp

#include "PX Precompiled.hpp"
#include "PX Debug Injector.hpp"

const wstr_t wstrApplication = LR"(csgo.exe)";
//= LR"(csgo.exe)";
//= LR"(Empty.exe)";
const wstr_t wstrLibraryPath = LR"(C:\Users\Jeremiah\Desktop\PX CSGO.dll)";
//= LR"(C:\Users\Jeremiah\Documents\Paladin Extensions\Solutions\Paladin Extensions\Debug\PX CSGO.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX & PXLOG Debug.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX & PXLOG Release.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX & PXLOG Debug.vmp.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX & PXLOG Release.vmp.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX Debug.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX Release.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX Debug.vmp.dll)";
//= LR"(C:\Users\Jeremiah\Desktop\MSGBOX Release.vmp.dll)";

int main( )
{
#if defined PX_USE_RAW
	PX::Net::Login( );
	PX::Net::RequestExtensionInformation( PX_EXTENSION_CSGO );
	auto pFile = _wfopen( wstrLibraryPath.c_str( ), L"rb" );
	fseek( pFile, 0, SEEK_END );
	const auto sSize = ftell( pFile );
	rewind( pFile );
	const auto pData = new char[ sSize ];
	fread( pData, sizeof( char ), sSize, pFile );
	fclose( pFile );
	if ( !PX::sys::LoadRawLibraryEx( pData, wstrApplication, new injection_info_t( ), nullptr, nullptr ) )
	{
		std::wcout << "Loading library " << wstrLibraryPath.substr( wstrLibraryPath.find_last_of( L'\\' ) + 1 ) << " into process " << wstrApplication << " failed." << std::endl;
		std::cout << "Error code: 0x" << std::hex << GetLastError( ) << std::endl;
		system( "pause" );
	}
#else
	if ( !PX::sys::LoadLibraryEx( wstrApplication, wstrLibraryPath ) )
	{
		std::wcout << "Loading library " << wstrLibraryPath.substr( wstrLibraryPath.find_last_of( L'\\' ) + 1 ) << " into process " << wstrApplication << " failed." << std::endl;
		std::cout << "Error code: 0x" << std::hex << GetLastError( ) << std::endl;
		system( "pause" );
	}
#endif
}
