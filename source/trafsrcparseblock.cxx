//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: trafsrcparseblock.cxx,v 1.23 2015/05/21 19:48:49 IOWA\dheitbri Exp $
//
// The implementation for the trafsrc parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

const string cNAME = "";
const double	cACTVDEL = 0.0f;
const double cCRRAD = 0.0f;
const double cLIFETIME = 0.0f;
//const bool	cISRANDOMUNIFORM = true;
const double cSTARTTIME = 1.0f;
const double cENDTIME = 2.0f;
const CTrafSrcParseBlock::EDistribution cDISTRIBUTION = CTrafSrcParseBlock::eRANDOMUNIFORM;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafSrcParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "TrafficSource"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafSrcParseBlock::CTrafSrcParseBlock()
	: CSnoBlock()
{
	SetBlockName("TrafficSource");
} // end of CTrafSrcParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafSrcParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CTrafSrcParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafSrcParseBlock::CTrafSrcParseBlock(const CTrafSrcParseBlock& cCopy)
{
	*this = cCopy;
} // end of CTrafSrcParseBlock

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
CTrafSrcParseBlock::~CTrafSrcParseBlock() {}// end of CTrafSrcParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafSrcParseBlock
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
CTrafSrcParseBlock::CTrafSrcParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CTrafSrcParseBlock

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
CTrafSrcParseBlock&
CTrafSrcParseBlock::operator=(const CTrafSrcParseBlock& cRhs)
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
CTrafSrcParseBlock::GetName(void) const
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
CTrafSrcParseBlock::GetPosition(void) const
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
CTrafSrcParseBlock::GetDrawPosition(void) const
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
//
// Description: GetCrRad
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the CrRad field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafSrcParseBlock::GetCrRad(void) const
{
	CSnoValue val;
	if (GetField("CrRad", val))
		return val.GetFloatValue();
	else
		 return cCRRAD;
} // end of GetCrRad

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetActvDel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the ActvDel field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafSrcParseBlock::GetActvDel(void) const
{
	CSnoValue val;
	if (GetField("ActvDel", val))
		return val.GetFloatValue();
	else
		 return cACTVDEL;
} // end of GetActvDel

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetLifetime
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Lifetime field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTrafSrcParseBlock::GetLifetime(void) const
{
	CSnoValue val;
	if (GetField("Lifetime", val))
		return val.GetFloatValue();
	else
		 return cLIFETIME;
} // end of GetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: IsRandomUniform
//	DESCRIPTION
//
// Remarks: May be used to determine the type of traffic distribution the 
//	TrafficSource should use.  If a RandomUniform distribution was specfied, 
//	then the GetTimes() function will return 2 floats.  Otherwise, the 
//	Periodic distribution is specified, and GetTimes will return an 
//	indeterminate number of floats.
//
// Arguments:
//
// Returns: True if the current block contains a field named "RandomUniform", 
//	false otherwise.
//
//////////////////////////////////////////////////////////////////////////////

bool
CTrafSrcParseBlock::IsRandomUniform(void) const
{
	CSnoValue val;
	return GetField("RandomUniform", val);
} // end of IsRandomUniform

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTimes
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of double values for the times in the Random or Periodic 
// 	fields.
//
//////////////////////////////////////////////////////////////////////////////
vector<double>
CTrafSrcParseBlock::GetTimes(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> times;

	if (GetField("RandomUniform", vals)) {
		if (vals.size() != 2) {
			TCountError e("RandomUniform", 2);
			throw e;
		}		
		pVal = vals.begin();
		times.push_back(pVal->GetFloatValue());
		pVal++;
		times.push_back(pVal->GetFloatValue());
	}
	else if (GetField("Periodic", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) 
			times.push_back(pVal->GetFloatValue());
	}
	else {
		times.push_back( cSTARTTIME );
		times.push_back( cENDTIME );
	}
	return times;
} // end of GetTimes

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetWeights
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of TWeight values for the Weights field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CTrafSrcParseBlock::TWeight>
CTrafSrcParseBlock::GetWeights(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TWeight> weights;
	char* pCurrPos = NULL;
	if (GetField("Weights", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			
			string weightStr = pVal->GetStringValue();
			TWeight weight;

			char *pBuf = new char[strlen(weightStr.c_str())+1];
	    	char *pTokDel = " \t:";
			char *pTok;

			strcpy(pBuf, weightStr.c_str());
			pTok = strtok_s(pBuf, pTokDel,&pCurrPos);
			weight.name = pTok;
			pTok = strtok_s(NULL, pTokDel,&pCurrPos);
			weight.weight = atoi(pTok);

			weights.push_back(weight);
			delete [] pBuf;
		}
	}
	return weights;
} // end of GetWeights

