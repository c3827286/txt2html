// Txt2HtmlDoc.cpp : implementation of the CTxt2HtmlDoc class
//

#include "stdafx.h"
#include "Txt2Html.h"

#include "Txt2HtmlDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlDoc

IMPLEMENT_DYNCREATE(CTxt2HtmlDoc, CDocument)

BEGIN_MESSAGE_MAP(CTxt2HtmlDoc, CDocument)
	//{{AFX_MSG_MAP(CTxt2HtmlDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlDoc construction/destruction

CTxt2HtmlDoc::CTxt2HtmlDoc()
{
	// TODO: add one-time construction code here

}

CTxt2HtmlDoc::~CTxt2HtmlDoc()
{
}

BOOL CTxt2HtmlDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlDoc serialization

void CTxt2HtmlDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlDoc diagnostics

#ifdef _DEBUG
void CTxt2HtmlDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTxt2HtmlDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlDoc commands
