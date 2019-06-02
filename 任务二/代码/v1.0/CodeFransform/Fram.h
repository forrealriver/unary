
// Fram.h : ͷ�ļ�
//

#pragma once
#include "Browse.h"
#include "Log.h"
#include "TreadOperate.h"
// Fram �Ի���
class Fram : public CDialog
{
// ����
public:
	Fram(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CODEFRANSFORM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedStop();

	CEdit cc_sEdit;
	CEdit cc_dEdit;
	CWnd cc_okbnclick;
	CStatic cc_static;
	CWnd cc_killbnclick;
	CComboBox cc_sComboBox;
	CComboBox cc_dComboBox;
	CStatic cc_staticSpeed;
	CProgressCtrl cc_process;
	CButton cc_unicodeToUtf8;
	CButton cc_uft8ToUnicode;
	
	CString sFildPath;
	CString dFildPath;
	CString sCode;
	CString dCode;

	Log log;
	int m_flage;
	int m_okclick;
	DWORD m_count;
	Browse browse;
	TreadOperate treadOperate;
};
