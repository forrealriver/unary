
// Fold_NewDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Fold_New.h"
#include "Fold_NewDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CFold_NewDlg 对话框




CFold_NewDlg::CFold_NewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFold_NewDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFold_NewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFold_NewDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON2, &CFold_NewDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CFold_NewDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDOK, &CFold_NewDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON4, &CFold_NewDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CFold_NewDlg 消息处理程序

BOOL CFold_NewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFold_NewDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CFold_NewDlg::OnPaint()
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
HCURSOR CFold_NewDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFold_NewDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	Frame folder;
	CString sFolderPath=folder.BrowseForFolder();

	CEdit* pMessage;
    pMessage = (CEdit*) GetDlgItem(IDC_EDIT3);     
    pMessage->SetWindowText(sFolderPath);
}

void CFold_NewDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	Frame folder;
	CString dFolderPath=folder.BrowseForFolder();

	CEdit* pMessage;
    pMessage = (CEdit*) GetDlgItem(IDC_EDIT4);     
    pMessage->SetWindowText(dFolderPath);
}

void CFold_NewDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CEdit* pMessage;
	CString dFolderPath;
    pMessage = (CEdit*) GetDlgItem(IDC_EDIT4);     
    pMessage->GetWindowText(dFolderPath);
	if (SetCurrentDirectory(dFolderPath) != TRUE)
	{
		AfxMessageBox(_T("目标路径“"+dFolderPath+"”不存在，请重新输入！"));
		return;
	}
	CEdit* pMessage2;
	CString sFolderPath;
    pMessage2 = (CEdit*) GetDlgItem(IDC_EDIT3);     
    pMessage2->GetWindowText(sFolderPath);
	if (SetCurrentDirectory(sFolderPath) != TRUE)
	{
		AfxMessageBox(_T("原路径“"+sFolderPath+"”不存在，请重新输入！"));
		return;
	}

	//隐藏控件
	GetDlgItem(IDC_EDIT3)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(FALSE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_HIDE);
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_STATIC1)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(TRUE);

	//目录遍历
	Find finder;
	CString* fileNames=new CString[1000];
	int fileNum=finder.FindFold(sFolderPath,fileNames);
	if(fileNum==0) return;

	//读取Xml文件
	XmlRead xmlread;
	CString* filterNames=new CString[1000];
	CString xm=xmlread.GetWorkDir();
	int *filterNum = new int[1];
	int xml_warn = xmlread.Read(xm+"\\filter.xml", filterNames, filterNum);
	if (xml_warn == 0) return;
	
	//过滤
	Filter filter;
	int filenum = filter.filter(fileNames, fileNum, filterNames, filterNum[0]);

	//最新版本
	int f_num = 0;
	while (filenum > f_num) 
	{
		CString findfile = sFolderPath + "\\" + fileNames[f_num];
		f_num++;
		Compare compare;
		CString *new_filename = new CString[1];
		new_filename[0]="";
		int compare_warning = compare.TimMax(findfile, new_filename);
		if (compare_warning != 0)
			compare.Warning(compare_warning, findfile);
		if (new_filename[0] != "") 
		{
			CString newFullPath=findfile+"\\"+new_filename[0];
			//copy newFullPath to dFolderPath
			Copy copy;
			CreateDirectory(dFolderPath+"\\"+fileNames[f_num-1],NULL);  
			int copy_warnning=copy.copyFold(newFullPath,dFolderPath+"\\"+fileNames[f_num-1]+"\\"+new_filename[0]);
		}
	}
	AfxMessageBox(_T("获取成功！"));
	//显示控件
	GetDlgItem(IDC_EDIT3)->ShowWindow(TRUE);
	GetDlgItem(IDC_EDIT4)->ShowWindow(TRUE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_BUTTON4)->ShowWindow(SW_SHOW);
	GetDlgItem(IDOK)->ShowWindow(SW_SHOW);
	GetDlgItem(IDC_STATIC1)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC2)->ShowWindow(TRUE);
	GetDlgItem(IDC_STATIC3)->ShowWindow(FALSE);
}

void CFold_NewDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	XmlRead xmlread;
	CString xm=xmlread.GetWorkDir();
	WinExec(_T("notepad.exe "+xm+"\\filter.xml"), SW_SHOW);
}
