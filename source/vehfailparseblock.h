//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: vehfailparseblock.h,v 1.2 2000/03/08 21:43:02 jvogel Exp $
//
// The interface for the vehfail parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _VEH_FAIL_PARSE_BLOCK_H
#define _VEH_FAIL_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the vehfail block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CVehFailParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CVehFailParseBlock();
		CVehFailParseBlock(const CVehFailParseBlock&);
		CVehFailParseBlock(const CSnoBlock&);
		~CVehFailParseBlock();
		CVehFailParseBlock& operator=(const CVehFailParseBlock&);
};

#endif	// _VEH_FAIL_PARSE_BLOCK_H

