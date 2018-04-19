//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Omar Ahmad, Sunil Bulusu
// Date:	 June, 2001
//
// $Id: trafficdataparseblock.cxx,v 1.3 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
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
// Description: CTrafficDataParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "Ado" and the
//	default run mode is eREMOTE_CONTROL.
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafficDataParseBlock::CTrafficDataParseBlock()
	: CSnoBlock()
{
	SetBlockName("TrafficData");
} // end of CTrafficDataParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafficDataParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CTrafficDataParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafficDataParseBlock::CTrafficDataParseBlock(const CTrafficDataParseBlock& cCopy)
{
	*this = cCopy;
} // end of CTrafficDataParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~AdoParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafficDataParseBlock::~CTrafficDataParseBlock() {}// end of CTrafficDataParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafficDataParseBlock
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
CTrafficDataParseBlock::CTrafficDataParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CTrafficDataParseBlock

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
CTrafficDataParseBlock&
CTrafficDataParseBlock::operator=(const CTrafficDataParseBlock& cRhs)
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
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the LogAllObjs field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CTrafficDataParseBlock::GetLogAllObjs(void) const
{
	CSnoValue val;
	if (GetField("LogAllObjs", val))
		return ( val.GetIntValue() == 0 ? false : true );
	else
		return false;
} // end of GetLogAllObjs

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the LogObjName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CTrafficDataParseBlock::GetLogObjName(void) const
{
	CSnoValue val;
	if (GetField("GetLogObjName", val))
		return val.GetStringValue();
	else
		return "";
} // end of GetLogObjName

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the LogAccel field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CTrafficDataParseBlock::GetLogAccel(void) const
{
	CSnoValue val;
	if (GetField("LogAccel", val))
		return ( val.GetIntValue() == 0 ? false : true );
	else
		return false;
} // end of GetLogAccel

//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the AccelMin field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafficDataParseBlock::GetAccelMin(void) const
{
	CSnoValue val;
	if (GetField("AccelMin", val))
		return val.GetFloatValue();
	else
		return 0.0f;
} // end of GetAccelMin

//////////////////////////////////////////////////////////////////////////////
//
// Description:
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the AccelMax field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafficDataParseBlock::GetAccelMax(void) const
{
	CSnoValue val;
	if (GetField("AccelMax", val))
		return val.GetFloatValue();
	else
		return 0.0f;
} // end of GetAccelMax

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
//	 val - A boolean which indicates whether to log all objects.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafficDataParseBlock::SetLogAllObjs(bool val)
{
	// Delete any "LogAllObjs" fields
	ClearFields("LogAllObjs");

	// Add new "Name" field.
	AddField("LogAllObjs", val ? 1 : 0);

} // end of SetLogAllObjs

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
CTrafficDataParseBlock::SetLogObjName(const string& objName)
{
	// Delete any "LogObjName" fields
	ClearFields("LogObjName");

	// Add new "LogObjName" field.
	AddField("LogObjName", objName);

} // end of SetLogObjName

//////////////////////////////////////////////////////////////////////////////
//
// Description: 
//
// Remarks:
//
// Arguments:
//	 val - A boolean which indicates whether to log accelration.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafficDataParseBlock::SetLogAccel(bool val)
{
	// Delete any "LogAccel" fields
	ClearFields("LogAccel");

	// Add new "LogAccel" field.
	AddField("LogAccel", val ? 1 : 0);

} // end of SetLogAccel

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
CTrafficDataParseBlock::SetAccelMin(double val)
{
	// Delete any "AccelMin" fields
	ClearFields("AccelMin");

	// Add new "AccelMin" field.
	AddField("AccelMin", val);

} // end of SetAccelMin

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
CTrafficDataParseBlock::SetAccelMax(double val)
{
	// Delete any "AccelMax" fields
	ClearFields("AccelMax");

	// Add new "AccelMax" field.
	AddField("AccelMax", val);

} // end of SetAccelMax

