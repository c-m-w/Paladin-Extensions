/// CVectorGraphic.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CVectorGraphic::CreateDrawables( )
{
	const auto pDrawable = vecDrawables.emplace_back( new CDrawable( ) );
	const auto recLocation = GetAbsoluteLocation( );

	pDrawable->Rectangle( recLocation, 0xFFFFFFFF );
	pDrawable->SetTexture( strResourceName, recLocation.vecSize );
}

CVectorGraphic::CVectorGraphic( const std::string& strResourceName ) :
	IWidget( WIDGET_VECTOR_GRAPHIC ), strResourceName( strResourceName )
{ }
