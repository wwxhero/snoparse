/////////////////////////////////////////////////////////////////////////////
// 
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     September, 1998
//
// $Id: main.cxx,v 1.9 2000/03/27 18:33:25 jvogel Exp $
//
// This file contains test code for the CSnoParser and its associated classes.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include "snoparse.h"
#include <math.h>

// Data used in tests
#ifdef _WIN32
string data = 
	"Header\n"
	"  LongComment \"long comment\" \n"
	"  LongComment \" with line breaks and \" \n"
	"  LongComment \" \teverything.\" \n"
	"  LriFile \"ipte.bli\" \n"
	"  ShortComment \"testing123\" \n"
	"&&&&End&&&&\n"
	"HCSM TrajFollower\n"
	"  ActvDel 0.0000000E+000 \n"
	"  CrRad 0.0000000E+000 \n"
	"  Dependent 0 \n"
	"  InitHeading -1.5700001E+000 \n"
	"  InitZ 0.0000000E+000 \n"
	"  Lifetime 0.0000000E+000 \n"
	"  Lights 0 \n"
	"  Name \"Ped1\" \n"
	"  QuitAtEnd 0 \n"
	"  SolName \"AdultMale\" \n"
	"  Sound 5 \n"
	"  Traj 5.3067163E+002 4.3205262E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 5.7802856E+002 4.3206055E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 6.2621069E+002 4.3206316E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 6.9764008E+002 4.3206129E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 7.4763306E+002 4.3207223E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 8.5319489E+002 4.3210836E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 8.8475098E+002 4.3211781E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 9.8115485E+002 4.3210434E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 1.1027009E+003 4.3211051E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"&&&&End&&&&\n";

string blocks [] = {
	"Header\n"
	"  LongComment \"long comment\" \n"
	"  LongComment \" with line breaks and \" \n"
	"  LongComment \" \teverything.\" \n"
	"  LriFile \"ipte.bli\" \n"
	"  ShortComment \"testing123\" \n"
	"&&&&End&&&&\n", 

	"HCSM TrajFollower\n"
	"  ActvDel 0.0000000E+000 \n"
	"  CrRad 0.0000000E+000 \n"
	"  Dependent 0 \n"
	"  InitHeading -1.5700001E+000 \n"
	"  InitZ 0.0000000E+000 \n"
	"  Lifetime 0.0000000E+000 \n"
	"  Lights 0 \n"
	"  Name \"Ped1\" \n"
	"  QuitAtEnd 0 \n"
	"  SolName \"AdultMale\" \n"
	"  Sound 5 \n"
	"  Traj 5.3067163E+002 4.3205262E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 5.7802856E+002 4.3206055E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 6.2621069E+002 4.3206316E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 6.9764008E+002 4.3206129E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 7.4763306E+002 4.3207223E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 8.5319489E+002 4.3210836E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 8.8475098E+002 4.3211781E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 9.8115485E+002 4.3210434E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"  Traj 1.1027009E+003 4.3211051E+004 2.7801762E-042 3.9895617E-038 2.7801762E-042 \n"
	"&&&&End&&&&\n",

	"HCSM ScoobyBlock\n"
	"  Scooby \"Hey, Scooby!\" \"Scoobysnacks?\" \n"
	"  Shaggy 1 \n"
	"  Shaggy 2 \n"
	"  Velma 3.4132559E+000 \n"
	"    HCSM ScrappyBlock\n"
	"      Nephew \"or Scooby's bastard?\" \n"
	"    &&&&End&&&&\n"
	"&&&&End&&&&\n"
};

#else
string data = 
	"Header\n"
	"  LongComment \"long comment\" \n"
	"  LongComment \" with line breaks and \" \n"
	"  LongComment \" \teverything.\" \n"
	"  LriFile \"ipte.bli\" \n"
	"  ShortComment \"testing123\" \n"
	"&&&&End&&&&\n"
	"HCSM TrajFollower\n"
	"  ActvDel 0.0000000E+00 \n"
	"  CrRad 0.0000000E+00 \n"
	"  Dependent 0 \n"
	"  InitHeading -1.5700001E+00 \n"
	"  InitZ 0.0000000E+00 \n"
	"  Lifetime 0.0000000E+00 \n"
	"  Lights 0 \n"
	"  Name \"Ped1\" \n"
	"  QuitAtEnd 0 \n"
	"  SolName \"AdultMale\" \n"
	"  Sound 5 \n"
	"  Traj 5.3067163E+02 4.3205262E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 5.7802856E+02 4.3206055E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 6.2621069E+02 4.3206316E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 6.9764008E+02 4.3206129E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 7.4763306E+02 4.3207223E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 8.5319489E+02 4.3210836E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 8.8475098E+02 4.3211781E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 9.8115485E+02 4.3210434E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 1.1027009E+03 4.3211051E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
	"&&&&End&&&&\n";

