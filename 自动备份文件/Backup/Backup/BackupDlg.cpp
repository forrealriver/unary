
// BackupDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Backup.h"
#include "BackupDlg.h"
#include "Find.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK (WM_USER +1)

// CBackupDlg �Ի���


CBackupDlg::CBackupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CBackupDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CBackupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, mc_sEdit);
	DDX_Control(pDX, IDC_EDIT2, mc_dEdit);
	DDX_Control(pDX, IDOK, cc_okbnclick);
	DDX_Control(pDX, IDC_BUTTON5, cc_killbnclick);
}

BEGIN_MESSAGE_MAP(CBackupDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
//	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CBackupDlg::OnBnClickedOk)
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SIZE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CBackupDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CBackupDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CBackupDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON5, &CBackupDlg::OnBnClickedButton5)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CBackupDlg::OnBnClickedButton3)
END_MESSAGE_MAP()

// CBackupDlg ��Ϣ�������

BOOL CBackupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _T("�Զ�������..."));                // ��Ϣ��ʾ��Ϊ"����������"��VS2008 UNICODE������wcscpy_s()����
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��
	m_sourcePath=sourceLog.ReadPath();
	m_targetPath=targetLog.ReadPath();
	mc_sEdit.SetWindowText(m_sourcePath);
	mc_dEdit.SetWindowText(m_targetPath);
	cc_killbnclick.EnableWindow(FALSE);
	m_okclick = 0;
	CString lg = m_browse.GetWorkFold();
	lg += "\\SourceLog.txt";
	CString ll=m_browse.GetWorkFold();
	ll += "\\TargetLog.txt";
	if(PathFileExists(lg) && PathFileExists(ll)){
		SetTimer(1,1,NULL);
		PostMessage(WM_COMMAND, MAKEWPARAM(IDOK, BN_CLICKED), NULL);
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CBackupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
LRESULT CBackupDlg::OnShowTask(WPARAM wParam, LPARAM lParam){
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam) {
		case WM_RBUTTONUP: {                                       // �Ҽ�����ʱ�����˵�
				LPPOINT lpoint = new tagPOINT;
				::GetCursorPos(lpoint);                    // �õ����λ��
				CMenu menu;
				menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
				menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�ر�"));
				menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
				HMENU hmenu = menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
			}
		break;
		case WM_LBUTTONDBLCLK: {                         // ˫������Ĵ���
				this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
			}
			break;
	}
	return 0;
}
void CBackupDlg::OnSize(UINT nType, int cx, int cy){
	CDialog::OnSize(nType, cx, cy);
	if(nType == SIZE_MINIMIZED){  
		ShowWindow(SW_HIDE);           
	}  
}

//void CBackupDlg::OnTimer(UINT_PTR nIDEvent){
//	CDialog::OnTimer(nIDEvent);
//}

void CBackupDlg::OnBnClickedOk(){
	autoboot.AutoBootSet();
	if(SetCurrentDirectory(m_sourcePath) != TRUE){
		ShowWindow(SW_SHOWNORMAL);
		AfxMessageBox(_T("Ŀ��·����" + m_sourcePath + "�������ڣ����������룡"));
		return;
	}
	if(SetCurrentDirectory(m_targetPath) != TRUE){
		ShowWindow(SW_SHOWNORMAL);
		AfxMessageBox(_T("Ŀ��·����" + m_targetPath + "�������ڣ����������룡"));
		return;
	}
	sourceLog.OutputLog(m_sourcePath);
	targetLog.OutputLog(m_targetPath);
	m_okclick = 1;
	cc_killbnclick.EnableWindow(TRUE);
	cc_okbnclick.EnableWindow(FALSE);
	if(!treadoperate.creadTread(m_sourcePath,m_targetPath))
		AfxMessageBox(_T("�̴߳���ʧ�ܣ���"));
}
void CBackupDlg::OnBnClickedButton1(){
	m_sourcePath=browse.BrowseForFolder();
	mc_sEdit.SetWindowText(m_sourcePath);
}

void CBackupDlg::OnBnClickedCancel(){
	if (m_okclick == 1) {
		if (treadoperate.m_find != NULL) {
			TerminateThread(treadoperate.m_find->m_ThreadHandle, -1);
		}
	}
	OnCancel();
}

void CBackupDlg::OnBnClickedButton2(){
	m_targetPath=browse.BrowseForFolder();
	mc_dEdit.SetWindowText(m_targetPath);
}

void CBackupDlg::OnBnClickedButton5()
{
	if (m_okclick == 1) {
		if (treadoperate.m_find != NULL) {
			m_okclick = 0;
			treadoperate.killTread();
			KillTimer(1);
			cc_killbnclick.EnableWindow(FALSE);
			cc_okbnclick.EnableWindow(TRUE);
		}
	}
}
void CBackupDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	ShowWindow(SW_HIDE);
	KillTimer(1);
	CDialog::OnTimer(nIDEvent);
}

void CBackupDlg::OnBnClickedButton3()
{
	ShellExecute(m_hWnd,_T("open"),m_targetPath,NULL,NULL,SW_SHOW);
}
