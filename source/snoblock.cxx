/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     September, 1998
//
// $Id: snoblock.cxx,v 1.49 2018/03/22 19:31:04 IOWA\dheitbri Exp $
//
// The implementation file for the scenario block class (CSnoBlock), a helper
// class for the scenario parser class.
//
//////////////////////////////////////////////////////////////////////////////

#include "hcsmspec.h"
#include <fstream>
#include <sstream>

using namespace std;

//////////////////////////////////////////////////////////////////////////////
//	Ostream operators
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//	Constructors, destructor, and assignment operator
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///
///\brief  CSnoBlock
/// 	The copy constructor copies the contents of the parameter to the current
/// 	instance using the assignment operator.
///
///\remarks
///
/// Arguments:
/// 	cCopy - CSnoBlock instance to copy
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock::CSnoBlock(const CSnoBlock &cCopy)
{
	*this = cCopy;
} // end of CSnoBlock

//////////////////////////////////////////////////////////////////////////////
///
///\brief  operator=
/// 	Assignment operator copies the contents of the parameter to the current
/// 	instance.
///
///\remarks
///
/// Arguments:
/// 	rhs - a CSnoBlock instance on the righthand of the assignment statement
///
///\returns  A reference to the current instance, to allow nested assignments.
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock &CSnoBlock::operator=(const CSnoBlock &rhs)
{
	if ( &rhs != this ) {
		m_name		= rhs.m_name;
		m_fields	= rhs.m_fields;
		m_children	= rhs.m_children;
	}
	return *this;
} // end of operator=


