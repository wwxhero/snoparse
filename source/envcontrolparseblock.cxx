//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: envcontrolparseblock.cxx,v 1.18 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The implementation for the envcontrol parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnvControlParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "EnvironmentController"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnvControlParseBlock::CEnvControlParseBlock()
	: CSnoBlock()
{
	SetBlockName("EnvironmentController"); 
} // end of CEnvControlParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnvControlParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CEnvControlParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnvControlParseBlock::CEnvControlParseBlock(const CEnvControlParseBlock& cCopy)
{
	*this = cCopy;
} // end of CEnvControlParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~EnvControlParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnvControlParseBlock::~CEnvControlParseBlock() {}// end of CEnvControlParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnvControlParseBlock
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
CEnvControlParseBlock::CEnvControlParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CEnvControlParseBlock

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
CEnvControlParseBlock&
CEnvControlParseBlock::operator=(const CEnvControlParseBlock& cRhs)
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
// Description: GetOrigin
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint2D value for the Origin field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint2D
CEnvControlParseBlock::GetOrigin(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint2D pos;
	if (GetField("Origin", vals)) {
		if (vals.size() != 2) {
			TCountError e("Origin", 2);
			throw e;
		}
		pVal = vals.begin();
		pos.m_x = pVal->GetFloatValue();
		pVal++;
		pos.m_y = pVal->GetFloatValue();
		pVal++;
	}
	return pos;
} // end of GetOrigin

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetArea
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of CPoint2D values for the Area field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CPoint2D>
CEnvControlParseBlock::GetArea(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<CPoint2D> area;
	CPoint2D pos;
	if (GetField("Area", vals)) {
		if (vals.size() % 2 != 0) {
			TCountError e("Area", 2);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			pos.m_x = pVal->GetFloatValue();
			pVal++;
			pos.m_y = pVal->GetFloatValue();
			area.push_back(pos);
		}
	}
	return area;
} // end of GetArea


//////////////////////////////////////////////////////////////////////////////
// Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOrigin
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	origin - a CPoint2D to which to set the Origin field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CEnvControlParseBlock::SetOrigin(const CPoint2D& origin)
{
	vector<double> originVec;
	// Delete any "Origin" fields
	ClearFields("Origin");

	// Add new "Origin" field.
	originVec.push_back((double)origin.m_x);
	originVec.push_back((double)origin.m_y);

	AddField("Origin", originVec);

} // end of SetOrigin

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetArea
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	areas - a CPoint2D vector to which to set the Area field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CEnvControlParseBlock::SetArea(const vector<CPoint2D>& areas)
{
	vector<CPoint2D>::const_iterator itr;
	vector<double> areasVec;

	// Delete any "Area" fields
	ClearFields("Area");

	// Add fields to the list
	for (itr = areas.begin(); itr != areas.end(); itr++) {
		areasVec.clear();
		areasVec.push_back((double)itr->m_x);
		areasVec.push_back((double)itr->m_y);

		AddField("Area", areasVec);
	}
} // end of SetArea

//////////////////////////////////////////////////////////////////////////////
//
// Description: IfGlobal
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: true if this environment is for global
//
//////////////////////////////////////////////////////////////////////////////
bool
CEnvControlParseBlock::IsGlobalEnv() const
{
	vector<CSnoValue> vals;
    CPoint2D pos;
    if (GetField("Origin", vals)) {
		return false;
	} else {
		return true;
	}
}
		

