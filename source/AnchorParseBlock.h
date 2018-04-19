//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: AnchorParseBlock.h,v 1.3 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The interface for the trafsrc parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ANCHOR_PARSE_BLOCK_H
#define _ANCHOR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"
#include "point3d.h"

#ifdef _WIN32
#include <strstream>
#elif _PowerMAXOS
#include <strstream>
#define ostringstream ostrstream
#elif __sgi
#include <strstream.h>
#endif
#pragma once

#include "snoblock.h"

class CAnchorParseBlock :
	public CSnoBlock
{
public:
		// Constructors, destructor, and assignment operator
		CAnchorParseBlock();
		CAnchorParseBlock(const CAnchorParseBlock&);
		CAnchorParseBlock(const CSnoBlock&);
		~CAnchorParseBlock();
		CAnchorParseBlock& operator=(const CAnchorParseBlock&);

		// Accessor functions
		std::string			GetName(void) const;
		CPoint3D		GetPosition(void) const;
		CPoint3D		GetDrawPosition(void) const;

		// Mutator functions
		void			SetName(const std::string&);
		void			SetPosition(const CPoint3D&);
		void			SetDrawPosition(const CPoint3D&);
};
#endif
