#pragma once

class TransformOperate
{
public:
	TransformOperate(void);
	~TransformOperate(void);
	void TransformOperate::SetLastError(CString lastErrInfo);
	CString TransformOperate::GetLastError(void);
	virtual DWORD TransformOperate:: TransformCode(byte *unicode,byte *utf8,DWORD readLineSize)=0;
	CString m_LastError;
};