//////////////////////////////////////////////////////////////////////////////
//	Mutator functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///
///\brief  Parse
/// 	Parse a block from a string parameter.
///
///\remarks  This function parses a string that contains the description
/// 	of a block and loads this block into the class.
///
/// 	This function calls the other Parse function with its 'pos' equal to 0,
/// 	indicating that the parsing should begin at the start of the string.
///
///	If there is a field parsed that contains values of different types, then
///	an exception of type CSnoBlock::TTypeMismatch will be thrown.
///
/// Arguments:
///\param[in] 	input - the string to parse
///
///\returns  Returns a true if parsing was successful, false if the end of the
///	input string has been reached.
///
//////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::Parse(const string &input) {
	int pos = 0;
	return Parse(input, pos);
} // end of Parse
//////////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets the static object external refrences
///\remark
///  This function takes in a pointer to a vector<CSnoBlock>, and adds any static
///  external refrences that it may have parsed. This will latter be added to the
///  static object manager.
///
///
//////////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::GetStaticExtRefChildren(vector<CSnoBlock> *staticExtRefs){
	if (m_staticExtRefs.size() == 0)
		return false; //we have no static external refs
	for (unsigned int i=0; i<m_staticExtRefs.size(); i++){
		staticExtRefs->push_back(m_staticExtRefs.at(i));
	}
	return true; //some external static refs where added
}
//////////////////////////////////////////////////////////////////////////////////
///\brief
///		Gets the traffic light external refrences
///\remark
///	 This function takes in a pointer to a vector<CSnoBlock>, and adds any intersections
///  blocks to the intersection manager that are externaly refrenced the top level parser
///  will be responsible for adding these to the traffic light manager.
///
///
//////////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::GetTrafficLightExtRefChildren(vector <CSnoBlock> *lightExtRefs){
	if (m_TrafLightExtRefs.size() == 0)
		return false; //we have no static external refs
	for (unsigned int i=0; i<m_TrafLightExtRefs.size(); i++){
		lightExtRefs->push_back(m_TrafLightExtRefs.at(i));
	}
	return true; //some external static refs where added
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief  Parse
/// 	Parse a block from a string parameter.
///
///\remarks  This function parses a string that contains the description
/// 	of a block and loads this block into the class.
///
///	If there is a field parsed that contains values of different types, then
///	an exception of type CSnoBlock::TTypeMismatch will be thrown.
///
///	If there is an error in the string to parse, then an exception of type
///	CSnoBlock::T
/// Arguments:
///\param[in] 	input - the string to parse
///\param[in] 	pos - the position within input to begin parsing
///
///\returns Returns a true if parsing was successful, false if the end of the
///	input string has been reached.
///
//////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::Parse(const string &input, int &pos)
{
	string	line;
	string	token;
	int		tok;
	int		endOfPriorLine;
	vector <CSnoBlock> staticExtRefs;
	if (pos >= (int)input.size()) return false;

	if ( !GetLine(input, pos, line) )
		return false;

	// read title of hcsm or Header block
	tok = 0;
	if ( !Tokenize(line, tok, token) ) {
		TSyntaxError e(line, tok,
			"Unable to read block tag");
        e.err += "\r\n near \r\n";
        e.err += line;
		throw e;
	}

	// If header, set name to "Header"
	if (token.compare("Header") == 0
		|| token.compare("DistriSim") == 0) {
		m_name = token;
	}
	// If HCSM, look for HCSM name
	else if (token.compare("HCSM") == 0) {

		if (Tokenize(line, tok, token))
			m_name = token;

		// If unable to parse name of HCSM,
		//	throw a TSyntaxError
		else {
			TSyntaxError e(line, tok,
				"No HCSM name found");

            e.err += "\r\n near \r\n";
            e.err += line;

			throw e;
		}
	}
	// If not HCSM, or Header, throw a TSyntaxError
	else {
		TSyntaxError e(line, tok,
			"'HCSM' or 'Header' tag not found");
		throw e;
	}

	// remove existing fields and children
	ClearAll();

	// read each line and add fields to the class.
	endOfPriorLine = pos;
	while ( GetLine(input, pos, line) ) {
		int tokPos = 0;
		bool first = true;		// set when we get the first token
		TField fld;

		while ( Tokenize(line, tokPos, token) ) {
			if ( first ) {
				// If we found the end token, we are done for this block
				if ( token.compare("&&&&End&&&&") == 0 ) {
					if (m_name == "Header") {
						vector<CSnoValue> extRefs;
						CSnoBlock::cTValueIterator pVal;
						if (GetField( "ExtRef", extRefs )) {
							// Assemble values
							pVal = extRefs.begin();
							while (pVal != extRefs.end() ) {
								string filename;
								if (m_pParser && m_pParser->GetFilename().size() > 0 ) {
									filename = m_pParser->GetFilename();
									filename.erase(filename.find_last_of('\\')+1);
								}
								if (filename.size() == 0){
									filename = getenv("NADSSDC_SCN");
								}
								filename += pVal->GetStringValue();
								pVal++;
								string groupName = pVal->GetStringValue();
								pVal++;

								string contents;
								char buffer[4097];
								int bytes;
								ifstream is( filename.c_str() );
								if (!is) {
									string str;
									if (m_pParser) {
										str = m_pParser->GetFilename();
										str.erase(str.find_last_of('\\')+1);
									} else {
										str = "No filename";
									}
									str += " - Unable to open external reference:\r\n";
									str +=filename;
									TSyntaxError e(line, tok, str.c_str());
									throw e;
								}
								do {
									is.read( buffer, 4096 );
									bytes = (int)is.gcount();
									buffer[bytes] = 0;
									if (bytes > 0) contents += buffer;
								} while (bytes > 0);

								CSnoBlock blk;
								int pos = 0;

								try {
									while (blk.Parse(contents, pos)) {
										if (blk.GetGroupName() == groupName) {
											if (m_pParser) {
												blk.SetIsExtRef( true );
												m_pParser->AddBlock(blk);
											}
										//Static Objects are always children of the StaticObjManager
										}else if (blk.GetGroupName() == "" && blk.GetBlockName() == "StaticObjManager"
											&& m_pParser){
											for(CSnoBlock::TChildIterator child = blk.BeginChild(); child != blk.EndChild(); child++){
												child->SetIsExtRef(true);
												if (child->GetGroupName() == groupName)
													m_staticExtRefs.push_back(*child);

											}
										}else if (blk.GetGroupName() == "" && blk.GetBlockName() == "TrafficLightManager"
											&& m_pParser){
											for(CSnoBlock::TChildIterator child = blk.BeginChild(); child != blk.EndChild(); child++){
												child->SetIsExtRef(true);
												if (child->GetGroupName() == groupName)
													m_TrafLightExtRefs.push_back(*child);

											}
										}
									}
									blk.ClearAll();

								}
								catch (CSnoBlock::TTypeMismatch e) {
									std::ostringstream strout;
									strout.str("");
									cerr << "CSnoParser::Parse: Error when parsing field: "
										 << e.msg << endl;
									strout << "CSnoParser::Parse: Error when parsing field: "
										   << e.msg << endl;
									m_lastErr = strout.str();

									return false;
								}
								catch (CSnoBlock::TSyntaxError e) {
									std::ostringstream strout;
									strout.str("");
									cerr << "CSnoParser::Parse: Syntax error at position "
										 << e.pos << " Near Line: " << endl;
									cerr << "  " << e.line << endl;
									cerr << "  Error: " << e.err << endl;

									strout << "CSnoParser::Parse: Syntax error at position "
										   << e.pos << " Near Line: " << endl;
									strout << "  " << e.line << endl;
									strout << "  Error: " << e.err << endl;
									m_lastErr = strout.str();

									return false;
								}
								catch (...) {
									cerr << "Unknown error found during CSnoBlock::Parse"
										 << endl;
									m_lastErr = "Unknown error found during CSnoBlock::Parse\n";
									return false;
								}
							}
						}

					}
					//for (int i =0; i<staticExtRefs.size(); i++)
					//	m_pParser->AddStaticBlock(staticExtRefs.at(i));
					return true;
				}

				// if the string says HCSM, it's a nested block
				if ( token.compare("HCSM") == 0
					|| (token.compare("DistriSim") == 0 && m_name == "Header") ) {
					CSnoBlock  child;

					if (!child.Parse(input, endOfPriorLine))
						return false;

					AddChild(child);
					pos = endOfPriorLine;
					break;
				}
				else fld.first = token;
				first = false;
			}
			else {
				// we need to use the properly typed AddValue function
				CSnoValue val;
				if ( token[0] == '\"' )	{	// string
					val.SetValue(token.substr(1, token.size()-2));
				}
				else if ( token.find(".") != string::npos ||
						  token.find("E") != string::npos ||
						  token.find("e") != string::npos )	{	// double
					val.SetValue(atof(token.c_str()));
				}
				else { // int
					val.SetValue(atoi(token.c_str()));
				}

				// Check that type matches other types in field
				if (!fld.second.empty()) {

					CSnoValue::EType newType = val.GetType(),
						corrType = fld.second.begin()->GetType();
					if (corrType != newType) {

						TTypeMismatch e(fld.first,
										GetTypeName(newType),
										GetTypeName(corrType));
                        e.msg += "\r\n near \r\n";
                        e.msg += line;
                        throw e;
					}
				}
				// Add value to field list
				fld.second.push_back(val);
			}
		}

		// If the field has a name, add it to the list
		if ( !fld.first.empty() )
			AddField(fld);
		endOfPriorLine = pos;
	}


	// If control makes it here, then we've reached
	//	the end of the string.  So, return false.
	return false;

} // end of Parse

