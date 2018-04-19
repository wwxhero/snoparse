/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     January, 1999
//
// $Id: headerparseblock.cxx,v 1.52 2018/03/22 22:14:05 IOWA\dheitbri Exp $
//
// The implementation for the header parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include <assert.h>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CHeaderParseBlock
// 	Default constructor calls the superclass default constructor.
//
// Remarks: The name of the block is set to "Header"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CHeaderParseBlock::CHeaderParseBlock()
	: CSnoBlock()
{
	SetBlockName("Header");
} // end of CHeaderParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CHeaderParseBlock
// 	Copy constructor assigns the parameter to the current instance.
//
// Remarks:
//
// Arguments:
// 	cCopy - CHeaderParseBlock to copy
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CHeaderParseBlock::CHeaderParseBlock(const CHeaderParseBlock& cCopy) {
	*this = cCopy;
} // end of CHeaderParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~CHeaderParseBlock
// 	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CHeaderParseBlock::~CHeaderParseBlock() {} // end of ~CHeaderParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CHeaderParseBlock
// 	Creates a CHeaderParseBlock from a CSnoBlock.
//
// Remarks:	This function parses out all the fields in a CSnoBlock and places
//	them in the proper fields of the CSnoBlock superclass instance.
//
// Arguments:
//   blk - The HCSM initialization information from the parser.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CHeaderParseBlock::CHeaderParseBlock(const CSnoBlock &blk)
		: CSnoBlock(blk) {} // end of CHeaderParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: operator=
// 	The assignment operator calls the superclass assignment operator
//
// Remarks: Copies the instance of CHeaderParseBlock that's passed
//   in as argument.
//
// Arguments:
//   objToCopy -- The object to copy.
//
// Returns: A reference to iteslf to allow for nexted assignments.
//
//////////////////////////////////////////////////////////////////////////////

CHeaderParseBlock &
CHeaderParseBlock::operator=( const CHeaderParseBlock& objToCopy )
{
	// check to make sure that object passed in is not me
	if ( this != &objToCopy ) {

		// Call superclass assignment operator
		CSnoBlock::operator=( objToCopy );
	}
	return *this;
} // end of operator=


