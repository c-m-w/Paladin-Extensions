/// CContainer.hpp

#pragma once

#include "GUI.hpp"

class CContainer: public IInteractable
{
protected:

	std::vector< IInteractable* > vecObjects { };
	unsigned uScrollAmount = 0u;

public:

	CContainer( const rectangle_t& recLocation );

	void AddObject( IInteractable* pObject, const Utilities::vector2_t& vecRelative );
	void Draw( ) override;
};

