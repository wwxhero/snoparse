//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:   Yiannis Papelis
// Date:     January, 1999
//
// $Id: headerparseblock.h,v 1.38 2018/03/22 22:14:05 IOWA\dheitbri Exp $
//
// The interface for the header parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _HEADER_PARSE_BLOCK_H
#define _HEADER_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"
#include "point3d.h"
#include "vector3d.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the header block.  It provides custom
// access functions for accessing the header data.
//
class CHeaderParseBlock : public CSnoBlock {
	public:
		struct TMotionPosition {
			double m_crossbeamX;
			double m_carriageY;
			double m_hexX;
			double m_hexY;
			double m_hexZ;
			double m_hexRoll;
			double m_hexPitch;
			double m_hexYaw;
			double m_turntable;
			TMotionPosition() {
				m_crossbeamX = m_carriageY = m_hexX = m_hexY = m_hexZ = m_hexRoll =
					m_hexPitch = m_hexYaw = m_turntable = 0.0;
			}
		};
		struct TCoordSave {
			bool  m_used;
			double m_x;
			double m_y;
			double m_z;
			double m_zoom;
			TCoordSave() {
				m_used = false;
				m_x = m_y = m_z = m_zoom = 0.0f;
			}
		};

		struct TExtRef {
			std::string m_fileName;
			std::string m_groupName;
		};
        enum ECrashEffects{
            eCAB_SHAKE = 1,
            eCRACK_WINDSHIELD =2
        };
		// Constructors, destructor, and assignment operator
		CHeaderParseBlock();
		CHeaderParseBlock(const CHeaderParseBlock &);
		CHeaderParseBlock(const CSnoBlock &);
		~CHeaderParseBlock();
		CHeaderParseBlock &operator=(const CHeaderParseBlock &);

		// Accessor functions
		std::string		GetDate(void) const;
		std::string		GetShortComment(void) const;
		std::string		GetLongComment(void) const;
		std::string		GetLriFile(void) const;
		std::string		GetCabSolObjName(void) const;
		bool		GetShowCab(void) const;
		std::string		GetTrailerSolObjName(void) const;
		virtual CPoint3D	GetOwnVehPos(void) const;
		virtual CVector3D	GetOwnVehOri(void) const;
		std::string		GetMotionDriveFilename(void) const;
		std::string		GetMotionSettingsFilename(void) const;
		std::string		GetCollisionSimulation(void) const;
		std::string		GetDaqFile(void) const;
		TMotionPosition	GetMotionScenarioPosition(void) const;
		std::vector<int> GetInitialTireConditions(void) const;
		std::vector<int> GetInitialBrakeConditions(void) const;
		virtual double		GetScenPosX(void) const;
		virtual double		GetScenPosY(void) const;
		virtual double		GetScenZoom(void) const;
		std::string		GetBliPath(void) const;
		std::vector<std::string>	GetPath(void) const;
		std::vector<std::string>	GetTextObjs(void) const;
		std::vector<std::string>	GetPreloadFiles(void) const;
		virtual bool		HasOwnVeh(void) const;
		std::vector<double>	GetVibrationSpec(void) const;
		std::vector<TCoordSave>	GetSavedCoords(void) const;
		std::vector<TExtRef>		GetExtRefs(void) const;
		std::string		GetOtherTerrain(void) const;
		std::string		GetVisualSettings(void) const;
		std::vector<std::string> GetReadCellNames(void) const;
		std::vector<std::string> GetWriteCellNames(void) const;
		bool           GetBlanking(void) const;
		bool        GetHeadlightsOn(void) const;
		double      GetHeadlightsAzimuth(void) const;
		double      GetHeadlightsElevation(void) const;
		double      GetHeadlightsBeamWidth(void) const;
		double      GetHeadlightsBeamHeight(void) const;
		double      GetHeadlightsConstCoeff(void) const;
		double      GetHeadlightsLinearCoeff(void) const;
		double      GetHeadlightsQuadCoeff(void) const;
		double      GetHeadlightsHeightFade(void) const;
		double		GetHeadlightsCutOffDist(void) const;
		double      GetHeadlightsIntensity(void) const;
		double      GetAmbientLightInt(void) const;
		double      GetHeadlightLampSeparation(void) const;
		double      GetHeadlightForwardOffset(void) const;
		int			GetEnvMonth(void) const;
		int			GetEnvDay(void) const;
		int			GetEnvHour(void) const;
		int			GetEnvMinute(void) const;
		float		GetEnvLong(void) const;
		float		GetEnvLat(void) const;
		int			GetEnvYear(void) const;
		float		GetEnvAlt(void) const;
		void		GetBlankColor(float &r,float &g, float &b);
		bool		GetSirenOverSpeed() const;
		float		GetSirenSpeed() const;
		int		    GetCollisionEffectMask() const;



