
// TtsClientDlg.h: 標頭檔
//

#pragma once
#include "ttsCore.h"


// CTtsClientDlg 對話方塊
class CTtsClientDlg : public CDialogEx
{
// 建構
public:
	CTtsClientDlg(CWnd* pParent = nullptr);	// 標準建構函式

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TTSCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支援


// 程式碼實作
protected:
	HICON m_hIcon;

	// 產生的訊息對應函式
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	CComboBox m_SampleRate;
	CComboBox m_Voice;
	CComboBox m_Format;
	CEdit m_Text;
	CEdit m_AppKey;
	CEdit m_Token;
	CEdit m_IpAddr;
	CEdit m_VolCtrl;
	CEdit m_SpdCtrl;
	CEdit m_PitchCtrl;
	CEdit m_FileName;

	ttsParam	*m_params;
	int	m_vol, m_speed, m_pitch;

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnDestroy();
private:
	CComboBox m_Engine;
public:
	afx_msg void OnCbnSelchangeEngine();
};
