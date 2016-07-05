// chatroomsDlg.h : header file
//

#if !defined(AFX_CHATROOMSDLG_H__A66A5610_CF7A_4AF5_951E_D2887FDB519A__INCLUDED_)
#define AFX_CHATROOMSDLG_H__A66A5610_CF7A_4AF5_951E_D2887FDB519A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <afxtempl.h> 
#include "inc.h"


/////////////////////////////////////////////////////////////////////////////
// CChatroomsDlg dialog

class CChatroomsDlg : public CDialog
{
// Construction
public:
	CChatroomsDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CChatroomsDlg)
	enum { IDD = IDD_CHATROOMS_DIALOG };
	CEdit	m_MsgEdit;
	CButton	m_startclient;
	CButton	m_stopsever;
	CButton	m_startsever;
	CButton	m_stopclient;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatroomsDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CChatroomsDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnRadioSever();
	afx_msg void OnNetset();
	afx_msg void OnStartSever();
	afx_msg void OnRadioClient();
	afx_msg void OnSendmsg();
	afx_msg void OnStartClient();
	afx_msg void OnChangeInputMsg();
	afx_msg void OnStopClient();
	afx_msg void OnStopSever();
	afx_msg void OnShutdown();
	afx_msg void OnOther();
	afx_msg void OnMenuTrayinco();
	afx_msg LRESULT OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	void DlgAllInit();
	void DlgClientInit();
	void DlgSeverInit();
    BOOL EnableWindow(UINT uID,BOOL benable=true);
	void ExtendDlg(BOOL bShow);
	bool bShowAll;
    SOCKET m_ListenSock;
	SOCKET m_ConnectSock;
	HANDLE m_hListenThread;
	HANDLE m_hConnectThread;
	CArray <CClientItem,CClientItem> m_ClientArray;
	void ShowMsg(CString strMsg);
	void RemoveClientFromArray(CClientItem in_Item);
	void SendClientsMsg(CString strMsg, CClientItem *pNotSend=NULL);
	int m_bIsServer;
	void StopClient();
	BOOL bShutDown;
	void StopSever();
	BOOL TrayMyIcon(BOOL bAdd=TRUE);



	afx_msg void OnMenuExit();
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMSDLG_H__A66A5610_CF7A_4AF5_951E_D2887FDB519A__INCLUDED_)
