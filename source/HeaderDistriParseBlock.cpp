#include "HeaderDistriParseBlock.h"
#include <assert.h>

class CDistriSimBlock : public CHeaderParseBlock
{
public:
	CDistriSimBlock(const CSnoBlock& blk) : CHeaderParseBlock(blk)
	{
	}
	std::string GetSimName()
	{
		CSnoValue v;
		bool r = GetField("Name", v);
		assert(r);
		return v.GetStringValue();
	}
	std::string GetIPV4()
	{
		CSnoValue v;
		bool r = GetField("IPV4", v);
		assert(r);
		return v.GetStringValue();
	}
	std::string GetIPMask()
	{
		CSnoValue v;
		bool r = GetField("IPMask", v);
		assert(r);
		return v.GetStringValue();
	}

	int GetType()
	{
		CSnoValue v;
		bool r = GetField("Type", v);
		assert(r);
		return v.GetIntValue();
	}
};


CHeaderDistriParseBlock::CHeaderDistriParseBlock(const CSnoBlock &blk)
	: CHeaderParseBlock(blk)
	, m_selfBlkIdx(0)
	, m_travBlkIdx(-1)
{

}

CHeaderDistriParseBlock::~CHeaderDistriParseBlock()
{

}

bool CHeaderDistriParseBlock::NextExternalBlk()
{
	static int s_lockedSelfBlkIdx = 0;
	if (m_travBlkIdx == -1)
	{
		s_lockedSelfBlkIdx = m_selfBlkIdx;
		//lock self block index when start traversing due to the self one might change during tranversing
		m_travBlkIdx = s_lockedSelfBlkIdx + 1;
		m_travBlkIdx = m_travBlkIdx % GetChildCount();
	}
	else
	{
		m_travBlkIdx ++;
		m_travBlkIdx = m_travBlkIdx % GetChildCount();
		if (m_travBlkIdx == s_lockedSelfBlkIdx)
			m_travBlkIdx = -1;
	}
	return m_travBlkIdx != -1;
}

int CHeaderDistriParseBlock::GetPort()
{
	CSnoValue v;
	bool r = GetField("Port", v);
	assert(r);
	return v.GetIntValue();
}

std::string CHeaderDistriParseBlock::GetMCIP() const
{
	CSnoValue v;
	bool r = GetField("MCIP", v);
	assert(r);
	return v.GetStringValue();
}


void CHeaderDistriParseBlock::TagLocalhost()
{
	if (m_travBlkIdx == -1) //taged without calling Next...
		m_selfBlkIdx = 0;
	else
		m_selfBlkIdx = m_travBlkIdx;
}

#define CHILD_BLKRUN(func)\
	int idx = (-1 != m_travBlkIdx) ? m_travBlkIdx : m_selfBlkIdx;\
	assert(GetChildCount() > idx);\
	CDistriSimBlock blk(GetChild(idx));\
	return blk.func

CPoint3D CHeaderDistriParseBlock::GetOwnVehPos(void) const
{
	CHILD_BLKRUN(GetOwnVehPos());
}

CVector3D	CHeaderDistriParseBlock::GetOwnVehOri(void) const
{
	CHILD_BLKRUN(GetOwnVehOri());
}

double		CHeaderDistriParseBlock::GetScenPosX(void) const
{
	CHILD_BLKRUN(GetScenPosX());
}

double		CHeaderDistriParseBlock::GetScenPosY(void) const
{
	CHILD_BLKRUN(GetScenPosY());
}

double		CHeaderDistriParseBlock::GetScenZoom(void) const
{
	CHILD_BLKRUN(GetScenZoom());
}

std::string CHeaderDistriParseBlock::GetIPV4(void) const
{
	CHILD_BLKRUN(GetIPV4());
}

std::string CHeaderDistriParseBlock::GetIPMask(void) const
{
	CHILD_BLKRUN(GetIPMask());
}

std::string	CHeaderDistriParseBlock::GetSimName(void) const
{
	CHILD_BLKRUN(GetSimName());
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetSolName
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A string value for the SolName field.
//
//////////////////////////////////////////////////////////////////////////////
string
CHeaderDistriParseBlock::GetSolName(void) const
{
	CHILD_BLKRUN(GetCabSolObjName());
} // end of GetSolName

int CHeaderDistriParseBlock::GetType(void) const
{
	CHILD_BLKRUN(GetType());
}

#undef CHILD_BLKRUN

bool		CHeaderDistriParseBlock::HasOwnVeh(void) const
{
	return GetChildCount() > 0;
}

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetAudioState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the AudioState field.
//
//////////////////////////////////////////////////////////////////////////////
int
CHeaderDistriParseBlock::GetAudioState(void) const
{
	const int   cAUDIOSTATE = 0;
	CSnoValue val;
	if (GetField("AudioState", val))
		return val.GetIntValue();
	else
		 return cAUDIOSTATE;
} // end of GetAudioState

//////////////////////////////////////////////////////////////////////////////
//
// Description: GetVisualState
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the VisualState field.
//
//////////////////////////////////////////////////////////////////////////////
int
CHeaderDistriParseBlock::GetVisualState(void) const
{
	const int   cVISUALSTATE = 0;
	CSnoValue val;
	if (GetField("VisualState", val))
		return val.GetIntValue();
	else
		 return cVISUALSTATE;
} // end of GetVisualState





//////////////////////////////////////////////////////////////////////////////
//
// Description: GetColorIndex
//	DESCRIPTION
//
// Remarks:
//
// Arguments:
//
// Returns: A int value for the ColorIndex field.
//
//////////////////////////////////////////////////////////////////////////////
int
CHeaderDistriParseBlock::GetColorIndex(void) const
{
	const int    cCOLORINDEX = 0;
	CSnoValue val;
	if (GetField("ColorIndex", val))
		return val.GetIntValue();
	else
		return cCOLORINDEX;
} // end of GetColorIn