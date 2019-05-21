/// IInteractable.hpp

#pragma once

#include "GUI.hpp"

class CContainer;

enum EState
{
	/** \brief Not being interacted with. */
	STATE_DORMANT,
	/** \brief Last interacted with. */
	STATE_ACTIVE,
	/** \brief Currently being hovered. */
	STATE_HOVERING,
	/** \brief Currently being clicked. */
	STATE_CLICKING
};

class IInteractable: public IDrawable
{
protected:

	CContainer* pParent = nullptr;
	Utilities::vector2_t vecPadding { };
	EState _State = STATE_DORMANT;
	std::string strToolTip { };

public:

	IInteractable( const rectangle_t& recLocation );

	void PreStateChange( );
	rectangle_t GetAbsoluteLocation( );
	Utilities::vector2_t GetPadding( );
	double GetNetWidth( );

	virtual void OnStateChange( );
	virtual void OnClick( CKeyState _State );
	virtual void OnRightClick( CKeyState _State );
	virtual void OnKeyPress( key_t _Code, CKeyState _State );
	virtual void OnKeyTyped( char chCharacter, CKeyState _State );
	virtual void OnScroll( int iScrollAmount );
};

