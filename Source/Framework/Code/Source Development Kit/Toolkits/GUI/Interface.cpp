/// Interface.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

namespace Interface
{
	decltype( _WidgetContext ) _WidgetContext;

	void decltype( _WidgetContext )::BringWidgetContainingWindowToFront( IWidget* pWidget )
	{
		auto pWindow = reinterpret_cast< CWindow* >( pWidget );

		while ( pWindow->pParentContainer != nullptr )
			pWindow = decltype( pWindow )( pWindow->pParentContainer );

		for ( auto u = 0u; u < vecWindows.size( ); u++ )
			if ( vecWindows[ u ] == pWindow )
			{
				vecWindows.erase( vecWindows.begin( ) + u );
				break;
			}

		vecWindows.emplace_front( pWindow );
	}

	CWindow* decltype( _WidgetContext )::GetForegroundWindow( )
	{
		auto pWindow = vecWindows[ 0 ];

		while ( pWindow->pPopup != nullptr )
			pWindow = pWindow->pPopup;

		while ( pWindow->wfFlags & CWindow::FLAG_WINDOW_NONBLOCK )
			pWindow = decltype( pWindow )( pWindow->pParentContainer );

		return pWindow;
	}

	void decltype( _WidgetContext )::DoToolTip( )
	{
		constexpr auto TOOLTIP_WAIT = 1500ull;
		static auto locOld = locMouse;
		static auto mmtStart = GetMoment( );
		static CWindow* pToolTipWindow = nullptr;

		if ( locOld != locMouse )
		{
			if ( pToolTipWindow != nullptr )
			{
				pToolTipWindow->ClosePopup( false );
				pToolTipWindow = nullptr;
			}

			locOld = locMouse;
			mmtStart = GetMoment( );
			return;
		}

		if ( GetMoment( ) - mmtStart >= TOOLTIP_WAIT
			 && pToolTipWindow == nullptr
			 && pHoveringWidget != nullptr
			 && pHoveringWidget->uState == IWidget::HOVER
			 && pHoveringWidget->pToolTip != nullptr )
		{
			const auto recWidgetLocation = pHoveringWidget->GetAbsoluteLocation( );
			auto& recToolTip = pHoveringWidget->pToolTip->recLocation;

			pToolTipWindow = pHoveringWidget->GetContainingWindow( );
			recToolTip.x = std::clamp( recWidgetLocation.x + recWidgetLocation.flWidth / 2.f - pToolTipWindow->recLocation.x - recToolTip.flWidth / 2.f, 0.f, pToolTipWindow->recLocation.flWidth - recToolTip.flWidth );
			recToolTip.y = std::clamp( recWidgetLocation.y - 25.f - pToolTipWindow->recLocation.y - recToolTip.flHeight / 2.f, 0.f, pToolTipWindow->recLocation.flHeight - recToolTip.flHeight );
			auto pWindow = new CToolTip { *pHoveringWidget->pToolTip };
			pWindow->flWidgetRatio = ( recWidgetLocation.x + recWidgetLocation.flWidth / 2.f - pToolTipWindow->recLocation.x ) / recToolTip.flWidth;
			for ( auto& widget : pWindow->vecWidgets )
				widget->pParentContainer = pWindow;

			pToolTipWindow->Popup( pWindow );
		}
	}

	void decltype( _WidgetContext )::ApplyCursor( )
	{
		int iTexture = ECursor::ARROW;
		if ( pHoveringWidget != nullptr
			 && pHoveringWidget->GetContainingWindow( ) == GetForegroundWindow( ) )
			iTexture = pHoveringWidget->iCursor;

		_Drawing.ApplyCursor( iTexture );
	}

	void decltype( _WidgetContext )::UpdateContainerWidgets( IContainer* pContainer )
	{
		pContainer->Setup( );

		for ( auto& widget : pContainer->vecWidgets )
		{
			if ( widget->iType == IWidget::CONTAINER )
				UpdateContainerWidgets( reinterpret_cast< IContainer* >( widget ) );
			else
				widget->Setup( );
		}
	}

	bool IWidget::IsCovered( )
	{
		return false;
	}

	IWidget::IWidget( int _iType, int _iCursor, CToolTip* _pToolTip ): iType( _iType ), iCursor( _iCursor ), uState( DORMANT ), pToolTip( _pToolTip )
	{ }

	IWidget::IWidget( int _iType, int _iCursor, padding_t _padBorder, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, CToolTip* _pToolTip ) :
		iType( _iType ), iCursor( _iCursor ), uState( DORMANT ), padBorder( _padBorder ), clrForeground { clrForegroundActive, clrForegroundHover, clrForegroundDormant }, clrBackground { clrBackgroundActive, clrBackgroundHover, clrBackgroundDormant },
		pCurrentForeground( &clrForeground[ DORMANT ] ), pCurrentBackground( &clrBackground[ DORMANT ] ), iAlignment( DEFAULT_ALIGNMENT ), recLocation( { } ), bPressing( false ), pToolTip( _pToolTip )
	{ }

	IWidget::IWidget( int _iType, int _iCursor, padding_t _padBorder, color_t clrColor, CToolTip* _pToolTip ) : iType( _iType ), iCursor( _iCursor ), uState( DORMANT ), padBorder( _padBorder ), clrForeground { clrColor, clrColor , clrColor }, clrBackground { clrColor, clrColor, clrColor },
		pCurrentForeground( &clrForeground[ DORMANT ] ), pCurrentBackground( &clrBackground[ DORMANT ] ), iAlignment( DEFAULT_ALIGNMENT ), recLocation( { } ), bPressing( false ), pToolTip( _pToolTip )
	{ }

	void IWidget::Initialize( )
	{ }

	void IWidget::NoLongerActive( )
	{ }

	void IWidget::SetRectangle( rectangle_t recNew )
	{
		recLocation = recNew;
	}

	void IWidget::MouseMove( location_t locMouse )
	{ }

	void IWidget::KeyTyped( unsigned uKey )
	{ }

	void IWidget::Event( unsigned uKey, CKeyState ksState )
	{ }

	bool IWidget::Scroll( short sDelta )
	{
		return false;
	}

	void IWidget::Setup( )
	{
		for ( auto& vertex : vecGeometry )
			vertex.pVertexBuffer->Release( );

		vecGeometry.clear( );
		InitializeDrawingInformation( );
	}

	void IWidget::ModifyActivity( int iState )
	{
		bPressing = ( uState = iState ) == ACTIVE;
		pCurrentForeground = &clrForeground[ iState ];
		pCurrentBackground = &clrBackground[ iState ];

		if ( iType == CONTAINER )
			return;

		Setup( );
	}

	void IWidget::PreDraw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		if ( iType == CONTAINER
			 && reinterpret_cast< IContainer* >( this )->bUpdate )
		{
			_WidgetContext.UpdateContainerWidgets( reinterpret_cast< IContainer* >( this ) );
			reinterpret_cast< IContainer* >( this )->bUpdate = false;
		}

		if ( iType != SCROLLBAR && !_Drawing.IsAreaVisible( recAbsolute )
			 || IsCovered( ) )
			return;

