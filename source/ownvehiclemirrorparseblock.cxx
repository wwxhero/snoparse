//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: ownvehiclemirrorparseblock.cxx,v 1.7 2000/03/27 18:33:25 jvogel Exp $
//
// The implementation for the ownvehiclemirror parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: COwnVehicleMirrorParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "OwnVehicleMirror"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
COwnVehicleMirrorParseBlock::COwnVehicleMirrorParseBlock()
	: CSnoBlock()
{
	SetBlockName("OwnVehicleMirror");
} // end of COwnVehicleMirrorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: COwnVehicleMirrorParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - COwnVehicleMirrorParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
COwnVehicleMirrorParseBlock::COwnVehicleMirrorParseBlock(const COwnVehicleMirrorParseBlock& cCopy)
{
	*this = cCopy;
} // end of COwnVehicleMirrorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~OwnVehicleMirrorParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
COwnVehicleMirrorParseBlock::~COwnVehicleMirrorParseBlock() 
{}// end of COwnVehicleMirrorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: COwnVehicleMirrorParseBlock
//	CSnoBlock constructor calls the superclass constructor with the parameter.
//
// Remarks:
//
// Arguments:
//	blk - the CSnoBlock initialization information
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
COwnVehicleMirrorParseBlock::COwnVehicleMirrorParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of COwnVehicleMirrorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: operator=
//	The assignment operator calls the superclass assignment operator.
//
// Remarks:
//
// Arguments:
//	cRhs - righthand side of the assignment
//
// Returns: A reference to the current instance to allow nested assignments
//
//////////////////////////////////////////////////////////////////////////////
COwnVehicleMirrorParseBlock&
COwnVehicleMirrorParseBlock::operator=(const COwnVehicleMirrorParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

