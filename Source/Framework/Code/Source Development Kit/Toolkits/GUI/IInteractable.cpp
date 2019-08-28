/// IInteractable.hpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

EState operator|( EState lhs, EState rhs )
{
	return EState( int( lhs ) | int( rhs ) );
}

EState operator&( EState lhs, EState rhs )
{
	return EState( int( lhs ) & int( rhs ) );
}

EState operator~( EState rhs )
{
	return EState( ~int( rhs ) );
}

padding_t::padding_t( double dbTop, double d ) :
	vecData( dbTop, d )
{ }

padding_t::padding_t( vector2_t& vecPadding ) :
	vecData( vecPadding )
{ }

double padding_t::GetHorizontalPadding( )
{
	return vecData.x;
}

void padding_t::PutHorizontalPadding( double dbHorizontal )
{
	vecData.x = dbHorizontal;
}

double padding_t::GetVerticalPadding( )
{
	return vecData.y;
}

void padding_t::PutVerticalPadding( double dbVertical )
{
	vecData.y = dbVertical;
}

void IInteractable::UpdateAnimatedValues( )
{
	for ( auto& pAnimatedVector : vecAnimatedVectors )
	{
		bCreateDrawables |= pAnimatedVector->Update( );

		if ( pAnimatedVector->_Timer.Finished( ) 
			 && pAnimatedVector->_Timer._EndBehaviour == BEHAVIOUR_CLAMP )
			RemoveAnimatedValue( pAnimatedVector );
	}

	for ( auto& pAnimatedDouble : vecAnimatedDoubles )
	{
		bCreateDrawables |= pAnimatedDouble->Update( );
		
		if ( pAnimatedDouble->_Timer.Finished( ) 
			 && pAnimatedDouble->_Timer._EndBehaviour == BEHAVIOUR_CLAMP )
			RemoveAnimatedValue( pAnimatedDouble );
	}
}

double IInteractable::CalculateAlphaRatio( )
{
	auto dbReturn = 1.0;
	auto pCurrent = pParent;

	if ( _Type == INTERACTABLE_CONTAINER )
		dbReturn *= reinterpret_cast< CContainer* >( this )->GetAlphaRatio( );

	while ( pCurrent != nullptr )
		dbReturn *= reinterpret_cast< CContainer* >( pCurrent )->CalculateAlphaRatio( ), pCurrent = pCurrent->pParent;

	return dbReturn;
}

void IInteractable::UpdateContainerContents( CContainer *pContainer )
{
	for ( auto& pInteractable : pContainer->GetContainedInteractables(  ) )
	{
		pInteractable->PreCreateDrawables( );
		if ( pInteractable->IsInteractableType( INTERACTABLE_CONTAINER ) )
			UpdateContainerContents( reinterpret_cast< CContainer* >( pInteractable ) );
	}
}

IInteractable::IInteractable( EInteractableType _Type ) :
	_Type( _Type )
{
	for ( int i = COLOR_INDEX_PRIMARY; i != COLOR_INDEX_MAX; i++ )
		SetColor( EColorIndex( i ), STATE_DORMANT, DEFAULT_COLOR );
}

IInteractable::~IInteractable( )
{ }

void IInteractable::SetParent( CContainer *pNewParent )
{
	if ( !pNewParent->IsInteractableType( INTERACTABLE_CONTAINER ) )
		throw std::runtime_error( ENC( "Parent type must be container." ) );

	pParent = pNewParent;
}

CContainer* IInteractable::GetParent( )
{
	return reinterpret_cast< CContainer* >( pParent );
}

rectangle_t IInteractable::GetHitbox( )
{
	auto pHitbox = GetAbsoluteLocation( );
	auto pParentIterator = pParent;

	while ( pParentIterator )
	{
		if ( pParentIterator->GetStrictBounds( ) )
			pHitbox.Clamp( pParentIterator->GetAbsoluteLocation( ) );

		pParentIterator = pParentIterator->pParent;
	}

	return pHitbox;
}

void IInteractable::SetScrollImmune( bool bNewScrollImmune )
{
	bScrollImmune = bNewScrollImmune;
}

bool IInteractable::GetScrollImmune( )
{
	return bScrollImmune;
}

bool IInteractable::IsInteractableType( EInteractableType _TestType )
{
	return _Type == _TestType;
}

void IInteractable::Initialize( CContainer *pNewParent, const rectangle_t &recNewLocation )
{
	pParent = pNewParent;
	recLocation = recNewLocation;
	bCreateDrawables = true;
}

void IInteractable::Initialize( CContainer *pNewParent, const vector2_t &vecNewLocation )
{
	pParent = pNewParent;
	recLocation.vecLocation = vecNewLocation;
	bCreateDrawables = true;
}

