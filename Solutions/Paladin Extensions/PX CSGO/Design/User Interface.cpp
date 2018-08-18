/// User Interface.cpp

#include "../PX CSGO.hpp"

namespace PX::UI::Manager
{
	void PX_API SetLayout( )
	{
		Example( );
	}

	void PX_API DrawOther( )
	{
		std::deque< D3DXVECTOR2 > dqPoints;
		dqPoints.emplace_back( 0, 0 );
		dqPoints.emplace_back( 100, 0 );
		dqPoints.emplace_back( 100, 100 );
		dqPoints.emplace_back( 600, 600 );
		Drawing::Line( dqPoints, 5, D3DCOLOR_ARGB( 150, 0, 0, 255 ) );
	}
}
