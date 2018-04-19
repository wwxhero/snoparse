//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: actionparseblock.cxx,v 1.54 2017/05/03 17:14:07 IOWA\dheitbri Exp $
//
// The implementation f r the action parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#ifdef __sgi
#include <strstream.h>
#define ostringstream ostrstream
#define istringstream istrstream
#elif _PowerMAXOS
#include <strstream>
#define ostringstream ostrstream
#define istringstream istrstream
#elif _WIN32
#include <sstream>
#endif

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CActionParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: Name of the block is not set.
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::CActionParseBlock()
	: CSnoBlock() {} // end of CActionParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CActionParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CActionParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::CActionParseBlock(const CActionParseBlock& cCopy)
{
	*this = cCopy;
} // end of CActionParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~ActionParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::~CActionParseBlock() {}// end of CActionParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CActionParseBlock
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
CActionParseBlock::CActionParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CActionParseBlock

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
CActionParseBlock&
CActionParseBlock::operator=(const CActionParseBlock& cRhs)
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
CActionParseBlock::GetByNameSet(void) const
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
CActionParseBlock::GetByTypeSet(void) const
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
CActionParseBlock::GetByRoadSet(void) const
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
CActionParseBlock::GetByPstnSet(void) const
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


CActionParseBlock::TRelativeInfo
CActionParseBlock::GetRelativeSet(void) const
{
	TRelativeInfo info;

	vector<CSnoValue> vals;
	CSnoValue val;

	if (GetField("RelIsDrvr", val)) {
		info.m_isDriver = (val.GetIntValue() != 0);
	}
	if (GetField("RelObjName", val)) {
		info.m_objName = val.GetStringValue();
	}
	if (GetField("RelNumObjs", val)) {
		info.m_numObjs = val.GetIntValue();
	}
	if (GetField("RelParams", vals)) {
		for (vector<CSnoValue>::iterator i = vals.begin(); i != vals.end(); i++) {
			info.m_params.push_back( i->GetStringValue() );
		}
	}


	return info;
}

