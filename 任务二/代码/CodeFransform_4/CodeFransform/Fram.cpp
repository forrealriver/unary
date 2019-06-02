
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
	DDX_Control(pDX, IDC_COMBO1, cc_sComboBox);
	DDX_Control(pDX, IDC_COMBO2, cc_dComboBox);
	DDX_Control(pDX, IDC_EDIT1, cc_sEdit);
	DDX_Control(pDX, IDC_EDIT2, cc_dEdit);
	DDX_Control(pDX, IDC_PROGRESS1, cc_process);
	DDX_Control(pDX, IDC_STATIC4, cc_static);
}

BEGIN_MESSAGE_MAP(Fram, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &Fram::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Fram::OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, &Fram::OnBnClickedOk)
END_MESSAGE_MAP()


// Fram 消息处理程序

BOOL Fram::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cc_process.SetRange(0,100); 
	cc_process.SetStep(1);
	cc_process.SetPos(0);

	cc_sComboBox.AddString(_T("Unicode"));
	cc_sComboBox.AddString(_T("UTF_8"));
	cc_dComboBox.AddString(_T("Unicode"));
	cc_dComboBox.AddString(_T("UTF_8"));
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
	cc_sEdit.SetWindowText(browse.BrowseForFile(this->m_hWnd));
}

void Fram::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	cc_dEdit.SetWindowText(browse.BrowseFileFor());
}

void Fram::OnBnClickedOk()
{
	cc_sEdit.GetWindowText(sFildPath);
	cc_dEdit.GetWindowText(dFildPath);
	int sIndex=cc_sComboBox.GetCurSel();
	if(sIndex<0){
		AfxMessageBox(_T("请选择原文件编码格式"));
		return;
	}

	cc_sComboBox.GetLBText(sIndex,sCode);
	int dIndex=cc_dComboBox.GetCurSel();
	if(dIndex<0){
		AfxMessageBox(_T("请选择需要的目标文件编码格式"));
		return;
	}
	cc_dComboBox.GetLBText(dIndex,dCode);
	if(dCode==sCode){
		AfxMessageBox(_T("请选择不同的编码格式"));
		return;
	}
	if (!treadOperate.creadTread(sFildPath,dFildPath,sCode,dCode)){
		CString error=treadOperate.GetLastError();
		AfxMessageBox(error);
	}
	/*for(int i = 0; i<100; i++)
	{
		CString is=Format("%d",i);
		cc_process.SetPos(i);
		cc_static.SetWindowText(_T(is+"%");
	}*/
	//OnOK();
}