//////////////////////////////////////////////////////////////////////////////
///
///\brief  Store
/// 	Write the block to a string.
///
///\remarks  This function creates a printable representation of the block
/// 	and stores it in space.  The printable representation is such
/// 	that it can be parsed into the class using the parse function.
///
/// Arguments:
///\param[in] 	space - the string to store the output
///\param[in]	level - number of spaces to indent the current block.
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void CSnoBlock::Store(string &space, int level) const
{
	cTFieldIterator	f;
	string			line;
	string			indent = "";

	for (int i = 0; i < level; i++)
		indent += " ";

	if ( m_name.compare("Header") == 0 ) {
		space = indent + "Header\n";
	}
	else {
		space = indent + "HCSM ";
		space += m_name;
		space += "\n";
	}

	for (f = m_fields.begin(); f != m_fields.end(); f++) {
		line = "  ";
		line += f->first;
		line += " ";

		cTValueIterator v;
		for (v = f->second.begin(); v != f->second.end(); v++) {
			line += v->GetStringRep();
			line += " ";
		}
		line += "\n";

		space += indent;
		space += line;
	}

	// Recursivly write out children
	cTChildIterator childIter;
	for (childIter = m_children.begin();
		 childIter != m_children.end();
		 childIter++) {
		string s;
		if (!childIter->IsExtRef()){
			childIter->Store(s, level + 4);
			space += s;
		}
	}

	space += indent;
	space += "&&&&End&&&&\n";
} // end of Store

//////////////////////////////////////////////////////////////////////////////
///
///\brief  ClearAll
/// 	Clears the fields and children of the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::ClearAll(void)
{
	ClearChildren();
	ClearFields();
} // end of ClearAll

//////////////////////////////////////////////////////////////////////////////
///
///\brief  ClearChildren
/// 	Removes all the child blocks from the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::ClearChildren(void)
{
	m_children.clear();
} // end of ClearChildren

//////////////////////////////////////////////////////////////////////////////
///
///\brief  ClearFields
/// 	Removes all the fields from the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::ClearFields(void)
{
	m_fields.clear();
} // end of ClearFields

//////////////////////////////////////////////////////////////////////////////
///
///\brief  ClearFields
///	Removes the fields with the given name from the current block.
///
///\remarks
///
/// Arguments:
///	name - name of the field to delete
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::ClearFields(const string& name)
{
	TFieldIterator first = FindFirst( name );

	if ( first != m_fields.end() ) {
		TFieldIterator last = FindLast( name );
		if (last != m_fields.end())
			last++;
		m_fields.erase(first, last);
	}
} // end of ClearFields

//////////////////////////////////////////////////////////////////////////////
///
///\brief  SetBlockName
/// 	Sets the name of the current block.
///
///\remarks
///
/// Arguments:
/// 	name - name to which to set the current block name
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::SetBlockName(const string& name)
{
	 m_name = name;
} // end of SetBlockName


