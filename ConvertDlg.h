#if !defined(AFX_CONVERTDLG_H__13E4F69A_C027_4E55_B5F3_C53C8D1A0A94__INCLUDED_)
#define AFX_CONVERTDLG_H__13E4F69A_C027_4E55_B5F3_C53C8D1A0A94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConvertDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvertDlg dialog

class CConvertDlg : public CDialog
{
// Construction
public:
	CConvertDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConvertDlg)
	enum { IDD = IDD_DLGCONVERT };
	CString	m_strSrcFile;
	CString	m_strDestFile;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvertDlg)
	afx_msg void OnButtonSdest();
	afx_msg void OnButtonSsrc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERTDLG_H__13E4F69A_C027_4E55_B5F3_C53C8D1A0A94__INCLUDED_)
