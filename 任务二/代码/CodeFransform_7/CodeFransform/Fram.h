
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

	CComboBox cc_sComboBox;
	CComboBox cc_dComboBox;
	CProgressCtrl cc_process;
	CStatic cc_static;
	CEdit cc_sEdit;
	CEdit cc_dEdit;
	
	CString sFildPath;
	CString dFildPath;
	CString sCode;
	CString dCode;

	Browse browse;
	Log log;
	TreadOperate treadOperate;
	
	afx_msg void OnBnClickedStop();
};