CActionParseBlock::TRelativeStates
CActionParseBlock::GetRelativeStates(void)const
{
	TRelativeStates info;
	vector<CSnoValue> vals;

	if(GetField("RelativeStates",vals)){
		for (vector<CSnoValue>::iterator i = vals.begin(); i != vals.end(); i++) {
			info.m_AllStates.push_back( i->GetStringValue() );
		}
	}
	return info;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetInstigatorSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the InstigatorSet field.
//
//////////////////////////////////////////////////////////////////////////////
int
CActionParseBlock::GetInstigatorSet(void) const
{
	CSnoValue val;
	if (GetField("InstigatorSet", val))
		return val.GetIntValue();
	else
		 return 0;
} // end of GetInstigatorSet

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
CActionParseBlock::GetTime(void) const
{
	CSnoValue val;
	if (GetField("Time", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetTime

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
CActionParseBlock::GetState(void) const
{
	CSnoValue val;
	if (GetField("State", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetState

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFailure
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Failure field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetFailure(void) const
{
	CSnoValue val;
	if (GetField("Failure", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetFailure

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetButton
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Button field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetButton(void) const
{
	CSnoValue val;
	if (GetField("Button", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetButton

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDial
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A pbTDial value for the Dial field.
//
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::pbTDial
CActionParseBlock::GetDial(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	pbTDial dial;
	if (GetField("Dial", vals)) {
		if (vals.size() != 2) {
			TCountError e("Dial", 2);
			throw e;
		}
		pVal = vals.begin();
		dial.name = pVal->GetStringValue();
		pVal++;
		dial.value = pVal->GetStringValue();
	}
	return dial;
} // end of GetDial

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetButtonDialPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Button field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetButtonDialPath(void) const
{
	CSnoValue val;
	if (GetField("ButtonDialPath", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetButtonDialPath

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetAudio
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Audio field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetAudio(void) const
{
	CSnoValue val;
	if (GetField("Audio", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetAudio


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetAudio
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the File field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetFile(void) const
{
	CSnoValue val;
	if (GetField("File", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the File field.
//
//////////////////////////////////////////////////////////////////////////////
int
CActionParseBlock::GetStream(void) const
{
	CSnoValue val;
	if (GetField("Stream", val))
		return val.GetIntValue();
	else
		 return 1;
} // end of GetStream

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetFile
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the StreamVal field.
//
//////////////////////////////////////////////////////////////////////////////
double
CActionParseBlock::GetStreamValue(void) const
{
	CSnoValue val;
	if (GetField("StreamVal", val))
		return val.GetFloatValue();
	else
		 return 1;
} // end of GetStreamValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetComment
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the Comment field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetComment(void) const
{
	CSnoValue val;
	if (GetField("Comment", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetComment


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetTrafManSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the TrafManSet field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetTrafManSet(void) const
{
	CSnoValue val;
	if (GetField("TrafManSet", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetTrafManSet


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetMotionPreposition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A pbTMotionPreposition value for the MotionPreposition field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetMotionPreposition(void) const
{
	CSnoValue val;
	if (GetField("MotionPreposition", val)) {
		return val.GetStringValue();
	}
	else return "";
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A double value for the Delay field.
//
//////////////////////////////////////////////////////////////////////////////
double
CActionParseBlock::GetDelay(void) const
{
	CSnoValue val;
	if (GetField("Delay", val)) {
		return val.GetFloatValue();
	}
	else return 0.0f;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDataRedVars
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A pbTDataRedVar value for the DataRedVar field.
//
//////////////////////////////////////////////////////////////////////////////
vector<CActionParseBlock::pbTDataRedVar>
CActionParseBlock::GetDataRedVars(void) const
{
	CSnoValue val;
	if (GetField("DataRedVars", val)) {
		string str = val.GetStringValue();
		return StringToDataRedVars(str);
	}
	
	// else
	vector<CActionParseBlock::pbTDataRedVar> vars;
	return vars;
}

vector<CActionParseBlock::pbTDataRedVar> 
CActionParseBlock::StringToDataRedVars( const string& cStr )
{
	vector<pbTDataRedVar> vars;

	int i = 0;
	while( (i = (int) cStr.find(';', i)) != cStr.npos ) 
	{
		int n = (int) cStr.find( ';', i + 1 );
		string substr = cStr.substr( i, (n-1) );
		i += (int)substr.size();
		istrstream istr( substr.c_str() );

		pbTDataRedVar var;

		char c;
		istr >> c >> var.type >> c;
		switch( var.type ) 
		{
		case 1:
			istr.get( var.data, cDR_COLSIZE, ':' );
			istr >> c;
			istr.get( &var.data[cDR_COLSIZE], cDR_DATASIZE, ';' );
			break;
		case 2:
			istr.get( var.data, cDR_COLSIZE, ':' );
			istr >> c;
			istr.get( &var.data[cDR_COLSIZE], cDR_DATASIZE, ';' );
			break;
		case 4:
			istr.get( var.data, cDR_COLSIZE, ':' );
			istr >> c;
			istr.get( &var.data[cDR_COLSIZE], cDR_DATASIZE, ';' );
			break;
		case 8:
			istr.get( var.data, cDR_COLSIZE, ':' );
			istr >> c;
			istr.get( &var.data[cDR_COLSIZE], cDR_DATASIZE, ';' );
			break;
		}
		vars.push_back( var );
	}
	return vars;
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: GetDataRedVarsStr
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the DataRedVar field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetDataRedVarsStr(void) const
{
	CSnoValue val;
	string str;
	if (GetField("DataRedVars", val)) {
		 str = val.GetStringValue();
	}
	
	return str;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVarName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the VarName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetVarName(void) const
{
	CSnoValue val;
	string str;
	if (GetField("VarName", val)) {
		 str = val.GetStringValue();
	}
	
	return str;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVarName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the VarName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetVarQueueOperation(void) const
{
	CSnoValue val;
	string str;
	if (GetField("VarQueueOperation", val)) {
		 str = val.GetStringValue();
	}
	
	return str;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVarValue
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the VarValue field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetVarValue(void) const
{
	CSnoValue val;
	string str;
	if (GetField("VarValue", val)) {
		str = val.GetStringValue();
		if (str == "") {
			double d = val.GetFloatValue();
			char buffer[64];
			sprintf(buffer, "%lf", d);
			str = buffer;
		}
	}

	return str;
}

bool			
CActionParseBlock::GetIsVarValExpression(void) const
{
	CSnoValue val;
	if (GetField("IsVarValExpression", val)) {
		return val.GetIntValue() > 0;
	}else{
        return false;
    }

}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CellName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetCellName(void) const
{
	CSnoValue val;
	string str;
	if (GetField("CellName", val)) {
		str = val.GetStringValue();
	}

	return str;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the UniformName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetUniformName(void) const
{
	CSnoValue val;
	string str;
	if (GetField("UniformName", val)) {
		str = val.GetStringValue();
	}

	return str;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the ShaderName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetShaderName(void) const
{
	CSnoValue val;
	string str;
	if (GetField("ShaderName", val)) {
		str = val.GetStringValue();
	}

	return str;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the UniformName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetShaderOption(void) const
{
	CSnoValue val;
	string str;
	if (GetField("ShaderOption", val)) {
		str = val.GetStringValue();
	}

	return str;
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///	  Sets a switch by name
///
///\remark
///     This is used to set a switch for a visual model, outside of our normal
///     audio visual states. For instance if we added a loose trunk animation 
///     we can use this to turn on the animation by the switch name
///  
///
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::TSwitchInfo 
CActionParseBlock::GetSwitch(void) const
{
	TSwitchInfo info;
    CSnoValue val;
	if (GetField("SwitchName", val)) {
		info.switchName = val.GetStringValue();
	}
	if (GetField("SwitchValue", val)) {
		info.value = val.GetIntValue();
	}
    return info;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellType
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CellType field.
//
//////////////////////////////////////////////////////////////////////////////
CActionParseBlock::ECellDataType
CActionParseBlock::GetCellType(void) const
{
	CSnoValue val;
	int i = eNOTSET;
	if (GetField("CellType", val)) {
		i = val.GetIntValue();
	}

	return ECellDataType(i);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: IsCellTypeVariable
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CellType field.
//
//////////////////////////////////////////////////////////////////////////////
bool
CActionParseBlock::IsCellTypeVariable(void) const
{
	CSnoValue val;
	if (GetField("CellVar", val)) {
		return val.GetIntValue() != 0;
	}
	else
		return false;
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: IsCellTypeVariable
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the VisualDisplayLocation field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetVisualDisplayLocation(void)const{
	CSnoValue val;
	if (GetField("VisualDisplayLocation", val) && val.GetStringValue() != "")
		return val.GetStringValue();
	else
		return "1";
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: IsCellTypeVariable
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the VisualDisplayValue field.
//
//////////////////////////////////////////////////////////////////////////////
string			
CActionParseBlock::GetVisualDisplayValue(void)const{
	CSnoValue val;
	GetField("VisualDisplayValue", val);
	return val.GetStringValue();
}
string
CActionParseBlock::GetScreenPosition(void) const{
	
	CSnoValue val;
	GetField("ScreenPosition", val);
	return val.GetStringValue();
	
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///    The functions Gets a string for changing some visual setting for the cab
///////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetCabSettingsString(void) const{
	CSnoValue val;
	GetField("CabString", val);
	return val.GetStringValue();
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///    Gets a Command to tell the renderer to override the headlight state
///////////////////////////////////////////////////////////////////////////////
int
CActionParseBlock::GetHeadlightControlCommand(void) const{
	CSnoValue val;
	GetField("HeadlightControlCommand", val);
	return val.GetIntValue();
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///    The functions Gets a string for changing some visual setting for the cab
///////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCabSettingsString(const string& cabString){
	// Delete any "VarValue" fields
	ClearFields("CabString");

	// Add new "VarValue" field.
	AddField("CabString", cabString );
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///    Sets a command to tell the render to turn on/off headlight, allow user 
///    control
///\param[in] command -1 off, 0 allow driver control, 1 low beams, 2 high beams 
///////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetHeadlightControlCommand(int command){
	// Delete any "VarValue" fields
	ClearFields("HeadlightControlCommand");

	// Add new "VarValue" field.
	AddField("HeadlightControlCommand", command );
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///		Sets up a graph
///\remark
///
/////////////////////////////////////////////////////////////////////////////////
void 
CActionParseBlock::SetGraphString(const string& graphString)
{
	ClearFields("VarName");

	AddField("VarName", graphString);
}
//////////////////////////////////////////////////////////////////////////////
///\
///
///
///
///
///////////////////////////////////////////////////////////////////////////////
string 
CActionParseBlock::GetGraphString(void) const
{
	CSnoValue val;
	string str;
	if (GetField("VarName", val)) {
		str = val.GetStringValue();
	}
	return str;
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets a seed for a random number generator
///\remark
///		Return a empty vector by default
///////////////////////////////////////////////////////////////////////////////
std::vector<long>           
CActionParseBlock::GetSeed(void) const{
	vector<long> data;

	CSnoValue val;
	string str;
	if (GetField("RanSeed", val)) {
		str = val.GetStringValue();
	}
	if (str.size() == 0)
		return data;
	std::stringstream ss;
	ss.str(str);
	long tempVal =0;
	while (!ss.fail() && !ss.eof()){
		ss>>tempVal;
		if (!ss.fail())
			data.push_back(tempVal);
	}

	return data;
}
//////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets a seed for a random number generator
///\remark
///		Return a empty vector by default
///////////////////////////////////////////////////////////////////////////////
void         
CActionParseBlock::SetSeed(const std::vector<long> & vals){
	ClearFields("RanSeed");
	vector<long> data;
	std::stringstream ss;
	for (auto itr = vals.begin(); itr != vals.end(); itr++){
		ss<<*itr<<" ";
	}
	string str;	AddField("RanSeed", ss.str());

}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellDataInt
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of int values encoded in the CellData field.
//
//////////////////////////////////////////////////////////////////////////////
vector<int>
CActionParseBlock::GetCellDataInt(void) const
{
	vector<int> data;

	CSnoValue val;
	string str;
	if (GetField("CellData", val)) {
		str = val.GetStringValue();
	}
    if (str.size() == 0) 
        return data;
	char* pos = &str[0];

	int value;
	while (pos != NULL) {
		sscanf(pos, "%d", &value);
		data.push_back(value);
		pos = strchr(pos, '|');
		if (pos != NULL) pos++;
	}

	return data;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellDataFloat
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of float values encoded in the CellData field.
//
//////////////////////////////////////////////////////////////////////////////
vector<float>
CActionParseBlock::GetCellDataFloat(void) const
{
	vector<float> data;

	CSnoValue val;
	string str;
	if (GetField("CellData", val)) {
		str = val.GetStringValue();
	}
    if (str.size() == 0) 
        return data;
	char* pos = &str[0];

	float value;
	while (pos != NULL) {
		sscanf(pos, "%f", &value);
		data.push_back(value);
		pos = strchr(pos, '|');
		if (pos != NULL) pos++;
	}

	return data;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellDataShort
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A vector of short values encoded in the CellData field.
//
//////////////////////////////////////////////////////////////////////////////
vector<short>
CActionParseBlock::GetCellDataShort(void) const
{
	vector<short> data;

	CSnoValue val;
	string str;
	if (GetField("CellData", val)) {
		str = val.GetStringValue();
	}
    if (str.size() == 0) 
        return data;
	char* pos = &str[0];

	short value;
	while (pos != NULL) {
		sscanf(pos, "%hd", &value);
		data.push_back(value);
		pos = strchr(pos, '|');
		if (pos != NULL) pos++;
	}

	return data;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellDataString
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CellData field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetCellDataString(void) const
{
	CSnoValue val;
	string str;
	if (GetField("CellData", val)) {
		str = val.GetStringValue();
	}
	return str;
}

///////////////////////////////////////////////////////////////////////////////
///\brief
///Gets the command for setting TOD
///\remark
///  This function does not strickly output a time value,
///  this is a command that will be used by the set TOD function.
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetSetTimeOfDayStr(void) const{
	CSnoValue val;
	GetField("SetTimeCommand", val);
	return val.GetStringValue();
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: GetCellDataString
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the CellData field.
//
//////////////////////////////////////////////////////////////////////////////
string
CActionParseBlock::GetCommand(void) const
{
	CSnoValue val;
	string str;
	if (GetField("Command", val)) {
		str = val.GetStringValue();
	}
	return str;
}

///////////////////////////////////////////////////////////////////////////////
///\brief
///Gets the command for setting TOD
///\remark
///  This function does not strickly output a time value,
///  this is a command that will be used by the set TOD function.
//////////////////////////////////////////////////////////////////////////////
int
CActionParseBlock::GetTargetID(void) const{
	CSnoValue val;
	GetField("TargetID", val);
    return val.GetIntValue();
}
//////////////////////////////////////////////////////////////////////////////
// 	Mutator functions
//////////////////////////////////////////////////////////////////////////////

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
CActionParseBlock::SetByNameSet(const vector<string>& byNameSets)
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
CActionParseBlock::SetByTypeSet(const vector<string>& byTypeSets)
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
CActionParseBlock::SetByRoadSet(const vector<pbTRoad>& byRoadSets)
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
CActionParseBlock::SetByPstnSet(const vector<pbTPstn>& byPstnSets)
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

void
CActionParseBlock::SetRelativeSet(const TRelativeInfo& info)
{
	ClearFields( "RelIsDrvr" );
	AddField( "RelIsDrvr", info.m_isDriver ? 1 : 0 );

	ClearFields( "RelObjName" );
	AddField( "RelObjName", info.m_objName );

	ClearFields( "RelNumObjs" );
	AddField( "RelNumObjs", info.m_numObjs );

	ClearFields( "RelParams" );
	AddField( "RelParams", info.m_params );
}

void
CActionParseBlock::SetRelativeStates(const TRelativeStates& info)
{
	ClearFields("RelativeStates");
	AddField("RelativeStates",info.m_AllStates);
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInstigatorSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	instigatorSet - a int to which to set the InstigatorSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetInstigatorSet(int instigatorSet)
{
	// Delete any "InstigatorSet" fields
	ClearFields("InstigatorSet");

	// Add new "InstigatorSet" field.
	AddField("InstigatorSet", instigatorSet);

} // end of SetInstigatorSet

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
CActionParseBlock::SetTime(double time)
{
	// Delete any "Time" fields
	ClearFields("Time");

	// Add new "Time" field.
	AddField("Time", time);

} // end of SetTime

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
CActionParseBlock::SetState(const string& state)
{
	// Delete any "State" fields
	ClearFields("State");

	// Add new "State" field.
	AddField("State", state);

} // end of SetState

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetFailure
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	failure - a string to which to set the Failure field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetFailure(const string& failure)
{
	// Delete any "Failure" fields
	ClearFields("Failure");

	// Add new "Failure" field.
	AddField("Failure", failure);

} // end of SetFailure

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetButton
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	button - a string to which to set the Button field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetButton(const string& button)
{
	// Delete any "Button" fields
	ClearFields("Button");

	// Add new "Button" field.
	AddField("Button", button);

} // end of SetButton

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDial
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	dial - a pbTDial to which to set the Dial field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetDial(const pbTDial& dial)
{
	vector<string> dialVec;
	// Delete any "Dial" fields
	ClearFields("Dial");

	// Add new "Dial" field.
	dialVec.push_back(dial.name);
	dialVec.push_back(dial.value);

	AddField("Dial", dialVec);

} // end of SetDial


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetButtonDialPath
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	button - a string to which to set the ButtonDialPath field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetButtonDialPath(const string& path)
{
	// Delete any "ButtonDialPath" fields
	ClearFields("ButtonDialPath");

	// Add new "ButtonDialPath" field.
	AddField("ButtonDialPath", path);

} // end of SetButton


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetAudio
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	audio - a string to which to set the Audio field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetAudio(const string& audio)
{
	// Delete any "Audio" fields
	ClearFields("Audio");

	// Add new "Audio" field.
	AddField("Audio", audio);

} // end of SetAudio

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetAudio
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	audio - a string to which to set the Audio field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetFile(const string& file)
{
	// Delete any "File" fields
	ClearFields("File");

	// Add new "File" field.
	AddField("File", file);

} // end of SetFile

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetStream
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	file - a string to which to set the File field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetStream(const int val)
{
	// Delete any "Stream" fields
	ClearFields("Stream");

	// Add new "Stream" field.
	AddField("Stream", val);

} // end of SetStream

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetStreamValue
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	file - a string to which to set the File field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetStreamValue(const double val)
{
	// Delete any "StreamVal" fields
	ClearFields("StreamVal");

	// Add new "StreamVal" field.
	AddField("StreamVal", val);

} // end of SetStreamValue

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetComment
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	comment - a string to which to set the Comment field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetComment(const string& comment)
{
	// Delete any "Comment" fields
	ClearFields("Comment");

	// Add new "Comment" field.
	AddField("Comment", comment);

} // end of SetComment

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTrafManSet
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	comment - a string to which to set the TrafManSet field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetTrafManSet(const string& trafManSet)
{
	// Delete any "TrafManSet" fields
	ClearFields("TrafManSet");

	// Add new "TrafManSet" field.
	AddField("TrafManSet", trafManSet);

} // end of SetTrafManSet


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetMotionPreposition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	motion - a pbTMotionPreposition to which to set the MotionPreposition field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetMotionPreposition(const string& str)
{
	// Delete any "MotionPreposition" fields
	ClearFields("MotionPreposition");

	// Add new "MotionPreposition" field.
	AddField("MotionPreposition", str );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDataRedVars
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	motion - a vector<pbTDataRedVar> to which to set the Delay field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetDataRedVars(const string& val)
{
	// Delete any "DataRedVars" fields
	ClearFields("DataRedVars");

	// Add new "DataRedVars" field.
	AddField("DataRedVars", val );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVarName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the VarName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetVarName(const string& val)
{
	// Delete any "VarName" fields
	ClearFields("VarName");

	// Add new "VarName" field.
	AddField("VarName", val );
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetVarValue
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the VarValue field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetVarValue(const string& str)
{
	// Delete any "VarValue" fields
	ClearFields("VarValue");

	// Add new "VarValue" field.
	AddField("VarValue", str );
}
void
CActionParseBlock::SetVarQueueOperation(const string& str)
{
	// Delete any "VarValue" fields
	ClearFields("VarQueueOperation");

	// Add new "VarValue" field.
	AddField("VarQueueOperation", str );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetIsVarValExpression
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a bool, is the value an expression? 
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void	
CActionParseBlock::SetIsVarValExpression(bool val){
	// Delete any "VarValue" fields
	ClearFields("IsVarValExpression");

	// Add new "VarValue" field.
	AddField("IsVarValExpression",  val ? 1 : 0 );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	motion - a double to which to set the Delay field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetDelay(double val)
{
	// Delete any "Delay" fields
	ClearFields("Delay");

	// Add new "Delay" field.
	AddField("Delay", val );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the CellName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellName(const string& val)
{
	// Delete any "CellName" fields
	ClearFields("CellName");

	// Add new "CellName" field.
	AddField("CellName", val );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the CellName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetUniformName(const string& val)
{
	// Delete any "CellName" fields
	ClearFields("UniformName");

	// Add new "CellName" field.
	AddField("UniformName", val );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetShaderName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the ShaderName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetShaderName(const string& val)
{
	// Delete any "CellName" fields
	ClearFields("ShaderName");

	// Add new "CellName" field.
	AddField("ShaderName", val );
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief
///	  Sets a switch by name
///
///\remark
///     This is used to set a switch for a visual model, outside of our normal
///     audio visual states. For instance if we added a loose trunk animation 
///     we can use this to turn on the animation by the switch name
///  
///
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetSwitch(const TSwitchInfo& info)
{
	// Delete any "CellName" fields
	ClearFields("SwitchName");

	// Delete any "CellName" fields
	ClearFields("SwitchValue");

	// Add new "CellName" field.
	AddField("SwitchName", info.switchName );

	// Add new "CellName" field.
	AddField("SwitchValue", info.value );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCellName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the CellName field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetShaderOption(const string& val)
{
	// Delete any "CellName" fields
	ClearFields("ShaderOption");

	// Add new "CellName" field.
	AddField("ShaderOption", val );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a ECellDataType to which to set the CellType field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellType(ECellDataType val)
{
	int valInt = (int)val;

	// Delete any "CellType" fields
	ClearFields("CellType");

	// Add new "CellType" field.
	AddField("CellType", valInt );
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	vals - a double to which to set the CellData field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellDataInt(const vector<int>& vals)
{
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	vals - a double to which to set the CellData field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellDataFloat(const vector<float>& vals)
{
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	vals - a double to which to set the CellData field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellDataShort(const vector<short>& vals)
{
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	vals - a int to which to set the VisualDisplayLocation field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void			
CActionParseBlock::SetVisualDisplayLocation(const string& val){
	// Delete any "VisualDisplayLocation" fields
	ClearFields("VisualDisplayLocation");

	// Add new "VisualDisplayLocation" field.
	AddField("VisualDisplayLocation",val );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDelay
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	vals - a string to which to set the VisualDisplayValue field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void			
CActionParseBlock::SetVisualDisplayValue(const string& val){
	// Delete any "VisualDisplayValue" fields
	ClearFields("VisualDisplayValue");

	// Add new "VisualDisplayValue" field.
	AddField("VisualDisplayValue",val );
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///		Set the Position on the screen to display something
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetScreenPosition(const string& val){
	// Delete any "VisualDisplayValue" fields
	ClearFields("ScreenPosition");

	// Add new "VisualDisplayValue" field.
	AddField("ScreenPosition",val );
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: SetCellDataString
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	val - a string to which to set the CellData field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetCellDataString(const string& val)
{
	// Delete any "CellData" fields
	ClearFields("CellData");

	// Add new "CellData" field.
	AddField("CellData", val );
}

void
CActionParseBlock::SetIsCellTypeVariable(bool b)
{
	// Delete any "CellVar" fields
	ClearFields("CellVar");

	// Add new "CellVar" field.
	AddField("CellVar", b ? 1 : 0 );
}
///////////////////////////////////////////////////////////////////////////////
///\brief
///		Sets the Command to Change Time of Day
///\sa GetSetTimeOfDayStr
//////////////////////////////////////////////////////////////////////////////
void
CActionParseBlock::SetSetTimeOfDayStr(const string& val){
	// Delete any "VisualDisplayValue" fields
	ClearFields("SetTimeCommand");

	// Add new "VisualDisplayValue" field.
	AddField("SetTimeCommand",val );
}

CActionParseBlock::pbTFailure
CActionParseBlock::StringToFailure( const string& s )
{
	const int cBUFSIZE = 1024;
	char buffer[cBUFSIZE];
	pbTFailure retVal;
	istringstream str(s.c_str());
	string tempStr;
	char ch;
	str.get( buffer, cBUFSIZE, ':' );
	str.get( ch );
	if (!strcmp( buffer, "TireCond")) {
		retVal.type = eTIRE;
		for (int n=0; n < 10; n++) {
			str.get( buffer, cBUFSIZE, ':' );
			int type = atoi( buffer );
			retVal.info.TireCond.type[n] = type;
			str.get( ch );
			str.get( buffer, cBUFSIZE, ':' );
			retVal.info.TireCond.time[n] = atoi( buffer );
			str.get( ch );
		}
	} else 	if (!strcmp( buffer, "BrakeCond")) {
		retVal.type = eBRAKE;
		for (int n=0; n < 11; n++) {
			str.get( buffer, cBUFSIZE, ':' );
			retVal.info.BrakeCond.type[n] = atoi( buffer );
			str.get( ch );
		}
	} else 	if (!strcmp( buffer, "Steering")) {
		retVal.type = eSTEERING;
		str.get( buffer, cBUFSIZE, ':' );
		str.get( ch );
		retVal.info.Steering.type = atoi( buffer );
	} else 	if (!strcmp( buffer, "Alert")) {
		retVal.type = eALERT;
		str.get( buffer, cBUFSIZE, ':' );
		str.get( ch );
		retVal.info.Alert.type = atoi( buffer );
	} else 	if (!strcmp( buffer, "Info")) {
		retVal.type = eINFORMATIONAL;
		str.get( buffer, cBUFSIZE, ':' );
		str.get( ch );
		retVal.info.Information.type = atoi( buffer );
		str.get( buffer, cBUFSIZE, ':' );
		str.get( ch );
		retVal.info.Information.multiplier = atoi( buffer );
	} else 	if (!strcmp( buffer, "Cab")) {
		retVal.type = eCAB_COMPONENT;
		str.get( buffer, cBUFSIZE, ':' );
		str.get( ch );
		retVal.info.CabComponent.type = atoi( buffer );
	} else {
		// error
	}

	return retVal;
}


string
CActionParseBlock::FailureToString( const CActionParseBlock::pbTFailure& failure)
{
	ostringstream str;
	int n;

	switch ( failure.type ) {
		case eTIRE:
			str << "TireCond";
			for (n = 0; n < 10; n++) {
				str << ':' << failure.info.TireCond.type[n];
				str << ':' << failure.info.TireCond.time[n];
			}
			break;
		case eBRAKE:
			str << "BrakeCond";
			for (n = 0; n < 11; n++) {
				str << ':' << failure.info.BrakeCond.type[n];
			}
			break;
		case eSTEERING:
			str << "Steering:" << failure.info.Steering.type;
			break;
		case eALERT:
			str << "Alert:" << failure.info.Alert.type;
			break;
		case eINFORMATIONAL:
			str << "Info:" << failure.info.Information.type;
			str << ':' << failure.info.Information.multiplier;
			break;
		case eCAB_COMPONENT:
			str << "Cab:" << failure.info.CabComponent.type;
			break;
	}
	str << '\0';
	return str.str();
}


int
CActionParseBlock::StringToFlags( const string& str, unsigned int* pFlags )
{
	pbTFailure failure = StringToFailure( str );
	int n;

	switch (failure.type) {
	case eTIRE:
		for (n=0; n < 10; n++) {
			pFlags[n] = failure.info.TireCond.type[n];
			if (pFlags[n] == eTF_GOING_FLAT) {
				pFlags[n] += (failure.info.TireCond.time[n] << 4);
			}
		}
		break;
	case eBRAKE:
		for (n=0; n < 11; n++) {
			pFlags[n] = failure.info.BrakeCond.type[n];
		}
		break;
	case eSTEERING:
		pFlags[0] = 1;
		break;
	case eALERT:
		pFlags[0] = failure.info.Alert.type;
		break;
	case eINFORMATIONAL:
		pFlags[0] = failure.info.Information.type + (failure.info.Information.multiplier << 8);
		break;
	case eCAB_COMPONENT:
		pFlags[0] = failure.info.CabComponent.type;
		break;
	}
	return (int)failure.type;
}

void CActionParseBlock::SetCommand(const std::string& str){
	// Delete any "VisualDisplayValue" fields
	ClearFields("Command");

	// Add new "VisualDisplayValue" field.
	AddField("Command", str );
}
void CActionParseBlock::SetTargetID(int id){
	// Delete any "VisualDisplayValue" fields
	ClearFields("TargetID");

	// Add new "VisualDisplayValue" field.
	AddField("TargetID",id );
}

CActionParseBlock::pbTMotionPreposition
CActionParseBlock::StringToPreposition( const string& str )
{
	pbTMotionPreposition mp;
	istringstream istr( str.c_str() );
	char c;
	istr >> mp.crossbeam >> c >> mp.carriage >> c >>
			mp.hexX >> c >> mp.hexY >> c >> mp.hexZ >> c >>
			mp.hexRoll >> c >> mp.hexPitch >> c >> mp.hexYaw >> c >>
			mp.turntable;

	return mp;
}



string
CActionParseBlock::PrepositionToString( const CActionParseBlock::pbTMotionPreposition& mp )
{
	ostringstream ostr;

	ostr << mp.crossbeam << ':' << mp.carriage << ':' <<
			mp.hexX << ':' << mp.hexY << ':' << mp.hexZ << ':' <<
			mp.hexRoll << ':' << mp.hexPitch << ':' << mp.hexYaw << ':' <<
			mp.turntable;

	return ostr.str();
}




