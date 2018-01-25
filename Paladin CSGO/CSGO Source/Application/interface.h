#pragma once

typedef void *( *CreateInterfaceFn )( const char *, int * );

class CInterface
{
	CreateInterfaceFn GetModuleFactory( HMODULE );

	template< typename xDatatype > xDatatype *GetInterface( CreateInterfaceFn cifInterface, const char *szInterfaceName )
	{
		return reinterpret_cast< xDatatype * >( cifInterface( szInterfaceName, nullptr ) );
	}

public:
	void Initialize( );
};

extern CInterface ntf;
