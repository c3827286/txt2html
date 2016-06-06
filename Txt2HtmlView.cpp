// Txt2HtmlView.cpp : implementation of the CTxt2HtmlView class
//

#include "stdafx.h"
#include "Txt2Html.h"

#include "Txt2HtmlDoc.h"
#include "Txt2HtmlView.h"
#include ".\txt2htmlview.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlView

IMPLEMENT_DYNCREATE(CTxt2HtmlView, CListView)

BEGIN_MESSAGE_MAP(CTxt2HtmlView, CListView)
	//{{AFX_MSG_MAP(CTxt2HtmlView)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CONVERT, OnConvert)
	ON_COMMAND(ID_CONVFILE, OnConvfile)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlView construction/destruction

CTxt2HtmlView::CTxt2HtmlView()
: m_szDir(_T(""))
{
	// TODO: add construction code here

}

CTxt2HtmlView::~CTxt2HtmlView()
{
}

BOOL CTxt2HtmlView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style|=LVS_REPORT; 
	
	return CListView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlView drawing

void CTxt2HtmlView::OnDraw(CDC* pDC)
{
	CTxt2HtmlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//CListCtrl& refCtrl = GetListCtrl();
	//refCtrl.InsertItem(0, "Item!");
	// TODO: add draw code for native data here
}

#define NUM_COLUMNS 3

static _TCHAR *_gszColumnLabel[NUM_COLUMNS] =
{
	_T("名称"), _T("大小"), _T("最后修改日期")
};

static int _gnColumnFmt[NUM_COLUMNS] =
{
	LVCFMT_LEFT, LVCFMT_LEFT, LVCFMT_LEFT
};

static int _gnColumnWidth[NUM_COLUMNS] =
{
	300, 60,60
};

void CTxt2HtmlView::OnInitialUpdate()
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

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlView diagnostics

#ifdef _DEBUG
void CTxt2HtmlView::AssertValid() const
{
	CListView::AssertValid();
}

void CTxt2HtmlView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CTxt2HtmlDoc* CTxt2HtmlView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTxt2HtmlDoc)));
	return (CTxt2HtmlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTxt2HtmlView message handlers
void CTxt2HtmlView::OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct)
{
	//TODO: add code to react to the user changing the view style of your window
}

void CTxt2HtmlView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	//GetParentFrame()->ActivateFrame();

	
	CMenu menu;
	if (menu.LoadMenu(IDR_POPUPFILE))
	{
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
							   point.x, point.y,
							   AfxGetMainWnd()); // route commands through main window
	}
}

// 更新目录
int CTxt2HtmlView::RefreshDir(const char * pszDir)
{
	int iCount=0;
	CString strFilter = pszDir;
	strFilter+=_T("\\*.txt");
	CListCtrl& refCtrl = GetListCtrl();
	refCtrl.DeleteAllItems();
	m_szDir=pszDir;

	WIN32_FIND_DATA finddata;
	HANDLE hFind = FindFirstFile(strFilter, &finddata);
	if (hFind==INVALID_HANDLE_VALUE)
		return 0;

	CString strSrcFile ;
	CString strDestFile ;
	do
	{
		if((finddata.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			//目录
			if(strcmp(finddata.cFileName,_T(".."))==0||strcmp(finddata.cFileName,_T("."))==0)
			{
			}else {
				AddItem(finddata);
			}
		}else if(finddata.cFileName){
			AddItem(finddata);			
		}
		
	} while (FindNextFile(hFind, &finddata));

	FindClose(hFind);
	return iCount;
}

void CTxt2HtmlView::AddItem(WIN32_FIND_DATA finddata)
{
	int Index=0;
	CListCtrl& refCtrl = GetListCtrl();
	Index=refCtrl.GetItemCount();

	LV_ITEM lvi;
	lvi.mask = LVIF_TEXT;
	lvi.iItem = Index;
	//lvi.iImage=
	lvi.iSubItem = 0;
	lvi.pszText = finddata.cFileName;

	refCtrl.InsertItem(&lvi);

	char szContent[512]="";
	sprintf(szContent,"%dKB",finddata.nFileSizeLow/1000);
	lvi.iSubItem = 1;
	lvi.pszText = szContent;
	refCtrl.SetItem(&lvi);

	CString strDate;
	CTime t(finddata.ftLastWriteTime);
	strDate = t.Format(_T("%Y-%m-%d %H:%M%S"));
	sprintf(szContent,"%s",strDate);

	lvi.iSubItem = 2;
	lvi.pszText = szContent;
	refCtrl.SetItem(&lvi);
}

void CTxt2HtmlView::OnConvert()
{
	
}

void CTxt2HtmlView::OnConvfile()
{
	CMainFrame* pMainFrame=(CMainFrame*)theApp.m_pMainWnd;
	CListCtrl& refCtrl = GetListCtrl();
	POSITION pos = refCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
	TRACE0("No items were selected!\n");
	else
	{
		while (pos)
		{
			int nItem = refCtrl.GetNextSelectedItem(pos);
			TRACE1("Item %d was selected!\n", nItem);
			// you could do your own processing on nItem here
			CString strSrcFile=m_szDir+"\\"+refCtrl.GetItemText(nItem,0);
			CString strDestFile=strSrcFile;
			int strDot=strDestFile.ReverseFind('.');
			strDestFile=strDestFile.Left(strDot)+_T(".html");

			pMainFrame->oTxtToHtml.ConvertFile(strSrcFile,strDestFile);
		}
	}
}
