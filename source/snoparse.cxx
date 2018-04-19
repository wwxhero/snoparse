//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     January, 1999
//
// $Id: snoparse.cxx,v 1.22 2015/05/21 19:48:49 IOWA\dheitbri Exp $
//
// The implementation for the scenario parser class.
//
//////////////////////////////////////////////////////////////////////////////
#include "snoparse.h"
#include <iostream>
#include <fstream>
#include <sstream>
//#include "headerparseblock.h"
//#include "roadpos.h"

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//	Constructors, Destructor, and Assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSnoParser
// 	The copy constructor uses the assignment operator to assign the parameter
// 	to the current instance.
//
// Remarks:
//
// Arguments:
// 	cCopy - a CSnoParser instance to assign to the current instance
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSnoParser::CSnoParser(const CSnoParser& cCopy)
{
	*this = cCopy;
} // end of CSnoParser

//////////////////////////////////////////////////////////////////////////////
//
// Description: CSnoParser
// 	This constructor parses its string argument into CSnoBlocks and
// 	initializes the class.
//
// Remarks: The default constuctor creates an empty instance of the class.
// 	It is best used when creating a new file.
//
// Arguments:
// 	input - the string to parse
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
CSnoParser::CSnoParser(const string& input)
{
	m_state = eEMPTY;
	Parse(input);
} // end of CSnoParser

//////////////////////////////////////////////////////////////////////////////
//
// Description: operator=
// 	The assignment operator performs a deep copy of the contents of the
// 	parameter to the current instance.
//
// Remarks:
//
// Arguments:
// 	rhs - a CSnoParser instance that is on the righthand side of the equation
//
// Returns: A reference to the current instance so that the assignment
// 	statements can be nested.
//
//////////////////////////////////////////////////////////////////////////////
CSnoParser &CSnoParser::operator=(const CSnoParser &rhs)
{
	if ( &rhs != this ) {
		m_state = rhs.m_state;
		m_blocks = rhs.m_blocks;
	}
	return *this;
} // end of operator=


//////////////////////////////////////////////////////////////////////////////
//	Mutator functions
//////////////////////////////////////////////////////////////////////////////

bool
CSnoParser::ParseFile(const string& filename)
{
	m_filename = filename;
	string contents;
	char buffer[4096+1];
	int bytes;
	ifstream is;//( m_filename.c_str() );
    m_lastErr = "";
    try {
        is.open(filename);
    }
    catch (std::ios_base::failure& e) {
        ostringstream errStrm;
        std::cerr <<"Failed Opening File"<< e.what() << endl;
        errStrm <<"Failed Opening File"<< e.what() << endl;
        return false;
    }

    if (is.fail()){
        ostringstream errStrm;
		cerr << "CSnoParser::Error Opening File :" << strerror(errno)<< endl;
		errStrm << "CSnoParser::Error Opening File :" << strerror(errno)<< endl;
        m_lastErr += errStrm.str();
		return false;
    }
	do {
		is.read( buffer, 4096 );
		bytes = (int)is.gcount();
		buffer[bytes] = 0;
		if (bytes > 0) contents += buffer;
	} while (bytes > 0);

	return Parse( contents );
}


/////////////////////////////////////////////////////////////////////////////
//
// Description: Parse
// 	Breaks a string down into a sequence of blocks.
//
// Remarks: This function parses the string into a series of blocks and
//	stores them in the class.  Once this function has been called, the
//	various access functions and iterators can be used to traverse the
//	contents of the string at a high level.
//
// 	Note that this functionality can also be accessed through the
// 	appropriate << operator.
//
// Example:
// The following is an example of using the class:
//
//		CSnoParser  inf;
//		string      data;
//
//		OpenFileAndReadIt("Scenario.scf", data);
//
//		inf.parse(data);
//		CSnoParser::iterator  pI;
//		for (pI = inf.begin(); pI != inf.end(); pI++ ) {
//			// process CSnoBlock *pI
//		}
//
// Arguments:
// 	input - the string to parse
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
bool
CSnoParser::Parse(const string &input)
{
	CSnoBlock blk;
	blk.SetParser( this );
	int pos = 0;

	Clear();
	try {
		while (blk.Parse(input, pos)) {
			if (blk.GetBlockName() != "Header") {
 				AddBlock(blk);
			} else {
				m_blocks.insert( m_blocks.begin(), blk );
			}
		}
		vector <CSnoBlock> extStaticRefs;
		//if we have external static objects add them to the static object manager
		if (blk.GetStaticExtRefChildren(&extStaticRefs)){
			for (unsigned int i=0; i<m_blocks.size(); i++){
				if (m_blocks.at(i).GetBlockName() == "StaticObjManager"){
					for (unsigned int j = 0; j<extStaticRefs.size(); j++){
						m_blocks.at(i).AddChild(extStaticRefs.at(j));
					}
				}
			}
		}
		extStaticRefs.clear();
		if (blk.GetTrafficLightExtRefChildren(&extStaticRefs)){
			for (unsigned int i=0; i<m_blocks.size(); i++){
				if (m_blocks.at(i).GetBlockName() == "TrafficLightManager"){
					for (unsigned int j = 0; j<extStaticRefs.size(); j++){
						bool found = false;
						auto itr = m_blocks.at(i).BeginChild();
						for (; itr != m_blocks.at(i).EndChild();itr++){
							CSnoValue val1;
							CSnoValue val2;
							if (itr->GetField("IntrsctnName",val1) && extStaticRefs.at(j).GetField("IntrsctnName",val2)){
								if (val1.GetStringValue() == val2.GetStringValue()){
									found = true;
									break;
								}
							}
						}
						if (!found)
							m_blocks.at(i).AddChild(extStaticRefs.at(j));
					}
				}
			}
		}

	}
	catch (CSnoBlock::TTypeMismatch e) {
		ostringstream errStrm;
		cerr << "CSnoParser::Parse: Error when parsing field: "
			 << e.msg << endl;
		errStrm << "CSnoParser::Parse: Error when parsing field: "
				<< e.msg;

		m_lastErr = errStrm.str();
		m_state = eEMPTY;
		return false;
	}
	catch (CSnoBlock::TSyntaxError e) {
		ostringstream errStrm;
		cerr << "CSnoParser::Parse: Syntax error at position "
			 << e.pos << " in line: " << endl;
		cerr << "  " << e.line << endl;
		cerr << "  Error: " << e.err << endl;

		errStrm << "CSnoParser::Parse: Syntax error at position "
				<< e.pos << " in line: " << endl;
		errStrm << "  " << e.line << endl;
		errStrm << "  Error: " << e.err << endl;

		m_state = eEMPTY;
		m_lastErr = errStrm.str();
		return false;
	}
	catch (...) {
		cerr << "Unknown error found during CSnoBlock::Parse"
			 << endl;
		m_lastErr = "Unknown error found during CSnoBlock::Parse";
		m_state = eEMPTY;
		return false;
	}

	m_state = eLOADED;
	return true;

} // end of Parse

