/// User Interface.cpp

#include "../PX CSGO.hpp"

namespace PX::UI::Manager
{
	namespace CSGO
	{
		bool PX_API Initialize( )
		{
			unsigned uDimensions[ 2 ] { 720, 600 };

			PX_INPUT.AddKeyCallback( VK_HOME, [ = ]( bool bIsPressed )
			{
				if( bIsPressed )
					Render::bShouldRender = !Render::bShouldRender;
				while( ShowCursor( true ) <= 0 );
			} );

			return Render::InitializeRenderTarget( Information::Interfaces::pDevice, uDimensions )
				&& InitializeUI( PX_XOR( "CS: GO" ) );
		}
	}

	void PX_API SetLayout( )
	{
		Example( );
	}

	void PX_API DrawOther( )
	{
	}
}
