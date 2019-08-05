/// CRow.hpp

#pragma once

#include "GUI.hpp"

enum EHorizontalAlignment
{
	HALIGNMENT_LEFT,
	HALIGNMENT_CENTER,
	HALIGNMENT_RIGHT,
	HALIGNMENT_MAX
};

enum EVerticalAlignment
{
	VALIGNMENT_TOP,
	VALIGNMENT_CENTER,
	VALIGNMENT_BOTTOM,
	VALIGNMENT_MAX
};

class IRow: public CContainer
{
protected:

	double dbAlignmentGap = 0.0;
	double dbAlignmentGapAddition = 0.0;

	virtual void AdjustWidgetPositions( ) = 0;
	virtual std::vector< IInteractable* > GetWidgets( ) = 0;

public:

	IRow( ) = default;
	virtual ~IRow( ) = default;

	void SetAlignmentGap( double dbNewAlignmentGap );
	virtual void AddWidget( IWidget* pWidget ) = 0;
	virtual void RemoveWidget( IWidget* pWidget ) = 0;
	virtual bool Overfilled( ) = 0;
	virtual void Clamp( ) = 0;
};

class CHorizontalRow: public IRow
{
private:

	EHorizontalAlignment _CurrentAlignment = HALIGNMENT_LEFT;
	double dbFill[ HALIGNMENT_MAX ] { };
	std::vector< EHorizontalAlignment > vecObjectAlignments { };

	void SetDefaultSize( ) override;
	std::vector< IInteractable* > GetWidgets( ) override;
	void AdjustWidgetPositions( ) override;

public:

	CHorizontalRow( ) = default;

	void AddWidget( IWidget* pWidget ) override;
	void RemoveWidget( IWidget* pWidget ) override;
	bool Overfilled( ) override;
	void Clamp( ) override;

	void SetAlignment( EHorizontalAlignment _NewAlignment );
};

class CVerticalRow: public IRow
{
private:

	EVerticalAlignment _CurrentAlignment = VALIGNMENT_TOP;
	double dbFill[ VALIGNMENT_MAX ] { };
	std::vector< EVerticalAlignment > vecObjectAlignments { };

	std::vector< IInteractable* > GetWidgets( ) override;
	void AdjustWidgetPositions( ) override;

public:

	CVerticalRow( ) = default;

	void AddWidget( IWidget* pWidget ) override;
	void RemoveWidget( IWidget* pWidget ) override;
	bool Overfilled( ) override;
	void Clamp( ) override;

	void SetAlignment( EVerticalAlignment _NewAlignment );
};
