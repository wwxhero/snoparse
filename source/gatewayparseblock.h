//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: gatewayparseblock.h,v 1.2 2000/03/08 21:43:02 jvogel Exp $
//
// The interface for the gateway parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _GATEWAY_PARSE_BLOCK_H
#define _GATEWAY_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the gateway block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CGatewayParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CGatewayParseBlock();
		CGatewayParseBlock(const CGatewayParseBlock&);
		CGatewayParseBlock(const CSnoBlock&);
		~CGatewayParseBlock();
		CGatewayParseBlock& operator=(const CGatewayParseBlock&);
};

#endif	// _GATEWAY_PARSE_BLOCK_H

