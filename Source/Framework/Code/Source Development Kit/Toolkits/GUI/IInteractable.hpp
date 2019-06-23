/// IInteractable.hpp

#pragma once

#include "GUI.hpp"

class IContainer;

enum EInteractableType
{
	INTERACTABLE_NONE,
	INTERACTABLE_CONTAINER,
	INTERACTABLE_WIDGET
};

enum EState
{
	STATE_NONE,
	/** \brief Last interacted with. */
	STATE_ACTIVATED	= 1 << 0,
	/** \brief Currently being hovered. */
	STATE_HOVERING	= 1 << 1,
	/** \brief Currently being clicked. */
	STATE_CLICKING	= 1 << 2
};

EState operator|( EState lhs, EState rhs );
EState operator&( EState lhs, EState rhs );
EState operator~( EState rhs );

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

	virtual void CreateDrawables( ) = 0;
	virtual void Draw( );

	IContainer* pParent = nullptr;
	EInteractableType _Type = INTERACTABLE_NONE;
	rectangle_t recLocation { };
	double dbTransparency = 0.0;
	Utilities::vector2_t vecRelative { };
	padding_t _Padding { };
	std::vector< CDrawable* > vecDrawables { };
	EState _State = STATE_NONE;
	std::string strToolTip { };

public:

	IInteractable( ) = default;
	explicit IInteractable( EInteractableType _Type, const Utilities::vector2_t& vecSize );
	explicit IInteractable( EInteractableType _Type, const padding_t& _Padding );
	explicit IInteractable( EInteractableType _Type, const Utilities::vector2_t& vecSize, const padding_t& _Padding );
	virtual ~IInteractable( ) = default;

	bool IsInteractableType( EInteractableType _TestType );
	void Initialize( IContainer* pNewParent, const rectangle_t& recNewLocation );
	void Initialize( IContainer* pNewParent, const Utilities::vector2_t& vecNewLocation );
	rectangle_t GetLocation( );
	Utilities::vector2_t GetSize( );
	void PreCreateDrawables( );
	void PreDraw( );
	void SetLocation( const Utilities::vector2_t& vecNew );
	void AddState( EState _NewState );
	void RemoveState( EState _NewState );
	rectangle_t GetAbsoluteLocation( );
	padding_t GetPadding( );
	Utilities::vector2_t GetNetSize( );

	virtual void OnStateChange( );
	virtual void OnClick( CKeyState _State );
	virtual void OnRightClick( CKeyState _State );
	virtual void OnKeyPress( key_t _Code, CKeyState _State );
	virtual void OnKeyTyped( char chCharacter );
	virtual void OnScroll( int iScrollAmount );
};
