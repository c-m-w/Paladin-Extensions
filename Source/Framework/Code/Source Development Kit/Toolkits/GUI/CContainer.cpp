/// CContainer.cpp

#include "Precompile.hpp"

#define ACKNOWLEDGED_ENTRY_WARNING_1
#define USE_NAMESPACES
#include "../../../Framework.hpp"

CContainer::CContainer( const rectangle_t &recLocation ) :
	IInteractable( recLocation )
{ }

void CContainer::AddObject( IInteractable *pObject, const vector2_t& vecRelative )
{
	vecObjects.emplace_back( pObject );
	pObject->SetLocation( vecRelative );
	pObject->PreCreateDrawables( );
}

void CContainer::Draw( )
{
	for ( auto& pObject : vecObjects )
		pObject->Draw( );
}

std::vector<IInteractable *> CRow::GetWidgets( EAlignment _Alignment )
{
	std::vector< IInteractable* > vecReturn { };

	for ( auto u = 0u; u < vecObjects.size( ); u++ )
		if ( vecObjectAlignments[ u ] == _Alignment )
			vecReturn.emplace_back( vecObjects[ u ] );

	return vecReturn;
}

void CRow::AdjustWidgetPositions( )
{
	const std::vector< IInteractable* > vecWidgets[ ALIGNMENT_MAX ] { GetWidgets( ALIGNMENT_LEFT ), GetWidgets( ALIGNMENT_CENTER ), GetWidgets( ALIGNMENT_RIGHT ) };
	auto dbCenterWidgetWidth = 0.0;
	memset( dbFill, 0, sizeof dbFill );

	for ( auto& pWidget : vecWidgets[ ALIGNMENT_LEFT ] )
	{
		pWidget->SetLocation( { dbFill[ ALIGNMENT_LEFT ] + pWidget->GetPadding( ).x, pWidget->GetPadding( ).y } );
		dbFill[ ALIGNMENT_LEFT ] += pWidget->GetNetWidth( );
	}

	for ( auto& pWidget : vecWidgets[ ALIGNMENT_CENTER ] )
		dbCenterWidgetWidth += pWidget->GetNetWidth( );

	const auto dbCenterStart = std::round( recLocation.w / 2.0 - dbCenterWidgetWidth / 2.0 );

	for ( auto& pWidget : vecWidgets[ ALIGNMENT_CENTER ] )
	{
		auto vecPadding = pWidget->GetPadding( );

		if ( pWidget == vecWidgets[ ALIGNMENT_CENTER ][ 0 ] )
			vecPadding.x = 0.0;

		pWidget->SetLocation( { dbCenterStart + ( pWidget == vecWidgets[ ALIGNMENT_CENTER ][ 0 ] ? 0.0 : vecPadding.x ), vecPadding.y } );
		dbFill[ ALIGNMENT_CENTER ] += vecPadding.x + pWidget->GetSize( ).x;
	}

	for ( auto& pWidget : vecWidgets[ ALIGNMENT_RIGHT ] )
	{
		pWidget->SetLocation( { recLocation.w - dbFill[ ALIGNMENT_RIGHT ] - pWidget->GetPadding( ).x, pWidget->GetPadding( ).y } );
		dbFill[ ALIGNMENT_RIGHT ] += pWidget->GetNetWidth( );
	}

	for ( auto i = 0; i < ALIGNMENT_MAX; i++ )
		for ( auto j = 0u; j < vecWidgets[ i ].size( ); j++ )
			vecWidgets[ i ][ j ]->PreCreateDrawables( );
}

CRow::CRow( const rectangle_t& recLocation ) :
	CContainer( recLocation )
{ }

void CRow::AddWidget( IWidget *pWidget, EAlignment _Alignment )
{
	vecObjects.emplace_back( pWidget );
	vecObjectAlignments.emplace_back( _Alignment );
	AdjustWidgetPositions( );
}

void CRow::RemoveWidget( IWidget* pWidgetToRemove )
{
	for ( auto u = 0u; u < vecObjects.size( ); u++ )
		if ( vecObjects[ u ] == pWidgetToRemove )
			return vecObjects.erase( vecObjects.begin( ) + u ), vecObjectAlignments.erase( vecObjectAlignments.begin() + u ), void( );
}

bool CRow::Overfilled( )
{
	return dbFill[ ALIGNMENT_LEFT ] + dbFill[ ALIGNMENT_CENTER ] + dbFill[ ALIGNMENT_RIGHT ] > GetAbsoluteLocation( ).w;
}
