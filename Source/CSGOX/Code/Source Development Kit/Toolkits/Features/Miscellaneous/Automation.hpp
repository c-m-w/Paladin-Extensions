/// Automation.hpp

#pragma once

class CAutomation: IMiscellaneousContextInternal
{
public:
	void flee( ) override;



	// when you move mouse, it'll automatically adjust directional movement input
	void StrafeAutomation( );
	// autonomously changes input and mouse direction silently to gain maximum air strafe speed
	void AutonomousStrafe( );
} inline _Automation;
