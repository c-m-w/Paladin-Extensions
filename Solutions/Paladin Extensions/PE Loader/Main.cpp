/// Main.cpp

#include "Main.hpp"
#include <Framework.hpp>

void OnLaunch( )
{
	unsigned asd[ ] = { 500, 500 };
	Paladin::ui = new Paladin::CUserInterface( "men", asd );
	Paladin::ui->InitializeUserInterface( );
}
