
// Fram.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CodeFransform.h"
#include "Fram.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Fram �Ի���




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


// Fram ��Ϣ�������

BOOL Fram::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	cc_process.SetRange(0,100); 
	cc_process.SetStep(1);
	cc_process.SetPos(0);

	cc_sComboBox.AddString(_T("Unicode"));
	cc_sComboBox.AddString(_T("UTF_8"));
	cc_dComboBox.AddString(_T("Unicode"));
	cc_dComboBox.AddString(_T("UTF_8"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Fram::OnPaint()
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
		AfxMessageBox(_T("��ѡ��ԭ�ļ������ʽ"));
		return;
	}

	cc_sComboBox.GetLBText(sIndex,sCode);
	int dIndex=cc_dComboBox.GetCurSel();
	if(dIndex<0){
		AfxMessageBox(_T("��ѡ����Ҫ��Ŀ���ļ������ʽ"));
		return;
	}
	cc_dComboBox.GetLBText(dIndex,dCode);
	if(dCode==sCode){
		AfxMessageBox(_T("��ѡ��ͬ�ı����ʽ"));
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