void
CSnoBlock::SetPriority(const int val){
	// Delete any "ShortComment" fields
	ClearFields("Priority");

	// Add new "ShortComment" field.
	AddField("Priority", val);
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddChild
///	Adds a child block to the current block.
///
///\remarks  This function stores the parameter in the list of children.
///
/// Arguments:
///	child - the block that will be appended to the current list of children
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////
void
CSnoBlock::AddChild(const CSnoBlock &child)
{
	m_children.push_back(child);
} // end of AddChild
void CSnoBlock::AddChildFront(const CSnoBlock &child){
    m_children.insert(m_children.begin(),child);
}
/////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add the field to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// Arguments:
/// 	fld - field to append to the block
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const TField &fld)
{
//	cout << "****************Adding field " << fld.first << endl;
	// if no fields, push_back
//	if (m_fields.size() == 0) {
		m_fields.push_back( fld );
		return;
//	}
	// else, find where to insert the field
//	TFieldMap::iterator i = m_fields.end();
//	while ((i != m_fields.begin() ) && ( (i-1)->first > fld.first ))
//		i--;
//	m_fields.insert(i, fld);

//	for (i = m_fields.begin(); i != m_fields.end(); i++) {
//		CSnoValue val = i->second[0];
//		cout << i->first << " : " << val.GetStringRep() << endl;
//	}

} // end of AddField

//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add a field with the given name and int value to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// Arguments:
/// 	name - name to assign to the field
/// 	val - value to give the field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, int val)
{
	TField fld;
	CSnoValue sVal;
	fld.first = name;
	sVal.SetValue(val);
	fld.second.push_back(sVal);
	AddField( fld );
} // end of AddField

//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add a field with the given name and double value to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// The different variants of this function are used to discriminate the
/// type of the field.  For example, if the function is called as
/// addField("Velocity",3.2) then the field Velocity will be marked
/// as been of type double.  A field added as a string will be written
/// within double quotes.
///
/// Arguments:
/// 	name - name to assign to the field
/// 	val - value to give the field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, double val)
{
	TField fld;
	CSnoValue sVal;
	fld.first = name;
	sVal.SetValue(val);
	fld.second.push_back(sVal);
	AddField( fld );
} // end of AddField

//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add a field with the given name and string value to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// Arguments:
/// 	name - name to assign to the field
/// 	val - value to give the field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, string val)
{
	TField fld;
	CSnoValue sVal;
	fld.first = name;
	sVal.SetValue(val);
	fld.second.push_back(sVal);
	AddField( fld );
} // end of AddField
//////////////////////////////////////////////////////////////////////////////
///
///\brief
/// 	Add a field with the given name and char values to the block.
///
///\remark
/// This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// entries, the function simply appends the field and performs no other
/// checks. The elements passed into this function will be treated as ints
/// 0-255 in value
///
///
///\param[in] 	name - name to assign to the field
///\param[in] 	vals - vector of values to give the field
///
///\returns void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const std::string& name, const std::vector<char>& vals){
	TField fld;
	CSnoValue sVal;
	vector<char>::const_iterator itr;
	fld.first = name;

	// Add all the CSnoValues to the vector
	for (itr = vals.begin(); itr != vals.end(); itr++) {
		sVal.SetValue((int)*itr);
		fld.second.push_back(sVal);
	}
	AddField( fld );
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief
/// 	Add a field with the given name and int values to the block.
///
///\remarks This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
///
///\param[in] 	name - name to assign to the field
///\param[in] 	vals - vector of values to give the field
///
///\returns void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, const vector<int>& vals)
{
	TField fld;
	CSnoValue sVal;
	vector<int>::const_iterator itr;
	fld.first = name;

	// Add all the CSnoValues to the vector
	for (itr = vals.begin(); itr != vals.end(); itr++) {
		sVal.SetValue(*itr);
		fld.second.push_back(sVal);
	}
	AddField( fld );
} // end of AddField

//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add a field with the given name and double values to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// Arguments:
/// 	name - name to assign to the field
/// 	vals - vector of values to give the field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, const vector<double>& vals)
{
	TField fld;
	CSnoValue sVal;
	vector<double>::const_iterator itr;
	fld.first = name;

	// Add all the CSnoValues to the vector
	for (itr = vals.begin(); itr != vals.end(); itr++) {
		sVal.SetValue(*itr);
		fld.second.push_back(sVal);
	}
	AddField( fld );
} // end of AddField
void CSnoBlock::AddField(const std::string& name, const std::vector<float>& vals){
	TField fld;
	CSnoValue sVal;
	vector<float>::const_iterator itr;
	fld.first = name;

	// Add all the CSnoValues to the vector
	for (itr = vals.begin(); itr != vals.end(); itr++) {
		sVal.SetValue(*itr);
		fld.second.push_back(sVal);
	}
	AddField( fld );
}
//////////////////////////////////////////////////////////////////////////////
///
///\brief  AddField
/// 	Add a field with the given name and string values to the block.
///
///\remarks  This function adds the specified field to the map of fields
///	that comprise the block.  Since it is permissible to have duplicate
/// 	entries, the function simply appends the field and performs no other
/// 	checks.
///
/// Arguments:
/// 	name - name to assign to the field
/// 	vals - vector of values to give the field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AddField(const string& name, const vector<string>& vals)
{
	TField fld;
	CSnoValue sVal;
	vector<string>::const_iterator itr;
	fld.first = name;

	// Add all the CSnoValues to the vector
	for (itr = vals.begin(); itr != vals.end(); itr++) {
		sVal.SetValue(*itr);
		fld.second.push_back(sVal);
	}
	AddField( fld );
} // end of AddField


