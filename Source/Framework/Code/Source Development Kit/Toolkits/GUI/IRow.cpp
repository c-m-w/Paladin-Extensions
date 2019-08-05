/// CRow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

void IRow::SetAlignmentGap( double dbNewAlignmentGap )
{
	dbAlignmentGap = dbNewAlignmentGap;
	if ( bSetSize )
		SetDefaultSize( );
}

void CHorizontalRow::SetDefaultSize( )
{
	const std::vector< IInteractable* > vecWidgets[ HALIGNMENT_MAX ]
	{
		( SetAlignment( HALIGNMENT_LEFT ), GetWidgets( ) ),
		( SetAlignment( HALIGNMENT_CENTER ), GetWidgets( ) ),
		( SetAlignment( HALIGNMENT_RIGHT ), GetWidgets( ) )
	};

	auto iAlignmentsFilled = 0;
	vector2_t vecNewSize { };

	for ( auto& _Interactables : vecWidgets )
	{
		if ( !_Interactables.empty( ) )
			iAlignmentsFilled++;

		for ( auto& _Interactable : _Interactables )
		{
			const auto vecNetSize = _Interactable->GetNetSize( );

			vecNewSize.y = std::max( vecNewSize.y, vecNetSize.y );
			vecNewSize.x += vecNetSize.x;
		}
	}

	dbAlignmentGapAddition = ( iAlignmentsFilled - 1 ) * dbAlignmentGap;
	vecNewSize.x += dbAlignmentGapAddition;

	SetSize( vecNewSize );
	AdjustWidgetPositions( );
}

std::vector<IInteractable*> CHorizontalRow::GetWidgets( )
{
	std::vector< IInteractable* > vecReturn { };

	for ( auto u = 0u; u < vecInteractables.size( ); u++ )
		if ( vecObjectAlignments[ u ] == _CurrentAlignment )
			vecReturn.emplace_back( vecInteractables[ u ] );

	return vecReturn;
}

void CHorizontalRow::AdjustWidgetPositions( )
{
	const auto _Alignment = _CurrentAlignment;
	const std::vector< IInteractable* > vecWidgets[ HALIGNMENT_MAX ] 
	{ 
		( SetAlignment( HALIGNMENT_LEFT ), GetWidgets( ) ),
		( SetAlignment( HALIGNMENT_CENTER ), GetWidgets( ) ),
		( SetAlignment( HALIGNMENT_RIGHT ), GetWidgets( ) ) 
	};
	auto dbCenterWidgetWidth = 0.0;
	memset( dbFill, 0, sizeof dbFill );

	for ( auto& pWidget : vecWidgets[ HALIGNMENT_LEFT ] )
	{
		pWidget->SetLocation( { dbFill[ HALIGNMENT_LEFT ] + pWidget->GetPadding( ).h, pWidget->GetPadding( ).v } );
		dbFill[ HALIGNMENT_LEFT ] += pWidget->GetNetSize( ).x;
	}

	for ( auto& pWidget : vecWidgets[ HALIGNMENT_CENTER ] )
		dbCenterWidgetWidth += pWidget->GetNetSize( ).x;

	if ( !vecWidgets[ HALIGNMENT_CENTER ].empty( ) )
		dbCenterWidgetWidth -= vecWidgets[ HALIGNMENT_CENTER ][ 0 ]->GetPadding( ).h;

	auto dbCenterStart = PixelsToInches( InchesToPixels( ( recLocation.w - dbAlignmentGapAddition ) / 2.0 ) - InchesToPixels( dbCenterWidgetWidth / 2.0 ) );

	if ( !vecWidgets[ HALIGNMENT_LEFT ].empty( ) )
		dbCenterStart += dbAlignmentGap;

	for ( auto& pWidget : vecWidgets[ HALIGNMENT_CENTER ] )
	{
		auto vecPadding = pWidget->GetPadding( );

		if ( pWidget == vecWidgets[ HALIGNMENT_CENTER ][ 0 ] )
			vecPadding.h = 0.0;

		pWidget->SetLocation( { dbCenterStart + vecPadding.h, vecPadding.v } );
		dbFill[ HALIGNMENT_CENTER ] += vecPadding.h + pWidget->GetSize( ).x;
	}

	const auto dbRightAlignmentStart = recLocation.w - dbAlignmentGapAddition + ( !vecWidgets[ HALIGNMENT_LEFT ].empty( ) || !vecWidgets[ HALIGNMENT_CENTER ].empty( ) ? dbAlignmentGap : 0.0 );

	for ( auto i = int( vecWidgets[ HALIGNMENT_RIGHT ].size( ) ) - 1; i >= 0; i-- )
	{
		auto& pWidget = vecWidgets[ HALIGNMENT_RIGHT ][ i ];

		pWidget->SetLocation( { recLocation.w - dbFill[ HALIGNMENT_RIGHT ] - pWidget->GetNetSize( ).x, pWidget->GetPadding( ).v } );
		dbFill[ HALIGNMENT_RIGHT ] += pWidget->GetNetSize( ).x;
	}

	for ( auto i = 0; i < HALIGNMENT_MAX; i++ )
		for ( auto j = 0u; j < vecWidgets[ i ].size( ); j++ )
			vecWidgets[ i ][ j ]->PreCreateDrawables( );

	SetAlignment( _Alignment );
}

void CHorizontalRow::AddWidget( IWidget * pWidget )
{
	vecInteractables.emplace_back( pWidget );
	vecObjectAlignments.emplace_back( _CurrentAlignment );
	AdjustWidgetPositions( );
	pWidget->SetParent( this );
}

