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

IInteractable::IInteractable( unsigned uObjectSize, EInteractableType _Type ) :
	uObjectSize( uObjectSize ), _Type( _Type )
{ }

IInteractable::~IInteractable( )
{
	delete pHash;
}

bool IInteractable::IsInteractableType( EInteractableType _TestType )
{
	return _Type == _TestType;
}

void IInteractable::Initialize( IContainer *pNewParent, const rectangle_t &recNewLocation )
{
	pParent = pNewParent;
	recLocation = recNewLocation;
}

void IInteractable::Initialize( IContainer *pNewParent, const vector2_t &vecNewLocation )
{
	pParent = pNewParent;
	recLocation.vecLocation = vecNewLocation;
}

rectangle_t IInteractable::GetLocation( )
{
	return { recLocation.x + vecRelative.x, recLocation.y + vecRelative.y, recLocation.w, recLocation.h };
}

vector2_t IInteractable::GetSize( )
{
	return recLocation.vecSize;
}

void IInteractable::PreCreateDrawables( )
{
	if ( !bSetSize )
		throw std::runtime_error( ENC( "Size not set on interactable before attempting to create drawables." ) );

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
	const auto uHash = _Cryptography.GenerateNumericHash( this, uObjectSize );

	if ( uHash != *pHash )
	{
		PreCreateDrawables( );
		*pHash = uHash;
	}

	const auto recLocation = GetAbsoluteLocation( );

	if ( !_Drawing.IsAreaVisible( recLocation ) )
		return;

	_Drawing.PushDrawingSpace( recLocation );
	Draw( );
	_Drawing.PopDrawingSpace( );
}

void IInteractable::SetLocation( const vector2_t& vecNew )
{
	recLocation.vecLocation = vecNew;
	if ( bInitialized )
		PreCreateDrawables( );
}

void IInteractable::SetSize( const vector2_t &vecSize )
{
	bSetSize = true;
	recLocation.vecSize = vecSize;
	if ( bInitialized )
		PreCreateDrawables( );
}

void IInteractable::SetPadding( const padding_t &_NewPadding )
{
	_Padding = _NewPadding;
}

void IInteractable::AddState( EState _NewState )
{
	_State = _State | _NewState;
	PreCreateDrawables( );
	OnStateChange( );
}

void IInteractable::RemoveState( EState _NewState )
{
	_State = _State & ~_NewState;
	PreCreateDrawables( );
	OnStateChange( );
}

rectangle_t IInteractable::GetAbsoluteLocation( )
{
	if ( pParent != nullptr )
		return GetLocation( ) + pParent->GetLocation( );

	return GetLocation( );
}

padding_t IInteractable::GetPadding( )
{
	return _Padding;
}

vector2_t IInteractable::GetNetSize( )
{
	return _Padding.vecData + recLocation.vecSize;
}

auto IInteractable::size( ) -> unsigned
{
	return sizeof( *this );
}

void IInteractable::Initialize( )
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

void IInteractable::OnScroll( int iScrollAmount )
{ }
