/// CVectorGraphic.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CVectorGraphic::CreateDrawables( )
{
	const auto pDrawable = vecDrawables.emplace_back( new CDrawable( ) );
	const auto recLocation = GetAbsoluteLocation( );

	pDrawable->Rectangle( recLocation, GetCurrentColor( COLOR_INDEX_PRIMARY ) );
	pDrawable->SetTexture( strResourceName, recLocation.vecSize );
}

void CVectorGraphic::SetResourceName( const std::string &strNewResourceName )
{
	if ( _ResourceManager.ResourceExists( strNewResourceName ) )
		strResourceName = strNewResourceName;
}

CVectorGraphic::CVectorGraphic( ) :
	IWidget( WIDGET_VECTOR_GRAPHIC, CURSOR_ARROW )
{ }
