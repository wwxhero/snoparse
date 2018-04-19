/////////////////////////////////////////////////////////////////////////////
// 
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     September, 1998
//
// $Id: snovalue.cxx,v 1.6 2014/09/08 22:17:48 IOWA\dheitbri Exp $
//
// The implementation file for the scenario value class (CSnoValue), a 
// 	helper class to the scenario parse block.
//
//////////////////////////////////////////////////////////////////////////////
#include "snovalue.h"
#include <algorithm>
using namespace std;

//////////////////////////////////////////////////////////////////////////////
//	Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSnoValue
// 	The copy constructor uses the assignment operator to copy the parameter
// 	to the current instance.
//
// Remarks:
//
// Arguments: 
// 	cCopy - CSnoValue instance to copy
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSnoValue::CSnoValue(const CSnoValue& cCopy)
{
	*this = cCopy;
} // end of CSnoValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: operator=
// 	The assignment operator copies the contents of the parameter to the 
// 	current instance.
//
// Remarks:
//
// Arguments: 
// 	rhs - righthand side of the assignment
//
// Returns: A reference to the current instance to allow nested assignments.
//
//////////////////////////////////////////////////////////////////////////////
CSnoValue& 
CSnoValue::operator=(const CSnoValue &rhs)
{
	if ( &rhs != this ) {
		m_type = rhs.m_type;
		m_strValue = rhs.m_strValue;
		m_intValue = rhs.m_intValue;
		m_fltValue = rhs.m_fltValue;
	}
	return *this;
} // end of operator=


//////////////////////////////////////////////////////////////////////////////
//	Accessor functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetType
// 	Returns the type of the current CSnoValue instance
//
// Remarks: 
// 
// Arguments:
//
// Returns: the enumerated type value.
//
//////////////////////////////////////////////////////////////////////////////
CSnoValue::EType
CSnoValue::GetType(void) const
{
	return m_type;
} // end of GetType

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetIntValue
// 	Returns the integer value.
//
// Remarks: If the current CSnoValue is not of type integer, the default will
// 	be returned.
// 
// Arguments:
//
// Returns: a const reference to the integer value
//
//////////////////////////////////////////////////////////////////////////////
const int&
CSnoValue::GetIntValue(void) const
{
	return m_intValue;
} // end of GetIntValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFloatValue
// 	Returns the double value.
//
// Remarks: If the current CSnoValue is not of type double, the default will
// 	be returned.
// 
// Arguments:
//
// Returns: a const reference to the double value
//
//////////////////////////////////////////////////////////////////////////////
const double&
CSnoValue::GetFloatValue(void) const
{
	return m_fltValue;
} // end of GetFloatValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetStringValue
// 	Returns the string value.
//
// Remarks: If the current CSnoValue is not of type string, the default will
// 	be returned.
// 
// Arguments:
//
// Returns: a const reference to the string value
//
//////////////////////////////////////////////////////////////////////////////
const string&
CSnoValue::GetStringValue(void) const
{
	return m_strValue;
} // end of GetStringValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetStringRep
// 	Returns a string representing the stored value 
//
// Remarks: The actual contents of the string depend on the type of the value 
// 	but in all cases, a printable representation of the value value is 
// 	returned as a string.  The primary difference between this function and 
// 	the getStringValue function is that this function will return a string 
// 	representation of the value independent of the actual type of the string 
// 	whereas the getStringValue will return an empty string unless the value 
// 	type is string.  Another difference is that for string typed values, this 
// 	function will not enclose the string in quotes.
//
// Arguments:
//
// Returns: A string holding the contents of the stored value
//
//////////////////////////////////////////////////////////////////////////////
string 
CSnoValue::GetStringRep(void) const
{
	char   buf[64];
	string s;

	switch ( m_type ) {
		case eNONE: 
			s = "";
			break;
		case eINT: 
			sprintf_s(buf, "%d", m_intValue); 
			s = buf; 
			break;
		case eFLOAT: 
			sprintf_s(buf, "%.7E", m_fltValue); 
			s = buf; 
			break;
		case eSTRING: 
			s = "\""; 
			s+= m_strValue; 
			s+= "\"";
			break;
	}
	return s;
} // end of GetStringRep


//////////////////////////////////////////////////////////////////////////////
//	Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: Clear
// 	Sets the type to none
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void CSnoValue::Clear(void)
{
	m_type = eNONE;
} // end of Clear

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetValue
// 	Sets the value of the current CSnoValue to the parameter.
//
// Remarks: 
//
// Arguments:
// 	val	- Value to set 
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void 
CSnoValue::SetValue(int val)
{
	m_type = eINT;
	m_intValue = val;
} // end of SetValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetValue
// 	Sets the value of the current CSnoValue to the parameter.
//
// Remarks: 
//
// Arguments:
// 	val	- Value to set 
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void 
CSnoValue::SetValue(double val)
{
	m_type = eFLOAT;
	m_fltValue = (double)val;
} // end of SetValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetValue
// 	Sets the value of the current CSnoValue to the parameter.
//
// Remarks: 
//
// Arguments:
// 	val	- Value to set 
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void 
CSnoValue::SetValue(const string& val)
{
	m_type = eSTRING;
	m_strValue = val;
    std::replace( m_strValue.begin(), m_strValue.end(), '"', '\''); 
} // end of SetValue

