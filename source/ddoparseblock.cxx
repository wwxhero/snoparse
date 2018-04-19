//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: ddoparseblock.cxx,v 1.28 2015/05/21 19:48:49 IOWA\dheitbri Exp $
//
// The implementation for the ddo parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include "splinehermite.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDdoParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "Ddo"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDdoParseBlock::CDdoParseBlock()
	: CSnoBlock()
{
	SetBlockName("Ddo");
} // end of CDdoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDdoParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CDdoParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDdoParseBlock::CDdoParseBlock(const CDdoParseBlock& cCopy)
{
	*this = cCopy;
} // end of CDdoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~DdoParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CDdoParseBlock::~CDdoParseBlock() {}// end of CDdoParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CDdoParseBlock
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
CDdoParseBlock::CDdoParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CDdoParseBlock

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
CDdoParseBlock&
CDdoParseBlock::operator=(const CDdoParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=
////////////////////////////////////////////////////////////////////////////
///\brief
///		Converts Action type to a string
///\param[in] in action ID
///\param[out] text description of action type
///\return false on no matching string found
/////////////////////////////////////////////////////////////////////////////
bool CDdoParseBlock::ActionTypeToString(char in, std::string& out){
	switch (in){
	case eNothing:        out = "Nothing";       return true;
	case eWalkingAct1:    out =  "Walk 1";		 return true;
	case eWalkingAct2:    out =  "Walk 2";		 return true;
	case eRunningAct1:    out =  "Run 1";		 return true;
	case eStationaryAct1: out =  "Stand";		 return true;
	case eStationaryAct2: out =  "Sationary 2";	 return true;
	case eStationaryAct3: out =  "Sationary 3";	 return true;
	case eStationaryAct4: out =  "Sationary 4";	 return true;
	default:
		return false;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////
///\brief
///		converts a string to a action type, if no strings match up, return 0
/////////////////////////////////////////////////////////////////////////////
char CDdoParseBlock::StringToActionType(const std::string& in ){
	if (in == "Nothing")     return eNothing;       
	if (in == "Walk 1")      return eWalkingAct1;   
	if (in == "Walk 2")      return eWalkingAct2;   
	if (in == "Run 1")       return eRunningAct1;   
	if (in == "Stand")       return eStationaryAct1;
	if (in == "Sationary 2") return eStationaryAct2;
	if (in == "Sationary 3") return eStationaryAct3;
	if (in == "Sationary 4") return eStationaryAct4;
	return eNothing;
}

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
CDdoParseBlock::GetName(void) const
{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return "";
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
CDdoParseBlock::GetPosition(void) const
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
CDdoParseBlock::GetCrRad(void) const
{
	CSnoValue val;
	if (GetField("CrRad", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
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
CDdoParseBlock::GetActvDel(void) const
{
	CSnoValue val;
	if (GetField("ActvDel", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
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
CDdoParseBlock::GetLifetime(void) const
{
	CSnoValue val;
	if (GetField("Lifetime", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
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
CDdoParseBlock::GetSolName(void) const
{
	CSnoValue val;
	if (GetField("SolName", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetSolName

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
CDdoParseBlock::GetAudioState(void) const
{
	CSnoValue val;
	if (GetField("AudioState", val))
		return val.GetIntValue();
	else
		 return 0;
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
CDdoParseBlock::GetVisualState(void) const
{
	CSnoValue val;
	if (GetField("VisualState", val))
		return val.GetIntValue();
	else
		 return 0;
} // end of GetVisualState

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetQuitAtEnd
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the QuitAtEnd field.
//
//////////////////////////////////////////////////////////////////////////////
int
CDdoParseBlock::GetQuitAtEnd(void) const
{
	CSnoValue val;
	if (GetField("QuitAtEnd", val))
		return val.GetIntValue();
	else
		 return 0;
} // end of GetQuitAtEnd

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDependent
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the Dependent field.
//
//////////////////////////////////////////////////////////////////////////////
int
CDdoParseBlock::GetDependent(void) const
{
	CSnoValue val;
	if (GetField("Dependent", val))
		return val.GetIntValue();
	else
		 return 0;
} // end of GetDependent

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRefPoint
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the RefPoint field.
//
//////////////////////////////////////////////////////////////////////////////
int
CDdoParseBlock::GetRefPoint(void) const
{
	CSnoValue val;
	if (GetField("RefPoint", val))
		return val.GetIntValue();
	else
		 return -1;
} // end of GetRefPoint


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetColorIndex
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the ColorIndex field.
//
//////////////////////////////////////////////////////////////////////////////
int
CDdoParseBlock::GetColorIndex(void) const
{
	CSnoValue val;
	if (GetField("ColorIndex", val))
		return val.GetIntValue();
	else
		return 0;
} // end of GetColorIndex


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDependentRefPoint
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the DependentRefPoint field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CDdoParseBlock::GetDependentRefPoint(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint3D pos;
	if (GetField("DependentRefPoint", vals)) {
		if (vals.size() != 3) {
			TCountError e("DependentRefPoint", 3);
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
} // end of GetDependentRefPoint

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDependentName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the DependentName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CDdoParseBlock::GetDependentName(void) const
{
	CSnoValue val;
	if (GetField("DependentName", val))
		return val.GetStringValue();
	else
		 return "ExternalDriver";
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: IsDependentOwnVeh
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the DependentOwnVeh field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CDdoParseBlock::IsDependentOwnVeh(void) const
{
	CSnoValue val;
	if (GetField("DependentOwnVeh", val))
		return (1 == val.GetIntValue());
	else
		 return 1;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInitZ
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the InitZ field.
//
//////////////////////////////////////////////////////////////////////////////
double
CDdoParseBlock::GetInitZ(void) const
{
	CSnoValue val;
	if (GetField("InitZ", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetInitZ

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTraj
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of TTrajPoint values for the Traj field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CDdoParseBlock::TTrajPoint>
CDdoParseBlock::GetTraj(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TTrajPoint> traj;
	TTrajPoint point;
	if (GetField("Traj", vals)) {
		if (vals.size() % 5 != 0) {
			TCountError e("Traj", 5);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			point.x = pVal->GetFloatValue();
			pVal++;
			point.y = pVal->GetFloatValue();
			pVal++;
			point.vel = pVal->GetFloatValue();
			pVal++;
			point.i = pVal->GetFloatValue();
			pVal++;
			point.j = pVal->GetFloatValue();
			traj.push_back(point);
		}
	}
	return traj;
} // end of GetTraj

vector<double>
CDdoParseBlock::GetDirs(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> dirs;
	if (GetField("Dirs", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			double val = pVal->GetFloatValue();
			dirs.push_back(val);
		}
	} else {
		CSplineHermite spline;
		vector<TTrajPoint> points = GetTraj();
		for (vector<TTrajPoint>::iterator i = points.begin(); i != points.end(); i++) {
			spline.addPoint( i->x, i->y, 0 );
		}
		spline.calc();
		for (unsigned int n=0 ; n < points.size(); n++) {
			CVector3D tang;
			spline.getTangent(n, tang);
			dirs.push_back( (double)atan2( tang.m_j, tang.m_i ));
		}
	}
	return dirs;
}

/////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets how long DiGuy does an animation action per node
///\remark
///		For DDO that do not have a DiGuy object this does nothing time
///	is in seconds. This sould either be empty or match with the simze of 
/// the path 
////////////////////////////////////////////////////////////////////////////
vector<float>
CDdoParseBlock::GetDiGuyActionTime(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<float> times;
	if (GetField("ActionTime", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			double val = pVal->GetFloatValue();
			times.push_back((float)val);
		}
	}
	else {
		CSplineHermite spline;
		vector<TTrajPoint> points = GetTraj();
		for (vector<TTrajPoint>::iterator i = points.begin(); i != points.end(); i++) {
			times.push_back(0);
		}
	}
	return times;
}
/////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets an animation action per node
///\remark
///		For DDO that do not have a DiGuy object this does nothing 
///This sould either be empty or match with the size of the path 
////////////////////////////////////////////////////////////////////////////
vector<char>
CDdoParseBlock::GetDiGuyActionType(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<char> actions;
	if (GetField("ActionTypes", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			char val = (char)pVal->GetIntValue();
			actions.push_back(val);
		}
	}
	else {
		CSplineHermite spline;
		vector<TTrajPoint> points = GetTraj();
		for (vector<TTrajPoint>::iterator i = points.begin(); i != points.end(); i++) {
			actions.push_back(0);
		}
	}
	return actions;
}

vector<double>
CDdoParseBlock::GetDelays(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> delays;
	if (GetField("Delays", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			double val = pVal->GetFloatValue();
			delays.push_back(val);
		}
	}
	else {
		CSplineHermite spline;
		vector<TTrajPoint> points = GetTraj();
		for (vector<TTrajPoint>::iterator i = points.begin(); i != points.end(); i++) {
			delays.push_back(0);
		}
	}
	return delays;
}

vector<bool>
CDdoParseBlock::GetDirsDefault(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<bool> dirs;
	if (GetField("DirsDef", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			double val = (double)pVal->GetIntValue();
			dirs.push_back(val!=0);
		}
	} else {
		vector<TTrajPoint> points = GetTraj();
		for (vector<TTrajPoint>::iterator i = points.begin(); i != points.end(); i++) {
			dirs.push_back( true );
		}
	}
	return dirs;
}

CDdoParseBlock::EState
CDdoParseBlock::GetInitialState(void) const
{
	CSnoValue val;
	if (GetField("InitState", val))
		return (EState)val.GetIntValue();
	else
		return eNORMAL;
}

bool
CDdoParseBlock::GetTrajIsGlobal(void) const
{
	CSnoValue val;
	if (GetField("GlobTraj", val))
		return val.GetIntValue() != 0;
	else
		return true;
}

string
CDdoParseBlock::GetCoupledName(void) const
{
	CSnoValue val;
	if (GetField("Coupled", val))
		return val.GetStringValue();
	else
		return "";
}

CVector3D
CDdoParseBlock::GetRelativeLocation(void) const
{
	CVector3D ret;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("RelLoc", vals)) {
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		ret.m_i = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_j = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_k = val;
	}
	return ret;
}

CVector3D
CDdoParseBlock::GetRelativeOrientation(void) const
{
	CVector3D ret;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("RelRot", vals)) {
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		ret.m_i = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_j = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_k = val;
	}
	return ret;
}

CVector3D
CDdoParseBlock::GetInitVelocityXYZ(void) const
{
	CVector3D ret;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("InitVelXYZ", vals)) {
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		ret.m_i = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_j = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_k = val;
	}
	return ret;
}

CVector3D
CDdoParseBlock::GetInitVelocityRPY(void) const
{
	CVector3D ret;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("InitVelRPY", vals)) {
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		ret.m_i = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_j = val;
		pVal++;
		val = pVal->GetFloatValue();
		ret.m_k = val;
	}
	return ret;
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
CDdoParseBlock::SetName(const string& name)
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
CDdoParseBlock::SetPosition(const CPoint3D& position)
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
CDdoParseBlock::SetCrRad(double crRad)
{
	// Delete any "CrRad" fields
	ClearFields("CrRad");

	// Add new "CrRad" field.
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
CDdoParseBlock::SetActvDel(double actvDel)
{
	// Delete any "ActvDel" fields
	ClearFields("ActvDel");

	// Add new "ActvDel" field.
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
CDdoParseBlock::SetLifetime(double lifetime)
{
	// Delete any "Lifetime" fields
	ClearFields("Lifetime");

	// Add new "Lifetime" field.
	AddField("Lifetime", lifetime);

} // end of SetLifetime

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetSolName
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	solName - a string to which to set the SolName field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetSolName(const string& solName)
{
	// Delete any "SolName" fields
	ClearFields("SolName");

	// Add new "SolName" field.
	AddField("SolName", solName);

} // end of SetSolName

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetAudioState
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	sound - a int to which to set the AudioState field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetAudioState(int sound)
{
	// Delete any "AudioState" fields
	ClearFields("AudioState");

	// Add new "AudioState" field.
	AddField("AudioState", sound);

} // end of SetAudioState

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetVisualState
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	lights - a int to which to set the VisualState field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetVisualState(int lights)
{
	// Delete any "VisualState" fields
	ClearFields("VisualState");

	// Add new "VisualState" field.
	AddField("VisualState", lights);

} // end of SetVisualState

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetQuitAtEnd
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	quitAtEnd - a int to which to set the QuitAtEnd field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetQuitAtEnd(int quitAtEnd)
{
	// Delete any "QuitAtEnd" fields
	ClearFields("QuitAtEnd");

	// Add new "QuitAtEnd" field.
	AddField("QuitAtEnd", quitAtEnd);

} // end of SetQuitAtEnd

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetDependent
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	dependent - a int to which to set the Dependent field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetDependent(int dependent)
{
	// Delete any "Dependent" fields
	ClearFields("Dependent");

	// Add new "Dependent" field.
	AddField("Dependent", dependent);

} // end of SetDependent

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetRefPoint
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	refPoint - index of the point which to set the RefPoint field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetRefPoint(int refPoint)
{
	// Delete any "RefPoint" fields
	ClearFields("RefPoint");

	// Add new "RefPoint" field.
	AddField("RefPoint", refPoint);

} // end of SetRefPoint


//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetColorIndex
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	refPoint - index of the point which to set the ColorIndex field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetColorIndex(int index)
{
	// Delete any "ColorIndex" fields
	ClearFields("ColorIndex");

	// Add new "ColorIndex" field.
	if (index != 0) AddField("ColorIndex", index);

} // end of SetColorIndex

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetDependentRefPoint
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	DependentRefPoint - a CPoint3D to which to set the DependentRefPoint field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetDependentRefPoint(const CPoint3D& dependentRefPoint)
{
	vector<double> dependentRefPointVec;
	// Delete any "DependentRefPoint" fields
	ClearFields("DependentRefPoint");

	// Add new "DependentRefPoint" field.
	dependentRefPointVec.push_back((double)dependentRefPoint.m_x);
	dependentRefPointVec.push_back((double)dependentRefPoint.m_y);
	dependentRefPointVec.push_back((double)dependentRefPoint.m_z);

	AddField("DependentRefPoint", dependentRefPointVec);

} // end of SetDependentRefPoint

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetDependentName
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	name - a name to which to set the DependentName field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetDependentName(const string& name)
{
	// Delete any "DependentName" fields
	ClearFields("DependentName");

	// Add new "DependentName" field.
	AddField("DependentName", name);
}

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetDependentOwnVeh
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	ownVeh - a bool to which to set the DependentOwnVeh field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetDependentOwnVeh(bool ownVeh)
{
	// Delete any "DependentOwnVeh" fields
	ClearFields("DependentOwnVeh");

	// Add new "DependentOwnVeh" field.
	AddField("DependentOwnVeh", ownVeh ? 1 : 0 );
}


//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetInitZ
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	initZ - a double to which to set the InitZ field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetInitZ(double initZ)
{
	// Delete any "InitZ" fields
	ClearFields("InitZ");

	// Add new "InitZ" field.
	AddField("InitZ", initZ);

} // end of SetInitZ

//////////////////////////////////////////////////////////////////////////////
///
/// Description: SetTraj
///	DESCRIPTION
///
/// Remarks:
///
/// Arguments:
///	trajs - a TTrajPoint vector to which to set the Traj field
///
/// Returns: void
///
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetTraj(const vector<TTrajPoint>& trajs)
{
	vector<TTrajPoint>::const_iterator itr;
	vector<double> trajsVec;

	// Delete any "Traj" fields
	ClearFields("Traj");

	// Add fields to the list
	for (itr = trajs.begin(); itr != trajs.end(); itr++) {
		trajsVec.clear();
		trajsVec.push_back(itr->x);
		trajsVec.push_back(itr->y);
		trajsVec.push_back(itr->vel);
		trajsVec.push_back(itr->i);
		trajsVec.push_back(itr->j);

		AddField("Traj", trajsVec);
	}
} // end of SetTraj

void
CDdoParseBlock::SetDirs( const vector<double>& dirs) 
{
	// Delete any "Dirs" fields
	ClearFields("Dirs");

	// Add fields to the list
	AddField("Dirs", dirs);
}
void CDdoParseBlock::SetDiGuyActionTime(const std::vector<float>& actionTimes) {
	// Delete any "Delays" fields
	ClearFields("ActionTime");

	// Add fields to the list
	AddField("ActionTime", actionTimes);
}
void CDdoParseBlock::SetDiGuyActionType(const std::vector<char>& actionTypes) {
	// Delete any "Delays" fields
	ClearFields("ActionTypes");

	// Add fields to the list
	AddField("ActionTypes", actionTypes);
}

void
CDdoParseBlock::SetDelays( const vector<double>& delays) 
{
	// Delete any "Delays" fields
	ClearFields("Delays");

	// Add fields to the list
	AddField("Delays", delays);
}

void
CDdoParseBlock::SetDirsDefault( const vector<bool>& dirs) 
{
	// Delete any "DirsDef" fields
	ClearFields("DirsDef");

	vector<int> ints;
	for (vector<bool>::const_iterator i = dirs.begin(); i != dirs.end(); i++) ints.push_back( *i ? 1 : 0 );

	// Add fields to the list
	AddField("DirsDef", ints);
}

void
CDdoParseBlock::SetInitialState(EState state)
{
	// Delete any "InitState" fields
	ClearFields("InitState");

	// Add fields to the list
	AddField("InitState", (int)state);
}

void
CDdoParseBlock::SetTrajIsGlobal(bool global)
{
	// Delete any "GlobTraj" fields
	ClearFields("GlobTraj");

	// Add fields to the list
	AddField("GlobTraj", global ? 1 : 0);
}

void
CDdoParseBlock::SetCoupledName(const string& name)
{
	// Delete any "Coupled" fields
	ClearFields("Coupled");

	// Add fields to the list
	AddField("Coupled", name);
}

void
CDdoParseBlock::SetRelativeLocation(double x, double y, double z)
{
	vector<double> vals;
	vals.push_back(x);
	vals.push_back(y);
	vals.push_back(z);

	// Delete any "RelLoc" fields
	ClearFields("RelLoc");

	// Add fields to the list
	AddField("RelLoc", vals);
}

void
CDdoParseBlock::SetRelativeOrientation(double i, double j, double k)
{
	vector<double> vals;
	vals.push_back(i);
	vals.push_back(j);
	vals.push_back(k);

	// Delete any "RelRot" fields
	ClearFields("RelRot");

	// Add fields to the list
	AddField("RelRot", vals);
}


void
CDdoParseBlock::SetInitVelocityXYZ(double x, double y, double z)
{
	vector<double> vals;
	vals.push_back(x);
	vals.push_back(y);
	vals.push_back(z);

	// Delete any "InitVelXYZ" fields
	ClearFields("InitVelXYZ");

	// Add fields to the list
	AddField("InitVelXYZ", vals);
}

void
CDdoParseBlock::SetInitVelocityRPY(double i, double j, double k)
{
	vector<double> vals;
	vals.push_back(i);
	vals.push_back(j);
	vals.push_back(k);

	// Delete any "InitVelRPY" fields
	ClearFields("InitVelRPY");

	// Add fields to the list
	AddField("InitVelRPY", vals);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetOption
//				
//
// Remarks:		
//
// Arguments: 
//   int option - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CDdoParseBlock::SetOption(int option)
{

	ClearFields("Option");

	// Add new "Option" field.
	AddField("Option", option);
}
//////////////////////////////////////////////////////////////////////////////
//
///\brief 
///		Dedicates if we are going to start a dDD0 with a given speed 
///				
///\remark
///		Dedicates if we are going to start a dDD0 with a given speed,
///		We use the equation d=1/2(a)t^2 + vt to figure out the accelarion
///		to use.
///
///
///\param	useInitVal = True  -Use an initial velocity and calculate an accelation
///\param   useInitVal = False -Use a constant velocity (default)
//
//////////////////////////////////////////////////////////////////////////////
void CDdoParseBlock::SetUseInitVelocity(bool useInitVal){
	ClearFields("UseInitVelocity");

	AddField("UseInitVelocity", useInitVal);
}
void CDdoParseBlock::SetEnableAni(bool enableAnimation){
	ClearFields("EnableAnimation");
	AddField("EnableAnimation",enableAnimation);
}

//////////////////////////////////////////////////////////////////////////////
///\brief 
///		Dedicates if we are going to take ownship acceleration into account
///				
///\remark
///		This dictates if we are going to use a 2nd (accel + vel) order or 1st order
///		(vel only) calculation for the ownship when doing dDDO's
//////////////////////////////////////////////////////////////////////////////
void CDdoParseBlock::SetAccountAccel(bool val)
{
	ClearFields("AccountAccel");
	AddField("AccountAccel",val);
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Set the initial velocity to use if the object is a dDDO
///\remark				
///		Set the initial velocity to use if the object is a dDDO, and if
///	    UseInitVelocity == TRUE  
///
///\param val intial velocity to use in MPH
//////////////////////////////////////////////////////////////////////////////
void CDdoParseBlock::SetInitdDDOVelocity(double val){
	ClearFields("InitdDDOVelocity");
	AddField("InitdDDOVelocity",val);
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Set the Max Accel the DDO is allow to use
///
///\param val fps^2
//////////////////////////////////////////////////////////////////////////////
void CDdoParseBlock::SetMaxAccel(double val){
	ClearFields("MaxAccel");
	AddField("MaxAccel",val);
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Set the Max Decel the DDO is allow to use
///
///\param val fps^2
//////////////////////////////////////////////////////////////////////////////
void CDdoParseBlock::SetMaxDecel(double val){
	ClearFields("InitdDDOVelocity");
	AddField("MaxDecel",val);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetOption
//				
//
// Remarks:		
//
// Arguments: 
//   int option - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
int
CDdoParseBlock::GetOption(void) const
{
	CSnoValue val;
	if (GetField("Option", val))
		return val.GetIntValue();
	else
		return 0;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief 
///		Dedicates if we are going to start a dDD0 with a given speed 
///				
///\remark
///		Dedicates if we are going to start a dDD0 with a given speed,
///		We use the equation d=1/2(a)t^2 + vt to figure out the accelarion
///		to use.
///
///
///\return	True  -Use an initial velocity and calculate an accelation
///\return False -Use a constant velocity 
///
//////////////////////////////////////////////////////////////////////////////
bool CDdoParseBlock::GetUseInitVelocity(void) const
{
	CSnoValue val;
	if (GetField("UseInitVelocity", val))
		return val.GetIntValue()>0;
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief 
///		Dedicates if we are going to take ownship acceleration into account
///				
///\remark
///		This dictates if we are going to use a 2nd order or 1st order 
///		calculation for the ownship when doing dDDO's
///
///
//////////////////////////////////////////////////////////////////////////////
bool CDdoParseBlock::GetAccountAccel(void) const
{
	CSnoValue val;
	if (GetField("AccountAccel", val))
		return val.GetIntValue()>0;
	else
		return false;	
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief 
///		Dedicates if the we are going to start the animation
///				
///\remark
///		Not all models have animation, this should do nothing for models
///		with-out animation
///
///\return	True  -Run the animation
///\return False -Use the first animation model 
///
//////////////////////////////////////////////////////////////////////////////
bool CDdoParseBlock::GetEnableAni(void) const
{
	CSnoValue val;
	if (GetField("EnableAnimation", val))
		return val.GetIntValue()>0;
	else
		return false;	
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Get the initial velocity to use if the object is a dDDO
///\remark				
///		Get the initial velocity to use if the object is a dDDO, and if
///	    UseInitVelocity == TRUE  
///
///\return	intial velocity to use in MPH
///
//////////////////////////////////////////////////////////////////////////////
double	CDdoParseBlock::GetInitdDDOVelocity(void) const
{
	CSnoValue val;
	if (GetField("InitdDDOVelocity", val) )
		return val.GetFloatValue();
	else
		return 0.0;	
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Get the initial velocity to use if the object is a dDDO
///
///\return	max accel in fps^2
///
//////////////////////////////////////////////////////////////////////////////

double	CDdoParseBlock::GetMaxAccel(void) const
{
	CSnoValue val;
	if (GetField("MaxAccel", val) )
		return val.GetFloatValue();
	else
		return 0.0;	
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Get the Max Decceleration the DDO is allowed to use 
///
///\return	decel in fps^2
///
//////////////////////////////////////////////////////////////////////////////
double	CDdoParseBlock::GetMaxDecel(void) const
{
	CSnoValue val;
	if (GetField("MaxDecel", val) )
		return val.GetFloatValue();
	else
		return 0.0;	
}