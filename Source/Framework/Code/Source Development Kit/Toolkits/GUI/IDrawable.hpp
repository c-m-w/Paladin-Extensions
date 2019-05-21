/// IDrawable.hpp

#pragma once

#include "GUI.hpp"

class IDrawable
{
protected:

	rectangle_t recLocation { };
	std::vector< CDrawable* > vecDrawables { };

public:

	IDrawable( IDrawable* pParent, const rectangle_t& recLocation );
	IDrawable( const rectangle_t& recLocation );

	rectangle_t GetLocation( );
	Utilities::vector2_t GetSize( );
	void PreCreateDrawables( );
	void SetLocation( const Utilities::vector2_t& vecNew );


	virtual void CreateDrawables( ) = 0;
	virtual void Draw( );
};
