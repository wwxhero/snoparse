//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: trafmngrparseblock.h,v 1.9 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// The interface for the trafmngr parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TRAF_MNGR_PARSE_BLOCK_H
#define _TRAF_MNGR_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

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
// This class represents the trafmngr block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CTrafMngrParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CTrafMngrParseBlock();
		CTrafMngrParseBlock(const CTrafMngrParseBlock&);
		CTrafMngrParseBlock(const CSnoBlock&);
		~CTrafMngrParseBlock();
		CTrafMngrParseBlock& operator=(const CTrafMngrParseBlock&);

		// Useful types
		// This structure defines an Input Set.  An input set determines
		// 	the controls for the traffic manager.  Each traffic manager may
		// 	contain any number of input sets, which can be switched using
		// 	the InputSet dial.
		typedef CTrafSrcParseBlock::TWeight TWeight;
		typedef struct TInputSet {
			std::string name;		// Name of the particular input set
			double minDensity;	// Desired minimum number of objects 
								//	per unit of road
			double maxDensity;	// Desired maximum number of objects 
								//	per unit of road
			int maxObjects;		// Maximum allowed number of existing objects 
								//	that were created by the TrafficManager
			double createDist; 	// Minimum distance from the own vehicle that
								//	an ADO may be created
			double deleteDist;	// Minimum distance from the own vehicle that
								//	an ADO may be deleted
			double absDeleteDist;// Distance from the own vehicle that will 
								//	cause automatic deletion of a previously 
								//	created ADO
			double runFreq;		// Frequency at which the TrafficManager 
								//	should re-assess the traffic situation
			std::vector<TWeight> solWeights;
								// Sol Names and weights indicating the
								// 	frequency that they should be used.
			int	totalWeights;	// A value used by the TrafficManager that is
								//	the sum of all the weights in the vector.
								// There is NO ASSOCIATED FIELD.
			TInputSet() {
				name = ""; minDensity = 0.0f; maxDensity = 0.0f;
				maxObjects = 0; createDist = 0.0f; deleteDist = 0.0f;
				absDeleteDist = 0.0f; runFreq = 0.0f; totalWeights = 0;
			};
		} TInputSet;

		// Accessor functions
		std::vector<TInputSet>GetInputSets(void) const;

		// Mutator functions
		void			SetInputSets(const std::vector<TInputSet>&);
		void			AddInputSet(const TInputSet&);
		void			ClearInputSets(void);
};

#endif	// _TRAF_MNGR_PARSE_BLOCK_H