//////////////////////////////////////////////////////////////////////////////
//	Accessor functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDate
// 	Returns the value of the field named "Date" which was parsed by the
// 	constructor.
//
// Remarks: The "Date" field is used to mark the date that a scenario file
// 	was created.
//
// Arguments:
//
// Returns: A string containing the date, in no particular format.  If no
// 	date was specified, the function returns an empty string.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetDate(void) const
{
	CSnoValue val;
	if (GetField("Date", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetDate

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetOtherTerrain
// 	Returns the value of the field named "OtherTerrain" which was parsed by the
// 	constructor.
//
// Remarks:
//
// Arguments:
//
// Returns: A string containing the OtherTerrain field
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetOtherTerrain(void) const
{
	CSnoValue val;
	if (GetField("OtherTerrain", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetOtherTerrain
string	CHeaderParseBlock::GetVisualSettings(void) const
{
	CSnoValue val;
	if (GetField("VisualSettings", val))
		return val.GetStringValue();
	else
		 return "";
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetShortComment
// 	Returns the value of the field named "ShortComment" which was parsed by
// 	the constructor.
//
// Remarks: The "ShortComment" field is used to make comments about a
// 	scenario file.
//
// Arguments:
//
// Returns: A string containing the short comment.  If no short comment was
// 	specified, the function returns an empty string.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetShortComment(void) const
{
	CSnoValue val;
	if (GetField("ShortComment", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetShortComment

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetLongComment
// 	Returns the value of all the field named "LongComment" which were parsed
// 	by the constructor.
//
// Remarks: The "LongComment" field is used to make comments about a
// 	scenario file.
//
// Arguments:
//
// Returns: A string containing the concatenated values from the long comment
// 	fields, separated by carriage returns.  If no long comments were
// 	specified, the function returns an empty string.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetLongComment(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	string comment;
	if (GetField("LongComment", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			comment += pVal->GetStringValue();
			if (pVal != vals.end())
				comment += "\r\n";
		}
	}
	return comment;
} // end of GetLongComment

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetLriFile
// 	Returns the value of the field named "LriFile" which was parsed by
// 	the constructor.
//
// Remarks: The "LriFile" field is the only required field in the Header
// 	block.  It specifies the name of the file containing the compiled logical
// 	road information.
//
// Arguments:
//
// Returns: A string containing the name of the lri file.  If no lri file was
// 	specified, the function returns an empty string.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetLriFile(void) const
{
	CSnoValue val;
	if (GetField("LriFile", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetLriFile


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCabSolObjName
// 	Returns the value of the field named "CabType" which was parsed by
// 	the constructor.
//
// Remarks: The "CabType" field specifies the name of the cab to be used in
//  the scenario.  Can be one of "Taurus", "Jeep", "Malibu", or "Truck"
//
// Arguments:
//
// Returns:	A string containing the cab type.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetCabSolObjName(void) const
{
	CSnoValue val;
	if (GetField("CabType", val)){
        if (val.GetStringValue().size() > 0)
            return val.GetStringValue();
        else{
            return "NadsCabMalibu";
        }
    }
	else
		return "NadsCabMalibu";
}

bool
CHeaderParseBlock::GetShowCab(void) const
{
	CSnoValue val;
	if (GetField("ShowCab", val))
		return val.GetIntValue() > 0;
	else
		return true;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTrailerSolObjName
// 	Returns the value of the field named "TrailerType" which was parsed by
// 	the constructor.
//
// Remarks: The "TrailerType" field specifies the name of the trailer to be towed
//  by the ext. driver
//
// Arguments:
//
// Returns:	A string containing the Trailer type.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetTrailerSolObjName(void) const{
	CSnoValue val;
	if (GetField("TrailerType", val))
		return val.GetStringValue();
	else
		return "";
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetMotionDriveFilename
// 	Returns the value of the field named "MotionDrive" which was parsed by
// 	the constructor.
//
// Remarks: The "MotionDrive" field specifies the filename that contains the
//  motion drive parameter file
//
// Arguments:
//
// Returns:	A string containing the filename.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetMotionDriveFilename(void) const
{
	CSnoValue val;
	if (GetField("MotionDrive", val))
		return val.GetStringValue();
	else
		return "NadsCabMalibu";
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetMotionSettingsFilename
// 	Returns the value of the field named "MotionSettings" which was parsed by
// 	the constructor.
//
// Remarks: The "MotionSettings" field specifies the filename that contains the
//  motion setting parameter file
//
// Arguments:
//
// Returns:	A string containing the filename.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetMotionSettingsFilename(void) const
{
	CSnoValue val;
	if (GetField("MotionSettings", val))
		return val.GetStringValue();
	else
		return "";
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCollisionSimulation
// 	Returns the value of the field named "CollisionSimulation" which was parsed by
// 	the constructor.
//
// Remarks: The "CollisionSimulation" field specifies the method by which to
//  simulate a collision.
//
// Arguments:
//
// Returns:	A string containing the method.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetCollisionSimulation(void) const
{
	CSnoValue val;
	if (GetField("CollisionSimulation", val))
		return val.GetStringValue();
	else
		return "";
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetOwnVehPos
// 	Returns the value of the field named "OwnVehiclePosition" which was parsed by
// 	the constructor.
//
// Remarks: The "OwnVehiclePosition" field specifies the position of the own
//  vehicle at the start of the simulation.
//
// Arguments:
//
// Returns:	A CPoint3D containing the initial position.
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CHeaderParseBlock::GetOwnVehPos(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint3D pos;
	if (GetField("OwnVehiclePosition", vals)) {
		if (vals.size() != 3) {
			TCountError e("OwnVehiclePosition", 3);
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
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: HasOwnVeh
// 	Returns true if there is an own vehicle specification in the header
//
// Remarks: .
//
// Arguments:
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
bool
CHeaderParseBlock::HasOwnVeh(void) const
{
	vector<CSnoValue> vals;
	CPoint3D pos;
	if (GetField("OwnVehiclePosition", vals)) {
		return true;
	} else {
		return false;
	}
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetOwnVehOri
// 	Returns the value of the field named "OwnVehicleOrientation" which was parsed by
// 	the constructor.
//
// Remarks: The "OwnVehicleOrientation" field specifies the orientation of the own
//  vehicle at the start of the simulation.
//
// Arguments:
//
// Returns:	A CVector3D containing the initial orientation.
//
//////////////////////////////////////////////////////////////////////////////
CVector3D
CHeaderParseBlock::GetOwnVehOri(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CVector3D vec;
	if (GetField("OwnVehicleOrientation", vals)) {
		if (vals.size() != 3) {
			TCountError e("OwnVehicleOrientation", 3);
			throw e;
		}
		pVal = vals.begin();
		vec.m_i = pVal->GetFloatValue();
		pVal++;
		vec.m_j = pVal->GetFloatValue();
		pVal++;
		vec.m_k = pVal->GetFloatValue();
		pVal++;
	}
	return vec;
}






//////////////////////////////////////////////////////////////////////////////
//
// Description: GetMotionScenarioPosition
// 	Returns the value of the field named "MotionScenarioPosition" which was
//  parsed by the constructor.
//
// Remarks: The "MotionScenarioPosition" field specifies the default position
//  of the motion subsystem.
//
// Arguments:
//
// Returns:	A CPoint3D containing the initial position.
//
//////////////////////////////////////////////////////////////////////////////
CHeaderParseBlock::TMotionPosition
CHeaderParseBlock::GetMotionScenarioPosition(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	TMotionPosition pos;
	if (GetField("MotionScenarioPosition", vals)) {
		if (vals.size() != 9) {
			TCountError e("MotionScenarioPosition", 3);
			throw e;
		}
		pVal = vals.begin();
		pos.m_crossbeamX = pVal->GetFloatValue();
		pVal++;
		pos.m_carriageY = pVal->GetFloatValue();
		pVal++;
		pos.m_hexX = pVal->GetFloatValue();
		pVal++;
		pos.m_hexY = pVal->GetFloatValue();
		pVal++;
		pos.m_hexZ = pVal->GetFloatValue();
		pVal++;
		pos.m_hexRoll = pVal->GetFloatValue();
		pVal++;
		pos.m_hexPitch = pVal->GetFloatValue();
		pVal++;
		pos.m_hexYaw = pVal->GetFloatValue();
		pVal++;
		pos.m_turntable = pVal->GetFloatValue();
		pVal++;
	}
	return pos;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInitialTireConditions
// 	Returns the value of the field named "GetInitialTireConditions" which was
//  parsed by the constructor.
//
// Remarks: The "GetInitialTireConditions" field specifies the initial
//  conditions of each tire.  Possible values:
//  1 - Normal
//  2 - Worn Tire Tread
//  3 - Over inflated tire pressure
//  4 - Under inflated tire pressure
//
// Arguments:
//
// Returns:	A vector of conditions.
//
//////////////////////////////////////////////////////////////////////////////
vector<int>
CHeaderParseBlock::GetInitialTireConditions(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<int> retVal;
	if (GetField("InitialTireConditions", vals)) {
		if (vals.size() != 10) {
			TCountError e("InitialTireConditions", 10);
			throw e;
		}
		for(pVal = vals.begin(); pVal != vals.end(); pVal++)
			retVal.push_back( pVal->GetIntValue() );
	} else {
		retVal.resize( 10, 1 );
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInitialBrakeConditions
// 	Returns the value of the field named "GetInitialBrakeConditions" which was
//  parsed by the constructor.
//
// Remarks: The "InitialBrakeConditions" field specifies the initial
//  conditions of each brake.  Possible values:
//  1 - Normal
//  2 - Partially Failed Brake
//  3 - Fully Failed Brake
//
// Arguments:
//
// Returns:	A vector of conditions.
//
//////////////////////////////////////////////////////////////////////////////
vector<int>
CHeaderParseBlock::GetInitialBrakeConditions(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<int> retVal;
	if (GetField("InitialBrakeConditions", vals)) {
		if (vals.size() != 11) {
			TCountError e("InitialBrakeConditions", 11);
			throw e;
		}
		for(pVal = vals.begin(); pVal != vals.end(); pVal++)
			retVal.push_back( pVal->GetIntValue() );
	} else {
		retVal.resize( 11, 1 );
		retVal[0] = 0;
	}
	return retVal;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDaqFile
// 	Returns the value of the field named "DaqFile" which was parsed by
// 	the constructor.
//
// Remarks: The "DaqFile" field is used to specify the file used by the DAQ
//
// Arguments:
//
// Returns: A string containing the DAQ file.  If no DAQ file was
// 	specified, the function returns an empty string.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetDaqFile(void) const
{
	CSnoValue val;
	if (GetField("DaqFile", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetDaqFile


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetScenPosX
// 	Returns the value of the field named "ScenPosX" which was parsed by
// 	the constructor.
//
// Remarks: The "ScenPosX" field is used to keep the last position for the ISAT
//
// Arguments:
//
// Returns: A double containing the ScenPosX.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetScenPosX(void) const
{
	CSnoValue val;
	if (GetField("ScenPosX", val))
		return val.GetFloatValue();
	else
		 return 0.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetScenPosY
// 	Returns the value of the field named "ScenPosY" which was parsed by
// 	the constructor.
//
// Remarks: The "ScenPosY" field is used to keep the last position for the ISAT
//
// Arguments:
//
// Returns: A double containing the ScenPosY.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetScenPosY(void) const
{
	CSnoValue val;
	if (GetField("ScenPosY", val))
		return val.GetFloatValue();
	else
		 return 0.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetScenZoom
// 	Returns the value of the field named "ScenZoom" which was parsed by
// 	the constructor.
//
// Remarks: The "ScenZoom" field is used to keep the last position for the ISAT
//
// Arguments:
//
// Returns: A double containing the ScenZoom.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetScenZoom(void) const
{
	CSnoValue val;
	if (GetField("ScenZoom", val))
		return val.GetFloatValue();
	else
		 return -1;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetBliPath
// 	Returns the value of the field named "BliPath" which was parsed by
// 	the constructor.
//
// Remarks: The "BliPath" field is used to specify the file used by the DAQ
//
// Arguments:
//
// Returns: A string containing the path to the bli.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderParseBlock::GetBliPath(void) const
{
	CSnoValue val;
	if (GetField("BliPath", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetBliPath

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
CHeaderParseBlock::GetPath(void) const
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
// Description: GetReadCellNames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the CellName field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CHeaderParseBlock::GetReadCellNames(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> cellNames;
	if (GetField("CellName", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			cellNames.push_back(pVal->GetStringValue());
		}
	}
	return cellNames;
} // end of GetPath


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetWriteCellNames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the WriteCellName field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CHeaderParseBlock::GetWriteCellNames(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> cellNames;
	if (GetField("WriteCellName", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			cellNames.push_back(pVal->GetStringValue());
		}
	}
	return cellNames;
} // end of GetPath


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTextObjs
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the TextObjs field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CHeaderParseBlock::GetTextObjs(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> textObjs;
	if (GetField("TextObjs", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			textObjs.push_back(pVal->GetStringValue());
		}
	}
	return textObjs;
} // end of GetTextObjs

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetPreloadFiles
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of string values for the PreloadFiles field.
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CHeaderParseBlock::GetPreloadFiles(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> files;
	if (GetField("PreloadFiles", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			files.push_back(pVal->GetStringValue());
		}
	}
	return files;
} // end of GetPreloadFiles


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVibrationSpec
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of double values for the VibrationSpec field.
//
//////////////////////////////////////////////////////////////////////////////
vector<double>
CHeaderParseBlock::GetVibrationSpec(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<double> vibObjs;
	if (GetField("VibrationSpec", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			vibObjs.push_back(pVal->GetFloatValue());
		}
	}
	return vibObjs;
} // end of GetVibrationSpec


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetSavedCoords
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of double values for the SavedCoords field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CHeaderParseBlock::TCoordSave>
CHeaderParseBlock::GetSavedCoords(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TCoordSave> coordObjs;
	coordObjs.resize( 10 );
	int count = 0;
	if (GetField("SavedCoords", vals)) {
		// Assemble values
		pVal = vals.begin();
		for (count = 0; count < 10; count++) {
			TCoordSave save;
			save.m_used = (pVal->GetFloatValue() > 0);
			pVal++;
			if (save.m_used) {
				save.m_x = pVal->GetFloatValue();
				pVal++;
				save.m_y = pVal->GetFloatValue();
				pVal++;
				save.m_z = pVal->GetFloatValue();
				pVal++;
				save.m_zoom = pVal->GetFloatValue();
				pVal++;
			}
			coordObjs[count] = save;
		}
	}
	return coordObjs;
} // end of GetSavedCoords

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetExtRef
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of TExtRef fields for the ExtRef field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CHeaderParseBlock::TExtRef>
CHeaderParseBlock::GetExtRefs(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TExtRef> extRefs;
	int count = 0;
	if (GetField("ExtRef", vals)) {
		// Assemble values
		pVal = vals.begin();
		while (pVal != vals.end() ) {
			TExtRef ref;
			ref.m_fileName = pVal->GetStringValue();
			pVal++;
			ref.m_groupName = pVal->GetStringValue();
			pVal++;
			extRefs.push_back( ref );
		}
	}
	return extRefs;
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: GetBlanking
// 	Returns the value of the field named "Blanking" which was parsed by
// 	the constructor.
//
// Remarks:
//
// Arguments:
//
// Returns: A double containing the ScenZoom.
//
//////////////////////////////////////////////////////////////////////////////
bool
CHeaderParseBlock::GetBlanking(void) const
{
	CSnoValue val;
	if (GetField("Blanking", val))
		return val.GetIntValue() != 0;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsOn
// 	Returns the value of the field named "HeadlightsOn" which was parsed by
// 	the constructor.
//
// Remarks:
//
// Arguments:
//
// Returns: True if the headlights should be on.
//
//////////////////////////////////////////////////////////////////////////////
bool
CHeaderParseBlock::GetHeadlightsOn(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsOn", val))
		return val.GetIntValue() != 0;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsAzimuth
// 	Returns the value of the field named "HeadlightsAzimuth" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsAzimuth" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsAzimuth.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsAzimuth(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsAzimuth", val))
		return val.GetFloatValue();
	else
		 return 2.5;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsElevation
// 	Returns the value of the field named "HeadlightsElevation" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsElevation" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsElevation.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsElevation(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsElevation", val))
		return val.GetFloatValue();
	else
		 return -2.5;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsBeamHeight
// 	Returns the value of the field named "HeadlightsBeamHeight" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsBeamHeight" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsBeamWidth.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsBeamHeight(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsBeamHeight", val))
		return val.GetFloatValue();
	else
		 return 5.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsBeamWidth
// 	Returns the value of the field named "HeadlightsBeamWidth" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsBeamWidth" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsBeamWidth.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsBeamWidth(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsBeamWidth", val))
		return val.GetFloatValue();
	else
		 return 18.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsConstCoeff
// 	Returns the value of the field named "HeadlightsConstCoeff" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsConstCoeff" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsConstCoeff.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsConstCoeff(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsConstCoeff", val))
		return val.GetFloatValue();
	else
		 return 1.0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsLinearCoeff
// 	Returns the value of the field named "HeadlightsLinearCoeff" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsConstCoeff" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsLinearCoeff.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsLinearCoeff(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsLinearCoeff", val))
		return val.GetFloatValue();
	else
		 return 0.01;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsQuadCoeff
// 	Returns the value of the field named "HeadlightsQuadCoeff" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsQuadCoeff" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsQuadCoeff.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsQuadCoeff(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsQuadCoeff", val))
		return val.GetFloatValue();
	else
		 return 0.001;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsHeightFade
// 	Returns the value of the field named "HeadlightsHeightFade" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsHeightFade" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsHeightFade.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsHeightFade(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsHeightFade", val))
		return val.GetFloatValue();
	else
		return 2.0;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsCutOffDist
// 	Returns the value of the field named "HeadlightsHeightFade" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsCutOffDist" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double in feet, expressing the light source cut off dist.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsCutOffDist(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsCutOffDist", val))
		return val.GetFloatValue();
	else
		return 400.0;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsHeightFade
// 	Returns the value of the field named "HeadlightsHeightFade" which was parsed by
// 	the constructor.
//
// Remarks: The "AmbientLightInt" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsHeightFade.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetAmbientLightInt(void) const
{
	CSnoValue val;
	if (GetField("AmbientLightInt", val))
		return val.GetFloatValue();
	else
		return 1.0;
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///    Gets the HeadlightLampSeparation field
///\remark
///		The headlamp speration field controls the distance between headlamp
///		light sources.
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightLampSeparation(void) const
{
	CSnoValue val;
	if (GetField("HeadlightLampSeparation", val))
		return val.GetFloatValue();
	else
		return 3.5;
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///    Gets the HeadlightForwardOffset field
///\remark
///		The headlamp speration field controls the distance between headlamp
///		eyepoint pos.
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightForwardOffset(void) const
{
	CSnoValue val;
	if (GetField("HeadlightForwardOffset", val))
		return val.GetFloatValue();
	else
		return 6.6;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsIntensity
// 	Returns the value of the field named "HeadlightsIntensity" which was parsed by
// 	the constructor.
//
// Remarks: The "HeadlightsIntensity" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsIntensity.
//
//////////////////////////////////////////////////////////////////////////////
double
CHeaderParseBlock::GetHeadlightsIntensity(void) const
{
	CSnoValue val;
	if (GetField("HeadlightsIntensity", val))
		return val.GetFloatValue();
	else
		return 65.0;
}


//////////////////////////////////////////////////////////////////////////////
//	Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOtherTerrain
// 	Sets the value of the field named "OtherTerrain" to the value of the parameter.
//
// Remarks:
//
// Arguments:
//	other - A string containing the OtherTerrain field, in no particular format.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetOtherTerrain(const string& other)
{
	// Delete any "OtherTerrain" fields
	ClearFields("OtherTerrain");

	// Add new "OtherTerrain" field.
	AddField("OtherTerrain", other);

} // end of SetOtherTerrain
void
CHeaderParseBlock::SetVisualSettings(const string &settings){
	// Delete any "OtherTerrain" fields
	ClearFields("VisualSettings");

	// Add new "OtherTerrain" field.
	AddField("VisualSettings", settings);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDate
// 	Sets the value of the field named "Date" to the value of the parameter.
//
// Remarks: The "Date" field is used to mark the date that a scenario file
// 	was created.
//
// Arguments:
//	date - A string containing the date, in no particular format.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetDate(const string& date)
{
	// Delete any "Date" fields
	ClearFields("Date");

	// Add new "Date" field.
	AddField("Date", date);

} // end of SetDate

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetShortComment
// 	Sets the value of the field named "ShortComment" to the value of the
// 	parameter.
//
// Remarks: The "ShortComment" field is used to make comments about a
// 	scenario file.  This should contain no line breaks, and if it does,
// 	SetLongComment should be used instead.
//
// Arguments:
//	comment - A string containing the short comment.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetShortComment(const string& comment)
{
	// Delete any "ShortComment" fields
	ClearFields("ShortComment");

	// Add new "ShortComment" field.
	AddField("ShortComment", comment);

} // end of SetShortComment

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetLongComment
// 	Sets the value of the field named "LongComment" to the value of the
// 	parameter.
//
// Remarks: The "LongComment" field is used to make comments about a
// 	scenario file.  If the string contains line breaks, it is parsed into
// 	several strings and added as several field values.
//
// Arguments:
//	comment - A string containing the long comment.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetLongComment(const string& comment)
{
	// Parse parameter into strings divided by line breaks.
	char *pComment = new char[strlen(comment.c_str())+1];
	char *pTokDel = "\n\r";
	char *pTok;
	char *pCurrPos = NULL;
	strcpy(pComment, comment.c_str());

	// Delete any existing fields from the list.
	ClearFields("LongComment");

	pTok = strtok_s(pComment, pTokDel,&pCurrPos);
	if (pTok) {
		do {

			// Initialize the field with the token
			string c(pTok);

			// Add it to the list
			AddField("LongComment", c);

		} while ((pTok = strtok_s(NULL, pTokDel,&pCurrPos)) != NULL);
	}

} // end of SetLongComment

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetLriFile
// 	Sets the value of the field named "LriFile" to the value of the parameter.
//
// Remarks: The "LriFile" field is the only required field in the Header
// 	block.  It specifies the name of the file containing the compiled logical
// 	road information.
//
// Arguments:
//	file - A string containing the file name.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetLriFile(const string& file)
{
	// Delete any "LriFile" fields
	ClearFields("LriFile");

	// Add new "LriFile" field.
	AddField("LriFile", file);

} // end of SetLriFile


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCabSolObjName
//  Sets the value of the field named "CabType" to the value of the parameter
//
// Remarks: The "CabType" field specifies the name of the cab to be used in
//  the scenario.  Can be one of "Taurus", "Jeep", "Malibu", or "Truck"
//
// Arguments:
//   cab - A string containing the cab type.
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetCabSolObjName(const string& cab)
{
	// Delete any "CabType" fields
	ClearFields("CabType");

	// Add new "CabType" field.
	AddField("CabType", cab);

} // end of SetCabType
void
CHeaderParseBlock::SetShowCab(bool isShow){
	// Delete any "CabType" fields
	ClearFields("ShowCab");

	int val;
	if (isShow)
		val = 1;
	else
		val = 0;
	// Add new "ShowCab" field.
	AddField("ShowCab", val);

}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTrailerSolObjName
//  Sets the value of the field named "TrailerType" to the value of the parameter
//
// Remarks: The "TrailerType" field specifies the name of the Trailer to be towed
//  by the Ext.Driver
//
// Arguments:
//   trailer - A string containing the trailer type.
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetTrailerSolObjName(const string& trailer){
	// Delete any "TrailerType" fields
	ClearFields("TrailerType");

	// Add new "TrailerType" field.
	AddField("TrailerType", trailer);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetMotionDriveFilename
//  Sets the value of the field named "MotionDrive" to the value of the parameter
//
// Remarks: The "MotionDrive" field specifies the filename that contains the
//  motion drive parameter file
//
// Arguments:
//	filename - A string containing the filename.
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetMotionDriveFilename(const string& filename)
{
	// Delete any "MotionDrive" fields
	ClearFields("MotionDrive");

	// Add new "MotionDrive" field.
	AddField("MotionDrive", filename);

} // end of SetMotionDriveFilename


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetMotionSettingsFilename
//  Sets the value of the field named "MotionSettings" to the value of the parameter
//
// Remarks: The "MotionSettings" field specifies the filename that contains the
//  motion setting parameter file
//
// Arguments:
//  filename - A string containing the filename.
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetMotionSettingsFilename(const string& filename)
{
	// Delete any "MotionSettings" fields
	ClearFields("MotionSettings");

	// Add new "MotionSettings" field.
	AddField("MotionSettings", filename);

} // end of SetMotionSettingsFilename

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCollisionSimulation
// 	Sets the value of the field named "CollisionSimulation" to the value of the
//  parameter
//
// Remarks: The "CollisionSimulation" field specifies the method by which to
//  simulate a collision.
//
// Arguments:
//  method - A string containing the method.
//
// Returns:
//
void
CHeaderParseBlock::SetCollisionSimulation(const string& method)
{
	// Delete any "CollisionSimulation" fields
	ClearFields("CollisionSimulation");

	// Add new "CollisionSimulation" field.
	AddField("CollisionSimulation", method);

} // end of SetCollisionSimulation


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOwnVehPos
//  Sets the value of the field named "OwnVehiclePosition" to the value of
//  the parameter
//
// Remarks: The "OwnVehiclePosition" field specifies the position of the own
//  vehicle at the start of the simulation.
//
// Arguments:
//	position - A CPoint3D containing the initial position.
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetOwnVehPos(const CPoint3D& position)
{
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("OwnVehiclePosition");

	// Add new "Position" field.
	positionVec.push_back((double)position.m_x);
	positionVec.push_back((double)position.m_y);
	positionVec.push_back((double)position.m_z);

	AddField("OwnVehiclePosition", positionVec);

} // end of SetPosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetOwnVehOri
//  Sets the value of the field named "OwnVehicleOrientation" to the value of
//  the parameter
//
// Remarks: The "OwnVehicleOrientation" field specifies the orientation of the own
//  vehicle at the start of the simulation.
//
// Arguments:
//	position - A CPoint3D containing the initial orientation.
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetOwnVehOri(const CVector3D& position)
{
	vector<double> orientationVec;
	// Delete any "Position" fields
	ClearFields("OwnVehicleOrientation");

	// Add new "Position" field.
	orientationVec.push_back((double)position.m_i);
	orientationVec.push_back((double)position.m_j);
	orientationVec.push_back((double)position.m_k);

	AddField("OwnVehicleOrientation", orientationVec);

} // end of SetPosition

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetMotionScenarioPosition
//  Sets the value of the field named "MotionScenarioPosition" to the value of
//  the parameter
//
// Remarks: The "MotionScenarioPosition" field specifies the default position
//  of the motion subsystem.
//
// Arguments:
//  position - A CPoint3D containing the initial position.
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetMotionScenarioPosition(const CHeaderParseBlock::TMotionPosition& position)
{
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("MotionScenarioPosition");

	// Add new "Position" field.
	positionVec.push_back(position.m_crossbeamX);
	positionVec.push_back(position.m_carriageY);
	positionVec.push_back(position.m_hexX);
	positionVec.push_back(position.m_hexY);
	positionVec.push_back(position.m_hexZ);
	positionVec.push_back(position.m_hexRoll);
	positionVec.push_back(position.m_hexPitch);
	positionVec.push_back(position.m_hexYaw);
	positionVec.push_back(position.m_turntable);

	AddField("MotionScenarioPosition", positionVec);

} // end of SetPosition


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInitialTireConditions
//  Sets the value of the field named "InitialTireConditions" to the value of
//  the parameter
//
// Remarks: The "InitialTireConditions" field specifies the initial conditions
//  of the tires.
//  1 - Normal
//  2 - Worn Tire Tread
//  3 - Over inflated tire pressure
//  4 - Under inflated tire pressure
// Arguments:
//  cond - a vector of conditions (one per tire).
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetInitialTireConditions(const vector<int>& cond)
{
	// Delete any "InitialTireConditions" fields
	ClearFields("InitialTireConditions");

	AddField("InitialTireConditions", cond);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInitialBrakeConditions
// 	Sets the value of the field named "GetInitialBrakeConditions" to the value
//   of the parameter
//
// Remarks: The "InitialBrakeConditions" field specifies the initial
//  conditions of each brake.  Possible values:
//  1 - Normal
//  2 - Partially Failed Brake
//  3 - Fully Failed Brake
//
// Arguments:
//  cond - A vector of conditions (one per tire).
//
// Returns:
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetInitialBrakeConditions(const vector<int>& cond)
{
	// Delete any "InitialBrakeConditions" fields
	ClearFields("InitialBrakeConditions");

	AddField("InitialBrakeConditions", cond);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDaqFile
// 	Sets the value of the field named "DaqFile" to the value of the
// 	parameter.
//
// Remarks: The "DaqFile" field is used to specify the file used in the DAQ.
//
// Arguments:
//	comment - A string containing the DAQ file.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetDaqFile(const string& comment)
{
	// Delete any "DaqFile" fields
	ClearFields("DaqFile");

	// Add new "DaqFile" field.
	AddField("DaqFile", comment);

} // end of SetDaqFile

void
CHeaderParseBlock::SetScenPosX(double val)
{
	// Delete any "ScenPosX" fields
	ClearFields("ScenPosX");

	// Add new "ScenPosX" field.
	AddField("ScenPosX", val);

}

void
CHeaderParseBlock::SetScenPosY(double val)
{
	// Delete any "ScenPosY" fields
	ClearFields("ScenPosY");

	// Add new "ScenPosY" field.
	AddField("ScenPosY", val);

}

void
CHeaderParseBlock::SetScenZoom(double val)
{
	// Delete any "ScenZoom" fields
	ClearFields("ScenZoom");

	// Add new "ScenZoom" field.
	AddField("ScenZoom", val);

}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetBliPath
// 	Sets the value of the field named "BliPath" to the value of the
// 	parameter.
//
// Remarks: The "BliPath" field is used to specify the directory containing
//  the bli that the simop will copy to $NADSSDC_BLI.
//
// Arguments:
//	comment - A string containing the directory.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetBliPath(const string& path)
{
	// Delete any "BliPath" fields
	ClearFields("BliPath");

	// Add new "BliPath" field.
	AddField("BliPath", path);

} // end of SetBliPath



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
CHeaderParseBlock::SetPath(const vector<string>& paths)
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
// Description: SetReadCellNames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a string vector to which to set the CellName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetReadCellNames(const vector<string>& cellNames)
{
	vector<string>::const_iterator itr;

	// Delete any "CellName" fields
	ClearFields("CellName");

	// Add fields to the list
	for (itr = cellNames.begin(); itr != cellNames.end(); itr++) {
		AddField("CellName", *itr);
	}
} // end of SetReadCellNames

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetWriteCellNames
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a string vector to which to set the CellName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetWriteCellNames(const vector<string>& cellNames)
{
	vector<string>::const_iterator itr;

	// Delete any "WriteCellName" fields
	ClearFields("WriteCellName");

	// Add fields to the list
	for (itr = cellNames.begin(); itr != cellNames.end(); itr++) {
		AddField("WriteCellName", *itr);
	}
} // end of SetWriteCellNames


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetPreloadFiles
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a string vector to which to set the PreloadFiles field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetPreloadFiles(const vector<string>& files)
{
	vector<string>::const_iterator itr;

	// Delete any "PreloadFiles" fields
	ClearFields("PreloadFiles");

	// Add fields to the list
	for (itr = files.begin(); itr != files.end(); itr++) {
		AddField("PreloadFiles", *itr);
	}
} // end of SetPreloadFiles


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTextObjs
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a string vector to which to set the TextObjs field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetTextObjs(const vector<string>& textObjs)
{
	vector<string>::const_iterator itr;

	// Delete any "TextObjs" fields
	ClearFields("TextObjs");

	// Add fields to the list
	for (itr = textObjs.begin(); itr != textObjs.end(); itr++) {
		AddField("TextObjs", *itr);
	}
} // end of SetTextObjs


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVibrationSpec
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a double vector to which to set the VibrationSpec field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetVibrationSpec(const vector<double>& vibObjs)
{
	vector<double>::const_iterator itr;

	// Delete any "VibrationSpec" fields
	ClearFields("VibrationSpec");

	// Add fields to the list
	for (itr = vibObjs.begin(); itr != vibObjs.end(); itr++) {
		AddField("VibrationSpec", *itr);
	}
} // end of SetVibrationSpec

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetSavedCoords
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	paths - a double vector to which to set the SavedCoords field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetSavedCoords(const vector<CHeaderParseBlock::TCoordSave>& coordObjs)
{
	vector<TCoordSave>::const_iterator itr;

	// Delete any "SavedCoords" fields
	ClearFields("SavedCoords");

	// Add fields to the list
	for (itr = coordObjs.begin(); itr != coordObjs.end(); itr++) {
		AddField("SavedCoords", (double)(itr->m_used ? 1.0 : -1.0) );
		if (itr->m_used) {
			AddField("SavedCoords", itr->m_x );
			AddField("SavedCoords", itr->m_y );
			AddField("SavedCoords", itr->m_z );
			AddField("SavedCoords", itr->m_zoom );
		}
	}
} // end of SetSavedCoords


//////////////////////////////////////////////////////////////////////////////
//
// Description: RemoveOwnVeh
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
CHeaderParseBlock::RemoveOwnVeh()
{
	ClearFields( "OwnVehiclePosition" );
	ClearFields( "OwnVehicleOrientation" );
	ClearFields( "Path" );
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: RemoveOwnVeh
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
CHeaderParseBlock::SetExtRefs(const vector<CHeaderParseBlock::TExtRef>& refs)
{

	ClearFields( "ExtRef" );

	vector<TExtRef>::const_iterator itr;
	// Add fields to the list
	for (itr = refs.begin(); itr != refs.end(); itr++) {
		vector<string> strs;
		strs.push_back( itr->m_fileName );
		strs.push_back( itr->m_groupName );
		AddField("ExtRef", strs );
	}
}


void
CHeaderParseBlock::SetIsExtRef(bool extRef)
{
	// Delete any "ExtRef" fields
	ClearFields( "ExtRef" );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetBlanking
// 	Sets the value of the field named "Blanking" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetBlanking(bool blanking)
{
	// Delete any "Blanking" fields
	ClearFields("Blanking");

	// Add new "Blanking" field.
	AddField("Blanking", blanking ? 1 : 0);

} // end of SetBlanking

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsOn
// 	Sets the value of the field named "HeadlightsOn" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsOn(bool headlightsOn)
{
	// Delete any "HeadlightsOn" fields
	ClearFields("HeadlightsOn");

	// Add new "HeadlightsOn" field.
	AddField("HeadlightsOn", headlightsOn ? 1 : 0);

} // end of SetBlanking


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsAzimuth
// 	Sets the value of the field named "HeadlightsAzimuth" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsAzimuth(double val)
{
	// Delete any "HeadlightsAzimuth" fields
	ClearFields("HeadlightsAzimuth");

	// Add new "HeadlightsAzimuth" field.
	AddField("HeadlightsAzimuth", val);
} // end of SetHeadlightsAzimuth


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsElevation
// 	Sets the value of the field named "HeadlightsElevation" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsElevation(double val)
{
	// Delete any "HeadlightsElevation" fields
	ClearFields("HeadlightsElevation");

	// Add new "HeadlightsElevation" field.
	AddField("HeadlightsElevation", val);
} // end of HeadlightsElevation

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsBeamWidth
// 	Sets the value of the field named "HeadlightsBeamWidth" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsBeamWidth(double val)
{
	// Delete any "HeadlightsBeamWidth" fields
	ClearFields("HeadlightsBeamWidth");

	// Add new "HeadlightsBeamWidth" field.
	AddField("HeadlightsBeamWidth", val);
} // end of SetHeadlightsBeamWidth

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsBeamHeight
// 	Sets the value of the field named "HeadlightsBeamHeight" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsBeamHeight(double val)
{
	// Delete any "HeadlightsBeamHeight" fields
	ClearFields("HeadlightsBeamHeight");

	// Add new "HeadlightsBeamHeight" field.
	AddField("HeadlightsBeamHeight", val);
} // end of SetHeadlightsBeamHeight

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsConstCoeff
// 	Sets the value of the field named "HeadlightsConstCoeff" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsConstCoeff(double val)
{
	// Delete any "HeadlightsConstCoeff" fields
	ClearFields("HeadlightsConstCoeff");

	// Add new "HeadlightsConstCoeff" field.
	AddField("HeadlightsConstCoeff", val);
} // end of SetHeadlightsConstCoeff

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsLinearCoeff
// 	Sets the value of the field named "HeadlightsLinearCoeff" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsLinearCoeff(double val)
{
	// Delete any "HeadlightsLinearCoeff" fields
	ClearFields("HeadlightsLinearCoeff");

	// Add new "HeadlightsLinearCoeff" field.
	AddField("HeadlightsLinearCoeff", val);
} // end of SetHeadlightsLinearCoeff

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsQuadCoeff
// 	Sets the value of the field named "HeadlightsQuadCoeff" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsQuadCoeff(double val)
{
	// Delete any "HeadlightsQuadCoeff" fields
	ClearFields("HeadlightsQuadCoeff");

	// Add new "HeadlightsQuadCoeff" field.
	AddField("HeadlightsQuadCoeff", val);
} // end of SetHeadlightsQuadCoeff

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsHeightFade
// 	Sets the value of the field named "HeadlightsHeightFade" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsHeightFade(double val)
{
	// Delete any "HeadlightsHeightFade" fields
	ClearFields("HeadlightsHeightFade");

	// Add new "HeadlightsHeightFade" field.
	AddField("HeadlightsHeightFade", val);
} // end of SetHeadlightsHeightFade

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsHeightFade
// 	Sets the value of the field named "HeadlightsHeightFade" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetAmbientLightInt(double val)
{
	// Delete any "HeadlightsHeightFade" fields
	ClearFields("AmbientLightInt");

	// Add new "HeadlightsHeightFade" field.
	AddField("AmbientLightInt", val);
} // end of SetHeadlightsHeightFade

//////////////////////////////////////////////////////////////////////////////
///\brief
///    Sets the HeadlightLampSeparation field
///\remark
///		The headlamp speration field controls the distance between headlamp
///		light sources.
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightLampSeparation(double val)
{

	// Delete any "HeadlightsHeightFade" fields
	ClearFields("HeadlightLampSeparation");

	// Add new "HeadlightsHeightFade" field.
	AddField("HeadlightLampSeparation", val);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetHeadlightsHeightFade
// 	Returns the value of the field named "HeadlightsHeightFade" which was parsed by
// 	the constructor.
//
// Remarks: The "AmbientLightInt" field is used for headlights parameters
//
// Arguments:
//
// Returns: A double containing the HeadlightsHeightFade.
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightForwardOffset(double val)
{
	// Delete any "HeadlightsHeightFade" fields
	ClearFields("HeadlightForwardOffset");

	// Add new "HeadlightsHeightFade" field.
	AddField("HeadlightForwardOffset", val);


}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsIntensity
// 	Sets the value of the field named "HeadlightsIntensity" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsIntensity(double val)
{
	// Delete any "HeadlightsIntensity" fields
	ClearFields("HeadlightsIntensity");

	// Add new "HeadlightsIntensity" field.
	AddField("HeadlightsIntensity", val);
} // end of SetHeadlightsHeightFade

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetHeadlightsIntensity
// 	Sets the value of the field named "HeadlightsIntensity" to the value of the
// 	parameter.
//
// Remarks:
//
// Arguments:
//	comment - A bool
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CHeaderParseBlock::SetHeadlightsCutOffDist(double val)
{
	// Delete any "HeadlightsIntensity" fields
	ClearFields("HeadlightsCutOffDist");

	// Add new "HeadlightsIntensity" field.
	AddField("HeadlightsCutOffDist", val);
} // end of SetHeadlightsHeightFade
int	CHeaderParseBlock::GetEnvMonth(void) const{
	CSnoValue val;
	if (GetField("EnvMonth", val))
		return val.GetIntValue();
	else
		return 6;
}
int	CHeaderParseBlock::GetEnvDay(void) const{
	CSnoValue val;
	if (GetField("EnvDay", val))
		return val.GetIntValue();
	else
		return 1;
}
int	CHeaderParseBlock::GetEnvHour(void) const{
	CSnoValue val;
	if (GetField("EnvHour", val))
		return val.GetIntValue();
	else
		return 12;
}
int	CHeaderParseBlock::GetEnvMinute(void) const{
	CSnoValue val;
	if (GetField("EnvMinute", val))
		return val.GetIntValue();
	else
		return 0;
}
int CHeaderParseBlock::GetEnvYear(void) const{
	CSnoValue val;
	if (GetField("EnvYear", val))
		return val.GetIntValue();
	else
		return 2006;
}
float CHeaderParseBlock::GetEnvAlt(void) const{
	CSnoValue val;
	if (GetField("EnvAlt", val))
		return (float)val.GetFloatValue();
	else
		return 0;
}
void CHeaderParseBlock::GetBlankColor(float &r,float &g, float &b){
	CSnoValue val;
	if (GetField("BlankRed", val))
		r = (float)val.GetFloatValue();
	else
		r = 0;
	if (GetField("BlankGreen", val))
		g = (float)val.GetFloatValue();
	else
		g = 0;
	if (GetField("BlankBlue", val))
		b = (float)val.GetFloatValue();
	else
		b = 0;
}

bool  CHeaderParseBlock::GetSirenOverSpeed() const{
	CSnoValue val;
	if (GetField("SirenOverSpeed", val))
		return val.GetIntValue()>0;
	else
		return false;
}

float CHeaderParseBlock::GetSirenSpeed() const{
	CSnoValue val;
	if (GetField("SirenSpeed", val))
		return (float)val.GetFloatValue();
	else
		return 100.0f;
}
int  CHeaderParseBlock::GetCollisionEffectMask() const{
	CSnoValue val;
	if (GetField("CollisionEffectMask", val))
        return val.GetIntValue();
	else
		return 3;
}

void CHeaderParseBlock::SetBlankColor(float r, float g, float b){
	ClearFields("BlankRed");
	AddField("BlankRed", r);
	ClearFields("BlankGreen");
	AddField("BlankGreen", g);
	ClearFields("BlankBlue");
	AddField("BlankBlue", b);
}
///////////////////////////////////////////////////////////////////
///\brief Set the longitude
///\remark
///		Encoding: bits 0-8, degrees, bit 9 dir (0 = W, 1 = E )
///				  bits 15 - 31 fraction of degrees
//////////////////////////////////////////////////////////////////
float CHeaderParseBlock::GetEnvLong(void) const{
	CSnoValue val;
	if (GetField("EnvLong", val))
		return (float)val.GetFloatValue();
	else
		return 122;
}
///////////////////////////////////////////////////////////////////
///\brief Set the longitude
///\remark
///		Encoding: bits 0-8, degrees, bit 9 dir (0 = N, 1 = S )
///				  bits 16 - 31 fraction of degrees
///////////////////////////////////////////////////////////////////
float CHeaderParseBlock::GetEnvLat(void) const{
	CSnoValue val;
	if (GetField("EnvLat", val))
		return (float)val.GetFloatValue();
	else
		return 35.0f;
}
void CHeaderParseBlock::SetEnvMonth(int val){
	ClearFields("EnvMonth");
	AddField("EnvMonth", val);
}
void CHeaderParseBlock::SetEnvDay(int val){
	ClearFields("EnvDay");
	AddField("EnvDay", val);
}
void CHeaderParseBlock::SetEnvHour(int val){
	ClearFields("EnvHour");
	AddField("EnvHour", val);
}
void CHeaderParseBlock::SetEnvMinute(int val){
	ClearFields("EnvMinute");
	AddField("EnvMinute", val);
}
void CHeaderParseBlock::SetEnvLong(float val){
	ClearFields("EnvLong");
	AddField("EnvLong", val);
}
void CHeaderParseBlock::SetEnvLat(float val){
	ClearFields("EnvLat");
	AddField("EnvLat", val);
}
void CHeaderParseBlock::SetEnvAlt(float val){
	ClearFields("EnvAlt");
	AddField("EnvAlt",val);
}
void CHeaderParseBlock::SetEnvYear(int val){
	ClearFields("EnvYear");
	AddField("EnvYear",val);
}

void CHeaderParseBlock::SetSirenOverSpeed(bool SirenOn){
	ClearFields("SirenOverSpeed");
	if (SirenOn)
		AddField("SirenOverSpeed", 1);
	else{
		AddField("SirenOverSpeed", 0);
	}
}
void CHeaderParseBlock::SetSirenSpeed(float val){
	ClearFields("SirenSpeed");
	AddField("SirenSpeed", val);
}
void CHeaderParseBlock::SetCollisionEffectMask(int CollEffect){
	ClearFields("CollisionEffectMask");
	AddField("CollisionEffectMask", CollEffect);
}

bool CHeaderParseBlock::NextExternalBlk()
{
	return false;
}
