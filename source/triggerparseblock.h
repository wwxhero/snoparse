//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: triggerparseblock.h,v 1.23 2014/07/15 17:21:19 IOWA\dheitbri Exp $
//
// The interface for the trigger parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _TRIGGER_PARSE_BLOCK_H
#define _TRIGGER_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"
#include "point3d.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the trigger block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CTriggerParseBlock : public CSnoBlock {
	public:
		enum ETimeOrDistance{
			eDISTANCE = 0,
			eTIME = 1
		};

		enum EFollowInfo {
			eUNDEFINED = 0,
			eDRIVER,
			eNAMED,
			eAUTOMATIC
		};
		struct TFollowInfo {
			EFollowInfo m_type;
			std::string		m_name;
			bool		m_instigator;
		};
		// Constructors, destructor, and assignment operator
		CTriggerParseBlock();
		CTriggerParseBlock(const CTriggerParseBlock&);
		CTriggerParseBlock(const CSnoBlock&);
		~CTriggerParseBlock();
		CTriggerParseBlock& operator=(const CTriggerParseBlock&);

		// Accessor functions
		std::string			GetName(void) const;
		CPoint3D		GetPosition(void) const;
		CPoint3D		GetDrawPosition(void) const;
		double			GetCrRad(void) const;
		double			GetActvDel(void) const;
		double			GetLifetime(void) const;
		int				GetOneShot(void) const;
		double			GetDebounce(void) const;
		double			GetFireDel(void) const;
		int             GetFireDelFrames(void) const;
		double			GetTime(void) const;
		CPoint3D		GetFirePosition(void) const;
		double			GetRadius(void) const;
		std::vector<std::string>	GetByNameSet(void) const;
		std::vector<std::string>	GetByTypeSet(void) const;
		std::vector<pbTRoad>	GetByRoadSet(void) const;
		std::vector<pbTPstn>	GetByPstnSet(void) const;
		std::string			GetState(void) const;
		std::vector<std::string>	GetPath(void) const;
		int				GetNthFromStart(void) const;
		int				GetNthFromEnd(void) const;
		int				GetVehicleAhead(void) const;
		int				GetVehicleBehind(void) const;
		TFollowInfo		GetLeaderInfo(void) const;
		TFollowInfo		GetFollowerInfo(void) const;
		string			GetLeaderName(void);
		string			GetFollowerName(void);
		int				GetIsTimeOrDistance(void) const;
		int				GetUseExpression(void) const;
		bool			IsFollowTimeExp(void) const;
		bool			IsFollowDistExp(void) const;
		bool            GetIsUseExpression(void) const;
		double			GetFollowTime(void) const;
		double			GetFollowDist(void) const;
		std::string		GetFollowExpression(void) const;
		std::string     GetFollowDistExp(void) const;
		double			GetToleranceMinus(void) const;
		double			GetTolerancePlus(void) const;
		double			GetMinDuration(void) const;
		bool			UseDriverPath(void) const;
		bool			RequireSameLane(void) const;
		bool			GetSequentialActions(void) const;
		std::string			GetExpression(void) const;
		bool			GetUseSecondOrder(void) const;
		bool			GetLogTTA()const;
		int				GetTTALogNum() const;
		double			GetUpperBoundOnSpeed(void) const;
		double			GetWithinPercentSpeed(void) const;
		// Mutator functions
		void			SetName(const std::string&);
		void			SetPosition(const CPoint3D&);
		void			SetDrawPosition(const CPoint3D&);
		void			SetCrRad(double);
		void			SetActvDel(double);
		void			SetLifetime(double);
		void			SetOneShot(int);
		void			SetDebounce(double);
		void			SetFireDel(double);
		void			SetFireDelFrames(int);
		void			SetTime(double);
		void			SetFirePosition(const CPoint3D&);
		void			SetRadius(double);
		void			SetByNameSet(const std::vector<std::string>&);
		void			SetByTypeSet(const std::vector<std::string>&);
		void			SetByRoadSet(const std::vector<pbTRoad>&);
		void			SetByPstnSet(const std::vector<pbTPstn>&);
		void			SetState(const std::string&);
		void			SetPath(const std::vector<std::string>&);
		void			SetNthFromStart(int);
		void			SetNthFromEnd(int);
		void			SetVehicleAhead(int);
		void			SetVehicleBehind(int);
		void			SetLeaderInfo(const TFollowInfo&);
		void			SetFollowerInfo(const TFollowInfo&);
		void			SetFollowTime(double);
		void			SetFollowDist(double);
		void			SetUseExpression(bool);
		void			SetIsTimeOrDistance(int);
		void			SetFollowExpression(const std::string &str);
		void			SetFollowDistExp(const std::string &str);
		bool			IsFollowTime(void) const;
		void			SetToleranceMinus(double);
		void			SetTolerancePlus(double);
		void			SetMinDuration(double);
		void			SetUseDriverPath(bool);
		void			SetRequireSameLane(bool);
		void			SetSequentialActions(bool);
		void			SetExpression(const std::string&);
		void			SetUseSecondOrder(bool);
		void			SetLogTTA(bool);
		void			SetTTALogNum(int);
		void			SetUpperBoundOnSpeed(double);
		void			SetWithinPercentSpeed(double);

};

#endif	// _TRIGGER_PARSE_BLOCK_H

