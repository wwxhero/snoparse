//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: ddoparseblock.h,v 1.24 2015/05/21 19:48:49 IOWA\dheitbri Exp $
//
// The interface for the ddo parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _DDO_PARSE_BLOCK_H
#define _DDO_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

///////////////////////////////////////////////////////////////////////////////
///\brief
///		Snoparse block for DDOs
///\remark
/// This class represents the ddo block.  It provides custom
/// access functions for accsessing the data associated with this block.
///
/////////////////////////////////////////////////////////////////////////////// 
class CDdoParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CDdoParseBlock();
		CDdoParseBlock(const CDdoParseBlock&);
		CDdoParseBlock(const CSnoBlock&);
		~CDdoParseBlock();
		CDdoParseBlock& operator=(const CDdoParseBlock&);
		
		// Types
		/////////////////////////////////////////////////////////////////////////
		///\remark
		/// This structure holds a single point of the trajectory and the value for
		/// tangent of the spline at the control point.  Note
		/// that only the x,y coordinates are specified along with a desired
		/// velocity at each point.  Combined with the initial value of the
		/// z coordinate (accessed through InitZ()), a deterministic dynamic object
		/// can derive the necessary elevation at runtime.
		///////////////////////////////////////////////////////////////////////////
		typedef struct TTrajPoint {
			double x;		// x coordinate
			double y;		// y coordinate
			double vel;		// desired velocity at the point
			double i;		// x value fot the tangent vector
			double j;		// y value fot the tangent vector
			TTrajPoint() { x=0.0f; y=0.0f; vel=0.0f; i=0.0f; j=0.0f; };
		} TTrajPoint;

		enum EState {
			eNORMAL,
			eFREE,
			eCOUPLED,
			eRELATIVE
		};
		enum EAnimationActions {
			eNothing = 0,
			eWalkingAct1 =1,
			eWalkingAct2 =2,
			eRunningAct1 =3,
			eStationaryAct1 =4,
			eStationaryAct2 =5,
			eStationaryAct3 =6,
			eStationaryAct4 =7			
		};

		static bool ActionTypeToString(char in, std::string& out);
		static char StringToActionType(const std::string&);

		// Accessor functions
		std::string		       GetName(void) const;
		CPoint3D		       GetPosition(void) const;
		double			       GetCrRad(void) const;
		double			       GetActvDel(void) const;
		double			       GetLifetime(void) const;
		std::string		       GetSolName(void) const;
		int				       GetAudioState(void) const;
		int				       GetVisualState(void) const;
		int				       GetQuitAtEnd(void) const;
		int				       GetDependent(void) const;
		int				       GetRefPoint(void) const;
		CPoint3D		       GetDependentRefPoint(void) const;
		std::string	           GetDependentName(void) const;
		bool			       IsDependentOwnVeh(void) const;
		double			       GetInitZ(void) const;
		std::vector<TTrajPoint>GetTraj(void) const;
		std::vector<double>	   GetDirs(void) const;
		std::vector<bool>	   GetDirsDefault(void) const;
		std::vector<double>	   GetDelays(void) const;
		std::vector<float>	   GetDiGuyActionTime(void) const;
		std::vector<char>	   GetDiGuyActionType(void) const;
		int                    GetColorIndex(void) const;
		EState			       GetInitialState(void) const;
		bool			       GetTrajIsGlobal(void) const;
		std::string		       GetCoupledName(void) const;
		CVector3D		       GetRelativeLocation(void) const;
		CVector3D		       GetRelativeOrientation(void) const;
		CVector3D		       GetInitVelocityXYZ(void) const;
		CVector3D		       GetInitVelocityRPY(void) const;
		int				       GetOption(void) const;
		bool			       GetUseInitVelocity(void) const;
		bool			       GetEnableAni(void) const;
		bool			       GetAccountAccel(void) const;
		double			       GetInitdDDOVelocity(void) const;
		double			       GetMaxAccel(void) const;
		double			       GetMaxDecel(void) const;

		// Mutator functions
		void			SetName(const std::string&);
		void			SetPosition(const CPoint3D&);
		void			SetCrRad(double);
		void			SetActvDel(double);
		void			SetLifetime(double);
		void			SetSolName(const std::string&);
		void			SetAudioState(int);
		void			SetVisualState(int);
		void			SetQuitAtEnd(int);
		void			SetDependent(int);
		void			SetRefPoint(int);
		void			SetDependentRefPoint(const CPoint3D&);
		void			SetDependentName(const std::string&);
		void			SetDependentOwnVeh(bool);
		void			SetInitZ(double);
		void			SetTraj(const std::vector<TTrajPoint>&);
		void			SetDirs(const std::vector<double>&);
		void			SetDirsDefault(const std::vector<bool>&);
		void			SetDelays(const std::vector<double>&);
		void            SetDiGuyActionTime(const std::vector<float>&);
		void            SetDiGuyActionType(const std::vector<char>&);
		void            SetColorIndex(int);
		void			SetInitialState(EState state);
		void			SetTrajIsGlobal(bool global);
		void			SetCoupledName(const std::string& name);
		void			SetRelativeLocation(double x, double y, double z);
		void			SetRelativeOrientation(double i, double j, double k);
		void			SetInitVelocityXYZ(double x, double y, double z);
		void			SetInitVelocityRPY(double i, double j, double k);
		void			SetOption(int);
		void			SetUseInitVelocity(bool);
		void			SetInitdDDOVelocity(double val);
		void			SetMaxAccel(double val);
		void			SetMaxDecel(double val);
		void			SetEnableAni(bool val);
		void			SetAccountAccel(bool);
};

#endif	// _DDO_PARSE_BLOCK_H

