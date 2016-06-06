// ConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Txt2Html.h"
#include "ConvertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConvertDlg dialog


CConvertDlg::CConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConvertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConvertDlg)
	m_strSrcFile = _T("");
	m_strDestFile = _T("");
	//}}AFX_DATA_INIT
}


void CConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConvertDlg)
	DDX_Text(pDX, IDC_EDIT_DESTFILE, m_strDestFile);
	DDX_Text(pDX, IDC_EDIT_SRCFILE, m_strSrcFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConvertDlg, CDialog)
	//{{AFX_MSG_MAP(CConvertDlg)
	ON_BN_CLICKED(IDC_BUTTON_SDEST, OnButtonSdest)
	ON_BN_CLICKED(IDC_BUTTON_SSRC, OnButtonSsrc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConvertDlg message handlers

void CConvertDlg::OnButtonSdest() 
{
	// TODO: Add your control notification handler code here
	
	CFileDialog oFileDlg(FALSE,_T("html"),NULL, 
	  OFN_HIDEREADONLY|OFN_EXPLORER|OFN_LONGNAMES|OFN_OVERWRITEPROMPT, _T(" Html Files (*.html) |*.html| All Files (*.*) |*.*||"));
	if(IDOK==oFileDlg.DoModal())
	{
		UpdateData(TRUE);			
		m_strDestFile=oFileDlg.GetPathName();
		UpdateData(FALSE);	
	}
	
}

void CConvertDlg::OnButtonSsrc() 
{
	// TODO: Add your control notification handler code here
	CFileDialog oFileDlg(TRUE,"txt",NULL, OFN_HIDEREADONLY|OFN_ENABLEHOOK|OFN_EXPLORER|OFN_LONGNAMES|OFN_FILEMUSTEXIST, _T(" Text Files (*.txt) |*.txt| All Files (*.*) |*.*||"));
	if(IDOK==oFileDlg.DoModal())
	{
		UpdateData(TRUE);	
				
		m_strSrcFile=oFileDlg.GetPathName();
		m_strDestFile=m_strSrcFile;
		
		m_strDestFile=m_strDestFile.Left(m_strDestFile.ReverseFind('.')+1);
		m_strDestFile+="html";
		UpdateData(FALSE);		
	}
}
