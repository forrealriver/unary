
// BackupDlg.h : 头文件
//
#pragma once
#include "AutoBoot.h"
#include "NewTime.h"
#include "Log.h"
#include "SourceLog.h"
#include "TargetLog.h"
#include "Browse.h"
#include "TreadOperate.h"
// CBackupDlg 对话框
class CBackupDlg : public CDialog
{
// 构造
public:
	CBackupDlg(CWnd* pParent = NULL);	// 标准构造函数
// 对话框数据
	enum { IDD = IDD_BACKUP_DIALOG };
	AutoBoot autoboot;
	Browse browse;
	CString m_sourcePath;
	CString m_targetPath;
	CEdit mc_sEdit;
	CEdit mc_dEdit;
	SourceLog sourceLog;
	TargetLog targetLog;
	Log log;
	TreadOperate treadoperate;
	int m_okclick;
	CWnd cc_okbnclick;
	CWnd cc_killbnclick;
	Browse m_browse;
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	NOTIFYICONDATA m_nid;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButton3();
};