CTrafSrcParseBlock::EDistribution CTrafSrcParseBlock::GetDistribution(void) const
{
	CSnoValue val;
	if (GetField("Distribution", val)) {
		return (EDistribution)val.GetIntValue();
	}
	else return cDISTRIBUTION;
}

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
CTrafSrcParseBlock::SetName(const string& name)
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
CTrafSrcParseBlock::SetPosition(const CPoint3D& position)
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
CTrafSrcParseBlock::SetDrawPosition(const CPoint3D& position)
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

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCrRad
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	crRad - a double to which to set the CrRad field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetCrRad(double crRad)
{
	// Delete any "CrRad" fields
	ClearFields("CrRad");

	// Add new "CrRad" field.
	if (cCRRAD != crRad)
		AddField("CrRad", crRad);

} // end of SetCrRad

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetActvDel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	actvDel - a double to which to set the ActvDel field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetActvDel(double actvDel)
{
	// Delete any "ActvDel" fields
	ClearFields("ActvDel");

	// Add new "ActvDel" field.
	if (cACTVDEL != actvDel)
		AddField("ActvDel", actvDel);

} // end of SetActvDel

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetLifetime
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	lifetime - a double to which to set the Lifetime field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetLifetime(double lifetime)
{
	// Delete any "Lifetime" fields
	ClearFields("Lifetime");

	// Add new "Lifetime" field.
	if (cLIFETIME != lifetime)
		AddField("Lifetime", lifetime);

} // end of SetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetRandomUniform
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	startTime - a double value to which to set the starting time of the 
//		RandomUniform field
//	endTime - a double value to which to set the ending time of the 
//		RandomUniform field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetRandomUniform(double startTime, double endTime)
{
	vector<double> times;
	// Delete out Periodic and RandomUniform fields
	ClearFields("Periodic");
	ClearFields("RandomUniform");
	
	// Add a new field
	times.push_back(startTime);
	times.push_back(endTime);

	AddField("RandomUniform", times);
} // end of SetRandomUniform

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetPeriodic
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
// 	times - a vector of double values to which to set the times for the
// 		Periodic field.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetPeriodic(const vector<double>& times)
{
	// Delete out Periodic and RandomUniform fields
	ClearFields("Periodic");
	ClearFields("RandomUniform");
	
	vector<double> timesT;
	timesT = times;
	// Add a new field
	if (cSTARTTIME != times[0] || cENDTIME != times[1]){
		AddField("Periodic", timesT);
	}
	
} // end of SetPeriodic
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetPeriodic
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
// 	none
//
// Returns: const vector<double>, a vector of the periodic times.
//
//////////////////////////////////////////////////////////////////////////////
vector<double>
CTrafSrcParseBlock::GetPeriodic(void) const
{
	// Delete out Periodic and RandomUniform fields
	//ClearFields("Periodic");
	//ClearFields("RandomUniform");
	vector<double> timesT;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;	
	// Add a new field
	GetField("Periodic",vals);
	for (unsigned int i =0; i < vals.size(); i++){
		timesT.push_back(vals.at(i).GetFloatValue());
	}
	return timesT;
	
} // end of SetPeriodic
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetWeights
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	weights - a vector of TWeight values to which to set the Weights field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafSrcParseBlock::SetWeights(const vector<TWeight>& weights)
{
	vector<TWeight>::const_iterator itr;
	vector<string> weightVec;

	// Delete any "Weights" fields
	ClearFields("Weights");

	if (!weights.empty()) {
		for (itr = weights.begin(); itr != weights.end(); itr++) {
	
			// Initialize the field value
			string weight = itr->name;
			char intWght[20];
			sprintf(intWght, ":%d", itr->weight);
			weight += intWght;
			weightVec.push_back(weight);
		}
		// Add field to the list
		AddField("Weights", weightVec);
	}
} // end of SetWeights
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRandomizePeriodicFlag
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	RandomizePeriodic flag, used to set if the periodic set should be randomized 
//when it is used
// Returns: bool
//
//////////////////////////////////////////////////////////////////////////////
bool CTrafSrcParseBlock::GetRandomizePeriodicFlag(void) const{
	CSnoValue val;
	GetField("RandomizePeriodic",val);
	return bool(val.GetIntValue()>0);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRandomizePeriodicFlag
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	RandomizePeriodic flag, used to set if the periodic set should be randomized 
//when it is used
// Returns: bool
//
//////////////////////////////////////////////////////////////////////////////
void CTrafSrcParseBlock::SetRandomizePeriodicFlag(bool flag){
	CSnoValue val;
	ClearFields("RandomizePeriodic");
	AddField("RandomizePeriodic",flag);
}
void CTrafSrcParseBlock::SetDistribution(CTrafSrcParseBlock::EDistribution val)
{
	// Delete any "Distribution" fields
	ClearFields("Distribution");

	// Add new "Distribution" field.
	if (cDISTRIBUTION != val)
		AddField("Distribution", val);
}