		// Mutator functions
		void 	SetDate(const std::string&);
		void 	SetShortComment(const std::string&);
		void 	SetLongComment(const std::string&);
		void	SetLriFile(const std::string&);
		void	SetCabSolObjName(const std::string&);
		void    SetShowCab(bool);
		void	SetTrailerSolObjName(const std::string&);
		void	SetOwnVehPos(const CPoint3D&);
		void	SetOwnVehOri(const CVector3D&);
		void	SetMotionDriveFilename(const std::string&);
		void	SetMotionSettingsFilename(const std::string&);
		void	SetMotionScenarioPosition(const TMotionPosition&);
		void	SetCollisionSimulation(const std::string& method);
		void	SetDaqFile(const std::string&);
		void	SetInitialTireConditions(const std::vector<int>& cond);
		void	SetInitialBrakeConditions(const std::vector<int>& cond);
		void	SetScenPosX(double);
		void	SetScenPosY(double);
		void	SetScenZoom(double);
		void	SetBliPath(const std::string&);
		void	SetPath(const std::vector<std::string>&);
		void	SetTextObjs(const std::vector<std::string>&);
		void    SetPreloadFiles(const std::vector<std::string>&);
		void	RemoveOwnVeh();
		void	SetVibrationSpec( const std::vector<double>& );
		void	SetSavedCoords( const std::vector<TCoordSave>& );
		void	SetExtRefs(const std::vector<TExtRef>& );
		void	SetOtherTerrain(const std::string&);
		void    SetVisualSettings(const std::string&);
		virtual void	SetIsExtRef(bool extRef);
		void    SetReadCellNames(const std::vector<std::string>&);
		void    SetWriteCellNames(const std::vector<std::string>&);
		void    SetBlanking(bool blanking);
		void    SetHeadlightsOn(bool);
		void    SetHeadlightsAzimuth(double);
		void    SetHeadlightsElevation(double);
		void    SetHeadlightsBeamWidth(double);
		void    SetHeadlightsBeamHeight(double);
		void    SetHeadlightsConstCoeff(double);
		void    SetHeadlightsLinearCoeff(double);
		void    SetHeadlightsQuadCoeff(double);
		void    SetHeadlightsHeightFade(double);
		void    SetHeadlightsIntensity(double);
		void    SetAmbientLightInt(double val);
		void    SetHeadlightsCutOffDist(double val);
		void    SetHeadlightLampSeparation(double val);
		void    SetHeadlightForwardOffset(double val);

		void	SetEnvMonth(int);
		void	SetEnvDay(int);
		void	SetEnvHour(int);
		void	SetEnvMinute(int);
		void	SetEnvLong(float);
		void	SetEnvLat(float);
		void	SetEnvYear(int);
		void	SetEnvAlt(float);
		void	SetBlankColor(float r,float g, float b);
		void	SetSirenOverSpeed(bool SirenOn);
		void	SetSirenSpeed(float val);
		void	SetCollisionEffectMask(int CollEffect);
		virtual bool NextExternalBlk();


};

#endif	// _HEADER_PARSE_BLOCK_H

