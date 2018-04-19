//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Matt Schikore
// Date:	 May, 2000
//
// $Id: sobjmngrparseblock.h,v 1.1 2000/05/08 16:49:17 schikore Exp $
//
// The interface for the sobjmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _SOBJ_MNGR_PARSE_BLOCK_H
#define _SOBJ_MNGR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the sobjmngr block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CSobjMngrParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CSobjMngrParseBlock();
		CSobjMngrParseBlock(const CSobjMngrParseBlock&);
		CSobjMngrParseBlock(const CSnoBlock&);
		~CSobjMngrParseBlock();
		CSobjMngrParseBlock& operator=(const CSobjMngrParseBlock&);
};

#endif	// _SOBJ_MNGR_PARSE_BLOCK_H

