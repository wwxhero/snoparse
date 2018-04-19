//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: clgparseblock.h,v 1.5 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The interface for the clg parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _CLG_PARSE_BLOCK_H
#define _CLG_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the clg block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CClgParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CClgParseBlock();
		CClgParseBlock(const CClgParseBlock&);
		CClgParseBlock(const CSnoBlock&);
		~CClgParseBlock();
		CClgParseBlock& operator=(const CClgParseBlock&);

		// Types
		typedef struct TClgRow {
			std::string          lightName;
			std::vector<std::string>  pattern;
		} TClgRow;

		typedef struct TClgTable {
			std::string          intrsctnName;
			std::vector<double>	duration;
			std::vector<TClgRow>	clgRows;
		} TClgTable;

		// Accessor functions
		TClgTable		GetClgTable(void) const;
		std::string			GetIntrsctnName(void) const;
		std::vector<double>	GetDuration(void) const;
		std::vector<TClgRow>	GetClgRows(void) const;

		// Mutator functions
		void			SetClgTable(const TClgTable&);
		void			SetIntrsctnName(const std::string&);
		void			SetDuration(const std::vector<double>&);
		void			SetClgRows(const std::vector<TClgRow>&);
};

#endif	// _CLG_PARSE_BLOCK_H