//////////////////////////////////////////////////////////////////////////////
//
// Description: Clear
// 	Removes all blocks from the current instance.
//
// Remarks:
//
// Arguments:
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CSnoParser::Clear(void)
{
	// Clear out m_blocks
	m_blocks.clear();
} // end of Clear

//////////////////////////////////////////////////////////////////////////////
//
// Description: AddBlock
// 	Adds a block to the current instance.
//
// Remarks:
// This function adds a block to the list of blocks in the class instance.
// If the class has just been initialized, the first block should be
// a header block, otherwise it should be an HCSM block.  The function
// can also be used to add a block to an instance that has been
// initialized by parsing an existing description.  In the latter case,
// the new block will be added to the end of the list.
//
// Arguments:
// 	blk - the CSnoBlock to add
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CSnoParser::AddBlock(const CSnoBlock &blk)
{
	m_blocks.push_back(blk);
} // end of AddBlock

//////////////////////////////////////////////////////////////////////////////
//	Accessor functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: Store
// 	Store each block in the current instance to a string.
//
// Remarks: This function stores the contents of the class into a string
// 	where it can later be retrieved by the parse function.
//
//	Note that this functionality can also be accessed through the
//	appropriate >> operator.
//
// Arguments:
// 	out - the string where data is stored
//
// Returns: void
//
//////////////////////////////////////////////////////////////////////////////
void
CSnoParser::Store(string& out) const
{
	if ( m_state != eLOADED) {
		TError e("CSnoParser::Store: parser not loaded!");
		throw e;
	}

	out.erase();
	out.reserve(512);

	TIterator itr;
	for (itr = m_blocks.begin(); itr != m_blocks.end(); itr++) {
		string s;
		s.reserve(256);

		itr->Store(s);
		out += s;
	}
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetBlockCount
// 	Return the number of blocks in the current instance.
//
// Remarks: Once a scenario file has been parsed, this function can be used
// 	to determine the number of blocks in the file.  The header counts as one
// 	of the blocks.
//
// 	Do not call this class without first parsing a scenario file as it will
// 	throw an exception of type TError.
//
// Arguments:
//
// Returns: The number of blocks in the file
//
//////////////////////////////////////////////////////////////////////////////
int
CSnoParser::GetBlockCount(void) const
{
	if ( m_state != eLOADED ) {
		TError e("CSnoParser::GetBlockCount: parser not loaded.");
		throw e;
	}
	return (int) m_blocks.size();
} // end of GetBlockCount


//////////////////////////////////////////////////////////////////////////////
//	Iterator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//
// Description: Begin
// 	Returns an iterator pointing to the beginning of the block list
//
// Remarks:
//
// Arguments:
//
// Returns: an iterator pointing to the beginning of the block list
//
//////////////////////////////////////////////////////////////////////////////
CSnoParser::TIterator
CSnoParser::Begin(void) const
{
	return m_blocks.begin();
} // end of Begin

//////////////////////////////////////////////////////////////////////////////
//
// Description: End
// 	Returns an iterator pointing to the end of the block list
//
// Remarks:
//
// Arguments:
//
// Returns: an iterator pointing to the end of the block list
//
//////////////////////////////////////////////////////////////////////////////
CSnoParser::TIterator
CSnoParser::End(void) const
{
	return m_blocks.end();
} // end of End


//////////////////////////////////////////////////////////////////////////////
//
// Description: operator<<
// 	Store each block of the current instance to an output stream.
//
// Remarks: The functionality of this operator is equivalent to using the
// 	store function to write the contents of the class to a string and then
// 	sending the string to the output stream.
//
// Arguments:
// 	stream - where to write the contents of the class instance
// 	item - the CSnoParser instance to be written
//
// Returns: The resulting ostream.
//
//////////////////////////////////////////////////////////////////////////////
ostream &
operator<<(ostream& stream, const CSnoParser& item)
{
	string  output;
	item.Store(output);
	stream << output;
	return stream;
} // end of operator<<