//////////////////////////////////////////////////////////////////////////////
//	Accessor functions
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///
///\brief  IsHeader
/// 	Returns true if the current block is the header, false otherwise.
///
///\remarks  The name of the block is compared to the string "Header" to
/// 	determine if it is the header.
///
/// Arguments:
///
///\returns  true if the current block is the header, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::IsHeader(void) const
{
	 return m_name.compare("Header") == 0;
} // end of IsHeader

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetBlockName
/// 	Returns the name of the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  a const reference to the name of the current block.
///
///////////////////////////////////////////////////////////////////////////////
const string&
CSnoBlock::GetBlockName(void) const
{
	 return m_name;
} // end of GetBlockName

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetChildCount
/// 	Returns the number of children in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an integer count of the children in the current block.
///
///////////////////////////////////////////////////////////////////////////////
int
CSnoBlock::GetChildCount(void) const
{
	 return (int) m_children.size();
} // end of GetChildCount

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetFieldCount
/// 	Returns the number of fields in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an integer count of the fields in the current block.
///
///////////////////////////////////////////////////////////////////////////////
int
CSnoBlock::GetFieldCount(void) const
{
	 return (int) m_fields.size();
} // end of GetFieldCount

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetFieldCount
/// 	Returns the number of fields with the given name in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an integer count of the fields with the given name in the
/// 	current block.
///
///////////////////////////////////////////////////////////////////////////////
int
CSnoBlock::GetFieldCount(const string& name) const
{
	cTFieldIterator first = FindFirst( name );
	cTFieldIterator last = FindLast( name );
	if (first == m_fields.end()) return 0;
	return (int) ( last - first + 1 );
} // end of GetFieldCount

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetField
/// 	Returns the first field value associated with the parameter name.
///
///\remarks  Because a reference to the field value is returned, it may be
/// 	modified and the changes will be reflected in the field.
///
/// Arguments:
/// 	name - name of field to return.
/// 	val - (Output) Reference to the first CSnoValue instance associated
/// 		with the given name.
///
///\returns  True if the field was found, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::GetField(const string &name, CSnoValue &val) const
{
	cTFieldIterator itr = FindFirst(name);
	if (itr != m_fields.end() && itr->second.size() > 0) {
		val = *(itr->second.begin());
		return true;
	}
	else {
		val.Clear();
		return false;
	}
} // end of GetField

///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetField
/// 	Returns all the field value associated with the parameter name.
///
///\remarks  Because a copy of the field values are returned, any changes made
/// 	to them will not be reflected in the field.
///
/// Arguments:
/// 	name - name of field to return.
/// 	values - (Output) Vector CSnoValue instances associated with the given
/// 		name.
///
///\returns  True if the field was found, false otherwise.
///
///////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::GetField(const string &name, vector<CSnoValue>& values) const
{
	cTFieldIterator lItr = FindFirst(name),
					uItr = FindLast(name);
	values.clear();
	if (lItr != m_fields.end()) {
		for (; lItr <= uItr; lItr++)
			values.insert(values.end(),
						  lItr->second.begin(),
						  lItr->second.end());
		return (values.size() != 0);
	}
	return false;

} // end of GetField


//////////////////////////////////////////////////////////////////////////////
//	Iterator functions
//////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
///
///\brief  BeginField
/// 	Returns a const iterator pointing to the beginning of the list of fields
/// 	in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the beginning of the list of fields.
///
///////////////////////////////////////////////////////////////////////////////
CSnoBlock::cTFieldIterator
CSnoBlock::BeginField(void) const
{
	return m_fields.begin();
} // end of BeginField

///////////////////////////////////////////////////////////////////////////////
///
///\brief  EndField
/// 	Returns a const iterator pointing to the end of the list of fields in
/// 	the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the end of the list of fields.
///
///////////////////////////////////////////////////////////////////////////////
CSnoBlock::cTFieldIterator
CSnoBlock::EndField(void) const
{
	return m_fields.end();
} // end of endField

//////////////////////////////////////////////////////////////////////////////
///
///\brief  BeginChild
/// 	Returns a const iterator pointing to the beginning of the list of
/// 	children in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the beginning of the list of children.
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock::cTChildIterator
CSnoBlock::BeginChild(void) const
{
	return m_children.begin();
} // end of BeginChild

