//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: ownvehiclemirrorparseblock.h,v 1.2 2000/03/08 21:43:02 jvogel Exp $
//
// The interface for the ownvehiclemirror parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _OWN_VEHICLE_MIRROR_PARSE_BLOCK_H
#define _OWN_VEHICLE_MIRROR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the ownvehiclemirror block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class COwnVehicleMirrorParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		COwnVehicleMirrorParseBlock();
		COwnVehicleMirrorParseBlock(const COwnVehicleMirrorParseBlock&);
		COwnVehicleMirrorParseBlock(const CSnoBlock&);
		~COwnVehicleMirrorParseBlock();
		COwnVehicleMirrorParseBlock& operator=(const COwnVehicleMirrorParseBlock&);

};

#endif	// _OWN_VEHICLE_MIRROR_PARSE_BLOCK_H

