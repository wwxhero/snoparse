//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: enviroinfoparseblock.h,v 1.4 2016/10/28 21:00:53 IOWA\dheitbri Exp $
//
// The interface for the envroinfo parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ENVRO_INFO_PARSE_BLOCK_H
#define _ENVRO_INFO_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the envroinfo block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CEnviroInfoParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CEnviroInfoParseBlock();
		CEnviroInfoParseBlock(const CEnviroInfoParseBlock&);
		CEnviroInfoParseBlock(const CSnoBlock&);
		~CEnviroInfoParseBlock();
		CEnviroInfoParseBlock& operator=(const CEnviroInfoParseBlock&);
        static const size_t m_cStrSize = 10;
		// Types
		typedef union TEnvUnion{

			struct Lightning {
				char        degree[m_cStrSize];
			} Lightning;

			struct Visibility {
				double       dist;
			} Visibility;

			struct Haze {
				double       dist;
			} Haze;

			struct Fog {
				double       dist;
			} Fog;

			struct Smoke {
				double       degree;
			} Smoke;

			struct Clouds {
				double       altitude;
				int         type;
			} Clouds;

			struct Glare {
				double       degree;
			} Glare;

			struct Snow {
				char        degree[m_cStrSize];
			} Snow;

			struct Rain {
				char        degree[m_cStrSize];
			} Rain;

			struct Wind {
				double       dirX;
				double       dirY;
				double       vel;
				double       gust;
			} Wind;

		} TEnvUnion;

		struct TEnviroInfo{
			char       type[m_cStrSize];
			TEnvUnion  info;
		};	

		// Accessor functions
		TEnviroInfo		GetEnviroInfo(void) const;

		// Mutator functions
		void			SetEnviroInfo(const TEnviroInfo&);

	private:
		// Other function
		static void ConvertStringUpper(char*); 
};

#endif	// _ENVRO_INFO_PARSE_BLOCK_H