//////////////////////////////////////////////////////////////////////////////
///
///\brief  EndChild
/// 	Returns a const iterator pointing to the end of the list of children in
/// 	the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the end of the list of children.
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock::cTChildIterator
CSnoBlock::EndChild(void) const
{
	return m_children.end();
} // end of EndChild

//////////////////////////////////////////////////////////////////////////////
///
///\brief  BeginChild
/// 	Returns a non-const iterator pointing to the beginning of the list of
/// 	children in the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the beginning of the list of children.
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock::TChildIterator
CSnoBlock::BeginChild(void)
{
	return m_children.begin();
} // end of BeginChild

//////////////////////////////////////////////////////////////////////////////
///
///\brief  EndChild
/// 	Returns a non-const iterator pointing to the end of the list of children in
/// 	the current block.
///
///\remarks
///
/// Arguments:
///
///\returns  an iterator at the end of the list of children.
///
//////////////////////////////////////////////////////////////////////////////
CSnoBlock::TChildIterator
CSnoBlock::EndChild(void)
{
	return m_children.end();
} // end of EndChild


//////////////////////////////////////////////////////////////////////////////
//	Private functions
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
///
///\brief  IsEmptyLine {secret}
/// 	Indicates whether the parameter contains an empty string or a line with
/// 	only whitespace.
///
///\remarks
///
/// Arguments:
/// 	str - string to test for emptiness
///
///\returns  True if the parameter is empty, false otherwise.
///
//////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::IsEmptyLine(string &str)
{
	if ( str.size() == 0 || str.find_first_not_of("\n\t ") == string::npos )
		return true;
	else
		return false;
} // end of IsEmptyLine

//////////////////////////////////////////////////////////////////////////////
///
///\brief  GetLine {secret}
/// 	Extracts a line from str, starting at position pos and putting in line.
/// 	If end of string is encountered, return false otherwise return true.
///
///\remarks  Skips empty lines.
///
/// Arguments:
/// 	cStr - string to parse
/// 	pos - position to begin at in str
/// 	line - result of the parsing
///
///\returns  True if the parameter contains another non-empty line, false
/// 	otherwise.
///
//////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::GetLine( const string& cStr, int& pos, string& line )
{
	int index;
	do
	{
		index = (int) cStr.find_first_of( '\n', pos );
		if( index == string::npos )  return false;
		line = cStr.substr( pos, index - pos + 1 );
		pos = index + 1;
	} while( IsEmptyLine( line ) );

	return true;
} // end of GetLine

string
CSnoBlock::GetName( ) const
{
	string blockName = GetBlockName();
	if (blockName == "Ado") {
		CAdoParseBlock block( *this );
		return block.GetName();
	} else if (blockName == "Ddo") {
		CDdoParseBlock block( *this );
		return block.GetName();
	} else if (blockName == "TimeTrigger" || blockName == "GmtrcPstnTrigger" || blockName == "TrffcLghtTrigger" || blockName == "RoadPadTrigger" || blockName == "TimeToArrvlTrigger") {
		CTriggerParseBlock block( *this );
		return block.GetName();
	} else if (blockName == "EnviroInfo") {
		CEnviroInfoParseBlock block( *this );
		return block.GetName();
	} else if (blockName == "StaticObject") {
		CStaticObjParseBlock block( *this );
		return block.GetName();
	}
	return GetBlockName();
}

//////////////////////////////////////////////////////////////////////////////
///
///\brief  Tokenize {secret}
///	Accepts a string and a starting position and returns a token that
///	consists of the first group of non white space characters or a quoted
///	string
///
///\remarks  Skips empty lines.
///
/// Arguments:
/// 	cLine - string to parse
/// 	curPos - position to begin at in str
/// 	token - result of the parsing
///
///\returns  True if the parameter contains another token, false otherwise.
///
//////////////////////////////////////////////////////////////////////////////
bool
CSnoBlock::Tokenize( const string& cLine, int& curPos, string& token )
{
	int pos1 = (int) cLine.find_first_not_of( " \t\n", curPos );
	if( pos1 == string::npos )  return false;

	if( cLine[pos1] == '\"' )
	{
		int pos2 = (int) cLine.find_first_of('\"', pos1+1);
		if( pos2 == string::npos )  return false;
		curPos = pos2 + 1;
		token = cLine.substr( pos1, pos2 - pos1 + 1);
		return true;
	}
	else
	{
		int pos2 = (int) cLine.find_first_of(" \t\n", pos1);
		if( pos2 == string::npos )  return false;
		curPos = pos2;
		token = cLine.substr( pos1, pos2 - pos1 );
		return true;
	}
} // end of Tokenize

