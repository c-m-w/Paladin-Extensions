/// PX Loader.cpp

#define PX_ENTRY_AS_WIN
#define PX_INSTANCE_ID L"Internal Testing"
#include <J-e-r-e-m-i-a-h/Entry Manager.hpp>

#include "Internal Testing.hpp"

using namespace PX;

class CVirtualTable
{
public:
	virtual void	FunctionOne( )							= 0;
	virtual void	FunctionTwo( const wchar_t* szText )	= 0;
	virtual void	FunctionThree( unsigned uFlags )		= 0;
	virtual int		FunctionFour( )							= 0;
	virtual bool	FunctionFive( bool bReturn )			= 0;
};

class CFunctions : public CVirtualTable
{
public:
	void FunctionOne( )
	{ }

	void FunctionTwo( const wchar_t* szText )
	{
		MessageBox( nullptr, szText, L"Message Box", MB_OK );
	}

	void FunctionThree( unsigned uFlags )
	{
		MessageBox( nullptr, L"Message Box", L"Message Box", uFlags );
	}

	int FunctionFour( )
	{
		return 10;
	}

	bool FunctionFive( bool bReturn )
	{
		return !bReturn;
	}
};

using fn1_t = void( __cdecl* )( void );
using fn2_t = void( __cdecl* )( const wchar_t* );
using fn3_t = void( __cdecl* )( unsigned );
using fn4_t = int( __cdecl* )( void );
using fn5_t = bool( __cdecl* )( bool );

void PX_API OnLaunch( )
{
	CFunctions obj;

	/// Calling virtual functions manually.
	// We can do this because since it's virtual, it counts as memory within the class as a 4 byte pointer. For this, we need a calling convention with a pointer( __cdecl* )
	//( *reinterpret_cast< void( __cdecl*** )( void ) >( &obj ) )[ 0 ]( ); // obj.FunctionOne( );
	//( *reinterpret_cast< fn2_t** >( &obj ) )[ 1 ]( L"Test" );
	//( *reinterpret_cast< fn3_t** >( &obj ) )[ 2 ]( MB_ICONERROR | MB_OK );
	//std::cout << ( *reinterpret_cast< fn4_t** >( &obj ) )[ 3 ]( ) << std::endl;
	//std::cout << ( *reinterpret_cast< fn5_t** >( &obj ) )[ 4 ]( true ) << std::endl;
	std::cout << Tools::EstimateTableLength( &obj );
}
