
// Fram.h : 头文件
//

#pragma once
#include "Browse.h"
#include "Log.h"
#include "TreadOperate.h"
// Fram 对话框
class Fram : public CDialog
{
// 构造
public:
	Fram(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CODEFRANSFORM_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
	
	CString m_sFildPath;
	CString m_dFildPath;
	CString m_sCode;
	CString m_dCode;

	Log log;
	int m_flage;
	int m_okclick;
	DWORD m_count;
	Browse m_browse;
	TreadOperate m_treadOperate;
};
