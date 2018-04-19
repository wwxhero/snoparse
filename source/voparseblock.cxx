//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 David Heitbrink
// Date:	 May, 2011
//
// $Id: voparseblock.cxx,v 1.11 2017/10/23 16:43:35 iowa\cschwarz Exp $
//
// The implementation for the Visual Object parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include <algorithm>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVirtualObjectParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "Gateway"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVirtualObjectParseBlock::CVirtualObjectParseBlock()
	: CSnoBlock()
{
	SetBlockName("VirtualObject");
} // end of CVirtualObjectParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVirtualObjectParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CVirtualObjectParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVirtualObjectParseBlock::CVirtualObjectParseBlock(const CVirtualObjectParseBlock& cCopy)
{
	*this = cCopy;
} // end of CVirtualObjectParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~GatewayParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CVirtualObjectParseBlock::~CVirtualObjectParseBlock() {}// end of CVirtualObjectParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CVirtualObjectParseBlock
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
CVirtualObjectParseBlock::CVirtualObjectParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {

} // end of CVirtualObjectParseBlock

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
CVirtualObjectParseBlock&
CVirtualObjectParseBlock::operator=(const CVirtualObjectParseBlock& cRhs)
{
	// Check to make sure that parameter is not me
	if (this != &cRhs) {
		// Call superclass assignment operator
		CSnoBlock::operator=(cRhs);
	}
	return *this;
} // end of operator=

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
CVirtualObjectParseBlock::GetPosition(void) const
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
CVirtualObjectParseBlock::SetPosition(const CPoint3D& position)
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
// Description: GetPosition
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A CPoint3D value for the Draw Position field, This is where
//			the object will be drawn durring the scenario run
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CVirtualObjectParseBlock::GetDrawPosition(void) const
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
} // end of GetPosition

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
CVirtualObjectParseBlock::SetDrawPosition(const CPoint3D& position)
{
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("DrawPosition");

	// Add new "Position" field.
	positionVec.push_back((double)position.m_x);
	positionVec.push_back((double)position.m_y);
	positionVec.push_back((double)position.m_z);

	AddField("DrawPosition", positionVec);

} // end of SetPosition