rectangle_t IInteractable::GetLocation( )
{
	auto vecRoundedRelativeSize = InchesToPixels( vecRelativeSize ) / 2.0;
	rectangle_t recReturn { };
	
	vecRoundedRelativeSize.Round( );
	vecRoundedRelativeSize = PixelsToInches( vecRoundedRelativeSize );
	recReturn = rectangle_t { recLocation.x + vecRelativeLocation.x - vecRoundedRelativeSize.x, recLocation.y + vecRelativeLocation.y - vecRoundedRelativeSize.y, recLocation.w + vecRoundedRelativeSize.x * 2.0, recLocation.h + vecRoundedRelativeSize.y * 2.0 };

	if ( pParent != nullptr
		 && !GetScrollImmune( ) )
	{
		const auto vecScrollLocationOffset = reinterpret_cast< CContainer* >( pParent )->GetScrollOffset( );

		recReturn.x -= vecScrollLocationOffset.x;
		recReturn.y -= vecScrollLocationOffset.y;
	}

	return recReturn;
}

vector2_t IInteractable::GetSize( )
{
	if ( !bSetSize )
	{
		SetDefaultSize( );

		if ( !bSetSize )
			throw std::runtime_error( ENC( "Set interactable size before attempting to retrieve size." ) );
	}

	return recLocation.vecSize + vecRelativeSize;
}

vector2_t& IInteractable::GetRelativeSize( )
{
	return vecRelativeSize;
}

vector2_t& IInteractable::GetRelativeLocation( )
{
	return vecRelativeLocation;
}

void IInteractable::PreCreateDrawables( )
{
	if ( !bSetSize )
	{
		SetDefaultSize( );

		if ( !bSetSize )
			throw std::runtime_error( ENC( "Size not set on interactable before attempting to create drawables." ) );
	}

	if ( !bInitialized )
		Initialize( ), bInitialized = true;

	for ( auto& pDrawable : vecDrawables )
		if ( !_Drawing.UnregisterDrawable( pDrawable ) )
			throw std::runtime_error( ENC( "Unable to unregister drawables." ) );

	vecDrawables.clear( );
	CreateDrawables( );
	for ( auto& pDrawable : vecDrawables )
		if ( !_Drawing.RegisterDrawable( pDrawable ) )
			throw std::runtime_error( ENC( "Unable to register drawables." ) );
}

void IInteractable::PreDraw( )
{
	UpdateAnimatedValues( );

	if ( bCreateDrawables )
	{
		PreCreateDrawables( );

		if ( _Type == INTERACTABLE_CONTAINER )
			UpdateContainerContents( reinterpret_cast< CContainer* >( this ) );

		bCreateDrawables = false;
	}

	if ( _ColorChangeTimer.Running( ) )
	{
		if ( _ColorChangeTimer.Finished( ) )
			_ColorChangeTimer.Reset( );
		else
			PreCreateDrawables( );
	}

	const auto recHitbox = GetHitbox( );

	if ( !_Drawing.IsAreaVisible( recHitbox ) ) /// TODO: this is broken
		return;

	_Drawing.PushDrawingSpace( recHitbox );
	Draw( );
	_Drawing.PopDrawingSpace( );
}

void IInteractable::SetLocation( const vector2_t& vecNew )
{
	recLocation.vecLocation = vecNew;
	if ( bInitialized )
		_GUI.FindHoveredInteractable( ), PreCreateDrawables( );
}

void IInteractable::SetSize( const vector2_t &vecSize )
{
	bSetSize = true;
	bCreateDrawables = true;
	recLocation.vecSize = vecSize;
	if ( bInitialized )
		_GUI.FindHoveredInteractable( ), PreCreateDrawables( );
}

void IInteractable::SetPadding( const padding_t &_NewPadding )
{
	_Padding = _NewPadding;
	bCreateDrawables = true;
}

void IInteractable::SetColorChangeTime( unsigned uNewTime )
{
	_ColorChangeTimer.SetLength( uNewTime );
}

void IInteractable::SetColorChangeEaseType( EEaseType _NewEaseType )
{
	_ColorEaseType = _NewEaseType;
}

void IInteractable::SetColor( EColorIndex _ColorIndex, EState _ColorState, const color_t &clrState )
{
	const auto pSearch = _Colors[ _ColorIndex ].find( _ColorState );

	if ( pSearch != _Colors[ _ColorIndex ].end( ) )
		pSearch->second = clrState;
	else
		_Colors[ _ColorIndex ].insert( { _ColorState, clrState } );
}

void IInteractable::SetColor( EColorIndex _ColorIndex, std::initializer_list< EState > _ColorStates, const color_t &clrState )
{
	for ( auto _ColorState : _ColorStates )
		SetColor( _ColorIndex, _ColorState, clrState );
}

