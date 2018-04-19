//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: triggerparseblock.cxx,v 1.33 2014/07/21 20:07:15 IOWA\dheitbri Exp $
//
// The implementation for the trigger parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

const int cFRAMES_PER_SECOND = 30;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTriggerParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: Name of the block is not set.
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTriggerParseBlock::CTriggerParseBlock()
	: CSnoBlock() {} // end of CTriggerParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTriggerParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CTriggerParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTriggerParseBlock::CTriggerParseBlock(const CTriggerParseBlock& cCopy)
{
	*this = cCopy;
} // end of CTriggerParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~TriggerParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTriggerParseBlock::~CTriggerParseBlock() {}// end of CTriggerParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTriggerParseBlock
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
CTriggerParseBlock::CTriggerParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CTriggerParseBlock

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
CTriggerParseBlock&
CTriggerParseBlock::operator=(const CTriggerParseBlock& cRhs)
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
CTriggerParseBlock::GetName(void) const
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
CTriggerParseBlock::GetPosition(void) const
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
CTriggerParseBlock::GetDrawPosition(void) const
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
CTriggerParseBlock::GetCrRad(void) const
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
CTriggerParseBlock::GetActvDel(void) const
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
CTriggerParseBlock::GetLifetime(void) const
{
	CSnoValue val;
	if (GetField("Lifetime", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetOneShot
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the OneShot field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetOneShot(void) const
{
	CSnoValue val;
	if (GetField("OneShot", val))
		return val.GetIntValue();
	else
		 return 1;
} // end of GetOneShot

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDebounce
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Debounce field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetDebounce(void) const
{
	CSnoValue val;
	if (GetField("Debounce", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetDebounce

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFireDel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the FireDelFrames field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetFireDel(void) const
{
	CSnoValue val;
	if (GetField("FireDelFrames", val))
		return val.GetIntValue() / (double)cFRAMES_PER_SECOND;
	else if (GetField("FireDel", val))
		return val.GetFloatValue();
	else
		return 0.0f;
} // end of GetFireDel

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFireDelFrames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the FireDel field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetFireDelFrames(void) const
{
	CSnoValue val;
	if (GetField("FireDelFrames", val))
		return val.GetIntValue();
	else if (GetField("FireDel", val))
		return (int)(val.GetFloatValue() * cFRAMES_PER_SECOND);
	else 
		 return 0;
} // end of GetFireDel

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTime
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Time field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetTime(void) const
{
	CSnoValue val;
	if (GetField("Time", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetTime

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFirePosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the FirePosition field.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CTriggerParseBlock::GetFirePosition(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint3D pos;
	if (GetField("FirePosition", vals)) {
		if (vals.size() != 3) {
			TCountError e("FirePosition", 3);
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
} // end of GetFirePosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetRadius
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Radius field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetRadius(void) const
{
	CSnoValue val;
	if (GetField("Radius", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetRadius

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetByNameSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the ByNameSet field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CTriggerParseBlock::GetByNameSet(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> byNameSet;
	if (GetField("ByNameSet", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			byNameSet.push_back(pVal->GetStringValue());
		}
	}
	return byNameSet;
} // end of GetByNameSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetByTypeSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the ByTypeSet field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CTriggerParseBlock::GetByTypeSet(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> byTypeSet;
	if (GetField("ByTypeSet", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			byTypeSet.push_back(pVal->GetStringValue());
		}
	}
	return byTypeSet;
} // end of GetByTypeSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetByRoadSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of pbTRoad values for the ByRoadSet field.
//
//////////////////////////////////////////////////////////////////////////////
vector<pbTRoad>
CTriggerParseBlock::GetByRoadSet(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<pbTRoad> byRoadSet;
	pbTRoad road;
	if (GetField("ByRoadSet", vals)) {
		if (vals.size() % 2 != 0) {
			TCountError e("ByRoadSet", 2);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			road.road = pVal->GetStringValue();
			pVal++;
			road.lanes = pVal->GetStringValue();
			byRoadSet.push_back(road);
		}
	}
	return byRoadSet;
} // end of GetByRoadSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetByPstnSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of pbTPstn values for the ByPstnSet field.
//
//////////////////////////////////////////////////////////////////////////////
vector<pbTPstn>
CTriggerParseBlock::GetByPstnSet(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<pbTPstn> byPstnSet;
	pbTPstn pstn;
	if (GetField("ByPstnSet", vals)) {
		if (vals.size() % 4 != 0) {
			TCountError e("ByPstnSet", 4);
			throw e;
		}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			pstn.x = pVal->GetFloatValue();
			pVal++;
			pstn.y = pVal->GetFloatValue();
			pVal++;
			pstn.z = pVal->GetFloatValue();
			pVal++;
			pstn.radius = pVal->GetFloatValue();
			byPstnSet.push_back(pstn);
		}
	}
	return byPstnSet;
} // end of GetByPstnSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the State field.
//
//////////////////////////////////////////////////////////////////////////////
string
CTriggerParseBlock::GetState(void) const
{
	CSnoValue val;
	if (GetField("State", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetState

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
CTriggerParseBlock::GetPath(void) const
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
// Description: GetNthFromStart
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the NthFromStart field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetNthFromStart(void) const
{
	CSnoValue val;
	if (GetField("NthFromStart", val))
		return val.GetIntValue();
	else
		 return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetNthFromEnd
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the NthFromEnd field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetNthFromEnd(void) const
{
	CSnoValue val;
	if (GetField("NthFromEnd", val))
		return val.GetIntValue();
	else
		 return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleAhead
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleAhead field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetVehicleAhead(void) const
{
	CSnoValue val;
	if (GetField("VehicleAhead", val))
		return val.GetIntValue();
	else
		 return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleBehind field.
//
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetVehicleBehind(void) const
{
	CSnoValue val;
	if (GetField("VehicleBehind", val))
		return val.GetIntValue();
	else
		 return 0;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleBehind field.
//
//////////////////////////////////////////////////////////////////////////////
CTriggerParseBlock::TFollowInfo
CTriggerParseBlock::GetLeaderInfo(void) const
{
	TFollowInfo info;

	CSnoValue val;
	if (GetField("LeaderType", val)) {
		info.m_type = (EFollowInfo)val.GetIntValue();
	}
	else
		info.m_type = eUNDEFINED;

	if ( eNAMED == info.m_type ) {

		CSnoValue name;
		if (GetField("LeaderName", name)) {

			info.m_name = name.GetStringValue();
		}
	}
	CSnoValue inst;
	if (GetField("LeaderInstigator", inst)) {
		info.m_instigator = (inst.GetIntValue() != 0);
	}

	return info;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFollowerInfo
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An TFollowInfo value
//
//////////////////////////////////////////////////////////////////////////////
CTriggerParseBlock::TFollowInfo
CTriggerParseBlock::GetFollowerInfo(void) const
{
	TFollowInfo info;

	CSnoValue val;
	if (GetField("FollowerType", val)) {
		info.m_type = (EFollowInfo)val.GetIntValue();
	}
	else
		info.m_type = eUNDEFINED;

//	if ( eNAMED == info.m_type ) {
		CSnoValue name;
		if (GetField("FollowerName", name)) {
			info.m_name = name.GetStringValue();
		}
//	}
	CSnoValue inst;
	if (GetField("FollowerInstigator", inst)) {
		info.m_instigator = (inst.GetIntValue() != 0);
	}

	return info;
}

////////////////////////////////////////////////////////////////////////////////
///
///
///
///
///
///
///
///////////////////////////////////////////////////////////////////////////////////
string CTriggerParseBlock::GetLeaderName()
{
	string str("");
	CSnoValue name;
	if (GetField("LeaderName", name)) {
		str = name.GetStringValue();
	}
	return str;
}

/////////////////////////////////////////////////////////////////////////////////////
///
///
///
///
///
///
///
///////////////////////////////////////////////////////////////////////////////////
string CTriggerParseBlock::GetFollowerName()
{
	string str("");
	CSnoValue name;
	if(GetField("FollowerName", name)) {
		str = name.GetStringValue();
	}
	return str;
}
////////////////////////////////////////////////////////////////////////////////
///
///
///\brief: Used for an exception
///
///\remark: Used for an exception test
///
////////////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::IsFollowTime(void) const
{
	CSnoValue val;

	if(GetField("IsTime", val)) return (val.GetIntValue()) ? true : false;
	return false;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
/// Returns whether the time radio button or distance should be selected
///
///\remark
///  if val = 0, distance is selected. If val = 1, time is selected
///
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetIsTimeOrDistance(void) const
{
	CSnoValue val;
	if(GetField("TimeOrDistance", val)) return val.GetIntValue();
	else return 0;
}

///////////////////////////////////////////////////////////////////////////////
///
///
///
///\brief: If UseExpression has value 1, it means an expression is used
///
///\remark: Use expression only if the value with UseExpression = 1. 
///
///
///
//////////////////////////////////////////////////////////////////////////////
int CTriggerParseBlock::GetUseExpression(void) const
{
	CSnoValue val;
	if(GetField("UseExpression", val)) return val.GetIntValue();
	else return 0;
}
//////////////////////////////////////////////////////////////////////////
///
///\brief: Is the Follow time expression checkbox clicked?
///
///\remark: Used to set the follow trigger dialog information
///
///
////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::IsFollowTimeExp(void) const
{
	CSnoValue val;
	if(GetField("FollowDistExp", val)) return false;
	else return true;
}

bool CTriggerParseBlock::GetIsUseExpression(void) const
{
	CSnoValue val;
	if (GetField("UseExpression", val)) {
		return (val.GetIntValue() != 0);
	}
	else return false;
}
////////////////////////////////////////////////////////////////////////////////
///
///\brief: Is the follow distance expression checkbox clicked?
///
///\remark: Used to set the follow trigger dialog information
///
///
///
///////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::IsFollowDistExp(void) const
{
	CSnoValue val;
	if(GetField("FollowTimeExp", val)) return false;
	else return true;
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief: Get the Time to set the time value in dialog for follower time
///
///
///\remark: If There is no FollowTime then it will be set to 0.
///
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetFollowTime(void) const
{
	CSnoValue val;
	if (GetField("FollowTime", val)) return val.GetFloatValue();
	else return 0.0f;
}


//////////////////////////////////////////////////////////////////////////////
///
///\brief: Get Follower distance 
///
///\remark: If there is no FollowDist then ti will be set to 0.
///
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetFollowDist(void) const
{
	CSnoValue val;
	if (GetField("FollowDist", val)) return val.GetFloatValue();
	else return 0.0f;
}

////////////////////////////////////////////////////////////////////////////
///
///\brief: Gets the expression string for follow distance
///
///\remarks: If there is no expression, it will be an empty string
///
///
//////////////////////////////////////////////////////////////////////////////
std::string
CTriggerParseBlock::GetFollowExpression(void) const
{
	CSnoValue val;
	if(GetField("FollowExpression", val)) return val.GetStringValue();
	else return "";
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleBehind field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetToleranceMinus(void) const
{
	CSnoValue val;
	if (GetField("ToleranceMinus", val)) return val.GetFloatValue();
	else return 0.0f;

}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleBehind field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetTolerancePlus(void) const
{
	CSnoValue val;
	if (GetField("TolerancePlus", val)) return val.GetFloatValue();
	else return 0.0f;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: An int value for the VehicleBehind field.
//
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetMinDuration(void) const
{
	CSnoValue val;
	if (GetField("MinDuration", val)) return val.GetFloatValue();
	else return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: UseDriverPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the UseDriverPath field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::UseDriverPath(void) const
{
	CSnoValue val;
	if (GetField("UseDriverPath", val)) return (val.GetIntValue() != 0);
	else return false;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: RequireSameLane
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the RequireSameLane field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::RequireSameLane(void) const
{
	CSnoValue val;
	if (GetField("RequireSameLane", val)) return (val.GetIntValue() != 0);
	else return false;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetSequentialActions
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A bool value for the SequentialActions field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::GetSequentialActions(void) const
{
	CSnoValue val;
	if (GetField("SeqAct", val)) return (val.GetIntValue() != 0);
	else return false;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetExpression
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Expression field.
//
//////////////////////////////////////////////////////////////////////////////
string
CTriggerParseBlock::GetExpression(void) const
{
	CSnoValue val;
	if (GetField("Expression", val)) return (val.GetStringValue());
	else return "";
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		should the trig. use a 2nd order calc for the predicate
///\remark
///		Should the trigger use a 2nd order calc for the predicate. 
///		This function is used by the TTA trigger to determine if it should
///		take accelation into account or not. 
///
///
//////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::GetUseSecondOrder(void) const
{
	CSnoValue val;
	if (GetField("Use2ndOrder", val)) return (val.GetIntValue() > 0);
	else return false;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		should the trig. use a 2nd order calc for the predicate
///\remark
///		Should the trigger use a 2nd order calc for the predicate. 
///		This function is used by the TTA trigger to determine if it should
///		take accelation into account or not. 
///
///
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetUseSecondOrder(bool val) 
{
	ClearFields("Use2ndOrder");
	// Add new "Name" field.
	AddField("Use2ndOrder", val);
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		Do we log the clossest TTA to a log stream?
///
///
//////////////////////////////////////////////////////////////////////////////
bool
CTriggerParseBlock::GetLogTTA(void) const
{
	CSnoValue val;
	if (GetField("LogTTA", val)) return (val.GetIntValue() > 0);
	else return false;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		Do we log the clossest TTA to a log stream?
///
///
//////////////////////////////////////////////////////////////////////////////
int
CTriggerParseBlock::GetTTALogNum(void) const
{
	CSnoValue val;
	if (GetField("LogTTALogNum", val)) return (val.GetIntValue());
	else return 5;
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		What is the highest speed we can assume the user will accel to?
///\remark
///		If the trigger uses a 2nd order calc for the predicate, what is the
///		highest speed we can assume the driver will accelerate too?
///
///\return The highest speed the driver should accelerate to.
//////////////////////////////////////////////////////////////////////////////
double
CTriggerParseBlock::GetUpperBoundOnSpeed(void) const
{
	CSnoValue val;
	if (GetField("UpperBoundOnSpeed", val)) 
		return val.GetFloatValue();
	else return 0;
}
//////////////////////////////////////////////////////////////////////////////
///
///
///\brief
///		Do we log the clossest TTA to a log stream?
///
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetLogTTA(bool val)  
{
	ClearFields("LogTTA");
	// Add new "Name" field.
	AddField("LogTTA", val);
}

//////////////////////////////////////////////////////////////////////////////
///
///
///\brief
///		if we are loggign the clossest TTA to a log stream, which log stream?
///
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetTTALogNum(int val) 
{
	ClearFields("LogTTALogNum");
	// Add new "Name" field.
	AddField("LogTTALogNum", val);
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///		What is the highest speed we can assume the user will accel to?
///\remark
///		If the trigger uses a 2nd order calc for the predicate, what is the
///		highest speed we can assume the driver will accelerate too?
///
///\arg	val	The highest speed the user will accelerate too
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetUpperBoundOnSpeed(double val) 
{
	ClearFields("UpperBoundOnSpeed");
	// Add new "Name" field.
	AddField("UpperBoundOnSpeed", val);
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
CTriggerParseBlock::SetName(const string& name)
{
	// Delete any "Name" fields
	ClearFields("Name");

	// Add new "Name" field.
	AddField("Name", name);

} // end of SetName

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
CTriggerParseBlock::SetDrawPosition(const CPoint3D& position)
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
CTriggerParseBlock::SetPosition(const CPoint3D& position)
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
CTriggerParseBlock::SetCrRad(double crRad)
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
CTriggerParseBlock::SetActvDel(double actvDel)
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
CTriggerParseBlock::SetLifetime(double lifetime)
{
	// Delete any "Lifetime" fields
	ClearFields("Lifetime");

	// Add new "Lifetime" field.
	AddField("Lifetime", lifetime);

} // end of SetLifetime

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOneShot
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	oneShot - a int to which to set the OneShot field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetOneShot(int oneShot)
{
	// Delete any "OneShot" fields
	ClearFields("OneShot");

	// Add new "OneShot" field.
	AddField("OneShot", oneShot);

} // end of SetOneShot

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDebounce
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	debounce - a double to which to set the Debounce field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetDebounce(double debounce)
{
	// Delete any "Debounce" fields
	ClearFields("Debounce");

	// Add new "Debounce" field.
	AddField("Debounce", debounce);

} // end of SetDebounce

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFireDel
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	fireDel - a double to which to set the FireDel field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFireDel(double fireDel)
{
	// Delete any "FireDelFrames" fields
	ClearFields("FireDelFrames");

	// Add new "FireDelFrames" field.
	AddField("FireDelFrames", (int)(fireDel * cFRAMES_PER_SECOND));

} // end of SetFireDel

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFireDelFrames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	fireDel - an int to which to set the FireDel field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFireDelFrames(int fireDel)
{
	// Delete any "FireDelFrames" fields
	ClearFields("FireDelFrames");

	// Add new "FireDelFrames" field.
	AddField("FireDelFrames", fireDel);

} // end of SetFireDelFrames

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTime
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	time - a double to which to set the Time field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetTime(double time)
{
	// Delete any "Time" fields
	ClearFields("Time");

	// Add new "Time" field.
	AddField("Time", time);

} // end of SetTime

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFirePosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	firePosition - a CPoint3D to which to set the FirePosition field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFirePosition(const CPoint3D& firePosition)
{
	vector<double> firePositionVec;
	// Delete any "FirePosition" fields
	ClearFields("FirePosition");

	// Add new "FirePosition" field.
	firePositionVec.push_back((double)firePosition.m_x);
	firePositionVec.push_back((double)firePosition.m_y);
	firePositionVec.push_back((double)firePosition.m_z);

	AddField("FirePosition", firePositionVec);

} // end of SetFirePosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetRadius
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	radius - a double to which to set the Radius field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetRadius(double radius)
{
	// Delete any "Radius" fields
	ClearFields("Radius");

	// Add new "Radius" field.
	AddField("Radius", radius);

} // end of SetRadius

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetByNameSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	byNameSets - a string vector to which to set the ByNameSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetByNameSet(const vector<string>& byNameSets)
{
	vector<string>::const_iterator itr;

	// Delete any "ByNameSet" fields
	ClearFields("ByNameSet");

	// Add fields to the list
	for (itr = byNameSets.begin(); itr != byNameSets.end(); itr++) {
		AddField("ByNameSet", *itr);
	}
} // end of SetByNameSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetByTypeSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	byTypeSets - a string vector to which to set the ByTypeSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetByTypeSet(const vector<string>& byTypeSets)
{
	vector<string>::const_iterator itr;

	// Delete any "ByTypeSet" fields
	ClearFields("ByTypeSet");

	// Add fields to the list
	for (itr = byTypeSets.begin(); itr != byTypeSets.end(); itr++) {
		AddField("ByTypeSet", *itr);
	}
} // end of SetByTypeSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetByRoadSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	byRoadSets - a pbTRoad vector to which to set the ByRoadSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetByRoadSet(const vector<pbTRoad>& byRoadSets)
{
	vector<pbTRoad>::const_iterator itr;
	vector<string> byRoadSetsVec;

	// Delete any "ByRoadSet" fields
	ClearFields("ByRoadSet");

	// Add fields to the list
	for (itr = byRoadSets.begin(); itr != byRoadSets.end(); itr++) {
		byRoadSetsVec.clear();
		byRoadSetsVec.push_back(itr->road);
		byRoadSetsVec.push_back(itr->lanes);

		AddField("ByRoadSet", byRoadSetsVec);
	}
} // end of SetByRoadSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetByPstnSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	byPstnSets - a pbTPstn vector to which to set the ByPstnSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetByPstnSet(const vector<pbTPstn>& byPstnSets)
{
	vector<pbTPstn>::const_iterator itr;
	vector<double> byPstnSetsVec;

	// Delete any "ByPstnSet" fields
	ClearFields("ByPstnSet");

	// Add fields to the list
	for (itr = byPstnSets.begin(); itr != byPstnSets.end(); itr++) {
		byPstnSetsVec.clear();
		byPstnSetsVec.push_back(itr->x);
		byPstnSetsVec.push_back(itr->y);
		byPstnSetsVec.push_back(itr->z);
		byPstnSetsVec.push_back(itr->radius);

		AddField("ByPstnSet", byPstnSetsVec);
	}
} // end of SetByPstnSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	state - a string to which to set the State field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetState(const string& state)
{
	// Delete any "State" fields
	ClearFields("State");

	// Add new "State" field.
	AddField("State", state);

} // end of SetState

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
CTriggerParseBlock::SetPath(const vector<string>& paths)
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
// Description: SetNthFromStart
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the NthFromStart field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetNthFromStart(int value)
{
	// Delete any "NthFromStart" fields
	ClearFields("NthFromStart");

	// Add new "NthFromStart" field.
	AddField("NthFromStart", value);

}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetNthFromEnd
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the NthFromEnd field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetNthFromEnd(int value)
{
	// Delete any "NthFromEnd" fields
	ClearFields("NthFromEnd");

	// Add new "NthFromEnd" field.
	AddField("NthFromEnd", value);

}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVehicleAhead
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the VehicleAhead field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetVehicleAhead(int value)
{
	// Delete any "VehicleAhead" fields
	ClearFields("VehicleAhead");

	// Add new "VehicleAhead" field.
	AddField("VehicleAhead", value);

}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVehicleBehind
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the VehicleBehind field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetVehicleBehind(int value)
{
	// Delete any "VehicleBehind" fields
	ClearFields("VehicleBehind");

	// Add new "VehicleBehind" field.
	AddField("VehicleBehind", value);

}


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetLeaderInfo
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetLeaderInfo(const TFollowInfo& info)
{
	ClearFields( "LeaderType" );
	AddField( "LeaderType", (int)info.m_type );

	ClearFields( "LeaderName" );
	if (info.m_type == eNAMED) {
		AddField( "LeaderName", info.m_name );
	}

	ClearFields( "LeaderInstigator" );
	AddField( "LeaderInstigator", info.m_instigator ? 1 : 0 );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFollowerInfo
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFollowerInfo(const TFollowInfo& info)
{
	ClearFields( "FollowerType" );
	AddField( "FollowerType", (int)info.m_type );

	ClearFields( "FollowerName" );
	if (info.m_type == eNAMED) {
		AddField( "FollowerName", info.m_name );
	}

	ClearFields( "FollowerInstigator" );
	AddField( "FollowerInstigator", info.m_instigator ? 1 : 0 );
}

/////////////////////////////////////////////////////////////////////////
///
///\brief: Is follow units for time or distance
///
///\remark: If distance, val = 0, if time, val = 1
///
///
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetIsTimeOrDistance(int val)
{
	ClearFields("TimeOrDistance");
	if(val == 0)
		AddField("TimeOrDistance", eDISTANCE);
	if(val == 1)
		AddField("TimeOrDistance", eTIME);
}

//////////////////////////////////////////////////////////////////////////////
///
///
///\brief: Is an expression used for the follower trigger
///
///\remark: if using expression, UseExpression has value 1
///
///
/////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetUseExpression(bool val)
{
	ClearFields("UseExpression");

	if(val == true)
		AddField("UseExpression", val ? 1 : 0);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFollowTime
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the FollowTime field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFollowTime(double val)
{
	ClearFields("FollowTime");

	AddField("FollowTime", val);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFollowDist
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the FollowDist field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFollowDist(double val)
{
	ClearFields("FollowDist");

	AddField("FollowDist", val);
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief: writes expression to parse block
///
///\remark: 
///
///
///
///\param[in] str
///////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetFollowExpression(const std::string& str)
{
	ClearFields("FollowExpression");

	AddField("FollowExpression", str);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetToleranceMinus
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the ToleranceMinus field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetToleranceMinus(double val)
{
	ClearFields("ToleranceMinus");

	AddField("ToleranceMinus", val);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTolerancePlus
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the TolerancePlus field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetTolerancePlus(double val)
{
	ClearFields("TolerancePlus");

	AddField("TolerancePlus", val);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetMinDuration
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - an int to which to set the MinDuration field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetMinDuration(double val)
{
	ClearFields("MinDuration");

	AddField("MinDuration", val);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetUseDriverPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - a bool to which to set the UseDriverPath field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetUseDriverPath(bool val)
{
	ClearFields("UseDriverPath");

	AddField("UseDriverPath", val ? (int)1 : (int)0);
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: RequireSameLane
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - a bool to which to set the RequireSameLane field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetRequireSameLane(bool val)
{
	ClearFields("RequireSameLane");

	AddField("RequireSameLane", val ? (int)1 : (int)0);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetSequentialActions
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	value - a bool to which to set the SeqAct field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetSequentialActions(bool val)
{
	ClearFields("SeqAct");

	AddField("SeqAct", val ? (int)1 : (int)0);
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetExpression
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	expr - a string to which to set the Expression field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetExpression(const string& expr)
{
	ClearFields("Expression");

	AddField("Expression", expr);
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: SetExpression
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	expr - a string to which to set the Expression field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTriggerParseBlock::SetWithinPercentSpeed(const double val)
{
	ClearFields("WithinPercentSpeed");

	AddField("WithinPercentSpeed", val);
}


double CTriggerParseBlock::GetWithinPercentSpeed(void) const{
	CSnoValue val;
	if (GetField("WithinPercentSpeed", val))
		return val.GetFloatValue();
	else
		 return 0.10f;
}

