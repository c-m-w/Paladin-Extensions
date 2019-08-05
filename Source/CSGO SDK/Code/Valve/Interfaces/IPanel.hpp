#pragma once

#include "ISurface.hpp"
#include "../Types/UtlVector.hpp"
#include "IBaseInterface.hpp"

class SurfacePlat;
class KeyValues;
class IClientPanel;
class CDmxElement;
class DmxElementUnpackStructure_t;
typedef unsigned long HScheme;

//!! must be removed
class Panel;

class IPanel: public IBaseInterface
{
public:
	virtual void Init( vgui::VPANEL vguiPanel, IClientPanel *panel ) = 0;

	// methods
	virtual void SetPos( vgui::VPANEL vguiPanel, int x, int y ) = 0;
	virtual void GetPos( vgui::VPANEL vguiPanel, int &x, int &y ) = 0;
	virtual void SetSize( vgui::VPANEL vguiPanel, int wide, int tall ) = 0;
	virtual void GetSize( vgui::VPANEL vguiPanel, int &wide, int &tall ) = 0;
	virtual void SetMinimumSize( vgui::VPANEL vguiPanel, int wide, int tall ) = 0;
	virtual void GetMinimumSize( vgui::VPANEL vguiPanel, int &wide, int &tall ) = 0;
	virtual void SetZPos( vgui::VPANEL vguiPanel, int z ) = 0;
	virtual int GetZPos( vgui::VPANEL vguiPanel ) = 0;

	virtual void GetAbsPos( vgui::VPANEL vguiPanel, int &x, int &y ) = 0;
	virtual void GetClipRect( vgui::VPANEL vguiPanel, int &x0, int &y0, int &x1, int &y1 ) = 0;
	virtual void SetInset( vgui::VPANEL vguiPanel, int left, int top, int right, int bottom ) = 0;
	virtual void GetInset( vgui::VPANEL vguiPanel, int &left, int &top, int &right, int &bottom ) = 0;

	virtual void SetVisible( vgui::VPANEL vguiPanel, bool state ) = 0;
	virtual bool IsVisible( vgui::VPANEL vguiPanel ) = 0;
	virtual void SetParent( vgui::VPANEL vguiPanel, vgui::VPANEL newParent ) = 0;
	virtual int GetChildCount( vgui::VPANEL vguiPanel ) = 0;
	virtual vgui::VPANEL GetChild( vgui::VPANEL vguiPanel, int index ) = 0;
	virtual CUtlVector< vgui::VPANEL > &GetChildren( vgui::VPANEL vguiPanel ) = 0;
	virtual vgui::VPANEL GetParent( vgui::VPANEL vguiPanel ) = 0;
	virtual void MoveToFront( vgui::VPANEL vguiPanel ) = 0;
	virtual void MoveToBack( vgui::VPANEL vguiPanel ) = 0;
	virtual bool HasParent( vgui::VPANEL vguiPanel, vgui::VPANEL potentialParent ) = 0;
	virtual bool IsPopup( vgui::VPANEL vguiPanel ) = 0;
	virtual void SetPopup( vgui::VPANEL vguiPanel, bool state ) = 0;
	virtual bool IsFullyVisible( vgui::VPANEL vguiPanel ) = 0;

	// gets the scheme this panel uses
	virtual HScheme GetScheme( vgui::VPANEL vguiPanel ) = 0;
	// gets whether or not this panel should scale with screen resolution
	virtual bool IsProportional( vgui::VPANEL vguiPanel ) = 0;
	// returns true if auto-deletion flag is set
	virtual bool IsAutoDeleteSet( vgui::VPANEL vguiPanel ) = 0;
	// deletes the Panel * associated with the vpanel
	virtual void DeletePanel( vgui::VPANEL vguiPanel ) = 0;

	// input interest
	virtual void SetKeyBoardInputEnabled( vgui::VPANEL vguiPanel, bool state ) = 0;
	virtual void SetMouseInputEnabled( vgui::VPANEL vguiPanel, bool state ) = 0;
	virtual bool IsKeyBoardInputEnabled( vgui::VPANEL vguiPanel ) = 0;
	virtual bool IsMouseInputEnabled( vgui::VPANEL vguiPanel ) = 0;

