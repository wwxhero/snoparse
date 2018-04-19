//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: adoparseblock.h,v 1.36 2015/10/23 14:08:37 IOWA\dheitbri Exp $
//
// The interface for the ado parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ADO_PARSE_BLOCK_H
#define _ADO_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the ado block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CAdoParseBlock : public CSnoBlock {
	public:
		enum ESetLatOffsType {
			eRELATIVE = 0,
			eABSOLUTE = 1,
			eDISTANCE = 2
		};

		enum EDistribution {
			eFIXED,
			eUNIFORM,
			eNORMAL
		};
		struct CDelay {
			EDistribution m_type;
			double m_param1;
			double m_param2;
			CDelay() { m_type = eFIXED; m_param1 = 1.0; m_param2 = 1.0; }
		};

		enum ELcvModel {
			eRAMPS,
			eSIN,
			eRAMPSANDSIN,
			eEXPRESSION
		};

		// Constructors, destructor, and assignment operator
		CAdoParseBlock();
		CAdoParseBlock(const CAdoParseBlock&);
		CAdoParseBlock(const CSnoBlock&);
		~CAdoParseBlock();
		CAdoParseBlock& operator=(const CAdoParseBlock&);

		// Accessor functions
		std::string		GetName(void) const;
		double			GetCrRad(void) const;
		double			GetActvDel(void) const;
		double			GetLifetime(void) const;
		std::string		GetSolName(void) const;
		bool			GetRandomSol(void) const;
		std::vector<std::string>	GetPath(void) const;
		int				GetAudioState(void) const;
		int				GetVisualState(void) const;
		bool			GetAutoControlBrakeLight(void)const;
		bool			GetAutoControlHeadLight(void)const;
		std::string		GetRoadPos(void) const;
		std::string     GetDynModel(void) const;
		std::string		GetRunMode(void) const;
		std::string		GetLogFile(void) const;
		std::string		GetCmdFile(void) const;
		CPoint3D		GetOffroadPoint(void) const;
		double			GetFollowTimeMin(void) const;
		double			GetFollowTimeMax(void) const;
		double			GetFollowDistMin(void) const;
		double			GetFollowDistMax(void) const;
		bool			IsFollowTime(void) const;
		double			GetTtcThres1(void) const;
		double			GetTtcThres2(void) const;
		double			GetTtcThres3(void) const;
		double			GetEngThres(void) const;
		bool			GetUseReaDel(void) const;
		CDelay			GetStdToAccDel(void) const;
		CDelay			GetStdToDecDel(void) const;
		CDelay			GetDecToAccDel(void) const;
		CDelay			GetStpToAccDel(void) const;
		double			GetNormDistKp(void) const;
		double			GetNormDistKi(void) const;
		double			GetNormDistKd(void) const;
		double			GetNormVelKp(void) const;
		double			GetNormVel2Kp(void) const;
		double			GetOvSpeedClip(void) const;
		double			GetOvSpeedRng(void) const;
		double			GetNormAccelClip(void) const;
		double			GetNormDecelClip(void) const;
		double			GetBumpStopDist(void) const;
		double			GetAppDecRate(void) const;
		bool			GetAccel2Catch(void) const;
		double			GetMinEngTime(void) const;
		double			GetEmergDistKp(void) const;
		double			GetEmergDistKi(void) const;
		double			GetEmergDistKd(void) const;
		double			GetEmergVelKp(void) const;
		double			GetEmergVelKi(void) const;
		double			GetEmergVelKd(void) const;
		double			GetEmergAclKp(void) const;
		double			GetEmergDecClip(void) const;
		double			GetMainGapDistKp(void) const;
		double			GetMainGapDistKi(void) const;
		double			GetMainGapDistKd(void) const;
		double			GetMainGapVelKp(void) const;
		double			GetMainGapMaxAcc(void) const;
		double			GetMainGapMaxDec(void) const;
		ELcvModel		GetLcvModel(void) const;
		std::vector<double>	GetLcvRiseTime(void) const;
		std::vector<double>	GetLcvFallTime(void) const;
		std::vector<double>	GetLcvRampsAmplitude(void) const;
		std::vector<double>	GetLcvStableTime(void) const;
		std::vector<double>	GetLcvBias(void) const;
		std::vector<double>	GetLcvSinAmplitude(void) const;
		std::vector<double>	GetLcvFrequency(void) const;
		std::vector<double>	GetLcvPhase(void) const;
		std::string			GetLcvExpression(void) const;
		std::vector<double>	GetLcvReevalInterv(void) const;
		bool			GetLcvEnable(void) const;
		bool			GetLcvAutoDisable(void) const;	
		double			GetVelCtrlInitVel(void) const;	
		bool			GetVelCtrlInitMatchOvVel(void) const;
        bool            GetVelCtrlFollowSpeedLimit(void) const;
		double			GetVelCtrlRefreshTime(void) const;
		CDelay			GetVelCtrlDistribution(void) const;
		bool			GetRandomize(void) const;
		std::vector<double>	GetRandomizeSignalTime(void) const;
		double			GetSignalTime(void) const;
		double			GetUrgency(void) const;
		double			GetSteeringForce(void) const;
		bool			GetLosingCorridorEnable(void) const;
		bool			GetHighwayMergeEnable(void) const;
		bool			GetAvoidMergingObjEnable(void) const;
		bool			GetSlowMovingObjEnable(void) const;
		bool			GetVerySlowMovingObjEnable(void) const;
		bool			GetNonPassingLaneEnable(void) const;
		double			GetLaneChangeInitDelay(void) const;
		bool			GetFwdDistThresRand(void) const;
		std::vector<double>	GetFwdDistThresRandVal(void) const;
		double			GetFwdDistThresVal(void) const;
		bool			GetBackDistThresRand(void) const;
		std::vector<double>	GetBackDistThresRandVal(void) const;
		double			GetBackDistThresVal(void) const;
		bool			GetFwdTimeThresRand(void) const;
		std::vector<double>	GetFwdTimeThresRandVal(void) const;
		double			GetFwdTimeThresVal(void) const;
		bool			GetBackTimeThresRand(void) const;
		std::vector<double>	GetBackTimeThresRandVal(void) const;
		double			GetBackTimeThresVal(void) const;
		bool			GetDistFromRand(void) const;
		std::vector<double>	GetDistFromRandVal(void) const;
		double			GetDistFromVal(void) const;
		bool			GetTimeToRand(void) const;
		std::vector<double>	GetTimeToRandVal(void) const;
		double			GetTimeToVal(void) const;
		bool			GetAvoidTurning(void) const;
		int				GetColorIndex(void) const;
		bool            GetIsCreateRelative(void) const;
		bool            GetIsCreateLatFeet(void) const;
		int				GetLatOffsType(void) const;
		int             GetCreateAbsoluteLane(void) const;
		int             GetCreateRelativeLane(void) const;
		double          GetLaneOffs(void) const;
		std::string     GetCreateRelativeObjName(void) const;
		double          GetCreateRelativeOffsetLateral(void) const;
		double          GetCreateRelativeOffsetLongitudinal(void) const;
		std::string		GetCreateRelativeOffsetLongitudinalExpression(void) const;
		bool			GetUseExpressionForRelativeLongintidinalOffset(void) const;
		int				GetPathSearchDepth(void) const;
        double          GetMaxLaneChangeLatOffset(void) const;
		double          GetAggressiveness(void) const;
		// Mutator functions
		void			SetName(const std::string&);
		void			SetCrRad(double);
		void			SetActvDel(double);
		void			SetLifetime(double);
		void			SetSolName(const std::string&);
		void			SetRandomSol(bool);
		void			SetPath(const std::vector<std::string>&);
		void			SetAudioState(int);
		void			SetVisualState(int);
		void			SetAutoControlBrakeLight(bool);
		void			SetAutoControlHeadLight(bool);
		void			SetRoadPos(const std::string&);
		void            SetDynModel(const std::string&);
		void			SetRunMode(const std::string&);
		void			SetLogFile(const std::string&);
		void			SetCmdFile(const std::string&);
		void			SetOffroadPoint(const CPoint3D&);
		void			RemoveOffroadPoint(void);
		void			SetFollowTimeMin(double);
		void			SetFollowTimeMax(double);
		void			SetFollowDistMin(double);
		void			SetFollowDistMax(double);
		void			SetIsFollowTime(bool);
		void			SetTtcThres1(double);
		void			SetTtcThres2(double);
		void			SetTtcThres3(double);
		void			SetEngThres(double);
		void			SetUseReaDel(bool);
		void			SetStdToAccDel(const CDelay&);
		void			SetStdToDecDel(const CDelay&);
		void			SetDecToAccDel(const CDelay&);
		void			SetStpToAccDel(const CDelay&);
		void			SetNormDistKp(double);
		void			SetNormDistKi(double);
		void			SetNormDistKd(double);
		void			SetNormVelKp(double);
		void			SetNormVel2Kp(double);
		void			SetOvSpeedClip(double);
		void			SetOvSpeedRng(double);
		void			SetNormAccelClip(double);
		void			SetNormDecelClip(double);
		void			SetBumpStopDist(double);
		void			SetAppDecRate(double);
		void			SetAccel2Catch(bool);
		void			SetMinEngTime(double);
		void			SetEmergDistKp(double);
		void			SetEmergDistKi(double);
		void			SetEmergDistKd(double);
		void			SetEmergVelKp(double);
		void			SetEmergVelKi(double);
		void			SetEmergVelKd(double);
		void			SetEmergAclKp(double);
		void			SetEmergDecClip(double);
		void			SetMainGapDistKp(double);
		void			SetMainGapDistKi(double);
		void			SetMainGapDistKd(double);
		void			SetMainGapVelKp(double);
		void			SetMainGapMaxAcc(double);
		void			SetMainGapMaxDec(double);
		void			SetLcvModel(ELcvModel);
		void			SetLcvRiseTime(const std::vector<double>&);
		void			SetLcvFallTime(const std::vector<double>&);
		void			SetLcvRampsAmplitude(const std::vector<double>&);
		void			SetLcvStableTime(const std::vector<double>&);
		void			SetLcvBias(const std::vector<double>&);
		void			SetLcvSinAmplitude(const std::vector<double>&);
		void			SetLcvFrequency(const std::vector<double>&);
		void			SetLcvPhase(const std::vector<double>&);
		void			SetLcvExpression(const std::string&);
		void			SetLcvReevalInterv(const std::vector<double>&);
		void			SetLcvEnable(bool);
		void			SetLcvAutoDisable(bool);
		void			SetVelCtrlInitMatchOvVel(bool initMatchVel);
        void            SetVelCtrlFollowSpeedLimit(bool isFollowSpeedLimit);
		void			SetVelCtrlInitVel(double);
		void			SetVelCtrlTargetVel(double);
		void			SetVelCtrlRefreshTime(double);
		void			SetVelCtrlDistribution(const CDelay&);
		void			SetRandomize(bool);
		void			SetRandomizeSignalTime(const std::vector<double>&);
		void			SetSignalTime(double);
		void			SetUrgency(double);
		void			SetSteeringForce(double);
		void			SetLosingCorridorEnable(bool);
		void			SetHighwayMergeEnable(bool);
		void			SetAvoidMergingObjEnable(bool);
		void			SetSlowMovingObjEnable(bool);
		void			SetVerySlowMovingObjEnable(bool);
		void			SetNonPassingLaneEnable(bool);
		void			SetLaneChangeInitDelay(double);
		void			SetFwdDistThresRand(bool);
		void			SetFwdDistThresRandVal(const std::vector<double>&);
		void			SetFwdDistThresVal(double);
		void			SetBackDistThresRand(bool);
		void			SetBackDistThresRandVal(const std::vector<double>&);
		void			SetBackDistThresVal(double);
		void			SetFwdTimeThresRand(bool);
		void			SetFwdTimeThresRandVal(const std::vector<double>&);
		void			SetFwdTimeThresVal(double);
		void			SetBackTimeThresRand(bool);
		void			SetBackTimeThresRandVal(const std::vector<double>&);
		void			SetBackTimeThresVal(double);
		void			SetDistFromRand(bool);
		void			SetDistFromRandVal(const std::vector<double>&);
		void			SetDistFromVal(double);
		void			SetTimeToRand(bool);
		void			SetTimeToRandVal(const std::vector<double>&);
		void			SetTimeToVal(double);
		void			SetAvoidTurning(bool);
		void			SetColorIndex(int);
		void            SetIsCreateRelative(bool);
		void			SetLatOffsType(int);
		void            SetIsCreateLatFeet(bool);
		void            SetCreateAbsoluteLane(int);
		void            SetCreateRelativeLane(int);
		void            SetLaneOffs(double);
		void            SetCreateRelativeObjName(const std::string&);
		void            SetCreateRelativeOffsetLateral(double);
		void            SetCreateRelativeOffsetLongitudinal(double);
		void			SetCreateRelativeOffsetLongitudinalExpression(const std::string&) ;
		void			SetUseExpressionForRelativeLongintidinalOffset(bool);
		void			SetPathSearchDepth(int);
        void            SetMaxLaneChangeLatOffset(double);
		void            SetAggressiveness(double);
		// Misc functions
		bool			IsAdoOnRoad(void) const;
};

#endif	// _ADO_PARSE_BLOCK_H

