/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     September, 1998
//
// $Id: snoblock.h,v 1.33 2018/03/22 19:31:04 IOWA\dheitbri Exp $
//
// The interface for the scenario block class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _SNO_BLOCK_H
#define _SNO_BLOCK_H

#ifdef _WIN32
#pragma warning(disable:4786)
#endif
#include <stdlib.h>
#include <typeinfo.h>
#include <string>
#include <vector>

#include "snovalue.h"

class CSnoParser;

//////////////////////////////////////////////////////////////////////////////
///\brief
///		CSnoBlock base class for sno objects
///
/// This class represents a block within the scenario file.  A block
/// has a name and consists of one or more fields.  A block
/// represents either the header of the scenario file or the initialization
/// string of an hcsm.
///
/// A block can contain other blocks, in effect allowing the creation
/// of an arbitrary hierarchy.
///
/// The class provides functions to add fields, iterate through existing
/// fields, add blocks, and go through existing blocks.  In addition,
/// the class provides a member function (store) that can be used to
/// generate a representation of the block into an STL string.
///\ingroup snoparse
//////////////////////////////////////////////////////////////////////////////
class CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CSnoBlock();
		CSnoBlock(const CSnoBlock&);
		CSnoBlock(const std::string&);
		virtual ~CSnoBlock();
		CSnoBlock&	operator=(const CSnoBlock &);

		// Types
		typedef std::vector<CSnoValue>			TValueVec;
		typedef std::pair<std::string, TValueVec>		TField;
		typedef std::vector<TField>				TFieldMap;
		typedef std::vector<CSnoBlock>			TBlockVec;
        typedef std::vector<std::string>           TStringVec;
		// Mutators
		bool			Parse(const std::string &s);
		bool			Parse(const std::string &s, int& pos);
		void			Store(std::string &s, int level = 0) const;

		void			ClearAll(void);
		void			ClearChildren(void);
		void			ClearFields(void);
		void			ClearFields(const std::string&);

		void			SetShortComment(const std::string& comment);
		void			SetLongComment(const std::string& comment);
		void			SetBlockName(const std::string &);
        void            SetPriority(const int );

		void			AddChild(const CSnoBlock&);
        void			AddChildFront(const CSnoBlock&);
		void			AddField(const TField&);
		void			AddField(const std::string&, int);
		void			AddField(const std::string&, double);
		void			AddField(const std::string&, std::string);
		void			AddField(const std::string&, const std::vector<int>&);
		void			AddField(const std::string&, const std::vector<char>&);
		void			AddField(const std::string&, const std::vector<double>&);
		void			AddField(const std::string&, const std::vector<float>&);
        void            AddField(const std::string&, const TStringVec&);

        void            SetAnchor(const TStringVec&);
		// Accessors
		bool			IsHeader(void) const;
		const std::string&	GetBlockName(void) const;

		int				GetChildCount(void) const;
		int				GetFieldCount(void) const;
		int				GetFieldCount(const std::string&) const;
		bool			GetField(const std::string&, CSnoValue&) const;
		bool			GetField(const std::string&,
								 std::vector<CSnoValue>&) const;

		virtual std::string	GetName( ) const;

		std::string		GetGroupName() const;
		void			SetGroupName(const std::string& str);
		bool			IsExtRef() const;
		virtual void	SetIsExtRef(bool extRef);
		std::string		GetExtInfo() const;
		void			SetExtInfo(const std::string& str);
		std::string		GetLongComment(void) const;
		std::string		GetShortComment(void) const;
        bool                 GetStaticExtRefChildren(TBlockVec *staticExtRefs);
        bool                 GetTrafficLightExtRefChildren(TBlockVec *lightExtRefs);
        TStringVec  GetAnchor() const;

		void			SetAnchorName(const std::string& name);
		std::string		GetAnchorName(void) const;
		// Iterators
		typedef TFieldMap::const_iterator	cTFieldIterator;
		typedef TBlockVec::const_iterator	cTChildIterator;
		typedef TValueVec::const_iterator	cTValueIterator;
		typedef TBlockVec::iterator			TChildIterator;

		cTFieldIterator	BeginField(void) const;
		cTFieldIterator	EndField(void) const;

		cTChildIterator	BeginChild(void) const;
		cTChildIterator	EndChild(void) const;

		TChildIterator	BeginChild(void);
		TChildIterator	EndChild(void);

        int             GetPriority() const;
		void			SetParser(CSnoParser* pParser) { m_pParser = pParser; }
		std::string			GetLastErr(){return m_lastErr;}
		// Errors
		// This struct is thrown when there is an error
		//	in the number of fields present during a
		//	field retrieval on a subclass.
		typedef struct TCountError {
			std::string field;
			std::string msg;
			TCountError(const std::string& f, int n)
			{
				field=f;
				msg = f;
				msg += " must contain ";
				msg += n;
				msg += " values.";
			}
		} TCountError;
        void Annotate();
        void GetAnnotation(int&,int&) const;
        virtual void AnnotateChildren(int&,int);
		// This struct is thrown when there is a type mismatch
		//	during the parsing of a block
		typedef struct TTypeMismatch {
			std::string field;	// Name of field with mismatch
			std::string msg;		// Message to send
			TTypeMismatch(const std::string& f,
						  const std::string& b,
						  const std::string& c)
			{
				field = f;
				msg = f;
				msg += " contained two types: '";
				msg += b;
				msg += "' and '";
				msg += c;
				msg += "'";
			};
		} TTypeMismatch;

		// This struct is thrown when there is a syntax error
		//	encountered during the parsing of a block
		typedef struct TSyntaxError {
			std::string line;	// Line where error occurred
			int pos;		// Position on line where error occurred
			std::string err;		// Syntax error description
			TSyntaxError(const std::string& l, int p, const std::string& e)
				{ line=l; pos=p; err=e; };
		} TSyntaxError;

    private:

		// Local data
		std::string			m_name;
		std::string			m_lastErr;
		TFieldMap		m_fields;
		TBlockVec		m_children;
		CSnoParser		*m_pParser;

		std::vector <CSnoBlock> m_staticExtRefs;
		std::vector <CSnoBlock> m_TrafLightExtRefs;

		// Useful types
		typedef TFieldMap::iterator	TFieldIterator;
		typedef TValueVec::iterator	TValueIterator;

		// Utility functions
		static bool		IsEmptyLine(std::string &str);
		static bool		GetLine(const std::string&, int&, std::string&);
		static bool		Tokenize(const std::string&, int&, std::string&);


		cTFieldIterator  FindFirst( const std::string& str ) const;
		cTFieldIterator  FindLast( const std::string& str ) const;
		TFieldIterator   FindFirst( const std::string& str );
		TFieldIterator   FindLast( const std::string& str );
        static std::string    GetTypeName(CSnoValue::EType);
protected:
        CSnoBlock	GetChild(int idx) const;
        int  m_annotedID;   //<semi-unique ID, expresses order in the tree
        int  m_annotedlevel;//<marks how deep the block is in the tree
};	// end of CSnoBlock

//////////////////////////////////////////////////////////////////////////////
//	Inline functions
//////////////////////////////////////////////////////////////////////////////
inline CSnoBlock::~CSnoBlock() {}

inline CSnoBlock::CSnoBlock() : m_name(""),m_annotedID(-1),m_annotedlevel(-1) {m_pParser = 0;}

inline CSnoBlock::CSnoBlock(const std::string &s) : m_name(s),m_annotedID(-1),m_annotedlevel(-1) {m_pParser = 0;}

#endif	// _SNO_BLOCK_H

