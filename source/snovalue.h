/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     September, 1998
//
// $Id: snovalue.h,v 1.5 2013/12/03 20:33:38 IOWA\dheitbri Exp $
//
// The interface for the scenario value class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _SNO_VALUE_H
#define _SNO_VALUE_H	// {secret}

#include <string>
#include <vector>

#ifdef _WIN32
#include <iostream>
#include <stdlib.h>
#include <typeinfo.h>
#elif __sgi		// {secret}
#include <typeinfo>
#include <iostream.h>
#elif _PowerMAXOS	// {secret}
#include <iostream>
#endif			// elif _PowerMAXOS

//////////////////////////////////////////////////////////////////////////////
//
// This class represents a field in a scenario file block.  A field
// consists of a name and a list of typed values.  The name corresponds
// to the first label that appears on the line defining the field.  The
// values associated with the field correspond to the values specified
// after the field's label on the line. 
//
// Each field has a type represented by the CSnoValue::EType enumeration.
// Initially, a field is untyped but after adding the first value, the
// field takes on the type of that value.  From that point on, only
// similarly typed fields can be added.
//
// The class provides member functions to access the values associated with
// the field.  Two sets of functions are provided, the first one is
// to be used when the type of the field is known, and they returned
// values typed in C(++) built in types int, double and STL string.
// Another function returns a string representation of the value
// independent of its type.
//
//////////////////////////////////////////////////////////////////////////////
class CSnoValue {
	public:
		// Constructors, destructor, and assignment operator
		CSnoValue();
		CSnoValue(const CSnoValue &);
		~CSnoValue();
		CSnoValue &operator=(const CSnoValue &);

		// Types
		// This type indicates what type the CSnoValue is
		typedef enum { eNONE, eSTRING, eINT, eFLOAT } EType;

		// Accessors
		EType			GetType(void) const;
		const int&		GetIntValue(void) const;
		const double&	GetFloatValue(void) const;
		const std::string&	GetStringValue(void) const;
		std::string			GetStringRep(void) const;

		// Mutators
		void			Clear(void);

		void			SetValue(int);
		void			SetValue(double);
		void			SetValue(const std::string &);
		
	private:
		EType			m_type;			// what type is the value
		std::string 			m_strValue;		// string typed value
		int    			m_intValue;		// integer typed value
		double  			m_fltValue;		// double typed value

};	// end of CSnoValue

//////////////////////////////////////////////////////////////////////////////
//	Inline functions
//////////////////////////////////////////////////////////////////////////////

inline CSnoValue::CSnoValue() : m_type(eNONE),m_intValue(0),m_fltValue(0) {}

inline CSnoValue::~CSnoValue() {}

#endif	// SNO_VALUE_H

