//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: adoparseblock.cxx,v 1.52 2015/10/23 14:08:37 IOWA\dheitbri Exp $
//
// The implementation for the ado parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

const double cCRRAD = 0.0;
const double cACTVDEL = 0.0;
const double cLIFETIME = 0.0;
const int   cAUDIOSTATE = 0;
const int   cVISUALSTATE = 0;
const double cFOLLOWTIMEMIN = 1.0;
const double cFOLLOWTIMEMAX = 2.0;
const double cFOLLOWDISTMIN = -1.0;
const double cFOLLOWDISTMAX = -1.0;
const double cTTCTHRES1 = 3.0;
const double cTTCTHRES2 = 6.0;
const double cTTCTHRES3 = 40.0;
const double cENGTHRES = 400.0;
const CAdoParseBlock::EDistribution cSTDTOACCDELTYPE = CAdoParseBlock::eFIXED;
const double cSTDTOACCDELP1 = 1.0;
const double cSTDTOACCDELP2 = 0.0;
const double cSTDTOACCDELFIXEDP1 = 1.0;
const double cSTDTOACCDELFIXEDP2 = 0.0;
const double cSTDTOACCDELUNIFORMP1 = 0.9;
const double cSTDTOACCDELUNIFORMP2 = 1.1;
const double cSTDTOACCDELNORMALP1 = 1.0;
const double cSTDTOACCDELNORMALP2 = 0.1;
const CAdoParseBlock::EDistribution cSTDTODECDELTYPE = CAdoParseBlock::eFIXED;
const double cSTDTODECDELP1 = 0.9;
const double cSTDTODECDELP2 = 0.0;
const double cSTDTODECDELFIXEDP1 = 1.0;
const double cSTDTODECDELFIXEDP2 = 0.0;
const double cSTDTODECDELUNIFORMP1 = 0.8;
const double cSTDTODECDELUNIFORMP2 = 1.0;
const double cSTDTODECDELNORMALP1 = 0.9;
const double cSTDTODECDELNORMALP2 = 0.1;
const CAdoParseBlock::EDistribution cDECTOACCDELTYPE = CAdoParseBlock::eFIXED;
const double cDECTOACCDELP1 = 1.25;
const double cDECTOACCDELP2 = 0.0;
const double cDECTOACCDELFIXEDP1 = 1.25;
const double cDECTOACCDELFIXEDP2 = 0.0;
const double cDECTOACCDELUNIFORMP1 = 1.15;
const double cDECTOACCDELUNIFORMP2 = 1.35;
const double cDECTOACCDELNORMALP1 = 1.25;
const double cDECTOACCDELNORMALP2 = 0.1;
const CAdoParseBlock::EDistribution cSTPTOACCDELTYPE = CAdoParseBlock::eFIXED;
const double cSTPTOACCDELP1 = 1.25;
const double cSTPTOACCDELP2 = 0.0;
const double cSTPTOACCDELFIXEDP1 = 1.25;
const double cSTPTOACCDELFIXEDP2 = 0.0;
const double cSTPTOACCDELUNIFORMP1 = 1.15;
const double cSTPTOACCDELUNIFORMP2 = 1.35;
const double cSTPTOACCDELNORMALP1 = 1.25;
const double cSTPTOACCDELNORMALP2 = 0.1;

const double cNORMDISTKP = 0.6;
const double cNORMDISTKI = 0.0;
const double cNORMDISTKD = -0.08;
const double cNORMVELKP = 3.1;
const double cNORMVEL2KP = 0.7;
const double cOVSPEEDCLIP = 1.2;
const double cOVSPEEDRNG = 100.0;
const double cNORMACCELCLIP = 2.3;
const double cNORMDECELCLIP = -4.0;
const double cBUMPSTOPDIST = 7.0;
const double cAPPDECRATE = -4.0;
const double cMINENGTIME = 1.5;
const double cEMERGDISTKP = 0.95;
const double cEMERGDISTKI = 0.0;
const double cEMERGDISTKD = 0.0;
const double cEMERGVELKP = 1.5;
const double cEMERGVELKI = -1.1;
const double cEMERGVELKD = 0.0;
const double cEMERGACLKP = 0.0;
const double cEMERGDECCLIP = -11.0;
const double cMGDISTKP = 6.0;
const double cMGDISTKI = 0.0;
const double cMGDISTKD = -0.08;
const double cMGVELKP = 5.0;
const double cMGMAXACC = 10.0;
const double cMGMAXDEC = -10.0;

const CAdoParseBlock::ELcvModel cLCVMODEL = CAdoParseBlock::eRAMPS;
const double cLCVRISETIME1 = 2.5;
const double cLCVRISETIME2 = 6.0;
const double cLCVFALLTIME1 = 1.5;
const double cLCVFALLTIME2 = 2.0;
const double cLCVRAMPAMPL1 = 0.1;
const double cLCVRAMPAMPL2 = 0.5;
const double cLCVSTABLETIME1 = 2.0;
const double cLCVSTABLETIME2 = 4.0;

const double cLCVBIAS1 = -0.3;
const double cLCVBIAS2 = 0.3;
const double cLCVSINAMPL1 = 0.5;
const double cLCVSINAMPL2 = 0.5;
const double cLCVFREQ1 = 0.03;
const double cLCVFREQ2 = 0.05;
const double cLCVPHASE1 = 0.0;
const double cLCVPHASE2 = 0.1;

const double cREEVALINTERV1 = 20.0;
const double cREEVALINTERV2 = 40.0;
const string cEXPRESSION = "";
const bool cENABLE = true;
const bool cAUTODISABLE = true;

const double	cINITVEL = 0.0;
const double cREFRESHTIME = 45.0;
const CAdoParseBlock::EDistribution cVELCTRLDISTTYPE = CAdoParseBlock::eFIXED;
const double cVELCTRLDISTFIXEDP1 = 60.0;
const double cVELCTRLDISTFIXEDP2 = -1.0;
const double cVELCTRLDISTUNIFORMP1 = 50.0;
const double cVELCTRLDISTUNIFORMP2 = 70.0;
const double cVELCTRLDISTNORMALP1 = 65.0;
const double cVELCTRLDISTNORMALP2 = 10.0;
const double cVELCTRLDISTP1 = 60.0;
const double cVELCTRLDISTP2 = -1.0;
const int    cCOLORINDEX = 0;

const bool cRANDOMIZE = true;
const double cSIGNALTIME = 1.0;
const double cSIGNALTIMEMIN = 0.0;
const double cSIGNALTIMEMAX = 2.0;
const double cURGENCY = 0.5;
const double cSTEERINGFORCE = 1.0;
const double cLaneChangeInitDelay = 1.0;
const double cFwdDistThresMIN = 50.0;
const double cFwdDistThresMAX = 150.0; 
const double cFwdDistThresVal = 100.0;
const double cBackDistThresMIN = 50.0;
const double cBackDistThresMAX = 150.0;
const double cBackDistThresVal = 100.0;
const double cFwdTimeThresMIN = 1.0;
const double cFwdTimeThresMAX = 3.0;
const double cFwdTimeThresVal = 2.0;
const double cBackTimeThresMIN = 1.0;
const double cBackTimeThresMAX = 3.0;
const double cBackTimeThresVal = 2.0;
const double cDistFromRandMIN = 400.0;
const double cDistFromRandMAX = 800.0;	
const double cDistFromVal = 600.0;
const double cTimeToMIN = 20.0;
const double cTimeToMAX = 40.0;
const double cTimeToVal = 30.0;
const bool   cAvoidTurning = true;

const bool   cCreateRelative = false;
const bool   cCreateRelLatInFeet = true;
//const bool   cCreateLatCentered = true;
const string cCreateRelativeObjName = "ExternalDriver";
const double cCreateRelativeLateral = 0.0;
const double cCreateRelativeLongitudinal = 100.0;


