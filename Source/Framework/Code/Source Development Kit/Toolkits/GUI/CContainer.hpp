/// CContainer.hpp

#pragma once

#include "GUI.hpp"

class CContainer: public IInteractable
{
private:

	bool bDrawBackground = false;

	void CreateDrawables( ) override;
	void Draw( ) override;

protected:

	std::vector< IInteractable* > vecInteractables { };
	unsigned uScrollAmount = 0u;

public:

	CContainer( );

	void DrawBackground( );
	void AddObject( IInteractable* pObject, const Utilities::vector2_t& vecRelative );
	void RemoveObject( IInteractable* pObject );
	const std::vector< IInteractable* >& GetContainedInteractables( );
};

