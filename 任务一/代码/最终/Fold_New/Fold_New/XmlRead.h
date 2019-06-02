#pragma once
#include "tinyxml.h"
class XmlRead
{
public:
	XmlRead();
	~XmlRead();
	int XmlRead::Read(char * xmlpath, CStringArray * filternames, int * num);
	void XmlRead::dumpNode(TiXmlNode* pNode, int flag, CStringArray * filternames, int * num);
	void XmlRead::ConvertUtf8ToGbk(char* &szOut);
	CString XmlRead::GetWorkDir();
};

