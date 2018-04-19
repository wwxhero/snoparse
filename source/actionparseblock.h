//////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) NADS & Simulation Center, The University of Iowa and
// The University of Iowa.  All rights reserved.
//
// Author:	 Yiannis Papelis
// Date:	 February, 2000
//
// $Id: actionparseblock.h,v 1.45 2017/05/03 17:14:07 IOWA\dheitbri Exp $
//
// The interface for the action parser class.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef _ACTION_PARSE_BLOCK_H
#define _ACTION_PARSE_BLOCK_H		// {secret}

#include "hcsmspec.h"

// alert conditions
const int cAC_CHARGING_SYSTEM	= 1;
const int cAC_SERVICE_ENGINE	= 2;
const int cAC_AIRBAG			= 4;
const int cAC_LEFT_TURN_SIGNAL	= 8;
const int cAC_RIGHT_TURN_SIGNAL	= 16;
const int cAC_OIL_PRESSURE		= 32;
const int cAC_ENGINE_OVERHEATING= 64;

// cab component
const int cCC_RADIO				= 1;
const int cCC_AIR_CONDITIONER	= 2;
const int cCC_POWER_MIRRORS		= 4;
const int cCC_POWER_SEATS		= 8;
const int cCC_ENTERTAINMENT		= 16;


// Data Reduction
const int cDR_REACTION_TIME			= 1;
const int cDR_INSTANT_EXTRACT		= 2;
const int cDR_SIMPLE_STATS			= 4;

const int cDR_COLSIZE = 8;
const int cDR_DATASIZE = 60;


//////////////////////////////////////////////////////////////////////////////
///\brief
///    Parse block for actions
///\remark
/// This class represents the action block.  It provides custom
/// access functions fo accsessing the data associated with this block.
///\remark
//// All actions use the same parse block, the meaning of some values
///  may change per action type.
//////////////////////////////////////////////////////////////////////////////
class CActionParseBlock : public CSnoBlock {
	public:
		// Constructors, destructor, and assignment operator
		CActionParseBlock();
		CActionParseBlock(const CActionParseBlock&);
		CActionParseBlock(const CSnoBlock&);
		~CActionParseBlock();
		CActionParseBlock& operator=(const CActionParseBlock&);

		// Types
		// This type is used to represent a dial name and value
		typedef struct pbTDial {
			std::string name;
			std::string value;
			pbTDial() { name = ""; value = ""; };
		} pbTDial;

		typedef struct pbTMotionPreposition {
			double crossbeam;
			double carriage;
			double hexX;
			double hexY;
			double hexZ;
			double hexRoll;
			double hexPitch;
			double hexYaw;
			double turntable;
		} pbTMotionPreposition;

		struct pbTDataRedVar {
			int type;
			char data[cDR_COLSIZE + cDR_DATASIZE];

			pbTDataRedVar() {
				type = -1;
				memset(data, 0, cDR_COLSIZE + cDR_DATASIZE);
			}
		};

		enum EFailureType {
			eTIRE = 1,
			eBRAKE = 2,
			eSHOCKS = 3,
			eSTEERING = 4,
			eALERT = 5,
			eINFORMATIONAL = 6,
			eCAB_COMPONENT = 7
		};

		enum EBrakeFailureType {
			eBFT_POWER_ASSIST				= 1,
			eBFT_ABS						= 2,
			eBFT_FULL_MASTER_CYLINDER		= 3,
			eBFT_PARTIAL_MASTER_CYLINDER	= 4,
			eBFT_LOW_FLUID					= 5,
			eBFT_WORN_PADS					= 6
		};

		enum ETireFailure {
			eTF_NORMAL     = 1,
			eTF_GOING_FLAT = 2,
			eTF_DETREAD	   = 3
		};

		enum EBrakeCond {
			eBC_NORMAL		= 1,
			eBC_PARTIAL		= 2,
			eBC_FULL		= 3
		};

		enum ESteeringFailure {
			ePOWERASSIST = 1
		};

		enum EInformationalCond {
			eSPEEDOMETER = 1,
			eTACHOMETER  = 2
		};

		typedef union TFailureUnion {
			struct TireCond {
				int type[10];
				int time[10];
			} TireCond;

			struct BrakeCond {
				int type[11];
			} BrakeCond;

			struct Steering {
				int type;
			} Steering;

			struct Alert {
				int type;
			} Alert;

			struct Information {
				int type;
				int multiplier;
			} Information;

			struct CabComponent {
				int type;
			} CabComponent;
		} TFailureUnion;

		typedef struct pbTFailure {
			EFailureType type;
			TFailureUnion info;
		} pbTFailure;

		struct TRelativeInfo {
			bool			m_isDriver;
			std::string			m_objName;
			int				m_numObjs;
			std::vector<std::string>	m_params;
			TRelativeInfo() { m_isDriver = true; m_numObjs = 0;	}
		};

		struct TRelativeStates{
			std::vector<std::string> m_AllStates;
		};
		// Write Cell action
		enum ECellDataType {
			eFLOAT = 0,
			eSHORT = 1,
			eINT   = 2,
			eSTRING= 3,
            eNOTSET =4
		};

