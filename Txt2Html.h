// Txt2Html.h : main header file for the TXT2HTML application
//

#if !defined(AFX_TXT2HTML_H__CE32CCE1_FBA2_43F0_9E35_B80D23FEB445__INCLUDED_)
#define AFX_TXT2HTML_H__CE32CCE1_FBA2_43F0_9E35_B80D23FEB445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlApp:
// See Txt2Html.cpp for the implementation of this class
//

class CTxt2HtmlApp : public CWinApp
{
public:
	void AddLog(CString szMsg, int iType);
	CTxt2HtmlApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxt2HtmlApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTxt2HtmlApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

extern CTxt2HtmlApp theApp;
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXT2HTML_H__CE32CCE1_FBA2_43F0_9E35_B80D23FEB445__INCLUDED_)
