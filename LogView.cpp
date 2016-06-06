// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "txt2html.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogView

IMPLEMENT_DYNCREATE(CLogView, CListView)

CLogView::CLogView()
{
}

CLogView::~CLogView()
{
}


BEGIN_MESSAGE_MAP(CLogView, CListView)
	//{{AFX_MSG_MAP(CLogView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView drawing

void CLogView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CLogView diagnostics

#ifdef _DEBUG
void CLogView::AssertValid() const
{
	CListView::AssertValid();
}

void CLogView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

void CLogView::Add(CString szMsg, int iType)
{
	LV_ITEM lvi;
	int Index;
	char szType[10]="";
	char szContent[512]="";

	if(0==iType)
	{
		strcpy(szType,"³É¹¦");
	}else if(1==iType)
	{
		strcpy(szType,"Ê§°Ü");
	}
	strncpy(szContent,szMsg,511);

	CListCtrl& refCtrl = GetListCtrl();
	Index=refCtrl.GetItemCount();

	lvi.mask = LVIF_TEXT;
	lvi.iItem = Index;
	lvi.iSubItem = 0;
	lvi.pszText = szType;

	refCtrl.InsertItem(&lvi);

	lvi.iSubItem = 1;
	lvi.pszText = szContent;

	refCtrl.SetItem(&lvi);
}

BOOL CLogView::PreCreateWindow(CREATESTRUCT& cs) 
{
	// TODO: Add your specialized code here and/or call the base class
	cs.style|=LVS_REPORT; 
	return CListView::PreCreateWindow(cs);
}

#define NUM_COLUMNS 2

static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("×´Ì¬"), _T("ÄÚÈÝ")
};

static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_LEFT
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	50, 600
};

void CLogView::OnInitialUpdate() 
{
	CListView::OnInitialUpdate();
	
	CListCtrl& ListCtrl = GetListCtrl();
	// insert columns

	int i;
	LV_COLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;

	for(i = 0; i<NUM_COLUMNS; i++)
	{
		lvc.iSubItem = i;
		lvc.pszText = _gszColumnLabel[i];
		lvc.cx = _gnColumnWidth[i];
		lvc.fmt = _gnColumnFmt[i];
		ListCtrl.InsertColumn(i,&lvc);
	}
}
