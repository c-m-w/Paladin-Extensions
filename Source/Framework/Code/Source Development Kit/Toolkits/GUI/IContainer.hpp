/// IContainer.hpp

#pragma once

#include "GUI.hpp"

class IContainer: public IInteractable
{
private:

	void Draw( ) override;

protected:

	std::vector< IInteractable* > vecInteractables { };
	unsigned uScrollAmount = 0u;

public:

	IContainer( );

	void AddObject( IInteractable* pObject, const Utilities::vector2_t& vecRelative );
	void RemoveObject( IInteractable* pObject );
	const std::vector< IInteractable* >& GetContainedInteractables( );
};