void CHorizontalRow::RemoveWidget( IWidget* pWidget )
{
	for ( auto u = 0u; u < vecInteractables.size( ); u++ )
		if ( vecInteractables[ u ] == pWidget )
			return vecInteractables.erase( vecInteractables.begin( ) + u ), vecObjectAlignments.erase( vecObjectAlignments.begin( ) + u ), void( );
}

bool CHorizontalRow::Overfilled( )
{
	return dbFill[ HALIGNMENT_LEFT ] + dbFill[ HALIGNMENT_CENTER ] + dbFill[ HALIGNMENT_RIGHT ] > GetAbsoluteLocation( ).w;
}

void CHorizontalRow::Clamp( )
{
	if ( !bSetSize )
		SetDefaultSize( );

	for ( auto& pInteractable : vecInteractables )
		pInteractable->SetSize( { pInteractable->GetSize( ).x, pInteractable->GetSize( ).y + GetSize( ).y - pInteractable->GetNetSize( ).y } );
}

void CHorizontalRow::SetAlignment( EHorizontalAlignment _NewAlignment )
{
	_CurrentAlignment = _NewAlignment;
}

std::vector<IInteractable *> CVerticalRow::GetWidgets( )
{
	std::vector< IInteractable* > vecReturn { };

	for ( auto u = 0u; u < vecInteractables.size( ); u++ )
		if ( vecObjectAlignments[ u ] == _CurrentAlignment )
			vecReturn.emplace_back( vecInteractables[ u ] );

	return vecReturn;
}

void CVerticalRow::AdjustWidgetPositions( )
{
	const auto _Alignment = _CurrentAlignment;
	const std::vector< IInteractable* > vecWidgets[ HALIGNMENT_MAX ]
	{
		( SetAlignment( VALIGNMENT_TOP ), GetWidgets( ) ),
		( SetAlignment( VALIGNMENT_CENTER ), GetWidgets( ) ),
		( SetAlignment( VALIGNMENT_BOTTOM ), GetWidgets( ) )
	};
	auto dbCenterWidgetHeight = 0.0;
	memset( dbFill, 0, sizeof dbFill );

	for ( auto& pWidget : vecWidgets[ VALIGNMENT_TOP ] )
	{
		pWidget->SetLocation( { pWidget->GetPadding( ).h , dbFill[ VALIGNMENT_TOP ] + pWidget->GetPadding( ).v } );
		dbFill[ VALIGNMENT_TOP ] += pWidget->GetNetSize( ).y;
	}

	for ( auto& pWidget : vecWidgets[ VALIGNMENT_CENTER ] )
		dbCenterWidgetHeight += pWidget->GetNetSize( ).x;

	if ( dbCenterWidgetHeight > 0.0 )
		dbCenterWidgetHeight -= vecWidgets[ VALIGNMENT_CENTER ][ 0 ]->GetPadding( ).v;

	const auto dbCenterStart = PixelsToInches( std::round( InchesToPixels( recLocation.h / 2.0 - dbCenterWidgetHeight / 2.0 ) ) );

	for ( auto& pWidget : vecWidgets[ VALIGNMENT_CENTER ] )
	{
		auto vecPadding = pWidget->GetPadding( );

		if ( pWidget == vecWidgets[ VALIGNMENT_CENTER ][ 0 ] )
			vecPadding.v = 0.0;

		pWidget->SetLocation( { vecPadding.h, dbCenterStart + vecPadding.v } );
		dbFill[ VALIGNMENT_CENTER ] += vecPadding.v + pWidget->GetSize( ).y;
	}

	for ( auto& pWidget : vecWidgets[ VALIGNMENT_BOTTOM ] )
	{
		pWidget->SetLocation( { pWidget->GetPadding( ).h, recLocation.h - dbFill[ VALIGNMENT_BOTTOM ] - pWidget->GetPadding( ).v } );
		dbFill[ VALIGNMENT_BOTTOM ] += pWidget->GetNetSize( ).x;
	}

	for ( auto i = 0; i < HALIGNMENT_MAX; i++ )
		for ( auto j = 0u; j < vecWidgets[ i ].size( ); j++ )
			vecWidgets[ i ][ j ]->PreCreateDrawables( );

	SetAlignment( _Alignment );
}

void CVerticalRow::AddWidget( IWidget *pWidget )
{
	vecInteractables.emplace_back( pWidget );
	vecObjectAlignments.emplace_back( _CurrentAlignment );
	AdjustWidgetPositions( );
	pWidget->SetParent( this );
}

void CVerticalRow::RemoveWidget( IWidget *pWidget )
{
	for ( auto u = 0u; u < vecInteractables.size( ); u++ )
		if ( vecInteractables[ u ] == pWidget )
			return vecInteractables.erase( vecInteractables.begin( ) + u ), vecObjectAlignments.erase( vecObjectAlignments.begin( ) + u ), void( );
}

bool CVerticalRow::Overfilled( )
{
	return dbFill[ VALIGNMENT_TOP ] + dbFill[ VALIGNMENT_CENTER ] + dbFill[ VALIGNMENT_BOTTOM ] > GetAbsoluteLocation( ).w;
}

void CVerticalRow::Clamp( )
{
	if ( !bSetSize )
		SetDefaultSize( );

	for ( auto& pInteractable : vecInteractables )
		pInteractable->SetSize( { pInteractable->GetSize( ).x + GetSize( ).x - pInteractable->GetNetSize( ).x, pInteractable->GetSize( ).y } );
}

void CVerticalRow::SetAlignment( EVerticalAlignment _NewAlignment )
{
	_CurrentAlignment = _NewAlignment;
}
