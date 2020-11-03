
// TtsClientDlg.cpp: 實作檔案
//

#include "stdafx.h"
#include "TtsClient.h"
#include "TtsClientDlg.h"
#include "afxdialogex.h"
#include <mmsystem.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTtsClientDlg 對話方塊



CTtsClientDlg::CTtsClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TTSCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTtsClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SAMPLE_RATE, m_SampleRate);
	DDX_Control(pDX, IDC_VOICE, m_Voice);
	DDX_Control(pDX, IDC_FORMAT, m_Format);
	DDX_Control(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_APPKEY, m_AppKey);
	DDX_Control(pDX, IDC_TOKEN, m_Token);
	DDX_Control(pDX, IDC_IPADDR, m_IpAddr);

	DDX_Control(pDX, IDC_VOL, m_VolCtrl);
	DDX_Text(pDX, IDC_VOL, m_vol);
	DDV_MinMaxInt(pDX, m_vol, 0, 100);

	DDX_Control(pDX, IDC_SPEED, m_SpdCtrl);
	DDX_Text(pDX, IDC_SPEED, m_speed);
	DDV_MinMaxInt(pDX, m_speed, -500, 500);

	DDX_Control(pDX, IDC_PITCH, m_PitchCtrl);
	DDX_Text(pDX, IDC_PITCH, m_pitch);
	DDV_MinMaxInt(pDX, m_pitch, -500, 500);
	DDX_Control(pDX, IDC_FILENAME, m_FileName);
	DDX_Control(pDX, IDC_ENGINE, m_Engine);
}

BEGIN_MESSAGE_MAP(CTtsClientDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CTtsClientDlg::OnBnClickedOk)
	ON_WM_DESTROY()
	ON_CBN_SELCHANGE(IDC_ENGINE, &CTtsClientDlg::OnCbnSelchangeEngine)
END_MESSAGE_MAP()


// CTtsClientDlg 訊息處理常式

BOOL CTtsClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定
	InitCurlGlobal();

	m_Engine.InsertString(0, L"Ali");
	m_Engine.InsertString(1, L"BaiDu");
	m_Engine.InsertString(2, L"TongHua");
	m_Engine.SetCurSel(0);

	m_AppKey.SetWindowText(L"default");
	m_Token.SetWindowText(L"default");
	m_IpAddr.SetWindowText(L"115.236.44.181");
	m_FileName.SetWindowText(L".\\AliTTS.wav");

	m_SampleRate.InsertString(0, L"8000");
	m_SampleRate.InsertString(1, L"16000");
	m_SampleRate.SetCurSel(0);

	m_Voice.InsertString(0, L"Woman");
	m_Voice.InsertString(1, L"Man");
	m_Voice.InsertString(2, L"Woman2");
	m_Voice.SetCurSel(0);

	m_Format.InsertString(0, L"PCM");
	m_Format.InsertString(1, L"Wave");
	m_Format.InsertString(2, L"MP3");
	m_Format.SetCurSel(1);

	m_vol = 50;
	m_speed = m_pitch = 0;
	UpdateData(FALSE);
	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CTtsClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CTtsClientDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CTtsClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTtsClientDlg::OnBnClickedOk()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	DWORD	tick1, tick2;
	int		rc;
	CString	appKey, token, ip, file, text;
	char	szAppKey[MAX_KEY_LEN], szToken[MAX_KEY_LEN], szIP[MAX_KEY_LEN], szTemp[MAX_PATH];
	UpdateData(TRUE);
	GetDlgItem(IDOK)->EnableWindow(FALSE);

	m_AppKey.GetWindowText(appKey);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, appKey.GetBuffer(), -1, szAppKey, sizeof(szAppKey), NULL, NULL);
	m_Token.GetWindowText(token);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, token.GetBuffer(), -1, szToken, sizeof(szToken), NULL, NULL);
	m_IpAddr.GetWindowText(ip);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, ip.GetBuffer(), -1, szIP, sizeof(szIP), NULL, NULL);
	
	if (m_Engine.GetCurSel() == 0)
		m_params = CreateTtsParams(szAppKey, szToken, NULL, szIP);
	else if(m_Engine.GetCurSel() == 1)
		m_params = CreateTtsParams(szAppKey, szToken, szIP, NULL);
	else if(m_Engine.GetCurSel() == 2)
		m_params = CreateTtsParams(szToken, szAppKey, NULL, NULL);

	m_FileName.GetWindowText(file);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, file.GetBuffer(), -1, szTemp, sizeof(szTemp), NULL, NULL);
	SetFileName(m_params, szTemp);

	m_params->format = (ttsFormat) m_Format.GetCurSel();
	m_params->voice = (ttsVoice) m_Voice.GetCurSel();
	m_params->sample_rate = (m_SampleRate.GetCurSel() == 0) ? 8000 : 16000;
	m_params->volume = m_vol;
	m_params->speech_rate = m_speed;
	m_params->pitch_rate = m_pitch;

	m_Text.GetWindowText(text);
	WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, text.GetBuffer(), -1, szTemp, sizeof(szTemp), NULL, NULL);
	tick1 = GetTickCount();
	if (m_Engine.GetCurSel() == 0)
		rc = AliTextToSpeech(m_params, szTemp);
	else if (m_Engine.GetCurSel() == 1)
		rc = BaiBuTextToSpeech(m_params, szTemp);
	else if (m_Engine.GetCurSel() == 2)
		rc = ThsTextToSpeech(m_params, szTemp);
	tick2 = GetTickCount();
	
	RelaseTtsParams(m_params);
	text.Format(L"Translation took %d ms, rc=%d", tick2 - tick1, rc);

	if (AfxMessageBox(text, MB_ICONINFORMATION, 0) == IDOK)
	{
		if (rc == 0)
		{
			if (PlaySound(file.GetBuffer(), NULL, SND_FILENAME | SND_ASYNC) == FALSE)
			{
				OutputDebugString(L"PlaySound failed !!!");
			}
		}
	}

	GetDlgItem(IDOK)->EnableWindow(TRUE);
}


void CTtsClientDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此加入您的訊息處理常式程式碼
	ClearCurlGlobal();
}


void CTtsClientDlg::OnCbnSelchangeEngine()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	m_IpAddr.EnableWindow(TRUE);

	if (m_Engine.GetCurSel() == 0)
	{
		m_AppKey.SetWindowText(L"default");
		m_Token.SetWindowText(L"default");
		m_IpAddr.SetWindowText(L"115.236.44.181");
		m_FileName.SetWindowText(L".\\AliTTS.wav");

		m_SampleRate.SetCurSel(0);
		m_vol = 50;
		m_speed = m_pitch = 0;

		GetDlgItem(IDC_STATIC_APPKEY)->SetWindowText(L"appKey");
		GetDlgItem(IDC_STATIC_TOKEN)->SetWindowText(L"token");
		GetDlgItem(IDC_STATIC_KEY)->SetWindowText(L"IP Addr");
	}
	else if (m_Engine.GetCurSel() == 1)
	{
		m_AppKey.SetWindowText(L"11737775");
		m_Token.SetWindowText(L"uWouczwCO8mEMAOsYc1EmrIv");
		m_IpAddr.SetWindowText(L"4WPtAWOeRYHNY52dKFjHf6Hhlf2cdAqM");
		m_FileName.SetWindowText(L".\\BaiDuTTS.wav");

		m_SampleRate.SetCurSel(1);
		m_vol = m_speed = m_pitch = 5;

		GetDlgItem(IDC_STATIC_APPKEY)->SetWindowText(L"appID");
		GetDlgItem(IDC_STATIC_TOKEN)->SetWindowText(L"apiKey");
		GetDlgItem(IDC_STATIC_KEY)->SetWindowText(L"SeKey");
	}
	else if (m_Engine.GetCurSel() == 2)
	{
		m_AppKey.SetWindowText(L"1661EC10FBCA13820FF7A2E89260F5F6");
		m_Token.SetWindowText(L"2098F43BB3824CE8B920190827120424");
		m_IpAddr.EnableWindow(FALSE);
		m_FileName.SetWindowText(L".\\TongTTS.wav");

		m_SampleRate.SetCurSel(1);
		m_vol = 50;
		m_speed = 100;
		m_pitch = 0;

		GetDlgItem(IDC_STATIC_APPKEY)->SetWindowText(L"appKey");
		GetDlgItem(IDC_STATIC_TOKEN)->SetWindowText(L"appId");
	}

	UpdateData(FALSE);
}
