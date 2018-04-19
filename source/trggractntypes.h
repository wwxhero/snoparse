/////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Jillian Vogel
// Date:     October, 1999
//
// $Id: trggractntypes.h,v 1.2 2013/04/30 00:59:20 IOWA\vhorosewski Exp $
//
// Two struct definitions common to trigger and action parse blocks.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef __TRGGR_ACTN_TYPES_H__
#define __TRGGR_ACTN_TYPES_H__

////////////////////////////////////////////////////////////
// Useful types
///////////////////////////////////////////////////////////////

// This type is used to represent the name of a road and 
//	a set of lanes on that road.  An unsigned long is used to
//	represent the lanes, because it can be used to construct a
//	bitset with 1s in the slots where a lane is included.
typedef struct pbTRoad {
	std::string	road;
	std::string	lanes;
	pbTRoad() { road = ""; lanes = "0"; };
} pbTRoad;

// This type is used to represent a 3D position and a radius
//	around that position.
typedef struct pbTPstn { 
	double	x;
	double	y;
	double	z;
	double	radius;
	pbTPstn() { x = 0.0f; y = 0.0f; z = 0.0f; radius = 0.0f; };
} pbTPstn;

#endif	// __TRGGR_ACTN_TYPES_H__
