#include <list>
#include <assert.h>
#include "hcsmspec.h"
#include "SnoParserDistri.h"
#include "TestExp.h"
#include <Windows.h>
CSnoParserDistri::CSnoParserDistri(void)
{
}


CSnoParserDistri::~CSnoParserDistri(void)
{
}

bool CSnoParserDistri::Init()
{
	int len = 1024;
	char* dir = (char*)malloc(len * sizeof(char));
	bool done = false;
	do
	{
		int expl = GetModuleFileNameA(NULL, dir, len);
		done = (expl <= len); //expl + 1 <= len
		if (!done)
		{
			len = expl + 1;
			dir = (char*)realloc(dir, len * sizeof(char));
		}
		else
		{
			len = expl;
			dir[len] = '\0';
		}
	}while(!done);
	assert(len > 1);
	while(len > 0
		&& dir[len] != '\\')
	{
		len --;
	}
	dir[len + 1] = '\0';
	std::string path(dir);
	free(dir);
	path += "mockDistriConf.scn";
	return CSnoParser::ParseFile(path);
}


