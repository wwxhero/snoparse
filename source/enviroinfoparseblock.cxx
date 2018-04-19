//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: enviroinfoparseblock.cxx,v 1.8 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The implementation for the envroinfo parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnviroInfoParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "EnviroInfo"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnviroInfoParseBlock::CEnviroInfoParseBlock()
	: CSnoBlock()
{
	SetBlockName("EnviroInfo"); 
} // end of CEnviroInfoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnviroInfoParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CEnviroInfoParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnviroInfoParseBlock::CEnviroInfoParseBlock(const CEnviroInfoParseBlock& cCopy)
{
	*this = cCopy;
} // end of CEnviroInfoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~EnvroInfoParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CEnviroInfoParseBlock::~CEnviroInfoParseBlock() {}// end of CEnviroInfoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CEnviroInfoParseBlock
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
CEnviroInfoParseBlock::CEnviroInfoParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CEnviroInfoParseBlock

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
CEnviroInfoParseBlock&
CEnviroInfoParseBlock::operator=(const CEnviroInfoParseBlock& cRhs)
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
// Description: GetEnviroInfo
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A TEnviroInfo containing the environment type and parameter info.
//
//////////////////////////////////////////////////////////////////////////////
CEnviroInfoParseBlock::TEnviroInfo
CEnviroInfoParseBlock::GetEnviroInfo(void) const
{
	CSnoValue val;
	TEnviroInfo enviroInfo;

	// Get environment type
	if (GetField("EnviroType", val)) {
		strcpy(enviroInfo.type, val.GetStringValue().c_str());

		ConvertStringUpper(enviroInfo.type);
	}
	else {
		enviroInfo.type[0] = '\0';
		return enviroInfo;
	}

	
	if (!strcmp(enviroInfo.type, "LIGHTNING")) {
		if (GetField("Degree", val)) {
			strcpy(enviroInfo.info.Lightning.degree, 
				val.GetStringValue().c_str());
			ConvertStringUpper(enviroInfo.info.Lightning.degree);
		}
	}
	else if (!strcmp(enviroInfo.type, "VISIBILITY")) {
		if (GetField("Distance", val)) 
			enviroInfo.info.Visibility.dist = val.GetFloatValue();
	}
	else if (!strcmp(enviroInfo.type, "HAZE")) {
		if (GetField("Distance", val)) 
			enviroInfo.info.Haze.dist = val.GetFloatValue();
	}
	else if (!strcmp(enviroInfo.type, "FOG")) {
		if (GetField("Distance", val)) 
			enviroInfo.info.Fog.dist = val.GetFloatValue();
	}
	else if (!strcmp(enviroInfo.type, "CLOUDS")) {
		if (GetField("Altitude", val)) 
			enviroInfo.info.Clouds.altitude = val.GetFloatValue();
		if (GetField("Type", val)) 
			enviroInfo.info.Clouds.type = val.GetIntValue();
	}
	else if (!strcmp(enviroInfo.type, "SMOKE")) {
		if (GetField("Degree", val))
			enviroInfo.info.Smoke.degree = val.GetFloatValue();
	}
	else if (!strcmp(enviroInfo.type, "GLARE")) {
		if (GetField("Degree", val))
			enviroInfo.info.Glare.degree = val.GetFloatValue();
	}
	else if (!strcmp(enviroInfo.type, "SNOW")) {
		if (GetField("Degree", val)) {
			strcpy(enviroInfo.info.Snow.degree,
				val.GetStringValue().c_str());
			ConvertStringUpper(enviroInfo.info.Snow.degree);
		}
	}
	else if (!strcmp(enviroInfo.type, "RAIN")) {
		if (GetField("Degree", val)) {
			strcpy(enviroInfo.info.Rain.degree,
				val.GetStringValue().c_str());
			ConvertStringUpper(enviroInfo.info.Rain.degree);
		}
	}
	else if (!strcmp(enviroInfo.type, "WIND")) {
		if (GetField("Velocity", val)) 
			enviroInfo.info.Wind.vel = val.GetFloatValue();
		if (GetField("Gust", val)) 
			enviroInfo.info.Wind.gust = val.GetFloatValue();
		vector<CSnoValue> vals;
		if (GetField("Direction", vals)) {
			CSnoBlock::cTValueIterator pVal = vals.begin();
			enviroInfo.info.Wind.dirX = pVal->GetFloatValue();
			pVal++;
			enviroInfo.info.Wind.dirY = pVal->GetFloatValue();
		}
	}
	
	return enviroInfo;
	
} // end of GetEnviroInfo

//////////////////////////////////////////////////////////////////////////////
// Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetEnviroInfo
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	enviroInfo - A TEnviroInfo with its type and parameters initialized
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CEnviroInfoParseBlock::SetEnviroInfo(const TEnviroInfo& enviroInfo)
{
	// Delete out any previous fields
	ClearFields();

	// Add a new EnviroType field
	AddField("EnviroType", enviroInfo.type);
	
	// Based on the enviroInfo.type, add in the parameter fields
	if (!strcmp(enviroInfo.type, "LIGHTNING")) {
		AddField("Degree", enviroInfo.info.Lightning.degree);
	}
	else if (!strcmp(enviroInfo.type, "VISIBILITY")) {
		AddField("Distance", enviroInfo.info.Visibility.dist);
	}
	else if (!strcmp(enviroInfo.type, "HAZE")) {
		AddField("Distance", enviroInfo.info.Haze.dist);
	}
	else if (!strcmp(enviroInfo.type, "FOG")) {
		AddField("Distance", enviroInfo.info.Fog.dist);
	}
	else if (!strcmp(enviroInfo.type, "SMOKE")) {
		AddField("Degree", enviroInfo.info.Smoke.degree);
	}
	else if (!strcmp(enviroInfo.type, "CLOUDS")) {
		AddField("Altitude", enviroInfo.info.Clouds.altitude);
		AddField("Type", enviroInfo.info.Clouds.type);
	}
	else if (!strcmp(enviroInfo.type, "GLARE")) {
		AddField("Degree", enviroInfo.info.Glare.degree);
	}
	else if (!strcmp(enviroInfo.type, "SNOW")) {
		AddField("Degree", enviroInfo.info.Snow.degree);
	}
	else if (!strcmp(enviroInfo.type, "RAIN")) {
		AddField("Degree", enviroInfo.info.Rain.degree);
	}
	else if (!strcmp(enviroInfo.type, "WIND")) {
		AddField("Velocity", enviroInfo.info.Wind.vel);
		AddField("Gust", enviroInfo.info.Wind.gust);
		vector<double> dir;
		dir.push_back(enviroInfo.info.Wind.dirX);
		dir.push_back(enviroInfo.info.Wind.dirY);
		AddField("Direction", dir);
	}
	
} // end of SetEnviroInfo

//////////////////////////////////////////////////////////////////////////////
//
// Description: ConvertStringUpper
//	This function converts the string to uppercase 
//
// Remarks:	 
//
// Arguments:
//	 s - string to be converted
//
// Returns: 
//
//////////////////////////////////////////////////////////////////////////////
void
CEnviroInfoParseBlock::ConvertStringUpper(char* s)
{
    int diff = 'a' - 'A';
    for (; *s!= 0; s++){
        if ( (*s <= 'z') && (*s >= 'a') ){
            *s -= diff;
        }
    }
}

