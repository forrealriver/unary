#pragma once
#include "Find.h"
class TreadOperate
{
public:
	TreadOperate(void);
	~TreadOperate(void);
	bool TreadOperate::creadTread(CString sfilepath,CString dfilepath);
	void TreadOperate::killTread(void);
	Find *m_find;
};
