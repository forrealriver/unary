#pragma once

class TransformOperate
{
public:
	TransformOperate(void);
	~TransformOperate(void);
	void TransformOperate::SetLastError(CString lastErrInfo);
	CString TransformOperate::GetLastError(void);
	virtual long TransformOperate:: TransformCode(byte *unicode,byte *utf8,long readLineSize)=0;
	CString m_LastError;
};
