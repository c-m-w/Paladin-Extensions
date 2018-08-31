/// User Interface.hpp

#pragma once

namespace PX::UI::Manager
{
	namespace CSGO
	{
		PX_SDK auto bCreatedTextures = true;
		bool PX_API Initialize( );
		void PX_API OnEndScene( );
		void PX_API OnReset( );
		void PX_API OnSuccessfulReset( unsigned uWidth, unsigned uHeight );
	}

	void PX_API SetLayout( );
	void PX_API DrawOther( );
}