        struct TSwitchInfo {
            TSwitchInfo(){
                value = 0;
            }
            std::string switchName;
            int value;
        };
		// Accessor functions
		std::vector<std::string>	GetByNameSet(void) const;
		std::vector<std::string>	GetByTypeSet(void) const;
		std::vector<pbTRoad>	    GetByRoadSet(void) const;
		std::vector<pbTPstn>        GetByPstnSet(void) const;
		TRelativeInfo	            GetRelativeSet(void) const;
		TRelativeStates				GetRelativeStates(void) const;
		int			                GetInstigatorSet(void) const;
		double		                GetTime(void) const;
		std::string	                GetState(void) const;
		std::string	                GetFailure(void) const;
		std::string	                GetButton(void) const;
		pbTDial		                GetDial(void) const;
		std::string	                GetButtonDialPath(void) const;
		std::string	                GetAudio(void) const;
		std::string	                GetFile(void) const;
		int			                GetStream(void) const;
		double		                GetStreamValue(void) const;
		std::string	                GetComment(void) const;
		std::string	                GetTrafManSet(void) const;
		std::string	                GetMotionPreposition(void) const;
		double		                GetDelay(void) const; 
		std::vector<pbTDataRedVar>  GetDataRedVars(void) const;
		std::string		            GetDataRedVarsStr(void) const;
		std::string			        GetVarName(void) const;
		std::string			        GetVarValue(void) const;
        std::string                 GetVarQueueOperation(void) const;
		bool			            GetIsVarValExpression(void) const;
		std::string			        GetCellName(void) const;
		std::string                 GetUniformName(void) const;
		std::string                 GetShaderName(void) const;
		std::string                 GetShaderOption(void) const;
        TSwitchInfo                 GetSwitch(void) const;
		ECellDataType	            GetCellType(void) const;
		std::vector<int>	        GetCellDataInt(void) const;
		std::vector<float>          GetCellDataFloat(void) const;
		std::vector<short>          GetCellDataShort(void) const;
		std::string			        GetCellDataString(void) const;
		bool                        IsCellTypeVariable(void) const;
		std::string			        GetVisualDisplayLocation(void)const;
		std::string			        GetVisualDisplayValue(void)const;
		std::string			        GetScreenPosition(void) const;
		std::string                 GetCabSettingsString(void) const;
		int                         GetHeadlightControlCommand(void) const;
		std::string			        GetGraphString(void) const;
		std::vector<long>           GetSeed(void) const;
        std::string			        GetSetTimeOfDayStr() const; 
        std::string			        GetCommand() const;
        int                         GetTargetID() const;
		// Mutator functions
		void			SetGraphString(const std::string& graphString);
		void			SetByNameSet(const std::vector<std::string>&);
		void			SetByTypeSet(const std::vector<std::string>&);
		void			SetByRoadSet(const std::vector<pbTRoad>&);
		void			SetByPstnSet(const std::vector<pbTPstn>&);
		void			SetRelativeSet(const TRelativeInfo&);
		void			SetRelativeStates(const TRelativeStates&);
		void			SetInstigatorSet(int);
		void			SetTime(double);
		void			SetState(const std::string&);
		void			SetFailure(const std::string&);
		void			SetButton(const std::string&);
		void			SetDial(const pbTDial&);
		void			SetButtonDialPath(const std::string&);
		void			SetAudio(const std::string&);
		void			SetFile(const std::string&);
		void			SetStream(int);
		void			SetStreamValue(double);
		void			SetComment(const std::string&);
		void			SetTrafManSet(const std::string&);
		void			SetMotionPreposition(const std::string&);
		void			SetDelay(double);
		void			SetDataRedVars(const std::string&);
		void			SetVarName(const std::string&);
		void			SetVarValue(const std::string&);
        void            SetVarQueueOperation(const std::string&);
		void			SetIsVarValExpression(bool);
		void			SetCellName(const std::string&);
		void			SetCellType(ECellDataType);
		void            SetUniformName(const std::string&);
		void            SetShaderName(const std::string&);
		void            SetShaderOption(const std::string&);
		void            SetSwitch(const TSwitchInfo&);
		void			SetCellDataInt(const std::vector<int>&);
		void			SetCellDataFloat(const std::vector<float>&);
		void			SetCellDataShort(const std::vector<short>&);
		void			SetCellDataString(const std::string&);
		void            SetIsCellTypeVariable(bool);
		void			SetVisualDisplayLocation(const std::string&);
		void			SetVisualDisplayValue(const std::string&);
		void			SetScreenPosition(const std::string&);
		void            SetCabSettingsString(const std::string&);
		void            SetHeadlightControlCommand(int);
		void            SetSeed(const std::vector<long>&);
		void            SetSetTimeOfDayStr(const std::string& val);
        void		    SetCommand(const std::string&);
        void            SetTargetID(int id);
		// static functions
		static CActionParseBlock::pbTFailure StringToFailure( const std::string& );
		static std::string FailureToString( const CActionParseBlock::pbTFailure& );
		static int StringToFlags( const std::string&, unsigned int* pFlags );
		static CActionParseBlock::pbTMotionPreposition StringToPreposition( const std::string& );
		static std::string PrepositionToString( const CActionParseBlock::pbTMotionPreposition& );
		static std::vector<pbTDataRedVar> StringToDataRedVars(const std::string& str);
};

#endif	// _ACTION_PARSE_BLOCK_H

