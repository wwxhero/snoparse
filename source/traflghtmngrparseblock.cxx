//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: traflghtmngrparseblock.cxx,v 1.11 2003/12/05 20:22:35 schikore Exp $
//
// The implementation for the traflghtmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "TrafficLightManager"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafLghtMngrParseBlock::CTrafLghtMngrParseBlock()
	: CSnoBlock()
{
	SetBlockName("TrafficLightManager");
} // end of CTrafLghtMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CTrafLghtMngrParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafLghtMngrParseBlock::CTrafLghtMngrParseBlock(const CTrafLghtMngrParseBlock& cCopy)
{
	*this = cCopy;
} // end of CTrafLghtMngrParseBlock

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
CTrafLghtMngrParseBlock::~CTrafLghtMngrParseBlock() 
{}// end of CTrafLghtMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock
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
CTrafLghtMngrParseBlock::CTrafLghtMngrParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CTrafLghtMngrParseBlock

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
CTrafLghtMngrParseBlock&
CTrafLghtMngrParseBlock::operator=(const CTrafLghtMngrParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock::GetDist
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		double
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafLghtMngrParseBlock::GetDist(void) const
{
	CSnoValue val;
	if (GetField("Distance", val))
		return val.GetFloatValue();
	else
		return 0.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock::GetState
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		EState
//
//////////////////////////////////////////////////////////////////////////////
CTrafLghtMngrParseBlock::EState CTrafLghtMngrParseBlock::GetState(void) const
{
	CSnoValue val;
	if (GetField( "State", val)) {
		return EState( val.GetIntValue() );
	}
	else return eOFF;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetAudioState
//				
//
// Remarks:		
//
// Arguments: 
//   double dist - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafLghtMngrParseBlock::SetDist(double dist)
{
	// Delete any "Distance" fields
	ClearFields("Distance");

	// Add new "Distance" field.
	AddField("Distance", dist);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafLghtMngrParseBlock::GetState
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		EState
//
//////////////////////////////////////////////////////////////////////////////
void CTrafLghtMngrParseBlock::SetState(EState state) 
{
	// Delete any "State" fields
	ClearFields("State");

	// Add new "State" field.
	AddField("State", (int)state);
}

