#include "StdAfx.h"
#include "resource.h"
#include "chatroomsDlg.h"
#include "inc.h"



DWORD WINAPI ConnectThreadFunc(LPVOID pParam)
{
	CChatroomsDlg *pChatRooms = (CChatroomsDlg *)pParam;
	ASSERT(pChatRooms != NULL);
	pChatRooms->m_ConnectSock = socket(AF_INET , SOCK_STREAM , IPPROTO_TCP);
	if ( pChatRooms->m_ConnectSock == INVALID_SOCKET ) {
		AfxMessageBox(_T("�½�Socketʧ�ܣ�"));
		return FALSE;
	}
	CString strServIp;
	
	pChatRooms->GetDlgItemText(IDC_IP_ADDR, strServIp);
	int iPort = pChatRooms->GetDlgItemInt(IDC_CONNECT_PORT);
	if ( iPort <= 0 || iPort > 65535 ) {
		AfxMessageBox(_T("��������ʵĶ˿ڣ�1 - 65535"));
		closesocket(pChatRooms->m_ConnectSock);
	}
	int nLength=strServIp.GetLength();
	char* szIpAddr=new char[nLength];
	szIpAddr=strServIp.GetBuffer(0);
	//char szIpAddr[16] = {0};
	//USES_CONVERSION;
	//strcpy(szIpAddr, 16, T2A(strServIp));
	
	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(iPort);
	server.sin_addr.s_addr = inet_addr(szIpAddr);
	if ( connect(pChatRooms->m_ConnectSock, (struct sockaddr *)&server,  sizeof(struct sockaddr)) == SOCKET_ERROR ) {
		AfxMessageBox(_T("����ʧ�ܣ������ԣ�"));
	closesocket(pChatRooms->m_ConnectSock);
	pChatRooms->ShowMsg(_T("ϵͳ��Ϣ��δ�����ӷ�����������������Ƿ�����"));
	pChatRooms->GetDlgItem(IDC_STOP_CLIENT)->EnableWindow(false); 
	}
	else
	{
		pChatRooms->ShowMsg(_T("ϵͳ��Ϣ�����ӷ������ɹ���"));
		pChatRooms->GetDlgItem(IDC_START_CLIENT)->EnableWindow(false);
		pChatRooms->GetDlgItem(IDC_STOP_CLIENT)->EnableWindow(true);
		pChatRooms->SetWindowText(_T("chatrooms-client"));
	}
	pChatRooms->m_bIsServer=FALSE;
	
	while( TRUE&&!(pChatRooms->bShutDown) ) {
		if ( SOCKET_Select(pChatRooms->m_ConnectSock) ) {
			TCHAR szBuf[MAX_BUF_SIZE] = {0};
			int iRet = recv(pChatRooms->m_ConnectSock, (char *)szBuf, MAX_BUF_SIZE, 0);
			if ( iRet > 0 ) {
				//right;
				pChatRooms->ShowMsg(szBuf);
			}else{
				//close socket;
				pChatRooms->ShowMsg(_T("�����ҷ�������ֹͣ�������½������ӣ�"));
				pChatRooms->GetDlgItem(IDC_START_CLIENT)->EnableWindow(true);
				pChatRooms->GetDlgItem(IDC_STOP_CLIENT)->EnableWindow(false);
				break;
			}
		}
		Sleep(500);
	}
	
//__Error_End:
	
	return TRUE;
}