CPoint2D CVirtualObjectParseBlock::GetDrawScale(void) const{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CPoint2D pos;
	if (GetField("DrawSize", vals)) {
		if (vals.size() != 2) {
			TCountError e("DrawSize", 2);
			throw e;
		}
		pVal = vals.begin();
		pos.m_x = pVal->GetFloatValue();
		pVal++;
		pos.m_y = pVal->GetFloatValue();
		pVal++;
	}
	return pos;
}
void CVirtualObjectParseBlock::SetDrawScale(const CPoint2D& size){
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("DrawSize");

	// Add new "Position" field.
	positionVec.push_back((double)size.m_x);
	positionVec.push_back((double)size.m_y);

	AddField("DrawSize", positionVec);

}
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
CVirtualObjectParseBlock::SetIconName(const string& solName)
{
	// Delete any "SolName" fields
	ClearFields("IconName");

	// Add new "SolName" field.
	AddField("IconName", solName);

} // end of SetSolName

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
CVirtualObjectParseBlock::GetIconName(void) const
{
	CSnoValue val;
	if (GetField("IconName", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetSolName
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
CVirtualObjectParseBlock::SetSolName(const string& solName)
{
	// Delete any "SolName" fields
	ClearFields("SolName");

	// Add new "SolName" field.
	AddField("SolName", solName);

} // end of SetSolName

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
CVirtualObjectParseBlock::GetSolName(void) const
{
	CSnoValue val;
	if (GetField("SolName", val))
		return val.GetStringValue();
	else
		 return "";
} // end of GetSolName
//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetOption
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		int
//
//////////////////////////////////////////////////////////////////////////////
int
CVirtualObjectParseBlock::GetOption(void) const
{
	CSnoValue val;
	if (GetField("Option", val))
		return val.GetIntValue();
	else
		return 0;
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
CVirtualObjectParseBlock::SetOption(int option)
{

	ClearFields("Option");

	// Add new "Option" field.
	AddField("Option", option);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetOrientation
//				
//
// Remarks:		
//
// Arguments: 
//   double orientation - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CVirtualObjectParseBlock::SetOrientation(double orientation)
{
	// Delete any "Orientation" fields
	ClearFields("Orientation");

	// Add new "Orientation" field.
	AddField("Orientation", orientation);
}
//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetOrientation
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		double
//
//////////////////////////////////////////////////////////////////////////////
double
CVirtualObjectParseBlock::GetOrientation(void) const
{
	CSnoValue val;
	if (GetField("Orientation", val))
		return val.GetFloatValue();
	else
		 return 0;
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
CVirtualObjectParseBlock::GetColorIndex(void) const
{
	CSnoValue val;
	if (GetField("ColorIndex", val))
		return val.GetIntValue();
	else
		return 0;
} // end of GetColorIndex
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
CVirtualObjectParseBlock::SetColorIndex(int color)
{
	// Delete any "ColorIndex" fields
	ClearFields("ColorIndex");

	// Add new "ColorIndex" field.
	if (0 != color)
		AddField("ColorIndex", color);

} // end of SetColorIndex

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	solName - a string to which to set the Name field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CVirtualObjectParseBlock::SetName(const string& name)
{
	// Delete any "SolName" fields
	ClearFields("Name");

	// Add new "SolName" field.
	AddField("Name", name);
}

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
CVirtualObjectParseBlock::GetName(void) const
{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return "";
}  // end of GetSolName

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	solName - a string to which to set the Name field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CVirtualObjectParseBlock::SetTargetName(const string& name)
{
	// Delete any "SolName" fields
	ClearFields("TargetName");

	// Add new "SolName" field.
	AddField("TargetName", name);
}

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
CVirtualObjectParseBlock::GetTargetName(void) const
{
	CSnoValue val;
	if (GetField("TargetName", val))
		return val.GetStringValue();
	else
		 return "";
}  // end of GetSolName


void CVirtualObjectParseBlock::SetIsBlinking(bool val){
	// Delete any "SolName" fields
	ClearFields("IsBlinking");

	// Add new "SolName" field.
	AddField("IsBlinking", val?1:0);
}
bool CVirtualObjectParseBlock::GetIsBlinking() const{
	CSnoValue val;
	if (GetField("IsBlinking", val))
		return val.GetIntValue() > 0;
	else
		 return false;
}

float CVirtualObjectParseBlock::GetBlinkOnDurr() const{
	CSnoValue val;
	if (GetField("BlinkOn", val))
		return (float)val.GetFloatValue();
	else
		 return 1.0f;
}
void CVirtualObjectParseBlock::SetBlinkOnDurr(float val){
	// Delete any "SolName" fields
	ClearFields("BlinkOn");

	// Add new "SolName" field.
	AddField("BlinkOn", val);
}

void CVirtualObjectParseBlock::SetBlinkOffDurr(float val){
	// Delete any "SolName" fields
	ClearFields("BlinkOff");

	// Add new "SolName" field.
	AddField("BlinkOff", val);
}
float CVirtualObjectParseBlock::GetBlinkOffDurr() const{
	CSnoValue val;
	if (GetField("BlinkOff", val))
		return (float)val.GetFloatValue();
	else
		 return 1.0f;
}
void CVirtualObjectParseBlock::SetColor(float r, float g, float b, float a){
	vector<double> vals;
	vals.push_back(r);
	vals.push_back(g);
	vals.push_back(b);
	vals.push_back(a);

	// Delete any "InitVelRPY" fields
	ClearFields("FillColor");

	// Add fields to the list
	AddField("FillColor", vals);
}
void CVirtualObjectParseBlock::GetColor(float &r, float &g, float &b, float &a)const{
	r= 0; g = 0; b = 0; a = 0;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("FillColor", vals)) {
		if (vals.size() < 3)
			return;
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		r = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		g = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		b = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		a = (float)val;
	}
}


void CVirtualObjectParseBlock::SetBoarderColor(float r, float g, float b, float a){
	vector<double> vals;
	vals.push_back(r);
	vals.push_back(g);
	vals.push_back(b);
	vals.push_back(a);

	// Delete any "InitVelRPY" fields
	ClearFields("BoarderColor");

	// Add fields to the list
	AddField("BoarderColor", vals);
}
void CVirtualObjectParseBlock::GetBoarderColor(float &r, float &g, float &b, float &a)const{
	r= 0; g = 0; b = 0; a = 0;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("BoarderColor", vals)) {
		if (vals.size() < 3)
			return;
		// Assemble values
		pVal = vals.begin();
		double val = pVal->GetFloatValue();
		r = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		g = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		b = (float)val;
		pVal++;
		val = pVal->GetFloatValue();
		a = (float)val;
	}
}
void CVirtualObjectParseBlock::SetType(short type){
	// Delete any "SolName" fields
	ClearFields("DrawType");

	// Add new "SolName" field.
	AddField("DrawType", type);

}
short CVirtualObjectParseBlock::GetType() const{
	CSnoValue val;
	if (GetField("DrawType", val))
		return val.GetIntValue();
	else
		 return 1;

}

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
CVirtualObjectParseBlock::GetCrRad(void) const
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
CVirtualObjectParseBlock::GetActvDel(void) const
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
CVirtualObjectParseBlock::GetLifetime(void) const
{
	CSnoValue val;
	if (GetField("Lifetime", val))
		return val.GetFloatValue();
	else
		 return 0.0f;
} // end of GetLifetime


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
CVirtualObjectParseBlock::SetCrRad(double crRad)
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
CVirtualObjectParseBlock::SetActvDel(double actvDel)
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
CVirtualObjectParseBlock::SetLifetime(double lifetime)
{
	// Delete any "Lifetime" fields
	ClearFields("Lifetime");

	// Add new "Lifetime" field.
	AddField("Lifetime", lifetime);

} // end of SetLifetime

void 
CVirtualObjectParseBlock::GetStateMatrix(vector<TStatePoint> &states) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	states.clear();
	
	CVirtualObjectParseBlock::TStatePoint point;
	if (GetField("States", vals)) {
		//if (vals.size() % 5 != 0) {
		//	TCountError e("State", 5);
		//	throw e;
		//}
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			point.colorBorder[0] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorBorder[1] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorBorder[2] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorBorder[3] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorFill[0] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorFill[1] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorFill[2] = (float)pVal->GetFloatValue();
			pVal++;
			point.colorFill[3] = (float)pVal->GetFloatValue();

			pVal++;
			point.frameLength = (float)pVal->GetFloatValue();

			pVal++;
			point.scale[0] = (float)pVal->GetFloatValue();
			pVal++;
			point.scale[1] = (float)pVal->GetFloatValue();
			pVal++;
			point.scale[2] = (float)pVal->GetFloatValue();

			pVal++;
			point.type = pVal->GetIntValue();

			pVal++;

			point.group = pVal->GetIntValue();
			pVal++;


			string currVal = pVal->GetStringValue();
			memset(point.IconName,0,sizeof(point.IconName));
			memcpy(point.IconName,currVal.c_str(),
				min(sizeof(char) * currVal.size(),sizeof(point.IconName)));

			states.push_back(point);
		}
	}
	return;
} // end of GetTraj


//////////////////////////////////////////////////////////////////////////////
//
// Description: SetTraj
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//	trajs - a TTrajPoint vector to which to set the Traj field
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CVirtualObjectParseBlock::SetStateMatrix(const vector<CVirtualObjectParseBlock::TStatePoint> &states)
{
	vector<CVirtualObjectParseBlock::TTStatePoint>::const_iterator itr;
	vector<double> trajsVec;
	CSnoValue val;
	// Delete any "Traj" fields
	ClearFields("States");

	// Add fields to the list
	for (itr = states.begin(); itr != states.end(); itr++) {
		AddField("States",itr->colorBorder[0]);
		AddField("States",itr->colorBorder[1]);
		AddField("States",itr->colorBorder[2]);
		AddField("States",itr->colorBorder[3]);
		AddField("States",itr->colorFill[0]); 
		AddField("States",itr->colorFill[1]); 
		AddField("States",itr->colorFill[2]);
		AddField("States",itr->colorFill[3]);
		AddField("States",itr->frameLength);
		AddField("States",itr->scale[0]); 
		AddField("States",itr->scale[1]); 
		AddField("States",itr->scale[2]); 
		AddField("States",itr->type);
		AddField("States",itr->group);
		AddField("States",itr->IconName);
	}
} // end of SetTraj

//////////////////////////////////////////////////////////////////////////////
///\brief
///		This function deletes any Screen fields and then adds a new Screen field
///\param [in] val  - A Screen
///\returns void
/////////////////////////////////////////////////////////////////////////////////
void CVirtualObjectParseBlock::SetScreen(EScreen val)
{
	// Delete any "Screen" fields
	ClearFields("Screen");

	AddField("Screen", (int)val);
}

//////////////////////////////////////////////////////////////////////////////
///\brief This function gets the Screen field value and returns an enumerator
///       for the screen type
///       
///\returns EScreen - Enumerator that holds the values of each of the screens type
/////////////////////////////////////////////////////////////////////////////////
CVirtualObjectParseBlock::EScreen 
CVirtualObjectParseBlock::GetScreen() const
{
	CSnoValue val;
	if (GetField("Screen", val))
	{
		return IntToScreen(val.GetIntValue());
	}
	else
	{
		return CVirtualObjectParseBlock::eMainScreen;
	}
}

//////////////////////////////////////////////////////////////////////////////
///\brief Converts integer values to enumerators and returns the appropriate
///       enumerator dependent on the screen selection
///\param [in] val  - casted integer of the Screen 
///\returns Enumerator of the Screen type
/////////////////////////////////////////////////////////////////////////////////
CVirtualObjectParseBlock::EScreen 
CVirtualObjectParseBlock::IntToScreen(int val)
{
	if(val == 1)
	{
		return CVirtualObjectParseBlock::eMainScreen;
	}
	else if(val == 2)
	{
		return  CVirtualObjectParseBlock::eInstPanel;
	}
	else
	{
		return  CVirtualObjectParseBlock::eInvalid;
	}
}

//////////////////////////////////////////////////////////////////////////////
///\brief sets a unique ID for this snoparse block
///       
///\returns ID - Id of the value
/////////////////////////////////////////////////////////////////////////////////
int
CVirtualObjectParseBlock::GetPreCreateId() const
{
	CSnoValue val;
	if (GetField("VirtObjModelID", val))
	{
		return val.GetIntValue();
	}
	else
	{
		return -1;
	}
}

//////////////////////////////////////////////////////////////////////////////
///\brief gets a unique ID for this snoparse block
///\param [in] id  -id of the value
///\returns Enumerator of the Screen type
/////////////////////////////////////////////////////////////////////////////////
void
CVirtualObjectParseBlock::SetPreCreateId(int val)
{
	// Delete any "Screen" fields
	ClearFields("VirtObjModelID");

	AddField("VirtObjModelID", (int)val);
}
