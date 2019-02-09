/// Interface.inl

#pragma once

namespace Interface
{
	inline CSlider< int >::CSlider( padding_t padBorder, int _iMinimum, int _iMaximum, int _iCurrent ): IWidget( SLIDER, ECursor::HAND, padBorder, BLUE, BLUE, BLUE, DARK_BLUE, BACKGROUND_LIGHT, BACKGROUND_LIGHT, nullptr ),
		iMinimum( _iMinimum ), iMaximum( _iMaximum ), iCurrent( _iCurrent )
	{ }

	inline void CSlider< int >::Draw( )
	{
		for ( auto &vertex: vecGeometry )
			_Draw.DrawPolygon( vertex );
	}

	inline void CSlider< int >::MouseMove( Utilities::location_t locMouse )
	{
		if ( bPressing )
		{
			const auto recAbsolute = GetAbsoluteLocation( );
			iCurrent = std::clamp( int( roundf( iMinimum + ( locMouse.x - recAbsolute.x ) / recAbsolute.flWidth * ( iMaximum - iMinimum ) ) ), iMinimum, iMaximum );
		}
		Setup( );
	}

	inline void CSlider< int >::Event( unsigned uKey, CKeyState ksState )
	{
		if ( ksState )
		{
			if ( uKey == VK_LBUTTON )
			{
				const auto recAbsolute = GetAbsoluteLocation( );
				iCurrent = std::clamp( int( roundf( iMinimum + ( _WidgetContext.locMouse.x - recAbsolute.x ) / recAbsolute.flWidth * ( iMaximum - iMinimum ) ) ), iMinimum, iMaximum );
			}
			else if ( uKey == VK_LEFT )
				iCurrent = std::clamp( int( roundf( iCurrent - float( iMaximum - iMinimum ) / recLocation.flWidth ) ), iMinimum, iMaximum );
			else if ( uKey == VK_RIGHT )
				iCurrent = std::clamp( int( roundf( iCurrent + float( iMaximum - iMinimum ) / recLocation.flWidth ) ), iMinimum, iMaximum );
		}
		Setup( );
	}

	inline void CSlider< int >::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		const auto y = recAbsolute.y + recAbsolute.flHeight / 2.f;

