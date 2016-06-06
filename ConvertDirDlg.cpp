// ConvertDirDlg.cpp : implementation file
//

#include "stdafx.h"
#include "txt2html.h"
#include "ConvertDirDlg.h"
#include "FolderDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertDirDlg dialog


CConvertDirDlg::CConvertDirDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertDirDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvertDirDlg)
	m_strSrcDir = _T("");
	m_strDestDir = _T("");
	//}}AFX_DATA_INIT
}


void CConvertDirDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvertDirDlg)
	DDX_Text(pDX, IDC_EDIT_DESTDIR, m_strDestDir);
	DDX_Text(pDX, IDC_EDIT_SRCDIR, m_strSrcDir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvertDirDlg, CDialog)
	//{{AFX_MSG_MAP(CConvertDirDlg)
	ON_BN_CLICKED(IDC_BUTTON_SDEST, OnButtonSdest)
	ON_BN_CLICKED(IDC_BUTTON_SSRC, OnButtonSsrc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertDirDlg message handlers

void CConvertDirDlg::OnButtonSdest() 
{
	// TODO: Add your control notification handler code here
	
	CFolderDialog oFolderDlg;
	if(IDOK==oFolderDlg.DoModal())
	{
		UpdateData(TRUE);			
		m_strDestDir=oFolderDlg.GetPathName();
		UpdateData(FALSE);	
	}
	
}

void CConvertDirDlg::OnButtonSsrc() 
{
	// TODO: Add your control notification handler code here
	CFolderDialog oFolderDlg;
	if(IDOK==oFolderDlg.DoModal())
	{
		UpdateData(TRUE);	
				
		m_strSrcDir=oFolderDlg.GetPathName();
		m_strDestDir=m_strSrcDir;
				
		UpdateData(FALSE);		
	}
}
