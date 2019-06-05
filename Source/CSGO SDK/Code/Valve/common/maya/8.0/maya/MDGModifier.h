#ifndef _MDGModifier
#define _MDGModifier
//
//-
// ==========================================================================
// Copyright (C) 1995 - 2006 Autodesk, Inc., and/or its licensors.  All 
// rights reserved.
// 
// The coded instructions, statements, computer programs, and/or related 
// material (collectively the "Data") in these files contain unpublished 
// information proprietary to Autodesk, Inc. ("Autodesk") and/or its 
// licensors,  which is protected by U.S. and Canadian federal copyright law 
// and by international treaties.
// 
// The Data may not be disclosed or distributed to third parties or be 
// copied or duplicated, in whole or in part, without the prior written 
// consent of Autodesk.
// 
// The copyright notices in the Software and this entire statement, 
// including the above license grant, this restriction and the following 
// disclaimer, must be included in all copies of the Software, in whole 
// or in part, and all derivative works of the Software, unless such copies 
// or derivative works are solely in the form of machine-executable object 
// code generated by a source language processor.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
// AUTODESK DOES NOT MAKE AND HEREBY DISCLAIMS ANY EXPRESS OR IMPLIED 
// WARRANTIES INCLUDING, BUT NOT LIMITED TO, THE WARRANTIES OF 
// NON-INFRINGEMENT, MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, 
// OR ARISING FROM A COURSE OF DEALING, USAGE, OR TRADE PRACTICE. IN NO 
// EVENT WILL AUTODESK AND/OR ITS LICENSORS BE LIABLE FOR ANY LOST 
// REVENUES, DATA, OR PROFITS, OR SPECIAL, DIRECT, INDIRECT, OR 
// CONSEQUENTIAL DAMAGES, EVEN IF AUTODESK AND/OR ITS LICENSORS HAS 
// BEEN ADVISED OF THE POSSIBILITY OR PROBABILITY OF SUCH DAMAGES. 
// ==========================================================================
//+
//
// CLASS:    MDGModifier
//
// *****************************************************************************
//
// CLASS DESCRIPTION (MDGModifier)
//
// An MDGModifier is used to change the structure of the dependency graph.  This
// includes adding nodes, making new connections, and removing existing
// connections.  An MDGModifier keeps track of all operations that it is
// used for, so that they can be undone or redone.  Calling undo causes an
// MDGModifier to undo all of the dependency graph changes that it has
// done.
//
// *****************************************************************************

#if defined __cplusplus

// *****************************************************************************

// INCLUDED HEADER FILES



#include <maya/MStatus.h>
#include <maya/MFnDependencyNode.h>

// *****************************************************************************

// DECLARATIONS

class TdependNode;
class Tattribute;
class TattributeList;
class Tstring;
class MObject;
class MPlug;
class MTypeId;
class MString;

// *****************************************************************************

// CLASS DECLARATION (MDGModifier)

/// Dependency graph modifier
/**
  A class that is used to modify the dependency graph and also supports undo 
*/
#if defined(_WIN32)
#pragma warning(disable: 4522)
#endif // _WIN32

class OPENMAYA_EXPORT MDGModifier  
{
public:
    ///
	MDGModifier();
    ///
	virtual ~MDGModifier();    
    
    ///
    MObject     createNode( const MTypeId &typeId,
                            MStatus* ReturnStatus = NULL );
    ///
    MObject     createNode( const MString &type,
                            MStatus* ReturnStatus = NULL );
    /// 
    MStatus     deleteNode( const MObject & node );
    
    ///
    MStatus     renameNode( const MObject & node, const MString &newName );

	///
	MStatus		setNodeLockState( const MObject & node, bool newState ); 

    ///
	MStatus		connect(	const MObject & sourceNode,
							const MObject & sourceAttr,
							const MObject & destNode,	
							const MObject & destAttr );
    ///
	MStatus		disconnect(	const MObject & sourceNode,
							const MObject & sourceAttr,
							const MObject & destNode,
							const MObject & destAttr );
    ///
	MStatus		connect(	const MPlug& source, const MPlug& dest );
    ///
	MStatus		disconnect(	const MPlug& source, const MPlug& dest );

	///
    MStatus     addAttribute( const MObject& node, const MObject& attribute,
							  MFnDependencyNode::MAttrClass type 
									= MFnDependencyNode::kLocalDynamicAttr );
    ///
    MStatus     removeAttribute( const MObject& node, const MObject& attribute,
								 MFnDependencyNode::MAttrClass type 
									= MFnDependencyNode::kLocalDynamicAttr  );

    ///
	MStatus		commandToExecute( const MString& command );
    ///
	MStatus		doIt();
    ///
	MStatus		undoIt();


protected:
    MDGModifier( void * );
	MDGModifier( const MDGModifier & other );
	MDGModifier&	operator =( const MDGModifier & rhs );
	bool		checkCompoundAttrs(const TattributeList&, const Tstring&, const Tstring&);
	bool		attrExistsAtNode(TdependNode*, Tattribute*);
	void*		  data;
	bool		  fOwn;

private:
	static const  char*	className();
};

#if defined(_WIN32)
#pragma warning(default: 4522)
#endif // _WIN32

// *****************************************************************************
#endif /* __cplusplus */
#endif /* _MDGModifier */
