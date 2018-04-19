#ifndef _SNOPARSERDISTRI_H
#define _SNOPARSERDISTRI_H
#pragma once
#include "snoparse.h"
#include "headerparseblock.h"
class CSnoParserDistri :
	public CSnoParser
{
public:
	CSnoParserDistri(void);
	virtual ~CSnoParserDistri(void);
	bool Init();
};
#endif

