/// IInteractable.hpp

#pragma once

#include "GUI.hpp"

class CContainer;

enum EState
{
	/** \brief Not being interacted with. */
	STATE_DORMANT,
	/** \brief Last interacted with. */
	STATE_ACTIVED,
	/** \brief Currently being hovered. */
	STATE_HOVERING,
	/** \brief Currently being clicked. */
	STATE_CLICKING
};

struct padding_t
{
	Utilities::vector2_t vecData { };

	padding_t( ) = default;
	padding_t( double dbTop, double dbLeft );
	padding_t( Utilities::vector2_t& vecPadding );

	double GetHorizontalPadding( );
	void PutHorizontalPadding( double dbHorizontal );
	double GetVerticalPadding( );
	void PutVerticalPadding( double dbVertical );

	__declspec( property( get = GetHorizontalPadding, put = PutHorizontalPadding ) ) double h;
	__declspec( property( get = GetVerticalPadding, put = PutVerticalPadding ) ) double v;
};

class IInteractable
{
protected:

	CContainer* pParent = nullptr;
	rectangle_t recLocation { };
	Utilities::vector2_t vecRelative { };
	padding_t _Padding { };
	std::vector< CDrawable* > vecDrawables { };
	EState _State = STATE_DORMANT;
	std::string strToolTip { };

public:

	IInteractable( ) = default;
	explicit IInteractable( const Utilities::vector2_t& vecSize );
	explicit IInteractable( const padding_t& _Padding );
	explicit IInteractable( const Utilities::vector2_t& vecSize, const padding_t& _Padding );
	virtual ~IInteractable( ) = default;

	void Initialize( CContainer* pNewParent, const rectangle_t& recNewLocation );
	void Initialize( CContainer* pNewParent, const Utilities::vector2_t& vecNewLocation );
	rectangle_t GetLocation( );
	Utilities::vector2_t GetSize( );
	void PreCreateDrawables( );
	void SetLocation( const Utilities::vector2_t& vecNew );
	void PreStateChange( );
	rectangle_t GetAbsoluteLocation( );
	padding_t GetPadding( );
	Utilities::vector2_t GetNetSize( );

	virtual void CreateDrawables( ) = 0;
	virtual void Draw( );
	virtual void OnStateChange( );
	virtual void OnClick( CKeyState _State );
	virtual void OnRightClick( CKeyState _State );
	virtual void OnKeyPress( key_t _Code, CKeyState _State );
	virtual void OnKeyTyped( char chCharacter, CKeyState _State );
	virtual void OnScroll( int iScrollAmount );
};

