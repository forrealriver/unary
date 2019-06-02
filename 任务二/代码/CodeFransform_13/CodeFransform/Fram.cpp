
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


// Fram ��Ϣ�������

BOOL Fram::OnInitDialog()
{
	CDialog::OnInitDialog();
	log.OutputLog(_T("�򿪳���"));
	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	cc_process.SetRange(0, 100);
	cc_process.SetStep(1);
	cc_process.SetPos(0);

	cc_killbnclick.EnableWindow(FALSE);
	m_okclick = 0;
	m_flage = 0;
	m_count = 0;
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
//ȷ��ת��
void Fram::OnBnClickedOk()
{
	cc_sEdit.GetWindowText(sFildPath);
	cc_dEdit.GetWindowText(dFildPath);
	if (sFildPath == "" || dFildPath == "") {
		AfxMessageBox(_T("��ѡ���ļ�"));
		return;
	}
	if (!PathFileExists(sFildPath)) {
		AfxMessageBox(_T("ԭ�ļ�������"));
		return;
	}

	int uft8 = cc_uft8ToUnicode.GetCheck();
	int unicode = cc_unicodeToUtf8.GetCheck();
	if(uft8 == 0 && unicode == 0){
		AfxMessageBox(_T("��ѡ��ת������"));
		return;
	}
	if(uft8 == 1){
		sCode = "UTF_8";
		dCode = "Unicode";
	}
	else if(unicode == 1){
		dCode = "UTF_8";
		sCode = "Unicode";
	}
	else return;

	m_flage = 0;
	m_okclick = 1;
	cc_okbnclick.EnableWindow(FALSE);
	cc_killbnclick.EnableWindow(TRUE);
	SetTimer(1, 100, NULL);
	if (!treadOperate.creadTread(sFildPath, dFildPath, sCode, dCode)) {
		CString error = treadOperate.GetLastError();
		AfxMessageBox(error);
	}
}
//��ʱ����ʾ������
void Fram::OnTimer(UINT_PTR nIDEvent) {
	// TODO: Add your message handler code here and/or call default
	m_count++;
	int x = treadOperate.getState();
	if (x == -1 && m_flage == 0) {
		m_count = 0;
		m_flage = 1;
		cc_killbnclick.EnableWindow(FALSE);
		cc_okbnclick.EnableWindow(TRUE);
		KillTimer(1);
		AfxMessageBox(treadOperate.GetLastError());
		return;
	}
	//��������ʾ
	CString is;
	is.Format("%d", x);
	cc_process.SetPos(x);
	cc_static.SetWindowText(_T(is + "%"));

	//��ǰ�ٶ���ʾ
	if (m_flage == 0){
		double nowMB = (double)treadOperate.m_nowsize / (double)(1024 * 1024);
		double times = (double)m_count / (double)10;
		double speednow = (double)nowMB / times;
		CString speed;
		speed.Format("%.2lf", speednow);
		cc_staticSpeed.SetWindowText(_T(speed + " M/s"));
	}

	if (x == 100 && m_flage == 0) {
		m_flage = 1;
		log.OutputLog(_T("ת��ɹ�"));
		treadOperate.killTread();
		cc_killbnclick.EnableWindow(FALSE);
		cc_okbnclick.EnableWindow(TRUE);
		m_count = 0;
		KillTimer(1);
		AfxMessageBox(_T("ת��ɹ�"));
	}
	CDialog::OnTimer(1);
}
//ȡ��ת��
void Fram::OnBnClickedStop() {
	// TODO: Add your control notification handler code here
	if (m_okclick == 1) {
		if (treadOperate.tansControl != NULL) {
			m_okclick = 0;
			m_count = 0;
			KillTimer(1);
			log.OutputLog(_T("ת��ȡ��"));
			treadOperate.killTread();
			cc_killbnclick.EnableWindow(FALSE);
			cc_okbnclick.EnableWindow(TRUE);
		}
	}
}
void Fram::OnBnClickedCancel(){
	// TODO: Add your control notification handler code here
	OnCancel();
}

