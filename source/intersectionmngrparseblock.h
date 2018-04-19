//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: intersectionmngrparseblock.h,v 1.2 2000/03/08 21:43:02 jvogel Exp $
//
// The interface for the intrsctnmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _INTERSECTION_MNGR_PARSE_BLOCK_H
#define _INTERSECTION_MNGR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the intrsctnmngr block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CIntersectionMngrParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CIntersectionMngrParseBlock();
		CIntersectionMngrParseBlock(const CIntersectionMngrParseBlock&);
		CIntersectionMngrParseBlock(const CSnoBlock&);
		~CIntersectionMngrParseBlock();
		CIntersectionMngrParseBlock& operator=(const CIntersectionMngrParseBlock&);
};

#endif	// _INTERSECTION_MNGR_PARSE_BLOCK_H

