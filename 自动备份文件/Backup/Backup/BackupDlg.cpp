
// BackupDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Backup.h"
#include "BackupDlg.h"
#include "Find.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define WM_SHOWTASK (WM_USER +1)

// CBackupDlg 对话框


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

// CBackupDlg 消息处理程序

BOOL CBackupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	// TODO: 在此添加额外的初始化代码
	m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
	m_nid.hWnd    = this->m_hWnd;
	m_nid.uID     = IDR_MAINFRAME;
	m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
	m_nid.uCallbackMessage = WM_SHOWTASK;             // 自定义的消息名称
	m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
	wcscpy_s(m_nid.szTip, _T("自动备份中..."));                // 信息提示条为"服务器程序"，VS2008 UNICODE编码用wcscpy_s()函数
	Shell_NotifyIcon(NIM_ADD, &m_nid);                // 在托盘区添加图标
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
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CBackupDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CBackupDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
LRESULT CBackupDlg::OnShowTask(WPARAM wParam, LPARAM lParam){
	if(wParam != IDR_MAINFRAME)
		return 1;
	switch(lParam) {
		case WM_RBUTTONUP: {                                       // 右键起来时弹出菜单
				LPPOINT lpoint = new tagPOINT;
				::GetCursorPos(lpoint);                    // 得到鼠标位置
				CMenu menu;
				menu.CreatePopupMenu();                    // 声明一个弹出式菜单
				menu.AppendMenu(MF_STRING, WM_DESTROY, _T("关闭"));
				menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y, this);
				HMENU hmenu = menu.Detach();
				menu.DestroyMenu();
				delete lpoint;
			}
		break;
		case WM_LBUTTONDBLCLK: {                         // 双击左键的处理
				this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
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
		AfxMessageBox(_T("目标路径“" + m_sourcePath + "”不存在，请重新输入！"));
		return;
	}
	if(SetCurrentDirectory(m_targetPath) != TRUE){
		ShowWindow(SW_SHOWNORMAL);
		AfxMessageBox(_T("目标路径“" + m_targetPath + "”不存在，请重新输入！"));
		return;
	}
	sourceLog.OutputLog(m_sourcePath);
	targetLog.OutputLog(m_targetPath);
	m_okclick = 1;
	cc_killbnclick.EnableWindow(TRUE);
	cc_okbnclick.EnableWindow(FALSE);
	if(!treadoperate.creadTread(m_sourcePath,m_targetPath))
		AfxMessageBox(_T("线程创建失败！！"));
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
