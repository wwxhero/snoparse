//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     January, 1999
//
// $Id: snoparse.h,v 1.14 2017/05/03 17:14:07 IOWA\dheitbri Exp $
//
// The interface for the scenario parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _SNO_PARSE_H
#define _SNO_PARSE_H		// {secret}

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#ifdef _WIN32
#pragma warning(disable:4786)
#endif

#include "snoblock.h"

//////////////////////////////////////////////////////////////////////////////
///\defgroup snoparse snoparse
///\brief
///		Lib for parsing scenario files
///\remark
///		This class provides for parsing, serialization, and deserialization
///		of scenario elements.
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
///
/// This class represents a scenario file and allows parsing and saving
/// of the contents of the file without explicit knowledge of the
/// format or syntax of the file.
///
/// The scenario file consists of one or more blocks.  Each block can be
/// an HCSM block, or the scenario file header.  Generally, only the first
/// block of the file is the header, and the remaining blocks represent
/// HCSMs.  A block is represented by an instance of the class CSnoBlock.
///
/// Blocks can be nested, i.e., a block can contain a list of child blocks
/// defined within it.  This feature is useful to support HCSMs that contain
/// full blocks of other HCSMs within them.  An example of such an HCSM
/// is the trigger or the traffic source which can contain one or more
/// HCSMs in it.  The class allows manipulation of such blocks with ease.
///
/// The class can be used to parse a file and to also produce a file.  To
/// parse a file, read its contents into a field and pass it to the
/// appropriate constructor or the parse member function.  Once completed,
/// the various member functions
/// and iterators can be used to look into the available blocks.
///
/// For examples of how to use this class, see the parse and store
/// member functions.
///\ingroup snoparse
//////////////////////////////////////////////////////////////////////////////
class CSnoParser {

	public:
		// Constructors, destructor, and assignment operator
		CSnoParser();
		CSnoParser(const CSnoParser &);
		virtual ~CSnoParser();
		CSnoParser &operator=(const CSnoParser &);
		CSnoParser(const std::string &);

		// Mutators
		bool	Parse(const std::string&);
		bool	ParseFile(const std::string&);
		void	Clear(void);
		void	AddBlock(const CSnoBlock&);

		// Accessors
		void	Store(std::string&) const;
		int		GetBlockCount(void) const;
		std::string	GetLastErr(){return m_lastErr;}
		// Iterators
		typedef std::vector<CSnoBlock>::const_iterator TIterator;
		TIterator	Begin(void) const;
		TIterator	End(void) const;

		// Errors
		typedef struct TError {
			std::string msg;		// Describes the error
			TError(const std::string& s) { msg = s; }
		} TError;

		std::string	GetFilename() { return m_filename; }
		void	SetFilename(const std::string& filename) { m_filename = filename; }
        void    Annotate();
	private:
		// State of parser
		typedef enum { eEMPTY = 0, eLOADED } EState;	// {secret}
		EState		m_state;							// {secret}
		std::vector<CSnoBlock>	m_blocks;					// {secret}
		std::string				m_filename;
		std::string				m_lastErr;
}; // end of CSnoParser class

std::ostream&
operator<<(std::ostream&, const CSnoParser&);

//////////////////////////////////////////////////////////////////////////////
///
///\brief
/// 	The default constructor creates an unitialized instance of the class.
///
/// Remarks: This constuctor is best used when creating a new file.
///
/// Arguments:
///
///\returns void
///
//////////////////////////////////////////////////////////////////////////////
inline
CSnoParser::CSnoParser() : m_state(eEMPTY) {}

//////////////////////////////////////////////////////////////////////////////
///
///\brief
/// 	The default destructor clears out the member data.
///
/// Remarks:
///
/// Arguments:
///
///\returns void
///
//////////////////////////////////////////////////////////////////////////////
inline
CSnoParser::~CSnoParser() { Clear(); }
#endif	// _SNO_PARSE_H

