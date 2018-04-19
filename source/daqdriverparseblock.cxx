//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Omar Ahmad, Sunil Bulusu
// Date:	 June, 2001
//
// $Id: daqdriverparseblock.cxx,v 1.6 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The implementation for the traffic data parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDaqDriverParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "DaqDriver" and the
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDaqDriverParseBlock::CDaqDriverParseBlock()
	: CSnoBlock()
{
	SetBlockName("DaqDriver");
} // end of CDaqDriverParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDaqDriverParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CDaqDriverParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDaqDriverParseBlock::CDaqDriverParseBlock(const CDaqDriverParseBlock& cCopy)
{
	*this = cCopy;
} // end of CDaqDriverParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~CDaqDriverParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDaqDriverParseBlock::~CDaqDriverParseBlock() {}// end of CDaqDriverParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDaqDriverParseBlock
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
CDaqDriverParseBlock::CDaqDriverParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CDaqDriverParseBlock

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
CDaqDriverParseBlock&
CDaqDriverParseBlock::operator=(const CDaqDriverParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=


//////////////////////////////////////////////////////////////////////////////
// Accessor functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the 'DataFileName' field.
//
//////////////////////////////////////////////////////////////////////////////
string
CDaqDriverParseBlock::GetDriverPosFileName(void) const
{
	CSnoValue val;
	if (GetField("DriverPosFileName", val))
		return val.GetStringValue();
	else
		return "";
} // end of GetDriverPosFileName

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the 'PositionFileName' field.
//
//////////////////////////////////////////////////////////////////////////////
string
CDaqDriverParseBlock::GetDriverOriFileName(void) const
{
	CSnoValue val;
	if (GetField("DriverOriFileName", val))
		return val.GetStringValue();
	else
		return "";
} // end of GetDriverOriFileName

//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Freq field.
//
//////////////////////////////////////////////////////////////////////////////
double
CDaqDriverParseBlock::GetFreq(void) const
{
	CSnoValue val;
	if (GetField("Freq", val))
		return val.GetFloatValue();
	else
		return 0.0f;
} // end of GetFreq

//////////////////////////////////////////////////////////////////////////////
// 	Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
// Remarks:
//
// Arguments:
//	objName - The name of the object to log.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CDaqDriverParseBlock::SetDriverPosFileName(const string& objName)
{
	// Delete any "DriverPosFileName" fields
	ClearFields("DriverPosFileName");

	// Add new "DriverPosFileName" field.
	AddField("DriverPosFileName", objName);

} // end of SetDriverPosFileName

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
// Remarks:
//
// Arguments:
//	objName - The name of the object to log.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CDaqDriverParseBlock::SetDriverOriFileName(const string& objName)
{
	// Delete any "DriverOriFileName" fields
	ClearFields("DriverOriFileName");

	// Add new "DriverOriFileName" field.
	AddField("DriverOriFileName", objName);

} // end of SetDriverOriFileName

//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Remarks:
//
// Arguments:
//   val - A double that inidicates the minimum acceleration.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CDaqDriverParseBlock::SetFreq(double val)
{
	// Delete any "Freq" fields
	ClearFields("Freq");

	// Add new "Freq" field.
	AddField("Freq", val);

} // end of SetFreq
