// chatroomsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "chatrooms.h"
#include "chatroomsDlg.h"
#include "inc.h"
#include <afxtempl.h> 


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatroomsDlg dialog

CChatroomsDlg::CChatroomsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CChatroomsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CChatroomsDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	bShowAll=false;
	m_ListenSock=INVALID_SOCKET;
	m_ConnectSock=INVALID_SOCKET;
	m_hListenThread=NULL;
	m_hConnectThread=NULL;
	m_bIsServer=-1;
	bShutDown=FALSE;
}

void CChatroomsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChatroomsDlg)
	DDX_Control(pDX, IDC_SHOW_MSG, m_MsgEdit);
	DDX_Control(pDX, IDC_START_CLIENT, m_startclient);
	DDX_Control(pDX, IDC_STOP_SEVER, m_stopsever);
	DDX_Control(pDX, IDC_START_SEVER, m_startsever);
	DDX_Control(pDX, IDC_STOP_CLIENT, m_stopclient);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CChatroomsDlg, CDialog)
	//{{AFX_MSG_MAP(CChatroomsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO_SEVER, OnRadioSever)
	ON_BN_CLICKED(IDC_NETSET, OnNetset)
	ON_BN_CLICKED(IDC_START_SEVER, OnStartSever)
	ON_BN_CLICKED(IDC_RADIO_CLIENT, OnRadioClient)
	ON_BN_CLICKED(IDC_SENDMSG, OnSendmsg)
	ON_BN_CLICKED(IDC_START_CLIENT, OnStartClient)
	ON_EN_CHANGE(IDC_INPUT_MSG, OnChangeInputMsg)
	ON_BN_CLICKED(IDC_STOP_CLIENT, OnStopClient)
	ON_BN_CLICKED(IDC_STOP_SEVER, OnStopSever)
	ON_BN_CLICKED(IDC_SHUTDOWN, OnShutdown)
	ON_BN_CLICKED(IDC_OTHER, OnOther)
	ON_COMMAND(ID_MENU_TRAYINCO, OnMenuTrayinco)
	ON_MESSAGE(WM_TRAYICON_MSG, OnTrayCallBackMsg)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_MENU_EXIT, &CChatroomsDlg::OnMenuExit)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChatroomsDlg message handlers

BOOL CChatroomsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	DlgAllInit();
	
	ExtendDlg(false);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CChatroomsDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CChatroomsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CChatroomsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}
void CChatroomsDlg::DlgAllInit()
{
	
	CheckRadioButton(IDC_RADIO_CLIENT,IDC_RADIO_SEVER,IDC_RADIO_CLIENT);
    SetDlgItemText(IDC_IP_ADDR,"127.0.0.1");
	SetDlgItemText(IDC_CONNECT_PORT,"5566");
	SetDlgItemText(IDC_LISTEN_PORT,"5566");
m_stopclient.EnableWindow(false);
m_stopsever.EnableWindow(false);
m_startsever.EnableWindow(false);
//GetDlgItem(IDC_SLISTENPORT)->EnableWindow(false);
GetDlgItem(IDC_LISTEN_PORT)->EnableWindow(false);
EnableWindow(IDC_SLISTENPORT,false);
ShowMsg(_T("程序运行成功！"));
EnableWindow(IDC_SENDMSG,FALSE);
}
BOOL CChatroomsDlg::EnableWindow(UINT uID,BOOL benable)
{
    return GetDlgItem(uID)->EnableWindow(benable);
}
void CChatroomsDlg::DlgClientInit()
{//点服务端选项后
((CButton *)GetDlgItem(IDC_RADIO_CLIENT))->SetCheck(true);
((CButton *)GetDlgItem(IDC_RADIO_SEVER))->SetCheck(false);
m_stopclient.EnableWindow(false);
m_stopsever.EnableWindow(false);
m_startsever.EnableWindow(false);
m_startclient.EnableWindow(true);
//GetDlgItem(IDC_SLISTENPORT)->EnableWindow(false);
GetDlgItem(IDC_LISTEN_PORT)->EnableWindow(false);
EnableWindow(IDC_SLISTENPORT,false);
EnableWindow(IDC_SLISTENPORT,true);
EnableWindow(IDC_CLISTENPORT,true);
EnableWindow(IDC_CONNECT_PORT,true);
EnableWindow(IDC_SEVERIP,true);
EnableWindow(IDC_IP_ADDR,true);

}
void CChatroomsDlg::DlgSeverInit()
{
((CButton *)GetDlgItem(IDC_RADIO_CLIENT))->SetCheck(false);
((CButton *)GetDlgItem(IDC_RADIO_SEVER))->SetCheck(true);
m_stopsever.EnableWindow(true);
m_startsever.EnableWindow(true);
//GetDlgItem(IDC_SLISTENPORT)->EnableWindow(false);
GetDlgItem(IDC_LISTEN_PORT)->EnableWindow(true);
EnableWindow(IDC_SLISTENPORT,true);
m_startclient.EnableWindow(false);
EnableWindow(IDC_CLISTENPORT,false);
EnableWindow(IDC_CONNECT_PORT,false);
EnableWindow(IDC_SEVERIP,false);
EnableWindow(IDC_IP_ADDR,false);
EnableWindow(IDC_START_SEVER, true);
EnableWindow(IDC_STOP_SEVER, false);
SetWindowText(_T("chatrooms-sever"));
}
void CChatroomsDlg::OnRadioSever() 
{
	// TODO: Add your control notification handler code here
DlgSeverInit();
}
void CChatroomsDlg::ExtendDlg(BOOL bShow)
{
static CRect m_DlgRectLarge(0,0,0,0);
static CRect m_DlgRectSmall(0,0,0,0);
if(m_DlgRectLarge.IsRectNull()){
//CRect rectP;
GetWindowRect(&m_DlgRectLarge);
m_DlgRectSmall=m_DlgRectLarge;
//GetDlgItem(IDC_STATIC_CHAT)->GetWindowRect(&rectP);
//ScreenToClient(&rectP);
m_DlgRectSmall.right = m_DlgRectSmall.right*0.63;
//m_DlgRectSmall.right= rectP.right+18;
}
if(bShow){
	bShowAll=true;
SetWindowPos(NULL,m_DlgRectLarge.left,m_DlgRectLarge.right,m_DlgRectLarge.Width(),m_DlgRectLarge.Height(),SWP_NOZORDER|SWP_NOMOVE);
}else{
	bShowAll=false;
SetWindowPos(NULL,m_DlgRectSmall.left,m_DlgRectSmall.right,m_DlgRectSmall.Width(),m_DlgRectSmall.Height(),SWP_NOZORDER|SWP_NOMOVE);
}

}