string blocks [] = {
	"Header\n"
	"  LongComment \"long comment\" \n"
	"  LongComment \" with line breaks and \" \n"
	"  LongComment \" \teverything.\" \n"
	"  LriFile \"ipte.bli\" \n"
	"  ShortComment \"testing123\" \n"
	"&&&&End&&&&\n", 

	"HCSM TrajFollower\n"
	"  ActvDel 0.0000000E+00 \n"
	"  CrRad 0.0000000E+00 \n"
	"  Dependent 0 \n"
	"  InitHeading -1.5700001E+00 \n"
	"  InitZ 0.0000000E+00 \n"
	"  Lifetime 0.0000000E+00 \n"
	"  Lights 0 \n"
	"  Name \"Ped1\" \n"
	"  QuitAtEnd 0 \n"
	"  SolName \"AdultMale\" \n"
	"  Sound 5 \n"
	"  Traj 5.3067163E+02 4.3205262E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 5.7802856E+02 4.3206055E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 6.2621069E+02 4.3206316E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 6.9764008E+02 4.3206129E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 7.4763306E+02 4.3207223E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 8.5319489E+02 4.3210836E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 8.8475098E+02 4.3211781E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 9.8115485E+02 4.3210434E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
  	"  Traj 1.1027009E+03 4.3211051E+04 0.0000000E+00 3.9895617E-38 0.0000000E+00 \n"
	"&&&&End&&&&\n",

	"HCSM ScoobyBlock\n"
	"  Scooby \"Hey, Scooby!\" \"Scoobysnacks?\" \n"
	"  Shaggy 1 \n"
	"  Shaggy 2 \n"
	"  Velma 3.4132559E+00 \n"
	"    HCSM ScrappyBlock\n"
	"      Nephew \"or Scooby's bastard?\" \n"
	"    &&&&End&&&&\n"
	"&&&&End&&&&\n"
};
#endif

//////////////////////////////////////////////////////////////////////////////
//
// Description: TestHeader
//	Tests the functions for CHeaderParseBlock.
//
// Remarks: Tests the following functions:
//	CSnoParser::Parse
//		CSnoBlock::Parse
//			CSnoBlock::GetLine
//				CSnoBlock::IsEmptyLine
//			CSnoBlock::Tokenize
//			CSnoBlock::ClearAll
//			CSnoBlock::ClearFields
//				CSnoBlock::ClearChildren
//			CSnoBlock::AddChild
//			CSnoField::SetName
//			CSnoField::AddValue
//			CSnoField::GetName
//
//	CSnoParser::Store
//		CSnoBlock::Store
//		CSnoField::GetName
//		CSnoField::Begin
//		CSnoField::End
//		CSnoField::GetStringRep
//
//	CHeaderParseBlock::GetDate
//		CSnoBlock::GetField
//		CSnoField::GetStringValue
//	CHeaderParseBlock::SetDate
//		CSnoBlock::GetField
//		CSnoField::Clear
//		CSnoField::AddValue
//	CHeaderParseBlock::GetShortComment
//		CSnoBlock::GetField
//		CSnoField::GetStringValue
//	CHeaderParseBlock::SetShortComment
//		CSnoBlock::GetField
//		CSnoField::Clear
//		CSnoField::AddValue
//	CHeaderParseBlock::GetLongComment
//		CSnoBlock::GetField
//		CSnoField::Begin
//		CSnoField::End
//	CHeaderParseBlock::SetLongComment
//		CSnoBlock::GetField
//		CSnoField::Clear
//		CSnoField::AddValue
//	CHeaderParseBlock::GetLriFile
//		CSnoBlock::GetField
//		CSnoField::GetStringValue
//	CHeaderParseBlock::SetLriFile
//		CSnoBlock::GetField
//		CSnoField::Clear
//		CSnoField::AddValue
//
// Arguments:
//	err - If the function returns false, this contains the error description.
//	verbose - If true, then some debugging messages are printed.  Otherwise, 
//		nothing is printed.	
//
// Returns: True if the test was successful, false otherwise.
//
//////////////////////////////////////////////////////////////////////////////
bool TestHeader(string& err, int verbose)
{
	CSnoBlock snoBlock;
	snoBlock.Parse(blocks[0]);
	CHeaderParseBlock headerBlock(snoBlock);
	CHeaderParseBlock newHeader;
	string empty("");
	string origStr, newStr, origStr2;
	headerBlock.Store(origStr);

	newHeader.SetBlockName(headerBlock.GetBlockName());

	string date = headerBlock.GetDate();
	if (date.compare(empty) != 0) {
		newHeader.SetDate(date);
		headerBlock.SetDate(date);
	}
		
	string lriFile = headerBlock.GetLriFile();
	if (lriFile.compare(empty) != 0) {
		newHeader.SetLriFile(lriFile);
		headerBlock.SetLriFile(lriFile);
	}

	string shortComment = headerBlock.GetShortComment();
	if (shortComment.compare(empty) != 0) {
		newHeader.SetShortComment(shortComment);
		headerBlock.SetShortComment(shortComment);
	}

	string longComment = headerBlock.GetLongComment();
	if (longComment.compare(empty) != 0) {
		newHeader.SetLongComment(longComment);
		headerBlock.SetLongComment(longComment);
	}

	newHeader.Store(newStr);
	if (origStr != newStr) {

		if (verbose) {

			cout << "Original: " << endl;
			cout << origStr << endl;
			cout << "Created: " << endl;
			cout << newStr << endl;
		}
		err = "Created Header block did not match original.";
		return false;
	}

	headerBlock.Store(origStr2);
	if (origStr != origStr2) {

		if (verbose) {

			cout << "Original: " << endl;
			cout << origStr << endl;
			cout << "Original after setting: " << endl;
			cout << origStr2 << endl;
		}
		err = "Set original Header block did not match original.";
		return false;
	}
	return true;
} // end of TestHeader

