/// CContainer.hpp

#pragma once

#include "GUI.hpp"

enum EAlignment
{
	ALIGNMENT_LEFT,
	ALIGNMENT_CENTER,
	ALIGNMENT_RIGHT,
	ALIGNMENT_MAX
};

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

class CRow: public CContainer
{
private:

	double dbFill[ ALIGNMENT_MAX ] { };
	std::vector< EAlignment > vecObjectAlignments { };

	std::vector< IInteractable* > GetWidgets( EAlignment _Alignment );
	void AdjustWidgetPositions( );

public:

	CRow( const rectangle_t& recLocation );

	void AddWidget( IWidget* pWidget, EAlignment _Alignment );
	void RemoveWidget( IWidget* pWidgetToRemove );
	bool Overfilled( );
};

