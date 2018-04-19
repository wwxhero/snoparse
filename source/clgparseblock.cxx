//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: clgparseblock.cxx,v 1.14 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The implementation for the clg parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CClgParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "CLG"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CClgParseBlock::CClgParseBlock()
	: CSnoBlock() 
{
	SetBlockName("CLG");
} // end of CClgParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CClgParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CClgParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CClgParseBlock::CClgParseBlock(const CClgParseBlock& cCopy)
{
	*this = cCopy;
} // end of CClgParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~ClgParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CClgParseBlock::~CClgParseBlock() {}// end of CClgParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CClgParseBlock
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
CClgParseBlock::CClgParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CClgParseBlock

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
CClgParseBlock&
CClgParseBlock::operator=(const CClgParseBlock& cRhs)
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
// Description: GetClgTable
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A TClgTable value for the combination of the IntrsctnName, 
// 	Duration, LightName, and Pattern fields.
//
//////////////////////////////////////////////////////////////////////////////
CClgParseBlock::TClgTable
CClgParseBlock::GetClgTable(void) const
{
	CSnoValue val;
	vector<CSnoValue> vals;
	TClgTable clgTable;
	CSnoBlock::cTValueIterator pVal;
	
	if (GetField("IntrsctnName", val))
		clgTable.intrsctnName = val.GetStringValue();
	else
		clgTable.intrsctnName = "";

	if (GetField("Duration", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			double dur = pVal->GetFloatValue();
			clgTable.duration.push_back(dur);
		}
	}

	CSnoBlock::cTValueIterator pName, pPatt;
	vector<CSnoValue> nameVals, pattVals;
	if ( (GetField("LightName", nameVals)) &&
		 (GetField("Pattern", pattVals))) { 
	
		for (pName = nameVals.begin(), pPatt = pattVals.begin();
			 pName != nameVals.end();
			 pName++, pPatt++) {

			TClgRow    clgRow;
			clgRow.lightName = pName->GetStringValue();

			string pattern = pPatt->GetStringValue();
			while (!pattern.empty()) {
				clgRow.pattern.push_back(pattern);
				pPatt++;
				pattern = pPatt->GetStringValue();
			}
			
			clgTable.clgRows.push_back(clgRow);
		}
	}
	return clgTable;
} // end of GetClgTable

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetIntrsctnName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the IntrsctnName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CClgParseBlock::GetIntrsctnName(void) const
{
	CSnoValue val;
	if (GetField("IntrsctnName", val))
		return val.GetStringValue();
	else
		return "";
} // end of GetIntrsctnName
	
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDuration
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of double values for the Duration field.
//
//////////////////////////////////////////////////////////////////////////////
vector<double>
CClgParseBlock::GetDuration(void) const
{
	vector<CSnoValue> vals;
	vector<double> durs;
	CSnoBlock::cTValueIterator pVal;
	
	if (GetField("Duration", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++)
			durs.push_back(pVal->GetFloatValue());
	}
	return durs;
} // end of GetDuration


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetClgRows
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of TClgRow values created from the LightName and
//	Pattern fields.
//
//////////////////////////////////////////////////////////////////////////////
vector<CClgParseBlock::TClgRow>
CClgParseBlock::GetClgRows(void) const {

	CSnoBlock::cTValueIterator pName, pPatt;
	vector<CSnoValue> nameVals, pattVals;
	vector<TClgRow> rows;

	if ( (GetField("LightName", nameVals)) &&
		 (GetField("Pattern", pattVals))) { 
	
		for (pName = nameVals.begin(), pPatt = pattVals.begin();
			 pName != nameVals.end();
			 pName++, pPatt++) {

			TClgRow    clgRow;
			clgRow.lightName = pName->GetStringValue();

			string pattern = pPatt->GetStringValue();
			while (!pattern.empty()) {
				clgRow.pattern.push_back(pattern);
				pPatt++;
				pattern = pPatt->GetStringValue();
			}
			
			rows.push_back(clgRow);
		}
	}
	return rows;
} // end of GetClgRows


//////////////////////////////////////////////////////////////////////////////
// 	Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetClgTable
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	clgTable - A TClgTable instance with its fields initialized
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CClgParseBlock::SetClgTable(const TClgTable& clgTable)
{
	//	-- IntrsctnName -- 
	// Delete any "IntrsctnName" fields
	ClearFields("IntrsctnName");
	// Create, initialize, and add new field.
	AddField("IntrsctnName", clgTable.intrsctnName);

	// 	-- Duration -- 
	// Delete any "Duration" fields
	ClearFields("Duration");
	// Add new field.
	AddField("Duration", clgTable.duration);

	//	-- LightName and Pattern --
	// Delete out all previous LightName and Pattern fields.
	ClearFields("LightName");
	ClearFields("Pattern");

	vector<TClgRow>::const_iterator rItr;
	for (rItr = clgTable.clgRows.begin(); 
		 rItr != clgTable.clgRows.end(); rItr++) {

		// Add fields to list
		AddField("LightName", rItr->lightName);
	}
	for (rItr = clgTable.clgRows.begin(); 
		 rItr != clgTable.clgRows.end(); rItr++) {

		vector<string> tmp = rItr->pattern;
		tmp.push_back("");
		// Add fields to list
		AddField("Pattern", tmp);
	}

} // end of SetClgTable

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetIntrsctnName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	intrsctnName - a string to which to set the IntrsctnName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CClgParseBlock::SetIntrsctnName(const string& intrsctnName)
{
	//	-- IntrsctnName -- 
	// Delete any "IntrsctnName" fields
	ClearFields("IntrsctnName");

	// Add new "IntrsctnName" field.
	AddField("IntrsctnName", intrsctnName);

} // end of SetIntrsctnName

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDuration
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	duration - a double vector to which to set the Duration field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CClgParseBlock::SetDuration(const vector<double>& duration)
{
	// 	-- Duration -- 
	// Delete any "Duration" fields
	ClearFields("Duration");

	// Add new field.
	AddField("Duration", duration);

} // end of SetDuration

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetClgRows
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	clgRows - a TClgRow vector to which to set the LightName and Pattern fields
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CClgParseBlock::SetClgRows(const vector<TClgRow>& clgRows)
{
	//	-- LightName and Pattern --
	// Delete out all previous LightName and Pattern fields.
	ClearFields("LightName");
	ClearFields("Pattern");

	vector<TClgRow>::const_iterator rItr;
	for (rItr = clgRows.begin(); 
		 rItr != clgRows.end(); rItr++) {

		// Add fields to list
		AddField("LightName", rItr->lightName);
	}
	for (rItr = clgRows.begin(); 
		 rItr != clgRows.end(); rItr++) {

		vector<string> tmp = rItr->pattern;
		tmp.push_back("");
		// Add fields to list
		AddField("Pattern", tmp);
	}

} // end of SetClgRows

