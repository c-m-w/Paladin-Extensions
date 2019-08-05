/// IInteractable.hpp

#pragma once

#define STATE_INTERACTED { STATE_ACTIVATED, STATE_HOVERING, STATE_CLICKING, STATE_ACTIVATED | STATE_HOVERING, STATE_CLICKING | STATE_HOVERING, STATE_ACTIVATED | STATE_CLICKING, STATE_ACTIVATED | STATE_HOVERING | STATE_CLICKING }

#include "GUI.hpp"

class CContainer;

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

template < typename _t >
struct animated_value_t
{
	using value_change_t = std::function< void( void* ) >;
	constexpr static auto DEFAULT_ANIMATION_TIME = 125ull;

	_t* pValue = nullptr;
	bool bCombineStates = false;
	Utilities::timer_t _Timer = Utilities::timer_t( DEFAULT_ANIMATION_TIME );
	Utilities::EEaseType _EaseType = Utilities::EASE_SINE2;
	std::map< EState, _t > _Values { { STATE_DORMANT, { } } };
	_t _NextValue { }, _CurrentValue { };
	value_change_t _OnUpdate = nullptr;

	animated_value_t( _t* pValue ):
		pValue( pValue ), _CurrentValue( *pValue )
	{ }

	void SetCombineStates( bool bNewCombineStates )
	{
		bCombineStates = bNewCombineStates;
	}

	void SetAnimationTime( Utilities::moment_t mmtNewAnimationTime )
	{
		_Timer.SetLength( mmtNewAnimationTime );
	}

	void SetEaseType( Utilities::EEaseType _NewEaseType )
	{
		_EaseType = _NewEaseType;
	}

	void SetUpdateCallback( value_change_t _NewOnUpdate )
	{
		_OnUpdate = _NewOnUpdate;
	}

	EState GetSearchState( EState _State )
	{
		return bCombineStates ? _State : _State & STATE_CLICKING ? STATE_CLICKING : _State & STATE_HOVERING ? STATE_HOVERING : _State & STATE_ACTIVATED ? STATE_ACTIVATED : STATE_DORMANT;
	}

	void SetStateValue( EState _State, _t _StateValue )
	{
		const auto pSearch = _Values.find( GetSearchState( _State ) );

		if ( pSearch != _Values.end( ) )
			pSearch->second = _StateValue;
		else
			_Values.insert( { _State, _StateValue } );
	}

	_t GetStateValue( EState _State )
	{
		const auto pSearch = _Values.find( GetSearchState( _State ) );

		return pSearch == _Values.end( ) ? _Values.find( STATE_DORMANT )->second : pSearch->second;
	}

	void OnStateChange( EState _State )
	{
		_t _StateValue = GetStateValue( _State );

		if ( _Timer.Running( ) )
			_CurrentValue = GetCurrentValue( );

		_NextValue = _StateValue;
		_Timer.Reset( );
		_Timer.Start( );
	}

	void AnimateValue( _t _Next, _t _Current )
	{
		_CurrentValue = _Current;
		_NextValue = _Next;
		_Timer.Reset( );
		_Timer.Start( );
	}

	bool Update( )
	{
		*pValue = GetCurrentValue( );

		if ( _Timer.Running( ) )
		{
			if ( _Timer.Finished( ) )
				_CurrentValue = _NextValue, _NextValue = _t( ), _Timer.Reset( );

			if ( _OnUpdate )
				_OnUpdate( pValue );

			return true;
		}

		return false;
	}

	_t GetCurrentValue( )
	{
		if ( !_Timer.Running( ) )
			return _CurrentValue;

		return _NextValue * EaseIn( _EaseType, _Timer ) + _CurrentValue * EaseOut( _EaseType, _Timer );
	}
};

class IInteractable
{
protected:

	virtual void CreateDrawables( );
	virtual void Draw( );
	void UpdateAnimatedValues( );
	double CalculateAlphaRatio( );

