#pragma once
#include <sys/stat.h>
#include "string"
using namespace std;
class NewTime
{
public:
	NewTime(void);
	~NewTime(void);
	CString NewTime::newTime(CString filePath);
	float NewTime::sizefile(CString filePath);
};

