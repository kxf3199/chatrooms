#include "stdafx.h"
#include "resource.h"
#include "chatroomsDlg.h"
#include "inc.h"
 



BOOL SOCKET_Select(SOCKET hSocket, int nTimeOut, BOOL bRead)
{
	fd_set fdset;
	timeval tv;
	FD_ZERO(&fdset);
	FD_SET(hSocket, &fdset);
	nTimeOut = nTimeOut > 1000 ? 1000 : nTimeOut;
	tv.tv_sec  = 0;
	tv.tv_usec = nTimeOut;
	
	int iRet = 0;
	if ( bRead ) {
		iRet = select(0, &fdset, NULL , NULL, &tv);
	}else{
		iRet = select(0, NULL , &fdset, NULL, &tv);
	}
	
	if(iRet <= 0) {
		return FALSE;
	} else if (FD_ISSET(hSocket, &fdset)){
		return TRUE;
	}
	return FALSE;
}


DWORD WINAPI ListenThreadFunc(LPVOID pParam)
{
	
	CChatroomsDlg *pChatRooms = (CChatroomsDlg *)pParam;
	ASSERT(pChatRooms != NULL);
	pChatRooms->m_ListenSock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if ( pChatRooms->m_ListenSock == INVALID_SOCKET ) {
		AfxMessageBox(_T("新建Socket失败！"));
		return FALSE;
	}

	int iPort = pChatRooms->GetDlgItemInt(IDC_LISTEN_PORT);
	if ( iPort <= 0 || iPort > 65535 ) {
		AfxMessageBox(_T("请输入合适的端口：1 - 65535"));
		goto __Error_End;
	}

	sockaddr_in service;
	service.sin_family = AF_INET;
	service.sin_addr.s_addr = INADDR_ANY;
	service.sin_port = htons(iPort);

	if ( bind(pChatRooms->m_ListenSock, (sockaddr*)&service, sizeof(sockaddr_in)) == SOCKET_ERROR ) {
		AfxMessageBox(_T("绑定端口失败！"));
		goto __Error_End;
	}

	if( listen(pChatRooms->m_ListenSock, 5) == SOCKET_ERROR ) {
		AfxMessageBox(_T("监听失败！"));
		goto __Error_End;
	}
     pChatRooms->m_bIsServer=TRUE;
	 pChatRooms->GetDlgItem(IDC_START_SEVER)->EnableWindow(false);
	 pChatRooms->GetDlgItem(IDC_STOP_SEVER)->EnableWindow(true);
	while( TRUE&&!(pChatRooms->bShutDown) ) {
		if ( SOCKET_Select(pChatRooms->m_ListenSock, 100, TRUE) ) {
			sockaddr_in clientAddr;
			int iLen = sizeof(sockaddr_in);
			SOCKET accSock = accept(pChatRooms->m_ListenSock, (struct sockaddr *)&clientAddr , &iLen);
			if (accSock == INVALID_SOCKET) {
				continue;
			}
			CString strMsg;
		
			CClientItem tItem;
			tItem.m_Socket = accSock;
			tItem.m_pMainWnd = pChatRooms;
			tItem.m_strIp = inet_ntoa(clientAddr.sin_addr);
			strMsg = _T("客户端：") + tItem.m_strIp + _T(" 加入了聊天室！");
			tItem.m_pMainWnd->ShowMsg(strMsg);
			INT_PTR idx = pChatRooms->m_ClientArray.Add(tItem);
			tItem.hThread = CreateThread(NULL, 0, ClientThreadProc, &(pChatRooms->m_ClientArray.GetAt(idx)), CREATE_SUSPENDED, NULL);
			pChatRooms->m_ClientArray.ElementAt(idx).hThread = tItem.hThread;
			ResumeThread(tItem.hThread);

			Sleep(100);
		}
	}

__Error_End:
	closesocket(pChatRooms->m_ListenSock);
	return TRUE;
}
DWORD WINAPI ClientThreadProc(LPVOID lpParameter)
{
	CString strMsg;
	CClientItem m_ClientItem = *(CClientItem *)lpParameter;
	while( TRUE&&!(m_ClientItem.m_pMainWnd->bShutDown) ) {
		if ( SOCKET_Select(m_ClientItem.m_Socket, 100, TRUE) ) {
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(m_ClientItem.m_Socket, (char *)szBuf, MAX_BUF_SIZE, 0);
			if ( iRet > 0 ) {
				//right;
				strMsg.Format(_T("%s"), szBuf);
				strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(">") + strMsg;
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->SendClientsMsg(strMsg,&m_ClientItem);
			}else{
				//close socket;
				strMsg = _T("客户端：") + m_ClientItem.m_strIp + _T(" 离开了聊天室！");
				m_ClientItem.m_pMainWnd->ShowMsg(strMsg);
				m_ClientItem.m_pMainWnd->RemoveClientFromArray(m_ClientItem);
				break;
			}
		}
		Sleep(500);
	}
	return TRUE;
}
