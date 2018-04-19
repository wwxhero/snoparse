//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: vehfailparseblock.cxx,v 1.4 2000/03/08 21:43:01 jvogel Exp $
//
// The implementation for the vehfail parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVehFailParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "VehFail"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVehFailParseBlock::CVehFailParseBlock()
	: CSnoBlock()
{
	SetBlockName("VehFail");
} // end of CVehFailParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVehFailParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CVehFailParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVehFailParseBlock::CVehFailParseBlock(const CVehFailParseBlock& cCopy)
{
	*this = cCopy;
} // end of CVehFailParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~VehFailParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVehFailParseBlock::~CVehFailParseBlock() {}// end of CVehFailParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVehFailParseBlock
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
CVehFailParseBlock::CVehFailParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CVehFailParseBlock

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
CVehFailParseBlock&
CVehFailParseBlock::operator=(const CVehFailParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

