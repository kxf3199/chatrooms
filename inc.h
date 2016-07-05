#pragma once
class CChatroomsDlg;
class CClientItem
{
public:
	CString m_strIp;
	SOCKET m_Socket;
	HANDLE hThread;
	CChatroomsDlg *m_pMainWnd;
	CClientItem(){
		m_pMainWnd=NULL;
		m_Socket=INVALID_SOCKET;
		hThread=NULL;
	}
};
#define MAX_BUF_SIZE 1024
#define WM_TRAYICON_MSG (WM_USER+100)
DWORD WINAPI ListenThreadFunc(LPVOID pParam);
DWORD WINAPI ClientThreadProc(LPVOID lpParameter);
DWORD WINAPI ConnectThreadFunc(LPVOID pParam);
BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut=100, BOOL bRead=FALSE);
LRESULT OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam);
