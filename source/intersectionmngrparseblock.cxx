//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: intersectionmngrparseblock.cxx,v 1.7 2000/03/27 18:33:25 jvogel Exp $
//
// The implementation for the intrsctnmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CIntersectionMngrParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "IntersectionManager"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CIntersectionMngrParseBlock::CIntersectionMngrParseBlock()
	: CSnoBlock()
{
	SetBlockName("IntersectionManager");
} // end of CIntersectionMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CIntersectionMngrParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CIntersectionMngrParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CIntersectionMngrParseBlock::CIntersectionMngrParseBlock(const CIntersectionMngrParseBlock& cCopy)
{
	*this = cCopy;
} // end of CIntersectionMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~IntrsctnMngrParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CIntersectionMngrParseBlock::~CIntersectionMngrParseBlock() 
{}// end of CIntersectionMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CIntersectionMngrParseBlock
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
CIntersectionMngrParseBlock::CIntersectionMngrParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CIntersectionMngrParseBlock

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
CIntersectionMngrParseBlock&
CIntersectionMngrParseBlock::operator=(const CIntersectionMngrParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

