
// Fold_NewDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Fold_New.h"
#include "Fold_NewDlg.h"
#include "Frame.h"
#include "Find.h"
#include "Filter.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CFold_NewDlg �Ի���




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
END_MESSAGE_MAP()


// CFold_NewDlg ��Ϣ�������

BOOL CFold_NewDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CFold_NewDlg::OnPaint()
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

	CEdit* pMessage2;
	CString sFolderPath;
    pMessage2 = (CEdit*) GetDlgItem(IDC_EDIT3);     
    pMessage2->GetWindowText(sFolderPath);
	//Ŀ¼����
	Find finder;
	CString* fileNames=new CString[1000];
	int fileNum=finder.FindFold(sFolderPath,fileNames);

	//��ȡXml�ļ�
	Filter filter;
	CString* filterNames=new CString[1000];
	bool readXml=filter.ReadXml(filterNames);

	//OnOK();
}
