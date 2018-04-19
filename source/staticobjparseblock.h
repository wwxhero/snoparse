//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Matt Schikore
// Date:	 May, 2000
//
// $Id: staticobjparseblock.h,v 1.10 2015/07/31 15:42:19 IOWA\dheitbri Exp $
//
// The interface for the staticobj parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _STATIC_OBJ_PARSE_BLOCK_H
#define _STATIC_OBJ_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the staticobj block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CStaticObjParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CStaticObjParseBlock();
		CStaticObjParseBlock(const CStaticObjParseBlock&);
		CStaticObjParseBlock(const CSnoBlock&);
		~CStaticObjParseBlock();
		CStaticObjParseBlock& operator=(const CStaticObjParseBlock&);
		struct TCompositePiece {
			std::string solName;
			int cigiId;
			int option;
			int optionCigiId;
		};

		// Accessor functions
		std::string			GetSolName(void) const;
		std::string			GetName(void) const;
		CPoint3D		GetPosition(void) const;
		double			GetOrientation(void) const;
		bool			GetIsNewObj(void) const;
		int				GetAudioState(void) const;
		int				GetVisualState(void) const;
		int				GetOption(void) const;
		std::vector<std::string>	GetSolOptions(void) const;
		int				GetCrdr(void) const;
		int				GetHoldOffs(void) const;
		int				GetColorIndex(void) const;
		std::vector<TCompositePiece> GetCompositePieces(void) const;
		CPoint3D		GetDrawPosition(void) const;

		// Mutator functions
		void 			SetSolName(const std::string&);
		void 			SetName(const std::string&);
		void 			SetPosition(const CPoint3D&);
		void 			SetOrientation(double);
		void			SetIsNewObj(bool);
		void			SetAudioState(int);
		void			SetVisualState(int);
		void			SetOption(int);
		void			SetSolOptions(const std::vector<std::string>&);
		void			SetCrdr(int);
		void			SetHoldOffs(int);
		void			SetColorIndex(int);
		void			SetCompositePieces(const std::vector<TCompositePiece>&);
		void			SetDrawPosition(const CPoint3D& drawPos);
};

#endif	// _STATIC_OBJ_PARSE_BLOCK_H