	// calculates the panels current position within the hierarchy
	virtual void Solve( vgui::VPANEL vguiPanel ) = 0;

	// gets names of the object (for debugging purposes)
	virtual const char *GetName( vgui::VPANEL vguiPanel ) = 0;
	virtual const char *GetClassName( vgui::VPANEL vguiPanel ) = 0;

	// delivers a message to the panel
	virtual void SendMessage( vgui::VPANEL vguiPanel, KeyValues *params, vgui::VPANEL ifromPanel ) = 0;

	// these pass through to the IClientPanel
	virtual void Think( vgui::VPANEL vguiPanel ) = 0;
	virtual void PerformApplySchemeSettings( vgui::VPANEL vguiPanel ) = 0;
	virtual void PaintTraverse( vgui::VPANEL vguiPanel, bool forceRepaint, bool allowForce = true ) = 0;
	virtual void Repaint( vgui::VPANEL vguiPanel ) = 0;
	virtual vgui::VPANEL IsWithinTraverse( vgui::VPANEL vguiPanel, int x, int y, bool traversePopups ) = 0;
	virtual void OnChildAdded( vgui::VPANEL vguiPanel, vgui::VPANEL child ) = 0;
	virtual void OnSizeChanged( vgui::VPANEL vguiPanel, int newWide, int newTall ) = 0;

	virtual void InternalFocusChanged( vgui::VPANEL vguiPanel, bool lost ) = 0;
	virtual bool RequestInfo( vgui::VPANEL vguiPanel, KeyValues *outputData ) = 0;
	virtual void RequestFocus( vgui::VPANEL vguiPanel, int direction = 0 ) = 0;
	virtual bool RequestFocusPrev( vgui::VPANEL vguiPanel, vgui::VPANEL existingPanel ) = 0;
	virtual bool RequestFocusNext( vgui::VPANEL vguiPanel, vgui::VPANEL existingPanel ) = 0;
	virtual vgui::VPANEL GetCurrentKeyFocus( vgui::VPANEL vguiPanel ) = 0;
	virtual int GetTabPosition( vgui::VPANEL vguiPanel ) = 0;

	// used by ISurface to store platform-specific data
	virtual SurfacePlat *Plat( vgui::VPANEL vguiPanel ) = 0;
	virtual void SetPlat( vgui::VPANEL vguiPanel, SurfacePlat *Plat ) = 0;

	// returns a pointer to the vgui controls baseclass Panel *
	// destinationModule needs to be passed in to verify that the returned Panel * is from the same module
	// it must be from the same module since Panel * vtbl may be different in each module
	virtual Panel *GetPanel( vgui::VPANEL vguiPanel, const char *destinationModule ) = 0;

	virtual bool IsEnabled( vgui::VPANEL vguiPanel ) = 0;
	virtual void SetEnabled( vgui::VPANEL vguiPanel, bool state ) = 0;

	// Used by the drag/drop manager to always draw on top
	virtual bool IsTopmostPopup( vgui::VPANEL vguiPanel ) = 0;
	virtual void SetTopmostPopup( vgui::VPANEL vguiPanel, bool state ) = 0;

	virtual void SetMessageContextId( vgui::VPANEL vguiPanel, int nContextId ) = 0;
	virtual int GetMessageContextId( vgui::VPANEL vguiPanel ) = 0;

	virtual const DmxElementUnpackStructure_t *GetUnpackStructure( vgui::VPANEL vguiPanel ) const = 0;
	virtual void OnUnserialized( vgui::VPANEL vguiPanel, CDmxElement *pElement ) = 0;

	// sibling pins
	virtual void SetSiblingPin( vgui::VPANEL vguiPanel, vgui::VPANEL newSibling, unsigned char iMyCornerToPin = 0, unsigned char iSiblingCornerToPinTo = 0 ) = 0;
};
