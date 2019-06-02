#include "stdafx.h"
#include "XmlRead.h"
#include "tinyxml.h"
#include <Windows.h>
#pragma warning(disable:4996)
XmlRead::XmlRead()
{
}


XmlRead::~XmlRead()
{
}
int XmlRead::Read( char * xmlpath,CString * filternames,int * num) {
	num[0] = 0;
	TiXmlDocument *myDocument = new TiXmlDocument();
	if (!myDocument->LoadFile(xmlpath, TIXML_ENCODING_UTF8)) {
		//TRACE("--***%s***---",myDocument->ErrorDesc());
		AfxMessageBox(_T("XML�ļ���ʧ�ܣ�"));
		return 0;
	}
	TiXmlDeclaration *decl = myDocument->FirstChild()->ToDeclaration();
	TRACE("%s--%s\n", decl->Version(), decl->Encoding());
	TiXmlElement *rootElement = myDocument->RootElement();
	TiXmlAttribute *attributeOfRoot = rootElement->FirstAttribute();
	while (attributeOfRoot != NULL)
	{
		//TRACE("%s--%s\n", attributeOfRoot->Name(), attributeOfRoot->Value());
		attributeOfRoot = attributeOfRoot->Next();
	}
	TiXmlNode *pNode = NULL;
	for (pNode = rootElement->FirstChildElement(); pNode != NULL; pNode = pNode->NextSiblingElement())
	{
		dumpNode(pNode, 0, filternames,num);
	}

	delete myDocument;
	myDocument = NULL;
	return 1;
}
void XmlRead::ConvertUtf8ToGbk(char* &szOut)
{
	unsigned short* wszGbk = NULL;
	char* szGbk = NULL;

	int len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, NULL, 0);
	wszGbk = new unsigned short[len + 1];
	memset(wszGbk, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)szOut, -1, (LPWSTR)wszGbk, len);

	len = WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGbk, -1, NULL, 0, NULL, NULL);
	szGbk = new char[len + 1];
	memset(szGbk, 0, len + 1);
	WideCharToMultiByte(CP_ACP, 0, (LPWSTR)wszGbk, -1, szGbk, len, NULL, NULL);

	memset(szOut, '\0', strlen(szGbk) + 1);
	memcpy(szOut, szGbk, strlen(szGbk));

	delete[]szGbk;
	szGbk = NULL;
	delete[]wszGbk;
	wszGbk = NULL;
}
void XmlRead::dumpNode(TiXmlNode* pNode, int flag, CString * filternames,int * num)
{
	if (pNode == NULL)
		return;
	TiXmlText *pText = NULL;
	TiXmlNode *pChildNode = NULL;
	int t = pNode->Type();
	if (t == TiXmlText::TEXT)
	{
		pText = pNode->ToText();
		//TRACE("1--%s\n", pText->Value());

		char *text;
		text = new char[strlen(pText->Value()) + 1];
		strcpy(text, pText->Value());
		ConvertUtf8ToGbk(text);

		TRACE("un--%s\n", text);
		filternames[num[0]] = text;
		num[0]++;
		delete[] text;
		text = NULL;

	}
	else if (t == TiXmlText::ELEMENT)
	{
		//TRACE("%s--", pNode->Value());
		TiXmlElement* pElement = pNode->ToElement();
		TiXmlAttribute* pAttr = pElement->FirstAttribute();
		
	}
	for (pChildNode = pNode->FirstChild(); pChildNode != NULL; pChildNode = pChildNode->NextSibling())
	{
		//TRACE("flag---%d\n", flag);
		dumpNode(pChildNode, flag + 1, filternames,num);
	}
	
}

CString XmlRead::GetWorkDir()   
{    
	HMODULE module = GetModuleHandle(0);   
	TCHAR pFileName[MAX_PATH];   
	GetModuleFileName(module, pFileName, MAX_PATH);   
	CString csFullPath(pFileName);   
	int nPos = csFullPath.ReverseFind( _T('\\') );   
	if( nPos < 0 )   
		 return CString("");   
	else   
		return csFullPath.Left( nPos );     
}  