#pragma once
#ifndef _HEADERDISTRIPARSEBLOCK_H
#define _HEADERDISTRIPARSEBLOCK_H
#include "hcsmspec.h"
#include "point3d.h"
#include "vector3d.h"
#include "HeaderParseBlock.h"
class CHeaderDistriParseBlock : public CHeaderParseBlock
{
public:
	CHeaderDistriParseBlock(const CSnoBlock &);
	virtual ~CHeaderDistriParseBlock();
	int GetPort();
	void TagLocalhost();
	std::string			GetIPV4(void) const;
	std::string			GetIPMask(void) const;
	std::string			GetSimName(void) const;
	std::string			GetSolName(void) const;
	int					GetColorIndex(void) const;
	int					GetAudioState(void) const;
	int					GetVisualState(void) const;
	int					GetType(void) const;

	virtual CPoint3D	GetOwnVehPos(void) const;
	virtual CVector3D	GetOwnVehOri(void) const;
	virtual double		GetScenPosX(void) const;
	virtual double		GetScenPosY(void) const;
	virtual double		GetScenZoom(void) const;
	virtual bool		HasOwnVeh(void) const;
	virtual bool		NextExternalBlk();
private:
	int m_selfBlkIdx;
	int m_travBlkIdx;
};
#endif
