/// CWindow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CWindow::CWindow( EWindowFlags _Flags, const rectangle_t& recLocation ) :
	IContainer( recLocation ), _Flags( _Flags )
{ }

void CWindow::SetTitle( const std::string& strNewTitle )
{
	strTitle = strNewTitle;
}

void CWindow::SetSubtitle( const std::string& strNewSubtitle )
{
	strSubtitle = strNewSubtitle;
}

void CWindow::CreateDrawables( )
{
	color_t clrColor = BACKGROUND_DARK;
	vecDrawables.emplace_back( new CDrawable( ) );


	if ( _State & STATE_CLICKING )
		clrColor = BLUE;
	else if ( _State & STATE_ACTIVATED )
		clrColor = DARK_BLUE;
	else if ( _State & STATE_HOVERING )
		clrColor = BACKGROUND_LIGHT;

	vecDrawables.back( )->Rectangle( GetAbsoluteLocation( ), clrColor );
}