//////////////////////////////////////////////////////////////////////////////
///
///\brief  GetTypeName {secret}
/// 	Return a string containing the name of the given type.
///
///\remarks
///
/// Arguments:
///	type - enumerated type to translate
///
///\returns  A string representation of that type
///
//////////////////////////////////////////////////////////////////////////////
string
CSnoBlock::GetTypeName(CSnoValue::EType type)
{
	switch (type) {
		case CSnoValue::eSTRING:
			return "string";
		case CSnoValue::eINT:
			return "int";
		case CSnoValue::eFLOAT:
			return "double";
		default:
			return "none";
	}
} // end of GetTypeName

CSnoBlock::cTFieldIterator
CSnoBlock::FindFirst( const string& str ) const
{
	if (m_fields.size() == 0) return m_fields.end();
	cTFieldIterator i = m_fields.begin();
	while ((i != m_fields.end()) && (i->first != str))
		i++;

	return i;
}

CSnoBlock::TFieldIterator
CSnoBlock::FindFirst( const string& str )
{
	if (m_fields.size() == 0) return m_fields.end();
	TFieldIterator i = m_fields.begin();
	while ((i != m_fields.end()) && (i->first != str))
		i++;

	return i;
}


CSnoBlock::cTFieldIterator
CSnoBlock::FindLast( const string& str ) const
{
	if (m_fields.size() == 0) return m_fields.end();
	cTFieldIterator i = m_fields.end() - 1;
	while ((i > m_fields.begin()) && (i->first != str))
		i--;

	if (i == m_fields.begin() && i->first != str) return m_fields.end();
	return i;
}

CSnoBlock::TFieldIterator
CSnoBlock::FindLast( const string& str )
{
	if (m_fields.size() == 0) return m_fields.end();
	TFieldIterator i = m_fields.end() - 1;
	while ((i >= m_fields.begin()) && (i->first != str))
		i--;

	if (i < m_fields.begin()) return m_fields.end();
	return i;
}



string CSnoBlock::GetGroupName() const
{
	CSnoValue val;
	if (GetField("GroupName", val))
		return val.GetStringValue();
	else
		 return "";
}


void CSnoBlock::SetGroupName(const string& str)
{
	// Delete any "GroupName" fields
	ClearFields("GroupName");

	// Add new "GroupName" field.
	AddField("GroupName", str);

}


string CSnoBlock::GetExtInfo() const
{
	CSnoValue val;
	if (GetField("ExtInfo", val))
		return val.GetStringValue();
	else
		 return "";
}

void CSnoBlock::SetExtInfo(const string& str)
{
	// Delete any "ExtInfo" fields
	ClearFields("ExtInfo");

	// Add new "ExtInfo" field.
	AddField("ExtInfo", str);

}



bool CSnoBlock::IsExtRef() const
{
	CSnoValue val;
	if (GetField("ExtRef", val))
		return val.GetIntValue() != 0;
	else
		 return false;
}


void CSnoBlock::SetIsExtRef(bool extRef)
{
	// Delete any "ExtRef" fields
	ClearFields( "ExtRef" );

	// Add new "ExtRef" field.
	AddField( "ExtRef", extRef ? 1 : 0 );

}

//////////////////////////////////////////////////////////////////////////////
///
///\brief  SetShortComment
/// 	Sets the value of the field named "ShortComment" to the value of the
/// 	parameter.
///
///\remarks  The "ShortComment" field is used to make comments about a
/// 	scenario element.  This should contain no line breaks, and if it does,
/// 	SetLongComment should be used instead.
///
/// Arguments:
///	comment - A string containing the short comment.
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::SetShortComment(const string& comment)
{
	// Delete any "ShortComment" fields
	ClearFields("ShortComment");

	// Add new "ShortComment" field.
	AddField("ShortComment", comment);

} // end of SetShortComment