	bool bCreateDrawables = true;
	unsigned uObjectSize = 0u;
	CContainer* pParent = nullptr;
	EInteractableType _Type = INTERACTABLE_NONE;
	bool bSetSize = false;
	bool bInitialized = false;
	bool bCombineStateColors = false;
	bool bScrollImmune = false;
	rectangle_t recLocation { };
	Utilities::vector2_t vecRelativeLocation { };
	Utilities::vector2_t vecRelativeSize { };
	padding_t _Padding { };
	Utilities::EEaseType _ColorEaseType = DEFAULT_COLOR_CHANGE_EASING;
	Utilities::timer_t _ColorChangeTimer = Utilities::timer_t( DEFAULT_COLOR_CHANGE_TIME );
	color_t clrPrevious[ COLOR_INDEX_MAX ] { };
	std::map< EState, color_t > _Colors[ COLOR_INDEX_MAX ];
	std::vector< CDrawable* > vecDrawables { };
	EState _State = STATE_DORMANT;
	std::vector< animated_value_t< Utilities::vector2_t >* > vecAnimatedVectors { };
	std::vector< animated_value_t< double >* > vecAnimatedDoubles { };
	std::string strToolTip { };
	callbacks_t _Callbacks { };

public:

	constexpr static auto DEFAULT_COLOR = 0xFFFFFFFF;
	constexpr static auto DEFAULT_COLOR_CHANGE_TIME = 250u;
	constexpr static auto DEFAULT_COLOR_CHANGE_EASING = Utilities::EASE_SINE2;

	static void UpdateContainerContents( CContainer* pContainer );

	explicit IInteractable( EInteractableType _Type );
	virtual ~IInteractable( );

	void SetParent( CContainer* pNewParent );
	CContainer* GetParent( );
	rectangle_t GetHitbox( );
	void SetScrollImmune( bool bNewScrollImmune );
	bool GetScrollImmune( );
	void SetLocation( const Utilities::vector2_t& vecNew );
	void SetSize( const Utilities::vector2_t& vecSize );
	void SetPadding( const padding_t& _NewPadding );
	void SetColorChangeTime( unsigned uNewTime );
	void SetColorChangeEaseType( Utilities::EEaseType _NewEaseType );
	void SetColor( EColorIndex _ColorIndex, EState _ColorState, const color_t& clrState );
	void SetColor( EColorIndex _ColorIndex, std::initializer_list< EState > _ColorStates, const color_t& clrState );
	color_t GetCurrentColor( EColorIndex _ColorIndex );
	void DoColorAnimations( );
	void DoStateAnimations( );
	bool IsInteractableType( EInteractableType _TestType );
	void Initialize( CContainer* pNewParent, const rectangle_t& recNewLocation );
	void Initialize( CContainer* pNewParent, const Utilities::vector2_t& vecNewLocation );
	rectangle_t GetLocation( );
	Utilities::vector2_t GetSize( );
	Utilities::vector2_t& GetRelativeSize( );
	Utilities::vector2_t& GetRelativeLocation( );
	void PreCreateDrawables( );
	void PreDraw( );
	void AddState( EState _NewState );
	void RemoveState( EState _NewState );
	bool HasState( EState _TestState );
	rectangle_t GetAbsoluteLocation( );
	padding_t GetPadding( );
	Utilities::vector2_t GetNetSize( );
	void AddAnimatedValue( animated_value_t< Utilities::vector2_t >* pValue );
	void AddAnimatedValue( animated_value_t< double >* pValue );
	void RemoveAnimatedValue( animated_value_t< Utilities::vector2_t >* pValue );
	void RemoveAnimatedValue( animated_value_t< double >* pValue );
	std::pair< std::vector< animated_value_t< Utilities::vector2_t >* >, std::vector< animated_value_t< double >* > > GetAnimatedValues( );
	callbacks_t& GetCallbacks( );

	virtual void SetDefaultSize( );
	virtual void Initialize( );
	virtual void NewFrame( );
	virtual void OnStateChange( );
	virtual void OnClick( CKeyState _State );
	virtual void OnRightClick( CKeyState _State );
	virtual void OnKeyPress( key_t _Code, CKeyState _State );
	virtual void OnKeyTyped( char chCharacter );
	virtual bool OnScroll( int iScrollAmount );
	virtual void OnMouseMove( const Utilities::vector2_t& vecMouseLocation );
};
