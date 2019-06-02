
// Fold_NewDlg.h : 头文件
//

#pragma once
#include "tinyxml.h"

// CFold_NewDlg 对话框
class CFold_NewDlg : public CDialog
{
// 构造
public:
	CFold_NewDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FOLD_NEW_DIALOG };
public:
	int CFold_NewDlg::filter(CString* fileNames, int fileNum, CString* filterNames, int filterNum);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
};
