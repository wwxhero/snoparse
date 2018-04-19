//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: envcontrolparseblock.h,v 1.7 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The interface for the envcontrol parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ENV_CONTROL_PARSE_BLOCK_H
#define _ENV_CONTROL_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"
#include "point2d.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the envcontrol block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CEnvControlParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CEnvControlParseBlock();
		CEnvControlParseBlock(const CEnvControlParseBlock&);
		CEnvControlParseBlock(const CSnoBlock&);
		~CEnvControlParseBlock();
		CEnvControlParseBlock& operator=(const CEnvControlParseBlock&);

		// Accessor functions
		CPoint2D		GetOrigin(void) const;
		std::vector<CPoint2D>GetArea(void) const;

		// Mutator functions
		void			SetOrigin(const CPoint2D&);
		void			SetArea(const std::vector<CPoint2D>&);
		bool			IsGlobalEnv() const;

};

#endif	// _ENV_CONTROL_PARSE_BLOCK_H

