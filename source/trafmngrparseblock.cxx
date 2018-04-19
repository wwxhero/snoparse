//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: trafmngrparseblock.cxx,v 1.18 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The implementation for the trafmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
// Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafMngrParseBlock
//	Default constructor calls the superclass constructor.
//
// Remarks: The name of the block is set to "TrafficManager"
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafMngrParseBlock::CTrafMngrParseBlock()
	: CSnoBlock()
{
	SetBlockName("TrafficManager");
} // end of CTrafMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafMngrParseBlock
//	Copy constructor calls the assignment operator.
//
// Remarks:
//
// Arguments:
//	cCopy - CTrafMngrParseBlock to copy to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafMngrParseBlock::CTrafMngrParseBlock(const CTrafMngrParseBlock& cCopy)
{
	*this = cCopy;
} // end of CTrafMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: ~TrafMngrParseBlock
//	Default destructor does nothing.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CTrafMngrParseBlock::~CTrafMngrParseBlock() {}// end of CTrafMngrParseBlock

//////////////////////////////////////////////////////////////////////////////
//
// Description: CTrafMngrParseBlock
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
CTrafMngrParseBlock::CTrafMngrParseBlock(const CSnoBlock& blk)
	: CSnoBlock(blk) {} // end of CTrafMngrParseBlock

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
CTrafMngrParseBlock&
CTrafMngrParseBlock::operator=(const CTrafMngrParseBlock& cRhs)
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
// Description: GetInputSets
// 	Returns a TInputSet for each sub-block of the current block.
//
// Remarks:
//
// Arguments:
//
// Returns: A STL vector<TInputSet> value for the all InputSet 
// 	sub-blocks.
//
//////////////////////////////////////////////////////////////////////////////
vector<CTrafMngrParseBlock::TInputSet>
CTrafMngrParseBlock::GetInputSets(void) const
{
	CSnoValue val;
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<TInputSet> inputSets;
	CSnoBlock::cTChildIterator pChild;
	TInputSet input;
	char *pCurrPos = NULL;
	for (pChild = BeginChild(); pChild != EndChild(); pChild++) {
		if (pChild->GetField("Name", val)) 
			input.name = val.GetStringValue();
		else
			input.name = "";

		if (pChild->GetField("MinDensity", val))
			input.minDensity = val.GetFloatValue();
		else
			input.minDensity = 0.0f;

		if (pChild->GetField("MaxDensity", val))
			input.maxDensity = val.GetFloatValue();
		else
			input.maxDensity = 0.0f;

		if (pChild->GetField("MaxObjects", val))
			input.maxObjects = val.GetIntValue();
		else
			input.maxObjects = 0;

		if (pChild->GetField("CreateDist", val))
			input.createDist = val.GetFloatValue();
		else
			input.createDist = 0.0f;

		if (pChild->GetField("DeleteDist", val))
			input.deleteDist = val.GetFloatValue();
		else
			input.deleteDist = 0.0f;

		if (pChild->GetField("AbsDeleteDist", val))
			input.absDeleteDist = val.GetFloatValue();
		else
			input.absDeleteDist = 0.0f;

		if (pChild->GetField("RunFreq", val))
			input.runFreq = val.GetFloatValue();
		else
			input.runFreq = 0.0f;

		input.totalWeights = 0;
		input.solWeights.clear();
		if (pChild->GetField("SolWeights", vals)) {
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

				input.totalWeights += weight.weight;
				input.solWeights.push_back(weight);
				delete [] pBuf;
			}
		}
		inputSets.push_back(input);
	}
	return inputSets;
} // end of GetInputSets

//////////////////////////////////////////////////////////////////////////////
// Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: SetInputSets
// 	Creates a sub-block for each item in the TInputSet vector.
//
// Remarks:
//
// Arguments:
//	inputSets - a vector of TInputSet instances with which to initialize the 
//		sub-blocks.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafMngrParseBlock::SetInputSets(
		const vector<CTrafMngrParseBlock::TInputSet>& inputSets)
{
	CSnoBlock child("InputSet");
	vector<TInputSet>::const_iterator itr;
	vector<TWeight>::const_iterator wItr;
	
	// Delete all sub-blocks
	ClearChildren();

	// Create, initialize, and add new sub-block for each TInputSet
	for (itr = inputSets.begin(); itr != inputSets.end(); itr++) {

		child.ClearFields();

		child.AddField("Name", itr->name);
		child.AddField("MinDensity", itr->minDensity);
		child.AddField("MaxDensity", itr->maxDensity);
		child.AddField("MaxObjects", itr->maxObjects);
		child.AddField("CreateDist", itr->createDist);
		child.AddField("DeleteDist", itr->deleteDist);
		child.AddField("AbsDeleteDist", itr->absDeleteDist);
		child.AddField("RunFreq", itr->runFreq);

		if (!itr->solWeights.empty()) {
			vector<string> solWeights;
			for (wItr = itr->solWeights.begin(); 
				 wItr != itr->solWeights.end(); wItr++) {

				// Initialize the field value
				string weight = wItr->name;
				char intWght[20];
				sprintf(intWght, ":%d", wItr->weight);
				weight += intWght;

				solWeights.push_back(weight);
			}
			// Add field to the list
			child.AddField("SolWeights", solWeights);
		}
		// Add child to block
		AddChild(child);
	}
	
} // end of SetInputSets

//////////////////////////////////////////////////////////////////////////////
//
// Description: AddInputSet
// 	Adds a sub-block for the parameter.
//
// Remarks:
//
// Arguments:
//	inputSet - a TInputSet instances with which to initialize the new
//		sub-block.
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafMngrParseBlock::AddInputSet(
		const CTrafMngrParseBlock::TInputSet& inputSet)
{
	CSnoBlock child("InputSet");
	vector<TWeight>::const_iterator wItr;
	
	// Create, initialize, and add new sub-block for the parameter
	child.AddField("Name", inputSet.name);
	child.AddField("MinDensity", inputSet.minDensity);
	child.AddField("MaxDensity", inputSet.maxDensity);
	child.AddField("MaxObjects", inputSet.maxObjects);
	child.AddField("CreateDist", inputSet.createDist);
	child.AddField("DeleteDist", inputSet.deleteDist);
	child.AddField("AbsDeleteDist", inputSet.absDeleteDist);
	child.AddField("RunFreq", inputSet.runFreq);

	if (!inputSet.solWeights.empty()) {
		vector<string> solWeights;
		for (wItr = inputSet.solWeights.begin(); 
			 wItr != inputSet.solWeights.end(); wItr++) {
	
			// Initialize the field value
			string weight = wItr->name;
			char intWght[20];
			sprintf(intWght, ":%d", wItr->weight);
			weight += intWght;

			solWeights.push_back(weight);
		}
		// Add field to the list
		child.AddField("SolWeights", solWeights);
	}
	// Add child to block
	AddChild(child);
	
} // end of AddInputSet

//////////////////////////////////////////////////////////////////////////////
//
// Description: ClearInputSets
// 	Clears all InputSet sub-block from the current instance.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CTrafMngrParseBlock::ClearInputSets(void) 
{
	ClearChildren();
} // end of ClearInputSets