		vecGeometry.emplace_back( _Draw.Line( Utilities::location_t( recAbsolute.x, y ), Utilities::location_t( recAbsolute.x + recAbsolute.flWidth, y ), 3.f, *pCurrentBackground ).GetBuffer( ) );
		vecGeometry.emplace_back( _Draw.Circle( circle_t( Utilities::location_t( recAbsolute.x + recAbsolute.flWidth * ( float( iCurrent - iMinimum ) / float( iMaximum - iMinimum ) ), y ), 2.f, 24 ), *pCurrentForeground, 0.f ).GetBuffer( ) );
	}

	inline bool CSlider< int >::Scroll( short sDelta )
	{
		iCurrent = std::clamp( iCurrent + int( sDelta / abs( sDelta ) ) * std::clamp( int( roundf( float( iMaximum - iMinimum ) / recLocation.flWidth ) ), 1, iMaximum ), iMinimum, iMaximum );
		Setup( );
		return true;
	}

	inline CSlider< float >::CSlider( padding_t padBorder, float _flMinimum, float _flMaximum, float _flCurrent ): IWidget( SLIDER, ECursor::HAND, padBorder, BLUE, BLUE, BLUE, DARK_BLUE, BACKGROUND_LIGHT, BACKGROUND_LIGHT, nullptr ),
		flMinimum( _flMinimum ), flMaximum( _flMaximum ), flCurrent( _flCurrent )
	{ }

	inline void CSlider< float >::Draw( )
	{
		for ( auto &vertex: vecGeometry )
			_Draw.DrawPolygon( vertex );
	}

	inline void CSlider< float >::MouseMove( Utilities::location_t locMouse )
	{
		if ( bPressing )
		{
			const auto recAbsolute = GetAbsoluteLocation( );
			flCurrent = std::clamp( flMinimum + ( locMouse.x - recAbsolute.x ) / recAbsolute.flWidth * ( flMaximum - flMinimum ), flMinimum, flMaximum );
		}
		Setup( );
	}

	inline void CSlider< float >::Event( unsigned uKey, CKeyState ksState )
	{
		if ( ksState )
		{
			if ( uKey == VK_LBUTTON )
			{
				const auto recAbsolute = GetAbsoluteLocation( );
				flCurrent = std::clamp( flMinimum + ( _WidgetContext.locMouse.x - recAbsolute.x ) / recAbsolute.flWidth * ( flMaximum - flMinimum ), flMinimum, flMaximum );
			}
			else if ( uKey == VK_LEFT )
				flCurrent = std::clamp( flCurrent - ( flMaximum - flMinimum ) / recLocation.flWidth, flMinimum, flMaximum );
			else if ( uKey == VK_RIGHT )
				flCurrent = std::clamp( flCurrent + ( flMaximum - flMinimum ) / recLocation.flWidth, flMinimum, flMaximum );
		}
		Setup( );
	}

	inline bool CSlider< float >::Scroll( short sDelta )
	{
		flCurrent = std::clamp( flCurrent + sDelta / fabsf( float( sDelta ) ) * float( flMaximum - flMinimum ) / recLocation.flWidth, flMinimum, flMaximum );
		Setup( );
		return true;
	}

	inline void CSlider< float >::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		const auto y = recAbsolute.y + recAbsolute.flHeight / 2.f;

		vecGeometry.emplace_back( _Draw.Line( Utilities::location_t( recAbsolute.x, y ), Utilities::location_t( recAbsolute.x + recAbsolute.flWidth, y ), 3.f, *pCurrentBackground ).GetBuffer( ) );
		vecGeometry.emplace_back( _Draw.Circle( circle_t( Utilities::location_t( recAbsolute.x + recAbsolute.flWidth * ( ( flCurrent - flMinimum ) / ( flMaximum - flMinimum ) ), y ), 2.f, 24 ), *pCurrentForeground, 0.f ).GetBuffer( ) );
	}

	inline CEditLabel< int >::CEditLabel( padding_t _padBorder, padding_t padText, int iFont, int iStartValue ): IContainer( FLAG_CONTAINER_NONE, _padBorder, CLEAR ), lblDisplay( padText, new text_t( std::string( ), iFont, 14, text_t::LEFT, text_t::TOP ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
	{
		ClearRow( 0 );
		AddWidgetToRow( &inputEdit, recLocation.flWidth, 0 );
		inputEdit.SetActive( );
		bEditing = true;
	} ),
		inputEdit( padding_t( ), padText, iFont, CInputBox::INTEGER, std::to_string( iStartValue ), [ & ]( )
	{
		iValue = inputEdit.IntValue( );
		ClearRow( 0 );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
		lblDisplay.SetActive( );
		bEditing = false;
	}, [ & ]( )
	{
		ClearRow( 0 );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
		lblDisplay.SetActive( );
		bEditing = false;
	} ), bEditing( false ), iValue( iStartValue )
	{
		lblDisplay.iCursor = ECursor::HAND;
	}

	inline void CEditLabel< int >::Initialize( )
	{
		AddRow( row_t( padding_t( 0.f, 0.f, 0.f, 0.f ), recLocation.flHeight ) );
		lblDisplay.padBorder = padding_t( recLocation.flHeight / 2.f - lblDisplay.txtLabel->GetHeight( ) / 2.f, 0.f, 0.f, 3.f );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
	}

	inline void CEditLabel< int >::InitializeDrawingInformation( )
	{ }

	inline void CEditLabel< int >::Draw( )
	{
		if ( bEditing )
			inputEdit.PreDraw( );
		else
		{
			lblDisplay.txtLabel->ChangeText( text_t( std::to_string( iValue ), lblDisplay.txtLabel->iFont, lblDisplay.txtLabel->iSize, text_t::CENTER, text_t::CENTER ), *lblDisplay.pCurrentForeground, EFontFlags::NONE );
			lblDisplay.PreDraw( );
		}
	}

	inline CEditLabel< float >::CEditLabel( padding_t _padBorder, padding_t padText, int iFont, int _iDigits, float flStartValue ): IContainer( FLAG_CONTAINER_NONE, _padBorder, CLEAR ), lblDisplay( padText, new text_t( std::string( ), iFont, 14, text_t::LEFT, text_t::TOP ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE, [ & ]( )
	{
		ClearRow( 0 );
		AddWidgetToRow( &inputEdit, recLocation.flWidth, 0 );
		inputEdit.SetActive( );
		bEditing = true;
	} ),
		inputEdit( padding_t( ), padText, iFont, CInputBox::FLOAT, std::to_string( flStartValue ), [ & ]( )
	{
		flValue = inputEdit.FloatValue( );
		ClearRow( 0 );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
		lblDisplay.SetActive( );
		bEditing = false;
	}, [ & ]( )
	{
		ClearRow( 0 );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
		lblDisplay.SetActive( );
		bEditing = false;
	} ), bEditing( false ), iDigits( _iDigits ), flValue( flStartValue )
	{
		lblDisplay.iCursor = ECursor::HAND;
	}

	inline void CEditLabel< float >::Initialize( )
	{
		AddRow( row_t( padding_t( ), recLocation.flHeight ) );
		lblDisplay.padBorder = padding_t( recLocation.flHeight / 2.f - lblDisplay.txtLabel->GetHeight( ) / 2.f, 0.f, 0.f, 3.f );
		AddWidgetToRow( &lblDisplay, recLocation.flWidth, 0 );
	}

	inline void CEditLabel< float >::InitializeDrawingInformation( )
	{ }

	inline void CEditLabel< float >::Draw( )
	{
		if ( bEditing )
			inputEdit.PreDraw( );
		else
		{
			auto strText = std::to_string( flValue );
			strText = strText.substr( 0, strText.find( '.' ) + iDigits );
			lblDisplay.txtLabel->ChangeText( text_t( strText, lblDisplay.txtLabel->iFont, lblDisplay.txtLabel->iSize, text_t::CENTER, text_t::CENTER ), *lblDisplay.pCurrentForeground, EFontFlags::NONE );

			lblDisplay.PreDraw( );
		}
	}
}
