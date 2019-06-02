
// Fold_NewDlg.h : ͷ�ļ�
//

#pragma once
#include "Frame.h"
#include "Find.h"
#include "Filter.h"
#include "XmlRead.h"
#include "Compare.h"
#include "Copy.h"
#include "Log.h"
// CFold_NewDlg �Ի���
class CFold_NewDlg : public CDialog
{
// ����
public:
	CFold_NewDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FOLD_NEW_DIALOG };
public:
	void CFold_NewDlg::ShowItem();
	void CFold_NewDlg::HideItem();
	void CFold_NewDlg::ResultWarn(int resultwarning1,int resultwarning2);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedCancel();
};