//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAdoParseBlock
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
CAdoParseBlock::CAdoParseBlock()
	: CSnoBlock()
{
	SetBlockName("Ado");
	AddField("RunMode", "eREMOTE_CONTROL");
} // end of CAdoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAdoParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CAdoParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CAdoParseBlock::CAdoParseBlock(const CAdoParseBlock& cCopy)
{
	*this = cCopy;
} // end of CAdoParseBlock

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
CAdoParseBlock::~CAdoParseBlock() {}// end of CAdoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CAdoParseBlock
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
CAdoParseBlock::CAdoParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CAdoParseBlock

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
CAdoParseBlock&
CAdoParseBlock::operator=(const CAdoParseBlock& cRhs)
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
CAdoParseBlock::GetName(void) const
{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetName

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
CAdoParseBlock::GetCrRad(void) const
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
CAdoParseBlock::GetActvDel(void) const
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
CAdoParseBlock::GetLifetime(void) const
{
	CSnoValue val;
	if (GetField("Lifetime", val))
		return val.GetFloatValue();
	else
		 return cLIFETIME;
} // end of GetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetSolName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the SolName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetSolName(void) const
{
	CSnoValue val;
	if (GetField("SolName", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetSolName

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRandomSol
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the RandomSol field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CAdoParseBlock::GetRandomSol(void) const
{
	CSnoValue val;
	if (GetField("RandomSol", val))
		return (val.GetIntValue() == 0 ? false : true );
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the Path field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CAdoParseBlock::GetPath(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> path;
	if (GetField("Path", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			path.push_back(pVal->GetStringValue());
		}
	}
	return path;
} // end of GetPath

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetAudioState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the AudioState field.
//
//////////////////////////////////////////////////////////////////////////////
int
CAdoParseBlock::GetAudioState(void) const
{
	CSnoValue val;
	if (GetField("AudioState", val))
		return val.GetIntValue();
	else
		 return cAUDIOSTATE;
} // end of GetAudioState

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVisualState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the VisualState field.
//
//////////////////////////////////////////////////////////////////////////////
int
CAdoParseBlock::GetVisualState(void) const
{
	CSnoValue val;
	if (GetField("VisualState", val))
		return val.GetIntValue();
	else
		 return cVISUALSTATE;
} // end of GetVisualState
/////////////////////////////////////////////////////////////////////////////
///\brief
///		Does the ADO need to control the break lights based on accel ?
///////////////////////////////////////////////////////////////////////////
bool		
CAdoParseBlock::GetAutoControlBrakeLight(void) const{
	CSnoValue val;
	if (GetField("AutoControlBreakLights", val))
		return val.GetIntValue()>0?true:false;
	else
		 return false;

}
///////////////////////////////////////////////////////////////////////////////
///\brief
///		Does the ADO need to control the head lights based on time of day ?
//////////////////////////////////////////////////////////////////////////////
bool			
CAdoParseBlock::GetAutoControlHeadLight(void) const{

	CSnoValue val;
	if (GetField("AutoControlHeadLights", val))
		return val.GetIntValue()>0?true:false;
	else
		 return false;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetColorIndex
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the ColorIndex field.
//
//////////////////////////////////////////////////////////////////////////////
int
CAdoParseBlock::GetColorIndex(void) const
{
	CSnoValue val;
	if (GetField("ColorIndex", val))
		return val.GetIntValue();
	else
		return cCOLORINDEX;
} // end of GetColorIndex

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRoadPos
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the RoadPos field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetRoadPos(void) const
{
	CSnoValue val;
	if (GetField("RoadPos", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetRoadPos


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDynModel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the DynModel field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetDynModel(void) const
{
	CSnoValue val;
	if (GetField("DynModel", val))
		return val.GetStringValue();
	else
		return "";
} // end of GetDynModel

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRunMode
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the RunMode field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetRunMode(void) const
{
	CSnoValue val;
	if (GetField("RunMode", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetRunMode

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetLogFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the GetLogFile field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetLogFile(void) const
{
	CSnoValue val;
	if (GetField("LogFile", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetLogFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCmdFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CmdFile field.
//
//////////////////////////////////////////////////////////////////////////////
string
CAdoParseBlock::GetCmdFile(void) const
{
	CSnoValue val;
	if (GetField("CmdFile", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetCmdFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTargetPoint
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the TargetPoint field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CAdoParseBlock::GetOffroadPoint(void) const
{
	vector<CSnoValue> vals;
	CPoint3D point;
	if (GetField("OffroadPoint", vals)) {
		if (vals.size() != 3) {
			TCountError e("OffroadPoint", 3);
			throw e;
		}
		CSnoBlock::cTValueIterator pVal = vals.begin();
		point.m_x = pVal->GetFloatValue();
		pVal++;
		point.m_y = pVal->GetFloatValue();
		pVal++;
		point.m_z = pVal->GetFloatValue();
		return point;
	}

	return point;
} // end of GetTargetPoint


//////////////////////////////////////////////////////////////////////////////
//
// Description: IsAdoOnRoad
//				
//
// Remarks:		
//
// Arguments: 
//
// Returns:		bool
//
//////////////////////////////////////////////////////////////////////////////
bool
CAdoParseBlock::IsAdoOnRoad(void) const
{
	vector<CSnoValue> vals;
	if (GetField("OffroadPoint", vals)) return false;
	else return true;
}

double CAdoParseBlock::GetFollowTimeMin(void) const
{
	CSnoValue val;
	if (GetField("FollowTimeMin", val)) {
		return val.GetFloatValue();
	}
	else return cFOLLOWTIMEMIN;
}

double CAdoParseBlock::GetFollowTimeMax(void) const
{
	CSnoValue val;
	if (GetField("FollowTimeMax", val)) {
		return val.GetFloatValue();
	}
	else return cFOLLOWTIMEMAX;
}

double CAdoParseBlock::GetFollowDistMin(void) const
{
	CSnoValue val;
	if (GetField("FollowDistMin", val)) {
		return val.GetFloatValue();
	}
	else return cFOLLOWDISTMIN;
}

double CAdoParseBlock::GetFollowDistMax(void) const
{
	CSnoValue val;
	if (GetField("FollowDistMax", val)) {
		return val.GetFloatValue();
	}
	else return cFOLLOWDISTMAX;
}

bool CAdoParseBlock::IsFollowTime(void) const
{
	CSnoValue val;
	if (GetField("FollowDistMin", val)) return false;
	else return true;
}


double CAdoParseBlock::GetTtcThres1(void) const
{
	CSnoValue val;
	if (GetField("TtcThres1", val)) {
		return val.GetFloatValue();
	}
	else return cTTCTHRES1;
}


double CAdoParseBlock::GetTtcThres2(void) const
{
	CSnoValue val;
	if (GetField("TtcThres2", val)) {
		return val.GetFloatValue();
	}
	else return cTTCTHRES2;
}

double CAdoParseBlock::GetTtcThres3(void) const
{
	CSnoValue val;
	if (GetField("TtcThres3", val)) {
		return val.GetFloatValue();
	}
	else return cTTCTHRES3;
}

double CAdoParseBlock::GetEngThres(void) const
{
	CSnoValue val;
	if (GetField("EngThres", val)) {
		return val.GetFloatValue();
	}
	else return cENGTHRES;
}

bool CAdoParseBlock::GetUseReaDel(void) const
{
	CSnoValue val;
	if (GetField("UseReaDel", val)) {
		return val.GetIntValue() != 0;
	}
	else return true;
}

CAdoParseBlock::CDelay CAdoParseBlock::GetStdToAccDel(void) const
{
	CDelay delay;
	CSnoValue val;
	if (GetField("StdToAccType", val)) {
		delay.m_type = (EDistribution)val.GetIntValue();
		switch (delay.m_type) {
		case eFIXED:
			if (GetField("StdToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTOACCDELFIXEDP1;
			delay.m_param2 = cSTDTOACCDELFIXEDP2;
			break;
		case eUNIFORM:
			if (GetField("StdToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTOACCDELUNIFORMP1;
			if (GetField("StdToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTDTOACCDELUNIFORMP2;
			break;
		case eNORMAL:
			if (GetField("StdToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTOACCDELNORMALP1;
			if (GetField("StdToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTDTOACCDELNORMALP2;
			break;
		}
	}
	else {
		delay.m_type = cSTDTOACCDELTYPE;
		delay.m_param1 = cSTDTOACCDELP1;
		delay.m_param2 = cSTDTOACCDELP2;
	}
	
	return delay;
}

CAdoParseBlock::CDelay CAdoParseBlock::GetStdToDecDel(void) const
{
	CDelay delay;
	CSnoValue val;
	if (GetField("StdToDecType", val)) {
		delay.m_type = (EDistribution)val.GetIntValue();
		switch (delay.m_type) {
		case eFIXED:
			if (GetField("StdToDecVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTODECDELFIXEDP1;
			delay.m_param2 = cSTDTODECDELFIXEDP2;
			break;
		case eUNIFORM:
			if (GetField("StdToDecVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTODECDELUNIFORMP1;
			if (GetField("StdToDecVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTDTODECDELUNIFORMP2;
			break;
		case eNORMAL:
			if (GetField("StdToDecVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTDTODECDELNORMALP1;
			if (GetField("StdToDecVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTDTODECDELNORMALP2;
			break;
		}
	}
	else {
		delay.m_type = cSTDTODECDELTYPE;
		delay.m_param1 = cSTDTODECDELP1;
		delay.m_param2 = cSTDTODECDELP2;
	}
	
	return delay;
}

CAdoParseBlock::CDelay CAdoParseBlock::GetDecToAccDel(void) const
{
	CDelay delay;
	CSnoValue val;
	if (GetField("DecToAccType", val)) {
		delay.m_type = (EDistribution)val.GetIntValue();
		switch (delay.m_type) {
		case eFIXED:
			if (GetField("DecToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cDECTOACCDELFIXEDP1;
			delay.m_param2 = cDECTOACCDELFIXEDP2;
			break;
		case eUNIFORM:
			if (GetField("DecToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cDECTOACCDELUNIFORMP1;
			if (GetField("DecToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cDECTOACCDELUNIFORMP2;
			break;
		case eNORMAL:
			if (GetField("DecToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cDECTOACCDELNORMALP1;
			if (GetField("DecToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cDECTOACCDELNORMALP2;
			break;
		}
	}
	else {
		delay.m_type = cDECTOACCDELTYPE;
		delay.m_param1 = cDECTOACCDELP1;
		delay.m_param2 = cDECTOACCDELP2;
	}
	
	return delay;
}

CAdoParseBlock::CDelay CAdoParseBlock::GetStpToAccDel(void) const
{
	CDelay delay;
	CSnoValue val;
	if (GetField("StpToAccType", val)) {
		delay.m_type = (EDistribution)val.GetIntValue();
		switch (delay.m_type) {
		case eFIXED:
			if (GetField("StpToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTPTOACCDELFIXEDP1;
			delay.m_param2 = cSTPTOACCDELFIXEDP2;
			break;
		case eUNIFORM:
			if (GetField("StpToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTPTOACCDELUNIFORMP1;
			if (GetField("StpToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTPTOACCDELUNIFORMP2;
			break;
		case eNORMAL:
			if (GetField("StpToAccVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cSTPTOACCDELNORMALP1;
			if (GetField("StpToAccVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cSTPTOACCDELNORMALP2;
			break;
		}
	}
	else {
		delay.m_type = cSTPTOACCDELTYPE;
		delay.m_param1 = cSTPTOACCDELP1;
		delay.m_param2 = cSTPTOACCDELP2;
	}
	
	return delay;
}

double CAdoParseBlock::GetNormDistKp(void) const
{
	CSnoValue val;
	if (GetField("NormDistKp", val)) {
		return val.GetFloatValue();
	}
	else return cNORMDISTKP;
}

double CAdoParseBlock::GetNormDistKi(void) const
{
	CSnoValue val;
	if (GetField("NormDistKi", val)) {
		return val.GetFloatValue();
	}
	else return cNORMDISTKI;
}

double CAdoParseBlock::GetNormDistKd(void) const
{
	CSnoValue val;
	if (GetField("NormDistKd", val)) {
		return val.GetFloatValue();
	}
	else return cNORMDISTKD;
}

double CAdoParseBlock::GetNormVelKp(void) const
{
	CSnoValue val;
	if (GetField("NormVelKp", val)) {
		return val.GetFloatValue();
	}
	else return cNORMVELKP;
}

double CAdoParseBlock::GetNormVel2Kp(void) const
{
	CSnoValue val;
	if (GetField("NormVel2Kp", val)) {
		return val.GetFloatValue();
	}
	else return cNORMVEL2KP;
}

double CAdoParseBlock::GetOvSpeedClip(void) const
{
	CSnoValue val;
	if (GetField("OvSpeedClip", val)) {
		return val.GetFloatValue();
	}
	else return cOVSPEEDCLIP;
}

double CAdoParseBlock::GetOvSpeedRng(void) const
{
	CSnoValue val;
	if (GetField("OvSpeedRng", val)) {
		return val.GetFloatValue();
	}
	else return cOVSPEEDRNG;
}

double CAdoParseBlock::GetNormAccelClip(void) const
{
	CSnoValue val;
	if (GetField("NormAccelClip", val)) {
		return val.GetFloatValue();
	}
	else return cNORMACCELCLIP;
}

double CAdoParseBlock::GetNormDecelClip(void) const
{
	CSnoValue val;
	if (GetField("NormDecelClip", val)) {
		return val.GetFloatValue();
	}
	else return cNORMDECELCLIP;
}

double CAdoParseBlock::GetBumpStopDist(void) const
{
	CSnoValue val;
	if (GetField("BumpStopDist", val)) {
		return val.GetFloatValue();
	}
	else return cBUMPSTOPDIST;
}

double CAdoParseBlock::GetAppDecRate(void) const
{
	CSnoValue val;
	if (GetField("AppDecRate", val)) {
		return val.GetFloatValue();
	}
	else return cAPPDECRATE;
}

bool CAdoParseBlock::GetAccel2Catch(void) const
{
	CSnoValue val;
	if (GetField("Accel2Catch", val)) {
		return val.GetIntValue() != 0;
	}
	else return false;
}

double CAdoParseBlock::GetMinEngTime(void) const
{
	CSnoValue val;
	if (GetField("MinEngTime", val)) {
		return val.GetFloatValue();
	}
	else return cMINENGTIME;
}

double CAdoParseBlock::GetEmergDistKp(void) const
{
	CSnoValue val;
	if (GetField("EmergDistKp", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGDISTKP;
}

double CAdoParseBlock::GetEmergDistKi(void) const
{
	CSnoValue val;
	if (GetField("EmergDistKi", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGDISTKI;
}

double CAdoParseBlock::GetEmergDistKd(void) const
{
	CSnoValue val;
	if (GetField("EmergDistKd", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGDISTKD;
}

double CAdoParseBlock::GetEmergVelKp(void) const
{
	CSnoValue val;
	if (GetField("EmergVelKp", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGVELKP;
}

double CAdoParseBlock::GetEmergVelKi(void) const
{
	CSnoValue val;
	if (GetField("EmergVelKi", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGVELKI;
}

double CAdoParseBlock::GetEmergVelKd(void) const
{
	CSnoValue val;
	if (GetField("EmergVelKd", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGVELKD;
}

double CAdoParseBlock::GetEmergAclKp(void) const
{
	CSnoValue val;
	if (GetField("EmergAclKp", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGACLKP;
}

double CAdoParseBlock::GetEmergDecClip(void) const
{
	CSnoValue val;
	if (GetField("EmergDecClip", val)) {
		return val.GetFloatValue();
	}
	else return cEMERGDECCLIP;
}

double CAdoParseBlock::GetMainGapDistKp(void) const
{
	CSnoValue val;
	if (GetField("MgDistKp", val)) {
		return val.GetFloatValue();
	}
	else return cMGDISTKP;
}

double CAdoParseBlock::GetMainGapDistKi(void) const
{
	CSnoValue val;
	if (GetField("MgDistKi", val)) {
		return val.GetFloatValue();
	}
	else return cMGDISTKI;
}

double CAdoParseBlock::GetMainGapDistKd(void) const
{
	CSnoValue val;
	if (GetField("MgDistKd", val)) {
		return val.GetFloatValue();
	}
	else return cMGDISTKD;
}

double CAdoParseBlock::GetMainGapVelKp(void) const
{
	CSnoValue val;
	if (GetField("MgVelKp", val)) {
		return val.GetFloatValue();
	}
	else return cMGVELKP;
}

double CAdoParseBlock::GetMainGapMaxAcc(void) const
{
	CSnoValue val;
	if (GetField("MgMaxAcc", val)) {
		return val.GetFloatValue();
	}
	else return cMGMAXACC;
}

double CAdoParseBlock::GetMainGapMaxDec(void) const
{
	CSnoValue val;
	if (GetField("MgMaxDec", val)) {
		return val.GetFloatValue();
	}
	else return cMGMAXDEC;
}

CAdoParseBlock::ELcvModel CAdoParseBlock::GetLcvModel(void) const
{
	CSnoValue val;
	if (GetField("LcvMod", val)) {
		return (ELcvModel)val.GetIntValue();
	}
	else return cLCVMODEL;
}

vector<double> CAdoParseBlock::GetLcvRiseTime(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvRise", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVRISETIME1 );
		retVal.push_back( cLCVRISETIME2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvFallTime(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvFall", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVFALLTIME1 );
		retVal.push_back( cLCVFALLTIME2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvRampsAmplitude(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvRAmpl", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVRAMPAMPL1 );
		retVal.push_back( cLCVRAMPAMPL2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvStableTime(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvStab", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVSTABLETIME1 );
		retVal.push_back( cLCVSTABLETIME2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvBias(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvBias", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVBIAS1 );
		retVal.push_back( cLCVBIAS2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvSinAmplitude(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvSAmpl", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVSINAMPL1 );
		retVal.push_back( cLCVSINAMPL2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvFrequency(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvFreq", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVFREQ1 );
		retVal.push_back( cLCVFREQ2 );
	}
	return retVal;
}

vector<double> CAdoParseBlock::GetLcvPhase(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvPhase", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cLCVPHASE1 );
		retVal.push_back( cLCVPHASE2 );
	}
	return retVal;
}

string CAdoParseBlock::GetLcvExpression(void) const
{
	CSnoValue val;
	if (GetField("LcvExpr", val)) {
		return val.GetStringValue();
	}
	else return cEXPRESSION;
}

vector<double> CAdoParseBlock::GetLcvReevalInterv(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("LcvReevInt", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back(pVal->GetFloatValue());
		}
	}
	else {
		retVal.push_back( cREEVALINTERV1 );
		retVal.push_back( cREEVALINTERV2 );
	}
	return retVal;
}

bool CAdoParseBlock::GetLcvEnable(void) const
{
	CSnoValue val;
	if (GetField("LcvEnab", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetLcvAutoDisable(void) const
{
	CSnoValue val;
	if (GetField("LcvAutoDis", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cAUTODISABLE;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInitVel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the InitVel field.
//
//////////////////////////////////////////////////////////////////////////////
double
CAdoParseBlock::GetVelCtrlInitVel(void) const
{
	CSnoValue val;
	if (GetField("InitVel", val))
		return val.GetFloatValue();
	else if (GetField("VelCtrlInitVel", val))
		return val.GetFloatValue();
	else
		return cINITVEL;
} // end of GetInitVel

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInitVel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the InitVel field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CAdoParseBlock::GetVelCtrlInitMatchOvVel(void) const
{
	CSnoValue val;
	if (GetField("VelCtrlInitMatchOvVel", val))
		return val.GetIntValue()>0;
	else
		return false;
} // end of GetInitVel
double CAdoParseBlock::GetVelCtrlRefreshTime(void) const
{
	CSnoValue val;
	if (GetField("VelCtrlRefreshTime", val)) {
		return val.GetFloatValue();
	}
	else return cREFRESHTIME;
}
//////////////////////////////////////////////////////////////////////////
///\brief
///     Gets if the ADO should follow the Speed Limit by default
///\return  true -follow the speed limit (defualt)
/////////////////////////////////////////////////////////////////////////
bool 
CAdoParseBlock::GetVelCtrlFollowSpeedLimit(void) const
{
	CSnoValue val;
	if (GetField("VelCtrlFollowSpeedLimit", val)) {
        return val.GetIntValue() > 0;
	}
	else return false;
}

CAdoParseBlock::CDelay CAdoParseBlock::GetVelCtrlDistribution(void) const
{
	CDelay delay;
	CSnoValue val;
	if (GetField("VelCtrlDistType", val)) {
		delay.m_type = (EDistribution)val.GetIntValue();
		switch (delay.m_type) {
		case eFIXED:
			if (GetField("VelCtrlDistVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cVELCTRLDISTFIXEDP1;
			delay.m_param2 = cVELCTRLDISTFIXEDP2;
			break;
		case eUNIFORM:
			if (GetField("VelCtrlDistVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cVELCTRLDISTUNIFORMP1;
			if (GetField("VelCtrlDistVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cVELCTRLDISTUNIFORMP2;
			break;
		case eNORMAL:
			if (GetField("VelCtrlDistVal1", val)) delay.m_param1 = val.GetFloatValue();
			else delay.m_param1 = cVELCTRLDISTNORMALP1;
			if (GetField("VelCtrlDistVal2", val)) delay.m_param2 = val.GetFloatValue();
			else delay.m_param2 = cVELCTRLDISTNORMALP2;
			break;
		}
	}
	else {
		delay.m_type = cVELCTRLDISTTYPE;
		delay.m_param1 = cVELCTRLDISTP1;
		delay.m_param2 = cVELCTRLDISTP2;
	}
	
	return delay;
}

//CAdoParseBlock::ERandomize CAdoParseBlock::GetRandomize(void) const
bool CAdoParseBlock::GetRandomize(void) const
{
	CSnoValue val;
	if (GetField("Randomize", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cRANDOMIZE;
}

double CAdoParseBlock::GetSignalTime(void) const
{
	CSnoValue val;
	if (GetField("SignalTime", val)) {
		return val.GetFloatValue();
	}
	else return cSIGNALTIME;
}

vector<double> CAdoParseBlock::GetRandomizeSignalTime(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("RandomizeSignalTime", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cSIGNALTIMEMIN );
		retVal.push_back( cSIGNALTIMEMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetUrgency(void) const
{
	CSnoValue val;
	if (GetField("Urgency", val)) {
		return val.GetFloatValue();
	}
	else return cURGENCY;
}

double CAdoParseBlock::GetSteeringForce(void) const
{
	CSnoValue val;
	if (GetField("SteeringForce", val)) {
		return val.GetFloatValue();
	}
	else return cSTEERINGFORCE;
}

bool CAdoParseBlock::GetLosingCorridorEnable(void) const
{
	CSnoValue val;
	if (GetField("LosingCorridor", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetHighwayMergeEnable(void) const
{
	CSnoValue val;
	if (GetField("HighwayMerge", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetAvoidMergingObjEnable(void) const
{
	CSnoValue val;
	if (GetField("AvoidMergingObj", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetSlowMovingObjEnable(void) const
{
	CSnoValue val;
	if (GetField("SlowMovingObj", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetVerySlowMovingObjEnable(void) const
{
	CSnoValue val;
	if (GetField("VerySlowMovingObj", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

bool CAdoParseBlock::GetNonPassingLaneEnable(void) const
{
	CSnoValue val;
	if (GetField("NonPassingLane", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

double CAdoParseBlock::GetLaneChangeInitDelay(void) const
{
	CSnoValue val;
	if (GetField("LaneChangeInitDelay", val)) {
		return val.GetFloatValue();
	}
	else return cLaneChangeInitDelay;
}

bool CAdoParseBlock::GetFwdDistThresRand(void) const
{
	CSnoValue val;
	if (GetField("FwdDistThresRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetFwdDistThresRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("FwdDistThresRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cFwdDistThresMIN );
		retVal.push_back( cFwdDistThresMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetFwdDistThresVal(void) const
{
	CSnoValue val;
	if (GetField("FwdDistThresVal", val)) {
		return val.GetFloatValue();
	}
	else return cFwdDistThresVal;
}

bool CAdoParseBlock::GetBackDistThresRand(void) const
{
	CSnoValue val;
	if (GetField("BackDistThresRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetBackDistThresRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("BackDistThresRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cBackDistThresMIN );
		retVal.push_back( cBackDistThresMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetBackDistThresVal(void) const
{
	CSnoValue val;
	if (GetField("BackDistThresVal", val)) {
		return val.GetFloatValue();
	}
	else return cBackDistThresVal;
}

bool CAdoParseBlock::GetFwdTimeThresRand(void) const
{
	CSnoValue val;
	if (GetField("FwdTimeThresRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetFwdTimeThresRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("FwdTimeThresRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cFwdTimeThresMIN );
		retVal.push_back( cFwdTimeThresMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetFwdTimeThresVal(void) const
{
	CSnoValue val;
	if (GetField("FwdTimeThresVal", val)) {
		return val.GetFloatValue();
	}
	else return cFwdTimeThresVal;
}

bool CAdoParseBlock::GetBackTimeThresRand(void) const
{
	CSnoValue val;
	if (GetField("BackTimeThresRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetBackTimeThresRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("BackTimeThresRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cBackTimeThresMIN );
		retVal.push_back( cBackTimeThresMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetBackTimeThresVal(void) const
{
	CSnoValue val;
	if (GetField("BackTimeThresVal", val)) {
		return val.GetFloatValue();
	}
	else return cBackTimeThresVal;
}

bool CAdoParseBlock::GetDistFromRand(void) const
{
	CSnoValue val;
	if (GetField("DistFromRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetDistFromRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("DistFromRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cDistFromRandMIN );
		retVal.push_back( cDistFromRandMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetDistFromVal(void) const
{
	CSnoValue val;
	if (GetField("DistFromVal", val)) {
		return val.GetFloatValue();
	}
	else return cDistFromVal;
}

bool CAdoParseBlock::GetTimeToRand(void) const
{
	CSnoValue val;
	if (GetField("TimeToRand", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cENABLE;
}

vector<double> CAdoParseBlock::GetTimeToRandVal(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> retVal;
	if (GetField("TimeToRandVal", vals)) {
		pVal = vals.begin();
		retVal.push_back(pVal->GetFloatValue());
		pVal++;
		retVal.push_back(pVal->GetFloatValue());
	}
	else {
		retVal.push_back( cTimeToMIN );
		retVal.push_back( cTimeToMAX );
	}
	return retVal;
}

double CAdoParseBlock::GetTimeToVal(void) const
{
	CSnoValue val;
	if (GetField("TimeToVal", val)) {
		return val.GetFloatValue();
	}
	else return cTimeToVal;
}

bool CAdoParseBlock::GetAvoidTurning(void) const
{
	CSnoValue val;
	if (GetField("AvoidTurn", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cAvoidTurning;
}

bool CAdoParseBlock::GetIsCreateRelative(void) const
{
	CSnoValue val;
	if (GetField("CreateRel", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cCreateRelative;
}

bool CAdoParseBlock::GetIsCreateLatFeet(void) const
{
	CSnoValue val;
	if (GetField("CreateRelLatInFeet", val)) {
		return (val.GetIntValue() != 0);
	}
	else return cCreateRelLatInFeet;
}

int CAdoParseBlock::GetLatOffsType(void) const
{
	CSnoValue val;
	if(GetField("LatOffsType", val)) {
		return (val.GetIntValue());
	}
	else return 0;
}

int CAdoParseBlock::GetCreateAbsoluteLane(void) const
{
	CSnoValue val;
	if (GetField("CreateAbsLane", val)) {
		return (val.GetIntValue());
	}
	else return 0;
}

int CAdoParseBlock::GetCreateRelativeLane(void) const
{
	CSnoValue val;
	if (GetField("CreateRelLane", val)) {
		return (val.GetIntValue());
	}
	else return 0;
}

double CAdoParseBlock::GetLaneOffs(void) const
{
	CSnoValue val;
	if (GetField("LaneOffs", val)) {
		return (val.GetFloatValue());
	}
	else return 0.0;
}

string CAdoParseBlock::GetCreateRelativeObjName(void) const
{
	CSnoValue val;
	if (GetField("CreateRelObjName", val)) {
		return val.GetStringValue();
	}
	else return cCreateRelativeObjName;
}

double
CAdoParseBlock::GetCreateRelativeOffsetLateral(void) const
{
	CSnoValue val;
	if (GetField("CreateRelOffsLat", val)) {
		return val.GetFloatValue();
	}
	else return cCreateRelativeLateral;
}

double
CAdoParseBlock::GetCreateRelativeOffsetLongitudinal(void) const
{
	CSnoValue val;
	if (GetField("CreateRelOffsLon", val)) {
		return val.GetFloatValue();
	}
	else return cCreateRelativeLongitudinal;
}

string
CAdoParseBlock::GetCreateRelativeOffsetLongitudinalExpression(void) const
{
	CSnoValue val;
	if (GetField("CreateRelOffsLonExprStr", val)) {
		return val.GetStringValue();
	}else
		return string("");
}
bool
CAdoParseBlock::GetUseExpressionForRelativeLongintidinalOffset(void) const
{
	CSnoValue val;
	if (GetField("CreateRelOffsLonUsingExpr", val)) {
		return val.GetIntValue() > 0;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
// 	Mutator functions
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
CAdoParseBlock::SetName(const string& name)
{
	// Delete any "Name" fields
	ClearFields("Name");

	// Add new "Name" field.
	AddField("Name", name);

} // end of SetName

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
CAdoParseBlock::SetCrRad(double crRad)
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
CAdoParseBlock::SetActvDel(double actvDel)
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
CAdoParseBlock::SetLifetime(double lifetime)
{
	// Delete any "Lifetime" fields
	ClearFields("Lifetime");

	// Add new "Lifetime" field.
	if (cLIFETIME != lifetime)
		AddField("Lifetime", lifetime);

} // end of SetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetSolName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	solName - a string to which to set the SolName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetSolName(const string& solName)
{
	// Delete any "SolName" fields
	ClearFields("SolName");

	// Add new "SolName" field.
	AddField("SolName", solName);

} // end of SetSolName

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetRandomSol
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	isRand - a bool to which to set the RandomSol field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetRandomSol(bool isRand)
{
	// Delete any "RandomSol" fields
	ClearFields("RandomSol");

	// Add new "RandomSol" field.
	AddField("RandomSol", isRand ? 1 : 0);

}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetAudioState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	sound - a int to which to set the AudioState field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetAudioState(int sound)
{
	// Delete any "AudioState" fields
	ClearFields("AudioState");

	// Add new "AudioState" field.
	if (cAUDIOSTATE != sound)
		AddField("AudioState", sound);

} // end of SetAudioState

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVisualState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	lights - a int to which to set the VisualState field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetVisualState(int lights)
{
	// Delete any "VisualState" fields
	ClearFields("VisualState");

	// Add new "VisualState" field.
	if (cVISUALSTATE != lights)
		AddField("VisualState", lights);

} // end of SetVisualState
/////////////////////////////////////////////////////////////////////////////
///\brief
///		Tells the ADO it needs to control the break lights based on accel
///////////////////////////////////////////////////////////////////////////
void			
CAdoParseBlock::SetAutoControlBrakeLight(bool autoControl){
	// Delete any "VisualState" fields
	ClearFields("AutoControlBreakLights");

	AddField("AutoControlBreakLights", autoControl?1:0);
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///		Tells the ADO it needs to control the head lights based on time of day
//////////////////////////////////////////////////////////////////////////////
void			
CAdoParseBlock::SetAutoControlHeadLight(bool autoControl){
	// Delete any "VisualState" fields
	ClearFields("AutoControlHeadLights");


	AddField("AutoControlHeadLights", autoControl?1:0);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetColorIndex
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	color - a int to which to set the ColorIndex field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetColorIndex(int color)
{
	// Delete any "ColorIndex" fields
	ClearFields("ColorIndex");

	// Add new "ColorIndex" field.
	if (cCOLORINDEX != color)
		AddField("ColorIndex", color);

} // end of SetColorIndex

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a string vector to which to set the Path field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetPath(const vector<string>& paths)
{
	vector<string>::const_iterator itr;

	// Delete any "Path" fields
	ClearFields("Path");

	// Add fields to the list
	for (itr = paths.begin(); itr != paths.end(); itr++) {
		AddField("Path", *itr);
	}
} // end of SetPath

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetRoadPos
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	roadPos - a string to which to set the RoadPos field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetRoadPos(const string& roadPos)
{
	// Delete any "RoadPos" fields
	ClearFields("RoadPos");

	// Add new "RoadPos" field.
	AddField("RoadPos", roadPos);

} // end of SetRoadPos


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDynModel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	dynModel - A string representing the dynamics model to be used.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetDynModel(const string& dynModel)
{
	// Delete any "DynModel" fields
	ClearFields("DynModel");

	// Add new "DynModel" field.
	AddField("DynModel", dynModel);

} // end of SetDynModel

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetRunMode
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	runMode - a string to which to set the RunMode field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetRunMode(const string& runMode)
{
	// Delete any "RunMode" fields
	ClearFields("RunMode");

	// Add new "RunMode" field.
	AddField("RunMode", runMode);

} // end of SetRunMode

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetLogFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	logfile - a string to which to set the LogFile field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetLogFile(const string& logfile)
{
	// Delete any "LogFile" fields
	ClearFields("LogFile");

	// Add new "LogFile" field.
	AddField("LogFile", logfile);

} // end of SetLogFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCmdFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	cmdFile - a string to which to set the CmdFile field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetCmdFile(const string& cmdFile)
{
	// Delete any "CmdFile" fields
	ClearFields("CmdFile");

	// Add new "CmdFile" field.
	AddField("CmdFile", cmdFile);

} // end of SetCmdFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOffroadPoint
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	point - a CPoint2D to which to set the SetTargetPoint field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetOffroadPoint(const CPoint3D& point)
{
	// Delete any "OffroadPoint" fields
	ClearFields("OffroadPoint");

	vector<double> vals;
	vals.push_back( (double)point.m_x );
	vals.push_back( (double)point.m_y );
	vals.push_back( (double)point.m_z );

	// Add new "OffroadPoint" field.
	AddField("OffroadPoint", vals);

} // end of SetOffroadPoint


//////////////////////////////////////////////////////////////////////////////
//
// Description: RemoveOffroadPoint
//				
//
// Remarks:		
//
// Arguments: 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::RemoveOffroadPoint(void)
{
	// Delete any "OffroadPoint" fields
	ClearFields("OffroadPoint");
}


void
CAdoParseBlock::SetFollowTimeMin(double t)
{
	// Delete any "FollowTimeMin" fields
	ClearFields("FollowTimeMin");

	// Add new "FollowTimeMin" field.
	AddField("FollowTimeMin", t);

}

void
CAdoParseBlock::SetFollowTimeMax(double t)
{
	// Delete any "FollowTimeMax" fields
	ClearFields("FollowTimeMax");

	// Add new "FollowTimeMax" field.
	AddField("FollowTimeMax", t);
}

void
CAdoParseBlock::SetFollowDistMin(double t)
{
	// Delete any "FollowDistMin" fields
	ClearFields("FollowDistMin");

	// Add new "FollowDistMin" field.
	AddField("FollowDistMin", t);
}

void
CAdoParseBlock::SetFollowDistMax(double t)
{
	// Delete any "FollowDistMax" fields
	ClearFields("FollowDistMax");

	// Add new "FollowDistMax" field.
	AddField("FollowDistMax", t);
}

void
CAdoParseBlock::SetIsFollowTime(bool isTime)
{
	if (isTime) {
		ClearFields( "FollowDistMin" );
		ClearFields( "FollowDistMax" );
	} else {
		ClearFields( "FollowTimeMin" );
		ClearFields( "FollowTimeMax" );
	}
}


void
CAdoParseBlock::SetTtcThres1(double t)
{
	// Delete any "TtcThres1" fields
	ClearFields("TtcThres1");

	// Add new "TtcThres1" field.
	if (cTTCTHRES1 != t)
		AddField("TtcThres1", t);
}


void
CAdoParseBlock::SetTtcThres2(double t)
{
	// Delete any "TtcThres2" fields
	ClearFields("TtcThres2");

	// Add new "TtcThres2" field.
	if (cTTCTHRES2 != t)
		AddField("TtcThres2", t);
}

void
CAdoParseBlock::SetTtcThres3(double t)
{
	// Delete any "TtcThres3" fields
	ClearFields("TtcThres3");

	// Add new "TtcThres3" field.
	if (cTTCTHRES3 != t)
		AddField("TtcThres3", t);
}

void
CAdoParseBlock::SetEngThres(double t)
{
	// Delete any "EngThres" fields
	ClearFields("EngThres");

	// Add new "EngThres" field.
	AddField("EngThres", t);
}

void
CAdoParseBlock::SetUseReaDel(bool val)
{
	// Delete any "UseReaDel" fields
	ClearFields("UseReaDel");

	// Add new "UseReaDel" field.
	AddField("UseReaDel", val ? 1 : 0);
}

void
CAdoParseBlock::SetStdToAccDel(const CAdoParseBlock::CDelay& val)
{
	// Delete any "StdToAccType" fields
	ClearFields("StdToAccType");

	// Add new "StdToAccType" field.
	AddField("StdToAccType", (int)val.m_type );

	// Delete any "StdToAccVal1" fields
	ClearFields("StdToAccVal1");

	// Add new "StdToAccVal1" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTDTOACCDELFIXEDP1 != val.m_param1 )
			AddField("StdToAccVal1", val.m_param1 );
		break;
	case eUNIFORM:
		if ( cSTDTOACCDELUNIFORMP1 != val.m_param1 )
			AddField("StdToAccVal1", val.m_param1 );
		break;
	case eNORMAL:
		if ( cSTDTOACCDELNORMALP1 != val.m_param1 )
			AddField("StdToAccVal1", val.m_param1 );
		break;
	}

	// Delete any "StdToAccVal2" fields
	ClearFields("StdToAccVal2");

	// Add new "StdToAccVal2" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTDTOACCDELFIXEDP2 != val.m_param2 )
			AddField("StdToAccVal2", val.m_param2 );
		break;
	case eUNIFORM:
		if ( cSTDTOACCDELUNIFORMP2 != val.m_param2 )
			AddField("StdToAccVal2", val.m_param2 );
		break;
	case eNORMAL:
		if ( cSTDTOACCDELNORMALP2 != val.m_param2 )
			AddField("StdToAccVal2", val.m_param2 );
		break;
	}
}

void
CAdoParseBlock::SetStdToDecDel(const CAdoParseBlock::CDelay& val)
{
	// Delete any "StdToDecType" fields
	ClearFields("StdToDecType");

	// Add new "StdToDecType" field.
	AddField("StdToDecType", (int)val.m_type );

	// Delete any "StdToDecVal1" fields
	ClearFields("StdToDecVal1");

	// Add new "StdToDecVal1" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTDTODECDELFIXEDP1 != val.m_param1 )
			AddField("StdToDecVal1", val.m_param1 );
		break;
	case eUNIFORM:
		if ( cSTDTODECDELUNIFORMP1 != val.m_param1 )
			AddField("StdToDecVal1", val.m_param1 );
		break;
	case eNORMAL:
		if ( cSTDTODECDELNORMALP1 != val.m_param1 )
			AddField("StdToDecVal1", val.m_param1 );
		break;
	}

	// Delete any "StdToDecVal2" fields
	ClearFields("StdToDecVal2");

	// Add new "StdToDecVal2" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTDTODECDELFIXEDP2 != val.m_param2 )
			AddField("StdToDecVal2", val.m_param2 );
		break;
	case eUNIFORM:
		if ( cSTDTODECDELUNIFORMP2 != val.m_param2 )
			AddField("StdToDecVal2", val.m_param2 );
		break;
	case eNORMAL:
		if ( cSTDTODECDELNORMALP2 != val.m_param2 )
			AddField("StdToDecVal2", val.m_param2 );
		break;
	}
}

void
CAdoParseBlock::SetDecToAccDel(const CAdoParseBlock::CDelay& val)
{
	// Delete any "DecToAccType" fields
	ClearFields("DecToAccType");

	// Add new "DecToAccType" field.
	AddField("DecToAccType", (int)val.m_type );

	// Delete any "DecToAccVal1" fields
	ClearFields("DecToAccVal1");

	// Add new "DecToAccVal1" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cDECTOACCDELFIXEDP1 != val.m_param1 )
			AddField("DecToAccVal1", val.m_param1 );
		break;
	case eUNIFORM:
		if ( cDECTOACCDELUNIFORMP1 != val.m_param1 )
			AddField("DecToAccVal1", val.m_param1 );
		break;
	case eNORMAL:
		if ( cDECTOACCDELNORMALP1 != val.m_param1 )
			AddField("DecToAccVal1", val.m_param1 );
		break;
	}

	// Delete any "DecToAccVal2" fields
	ClearFields("DecToAccVal2");

	// Add new "DecToAccVal2" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cDECTOACCDELFIXEDP2 != val.m_param2 )
			AddField("DecToAccVal2", val.m_param2 );
		break;
	case eUNIFORM:
		if ( cDECTOACCDELUNIFORMP2 != val.m_param2 )
			AddField("DecToAccVal2", val.m_param2 );
		break;
	case eNORMAL:
		if ( cDECTOACCDELNORMALP2 != val.m_param2 )
			AddField("DecToAccVal2", val.m_param2 );
		break;
	}
}

void
CAdoParseBlock::SetStpToAccDel(const CAdoParseBlock::CDelay& val)
{
	// Delete any "StpToAccType" fields
	ClearFields("StpToAccType");

	// Add new "StpToAccType" field.
	AddField("StpToAccType", (int)val.m_type );

	// Delete any "StpToAccVal1" fields
	ClearFields("StpToAccVal1");

	// Add new "StpToAccVal1" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTPTOACCDELFIXEDP1 != val.m_param1 )
			AddField("StpToAccVal1", val.m_param1 );
		break;
	case eUNIFORM:
		if ( cSTPTOACCDELUNIFORMP1 != val.m_param1 )
			AddField("StpToAccVal1", val.m_param1 );
		break;
	case eNORMAL:
		if ( cSTPTOACCDELNORMALP1 != val.m_param1 )
			AddField("StpToAccVal1", val.m_param1 );
		break;
	}

	// Delete any "StpToAccVal2" fields
	ClearFields("StpToAccVal2");

	// Add new "StpToAccVal2" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cSTPTOACCDELFIXEDP2 != val.m_param2 )
			AddField("StpToAccVal2", val.m_param2 );
		break;
	case eUNIFORM:
		if ( cSTPTOACCDELUNIFORMP2 != val.m_param2 )
			AddField("StpToAccVal2", val.m_param2 );
		break;
	case eNORMAL:
		if ( cSTPTOACCDELNORMALP2 != val.m_param2 )
			AddField("StpToAccVal2", val.m_param2 );
		break;
	}
}

void
CAdoParseBlock::SetNormDistKp(double val)
{
	// Delete any "NormDistKp" fields
	ClearFields("NormDistKp");

	// Add new "NormDistKp" field.
	if (cNORMDISTKP != val)
		AddField("NormDistKp", val);
}

void
CAdoParseBlock::SetNormDistKi(double val)
{
	// Delete any "NormDistKi" fields
	ClearFields("NormDistKi");

	// Add new "NormDistKi" field.
	if (cNORMDISTKI != val)
		AddField("NormDistKi", val);
}

void
CAdoParseBlock::SetNormDistKd(double val)
{
	// Delete any "NormDistKd" fields
	ClearFields("NormDistKd");

	// Add new "NormDistKd" field.
	if (cNORMDISTKD != val)
		AddField("NormDistKd", val);
}

void
CAdoParseBlock::SetNormVelKp(double val)
{
	// Delete any "NormVelKp fields
	ClearFields("NormVelKp");

	// Add new "NormVelKp" field.
	if (cNORMVELKP != val)
		AddField("NormVelKp", val);
}

void
CAdoParseBlock::SetNormVel2Kp(double val)
{
	// Delete any "NormVel2Kp fields
	ClearFields("NormVel2Kp");

	// Add new "NormVel2Kp" field.
	AddField("NormVel2Kp", val);
}

void
CAdoParseBlock::SetOvSpeedClip(double val)
{
	// Delete any "OvSpeedClip fields
	ClearFields("OvSpeedClip");

	// Add new "OvSpeedClip" field.
	if (cOVSPEEDCLIP != val)
		AddField("OvSpeedClip", val);
}

void
CAdoParseBlock::SetOvSpeedRng(double val)
{
	// Delete any "OvSpeedRng fields
	ClearFields("OvSpeedRng");

	// Add new "OvSpeedRng" field.
	if (cOVSPEEDRNG != val)
		AddField("OvSpeedRng", val);
}

void
CAdoParseBlock::SetNormAccelClip(double val)
{
	// Delete any "NormAccelClip fields
	ClearFields("NormAccelClip");

	// Add new "NormAccelClip" field.
	if (cNORMACCELCLIP != val)
		AddField("NormAccelClip", val);
}

void
CAdoParseBlock::SetNormDecelClip(double val)
{
	// Delete any "NormDecelClip fields
	ClearFields("NormDecelClip");

	// Add new "NormDecelClip" field.
	if (cNORMDECELCLIP != val)
		AddField("NormDecelClip", val);
}

void
CAdoParseBlock::SetBumpStopDist(double val)
{
	// Delete any "BumpStopDist fields
	ClearFields("BumpStopDist");

	// Add new "BumpStopDist" field.
	if (cBUMPSTOPDIST != val)
		AddField("BumpStopDist", val);
}

void
CAdoParseBlock::SetAppDecRate(double val)
{
	// Delete any "AppDecRate fields
	ClearFields("AppDecRate");

	// Add new "AppDecRate" field.
	if (cAPPDECRATE != val)
		AddField("AppDecRate", val);
}

void
CAdoParseBlock::SetAccel2Catch(bool val)
{
	// Delete any "Accel2Catch fields
	ClearFields("Accel2Catch");

	// Add new "Accel2Catch" field.
	AddField("Accel2Catch", val ? 1:0);
}

void
CAdoParseBlock::SetMinEngTime(double val)
{
	// Delete any "MinEngTime fields
	ClearFields("MinEngTime");

	// Add new "MinEngTime" field.
	if (cMINENGTIME != val)
		AddField("MinEngTime", val);
}

void
CAdoParseBlock::SetEmergDistKp(double val)
{
	// Delete any "EmergDistKp fields
	ClearFields("EmergDistKp");

	// Add new "EmergDistKp" field.
	if (cEMERGDISTKP != val)
		AddField("EmergDistKp", val);
}

void
CAdoParseBlock::SetEmergDistKi(double val)
{
	// Delete any "EmergDistKi fields
	ClearFields("EmergDistKi");

	// Add new "EmergDistKi" field.
	if (cEMERGDISTKI != val)
		AddField("EmergDistKi", val);
}

void
CAdoParseBlock::SetEmergDistKd(double val)
{
	// Delete any "EmergDistKd fields
	ClearFields("EmergDistKd");

	// Add new "EmergDistKd" field.
	if (cEMERGDISTKD != val)
		AddField("EmergDistKd", val);
}

void
CAdoParseBlock::SetEmergVelKp(double val)
{
	// Delete any "EmergVelKp fields
	ClearFields("EmergVelKp");

	// Add new "EmergVelKp" field.
	if (cEMERGVELKP != val)
		AddField("EmergVelKp", val);
}

void
CAdoParseBlock::SetEmergVelKi(double val)
{
	// Delete any "EmergVelKi fields
	ClearFields("EmergVelKi");

	// Add new "EmergVelKi" field.
	if (cEMERGVELKI != val)
		AddField("EmergVelKi", val);
}

void
CAdoParseBlock::SetEmergVelKd(double val)
{
	// Delete any "EmergVelKd fields
	ClearFields("EmergVelKd");

	// Add new "EmergVelKd" field.
	if (cEMERGVELKD != val)
		AddField("EmergVelKd", val);
}

void
CAdoParseBlock::SetEmergAclKp(double val)
{
	// Delete any "EmergAclKp fields
	ClearFields("EmergAclKp");

	// Add new "EmergAclKp" field.
	if (cEMERGACLKP != val)
		AddField("EmergAclKp", val);
}

void
CAdoParseBlock::SetEmergDecClip(double val)
{
	// Delete any "EmergDecClip fields
	ClearFields("EmergDecClip");

	// Add new "EmergDecClip" field.
	AddField("EmergDecClip", val);
}

void
CAdoParseBlock::SetMainGapDistKp(double val)
{
	// Delete any "MgDistKp fields
	ClearFields("MgDistKp");

	// Add new "MgDistKp" field.
	if (cMGDISTKP != val)
		AddField("MgDistKp", val);
}

void
CAdoParseBlock::SetMainGapDistKi(double val)
{
	// Delete any "MgDistKi fields
	ClearFields("MgDistKi");

	// Add new "MgDistKi" field.
	if (cMGDISTKI != val)
		AddField("MgDistKi", val);
}

void
CAdoParseBlock::SetMainGapDistKd(double val)
{
	// Delete any "MgVelKp" fields
	ClearFields("MgVelKp");

	// Add new "MgVelKp" field.
	if (cMGVELKP != val)
		AddField("MgVelKp", val);
}

void
CAdoParseBlock::SetMainGapVelKp(double val)
{
	// Delete any "MgVelKp fields
	ClearFields("MgVelKp");

	// Add new "MgVelKp" field.
	if (cMGVELKP != val)
		AddField("MgVelKp", val);
}

void
CAdoParseBlock::SetMainGapMaxAcc(double val)
{
	// Delete any "MgMaxAcc fields
	ClearFields("MgMaxAcc");

	// Add new "MgMaxAcc" field.
	if (cMGMAXACC != val)
		AddField("MgMaxAcc", val);
}

void
CAdoParseBlock::SetMainGapMaxDec(double val)
{
	// Delete any "MgMaxDec fields
	ClearFields("MgMaxDec");

	// Add new "MgMaxDec" field.
	if (cMGMAXDEC != val)
		AddField("MgMaxDec", val);
}

void CAdoParseBlock::SetLcvModel(CAdoParseBlock::ELcvModel val)
{
	// Delete any "LcvMod" fields
	ClearFields("LcvMod");

	// Add new "LcvMod" field.
	if (cLCVMODEL != val)
		AddField("LcvMod", val);
}

void CAdoParseBlock::SetLcvRiseTime(const vector<double>& val)
{
	// Delete any "LcvRise" fields
	ClearFields("LcvRise");

	// Add new "LcvRise" field.
	if (cLCVRISETIME1 != val[0] || cLCVRISETIME2 != val[1])
		AddField("LcvRise", val);
}

void CAdoParseBlock::SetLcvFallTime(const vector<double>& val)
{
	// Delete any "LcvFall" fields
	ClearFields("LcvFall");

	// Add new "LcvFall" field.
	if (cLCVFALLTIME1 != val[0] || cLCVFALLTIME1 != val[1])
		AddField("LcvFall", val);
}

void CAdoParseBlock::SetLcvRampsAmplitude(const vector<double>& val)
{
	// Delete any "LcvRAmpl" fields
	ClearFields("LcvRAmpl");

	// Add new "LcvRAmpl" field.
	if (cLCVRAMPAMPL1 != val[0] || cLCVRAMPAMPL1 != val[1])
		AddField("LcvRAmpl", val);
}

void CAdoParseBlock::SetLcvStableTime(const vector<double>& val)
{
	// Delete any "LcvStab" fields
	ClearFields("LcvStab");

	// Add new "LcvStab" field.
	if (cLCVSTABLETIME1 != val[0] || cLCVSTABLETIME2 != val[1])
		AddField("LcvStab", val);
}

void CAdoParseBlock::SetLcvBias(const vector<double>& val)
{
	// Delete any "LcvBias" fields
	ClearFields("LcvBias");

	// Add new "LcvBias" field.
	if (cLCVBIAS1 != val[0] || cLCVBIAS2 != val[1])
		AddField("LcvBias", val);
}

void CAdoParseBlock::SetLcvSinAmplitude(const vector<double>& val)
{
	// Delete any "LcvSAmpl" fields
	ClearFields("LcvSAmpl");

	// Add new "LcvSAmpl" field.
	if (cLCVSINAMPL1 != val[0] || cLCVSINAMPL2 != val[1])
		AddField("LcvSAmpl", val);
}

void CAdoParseBlock::SetLcvFrequency(const vector<double>& val)
{
	// Delete any "LcvFreq" fields
	ClearFields("LcvFreq");

	// Add new "LcvFreq" field.
	if (cLCVFREQ1 != val[0] || cLCVFREQ1 != val[1])
		AddField("LcvFreq", val);
}

void CAdoParseBlock::SetLcvPhase(const vector<double>& val)
{
	// Delete any "LcvPhase" fields
	ClearFields("LcvPhase");

	// Add new "LcvPhase" field.
	if (cLCVPHASE1 != val[0] || cLCVPHASE2 != val[1])
		AddField("LcvPhase", val);
}

void CAdoParseBlock::SetLcvExpression(const string& val)
{
	// Delete any "LcvExpr" fields
	ClearFields("LcvExpr");

	// Add new "LcvExpr" field.
	if (cEXPRESSION != val)
		AddField("LcvExpr", val);
}

void CAdoParseBlock::SetLcvReevalInterv(const vector<double>& val)
{
	// Delete any "LcvReevInt" fields
	ClearFields("LcvReevInt");

	// Add new "LcvReevInt" field.
	if (cREEVALINTERV1 != val[0] || cREEVALINTERV2 != val[1])
		AddField("LcvReevInt", val);
}

void CAdoParseBlock::SetLcvEnable(bool val)
{
	// Delete any "LcvEnab" fields
	ClearFields("LcvEnab");

	// Add new "LcvEnab" field.
	if (cENABLE != val)
		AddField("LcvEnab", val ? 1 : 0);
}

void CAdoParseBlock::SetLcvAutoDisable(bool val)
{
	// Delete any "LcvAutoDis" fields
	ClearFields("LcvAutoDis");

	// Add new "LcvAutoDis" field.
	if (cAUTODISABLE != val)
		AddField("LcvAutoDis", val ? 1 : 0);
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInitVel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	initVel - a double to which to set the InitVel field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetVelCtrlInitVel(double initVel)
{
	// Delete any "VelCtrlInitVel" fields
	ClearFields("VelCtrlInitVel");
	ClearFields("InitVel");

	// Add new "InitVel" field.
	if (cINITVEL != initVel)
		AddField("VelCtrlInitVel", initVel);

} // end of SetInitVel
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInitVel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	initVel - a double to which to set the InitVel field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetVelCtrlInitMatchOvVel(bool initMatchVel)
{
	// Delete any "VelCtrlInitVel" fields
	ClearFields("VelCtrlInitMatchOvVel");

	// Add new "InitVel" field.
	AddField("VelCtrlInitMatchOvVel", initMatchVel);

} // end of SetInitVel
//////////////////////////////////////////////////////////////////////////
///\brief
///     Gets if the ADO should follow the Speed Limit by default
///\return  true -follow the speed limit (defualt)
/////////////////////////////////////////////////////////////////////////
void
CAdoParseBlock::SetVelCtrlFollowSpeedLimit(bool isFollwSpeedLimmit)
{
	// Delete any "VelCtrlInitVel" fields
	ClearFields("VelCtrlFollowSpeedLimit");

	// Add new "InitVel" field.
	AddField("VelCtrlFollowSpeedLimit", isFollwSpeedLimmit);

} // end of SetInitVel
///////////////////
void CAdoParseBlock::SetVelCtrlRefreshTime(double val)
{
	// Delete any "VelCtrlRefreshTime" fields
	ClearFields("VelCtrlRefreshTime");

	// Add new "VelCtrlRefreshTime" field.
	if (cREFRESHTIME != val)
		AddField("VelCtrlRefreshTime", val);
}

void
CAdoParseBlock::SetVelCtrlDistribution(const CAdoParseBlock::CDelay& val)
{
	// Delete any "VelCtrlDistType" fields
	ClearFields("VelCtrlDistType");

	// Add new "VelCtrlDistType" field.
	AddField("VelCtrlDistType", (int)val.m_type );

	// Delete any "VelCtrlDistVal1" fields
	ClearFields("VelCtrlDistVal1");

	// Add new "VelCtrlDistVal1" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cVELCTRLDISTFIXEDP1 != val.m_param1 )
			AddField("VelCtrlDistVal1", val.m_param1 );
		break;
	case eUNIFORM:
		if ( cVELCTRLDISTUNIFORMP1 != val.m_param1 )
			AddField("VelCtrlDistVal1", val.m_param1 );
		break;
	case eNORMAL:
		if ( cVELCTRLDISTNORMALP1 != val.m_param1 )
			AddField("VelCtrlDistVal1", val.m_param1 );
		break;
	}

	// Delete any "VelCtrlDistVal2" fields
	ClearFields("VelCtrlDistVal2");

	// Add new "VelCtrlDistVal2" field.
	switch (val.m_type) {
	case eFIXED:
		if ( cVELCTRLDISTFIXEDP2 != val.m_param2 )
			AddField("VelCtrlDistVal2", val.m_param2 );
		break;
	case eUNIFORM:
		if ( cVELCTRLDISTUNIFORMP2 != val.m_param2 )
			AddField("VelCtrlDistVal2", val.m_param2 );
		break;
	case eNORMAL:
		if ( cVELCTRLDISTNORMALP2 != val.m_param2 )
			AddField("VelCtrlDistVal2", val.m_param2 );
		break;
	}

}

void CAdoParseBlock::SetRandomize(bool val)
{
	// Delete any "Randomize" fields
	ClearFields("Randomize");

	// Add new "Randomize" field.
	if (cRANDOMIZE != val)
		AddField("Randomize", val ? 1 : 0);
}

void CAdoParseBlock::SetRandomizeSignalTime(const vector<double>& val)
{
	// Delete any "RandomSignalTime" fields
	ClearFields("SignalTime");
	ClearFields("RandomizeSignalTime");
	
	vector<double> valT;
	valT = val;
	// Add a new "Randomize SignalTime" field
	if (cSIGNALTIMEMIN != val[0] || cSIGNALTIMEMAX != val[1]){
		AddField("RandomizeSignalTime", valT);
	}
}

void CAdoParseBlock::SetSignalTime(double val)
{
	// Delete any "SignalTime" fields
	ClearFields("SignalTime");
	
	// Add new "SignalTime" field.
	if (cSIGNALTIME != val)
		AddField("SignalTime", val);
}
void CAdoParseBlock::SetUrgency(double val) 
{
	// Delete any "Urgency" fields
	ClearFields("Urgency");

	// Add new "Urgency" field.
	if (cURGENCY != val)
		AddField("Urgency", val);
}

void CAdoParseBlock::SetSteeringForce(double val)
{
	// Delete any "SteeringForce" fields
	ClearFields("SteeringForce");

	// Add new "SteeringForce" field.
	if (cSTEERINGFORCE != val)
		AddField("SteeringForce", val);
}

void CAdoParseBlock::SetLosingCorridorEnable(bool val)
{
	// Delete any "LosingCorridor" fields
	ClearFields("LosingCorridor");

	// Add new "LosingCorridor" field.
	if (cENABLE != val)
		AddField("LosingCorridor", val ? 1 : 0);
}

void CAdoParseBlock::SetHighwayMergeEnable(bool val)
{
	// Delete any "HighwayMerge" fields
	ClearFields("HighwayMerge");

	// Add new "HighwayMerge" field.
	if (cENABLE != val)
		AddField("HighwayMerge", val ? 1 : 0);
}

void CAdoParseBlock::SetAvoidMergingObjEnable(bool val)
{
	// Delete any "AvoidMergingObj" fields
	ClearFields("AvoidMergingObj");

	// Add new "AvoidMergingObj" field.
	if (cENABLE != val)
		AddField("AvoidMergingObj", val ? 1 : 0);
}

void CAdoParseBlock::SetSlowMovingObjEnable(bool val)
{
	// Delete any "SlowMovingObj" fields
	ClearFields("SlowMovingObj");

	// Add new "SlowMovingObj" field.
	if (cENABLE != val)
		AddField("SlowMovingObj", val ? 1 : 0);
}

void CAdoParseBlock::SetVerySlowMovingObjEnable(bool val)
{
	// Delete any "VerySlowMovingObj" fields
	ClearFields("VerySlowMovingObj");

	// Add new "VerySlowMovingObj" field.
	if (cENABLE != val)
		AddField("VerySlowMovingObj", val ? 1 : 0);
}

void CAdoParseBlock::SetNonPassingLaneEnable(bool val)
{
	// Delete any "NonPassingLane" fields
	ClearFields("NonPassingLane");

	// Add new "NonPassingLane" field.
	if (cENABLE != val)
		AddField("NonPassingLane", val ? 1 : 0);
}

void CAdoParseBlock::SetLaneChangeInitDelay(double val)
{
	// Delete any "LaneChangeInitDelay" fields
	ClearFields("LaneChangeInitDelay");

	// Add new "LaneChangeInitDelay" field.
	if (cLaneChangeInitDelay != val)
		AddField("LaneChangeInitDelay", val);
}

void CAdoParseBlock::SetFwdDistThresRand(bool val)
{
	// Delete any "FwdDistThresRand" fields
	ClearFields("FwdDistThresRand");

	// Add new "FwdDistThresRand" field.
	if (cENABLE != val)
		AddField("FwdDistThresRand", val ? 1 : 0);
}

void CAdoParseBlock::SetFwdDistThresRandVal(const vector<double>& val)
{
	// Delete any "FwdDistThresRandVal" fields
	ClearFields("FwdDistThresRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "FwdDistThresRandVal" field
	if (cFwdDistThresMIN != val[0] || cFwdDistThresMAX != val[1]){
		AddField("FwdDistThresRandVal", valT);
	}
}

void CAdoParseBlock::SetFwdDistThresVal(double val)
{
	// Delete any "FwdDistThresVal" fields
	ClearFields("FwdDistThresVal");

	// Add new "FwdDistThresVal" field.
	if (cFwdDistThresVal != val)
		AddField("FwdDistThresVal", val);
}

void CAdoParseBlock::SetBackDistThresRand(bool val)
{
	// Delete any "BackDistThresRand" fields
	ClearFields("BackDistThresRand");

	// Add new "BackDistThresRand" field.
	if (cENABLE != val)
		AddField("BackDistThresRand", val ? 1 : 0);
}

void CAdoParseBlock::SetBackDistThresRandVal(const vector<double>& val)
{
	// Delete any "BackDistThresRandVal" fields
	ClearFields("BackDistThresRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "BackDistThresRandVal" field
	if (cBackDistThresMIN != val[0] || cBackDistThresMAX != val[1]){
		AddField("BackDistThresRandVal", valT);
	}
}

void CAdoParseBlock::SetBackDistThresVal(double val)
{
	// Delete any "BackDistThresVal" fields
	ClearFields("BackDistThresVal");

	// Add new "BackDistThresVal" field.
	if (cBackDistThresVal != val)
		AddField("BackDistThresVal", val);
}

void CAdoParseBlock::SetFwdTimeThresRand(bool val)
{
	// Delete any "FwdTimeThresRand" fields
	ClearFields("FwdTimeThresRand");

	// Add new "FwdTimeThresRand" field.
	if (cENABLE != val)
		AddField("FwdTimeThresRand", val ? 1 : 0);
}

void CAdoParseBlock::SetFwdTimeThresRandVal(const vector<double>& val)
{
	// Delete any "FwdTimeThresRandVal" fields
	ClearFields("FwdTimeThresRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "FwdTimeThresRandVal" field
	if (cFwdTimeThresMIN != val[0] || cFwdTimeThresMAX != val[1]){
		AddField("FwdTimeThresRandVal", valT);
	}
}

void CAdoParseBlock::SetFwdTimeThresVal(double val)
{
	// Delete any "FwdTimeThresVal" fields
	ClearFields("FwdTimeThresVal");

	// Add new "FwdTimeThresVal" field.
	if (cFwdTimeThresVal != val)
		AddField("FwdTimeThresVal", val);
}

void CAdoParseBlock::SetBackTimeThresRand(bool val)
{
	// Delete any "BackTimeThresRand" fields
	ClearFields("BackTimeThresRand");

	// Add new "BackTimeThresRand" field.
	if (cENABLE != val)
		AddField("BackTimeThresRand", val ? 1 : 0);
}

void CAdoParseBlock::SetBackTimeThresRandVal(const vector<double>& val)
{
	// Delete any "BackTimeThresRandVal" fields
	ClearFields("BackTimeThresRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "BackTimeThresRandVal" field
	if (cBackTimeThresMIN != val[0] || cBackTimeThresMAX != val[1]){
		AddField("BackTimeThresRandVal", valT);
	}
}

void CAdoParseBlock::SetBackTimeThresVal(double val)
{
	// Delete any "BackTimeThresVal" fields
	ClearFields("BackTimeThresVal");

	// Add new "BackTimeThresVal" field.
	if (cBackTimeThresVal != val)
		AddField("BackTimeThresVal", val);
}

void CAdoParseBlock::SetDistFromRand(bool val)
{
	// Delete any "DistFromRand" fields
	ClearFields("DistFromRand");

	// Add new "DistFromRand" field.
	if (cENABLE != val)
		AddField("DistFromRand", val ? 1 : 0);
}

void CAdoParseBlock::SetDistFromRandVal(const vector<double>& val)
{
	// Delete any "DistFromRandVal" fields
	ClearFields("DistFromRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "Randomize SignalTime" field
	if (cDistFromRandMIN != val[0] || cDistFromRandMAX != val[1]){
		AddField("DistFromRandVal", valT);
	}
}

void CAdoParseBlock::SetDistFromVal(double val)
{
	// Delete any "DistFromVal" fields
	ClearFields("DistFromVal");

	// Add new "DistFromVal" field.
	if (cDistFromVal != val)
		AddField("DistFromVal", val);
}

void CAdoParseBlock::SetTimeToRand(bool val)
{
	// Delete any "TimeToRand" fields
	ClearFields("TimeToRand");

	// Add new "TimeToRand" field.
	if (cENABLE != val)
		AddField("TimeToRand", val ? 1 : 0);
}

void CAdoParseBlock::SetTimeToRandVal(const vector<double>& val)
{
	// Delete any "TimeToRandVal" fields
	ClearFields("TimeToRandVal");
	
	vector<double> valT;
	valT = val;
	// Add a new "TimeToRandVal" field
	if (cTimeToMIN != val[0] || cTimeToMAX != val[1]){
		AddField("TimeToRandVal", valT);
	}
}

void CAdoParseBlock::SetTimeToVal(double val)
{
	// Delete any "TimeToVal" fields
	ClearFields("TimeToVal");

	// Add new "TimeToVal" field.
	if (cTimeToVal != val)
		AddField("TimeToVal", val);
}


void CAdoParseBlock::SetAvoidTurning(bool val)
{
	// Delete any "AvoidTurn" fields
	ClearFields("AvoidTurn");

	// Add new "AvoidTurn" field.
	if (cAvoidTurning != val)
		AddField("AvoidTurn", val ? 1 : 0);
}

void CAdoParseBlock::SetIsCreateRelative(bool isCreateRel)
{
	// Delete any "CreateRel" fields
	ClearFields("CreateRel");

	// Add new "CreateRel" field.
	if (cCreateRelative != isCreateRel)
		AddField("CreateRel", isCreateRel ? 1 : 0);
}

void CAdoParseBlock::SetLatOffsType(int type)
{
	ClearFields("LatOffsType");

	if(type == eRELATIVE)
		AddField("LatOffsType", eRELATIVE);
	else if(type == eABSOLUTE)
		AddField("LatOffsType", eABSOLUTE);
	else if(type == eDISTANCE)
		AddField("LatOffsType", eDISTANCE);
}

void CAdoParseBlock::SetIsCreateLatFeet(bool isCreateFeet)
{
	// Delete any "CreateRelLatInFeet" fields
	ClearFields("CreateRelLatInFeet");

	// Add new "CreateRelLatInFeet" field.
	AddField("CreateRelLatInFeet", isCreateFeet ? 1 : 0);
}

void CAdoParseBlock::SetCreateRelativeObjName(const string& name)
{
	// Delete any "CreateRelObjName" fields
	ClearFields("CreateRelObjName");

	// Add new "CreateRelObjName" field.
	if (cCreateRelativeObjName != name)
		AddField("CreateRelObjName", name);
}

void CAdoParseBlock::SetCreateRelativeOffsetLateral(double lat)
{
	// Delete any "CreateRelOffsLat" fields
	ClearFields("CreateRelOffsLat");

	// Add new "CreateRelOffsLat" field.
	if (cCreateRelativeLateral != lat)
		AddField("CreateRelOffsLat", lat);
}

void CAdoParseBlock::SetCreateAbsoluteLane(int lane)
{
	// Delete any "CreateAbsLane" fields
	ClearFields("CreateAbsLane");

	// Add new "CreateAbsLane" field.
	if (0 != lane)
		AddField("CreateAbsLane", lane);
}

void CAdoParseBlock::SetCreateRelativeLane(int lane)
{
	// Delete any "CreateRelLane" fields
	ClearFields("CreateRelLane");

	// Add new "CreateRelLane" field.
	if (0 != lane)
		AddField("CreateRelLane", lane);
}

void CAdoParseBlock::SetLaneOffs(double offs)
{
	// Delete any "LaneOffs" fields
	ClearFields("LaneOffs");

	// Add new "LaneOffs" field.
	if (0.0 != offs)
		AddField("LaneOffs", offs);
}

void CAdoParseBlock::SetCreateRelativeOffsetLongitudinal(double longitude)
{
	// Delete any "CreateRelOffsLon" fields
	ClearFields("CreateRelOffsLon");

	// Add new "CreateRelOffsLon" field.
	if (cCreateRelativeLongitudinal != longitude)
		AddField("CreateRelOffsLon", longitude);
}


void CAdoParseBlock::SetCreateRelativeOffsetLongitudinalExpression(const string& str)
{
	// Delete any "CreateRelOffsLon" fields
	ClearFields("CreateRelOffsLonExprStr");

	// Add new "CreateRelOffsLon" field.
	AddField("CreateRelOffsLonExprStr", str);
}
void CAdoParseBlock::SetUseExpressionForRelativeLongintidinalOffset(bool val) 
{
	// Delete any "CreateRelOffsLon" fields
	ClearFields("CreateRelOffsLonUsingExpr");

	// Add new "CreateRelOffsLon" field.
	if (val)
		AddField("CreateRelOffsLonUsingExpr", 1);
	else
		AddField("CreateRelOffsLonUsingExpr", 0);
}
//////////////////////////////////////////////////////////////////////////
///\brief   Set the max 
////////////////////////////////////////////////////////////////////////
void CAdoParseBlock::SetMaxLaneChangeLatOffset(double offset){
 	// Delete any "CreateRelOffsLon" fields
	ClearFields("MaxLatOffset");

	// Add new "CreateRelOffsLon" field.
	AddField("MaxLatOffset", offset);   
}
//////////////////////////////////////////////////////////////////////////
///\brief   Set the aggressiveness of the veh 0 to 1
///\remark
///		This sets the aggressiveness of the vehicle, this changes a 
///     number of parameters, such as gap acceptance target accel,
///     lane change, ect. 
////////////////////////////////////////////////////////////////////////
void CAdoParseBlock::SetAggressiveness(double agg){
 	// Delete any "CreateRelOffsLon" fields
	ClearFields("Aggressiveness");

	// Add new "CreateRelOffsLon" field.
	AddField("Aggressiveness", agg);
}
/////////////////////////////////////////////////////////////////////////
///\brief Set Path Search Depth Value
///\remark
///		Sets the depth (cords's) the maintain gap will search to find its
///		its targaet
////////////////////////////////////////////////////////////////////////
void CAdoParseBlock::SetPathSearchDepth(int depth){
	// Delete any "CreateRelOffsLon" fields
	ClearFields("PathSearchDepth");

	// Add new "CreateRelOffsLon" field.
	AddField("PathSearchDepth", depth);
}
/////////////////////////////////////////////////////////////////////////
///\brief Get Path Search Depth Value
///\remark
///		The depth (cords's) the maintain gap will search to find its
///		its targaet
////////////////////////////////////////////////////////////////////////
int CAdoParseBlock::GetPathSearchDepth(void) const
{
	CSnoValue val;
	if (GetField("PathSearchDepth", val)) {
		return val.GetIntValue();
	}
	else return 2;
}
/////////////////////////////////////////////////////////////////////////
///\brief Get Path Search Depth Value
///\remark
///		The depth (cords's) the maintain gap will search to find its
///		its targaet
////////////////////////////////////////////////////////////////////////
double CAdoParseBlock::GetMaxLaneChangeLatOffset(void) const
{
	CSnoValue val;
	if (GetField("MaxLatOffset", val)) {
        return val.GetFloatValue();
	}
	else return 9.0;
}
//////////////////////////////////////////////////////////////////////////
///\brief   Get the aggressiveness of the veh 0 to 1
///\remark
///		The aggressiveness of the vehicle changes a 
///     number of parameters, such as gap acceptance target accel,
///     lane change, ect. 
////////////////////////////////////////////////////////////////////////
double  CAdoParseBlock::GetAggressiveness(void) const{
	CSnoValue val;
	if (GetField("Aggressiveness", val)) {
        return val.GetFloatValue();
	}
	else return 0.5;
}
