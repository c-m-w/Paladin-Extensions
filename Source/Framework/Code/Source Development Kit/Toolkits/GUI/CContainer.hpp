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

	std::deque< IInteractable* > vecInteractables { };
	bool bStrictBounds = false;
	bool bEnableScrollbar = false;
	Utilities::vector2_t vecScrollAmount { }, vecBoundary { };
	double dbAlphaRatio = 1.0;
	bool bHorizontal = false, bVertical = true;
	CScrollbar* pVertical = nullptr, *pHorizontal = nullptr;

	void UpdateScrollbarInformation( );
	void UpdateScrollbars( );
	void ClampScroll( );

public:

	CContainer( );

	void SetStrictBounds( bool bNewStrictBounds );
	bool GetStrictBounds( );
	void EnableScrollbars( );
	void DrawBackground( );
	double& GetAlphaRatio( );
	Utilities::vector2_t GetScrollOffset( );
	void AddObject( IInteractable* pObject, const Utilities::vector2_t& vecRelative );
	void RemoveObject( IInteractable* pObject );
	const std::deque< IInteractable* >& GetContainedInteractables( );
	bool OnScroll( int iScrollAmount ) override;

	friend class CScrollbar;
};

