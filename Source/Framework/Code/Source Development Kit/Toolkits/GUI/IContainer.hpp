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

	IContainer( const rectangle_t& recLocation );

	void AddObject( IInteractable* pObject, const Utilities::vector2_t& vecRelative );
	const std::vector< IInteractable* >& GetContainedInteractables( );
};

