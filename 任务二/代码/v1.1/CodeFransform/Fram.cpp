
// Fram.cpp : 实现文件
//

#include "stdafx.h"
#include "CodeFransform.h"
#include "Fram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Fram 对话框
Fram::Fram(CWnd* pParent /*=NULL*/)
	: CDialog(Fram::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Fram::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, cc_okbnclick);
	DDX_Control(pDX, IDC_EDIT1, cc_sEdit);
	DDX_Control(pDX, IDC_EDIT2, cc_dEdit);
	DDX_Control(pDX, IDSTOP, cc_killbnclick);
	DDX_Control(pDX, IDC_STATIC4, cc_static);
	DDX_Control(pDX, IDC_PROGRESS1, cc_process);
	DDX_Control(pDX, IDC_STATIC6, cc_staticSpeed);
	DDX_Control(pDX, IDC_RADIO2, cc_unicodeToUtf8);
	DDX_Control(pDX, IDC_RADIO3, cc_uft8ToUnicode);
}

BEGIN_MESSAGE_MAP(Fram, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &Fram::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Fram::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Fram::OnBnClickedOk)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &Fram::OnBnClickedCancel)
	ON_BN_CLICKED(IDSTOP, &Fram::OnBnClickedStop)
END_MESSAGE_MAP()


// Fram 消息处理程序

BOOL Fram::OnInitDialog()
{
	CDialog::OnInitDialog();
	log.OutputLog(_T("打开程序"));
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cc_process.SetRange(0, 100);
	cc_process.SetStep(1);
	cc_process.SetPos(0);

	cc_killbnclick.EnableWindow(FALSE);
	m_okclick = 0;
	m_count = 0;
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Fram::OnPaint()
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
HCURSOR Fram::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Fram::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	cc_sEdit.SetWindowText(m_browse.BrowseForFile(this->m_hWnd));
}

void Fram::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	cc_dEdit.SetWindowText(m_browse.BrowseFileFor());
}
//确定转换
void Fram::OnBnClickedOk()
{
	cc_sEdit.GetWindowText(m_sFildPath);
	cc_dEdit.GetWindowText(m_dFildPath);
	if (m_sFildPath == "" || m_dFildPath == "") {
		AfxMessageBox(_T("请选择文件"));
		return;
	}
	if (!PathFileExists(m_sFildPath)) {
		AfxMessageBox(_T("原文件不存在"));
		return;
	}

	int uft8 = cc_uft8ToUnicode.GetCheck();
	int unicode = cc_unicodeToUtf8.GetCheck();
	if(uft8 == 0 && unicode == 0){
		AfxMessageBox(_T("请选择转码类型"));
		return;
	}
	if(uft8 == 1){
		m_sCode = "UTF_8";
		m_dCode = "Unicode";
	}
	else if(unicode == 1){
		m_dCode = "UTF_8";
		m_sCode = "Unicode";
	}
	else return;

	m_okclick = 1;
	cc_okbnclick.EnableWindow(FALSE);
	cc_killbnclick.EnableWindow(TRUE);
	SetTimer(1, 100, NULL);
	if (!m_treadOperate.creadTread(m_sFildPath, m_dFildPath, m_sCode, m_dCode)) {
		CString error = m_treadOperate.GetLastError();
		AfxMessageBox(error);
	}
}
//定时器显示进度条
void Fram::OnTimer(UINT_PTR nIDEvent) {
	// TODO: Add your message handler code here and/or call default
	CString speed;
	CString now;
	CString all;
	CString is;
	double nowMB;
	double allMB;
	double times;
	double speednow;
	TreadState state;

	m_count++;
	int x = m_treadOperate.getState(state);
	if (x != 0){
		if (state.m_state == -1) {
			KillTimer(1);
			m_count = 0;
			x = 0;
			cc_killbnclick.EnableWindow(FALSE);
			cc_okbnclick.EnableWindow(TRUE);
			AfxMessageBox(m_treadOperate.GetLastError());
			return;
		}
		if (state.m_state == 2) {
			x = 100;
		}
		else if (state.m_state == 1) {
			double rate = (double)state.m_nowWork / (double)state.m_allWork;
			x = (int)(rate * 100);
		}
	}
	//进度条显示
	is.Format("%d", x);
	cc_process.SetPos(x);
	cc_static.SetWindowText(_T(is + "%"));

	//当前速度显示
	nowMB = (double)state.m_nowWork / (double)(1024 * 1024);
	allMB = (double)state.m_allWork / (double)(1024 * 1024);
	times = (double)m_count / (double)10;
	speednow = (double)nowMB / times;
	speed.Format("%.2lf", speednow);
	all.Format("%.2lf", allMB);
	now.Format("%.2lf", nowMB);
	cc_staticSpeed.SetWindowText(_T(speed + " M/S\n") + now + _T(" M/") + all + _T(" M"));

	if (x == 100) {
		KillTimer(1);
		log.OutputLog(_T("转码成功"));
		m_treadOperate.killTread();
		cc_killbnclick.EnableWindow(FALSE);
		cc_okbnclick.EnableWindow(TRUE);
		m_count = 0;
		AfxMessageBox(_T("转码成功"));
	}
	CDialog::OnTimer(1);
}
//取消转换
void Fram::OnBnClickedStop() {
	// TODO: Add your control notification handler code here
	if (m_okclick == 1) {
		if (m_treadOperate.m_tansControl != NULL) {
			m_okclick = 0;
			m_count = 0;
			KillTimer(1);
			log.OutputLog(_T("转码取消"));
			m_treadOperate.killTread();
			cc_killbnclick.EnableWindow(FALSE);
			cc_okbnclick.EnableWindow(TRUE);
		}
	}
}
void Fram::OnBnClickedCancel(){
	// TODO: Add your control notification handler code here
	OnCancel();
}

