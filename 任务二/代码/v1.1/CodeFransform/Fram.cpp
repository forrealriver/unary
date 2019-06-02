
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
	cc_sEdit.SetWindowText(m_browse.BrowseForFile(this->m_hWnd));
}

void Fram::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	cc_dEdit.SetWindowText(m_browse.BrowseFileFor());
}
//ȷ��ת��
void Fram::OnBnClickedOk()
{
	cc_sEdit.GetWindowText(m_sFildPath);
	cc_dEdit.GetWindowText(m_dFildPath);
	if (m_sFildPath == "" || m_dFildPath == "") {
		AfxMessageBox(_T("��ѡ���ļ�"));
		return;
	}
	if (!PathFileExists(m_sFildPath)) {
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
//��ʱ����ʾ������
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
	//��������ʾ
	is.Format("%d", x);
	cc_process.SetPos(x);
	cc_static.SetWindowText(_T(is + "%"));

	//��ǰ�ٶ���ʾ
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
		log.OutputLog(_T("ת��ɹ�"));
		m_treadOperate.killTread();
		cc_killbnclick.EnableWindow(FALSE);
		cc_okbnclick.EnableWindow(TRUE);
		m_count = 0;
		AfxMessageBox(_T("ת��ɹ�"));
	}
	CDialog::OnTimer(1);
}
//ȡ��ת��
void Fram::OnBnClickedStop() {
	// TODO: Add your control notification handler code here
	if (m_okclick == 1) {
		if (m_treadOperate.m_tansControl != NULL) {
			m_okclick = 0;
			m_count = 0;
			KillTimer(1);
			log.OutputLog(_T("ת��ȡ��"));
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

