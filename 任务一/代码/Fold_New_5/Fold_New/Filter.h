#pragma once

class Filter
{
public:
	Filter(void);
	~Filter(void);
	int Filter::filter(CString* fileNames, int fileNum, CString* filterNames, int filterNum);
};
