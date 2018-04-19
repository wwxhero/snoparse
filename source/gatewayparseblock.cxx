//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: gatewayparseblock.cxx,v 1.5 2000/03/08 21:43:01 jvogel Exp $
//
// The implementation for the gateway parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CGatewayParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "Gateway"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CGatewayParseBlock::CGatewayParseBlock()
	: CSnoBlock()
{
	SetBlockName("Gateway");
} // end of CGatewayParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CGatewayParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CGatewayParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CGatewayParseBlock::CGatewayParseBlock(const CGatewayParseBlock& cCopy)
{
	*this = cCopy;
} // end of CGatewayParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~GatewayParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CGatewayParseBlock::~CGatewayParseBlock() {}// end of CGatewayParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CGatewayParseBlock
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
CGatewayParseBlock::CGatewayParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CGatewayParseBlock

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
CGatewayParseBlock&
CGatewayParseBlock::operator=(const CGatewayParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

