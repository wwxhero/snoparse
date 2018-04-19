//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: trafsrcparseblock.h,v 1.9 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The interface for the trafsrc parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TRAF_SRC_PARSE_BLOCK_H
#define _TRAF_SRC_PARSE_BLOCK_H		// {secret}

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

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the trafsrc block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CTrafSrcParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CTrafSrcParseBlock();
		CTrafSrcParseBlock(const CTrafSrcParseBlock&);
		CTrafSrcParseBlock(const CSnoBlock&);
		~CTrafSrcParseBlock();
		CTrafSrcParseBlock& operator=(const CTrafSrcParseBlock&);

		// Types
		typedef struct TWeight {
			std::string name;
			int weight;
			TWeight() { name=""; weight=1; };
		} TWeight;

		enum EDistribution {
			eRANDOMUNIFORM,
			ePERIODIC
		};

		// Accessor functions
		std::string		GetName(void) const;
		CPoint3D		GetPosition(void) const;
		CPoint3D		GetDrawPosition(void) const;
		double			GetCrRad(void) const;
		double			GetActvDel(void) const;
		double			GetLifetime(void) const;
		bool			IsRandomUniform(void) const;
		std::vector<double>	GetTimes(void) const;
		std::vector<TWeight>	GetWeights(void) const;
		EDistribution	GetDistribution(void) const;
		std::vector<double>  GetPeriodic(void) const;
		bool			GetRandomizePeriodicFlag(void) const;
		// Mutator functions
		void			SetName(const std::string&);
		void			SetPosition(const CPoint3D&);
		void			SetDrawPosition(const CPoint3D&);
		void			SetCrRad(double);
		void			SetActvDel(double);
		void			SetLifetime(double);
		void			SetRandomUniform(double, double);
		void			SetPeriodic(const std::vector<double>&);
		void			SetWeights(const std::vector<TWeight>&);
		void			SetDistribution(EDistribution);
		void			SetRandomizePeriodicFlag(const bool flag);
};

#endif	// _TRAF_SRC_PARSE_BLOCK_H

