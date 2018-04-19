//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// $Id: daqdriverparseblock.h,v 1.4 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// Author:	 Omar Ahmad, Sunil Bulusu
// Date:	 June, 2001
//
// The interface for the traffic data parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _DAQ_DRIVER_PARSE_BLOCK_H
#define _DAQ_DRIVER_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the ado block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CDaqDriverParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CDaqDriverParseBlock();
		CDaqDriverParseBlock(const CDaqDriverParseBlock&);
		CDaqDriverParseBlock(const CSnoBlock&);
		~CDaqDriverParseBlock();
		CDaqDriverParseBlock& operator=(const CDaqDriverParseBlock&);

		// Accessor functions
		std::string          GetDriverPosFileName(void) const;
		std::string          GetDriverOriFileName(void) const;
		double           GetFreq(void) const;

		// Mutator functions
		void            SetDriverPosFileName(const std::string&);
		void            SetDriverOriFileName(const std::string&);
		void            SetFreq(double);
};

#endif	// _DAQ_DRIVER_PARSE_BLOCK_H

