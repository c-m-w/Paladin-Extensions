#include "../main.h"

CreateInterfaceFn CInterface::GetModuleFactory( HMODULE hModule )
{
	return reinterpret_cast< CreateInterfaceFn >( GetProcAddress( hModule, "CreateInterface" ) );
}

void CInterface::Initialize( )
{
	HMODULE hClientBase = GetModuleHandle( L"client.dll" );
	CreateInterfaceFn cifClient = GetModuleFactory( hClientBase );
}

CInterface ntf;
