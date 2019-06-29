/// Interface.hpp

#pragma once

#include "IInteractable.hpp"
#include "IWidget.hpp"
#include "IContainer.hpp"
#include "IRow.hpp"
#include "CGroupButton.hpp"
#include "CImage.hpp"
#include "CText.hpp"
#include "CVectorGraphic.hpp"
#include "CWindowHeader.hpp"
#include "CWindow.hpp"

class CGUI
{
private:

	bool bSetup = false;
	bool bActive = true;
	std::deque< CWindow* > vecWindows { };
	IInteractable* pActiveInteractable = nullptr;
	IInteractable* pHoveredInteractable = nullptr;
	CDrawable* pCursors[ CURSOR_MAX ] { };
	ECursorType _CurrentCursor = CURSOR_NONE;
	ECursorType _NextCursor = CURSOR_NONE;
	Utilities::timer_t _CursorFade = Utilities::timer_t( DEFAULT_CURSOR_FADE_TIME );

	IInteractable* GetHoveredInteractable( IContainer* pContainer = nullptr );
	void FindHoveredInteractable( );
	void ResetActiveInteractable( );
	void DrawCursor( ECursorType _Cursor, double dAlpha );
	void DrawCursor( ECursorType _Cursor );

public:

	constexpr static auto DEFAULT_CURSOR_FADE_TIME = 250u;

	void Setup( );
	void Shutdown( );
	void AddWindow( CWindow* pWindow );
	void RemoveWindow( CWindow* pWindow );
	void Draw( );
	void Deactivate( );
	void Activate( );

} inline _GUI;

namespace Interface
{
	inline const static color_t CLEAR = color_t( { 0, 0, 0, 0 } );
	inline const static color_t WHITE = color_t( { 255, 255, 255, 255 } );
	inline const static color_t SHADOW = color_t( { 0, 0, 0, 100 } );
	inline const static color_t BLACK = color_t( { 0, 0, 0, 255 } );
	inline const static color_t BACKGROUND_DARK = color_t( { 33, 36, 40, 255 } );
	inline const static color_t BACKGROUND_LIGHT = color_t( { 61, 65, 72, 255 } );
	inline const static color_t BACKGROUND_DEFAULT = color_t( { 45, 50, 56, 255 } );
	inline const static color_t BACKGROUND_DIM = color_t( { 0, 0, 0, 100 } );
	inline const static color_t OUTLINE_DARK = color_t( { 56, 60, 64, 255 } );
	inline const static color_t OUTLINE_LIGHT = color_t( { 73, 76, 83, 255 } );
	inline const static color_t TEXT_NORMAL = color_t( { 255, 255, 255, 255 } );
	inline const static color_t TEXT_DARK = color_t( { 175, 180, 187, 210 } );
	inline const static color_t BLUE = color_t( { 34, 145, 232, 255 } );
	inline const static color_t TRANSLUCENT_BLUE = color_t( { 34, 145, 232, 100 } );
	inline const static color_t VIVID_BLUE = color_t( { 13, 59, 95, 255 } );
	inline const static color_t VIVID_BLUE_ACTIVE = color_t( { 4, 56, 98, 255 } );
	inline const static color_t DARK_BLUE = color_t( { 43, 60, 75, 255 } );
	inline const static color_t BUTTON_TEXT = color_t( { 33, 150, 243, 255 } );
	inline const static color_t BUTTON_BACKGROUND_DORMANT = color_t( { 0, 0, 0, 0 } );
	inline const static color_t BUTTON_BACKGROUND_HOVER = color_t( { 33, 150, 243, 26 } );
	inline const static color_t BUTTON_BACKGROUND_ACTIVE = color_t( { 33, 150, 243, 51 } );
	static auto NO_CALLBACK = [ & ]( )
	{ };


}
