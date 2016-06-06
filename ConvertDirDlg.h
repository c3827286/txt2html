#if !defined(AFX_CONVERTDIRDLG_H__FFA8C11E_3874_4289_BC69_FACF243AB81F__INCLUDED_)
#define AFX_CONVERTDIRDLG_H__FFA8C11E_3874_4289_BC69_FACF243AB81F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConvertDirDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CConvertDirDlg dialog

class CConvertDirDlg : public CDialog
{
// Construction
public:
	CConvertDirDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CConvertDirDlg)
	enum { IDD = IDD_DLGCONVERTDIR };
	CString	m_strSrcDir;
	CString	m_strDestDir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConvertDirDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConvertDirDlg)
	afx_msg void OnButtonSdest();
	afx_msg void OnButtonSsrc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONVERTDIRDLG_H__FFA8C11E_3874_4289_BC69_FACF243AB81F__INCLUDED_)