void CChatroomsDlg::OnNetset() 
{

	if(bShowAll){	
		ExtendDlg(false);
	}else{
		ExtendDlg(true);
	}
}

void CChatroomsDlg::OnStartSever() 
{
	CreateThread(NULL,0,ListenThreadFunc,this,0,NULL);
   	
}

void CChatroomsDlg::OnRadioClient() 
{
DlgClientInit();	
}
void CChatroomsDlg::ShowMsg(CString strMsg)
{
	m_MsgEdit.SetSel(-1, -1);
	m_MsgEdit.ReplaceSel(strMsg+_T("\r\n"));
}
void CChatroomsDlg::RemoveClientFromArray(CClientItem in_Item)
{
	for( int idx = 0; idx <m_ClientArray.GetSize(); idx++ ) {
		CClientItem tItem = m_ClientArray.GetAt(idx);
		if ( tItem.m_Socket == in_Item.m_Socket &&
			tItem.hThread == in_Item.hThread &&
			tItem.m_strIp == in_Item.m_strIp ) {
			m_ClientArray.RemoveAt(idx);
		}
	}
}

void CChatroomsDlg::OnSendmsg() 
{
	CString strMsg;
	GetDlgItemText(IDC_INPUT_MSG, strMsg);
	if ( m_bIsServer == TRUE ) {
		strMsg = _T("服务器：>") + strMsg;
		ShowMsg(strMsg);
		SendClientsMsg(strMsg);
	}else if (m_bIsServer == FALSE) {
		CString strTmp = _T("本地客户端：>") + strMsg;
		ShowMsg(strTmp);
		int iSend = send(m_ConnectSock, (char *)strMsg.GetBuffer(0), strMsg.GetLength()*sizeof(TCHAR), 0);
		strMsg.ReleaseBuffer();
	}else {
		AfxMessageBox(_T("请您先进入聊天室"));
		}
	SetDlgItemText(IDC_INPUT_MSG, _T(""));
}

void CChatroomsDlg::OnStartClient() 
{
	m_hConnectThread=CreateThread(NULL,0,ConnectThreadFunc,this,0,NULL);
	EnableWindow(IDC_STOP_CLIENT,TRUE);
}
void CChatroomsDlg::SendClientsMsg(CString strMsg, CClientItem *pNotSend)
{
	TCHAR szBuf[MAX_BUF_SIZE] = {0};
	strncpy(szBuf, strMsg,MAX_BUF_SIZE);
	for( INT_PTR idx = 0; idx < m_ClientArray.GetSize(); idx++ ) {
		if ( !pNotSend || pNotSend->m_Socket != m_ClientArray.GetAt(idx).m_Socket ||pNotSend->hThread != m_ClientArray.GetAt(idx).hThread ||
			pNotSend->m_strIp != m_ClientArray.GetAt(idx).m_strIp) {
			send(m_ClientArray.GetAt(idx).m_Socket, (char *)szBuf, _tcslen(szBuf)*sizeof(TCHAR), 0);
		}
	}
}
/*
void CChatroomDlg::OnBnClickedSendmsg()
{
	
}
*/

