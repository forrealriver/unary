#pragma once
#include "tinyxml.h"
class XmlRead
{
public:
	XmlRead();
	~XmlRead();
	int XmlRead::Read(char * xmlpath, CStringArray &filternames);
	void XmlRead::dumpNode(TiXmlNode* pNode, int flag, CStringArray &filternames);
	void XmlRead::ConvertUtf8ToGbk(char* &szOut);
	CString XmlRead::GetWorkDir();
	void XmlRead::setLastError(CString lastErrInfo);
	CString XmlRead::getLastError();

	CString lastError;
};