//////////////////////////////////////////////////////////////////////////////
///
///\brief  SetLongComment
/// 	Sets the value of the field named "LongComment" to the value of the
/// 	parameter.
///
///\remarks  The "LongComment" field is used to make comments about a
/// 	scenario element.  If the string contains line breaks, it is parsed into
/// 	several strings and added as several field values.
///
/// Arguments:
///	comment - A string containing the long comment.
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::SetLongComment(const string& comment)
{
	// Parse parameter into strings divided by line breaks.
	char *pComment = new char[strlen(comment.c_str())+1];
	char *pTokDel = "\n\r";
	char *pTok;
	char *pCurrPos;
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
///
///\brief  SetAnchorName
/// 	Sets the value of the field named "AnchorName" to the value of the
/// 	parameter.
///
///\remarks  This names the Anchor the object is linked to, this is only used by
///			ISAT
/// Arguments:
///	name - A string containing the short comment.
///
///\returns  void
///
//////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::SetAnchorName(const string& name)
{
	// Delete any "ShortComment" fields
	ClearFields("AnchorName");

	// Add new "ShortComment" field.
	AddField("AnchorName", name);

} // end of SetShortComment
///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetPath
///	DESCRIPTION
///
///\remarks
///
/// Arguments:
///
///\returns  A vector of string values for the Path field.
///
///////////////////////////////////////////////////////////////////////////////
vector<string>
CSnoBlock::GetAnchor(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	vector<string> path;
	if (GetField("Anchor", vals)) {
		// Assemble values
		for (pVal = vals.begin(); pVal != vals.end(); pVal++) {
			path.push_back(pVal->GetStringValue());
		}
	}
	return path;
} // end of GetPath
///////////////////////////////////////////////////////////////////////////////
///
///\brief  GetAnchorName
///	DESCRIPTION
///
///\remarks
///
/// Arguments:
///
///\returns  The name of the Anchor this object is linked to
///
///////////////////////////////////////////////////////////////////////////////
string
CSnoBlock::GetAnchorName(void) const
{
	vector<CSnoValue> vals;
	CSnoBlock::cTValueIterator pVal;
	CSnoValue val;
	if (GetField("AnchorName", val)) {
		return val.GetStringValue();
	}
	return "";
} // end of GetPath

///////////////////////////////////////////////////////////////////////////////
///
///\brief  SetPath
///	DESCRIPTION
///
///\remarks
///
/// Arguments:
///	paths - a string vector to which to set the Path field
///
///\returns  void
///
///////////////////////////////////////////////////////////////////////////////
void
CSnoBlock::SetAnchor(const vector<string>& paths)
{
	vector<string>::const_iterator itr;

	// Delete any "Path" fields
	ClearFields("Anchor");

	// Add fields to the list
	for (itr = paths.begin(); itr != paths.end(); itr++) {
		AddField("Anchor", *itr);
	}
} // end of SetPath
//////////////////////////////////////////////////////////////////////////////
///
///\brief  GetShortComment
/// 	Returns the value of the field named "ShortComment" which was parsed by
/// 	the constructor.
///
///\remarks  The "ShortComment" field is used to make comments about a
/// 	scenario file.
///
/// Arguments:
///
///\returns  A string containing the short comment.  If no short comment was
/// 	specified, the function returns an empty string.
///
//////////////////////////////////////////////////////////////////////////////
string
CSnoBlock::GetShortComment(void) const
{
	CSnoValue val;
	if (GetField("ShortComment", val))
		return val.GetStringValue();
	else
		 return " ";
} // end of GetShortComment

//////////////////////////////////////////////////////////////////////////////
///
///\brief  GetLongComment
/// 	Returns the value of all the field named "LongComment" which were parsed
/// 	by the constructor.
///
///\remarks  The "LongComment" field is used to make comments about a
/// 	scenario file.
///
/// Arguments:
///
///\returns  A string containing the concatenated values from the long comment
/// 	fields, separated by carriage returns.  If no long comments were
/// 	specified, the function returns an empty string.
///
//////////////////////////////////////////////////////////////////////////////
string
CSnoBlock::GetLongComment(void) const
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
	}else{
		comment = " ";
	}
	return comment;
} // end of GetLongComment


//////////////////////////////////////////////////////////////////////////////
///\brief
/// 	Gets the "Priority" value for the HCSM object,
///\remark
///		HCSM elements are executed in the order according to priority
///////////////////////////////////////////////////////////////////////////////
int
CSnoBlock::GetPriority(void) const
{
	CSnoValue val;
	if (GetField("Priority", val))
        return val.GetIntValue();
	else
		 return 0;
}

CSnoBlock
CSnoBlock::GetChild(int idx) const
{
	return m_children[idx];
}

////////////////////////////////////////////////////////////////////////////////
void CSnoBlock::GetAnnotation(int& id,int& lvl) const{
    id =  m_annotedID;
    lvl = m_annotedlevel;
}
////////////////////////////////////////////////////////////////////////////////
///\brief
///   Gives a temprorary ID to each block in the tree
///\remark
///annotation: this section deals with the annotating of block, basically when merging scenario items
///and saving files, it is ideal alot of times to preserve the order the blocks appear in the file
///this makes it easier to diff a file, and is less likely to confuse alot of repo systems.
///These IDs should be consisdered temporary and transitive
///////////////////////////////////////////////////////////////////////////////
void CSnoBlock::Annotate(){
    m_annotedID = 0;
    m_annotedlevel = 0;
    AnnotateChildren(m_annotedID,m_annotedlevel);
}
////////////////////////////////////////////////////////////////////////////////
///\brief
///   Gives a temprorary IDs to children if this block
//////////////////////////////////////////////////////////////////////////////
void CSnoBlock::AnnotateChildren(int& id,int lvl){
    m_annotedlevel = lvl;
    m_annotedID = id;
    for (auto itr = m_children.begin(); itr != m_children.end(); ++itr){
        itr->AnnotateChildren(++id,lvl+1);
    }
}