//////////////////////////////////////////////////////////////////////////////
//
// Description: TestParser
//	Tests the functions for the basic classes associated with CSnoParser.
//
// Remarks: Tests the following functions:
//	CSnoParser::Parse
//		CSnoBlock::Parse
//			CSnoBlock::GetLine
//				CSnoBlock::IsEmptyLine
//			CSnoBlock::Tokenize
//			CSnoBlock::ClearAll
//			CSnoBlock::ClearFields
//				CSnoBlock::ClearChildren
//			CSnoBlock::AddChild
//			CSnoField::SetName
//			CSnoField::AddValue
//			CSnoField::GetName
//
//	CSnoParser::Store
//		CSnoBlock::Store
//		CSnoField::GetName
//		CSnoField::Begin
//		CSnoField::End
//		CSnoField::GetStringRep
//
//	CSnoBlock::SetName
//	CSnoBlock::AddField
//	CSnoBlock::GetFieldCount
//	CSnoBlock::BeginField
//	CSnoBlock::EndField
//	CSnoBlock::GetChildCount
//	CSnoBlock::BeginChild
//	CSnoBlock::EndChild
//	CSnoBlock::GetField
//
//	CSnoParser::AddBlock
//	CSnoParser::GetBlockCount
//	CSnoParser::Begin
//	CSnoParser::End
//	CSnoParser::Clear
// 	
// Arguments:
//	err - If the function returns false, this contains the error description.
//	verbose - If true, then some debugging messages are printed.  Otherwise, 
//		nothing is printed.	
//
// Returns: True if the test was successful, false otherwise.
//
//////////////////////////////////////////////////////////////////////////////
bool TestParser(string& err, int verbose)
{
	CSnoParser parser;
	if (!parser.Parse(data)) {
		err = "Error parsing data";
		return false;
	}
	
	string checkData;
	parser.Store(checkData);
	if (data.compare(checkData) != 0) {
	
		if (verbose) {

			if (data.size() != checkData.size()) 
				cout << "Original size: " << data.size() << " != "
					 << "check size: " << checkData.size() << endl;
			cout << "Original data: " << endl;
			cout << data << endl;
			cout << "Result of store: " << endl;
			cout << checkData << endl;
		}

		err = "Store did not reproduce data";
		return false;
	}

	CSnoBlock scooby;
	scooby.SetBlockName("ScoobyBlock");
	if (scooby.GetBlockName().compare("ScoobyBlock")) {
		err = "ScoobyBlock: Incorrect block name found";
		return false;
	}

	vector<string> scoobyStr;
	scoobyStr.push_back("Hey, Scooby!");
	scoobyStr.push_back("Scoobysnacks?");

	scooby.AddField("Scooby", scoobyStr);
	scooby.AddField("Shaggy", 1);
	scooby.AddField("Shaggy", 2);
	scooby.AddField("Velma", 3.413256f);

	if (scooby.GetFieldCount() != 4) {
		err = "ScoobyBlock: Incorrect field count found.";
		return false;
	}
	CSnoBlock::cTFieldIterator fldItr;
	CSnoBlock::cTValueIterator valItr;
	int fldCnt;
	for (fldCnt = 0, fldItr = scooby.BeginField(); 
		 fldItr != scooby.EndField(); 
		 fldCnt++, fldItr++) {

		valItr = fldItr->second.begin();

		switch (fldCnt) {

			case 0:
				if (fldItr->first.compare("Scooby")) {
					err = "Scooby: Incorrect field name found";
					return false;
				}
				if (fldItr->second.size() != 2) {
					err = "Scooby: Incorrect number of values found";
					return false;
				}
				if (valItr->GetStringValue() != scoobyStr[0]) {
					err = "Scooby: Field value incorrect (Hey, Scooby)";
					return false;
				}
				valItr++;
				if (valItr->GetStringValue() != scoobyStr[1]) {
					err = "Scooby: Field value incorrect (Hey, Scooby)";
					return false;
				}

				break;
			case 1:
				if (fldItr->first.compare("Shaggy")) {
					err = "Shaggy: Incorrect field name found";
					return false;
				}
				if (fldItr->second.size() != 1) {
					err = "Shaggy: Incorrect number of values found";
					return false;
				}
				if (valItr->GetIntValue() != 1) {
					err = "Shaggy: Field value incorrect (1)";
					return false;
				}
				break;
			case 2:
				if (fldItr->first.compare("Shaggy")) {
					err = "Shaggy: Incorrect field name found";
					return false;
				}
				if (fldItr->second.size() != 1) {
					err = "Shaggy: Incorrect number of values found";
					return false;
				}
				if (valItr->GetIntValue() != 2) {
					err = "Shaggy: Field value incorrect (2)";
					return false;
				}
				break;
			case 3:
				if (fldItr->first.compare("Velma")) {
					err = "Velma: Incorrect field name found";
					return false;
				}
				if (fldItr->second.size() != 1) {
					err = "Velma: Incorrect number of values found";
					return false;
				}
				if (fabs(valItr->GetFloatValue()-3.41326f) < 0.000001) {
					cout << valItr->GetFloatValue() << endl;
					err = "Velma: Field value incorrect (3.41326f)";
					return false;
				}
				break;
		 }
	}

	CSnoBlock scrappy("ScrappyBlock");
	scrappy.AddField("Nephew", "or Scooby's bastard?");
	scooby.AddChild(scrappy);
	if (scooby.GetChildCount() != 1) {
		err = "ScoobyBlock: Incorrect child count found";
		return false;
	}
	CSnoBlock::cTChildIterator childItr;

	for (childItr = scooby.BeginChild(); 
	 	 childItr != scooby.EndChild(); childItr++) {

		if (childItr->GetBlockName().compare("ScrappyBlock")) {
			err = "ScrappyBlock: Incorrect block name found";
			return false;
		}
		if (childItr->GetFieldCount() != 1) {
			err = "ScrappyBlock: Incorrect field count found";
			return false;
		}
	}

	parser.AddBlock(scooby);
	if (parser.GetBlockCount() != 3) {
		err = "parser: Incorrect block count found.";
		return false;
	}
	CSnoParser::TIterator pItr;
	int pCnt;
	for (pCnt = 0, pItr = parser.Begin(); pItr != parser.End(); 
		 pCnt++, pItr++) {

		string checkBlock;
		pItr->Store(checkBlock);
		if (checkBlock != blocks[pCnt]) {

			if (verbose) {

				if (blocks[pCnt].size() != checkBlock.size()) 
					cout << "Original size: " << blocks[pCnt].size() << " != "
						 << "check size: " << checkBlock.size() << endl;
				cout << "Original data: " << endl;
				cout << blocks[pCnt] << endl;
				cout << "Result of store: " << endl;
				cout << checkBlock << endl;
			}

			err = "Error storing subblocks.";
			return false;
		}
	}

	return true;
} // end of TestParser

int main(int argc, char **argv)
{
	bool verbose = false;

	if (argc > 1)
		verbose = true;

	string parseErr;
	if (!TestParser(parseErr, verbose)) {
		cout << "Error parsing file: " << parseErr << endl;
		return 0;
	}

	string headerErr;
	if (!TestHeader(headerErr, verbose)) {
		cout << "Error parsing header: " << headerErr << endl;
		return 0;
	}

	return 0;

} // end of main

