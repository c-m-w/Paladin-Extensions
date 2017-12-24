#pragma once

void Wait( unsigned long );
moment GetMoment( );

template< typename xDatatype, typename xDatatype2 > void Limit( xDatatype &xStatus, xDatatype2 xMinimum, xDatatype2 xMaximum )
{
	if ( xDatatype( xMinimum ) > xStatus )
	{
		xStatus = xDatatype( xMinimum );
	}
	else if ( xStatus > xDatatype( xMaximum ) )
	{
		xStatus = xDatatype( xMaximum );
	}
}

template< typename xDatatype > void Absolute( xDatatype &xStatus )
{
	if ( xStatus < 0 )
	{
		xStatus = -xStatus;
	}
}
