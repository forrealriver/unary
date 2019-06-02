#pragma once
#include "tinyxml.h"
class XmlRead
{
public:
	XmlRead();
	~XmlRead();
	int XmlRead::Read(char * xmlpath, CString * filternames, int * num);
	void XmlRead::dumpNode(TiXmlNode* pNode, int flag, CString * filternames, int * num);
	void XmlRead::ConvertUtf8ToGbk(char* &szOut);
	CString XmlRead::GetWorkDir();
};

