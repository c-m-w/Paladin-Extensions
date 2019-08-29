/// CText.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void CText::CreateDrawables( )
{
	const auto recLocation = GetAbsoluteLocation( );
	const auto pText = vecDrawables.emplace_back( new CDrawable( ) );
	const auto vecLocation = recLocation.FindSpace( _Bitmap.vecSize, _Horizontal, _Vertical );

	pText->Rectangle( { vecLocation, _Bitmap.vecSize }, 0xFFFFFFFF );
	pText->SetTexture( _Bitmap, GetCurrentColor( COLOR_INDEX_PRIMARY ) );
}

void CText::SetDefaultSize( )
{
	SetSize( PixelsToInches( GetTextSize( ) ) );
}

void CText::InitializeText( )
{
	bCreateDrawables = true;
	_Bitmap = _FontManager.CreateBitmap( &strText[ 0 ], _Font, _Weight, bItalic, InchesToPixels( dSize ) );
}

CText::CText( ) :
	IWidget( WIDGET_TEXT, CURSOR_ARROW )
{
	InitializeText( );
}

void CText::SetText( const std::string &strNewText )
{
	if ( strNewText.empty( ) )
		throw std::runtime_error( ENC( "Invalid text." ) );

	strText = strNewText;
	InitializeText( );
}

void CText::SetFont( EFont _NewFont )
{
	_Font = _NewFont;
	InitializeText( );
}

void CText::SetWeight( EFontWeight _NewWeight )
{
	_Weight = _NewWeight;
	InitializeText( );
}

void CText::SetItalic( bool bNewItalic )
{
	bItalic = bNewItalic;
	InitializeText( );
}

void CText::SetHeight( double dNewSize )
{
	dSize = dNewSize;
	InitializeText( );
}

void CText::SetAlignment( EAlignment _NewHorizontal, EAlignment _NewVertical )
{
	bCreateDrawables = true;
	_Horizontal = _NewHorizontal, _Vertical = _NewVertical;
}

vector2_t CText::GetTextSize( )
{
	return _Bitmap.vecSize;
}
