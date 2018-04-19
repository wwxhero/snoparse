//////////////////////////////////////////////////////////////////////////////
#pragma once

#include "hcsmspec.h"

//////////////////////////////////////////////////////////////////////////////
//
// This class represents the Visual Object block.  It provides custom
// access functions fo accsessing the data associated with this block.
//
//////////////////////////////////////////////////////////////////////////////
class CVirtualObjectParseBlock : public CSnoBlock {
	public:

		// Types
		// This structure holds a single point of the trajectory and the value for
		// tangent of the spline at the control point.  Note
		// that only the x,y coordinates are specified along with a desired
		// velocity at each point.  Combined with the initial value of the
		// z coordinate (accessed through InitZ()), a deterministic dynamic object
		// can derive the necessary elevation at runtime.
		typedef struct TTStatePoint {
			float colorFill [4] ;// RGBA
			float colorBorder[4]; // RGBA
			float frameLength;		// desired velocity at the point
			float scale[3];		// x value fot the tangent vector
			char  IconName[128];		// y value fot the tangent vector
			int   type;
			int   group;
		} TStatePoint;

		enum EScreen{
			eMainScreen = 1,
			eInstPanel = 2,
			eInvalid = -1
		};
		// Constructors, destructor, and assignment operator
		CVirtualObjectParseBlock();
		CVirtualObjectParseBlock(const CVirtualObjectParseBlock&);
		CVirtualObjectParseBlock(const CSnoBlock&);
		~CVirtualObjectParseBlock();
		CVirtualObjectParseBlock& operator=(const CVirtualObjectParseBlock&);
		CPoint3D GetPosition(void) const;
		void SetPosition(const CPoint3D& position);

		CPoint3D GetDrawPosition(void) const;
		void SetDrawPosition(const CPoint3D& position); 

		CPoint2D GetDrawScale(void) const;
		void SetDrawScale(const CPoint2D& size);  
		
		std::string GetSolName(void) const;
		void SetSolName(const std::string& solName);

		std::string GetIconName(void) const;
		void SetIconName(const std::string& solName);

		int GetOption(void) const;
		void SetOption(int option);
		void SetOrientation(double);
		double GetOrientation() const;
		int GetColorIndex(void) const;
		void SetColorIndex(int color);

		std::string GetName(void) const;
		void SetName(const std::string& name);

		std::string GetTargetName(void) const;
		void SetTargetName(const std::string& name);

		void SetIsBlinking(bool);
		bool GetIsBlinking()const;

		float GetBlinkOnDurr() const;
		void SetBlinkOnDurr(float);

		void SetBlinkOffDurr(float);
		float GetBlinkOffDurr() const;

		void SetColor(float r, float g, float b, float a);
		void GetColor(float &r, float &g, float &b, float &a)const;


		void SetBoarderColor(float r, float g, float b, float a);
		void GetBoarderColor(float &r, float &g, float &b, float &a)const;

		void SetType(short type);
		short GetType() const;


		double	GetCrRad(void) const;
		double	GetActvDel(void) const;
		double	GetLifetime(void) const;

		void	SetCrRad(double);
		void	SetActvDel(double);
		void	SetLifetime(double);
		void	SetStateMatrix(const std::vector<TStatePoint> &states);
		void	GetStateMatrix(std::vector<TStatePoint> &states) const;

		void    SetScreen(EScreen val);
		EScreen GetScreen(void) const;

		void    SetPreCreateId(int val);
		int     GetPreCreateId(void) const;

		static EScreen IntToScreen(int);
};