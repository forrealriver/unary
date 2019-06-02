
// BackupDlg.h : ͷ�ļ�
//
#pragma once
#include "AutoBoot.h"
#include "NewTime.h"
#include "Log.h"
#include "SourceLog.h"
#include "TargetLog.h"
#include "Browse.h"
#include "TreadOperate.h"
// CBackupDlg �Ի���
class CBackupDlg : public CDialog
{
// ����
public:
	CBackupDlg(CWnd* pParent = NULL);	// ��׼���캯��
// �Ի�������
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
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	NOTIFYICONDATA m_nid;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
