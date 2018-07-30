/// User Interface.tpp

#pragma once

namespace Paladin
{
	template< > int CUserInterface::CWidgets::Inputbox< int >( unsigned uMaxCharacters, char *szBuffer )
	{
		ui->SetFont( EFont::ENVY );
		nk_edit_string_zero_terminated( ui->pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters + 1, nk_filter_decimal );
		ui->HoverCheck( IBEAM );
		ui->SetFont( EFont::ROBOTOSMALL );
		return strlen( szBuffer ) ? std::stoi( szBuffer ) : 0;
	}

	template< > float CUserInterface::CWidgets::Inputbox< float >( unsigned uMaxCharacters, char *szBuffer )
	{
		ui->SetFont( EFont::ENVY );
		nk_edit_string_zero_terminated( ui->pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters, nk_filter_float );
		ui->HoverCheck( IBEAM );
		ui->SetFont( EFont::ROBOTOSMALL );
		return strlen( szBuffer ) && strcmp( szBuffer, "." ) ? std::stof( szBuffer ) : 0.f;
	}

	template< > char *CUserInterface::CWidgets::Inputbox< char * >( unsigned uMaxCharacters, char *szBuffer )
	{
		ui->SetFont( EFont::ENVY );
		nk_edit_string_zero_terminated( ui->pContext, NK_EDIT_FIELD | NK_EDIT_AUTO_SELECT, szBuffer, uMaxCharacters, nk_filter_ascii );
		ui->HoverCheck( IBEAM );
		ui->SetFont( EFont::ROBOTOSMALL );
		return szBuffer;
	}

