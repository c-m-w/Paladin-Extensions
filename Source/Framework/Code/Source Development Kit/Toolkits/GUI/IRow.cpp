/// CRow.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

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

	const auto dbCenterStart = std::round( recLocation.w / 2.0 - dbCenterWidgetWidth / 2.0 );

	for ( auto& pWidget : vecWidgets[ HALIGNMENT_CENTER ] )
	{
		auto vecPadding = pWidget->GetPadding( );

		if ( pWidget == vecWidgets[ HALIGNMENT_CENTER ][ 0 ] )
			vecPadding.h = 0.0;

		pWidget->SetLocation( { dbCenterStart + vecPadding.h, vecPadding.v } );
		dbFill[ HALIGNMENT_CENTER ] += vecPadding.h + pWidget->GetSize( ).x;
	}

	for ( auto& pWidget : vecWidgets[ HALIGNMENT_RIGHT ] )
	{
		pWidget->SetLocation( { recLocation.w - dbFill[ HALIGNMENT_RIGHT ] - pWidget->GetPadding( ).h, pWidget->GetPadding( ).v } );
		dbFill[ HALIGNMENT_RIGHT ] += GetNetSize( ).x;
	}

	for ( auto i = 0; i < HALIGNMENT_MAX; i++ )
		for ( auto j = 0u; j < vecWidgets[ i ].size( ); j++ )
			vecWidgets[ i ][ j ]->SetSize( { vecWidgets[ i ][ j ]->GetSize( ).x, recLocation.h - vecWidgets[ i ][ j ]->GetPadding( ).v } ), vecWidgets[ i ][ j ]->PreCreateDrawables( );

	SetAlignment( _Alignment );
}

void CHorizontalRow::AddWidget( IWidget * pWidget, double dWidth )
{
	vecInteractables.emplace_back( pWidget );
	vecObjectAlignments.emplace_back( _CurrentAlignment );
	pWidget->SetSize( { dWidth, 0.0 } );
	AdjustWidgetPositions( );
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

	const auto dbCenterStart = std::round( recLocation.h / 2.0 - dbCenterWidgetHeight / 2.0 );

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
			vecWidgets[ i ][ j ]->SetSize( { recLocation.w - vecWidgets[ i ][ j ]->GetPadding( ).h, vecWidgets[ i ][ j ]->GetSize( ).y } ), vecWidgets[ i ][ j ]->PreCreateDrawables( );

	SetAlignment( _Alignment );
}

void CVerticalRow::AddWidget( IWidget *pWidget, double dHeight )
{
	vecInteractables.emplace_back( pWidget );
	vecObjectAlignments.emplace_back( _CurrentAlignment );
	pWidget->SetSize( { 0.0, dHeight } );
	AdjustWidgetPositions( );
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

void CVerticalRow::SetAlignment( EVerticalAlignment _NewAlignment )
{
	_CurrentAlignment = _NewAlignment;
}
