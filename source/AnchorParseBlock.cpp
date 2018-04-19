//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 David Heitbrink
// Date:	 May 2006
//
// $Id: 
//
// The implementation for the CAnchorParseBlock parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include "anchorparseblock.h"

using namespace std;

const string cNAME = "";
//const double	cACTVDEL = 0.0f;
//const double cCRRAD = 0.0f;
//const double cLIFETIME = 0.0f;
//const bool	cISRANDOMUNIFORM = true;
//const double cSTARTTIME = 0.0f;
//const double cENDTIME = 0.0f;


//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAnchorParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "TrafficSource"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CAnchorParseBlock::CAnchorParseBlock()
	: CSnoBlock()
{
	SetBlockName("Anchor");
} // end of CAnchorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAnchorParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CAnchorParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CAnchorParseBlock::CAnchorParseBlock(const CAnchorParseBlock& cCopy)
{
	*this = cCopy;
} // end of CAnchorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~TrafSrcParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CAnchorParseBlock::~CAnchorParseBlock() {}// end of CAnchorParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAnchorParseBlock
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
CAnchorParseBlock::CAnchorParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CAnchorParseBlock

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
CAnchorParseBlock&
CAnchorParseBlock::operator=(const CAnchorParseBlock& cRhs)
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
// Description: GetName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Name field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAnchorParseBlock::GetName(void) const
{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return cNAME;
} // end of GetName

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetPosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the Position field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CAnchorParseBlock::GetPosition(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint3D pos;
	if (GetField("Position", vals)) {
		if (vals.size() != 3) {
			TCountError e("Position", 3);
			throw e;
		}
		pVal = vals.begin();
		pos.m_x = pVal->GetFloatValue();
		pVal++;
		pos.m_y = pVal->GetFloatValue();
		pVal++;
		pos.m_z = pVal->GetFloatValue();
		pVal++;
	}
	return pos;
} // end of GetPosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDrawPosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the DrawPosition field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CAnchorParseBlock::GetDrawPosition(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint3D pos;
	if (GetField("DrawPosition", vals)) {
		if (vals.size() != 3) {
			TCountError e("DrawPosition", 3);
			throw e;
		}
		pVal = vals.begin();
		pos.m_x = pVal->GetFloatValue();
		pVal++;
		pos.m_y = pVal->GetFloatValue();
		pVal++;
		pos.m_z = pVal->GetFloatValue();
		pVal++;
	}
	return pos;
} // end of GetDrawPosition

//////////////////////////////////////////////////////////////////////////////
// Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	name - a string to which to set the Name field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAnchorParseBlock::SetName(const string& name)
{
	// Delete any "Name" fields
	ClearFields("Name");

	// Add new "Name" field.
	AddField("Name", name);

} // end of SetName

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetPosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	position - a CPoint3D to which to set the Position field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAnchorParseBlock::SetPosition(const CPoint3D& position)
{
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("Position");

	// Add new "Position" field.
	positionVec.push_back((double)position.m_x);
	positionVec.push_back((double)position.m_y);
	positionVec.push_back((double)position.m_z);

	AddField("Position", positionVec);

} // end of SetPosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDrawPosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	position - a CPoint3D to which to set the DrawPosition field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAnchorParseBlock::SetDrawPosition(const CPoint3D& position)
{
	vector<double> positionVec;
	// Delete any "DrawPosition" fields
	ClearFields("DrawPosition");

	// Add new "DrawPosition" field.
	positionVec.push_back((double)position.m_x);
	positionVec.push_back((double)position.m_y);
	positionVec.push_back((double)position.m_z);

	AddField("DrawPosition", positionVec);

} // end of SetDrawPositionn