	template< typename _t > _t CUserInterface::CWidgets::Slider( const char *szTitle, char *szInputBuffer, _t flMin, _t flMax, _t flCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, unsigned uDigits )
	{
		dbg::Assert( flMax > flMin );
		auto szTexta = std::to_string( flCurrentValue ).substr( 0, std::to_string( int( flCurrentValue ) ).size( ) + 1 + uDigits );
		auto szText = szTexta.c_str( );

		static auto bInEdit = false, bSetEditValue = false;

		ui->SetFont( EFont::ROBOTOSMALL );
		auto vecTitleSize = ui->GetTextSize( szTitle, 10 );
		auto vecTextSize = ui->GetTextSize( szText, 10 );
		PushCustomRow( uStartX + 5, uStartY, vecTitleSize.x, vecTitleSize.y );
		nk_label( ui->pContext, szTitle, NK_TEXT_LEFT );
		PushCustomRow( uStartX + uWidth - vecTextSize.x - 5, uStartY, vecTextSize.x, vecTextSize.y );

		const auto recBounds = nk_widget_bounds( ui->pContext );
		const auto bHovering = nk_input_is_mouse_hovering_rect( &ui->pContext->input, recBounds );
		const auto bClicking = ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN;

		if ( bHovering && !bInEdit )
		{
			ui->bFoundHoverTarget = true;
			ui->SetActiveCursor( HAND );
			if ( bClicking )
			{
				bInEdit = true;
				strcpy( szInputBuffer, szText );
			}
		}
		auto bHoveringInputBox = false;

		if ( bInEdit )
		{
			PushCustomRow( uStartX + vecTitleSize.x + 8, uStartY, uWidth - vecTitleSize.x, vecTextSize.y + 5 );
			auto recNewBounds = nk_widget_bounds( ui->pContext );
			//if ( GetKeyState( VK_NUMPAD3 ) == KeyState::Down )
			//	auto i = 1;
			flCurrentValue = Inputbox< float >( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
			bHoveringInputBox = nk_input_is_mouse_hovering_rect( &ui->pContext->input, recNewBounds );

			if ( bHoveringInputBox )
			{
				ui->bFoundHoverTarget = true;
				ui->SetActiveCursor( IBEAM );
			}
			else if ( bClicking || ui->GetKeyState( VK_RETURN ) == EKeyState::DOWN )
			{
				bSetEditValue = strlen( szInputBuffer ) > 0;
				bInEdit = false;
			}
		}
		else if ( bSetEditValue )
		{
			bSetEditValue = false;
			const auto iValue = std::stof( szInputBuffer );
			flCurrentValue = iValue <= flMax ? ( iValue >= flMin ? iValue : flMin ) : flMax;
		}
		else
			nk_label( ui->pContext, szText, NK_TEXT_LEFT );

		PushCustomRow( uStartX, uStartY + vecTextSize.y + 3, uWidth, uHeight - vecTextSize.y - 3 );
		flCurrentValue = nk_slide_float( ui->pContext, flMin, flCurrentValue, flMax, ( flMax - flMin ) / 20.f );
		ui->HoverCheck( HAND );
		ui->SetFont( EFont::ROBOTOSMALL );
		return flCurrentValue;
	}

	template< > int CUserInterface::CWidgets::Slider< int >( const char *szTitle, char *szInputBuffer, int iMin, int iMax, int iCurrentValue, unsigned uStartX, unsigned uStartY, unsigned uWidth, unsigned uHeight, unsigned uMaxDigits )
	{
		assert( iMax > iMin );
		auto szTexta = std::to_string( iCurrentValue ).substr( 0, std::to_string( iCurrentValue ).size( ) ).substr( 0, uMaxDigits );
		auto szText = szTexta.c_str( );

		static auto bInEdit = false, bSetEditValue = false;

		ui->SetFont( EFont::ROBOTOSMALL );
		auto vecTitleSize = ui->GetTextSize( szTitle, 10 );
		auto vecTextSize = ui->GetTextSize( szText, 10 );
		PushCustomRow( uStartX + 5, uStartY, vecTitleSize.x, vecTitleSize.y );
		nk_label( ui->pContext, szTitle, NK_TEXT_LEFT );
		PushCustomRow( uStartX + uWidth - vecTextSize.x - 5, uStartY, vecTextSize.x, vecTextSize.y );

		const auto recBounds = nk_widget_bounds( ui->pContext );
		const auto bHovering = nk_input_is_mouse_hovering_rect( &ui->pContext->input, recBounds );
		const auto bClicking = ui->GetKeyState( VK_LBUTTON ) == EKeyState::DOWN;

		if ( bHovering && !bInEdit )
		{
			ui->bFoundHoverTarget = true;
			ui->SetActiveCursor( HAND );
			if ( bClicking )
			{
				bInEdit = true;
				strcpy( szInputBuffer, szText );
			}
		}
		auto bHoveringInputBox = false;

		if ( bInEdit )
		{
			PushCustomRow( uStartX + vecTitleSize.x + 8, uStartY, uWidth - vecTitleSize.x, vecTextSize.y + 5 );
			auto recNewBounds = nk_widget_bounds( ui->pContext );
			//if ( InputSys::ui->GetKeyState( VK_NUMPAD3 ) == KeyState::Down )
			//	auto i = 1;
			iCurrentValue = Inputbox< int >( strlen( std::to_string( FLT_MAX ).c_str( ) ), szInputBuffer );
			bHoveringInputBox = nk_input_is_mouse_hovering_rect( &ui->pContext->input, recNewBounds );

			if ( bHoveringInputBox )
			{
				ui->bFoundHoverTarget = true;
				ui->SetActiveCursor( IBEAM );
			}
			else if ( bClicking || ui->GetKeyState( VK_RETURN ) == EKeyState::DOWN )
			{
				bSetEditValue = strlen( szInputBuffer ) > 0;
				bInEdit = false;
			}
		}
		else if ( bSetEditValue )
		{
			bSetEditValue = false;
			const auto iValue = std::stoi( szInputBuffer );
			iCurrentValue = iValue <= iMax ? ( iValue >= iMin ? iValue : iMin ) : iMax;
		}
		else
			nk_label( ui->pContext, szText, NK_TEXT_LEFT );

		PushCustomRow( uStartX, uStartY + vecTextSize.y + 3, uWidth, uHeight - vecTextSize.y - 3 );
		iCurrentValue = nk_slide_int( ui->pContext, iMin, iCurrentValue, iMax, ( iMax - iMin ) / 20.f );
		ui->HoverCheck( HAND );
		ui->SetFont( EFont::ROBOTOSMALL );
		return iCurrentValue;
	}
}