void CChatroomsDlg::OnChangeInputMsg() 
{
	CString StrMsg;
	GetDlgItemText(IDC_INPUT_MSG,StrMsg);
	if (StrMsg.IsEmpty())
	{EnableWindow(IDC_SENDMSG,FALSE);
	} 
	else
	{EnableWindow(IDC_SENDMSG,TRUE);
	}

	
}
void CChatroomsDlg::StopClient()
{
	
	bShutDown = TRUE;
	EnableWindow(IDC_START_CLIENT, true);
	EnableWindow(IDC_STOP_CLIENT, false);
	DWORD dwRet = WaitForSingleObject(m_hConnectThread, 1000);
	if ( dwRet != WAIT_OBJECT_0 ) {
		TerminateThread(m_hConnectThread, -1);
		closesocket(m_ConnectSock);
	}
	m_hConnectThread = NULL;
	m_ConnectSock = INVALID_SOCKET;
	m_bIsServer = -1;
	bShutDown = FALSE;
}
void CChatroomsDlg::StopSever()
{
	UINT nCount = m_ClientArray.GetSize();
	HANDLE *m_pHandles = new HANDLE[nCount+1];
	m_pHandles[0] = m_hListenThread;
	for( int idx = 0; idx < nCount; idx++ ) {
		m_pHandles[idx+1] = m_ClientArray.GetAt(idx).hThread;
	}
	bShutDown = TRUE;
	EnableWindow(IDC_START_SEVER, true);
	EnableWindow(IDC_STOP_SEVER, false);
	DWORD dwRet = WaitForMultipleObjects(nCount+1, m_pHandles, TRUE, 1000);
	if ( dwRet != WAIT_OBJECT_0 ) {
		for( INT_PTR i = 0; i < m_ClientArray.GetSize(); i++ ) {
			TerminateThread(m_ClientArray.GetAt(i).hThread, -1);
			closesocket(m_ClientArray.GetAt(i).m_Socket);
		}
		TerminateThread(m_hListenThread, -1);
		closesocket(m_ListenSock);
	}
	delete [] m_pHandles;
	m_hListenThread = NULL;
	m_ListenSock = INVALID_SOCKET;
	m_bIsServer = -1;
	bShutDown = FALSE;
	
}




	void CChatroomsDlg::OnStopClient() 
	{StopClient();
	ShowMsg(_T("停止客户端"));
	}

void CChatroomsDlg::OnStopSever() 
{
	StopSever();
	
}

void CChatroomsDlg::OnShutdown() 
{
	if(m_bIsServer==TRUE)
	{
		StopSever();
	}else if (m_bIsServer==FALSE)
	{StopClient();
	}else
	{
		OnCancel();
	}
	// TODO: Add your control notification handler code here
	
}

void CChatroomsDlg::OnOther() 
{
	CPoint pt;
	CRect mRect;
	CMenu mMenu, *pMenu = NULL;
	GetDlgItem(IDC_OTHER)->GetWindowRect(&mRect);
	pt = mRect.BottomRight();
	pt.y = mRect.top+10;
	mMenu.LoadMenu(IDR_MENU1);
	pMenu = mMenu.GetSubMenu(0);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
	
}
BOOL CChatroomsDlg::TrayMyIcon(BOOL bAdd)
{
	BOOL bRet = FALSE;
	NOTIFYICONDATA tnd;
	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = GetSafeHwnd();
	tnd.uID = IDR_MAINFRAME;
	if ( bAdd == TRUE ) {
		tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnd.uCallbackMessage = WM_TRAYICON_MSG;
		tnd.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
		strncpy(tnd.szTip, _T("聊天室v1.0"), sizeof(tnd.szTip));
		ShowWindow(SW_MINIMIZE);
		ShowWindow(SW_HIDE);
		bRet = Shell_NotifyIcon(NIM_ADD, &tnd);
	}else{
		ShowWindow(SW_SHOWNA);
		SetForegroundWindow();
		bRet = Shell_NotifyIcon(NIM_DELETE, &tnd);
	}
	return bRet;
}



void CChatroomsDlg::OnMenuTrayinco() 
{
	TrayMyIcon();
}
LRESULT CChatroomsDlg::OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam)
{
	switch(lparam)
	{
	case WM_RBUTTONUP:
		{
			CMenu mMenu, *pMenu = NULL;
			CPoint pt;
			mMenu.LoadMenu(IDR_MENU2);
			pMenu = mMenu.GetSubMenu(0);
			GetCursorPos(&pt);
			SetForegroundWindow();
			pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
			break;
		}
	case WM_LBUTTONDBLCLK:
		ShowWindow(SW_RESTORE);
		SetForegroundWindow();
		break;
	default:break;
	}
	return NULL;
}


void CChatroomsDlg::OnMenuExit()
{
	// TODO:  在此添加命令处理程序代码
	OnShutdown();
}


