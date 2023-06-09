/// CImage.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CImage::CreateDrawables( )
{
	const auto pDrawable = vecDrawables.emplace_back( new CDrawable( ) );

	pDrawable->Rectangle( GetAbsoluteLocation( ), GetCurrentColor( COLOR_INDEX_PRIMARY ) );
	pDrawable->SetTexture( strResourceName );
}

CImage::CImage( const std::string &strResourceName ):
	IWidget( WIDGET_IMAGE, CURSOR_ARROW ), strResourceName( strResourceName )
{ }
