/// User Interface.hpp

#pragma once

namespace PX::UI::Manager
{
	namespace CSGO
	{
		PX_SDK auto bCreatedTextures = true;
		bool PX_API Initialize( );
		void PX_API OnEndScene( Types::ptr_t ptrReturnAddress );
	}

	void PX_API SetLayout( );
	void PX_API DrawOther( );
}