		Draw( );
	}

	rectangle_t IWidget::GetAbsoluteLocation( )
	{
		auto recCurrent = recLocation;

		if ( pParentContainer != nullptr )
		{
			recCurrent += pParentContainer->GetAbsoluteLocation( );
			recCurrent.y -= reinterpret_cast< IContainer* >( pParentContainer )->flScrollAmount;
		}

		if ( iType == SCROLLBAR )
			recCurrent.y += reinterpret_cast< IContainer* >( pParentContainer )->flScrollAmount;

		return recCurrent;
	}

	rectangle_t IWidget::GetRelativeLocation( )
	{
		return rectangle_t( 0.f, 0.f, recLocation.flWidth, recLocation.flHeight );
	}

	CWindow* IWidget::GetContainingWindow( )
	{
		auto pWindow = reinterpret_cast< CWindow* >( this );
		while ( pWindow != decltype( pWindow )( 0xDDDDDDDD )
				&& pWindow->pParentContainer != nullptr
				&& pWindow->iType != POPUP )
			pWindow = decltype( pWindow )( pWindow->pParentContainer );

		return pWindow;
	}

	bool IWidget::IsActive( )
	{
		return _WidgetContext.pActiveWidget == this;
	}

	void IWidget::SetActive( )
	{
		_WidgetContext.pActiveWidget = this;
	}

	void IWidget::SetHovered( )
	{
		_WidgetContext.pHoveringWidget = this;
	}

	CLabel::CLabel( padding_t padBorder, text_t* _txtLabel, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, EFontFlags _ffFlags, callback_t _cbOnClick /*= nullptr*/ ):
		IWidget( LABEL, ECursor::ARROW, padBorder, clrForegroundActive, clrForegroundHover, clrForegroundDormant, clrBackgroundActive, clrBackgroundHover, clrBackgroundDormant, nullptr ), txtLabel( _txtLabel ), ffFlags( _ffFlags ), cbOnClick( _cbOnClick )
	{ }

	CLabel::CLabel( padding_t padBorder, text_t* _txtLabel, color_t clrBackground, color_t clrText, EFontFlags _ffFlags, callback_t _cbOnClick /*= nullptr*/ ) : IWidget( LABEL, ECursor::ARROW, padBorder, clrText, clrText, clrText, clrBackground, clrBackground, clrBackground, nullptr ), txtLabel( _txtLabel ), ffFlags( _ffFlags ), cbOnClick( _cbOnClick )
	{ }

	CLabel::CLabel( padding_t padBorder, text_t* _txtLabel, color_t clrText, EFontFlags _ffFlags, callback_t _cbOnClick /*= nullptr*/ ) : IWidget( LABEL, ECursor::ARROW, padBorder, clrText, clrText, clrText, clrText, clrText, clrText, nullptr ), txtLabel( _txtLabel ), ffFlags( _ffFlags ), cbOnClick( _cbOnClick )
	{ }

	void CLabel::Event( unsigned uKey, CKeyState ksState )
	{
		if ( ksState && uKey == VK_LBUTTON && cbOnClick )
			cbOnClick( );
	}

	void CLabel::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		txtLabel->Draw( recAbsolute );
	}

	void CLabel::InitializeDrawingInformation( )
	{
		txtLabel->Initialize( *pCurrentForeground, ffFlags );
	}

	CButtonLabel::CButtonLabel( padding_t padBorder, text_t* _txtLabel, color_t clrForegroundActive, color_t clrForegroundHover, color_t clrForegroundDormant, color_t clrBackgroundActive, color_t clrBackgroundHover, color_t clrBackgroundDormant, invoke_callback_t _cbOnClick, int _iIndex ):
		IWidget( BUTTON, ECursor::HAND, padBorder, clrForegroundActive, clrForegroundHover, clrForegroundDormant, clrBackgroundActive, clrBackgroundHover, clrBackgroundDormant, nullptr ), txtLabel( _txtLabel ), cbOnClick( _cbOnClick ), iIndex( _iIndex )
	{ }

	void CButtonLabel::Event( unsigned uKey, CKeyState ksState )
	{
		if ( ksState && uKey == VK_LBUTTON )
			cbOnClick( this );
	}

	void CButtonLabel::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		for ( auto& polygon : vecGeometry )
			_Drawing.DrawPolygon( polygon );

		txtLabel->Draw( location_t( recAbsolute.x + 5.f, recAbsolute.y + recLocation.flHeight / 2.f - txtLabel->GetHeight( ) / 2.f ) );
	}

	void CButtonLabel::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		vecGeometry.emplace_back( _Drawing.Rectangle( recAbsolute, *pCurrentBackground ).GetBuffer( ) );
		txtLabel->Initialize( *pCurrentForeground, EFontFlags::NONE );
	}

	CButton::CButton( int _iOrientation, const char* szLabel, callback_t cbOnClick, CToolTip* pToolTip /*= nullptr*/ ):
		IWidget( BUTTON, ECursor::HAND, _iOrientation == CENTER ? padding_t( 0.f, 2.f, 0.f, 2.f ) : padding_t( ), BUTTON_TEXT, BUTTON_TEXT, BUTTON_TEXT, BUTTON_BACKGROUND_ACTIVE, BUTTON_BACKGROUND_HOVER, BUTTON_BACKGROUND_DORMANT, pToolTip ),
		iType( _iOrientation ), txtLabel( new text_t( szLabel, EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ) ), cbClick( cbOnClick )
	{ }

	void CButton::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		for ( auto& object : vecGeometry )
			_Drawing.DrawPolygon( object );

		txtLabel->Draw( recAbsolute );
	}

	void CButton::InitializeDrawingInformation( )
	{
		const auto recRelative = GetAbsoluteLocation( );
		bool bCorderRounding[ ] = { iType == LEFT || iType == STANDALONE, iType == RIGHT || iType == STANDALONE, iType == RIGHT || iType == STANDALONE, iType == LEFT || iType == STANDALONE };

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( recRelative, *pCurrentBackground, bCorderRounding, ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineRoundedRectangle( recRelative, OUTLINE_DARK, bCorderRounding, ROUNDING ).GetBuffer( D3DPT_LINESTRIP ) );

		txtLabel->Initialize( *pCurrentForeground, EFontFlags::NONE );
	}

	void CButton::Event( unsigned uKey, CKeyState ksState )
	{
		if ( uKey == VK_LBUTTON && ksState )
			cbClick( );
	}

	CImage::CImage( int _iTextureID ): IWidget( IMAGE, ECursor::ARROW, nullptr ), iTextureID( _iTextureID )
	{ }

	void CImage::Draw( )
	{
		const auto recLocation = GetAbsoluteLocation( );
		_Drawing.RenderTexture( iTextureID, location_t( recLocation.x, recLocation.y ) );
	}

	void CImage::InitializeDrawingInformation( )
	{ }

	rectangle_t CInputBox::GetTextSpace( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		return rectangle_t( recAbsolute.x + padText.flPadding[ POSITION_LEFT ], recAbsolute.y + padText.flPadding[ POSITION_TOP ],
							recAbsolute.flWidth - ( padText.flPadding[ POSITION_RIGHT ] + padText.flPadding[ POSITION_LEFT ] ),
							recAbsolute.flHeight - ( padText.flPadding[ POSITION_BOTTOM ] + padText.flPadding[ POSITION_TOP ] ) );
	}

	float CInputBox::GetCursorX( )
	{
		return GetTextSpace( ).x + flCharacterWidth * iPosition - flCharacterWidth * iDisplayBegin;
	}

	float CInputBox::GetSelectionX( )
	{
		return GetTextSpace( ).x + flCharacterWidth * ( iPosition + iSelection ) - flCharacterWidth * iDisplayBegin;
	}

	void CInputBox::CorrectPosition( )
	{
		const auto recAbsolute = GetTextSpace( );
		ClampSelection( );

		if ( recAbsolute.flWidth >= flCharacterWidth * strBuffer.length( ) )
			iDisplayBegin = 0;

		while ( recAbsolute.x > GetSelectionX( ) )
			iDisplayBegin--;

		while ( recAbsolute.x + recAbsolute.flWidth < GetSelectionX( ) )
			iDisplayBegin++;
	}

	void CInputBox::ClampSelection( )
	{
		if ( iPosition < 0 )
			iPosition = 0;
		else if ( iPosition > int( strBuffer.length( ) ) )
			iPosition = strBuffer.length( );

		if ( iPosition + iSelection < 0 )
			iSelection = -iPosition;
		else if ( iPosition + iSelection > int( strBuffer.length( ) ) )
			iSelection = strBuffer.length( ) - iPosition;
	}

	int CInputBox::GetEndOfNextWord( bool bLeftward )
	{
		const auto iIncrement = bLeftward ? -1 : 1;
		auto iCurrent = iPosition;

		if ( iCurrent == int( strBuffer.length( ) ) )
			iCurrent--;
		else if ( iCurrent == 0 )
			iCurrent++;

		while ( iCurrent > 0 && iCurrent < int( strBuffer.length( ) ) && strBuffer[ iCurrent ] == ' ' )
			iCurrent += iIncrement;

		while ( iCurrent > ( bLeftward ? 0 : -1 ) && iCurrent < int( strBuffer.length( ) ) && strBuffer[ iCurrent ] != ' ' )
			iCurrent += iIncrement;

		return iCurrent;
	}

	void CInputBox::RemoveSelected( )
	{
		auto iRelative = iPosition;
		if ( iSelection < 0 )
			iRelative += iSelection;

		for ( auto i = 0; i < abs( iSelection ); i++ )
			strBuffer.erase( strBuffer.begin( ) + iRelative );

		iDisplayBegin -= abs( iSelection );
		if ( iSelection < 0 )
			iPosition += iSelection;
	}

	int CInputBox::GetHoveringPosition( )
	{
		return int( roundf( ( _WidgetContext.locMouse.x - GetTextSpace( ).x ) / flCharacterWidth ) ) + iDisplayBegin;
	}

	CInputBox::CInputBox( ): IWidget( ), padText( padding_t( ) ), locClick( { } ), iFont( 0 ), iFilter( 0 ), cbOnValueEntered( nullptr ), strBuffer( { } ), iPosition( 0 ), iSelection( 0 ), iDisplayBegin( 0 )
	{ }

	CInputBox::CInputBox( padding_t padBorder, padding_t _padText, int _iFont, int _iFilter, std::string strStartValue, callback_t _cbOnValueEntered /*= nullptr*/, callback_t _cbNoLongerActive /*= nullptr*/ ) : IWidget( INPUTBOX, ECursor::IBEAM, padBorder, BACKGROUND_LIGHT, BACKGROUND_LIGHT, BACKGROUND_DEFAULT, BACKGROUND_LIGHT, BACKGROUND_LIGHT, BACKGROUND_DEFAULT, nullptr ),
		padText( _padText ), locClick( { } ), iFont( _iFont ), iFilter( _iFilter ), cbOnValueEntered( _cbOnValueEntered ), cbNoLongerActive( _cbNoLongerActive ), strBuffer( strStartValue ), iPosition( 0 ), iSelection( 0 ), iDisplayBegin( 0 )
	{
		auto txtReference = text_t( "a", iFont, TEXT_SIZE, text_t::LEFT, text_t::TOP );
		txtReference.Initialize( color_t( { 255, 255, 255, 255 } ), EFontFlags::NONE );
		flCharacterHeight = txtReference.GetHeight( );
		flCharacterWidth = txtReference.GetWidth( );
	}

	void CInputBox::NoLongerActive( )
	{
		if ( cbNoLongerActive )
			cbNoLongerActive( );
	}

	void CInputBox::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		bool bCornerRounding[ ] { true, true, true, true };
		std::vector< polygon_t > vecOutline { };

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( recAbsolute, *pCurrentBackground, bCornerRounding, ROUND_RATIO ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineRoundedRectangle( recAbsolute, IsActive( ) ? OUTLINE_LIGHT : OUTLINE_DARK, bCornerRounding, ROUND_RATIO ).GetBuffer( D3DPT_LINESTRIP ) );
	}

	void CInputBox::Draw( )
	{
		const auto recText = GetTextSpace( );
		const auto locText = location_t( recText.x, recText.y + recText.flHeight / 2.f - flCharacterHeight / 2.f );

		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );

		_Drawing.PushDrawingSpace( recText );
		auto txtTemp = text_t( strBuffer.substr( iDisplayBegin ), iFont, TEXT_SIZE, text_t::LEFT, text_t::TOP );
		txtTemp.Initialize( IsActive( ) ? TEXT_NORMAL : TEXT_DARK, EFontFlags::NONE );
		txtTemp.Draw( locText );
		txtTemp.Destruct( );

		if ( IsActive( ) )
		{
			if ( iSelection == 0 )
			{
				if ( GetMoment( ) % 1000 <= 500ull )
					_Drawing.DrawPolygon( _Drawing.Line( location_t( GetCursorX( ), locText.y + 1.f ), location_t( GetCursorX( ), locText.y + flCharacterHeight + 2.f ), 1.f, BLUE ).GetBuffer( ), true );
			}
			else
			{
				auto flStart = GetSelectionX( ), flEnd = GetCursorX( );
				const auto flWidth = fabsf( flStart - flEnd );
				if ( flEnd < flStart )
				{
					const auto flTemp = flStart;
					flStart = flEnd;
					flEnd = flTemp;
				}

				_Drawing.DrawPolygon( _Drawing.Rectangle( rectangle_t( flStart, locText.y - 1.f, flWidth, flCharacterHeight + 2.f ), TRANSLUCENT_BLUE ).GetBuffer( ), true );
			}
		}
		_Drawing.PopDrawingSpace( );
	}

	void CInputBox::MouseMove( location_t locMouse )
	{
		if ( bPressing )
		{
			iSelection = GetHoveringPosition( ) - iPosition;
			CorrectPosition( );
		}
	}

	void CInputBox::KeyTyped( unsigned uKey )
	{
		if ( uKey == VK_BACK )
		{
			if ( iSelection != 0 )
				RemoveSelected( );
			else
			{
				if ( iPosition > 0 )
					strBuffer.erase( strBuffer.begin( ) + --iPosition );
				if ( iDisplayBegin > 0 )
					iDisplayBegin--;
			}
		}
		else if ( uKey == VK_F16 )
		{
			const auto iEnd = GetEndOfNextWord( true );

			if ( iEnd >= 0 )
			{
				for ( auto i = 0; i <= iPosition - iEnd; i++, iDisplayBegin-- )
					strBuffer.erase( iEnd + strBuffer.begin( ) );

				iPosition = iEnd;
			}
		}
		else
			if ( FILTERS[ iFilter ]( uKey, strBuffer.c_str( ), std::min( iPosition, iPosition + iSelection ) ) )
			{
				RemoveSelected( );
				ClampSelection( );
				strBuffer.insert( strBuffer.begin( ) + iPosition++, char( uKey ) );
			}

		iSelection = 0;
		CorrectPosition( );
	}

	void CInputBox::Event( unsigned uKey, CKeyState ksState )
	{
		const auto bControl = _Input.GetKeyState( VK_CONTROL ) == true,
			bShift = _Input.GetKeyState( VK_SHIFT ) == true;

		if ( ksState )
			switch ( uKey )
			{
				case VK_LBUTTON:
				{
					locClick = _WidgetContext.locMouse;
					iPosition = GetHoveringPosition( );
					iSelection = 0;
				}
				break;

				case VK_RETURN:
				{
					if ( cbOnValueEntered )
						cbOnValueEntered( );

					_WidgetContext.pActiveWidget = nullptr;
				}
				break;

				case VK_RIGHT:
				{
					if ( bShift )
					{
						if ( bControl )
						{
							const auto iOldPosition = iPosition;
							iPosition += iSelection;
							const auto iNewPosition = GetEndOfNextWord( false );
							iPosition = iOldPosition;

							if ( iNewPosition <= int( strBuffer.length( ) ) )
								iSelection = iNewPosition - iPosition;
						}
						else
							iSelection++;
					}
					else
					{
						iSelection = 0;
						if ( iPosition < int( strBuffer.length( ) ) )
						{
							if ( bControl )
							{
								const auto iNewPosition = GetEndOfNextWord( false );
								if ( iNewPosition <= int( strBuffer.length( ) ) )
									iPosition = iNewPosition;
							}
							else
								iPosition++;
						}
					}
				}
				break;

				case VK_LEFT:
				{
					if ( bShift )
					{
						if ( bControl )
						{
							const auto iOldPosition = iPosition;
							iPosition += iSelection;
							const auto iNewPosition = GetEndOfNextWord( true );
							iPosition = iOldPosition;

							if ( iNewPosition >= 0 )
								iSelection = iNewPosition - iPosition;
						}
						else
							iSelection--;
					}
					else
					{
						iSelection = 0;
						if ( iPosition > 0 )
						{
							if ( bControl )
							{
								const auto iNewPosition = GetEndOfNextWord( true );
								if ( iNewPosition >= 0 )
									iPosition = iNewPosition;
							}
							else
								iPosition--;
						}
					}
				}

				default:
					break;
			}

		CorrectPosition( );
	}

	std::string CInputBox::StringValue( )
	{
		assert( iFilter == NONE || iFilter == ALPHANUMERIC );
		return strBuffer;
	}

	int CInputBox::IntValue( )
	{
		assert( iFilter == INTEGER );
		if ( strBuffer.empty( ) )
			return 0;

		return std::stoi( strBuffer );
	}

	float CInputBox::FloatValue( )
	{
		assert( iFilter == FLOAT );
		if ( strBuffer.empty( ) )
			return 0.f;

		return std::stof( strBuffer );
	}

	CColorButton::CColorButton( padding_t padBorder, color_t* _pColor ): IWidget( BUTTON, ECursor::HAND, padBorder, *_pColor, *_pColor, *_pColor, BLUE, BLUE, OUTLINE_LIGHT, nullptr ),
		pColor( _pColor )
	{ }

	void CColorButton::Draw( )
	{
		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );
	}

	void CColorButton::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		bool bRounding[ ] { true, true, true, true };

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( recAbsolute, *pColor, bRounding, ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineRoundedRectangle( recAbsolute, *pCurrentBackground, bRounding, ROUNDING ).GetBuffer( D3DPT_LINESTRIP ) );
	}

	CScrollbar::CScrollbar( ): IWidget( SCROLLBAR, ECursor::HAND, nullptr )
	{ }

	void CScrollbar::Draw( )
	{
		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );
	}

	void CScrollbar::InitializeDrawingInformation( )
	{
		const auto pContainer = reinterpret_cast< IContainer* >( pParentContainer );
		if ( pContainer->flUsedVerticalSpace <= pContainer->recLocation.flHeight )
			return;

		const auto recLocation = GetAbsoluteLocation( );
		const auto flScrollbarHeight = recLocation.flHeight * ( recLocation.flHeight / pContainer->flUsedVerticalSpace ),
			flBegin = ( recLocation.flHeight - flScrollbarHeight ) * pContainer->flScrollAmount / ( pContainer->flUsedVerticalSpace - pContainer->recLocation.flHeight );
		bool bRounding[ ] { true, true, true, true };

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( recLocation, BACKGROUND_DIM, bRounding, 1.f ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.RoundedRectangle( rectangle_t( recLocation.x, recLocation.y + flBegin, recLocation.flWidth, flScrollbarHeight ), BLUE, bRounding, 1.f ).GetBuffer( ) );
	}

	void CScrollbar::Event( unsigned uKey, CKeyState ksState )
	{
		if ( uKey == VK_LBUTTON && ksState )
		{
			const auto pContainer = reinterpret_cast< IContainer* >( pParentContainer );
			const auto recAbsolute = GetAbsoluteLocation( );

			const auto flScrollbarHeight = recLocation.flHeight * ( recLocation.flHeight / pContainer->flUsedVerticalSpace ),
				flBegin = ( recLocation.flHeight - flScrollbarHeight ) * pContainer->flScrollAmount / ( pContainer->flUsedVerticalSpace - pContainer->recLocation.flHeight );

			if ( rectangle_t( recAbsolute.x, recAbsolute.y + flBegin, recAbsolute.flWidth, flScrollbarHeight ).LocationInRectangle( _WidgetContext.locMouse ) )
				locDragStart = _WidgetContext.locMouse;
			else
			{
				pContainer->flScrollAmount = ( pContainer->flUsedVerticalSpace - pContainer->recLocation.flHeight ) * ( _WidgetContext.locMouse.y - recAbsolute.y ) / recAbsolute.flHeight;
				locDragStart.Invalidate( );
			}

			_WidgetContext.UpdateContainerWidgets( pContainer );
		}
	}

	bool CScrollbar::Scroll( short sDelta )
	{
		const auto pContainer = reinterpret_cast< IContainer* >( pParentContainer );

		if ( pContainer->flUsedVerticalSpace > recLocation.flHeight )
		{
			const auto flOldScroll = pContainer->flScrollAmount;
			if ( flOldScroll != ( pContainer->flScrollAmount = std::clamp( pContainer->flScrollAmount - DEFAULT_SCROLL_FACTOR * float( sDelta ), 0.f, pContainer->flUsedVerticalSpace - recLocation.flHeight - STANDARD_HEIGHT / 2.f ) ) )
			{
				_WidgetContext.UpdateContainerWidgets( pContainer );
				return true;
			}
		}
		return false;
	}

	void CScrollbar::MouseMove( location_t locMouse )
	{
		if ( bPressing && locDragStart.Valid( ) )
		{
			const auto pContainer = reinterpret_cast< IContainer* >( pParentContainer );
			const auto flDifference = locMouse.y - locDragStart.y;
			const auto  flScrollbarHeight = recLocation.flHeight * ( recLocation.flHeight / pContainer->flUsedVerticalSpace ),
				flPotential = pContainer->flUsedVerticalSpace - pContainer->recLocation.flHeight,
				flHeightDifference = recLocation.flHeight - flScrollbarHeight,
				flBegin = flHeightDifference * pContainer->flScrollAmount / flPotential + flDifference;

			pContainer->flScrollAmount = std::clamp( flBegin * flPotential / flHeightDifference, 0.f, pContainer->flUsedVerticalSpace - pContainer->recLocation.flHeight );
			locDragStart = locMouse;
			pContainer->bUpdate = true;
		}
	}

	CCombobox::CCombobox( text_t* _txtTitle, std::initializer_list< text_t* > initOptions ): IWidget( COMBOBOX, ECursor::HAND, padding_t( ), TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, CLEAR, CLEAR, CLEAR, nullptr ), txtTitle( _txtTitle ), iValue( 0 ), vecText( initOptions ), vecOptions( { } )
	{ }

	void CCombobox::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );

		txtTitle->Draw( location_t( recAbsolute.x + 5.f, recAbsolute.y + recAbsolute.flHeight / 2.f - txtTitle->GetHeight( ) / 2.f ) );
	}

	void CCombobox::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		bool bRounding[ ] { true, true, true, true };

		txtTitle->Initialize( *pCurrentForeground, EFontFlags::NONE );
		vecGeometry.emplace_back( _Drawing.RoundedRectangle( recAbsolute, *pCurrentBackground, bRounding, ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.Triangle( location_t( recAbsolute.x + recAbsolute.flWidth - 5.f - TRIANGLE_WIDTH, recAbsolute.y + recAbsolute.flHeight / 2.f - TRIANGLE_HEIGHT / 2.f ),
											location_t( recAbsolute.x + recAbsolute.flWidth - 5.f, recAbsolute.y + recAbsolute.flHeight / 2.f - TRIANGLE_HEIGHT / 2.f ),
											location_t( recAbsolute.x + recAbsolute.flWidth - 5.f - TRIANGLE_WIDTH / 2.f, recAbsolute.y + recAbsolute.flHeight / 2.f + TRIANGLE_HEIGHT / 2.f ), WHITE ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineRoundedRectangle( recAbsolute, OUTLINE_LIGHT, bRounding, ROUNDING ).GetBuffer( D3DPT_LINESTRIP ) );
	}

	void CCombobox::Event( unsigned uKey, CKeyState ksState )
	{
		if ( ksState && uKey )
		{
			const auto pContainingWindow = GetContainingWindow( );
			auto recAbsolute = GetAbsoluteLocation( );
			recAbsolute.x -= pContainingWindow->recLocation.x;
			recAbsolute.y -= pContainingWindow->recLocation.y;

			for ( auto& option : vecOptions )
				delete option;

			vecOptions.clear( );

			const auto pPopup = new CWindow( CWindow::FLAG_WINDOW_NONE, rectangle_t( recAbsolute.x, recAbsolute.y + recAbsolute.flHeight + 5.f, recAbsolute.flWidth, vecText.size( ) * 30.f ) );
			for ( auto u = 0u; u < vecText.size( ); u++ )
			{
				auto& lblCurrent = int( u ) == iValue ? vecOptions.emplace_back( new CButtonLabel( padding_t( ), vecText[ u ], BLUE, BLUE, BLUE, BACKGROUND_LIGHT, BACKGROUND_LIGHT, BACKGROUND_DEFAULT, [ & ]( IWidget* pInvokee )
				{
					iValue = reinterpret_cast< CButtonLabel* >( pInvokee )->iIndex;
					reinterpret_cast< CWindow* >( pInvokee->GetContainingWindow( )->pParentContainer )->ClosePopup( true );
				}, u ) ) : vecOptions.emplace_back( new CButtonLabel( padding_t( ), vecText[ u ], TEXT_NORMAL, TEXT_NORMAL, TEXT_DARK, BACKGROUND_LIGHT, BACKGROUND_LIGHT, BACKGROUND_DEFAULT, [ & ]( IWidget* pInvokee )
				{
					iValue = reinterpret_cast< CButtonLabel* >( pInvokee )->iIndex;
					reinterpret_cast< CWindow* >( pInvokee->GetContainingWindow( )->pParentContainer )->ClosePopup( true );
				}, u ) );

				pPopup->AddRow( row_t( padding_t( ), 30.f ) );
				pPopup->AddWidgetToRow( lblCurrent, recAbsolute.flWidth, u );
			}

			pContainingWindow->Popup( pPopup );
		}
	}

	row_t::row_t( ): flLeftFill( 0.f ), flRightFill( 0.f ), recLocation( rectangle_t( 0.f, 0.f, 0.f, DEFAULT_HEIGHT ) ), pParent( nullptr ), iRowNumber( 0 )
	{ }

	row_t::row_t( padding_t _padBorder, float _flHeight ) : padBorder( _padBorder ), flLeftFill( 0.f ), flRightFill( 0.f ), recLocation( rectangle_t( 0.f, 0.f, 0.f, _flHeight ) ), pParent( nullptr ), iRowNumber( 0 )
	{ }

	padding_t::padding_t( ) : flPadding { }
	{ }

	padding_t::padding_t( float* pPadding )
	{
		for ( auto i = 0; i < POSITION_MAX; i++ )
			flPadding[ i ] = pPadding[ i ];
	}

	padding_t::padding_t( float flTop, float flRight, float flBottom, float flLeft ): flPadding { flTop, flRight, flBottom, flLeft }
	{ }

	float padding_t::Horizontal( )
	{
		return flPadding[ POSITION_LEFT ] + flPadding[ POSITION_RIGHT ];
	}

	float padding_t::Vertical( )
	{
		return flPadding[ POSITION_TOP ] + flPadding[ POSITION_BOTTOM ];
	}

	void CPanel::Draw( )
	{
		const auto recLocation = GetAbsoluteLocation( );

		_Drawing.PushDrawingSpace( recLocation );

		_Drawing.Rectangle( recLocation, clrBackground[ 0 ] );

		for ( auto& pWidget : vecWidgets )
			pWidget->PreDraw( );

		_Drawing.PopDrawingSpace( );
	}

	void CPanel::InitializeDrawingInformation( )
	{ }

	CFileSelector::CFileSelector( callback_t cbOnFileSelected, const char* szSubject, const char* szFileExtension /*= FILE_EXTENSION_NONE*/ ): IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK ),
		lblSubject( padding_t( 0.f, 2.f, 0.f, 2.f ), new text_t( szSubject, EFont::ROBOTO, STANDARD_HEIGHT, text_t::LEFT, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE, NO_CALLBACK ),
		inputFile( padding_t( ), padding_t( 0.f, 2.f, 0.f, 2.f ), EFont::ENVY, CInputBox::ALPHANUMERIC, std::string( ), [ & ]( )
	{
		auto strResult = inputFile.StringValue( );
		if ( szExtension == nullptr
			 || strResult.find( szExtension ) == strResult.length( ) - strlen( szExtension )
			 && std::ifstream( strResult ).good( ) )
			cbOnFileSelected( );
	}, NO_CALLBACK ), btnBrowse( CButton::CENTER, "...", [ & ]( )
	{
		Popup( new CPathExplorer( szSubject, szFileExtension, [ & ]( )
		{
		} ) );
	}, nullptr ), szExtension( szFileExtension )
	{
		lblSubject.InitializeDrawingInformation( );
	}

	void CFileSelector::Initialize( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		AddRow( row_t( padding_t( ), 30.f ) );
		AddWidgetToRow( &lblSubject, lblSubject.txtLabel->GetWidth( ), 0 );

		inputFile.iAlignment = btnBrowse.iAlignment = RIGHT;
		AddWidgetToRow( &btnBrowse, 60.f, 0 );
		AddWidgetToRow( &inputFile, 150.f, 0 );
	}

	void CFileSelector::InitializeDrawingInformation( )
	{ }

	void CFileSelector::Draw( )
	{
		for ( auto& widget : vecWidgets )
			widget->PreDraw( );
	}

	std::string CFileSelector::GetFile( )
	{
		return inputFile.StringValue( );
	}

	CGroupbox::CGroupbox( padding_t _padBorder, const char* szTitle ): IContainer( FLAG_CONTAINER_SCROLLABLE, _padBorder, BACKGROUND_DEFAULT ), txtTitle( new text_t( szTitle, EFont::ROBOTO, STANDARD_HEIGHT, text_t::CENTER, text_t::CENTER ) )
	{
		VerticalSpacing( STANDARD_HEIGHT );
	}

	void CGroupbox::InitializeDrawingInformation( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );
		bool bRounding[ ] { true,true,true,true };
		color_t clrBackground[ ] { BACKGROUND_DEFAULT, BACKGROUND_DEFAULT, BACKGROUND_DARK, BACKGROUND_DARK };

		txtTitle->Initialize( TEXT_DARK, EFontFlags::DROPSHADOW );
		const auto flHalfHeight = txtTitle->GetHeight( ) / 2.f;

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( rectangle_t( recAbsolute.x, recAbsolute.y + flHalfHeight, recAbsolute.flWidth, recAbsolute.flHeight - flHalfHeight ), clrBackground, bRounding, ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineSpacedRoundedRectangle( rectangle_t( recAbsolute.x, recAbsolute.y + flHalfHeight, recAbsolute.flWidth, recAbsolute.flHeight - flHalfHeight ), OUTLINE_LIGHT, bRounding, ROUNDING, txtTitle->GetWidth( ) ).GetBuffer( D3DPT_LINESTRIP ) );
	}

	void CGroupbox::Initialize( )
	{
		AddWidget( &sbScrollbar, rectangle_t( recLocation.flWidth - CScrollbar::DEFAULT_WIDTH - CScrollbar::DEFAULT_PADDING, CScrollbar::DEFAULT_PADDING + STANDARD_HEIGHT / 2.f, CScrollbar::DEFAULT_WIDTH, recLocation.flHeight - CScrollbar::DEFAULT_PADDING * 2.f - STANDARD_HEIGHT / 2.f ) );
	}

	void CGroupbox::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );

		_Drawing.PushDrawingSpace( rectangle_t( recAbsolute.x, recAbsolute.y + STANDARD_HEIGHT / 2.f, recAbsolute.flWidth, recAbsolute.flHeight - STANDARD_HEIGHT / 2.f ) );

		for ( auto& widget : vecWidgets )
			widget->PreDraw( );

		_Drawing.PopDrawingSpace( );
		txtTitle->Draw( location_t( recAbsolute.x + std::min( recAbsolute.flWidth, recAbsolute.flHeight ) * ROUNDING, recAbsolute.y - 2.f ) );
	}

	CCheckbox::CCheckbox( padding_t padBorder, const char* szLabel, bool* _pEnabled, std::initializer_list< CColorButton* > l ): IContainer( FLAG_CONTAINER_NONE, padBorder, BLUE ),
		pEnabled( _pEnabled ), lblIconActive( padding_t( ), new text_t( ICON_FA_CHECK_SQUARE, EFont::FA, CHECKBOX_TEXT_HEIGHT, text_t::LEFT, text_t::TOP ), BLUE, EFontFlags::ICON, [ & ]( )
	{
		*pEnabled = false;
		ClearRow( 0 );
		Initialize( );
		lblIconDormant.SetHovered( );
	} ), lblIconDormant( padding_t( ), new text_t( ICON_FA_SQUARE, EFont::FA, CHECKBOX_TEXT_HEIGHT, text_t::LEFT, text_t::TOP ), BLUE, BLUE, TEXT_NORMAL, CLEAR, CLEAR, CLEAR, EFontFlags::ICON, [ & ]( )
	{
		*pEnabled = true;
		ClearRow( 0 );
		Initialize( );
		lblIconActive.SetHovered( );
	} ), lblLabel( padding_t( ), new text_t( szLabel, EFont::TAHOMA, CHECKBOX_TEXT_HEIGHT, text_t::LEFT, text_t::TOP ), TEXT_DARK, TEXT_DARK, TEXT_DARK, CLEAR, CLEAR, CLEAR, EFontFlags::NONE ), vecColors( l )
	{ }

	void CCheckbox::InitializeDrawingInformation( )
	{ }

	void CCheckbox::Initialize( )
	{
		lblIconDormant.txtLabel->Initialize( *lblIconDormant.pCurrentForeground, EFontFlags::ICON );
		lblIconActive.txtLabel->Initialize( *lblIconActive.pCurrentForeground, EFontFlags::ICON );
		if ( !lblLabel.txtLabel->Initialized( ) )
			lblLabel.txtLabel->Initialize( *lblLabel.pCurrentForeground, EFontFlags::NONE );

		const auto pDisplay = *pEnabled ? &lblIconActive : &lblIconDormant;
		const auto flIconTop = ( recLocation.flHeight - pDisplay->txtLabel->GetHeight( ) ) / 2.f,
			recTextTop = ( recLocation.flHeight - lblLabel.txtLabel->GetHeight( ) ) / 2.f;

		pDisplay->padBorder = padding_t( flIconTop, 2.f, 0.f, 5.f );
		pDisplay->iCursor = ECursor::HAND;
		lblLabel.padBorder = padding_t( recTextTop, 2.f, 0.f, 5.f );
		AddRow( row_t( padding_t( ), recLocation.flHeight ) );
		AddWidgetToRow( pDisplay, lblIconDormant.txtLabel->GetWidth( ), 0 );
		AddWidgetToRow( &lblLabel, lblLabel.txtLabel->GetWidth( ), 0 );

		for ( auto& color : vecColors )
		{
			color->iAlignment = RIGHT;
			AddWidgetToRow( color, COLOR_BUTTON_WIDTH, 0 );
		}
	}

	void CCheckbox::Draw( )
	{
		const auto recAbsolute = GetAbsoluteLocation( );

		_Drawing.PushDrawingSpace( recAbsolute );

		for ( auto& widget : vecWidgets )
			widget->PreDraw( );

		_Drawing.PopDrawingSpace( );
	}

	CHeaderPanel::CHeaderPanel( ): iIconTexture( -1 ), locDragStart( location_t( ) )
	{ }

	CHeaderPanel::CHeaderPanel( const char* szTitle, const char* szSubtitle, callback_t _cbMinimize, callback_t _cbClose, const char* szMinimize, const char* szClose ) : IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK ), iIconTexture( ETextures::TEXTURE_LOGO ),
		imgIcon( iIconTexture ), lblTitle( padding_t( ), new text_t( szTitle, EFont::ROBOTO_BOLD, TITLE_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, EFontFlags::NONE ), lblSubtitle( padding_t( ), new text_t( szSubtitle, EFont::ROBOTO, TITLE_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE ),
		lblMinimize( padding_t( ), new text_t( szMinimize, EFont::FA, WINDOW_ICON_HEIGHT, text_t::CENTER, text_t::TOP ), BLUE, EFontFlags::ICON, _cbMinimize ), lblClose( padding_t( ), new text_t( szClose, EFont::FA, WINDOW_ICON_HEIGHT, text_t::CENTER, text_t::TOP ), BLUE, EFontFlags::ICON, _cbClose ), locDragStart( location_t( ) )
	{
		lblTitle.InitializeDrawingInformation( );
		lblSubtitle.InitializeDrawingInformation( );
		lblClose.InitializeDrawingInformation( );
		lblMinimize.InitializeDrawingInformation( );
	}

	CHeaderPanel::CHeaderPanel( const char* szTitle, const char* szSubtitle, const char* szClose ): IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK ), iIconTexture( -1 ),
		lblTitle( padding_t( ), new text_t( szTitle, EFont::ROBOTO_BOLD, TITLE_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_NORMAL, EFontFlags::NONE ),
		lblSubtitle( padding_t( ), new text_t( szSubtitle, EFont::ROBOTO, TITLE_HEIGHT, text_t::CENTER, text_t::CENTER ), TEXT_DARK, EFontFlags::NONE ),
		lblClose( padding_t( ), new text_t( szClose, EFont::FA, WINDOW_ICON_HEIGHT, text_t::CENTER, text_t::TOP ), BLUE, EFontFlags::ICON, [ & ]( )
	{
		_WidgetContext.pActiveWidget = nullptr;
		reinterpret_cast< CWindow* >( pParentContainer->pParentContainer )->ClosePopup( true );
	} ), locDragStart( location_t( ) )
	{
		lblTitle.InitializeDrawingInformation( );
		lblSubtitle.InitializeDrawingInformation( );
		lblClose.InitializeDrawingInformation( );
	}

	void CHeaderPanel::InitializeDrawingInformation( )
	{
		const auto recLocation = GetAbsoluteLocation( );

		vecGeometry.emplace_back( _Drawing.Rectangle( recLocation, *clrBackground ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.Line( location_t( recLocation.x, recLocation.y + recLocation.flHeight ), location_t( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight ), 1.f, OUTLINE_LIGHT ).GetBuffer( ) );
	}

	void CHeaderPanel::Initialize( )
	{
		texture_renderable_t texIcon { };
		auto flIconPadding = 0.f;
		if ( iIconTexture > -1 )
		{
			texIcon = _Drawing.GetTexture( iIconTexture );
			flIconPadding = 20.f - texIcon.first.uHeight / 2.f;
		}

		const auto flTitlePadding = 20.f - lblTitle.txtLabel->GetHeight( ) / 2.f,
			flSubtitlePadding = 20.f - lblSubtitle.txtLabel->GetHeight( ) / 2.f,
			flClosePadding = 20.f - lblClose.txtLabel->GetHeight( ) / 2.f,
			flMinimizePadding = 20.f - ( lblMinimize.txtLabel != nullptr ? lblMinimize.txtLabel->GetHeight( ) / 2.f : 0.f );

		imgIcon.padBorder = padding_t( flIconPadding, 0.f, flIconPadding, flIconPadding );
		lblTitle.padBorder = padding_t( flTitlePadding, 0.f, flTitlePadding, flIconPadding != 0.f ? flIconPadding : flTitlePadding );
		lblSubtitle.padBorder = padding_t( flSubtitlePadding, flSubtitlePadding, flSubtitlePadding, flSubtitlePadding / 2.f );
		lblClose.padBorder = padding_t( flClosePadding, flClosePadding, 0.f, 0.f );
		lblMinimize.padBorder = padding_t( flMinimizePadding, flMinimizePadding, 0.f, flMinimizePadding );
		lblClose.iAlignment = lblMinimize.iAlignment = RIGHT;
		lblClose.iCursor = lblMinimize.iCursor = ECursor::HAND;

		AddRow( row_t( padding_t( ), recLocation.flHeight ) );
		if ( iIconTexture > -1 )
			AddWidgetToRow( &imgIcon, float( texIcon.first.uWidth ), 0 );

		AddWidgetToRow( &lblTitle, lblTitle.txtLabel->GetWidth( ), 0 );
		AddWidgetToRow( &lblSubtitle, lblSubtitle.txtLabel->GetWidth( ), 0 );

		if ( lblClose.cbOnClick != nullptr )
			AddWidgetToRow( &lblClose, lblClose.txtLabel->GetWidth( ), 0 );

		if ( lblMinimize.cbOnClick != nullptr )
			AddWidgetToRow( &lblMinimize, lblMinimize.txtLabel->GetWidth( ), 0 );
	}

	void CHeaderPanel::Draw( )
	{
		const auto recLocation = GetAbsoluteLocation( );

		for ( auto& vertex : vecGeometry )
			_Drawing.DrawPolygon( vertex );

		_Drawing.PushDrawingSpace( recLocation );

		for ( auto& pWidget : vecWidgets )
			pWidget->PreDraw( );

		_Drawing.PopDrawingSpace( );
	}

	void CHeaderPanel::Event( unsigned uKey, CKeyState ksKeyState )
	{
		if ( uKey == VK_LBUTTON && ksKeyState == true )
		{
			int x, y;
			_Input.GetMousePos( x, y );
			locDragStart = location_t( float( x ), float( y ) );
		}
	}

	void CHeaderPanel::MoveParentWindow( int x, int y )
	{
		if ( bPressing )
		{
			pParentContainer->recLocation.x += x - locDragStart.x;
			pParentContainer->recLocation.y += y - locDragStart.y;
			locDragStart = location_t( float( x ), float( y ) );

			reinterpret_cast< CWindow* >( pParentContainer )->bUpdate = true;
		}
	}

	CWindow::CWindow( unsigned _wfFlags, rectangle_t _recLocation, const char* szTitle, const char* szSubtitle, callback_t _cbMinimize, callback_t _cbClose ): wfFlags( _wfFlags ), IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK, _recLocation ),
		pHeader( new CHeaderPanel( szTitle, szSubtitle, _cbMinimize, _cbClose, ICON_FA_MINUS, ICON_FA_TIMES ) ), pPopup( nullptr )
	{
		AddRow( row_t( padding_t( ), 40.f ) );
		AddWidgetToRow( pHeader, recLocation.flWidth, 0 );
	}

	CWindow::CWindow( unsigned _wfFlags, rectangle_t _recLocation, const char* szTitle, const char* szSubtitle ): wfFlags( _wfFlags ), IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK, _recLocation ),
		pHeader( new CHeaderPanel( szTitle, szSubtitle, ICON_FA_TIMES ) ), pPopup( nullptr )
	{
		AddRow( row_t( padding_t( ), 40.f ) );
		AddWidgetToRow( pHeader, recLocation.flWidth, 0 );
	}

	CWindow::CWindow( unsigned _wfFlags, rectangle_t _recLocation ): wfFlags( _wfFlags ), IContainer( FLAG_CONTAINER_NONE, padding_t( ), BACKGROUND_DARK, _recLocation ), pHeader( nullptr ),
		pPopup( nullptr )
	{ }

	CWindow::~CWindow( )
	{
		if ( pHeader )
		{
			delete pHeader;
			pHeader = nullptr;
		}
	}

	void CWindow::InitializeDrawingInformation( )
	{
		bool bRounding[ ] { false, false, ( wfFlags & FLAG_WINDOW_ROUND_CORNERS ) > 0u, ( wfFlags & FLAG_WINDOW_ROUND_CORNERS ) > 0u };

		vecGeometry.emplace_back( _Drawing.RoundedRectangle( GetAbsoluteLocation( ), *clrBackground, bRounding, WINDOW_ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.RoundedRectangle( GetAbsoluteLocation( ), BACKGROUND_DIM, bRounding, WINDOW_ROUNDING ).GetBuffer( ) );
		vecGeometry.emplace_back( _Drawing.OutlineRoundedRectangle( recLocation, OUTLINE_LIGHT, bRounding, WINDOW_ROUNDING ).GetBuffer( D3DPT_LINESTRIP ) );
	}

	void CWindow::Draw( )
	{
		const auto recLocation = GetAbsoluteLocation( );

		_Drawing.PushDrawingSpace( recLocation );
		_Drawing.DrawPolygon( vecGeometry[ 0 ] );

		for ( auto& pWidget : vecWidgets )
			pWidget->PreDraw( );

		_Drawing.PopDrawingSpace( );

		if ( wfFlags & FLAG_WINDOW_OUTLINE_ALWAYS )
			for ( auto u = 2u; u < vecGeometry.size( ); u++ )
				_Drawing.DrawPolygon( vecGeometry[ u ] );

		if ( pPopup != nullptr )
		{
			if ( pPopup->wfFlags & FLAG_WINDOW_DIM_BACKGROUND )
			{
				auto pParent = this;
				while ( pParent->pParentContainer != nullptr )
					pParent = reinterpret_cast< CWindow* >( pParent->pParentContainer );

				_Drawing.DrawPolygon( pParent->vecGeometry[ 1 ] );
			}

			pPopup->PreDraw( );
		}
	}

	void CWindow::Popup( CWindow* _pPopup )
	{
		if ( pPopup != nullptr )
			ClosePopup( !( pPopup->wfFlags & FLAG_WINDOW_NONBLOCK ) );

		_pPopup->pParentContainer = this;
		if ( _pPopup->wfFlags & FLAG_WINDOW_ANCHOR )
			_pPopup->recLocation = rectangle_t( recLocation.flWidth / 2.f - _pPopup->recLocation.flWidth / 2.f, recLocation.flHeight / 2.f - _pPopup->recLocation.flHeight / 2.f, _pPopup->recLocation.flWidth, _pPopup->recLocation.flHeight );

		_pPopup->iType = POPUP;
		_WidgetContext.UpdateContainerWidgets( _pPopup );
		_pPopup->Setup( );
		pPopup = _pPopup;
	}

	void CWindow::ClosePopup( bool bResetWidgets )
	{
		if ( bResetWidgets )
			_WidgetContext.pActiveWidget = _WidgetContext.pHoveringWidget = nullptr;

		delete pPopup;
		pPopup = nullptr;
	}

	void CWindow::Pack( )
	{
		auto flMaxWidth = 0.f;
		recLocation.flHeight = 0.f;

		for ( auto& row : vecRows )
		{
			auto flWidth = row.padBorder.Horizontal( );
			recLocation.flHeight += row.padBorder.Vertical( ) + row.recLocation.flHeight;

			auto sSize = vecWidgets.size( );
			for ( auto u = 0u; u < sSize; u++ )
				if ( vecWidgets[ u ]->iRow == row.iRowNumber )
					flWidth += vecWidgets[ u ]->recLocation.flWidth + vecWidgets[ u ]->padBorder.Horizontal( );

			if ( flWidth > flMaxWidth )
				flMaxWidth = flWidth;
		}

		recLocation.flWidth = flMaxWidth;
	}

	CPathExplorer::CPathExplorer( const char* szSubject, const char* szExtension, callback_t cbOnFileSelected ): CWindow( POPUP_FLAGS, rectangle_t( 0.f, 0.f, 500.f, 500.f ), "Select File", szSubject ), strDesiredExtension( szExtension == nullptr ? std::string( ) : szExtension ),
		cbOnPathSelected( cbOnFileSelected ), iMode( FOLDER )
	{ }

	CPathExplorer::CPathExplorer( const char* szSubject, callback_t cbOnFolderSelected ) : CWindow( POPUP_FLAGS, rectangle_t( 0.f, 0.f, 500.f, 500.f ), "Select Folder", szSubject ), strDesiredExtension( { } ),
		cbOnPathSelected( cbOnFolderSelected ), iMode( FOLDER )
	{ }

	void CPathExplorer::InitializeDrawingInformation( )
	{

	}

	void CPathExplorer::Draw( )
	{

	}

	void CPathExplorer::Initialize( )
	{

	}

	void CToolTip::InitializeDrawingInformation( )
	{ }

	void CToolTip::Draw( )
	{
		const auto recLocation = GetAbsoluteLocation( );
		const auto dwBackground = BACKGROUND_DEFAULT.GetARGB( );

		_Drawing.PushDrawingSpace( recLocation );

		vertex_t vtxBackground[ ]
		{
			vertex_t( recLocation.x, recLocation.y, dwBackground ),
			vertex_t( recLocation.x + recLocation.flWidth, recLocation.y, dwBackground ),
			vertex_t( recLocation.x + recLocation.flWidth, recLocation.y + recLocation.flHeight, dwBackground ),
			vertex_t( recLocation.x + recLocation.flWidth * flWidgetRatio + TRIANGLE_WIDTH / 2.f, recLocation.y + recLocation.flHeight, dwBackground ),
			vertex_t( recLocation.x + recLocation.flWidth * flWidgetRatio, recLocation.y + recLocation.flHeight + TRIANGLE_HEIGHT, dwBackground ),
			vertex_t( recLocation.x + recLocation.flWidth * flWidgetRatio - TRIANGLE_WIDTH / 2.f, recLocation.y + recLocation.flHeight, dwBackground ),
			vertex_t( recLocation.x, recLocation.y + recLocation.flHeight, dwBackground )
		};

		_Drawing.Polygon( vtxBackground, 7, 5 );

		for ( auto& pWidget : vecWidgets )
			pWidget->PreDraw( );

		_Drawing.PopDrawingSpace( );

		for ( auto i = 0; i < 6; i++ )
			_Drawing.Line( location_t( vtxBackground[ i ].flVectors[ 0 ], vtxBackground[ i ].flVectors[ 1 ] ), location_t( vtxBackground[ i + 1 ].flVectors[ 0 ], vtxBackground[ i + 1 ].flVectors[ 1 ] ), 1.f, OUTLINE_LIGHT );
		
		_Drawing.Line( location_t( vtxBackground[ 0 ].flVectors[ 0 ], vtxBackground[ 0 ].flVectors[ 1 ] ), location_t( vtxBackground[ 6 ].flVectors[ 0 ], vtxBackground[ 6 ].flVectors[ 1 ] ), 1.f, OUTLINE_LIGHT );
	}

	CToolTip::CToolTip( text_t* txtToolTip ): CWindow( TOOLTIP_FLAGS, rectangle_t( ) ), vecText( { } ), flWidgetRatio( 0.f )
	{
		std::size_t sPosition { };
		auto flWidth = 0.f, flHeight = 0.f;

		while ( ( sPosition = txtToolTip->strText.find( '\n' ) ) != std::string::npos )
		{
			auto txtNew = txtToolTip;
			vecText.emplace_back( padding_t( ), new text_t( txtToolTip->strText.substr( 0, sPosition ), txtToolTip->iFont, txtToolTip->iSize, text_t::LEFT, text_t::TOP ), TEXT_NORMAL, EFontFlags::NONE );
			txtToolTip->strText = txtToolTip->strText.substr( sPosition + 1 );

			const auto flCurrentWidth = vecText.back( ).txtLabel->GetWidth( );
			if ( flCurrentWidth > flWidth )
				flWidth = flCurrentWidth;
		}
		vecText.emplace_back( padding_t( ), txtToolTip, TEXT_NORMAL, EFontFlags::NONE );
		const auto flCurrentWidth = vecText.back( ).txtLabel->GetWidth( );
		if ( flCurrentWidth > flWidth )
			flWidth = flCurrentWidth;

		flHeight = vecText[ 0 ].txtLabel->GetHeight( );

		for ( auto u = 0u; u < vecText.size( ); u++ )
		{
			vecText[ u ].padBorder = padding_t( 2.f, 5.f, flHeight / 2.f, 5.f );
			AddRow( row_t( padding_t( 2.f, 3.f, 0.f, 3.f ), flHeight ) );
			AddWidgetToRow( &vecText[ u ], flWidth, u );
		}

		Pack( );
	}

	IContainer::IContainer( unsigned _cfFlags, padding_t padBorder, color_t clrContainer ): cfFlags( _cfFlags ), IWidget( CONTAINER, ECursor::ARROW, padBorder, clrContainer, clrContainer, clrContainer, clrContainer, clrContainer, clrContainer, nullptr )
	{ }

	IContainer::IContainer( unsigned _cfFlags, padding_t padBorder, color_t clrContainer, rectangle_t _recWindowLocation ) : cfFlags( _cfFlags ), IWidget( CONTAINER, ECursor::ARROW, padBorder, clrContainer, clrContainer, clrContainer, clrContainer, clrContainer, clrContainer, nullptr )
	{
		recLocation = _recWindowLocation;
	}

	bool IContainer::Scroll( short sDelta )
	{
		return cfFlags & FLAG_CONTAINER_SCROLLABLE && sbScrollbar.Scroll( sDelta );
	}

	void IContainer::AddRow( row_t rowNew )
	{
		//for ( auto& row : vecRows )
		//	rowNew.recLocation.y += row.recLocation.flHeight + row.padBorder.Vertical( );

		rowNew.recLocation.y = flUsedVerticalSpace;
		rowNew.recLocation.y += rowNew.padBorder.flPadding[ POSITION_TOP ];
		rowNew.recLocation.x = rowNew.padBorder.flPadding[ POSITION_LEFT ];
		rowNew.recLocation.flWidth = recLocation.flWidth - ( rowNew.padBorder.flPadding[ POSITION_LEFT ] + rowNew.padBorder.flPadding[ POSITION_RIGHT ] );
		flUsedVerticalSpace = rowNew.recLocation.y + rowNew.recLocation.flHeight + rowNew.padBorder.flPadding[ POSITION_BOTTOM ];
		rowNew.pParent = this;
		rowNew.iRowNumber = iRowCount;
		vecRows.emplace_back( rowNew );
		iRowCount++;
	}

	void IContainer::ClearRow( int iRow )
	{
		auto sStart = vecWidgets.size( );

		for ( auto u = 0u; u < sStart; u++ )
			if ( vecWidgets[ u ]->iRow == iRow )
			{
				vecWidgets.erase( vecWidgets.begin( ) + u );
				sStart--;
			}

		auto& row = vecRows[ iRow ];
		row.flLeftFill = row.flRightFill = 0.f;
	}

	void IContainer::AddWidgetToRow( IWidget* pWidget, float flWidth, int iRow )
	{
		auto& rowCurrent = vecRows[ iRow ];
		pWidget->pParentContainer = this;
		pWidget->recLocation.flWidth = flWidth;

		if ( pWidget->iAlignment == LEFT )
		{
			rowCurrent.flLeftFill += pWidget->padBorder.flPadding[ POSITION_LEFT ];
			pWidget->recLocation.x = rowCurrent.recLocation.x + rowCurrent.flLeftFill;
			rowCurrent.flLeftFill += pWidget->recLocation.flWidth + pWidget->padBorder.flPadding[ POSITION_RIGHT ];
		}
		else
		{
			pWidget->recLocation.x = rowCurrent.recLocation.x + rowCurrent.recLocation.flWidth - rowCurrent.flRightFill - pWidget->recLocation.flWidth - pWidget->padBorder.flPadding[ POSITION_RIGHT ];
			rowCurrent.flRightFill += pWidget->recLocation.flWidth + pWidget->padBorder.flPadding[ POSITION_LEFT ] + pWidget->padBorder.flPadding[ POSITION_RIGHT ];
		}

		pWidget->recLocation.y = rowCurrent.recLocation.y + pWidget->padBorder.flPadding[ POSITION_TOP ];
		pWidget->recLocation.flHeight = rowCurrent.recLocation.flHeight - ( pWidget->padBorder.flPadding[ POSITION_TOP ] + pWidget->padBorder.flPadding[ POSITION_BOTTOM ] );
		pWidget->iRow = iRow;
		pWidget->Initialize( );
		pWidget->Setup( );
		vecWidgets.emplace_back( pWidget );
	}

	void IContainer::AddWidget( IWidget* pWidget, rectangle_t recRelative )
	{
		pWidget->pParentContainer = this;
		pWidget->recLocation = recRelative;
		pWidget->Initialize( );
		pWidget->Setup( );
		vecWidgets.emplace_back( pWidget );
	}

	void IContainer::RemoveWidget( IWidget* pWidget )
	{
		for ( auto u = 0u; u < vecWidgets.size( ); u++ )
			if ( vecWidgets[ u ] == pWidget )
			{
				vecWidgets.erase( vecWidgets.begin( ) + u );
				break;
			}
	}

	void IContainer::VerticalSpacing( float flAmount )
	{
		flUsedVerticalSpace += flAmount;
	}

	void IContainer::Popup( CWindow* _pPopup )
	{
		GetContainingWindow( )->Popup( _pPopup );
	}

	CPanel::CPanel( padding_t padBorder, color_t clrPanel ): IContainer( FLAG_CONTAINER_NONE, padBorder, clrPanel )
	{ }

	bool UpdateActiveWidget( IWidget* pContainer, const location_t& locMouse )
	{
		constexpr auto fnSetWidget = [ & ]( IWidget* pNew )
		{
			if ( _WidgetContext.pHoveringWidget != nullptr && !_WidgetContext.pHoveringWidget->bPressing )
				_WidgetContext.pHoveringWidget->ModifyActivity( IWidget::DORMANT );

			_WidgetContext.pHoveringWidget = pNew;
			if ( !_WidgetContext.pHoveringWidget->bPressing
				 && ( !_WidgetContext.pActiveWidget || !_WidgetContext.pActiveWidget->bPressing )
				 && _WidgetContext.pHoveringWidget->GetContainingWindow( ) == _WidgetContext.GetForegroundWindow( ) )
				_WidgetContext.pHoveringWidget->ModifyActivity( IWidget::HOVER );
		};

		if ( !pContainer->GetAbsoluteLocation( ).LocationInRectangle( locMouse ) )
			return false;

		for ( auto& widget : reinterpret_cast< IContainer* >( pContainer )->vecWidgets )
			if ( widget->GetAbsoluteLocation( ).LocationInRectangle( locMouse ) )
			{
				if ( widget->iType == IWidget::CONTAINER )
					return UpdateActiveWidget( widget, locMouse );

				fnSetWidget( widget );
				return true;
			}

		fnSetWidget( pContainer );
		return true;
	}

	void InitializeInterface( )
	{
		_Input.AddCallback( [ & ]( key_t _Key, CKeyState _KeyState ) // todo return true if processed
		{
			if ( _Key == VK_LBUTTON )
			{
				if ( _KeyState )
				{
					if ( _WidgetContext.pHoveringWidget != _WidgetContext.pActiveWidget )
					{
						if ( _WidgetContext.pActiveWidget )
						{
							_WidgetContext.pActiveWidget->NoLongerActive( );
							_WidgetContext.pActiveWidget->ModifyActivity( IWidget::DORMANT );
						}

						_WidgetContext.pActiveWidget = _WidgetContext.pHoveringWidget;
					}

					auto bClosedPopup = false;

					if ( _WidgetContext.pActiveWidget != nullptr )
					{
						_WidgetContext.BringWidgetContainingWindowToFront( _WidgetContext.pActiveWidget );

						auto pParentWindow = _WidgetContext.pActiveWidget->GetContainingWindow( )->pPopup;

						while ( pParentWindow != nullptr && pParentWindow->pPopup != nullptr )
							pParentWindow = pParentWindow->pPopup;

						if ( pParentWindow )
						{
							bClosedPopup = true;
							decltype( pParentWindow )( pParentWindow->pParentContainer )->ClosePopup( true );
						}
					}

					if ( bClosedPopup )
					{
						if ( _WidgetContext.pActiveWidget )
							_WidgetContext.pActiveWidget->ModifyActivity( IWidget::DORMANT );

						if ( _WidgetContext.pHoveringWidget )
							_WidgetContext.pHoveringWidget->ModifyActivity( IWidget::DORMANT );

						_WidgetContext.pActiveWidget = _WidgetContext.pHoveringWidget = nullptr;
					}
					else
					{
						if ( _WidgetContext.pActiveWidget )
							_WidgetContext.pActiveWidget->ModifyActivity( IWidget::ACTIVE );
						else if ( _WidgetContext.pActiveWidget != nullptr )
							_WidgetContext.pActiveWidget->ModifyActivity( _WidgetContext.pHoveringWidget == _WidgetContext.pActiveWidget ? IWidget::HOVER : IWidget::DORMANT );
					}
				}
				else if ( _WidgetContext.pActiveWidget )
					_WidgetContext.pActiveWidget->ModifyActivity( _WidgetContext.pHoveringWidget == _WidgetContext.pActiveWidget ? IWidget::HOVER : IWidget::DORMANT );
			}

			if ( _WidgetContext.pActiveWidget )
				_WidgetContext.pActiveWidget->Event( _Key, _KeyState );

			return false;
		});

		_Input.AddCallback( [ & ]( int x, int y )
		{
			_WidgetContext.locMouse = location_t( float( x ), float( y ) );
			auto bFound = false;

			for ( auto u = 0u; u < _WidgetContext.vecWindows.size( ) && !bFound; u++ )
			{
				auto& window = _WidgetContext.vecWindows[ u ];

				if ( window->pHeader )
					window->pHeader->MoveParentWindow( x, y );

				auto pPopup = window->pPopup;
				while ( pPopup != nullptr )
				{
					if ( !( pPopup->wfFlags & CWindow::FLAG_WINDOW_ANCHOR )
						 && pPopup->pHeader )
						pPopup->pHeader->MoveParentWindow( x, y );

					pPopup = pPopup->pPopup;
				}

				bFound = UpdateActiveWidget( window, _WidgetContext.locMouse );
				if ( bFound )
				{
					pPopup = window->pPopup;
					while ( pPopup != nullptr && UpdateActiveWidget( pPopup, _WidgetContext.locMouse ) )
						pPopup = pPopup->pPopup;
				}
			}

			if ( !bFound )
				if ( _WidgetContext.pHoveringWidget != nullptr )
				{
					_WidgetContext.pHoveringWidget->ModifyActivity( IWidget::DORMANT );
					_WidgetContext.pHoveringWidget = nullptr;
				}

			if ( _WidgetContext.pActiveWidget )
				_WidgetContext.pActiveWidget->MouseMove( _WidgetContext.locMouse );

			return false;
		});
		_Input.AddCallback( [ & ]( key_t _Key )
		{
			if ( _WidgetContext.pActiveWidget )
				_WidgetContext.pActiveWidget->KeyTyped( _Key );

			return false;
		});

		_Input.AddCallback( [ & ]( short sDelta, int iMouseX, int iMouseY )
		{
			if ( _WidgetContext.pActiveWidget )
				if ( _WidgetContext.pActiveWidget->Scroll( sDelta ) )
					return false;

			auto pWidget = _WidgetContext.pHoveringWidget;

			while ( pWidget != nullptr )
			{
				if ( pWidget->iType == IWidget::CONTAINER
					 && pWidget->Scroll( sDelta ) )
					break;

				pWidget = pWidget->pParentContainer;
			}

			return false;
		});
	}

	void DrawWindows( )
	{
		for ( auto i = int( _WidgetContext.vecWindows.size( ) ) - 1; i >= 0; i-- )
		{
			auto& pWindow = _WidgetContext.vecWindows[ i ];
			pWindow->PreDraw( );
		}

		auto& pCurrent = _WidgetContext.vecWindows[ 0 ];
		const auto& recCurrent = pCurrent->GetAbsoluteLocation( );
		bool bRounding[ ] { false, false, pCurrent->wfFlags & CWindow::FLAG_WINDOW_ROUND_CORNERS, pCurrent->wfFlags & CWindow::FLAG_WINDOW_ROUND_CORNERS };

		if ( pCurrent->wfFlags & CWindow::FLAG_WINDOW_OUTLINE_COVERED )
		{
			for ( auto i = 1; i < int( _WidgetContext.vecWindows.size( ) ); i++ )
			{
				_Drawing.PushDrawingSpace( _WidgetContext.vecWindows[ i ]->GetAbsoluteLocation( ) );
				_Drawing.DrawPolygon( _Drawing.OutlineRoundedRectangle( recCurrent, OUTLINE_LIGHT, bRounding, CWindow::WINDOW_ROUNDING ).GetBuffer( D3DPT_LINESTRIP ), true );
				_Drawing.PopDrawingSpace( );
			}
		}
		_WidgetContext.ApplyCursor( );
		_WidgetContext.DoToolTip( );
	}

	void AddWindow( CWindow* pWindow )
	{
		pWindow->Setup( );
		_WidgetContext.vecWindows.emplace_front( pWindow );
	}
}
