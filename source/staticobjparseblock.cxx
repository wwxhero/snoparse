//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Matt Schikore
// Date:	 May, 2000
//
// $Id: staticobjparseblock.cxx,v 1.13 2015/07/31 15:42:19 IOWA\dheitbri Exp $
//
// The implementation for the staticobj parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "StaticObj"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CStaticObjParseBlock::CStaticObjParseBlock()
	: CSnoBlock()
{
	SetBlockName("StaticObject");
} // end of CStaticObjParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CStaticObjParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CStaticObjParseBlock::CStaticObjParseBlock(const CStaticObjParseBlock& cCopy)
{
	*this = cCopy;
} // end of CStaticObjParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~TrafLghtMngrParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CStaticObjParseBlock::~CStaticObjParseBlock() 
{}// end of CStaticObjParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock
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
CStaticObjParseBlock::CStaticObjParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CStaticObjParseBlock

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
CStaticObjParseBlock&
CStaticObjParseBlock::operator=(const CStaticObjParseBlock& cRhs)
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
CStaticObjParseBlock::GetSolName(void) const
{
	CSnoValue val;
	if (GetField("SolName", val))
		return val.GetStringValue();
	else
		 return "";
}  // end of GetSolName

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
CStaticObjParseBlock::GetName(void) const
{
	CSnoValue val;
	if (GetField("Name", val))
		return val.GetStringValue();
	else
		 return "";
}  // end of GetSolName

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
CStaticObjParseBlock::GetPosition(void) const
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
CStaticObjParseBlock::GetOrientation(void) const
{
	CSnoValue val;
	if (GetField("Orientation", val))
		return val.GetFloatValue();
	else
		 return 0;
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetIsNewObj
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		bool
//
//////////////////////////////////////////////////////////////////////////////
bool
CStaticObjParseBlock::GetIsNewObj(void) const
{
	CSnoValue val;
	if (GetField("IsNewObj", val))
		return val.GetIntValue() != 0;
	else
		return true;
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetAudioState
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
CStaticObjParseBlock::GetAudioState(void) const
{
	CSnoValue val;
	if (GetField("AudioState", val))
		return val.GetIntValue();
	else
		return 0;
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetVisualState
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
CStaticObjParseBlock::GetVisualState(void) const
{
	CSnoValue val;
	if (GetField("VisualState", val))
		return val.GetIntValue();
	else
		return 0;
}


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
CStaticObjParseBlock::GetOption(void) const
{
	CSnoValue val;
	if (GetField("Option", val))
		return val.GetIntValue();
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetCompositePieces
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		vector<string>
//
//////////////////////////////////////////////////////////////////////////////
vector<CStaticObjParseBlock::TCompositePiece>
CStaticObjParseBlock::GetCompositePieces(void) const
{
	vector<TCompositePiece> retVal;

	vector<CSnoValue> sol, cigi, option, optionCigi;
	CSnoBlock::cTValueIterator pVal1, pVal2, pVal3, pVal4;
	if (GetField("CompSol", sol) && GetField("CompCigi", cigi) &&
				GetField("CompOpt", option) && GetField("CompOptCigi", optionCigi)) {
		pVal1 = sol.begin();
		pVal2 = cigi.begin();
		pVal3 = option.begin();
		pVal4 = optionCigi.begin();
		while (pVal1 != sol.end()) {
			TCompositePiece piece;
			piece.solName = pVal1->GetStringValue();
			piece.cigiId = pVal2->GetIntValue();
			piece.option = pVal3->GetIntValue();
			piece.optionCigiId = pVal4->GetIntValue();
			retVal.push_back(piece);
			pVal1++;
			pVal2++;
			pVal3++;
			pVal4++;
		}
	}
	return retVal;
}

void
CStaticObjParseBlock::SetCompositePieces(const vector<TCompositePiece>& pieces)
{
	ClearFields("CompSol");
	ClearFields("CompCigi");
	ClearFields("CompOpt");
	ClearFields("CompOptCigi");

	if (!pieces.size()) return;

	vector<string> sol;
	vector<int> cigi, option, optionCigi;

	for (vector<TCompositePiece>::const_iterator i = pieces.begin(); i != pieces.end(); i++) {
		sol.push_back(i->solName);
		cigi.push_back(i->cigiId);
		option.push_back(i->option);
		optionCigi.push_back(i->optionCigiId);
	}
	AddField("CompSol", sol);
	AddField("CompCigi", cigi);
	AddField("CompOpt", option);
	AddField("CompOptCigi", optionCigi);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetSolOptions
//				
//
// Remarks:		
//
// Arguments: 
//   void - 
//
// Returns:		vector<string>
//
//////////////////////////////////////////////////////////////////////////////
vector<string>
CStaticObjParseBlock::GetSolOptions(void) const
{
	vector<string> retVal;

	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	if (GetField("SolOptions", vals)) {
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			retVal.push_back( pVal->GetStringValue() );
		}
	}
	return retVal;
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
CStaticObjParseBlock::GetColorIndex(void) const
{
	CSnoValue val;
	if (GetField("ColorIndex", val))
		return val.GetIntValue();
	else
		return 0;
} // end of GetColorIndex




//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetCrdr
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
CStaticObjParseBlock::GetCrdr(void) const
{
	CSnoValue val;
	if (GetField("Crdr", val))
		return val.GetIntValue();
	else
		return 0;
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::GetHoldOffs
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
CStaticObjParseBlock::GetHoldOffs(void) const
{
	CSnoValue val;
	if (GetField("HoldOffs", val))
		return val.GetIntValue();
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetSignGrabberPos
//	DESCRIPTION - Gets the location of the sign's grabber
//
// Remarks:
//
// Arguments:
//	void
//
// Returns: pos - the position of the grabber
//
//////////////////////////////////////////////////////////////////////////////
CPoint3D
CStaticObjParseBlock::GetDrawPosition(void)const
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
	else{
		pos.m_x = NULL;
		pos.m_y = NULL;
		pos.m_z = NULL;
	}
	return pos;
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
CStaticObjParseBlock::SetSolName(const string& solName)
{
	// Delete any "SolName" fields
	ClearFields("SolName");

	// Add new "SolName" field.
	AddField("SolName", solName);
}


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
CStaticObjParseBlock::SetName(const string& name)
{
	// Delete any "SolName" fields
	ClearFields("Name");

	// Add new "SolName" field.
	AddField("Name", name);
}

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
CStaticObjParseBlock::SetPosition(const CPoint3D& position)
{
	vector<double> positionVec;
	// Delete any "Position" fields
	ClearFields("Position");

	// Add new "Position" field.
	positionVec.push_back((double)position.m_x);
	positionVec.push_back((double)position.m_y);
	positionVec.push_back((double)position.m_z);

	AddField("Position", positionVec);
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
CStaticObjParseBlock::SetOrientation(double orientation)
{
	// Delete any "Orientation" fields
	ClearFields("Orientation");

	// Add new "Orientation" field.
	AddField("Orientation", orientation);
}


//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetIsNewObj
//				
//
// Remarks:		
//
// Arguments: 
//   bool isNew - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetIsNewObj(bool isNew)
{
	// Delete any "IsNewObj" fields
	ClearFields("IsNewObj");

	// Add new "IsNewObj" field.
	AddField("IsNewObj", isNew ? 1 : 0);
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetAudioState
//				
//
// Remarks:		
//
// Arguments: 
//   int audioState - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetAudioState(int audioState)
{
	// Delete any "AudioState" fields
	ClearFields("AudioState");

	// Add new "AudioState" field.
	AddField("AudioState", audioState);
}



//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetVisualState
//				
//
// Remarks:		
//
// Arguments: 
//   int visualState - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetVisualState(int visualState)
{

	ClearFields("VisualState");

	// Add new "VisualState" field.
	AddField("VisualState", visualState);
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
CStaticObjParseBlock::SetOption(int option)
{

	ClearFields("Option");

	// Add new "Option" field.
	AddField("Option", option);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetSolOptions
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
CStaticObjParseBlock::SetSolOptions(const vector<string>& options)
{

	ClearFields("SolOptions");

	// Add new "Option" field.
	AddField("SolOptions", options);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetCrdr
//				
//
// Remarks:		
//
// Arguments: 
//   int crdr - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetCrdr(int crdr)
{

	ClearFields("Crdr");

	// Add new "Crdr" field.
	AddField("Crdr", crdr);
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: CStaticObjParseBlock::SetHoldOffs
//				
//
// Remarks:		
//
// Arguments: 
//   int holdoffs - 
//
// Returns:		void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetHoldOffs(int holdoffs)
{

	ClearFields("HoldOffs");

	// Add new "HoldOffs" field.
	AddField("HoldOffs", holdoffs);
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
CStaticObjParseBlock::SetColorIndex(int color)
{
	// Delete any "ColorIndex" fields
	ClearFields("ColorIndex");

	// Add new "ColorIndex" field.
	if (0 != color)
		AddField("ColorIndex", color);

} // end of SetColorIndex

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetDrawPosition
//	DESCRIPTION - Sets the position of the sign's grabber
//
// Remarks:
//
// Arguments:
//	grabberPos - Location of the sign's grabber
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CStaticObjParseBlock::SetDrawPosition(const CPoint3D& drawPos)
{
	vector<double> positionVec;
	// Delete any "DrawPosition" fields
	ClearFields("DrawPosition");

	// Add new "DrawPosition" field.
	positionVec.push_back((double)drawPos.m_x);
	positionVec.push_back((double)drawPos.m_y);
	positionVec.push_back((double)drawPos.m_z);

	AddField("DrawPosition", positionVec);
}