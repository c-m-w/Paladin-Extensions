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
	if ( !bImageData )
		pDrawable->SetTexture( strResourceName, recLocation.vecSize, &bImageData );
	else
		pDrawable->SetTexture( bImageData, recLocation.vecSize );
}

void CVectorGraphic::SetResourceName( const std::string &strNewResourceName )
{
	if ( _ResourceManager.ResourceExists( strNewResourceName ) )
		strResourceName = strNewResourceName, delete[ ] bImageData, bImageData = nullptr;
}

CVectorGraphic::CVectorGraphic( ) :
	IWidget( WIDGET_VECTOR_GRAPHIC, CURSOR_ARROW )
{ }
