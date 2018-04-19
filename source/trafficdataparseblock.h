//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// $Id: trafficdataparseblock.h,v 1.3 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// Author:	 Omar Ahmad, Sunil Bulusu
// Date:	 June, 2001
//
// The interface for the traffic data parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TRAFFIC_DATA_PARSE_BLOCK_H
#define _TRAFFIC_DATA_PARSE_BLOCK_H		// {secret}

#include <string>

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the ado block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CTrafficDataParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CTrafficDataParseBlock();
		CTrafficDataParseBlock(const CTrafficDataParseBlock&);
		CTrafficDataParseBlock(const CSnoBlock&);
		~CTrafficDataParseBlock();
		CTrafficDataParseBlock& operator=(const CTrafficDataParseBlock&);

		// Accessor functions
		bool            GetLogAllObjs(void) const;
		std::string          GetLogObjName(void) const;
		bool            GetLogAccel(void) const;       // Acceleration
		double           GetAccelMin(void) const;
		double           GetAccelMax(void) const;
//		bool            GetLogLaneOffset(void) const;  // Lane offset
//		bool            GetLogCollision(void) const;   // Collision
//		bool            GetLogQueueLength(void) const; // Queue length
//		bool            GetLogDeadlock(void) const;    // Deadlock
//		bool            GetLogTtc(void) const;         // Time-to-collision

		// Mutator functions
		void            SetLogAllObjs(bool);
		void            SetLogObjName(const std::string&);
		void            SetLogAccel(bool);       // Acceleration
		void            SetAccelMin(double);
		void            SetAccelMax(double);
//		void            SetLogLaneOffset(bool);  // Lane offset
//		void            SetLogCollision(bool);   // Collision
//		void            SetLogQueueLength(bool); // Queue length
//		void            SetLogDeadlock(bool);    // Deadlock
//		void            SetLogTtc(bool);         // Time-to-collision

};

#endif	// _TRAFFIC_DATA_PARSE_BLOCK_H

