// chatrooms.h : main header file for the CHATROOMS application
//

#if !defined(AFX_CHATROOMS_H__41BB65EC_A15B_47E0_84EE_6F3A07996DD6__INCLUDED_)
#define AFX_CHATROOMS_H__41BB65EC_A15B_47E0_84EE_6F3A07996DD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChatroomsApp:
// See chatrooms.cpp for the implementation of this class
//

class CChatroomsApp : public CWinApp
{
public:
	CChatroomsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChatroomsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CChatroomsApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHATROOMS_H__41BB65EC_A15B_47E0_84EE_6F3A07996DD6__INCLUDED_)
