//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: traflghtmngrparseblock.h,v 1.5 2003/12/05 20:22:36 schikore Exp $
//
// The interface for the traflghtmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TRAF_LGHT_MNGR_PARSE_BLOCK_H
#define _TRAF_LGHT_MNGR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the traflghtmngr block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CTrafLghtMngrParseBlock : public CSnoBlock {
	public:

		enum EState {
			eALWAYS_ON = 953,
			eNEAR_DRIVER,
			eOFF
		};

		// Constructors, destructor, and assignment operator
		CTrafLghtMngrParseBlock();
		CTrafLghtMngrParseBlock(const CTrafLghtMngrParseBlock&);
		CTrafLghtMngrParseBlock(const CSnoBlock&);
		~CTrafLghtMngrParseBlock();
		CTrafLghtMngrParseBlock& operator=(const CTrafLghtMngrParseBlock&);

		// Accessor functions
		double			GetDist(void) const;
		EState			GetState(void) const;
		
		// Mutator functions
		void			SetDist(double);
		void			SetState(EState);
};

#endif	// _TRAF_LGHT_MNGR_PARSE_BLOCK_H

