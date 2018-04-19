//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Matt Schikore
// Date:	 May, 2000
//
// $Id: sobjmngrparseblock.cxx,v 1.1 2000/05/08 16:49:17 schikore Exp $
//
// The implementation for the sobjmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSobjMngrParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "StaticObj"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSobjMngrParseBlock::CSobjMngrParseBlock()
	: CSnoBlock()
{
	SetBlockName("StaticObjManager");
} // end of CSobjMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSobjMngrParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CSobjMngrParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSobjMngrParseBlock::CSobjMngrParseBlock(const CSobjMngrParseBlock& cCopy)
{
	*this = cCopy;
} // end of CSobjMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~TrafLghtMngrParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSobjMngrParseBlock::~CSobjMngrParseBlock() 
{}// end of CSobjMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSobjMngrParseBlock
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
CSobjMngrParseBlock::CSobjMngrParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CSobjMngrParseBlock

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
CSobjMngrParseBlock&
CSobjMngrParseBlock::operator=(const CSobjMngrParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