color_t IInteractable::GetCurrentColor( EColorIndex _ColorIndex )
{
	const auto _ColorState = bCombineStateColors ? _State : ( _State & STATE_CLICKING ? STATE_CLICKING : ( _State & STATE_HOVERING ? STATE_HOVERING : ( _State & STATE_ACTIVATED ? STATE_ACTIVATED : STATE_DORMANT ) ) );
	const auto pSearch = _Colors[ _ColorIndex ].find( _ColorState );
	const auto _Color = pSearch == _Colors[ _ColorIndex ].end( ) ? _Colors[ _ColorIndex ].find( STATE_DORMANT )->second : pSearch->second;
	auto _Return = _ColorChangeTimer.Running( ) ? CColor::GetGradient( clrPrevious[ _ColorIndex ], _Color, EaseIn( _ColorEaseType, _ColorChangeTimer ) ) : _Color;
	_Return.a *= CalculateAlphaRatio( );

	return _Return;
}

void IInteractable::DoColorAnimations( )
{
	for ( int i = COLOR_INDEX_PRIMARY; i != COLOR_INDEX_MAX; i++ )
		clrPrevious[ i ] = GetCurrentColor( EColorIndex( i ) );

	_ColorChangeTimer.Reset( ), _ColorChangeTimer.Start( );
}

void IInteractable::DoStateAnimations( )
{
	for ( auto& pAnimatedVector : vecAnimatedVectors )
		pAnimatedVector->OnStateChange( _State );

	for ( auto& pAnimatedDouble : vecAnimatedDoubles )
		pAnimatedDouble->OnStateChange( _State );
}

void IInteractable::AddState( EState _NewState )
{
	DoColorAnimations( );
	_State = _State | _NewState;
	DoStateAnimations( );
	PreCreateDrawables( );
	OnStateChange( );
}

void IInteractable::RemoveState( EState _NewState )
{
	DoColorAnimations( );
	_State = _State & ~_NewState;
	DoStateAnimations( );
	PreCreateDrawables( );
	OnStateChange( );
}

bool IInteractable::HasState( EState _TestState )
{
	return _State & _TestState;
}

rectangle_t IInteractable::GetAbsoluteLocation( )
{
	if ( pParent != nullptr )
		return GetLocation( ).ToPixels( ) + pParent->GetAbsoluteLocation( );

	return GetLocation( ).ToPixels( );
}

padding_t IInteractable::GetPadding( )
{
	return _Padding;
}

vector2_t IInteractable::GetNetSize( )
{
	return _Padding.vecData + GetSize( );
}

void IInteractable::AddAnimatedValue( animated_value_t< vector2_t > *pValue )
{
	vecAnimatedVectors.emplace_back( pValue );
}

void IInteractable::AddAnimatedValue( animated_value_t< double > *pValue )
{
	vecAnimatedDoubles.emplace_back( pValue );
}

void IInteractable::RemoveAnimatedValue( animated_value_t< vector2_t > *pValue )
{
	for ( auto u = 0u; u < vecAnimatedVectors.size( ); u++ )
		if ( vecAnimatedVectors[ u ] == pValue )
			vecAnimatedVectors.erase( vecAnimatedVectors.begin( ) + u );
}

void IInteractable::RemoveAnimatedValue( animated_value_t< double > *pValue )
{
	for ( auto u = 0u; u < vecAnimatedDoubles.size( ); u++ )
		if ( vecAnimatedDoubles[ u ] == pValue )
			vecAnimatedDoubles.erase( vecAnimatedDoubles.begin( ) + u );
}

std::pair< std::vector< animated_value_t< vector2_t >* >, std::vector< animated_value_t< double >* > > IInteractable::GetAnimatedValues( )
{
	return { vecAnimatedVectors, vecAnimatedDoubles };
}

callbacks_t & IInteractable::GetCallbacks( )
{
	return _Callbacks;
}

void IInteractable::SetDefaultSize( )
{ }

void IInteractable::Initialize( )
{ }

void IInteractable::NewFrame( )
{ }

void IInteractable::CreateDrawables( )
{ }

void IInteractable::Draw( )
{
	for ( auto& pDrawable : vecDrawables )
		pDrawable->Draw( );
}

void IInteractable::OnStateChange( )
{ }

void IInteractable::OnClick( CKeyState _State )
{ }

void IInteractable::OnRightClick( CKeyState _State )
{ }

void IInteractable::OnKeyPress( key_t _Code, CKeyState _State )
{ }

void IInteractable::OnKeyTyped( char chCharacter )
{ }

bool IInteractable::OnScroll( int iScrollAmount )
{
	return false;
}

void IInteractable::OnMouseMove( const vector2_t &vecMouseLocation )
{ }

void IInteractable::OnCopy( )
{ }

void IInteractable::OnPaste( )
{ }
