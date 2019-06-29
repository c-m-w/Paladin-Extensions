/// IInteractable.hpp

#pragma once

#define STATE_INTERACTED { STATE_ACTIVATED, STATE_HOVERING, STATE_CLICKING, STATE_ACTIVATED | STATE_HOVERING, STATE_CLICKING | STATE_HOVERING, STATE_ACTIVATED | STATE_CLICKING, STATE_ACTIVATED | STATE_HOVERING | STATE_CLICKING }

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
	STATE_DORMANT	= 0,
	STATE_ACTIVATED	= 1 << 0,
	/** \brief Currently being hovered. */
	STATE_HOVERING	= 1 << 1,
	/** \brief Currently being clicked. */
	STATE_CLICKING	= 1 << 2
};

enum EColorIndex
{
	COLOR_INDEX_PRIMARY,
	COLOR_INDEX_SECONDARY,
	COLOR_INDEX_TERTIARY,
	COLOR_INDEX_MAX
};

EState operator|( EState lhs, EState rhs );
EState operator&( EState lhs, EState rhs );
EState operator~( EState rhs );

struct padding_t
{
	Utilities::vector2_t vecData { };

	padding_t( ) = default;
	padding_t( double dHorizontal, double dVertical );
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

	virtual void CreateDrawables( );
	virtual void Draw( );

	unsigned* pHash = new unsigned { 0 };
	unsigned uObjectSize = 0u;
	IContainer* pParent = nullptr;
	EInteractableType _Type = INTERACTABLE_NONE;
	bool bSetSize = false;
	bool bInitialized = false;
	bool bCombineStateColors = false;
	rectangle_t recLocation { };
	Utilities::vector2_t vecRelative { };
	padding_t _Padding { };
	Utilities::EEaseType _ColorEaseType = DEFAULT_COLOR_CHANGE_EASING;
	Utilities::timer_t _ColorChangeTimer = Utilities::timer_t( DEFAULT_COLOR_CHANGE_TIME );
	color_t clrPrevious[ COLOR_INDEX_MAX ] { };
	std::map< EState, color_t > _Colors[ COLOR_INDEX_MAX ] { };
	std::vector< CDrawable* > vecDrawables { };
	EState _State = STATE_DORMANT;
	std::string strToolTip { };

public:

	constexpr static auto DEFAULT_COLOR = 0xFFFFFFFF;
	constexpr static auto DEFAULT_COLOR_CHANGE_TIME = 250u;
	constexpr static auto DEFAULT_COLOR_CHANGE_EASING = Utilities::EASE_SINE2;

	explicit IInteractable( unsigned uObjectSize, EInteractableType _Type );
	virtual ~IInteractable( );

	void SetParent( IContainer* pNewParent );
	void SetLocation( const Utilities::vector2_t& vecNew );
	void SetSize( const Utilities::vector2_t& vecSize );
	void SetPadding( const padding_t& _NewPadding );
	void SetColorChangeTime( unsigned uNewTime );
	void SetColorChangeEaseType( Utilities::EEaseType _NewEaseType );
	void SetColor( EColorIndex _ColorIndex, EState _ColorState, const color_t& clrState );
	void SetColor( EColorIndex _ColorIndex, std::initializer_list< EState > _ColorStates, const color_t& clrState );
	color_t GetCurrentColor( EColorIndex _ColorIndex );
	void DoColorChangeBehaviour( );
	bool IsInteractableType( EInteractableType _TestType );
	void Initialize( IContainer* pNewParent, const rectangle_t& recNewLocation );
	void Initialize( IContainer* pNewParent, const Utilities::vector2_t& vecNewLocation );
	rectangle_t GetLocation( );
	Utilities::vector2_t GetSize( );
	void PreCreateDrawables( );
	void PreDraw( );
	void AddState( EState _NewState );
	void RemoveState( EState _NewState );
	rectangle_t GetAbsoluteLocation( );
	padding_t GetPadding( );
	Utilities::vector2_t GetNetSize( );

	virtual void Initialize( );
	virtual void OnStateChange( );
	virtual void OnClick( CKeyState _State );
	virtual void OnRightClick( CKeyState _State );
	virtual void OnKeyPress( key_t _Code, CKeyState _State );
	virtual void OnKeyTyped( char chCharacter );
	virtual void OnScroll( int iScrollAmount );
};
