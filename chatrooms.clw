; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CChatroomsDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "chatrooms.h"

ClassCount=3
Class1=CChatroomsApp
Class2=CChatroomsDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDR_MENU1
Resource2=IDR_MAINFRAME
Resource3=IDD_ABOUTBOX
Resource4=IDD_CHATROOMS_DIALOG
Resource5=IDR_MENU2

[CLS:CChatroomsApp]
Type=0
HeaderFile=chatrooms.h
ImplementationFile=chatrooms.cpp
Filter=N

[CLS:CChatroomsDlg]
Type=0
HeaderFile=chatroomsDlg.h
ImplementationFile=chatroomsDlg.cpp
Filter=D
BaseClass=CDialog
VirtualFilter=dWC
LastObject=IDC_NETSET

[CLS:CAboutDlg]
Type=0
HeaderFile=chatroomsDlg.h
ImplementationFile=chatroomsDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CHATROOMS_DIALOG]
Type=1
Class=CChatroomsDlg
ControlCount=22
Control1=IDC_STATIC,button,1342177287
Control2=IDC_SHOW_MSG,edit,1352730756
Control3=IDC_STATIC,button,1342177287
Control4=IDC_INPUT_MSG,edit,1350631552
Control5=IDC_STATIC,button,1342177287
Control6=IDC_NETSET,button,1342242816
Control7=IDC_SENDMSG,button,1342242816
Control8=IDC_SHUTDOWN,button,1342242816
Control9=IDC_OTHER,button,1342242816
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO_CLIENT,button,1342177289
Control12=IDC_SEVERIP,static,1342308352
Control13=IDC_IP_ADDR,SysIPAddress32,1342242816
Control14=IDC_CLISTENPORT,static,1342308352
Control15=IDC_CONNECT_PORT,edit,1350631552
Control16=IDC_START_CLIENT,button,1342242816
Control17=IDC_STOP_CLIENT,button,1342242816
Control18=IDC_RADIO_SEVER,button,1342177289
Control19=IDC_SLISTENPORT,static,1342308352
Control20=IDC_LISTEN_PORT,edit,1350631552
Control21=IDC_START_SEVER,button,1342242816
Control22=IDC_STOP_SEVER,button,1342242816

[MNU:IDR_MENU1]
Type=1
Class=CChatroomsDlg
Command1=ID_MENU_TRAYINCO
CommandCount=1

[MNU:IDR_MENU2]
Type=1
Class=?
Command1=ID_MENU_SHOW
Command2=ID_MENU_EXIT
CommandCount=2

