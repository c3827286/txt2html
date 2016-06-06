// LeftView.cpp : implementation of the CLeftView class
//

#include "stdafx.h"
#include "Txt2Html.h"

#include "Txt2HtmlDoc.h"
#include "LeftView.h"
#include "SortStringArray.h"
#include ".\leftview.h"
#include "MainFrm.h"
#include "Txt2HtmlView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLeftView

IMPLEMENT_DYNCREATE(CLeftView, CTreeView)

BEGIN_MESSAGE_MAP(CLeftView, CTreeView)
	//{{AFX_MSG_MAP(CLeftView)
	ON_NOTIFY_REFLECT(TVN_ITEMEXPANDED, OnItemexpanded)
	ON_WM_CONTEXTMENU()
	ON_NOTIFY_REFLECT(NM_RCLICK, OnRclick)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_CONVERT, OnConvert)
	ON_NOTIFY_REFLECT(TVN_SELCHANGED, OnTvnSelchanged)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLeftView construction/destruction

CLeftView::CLeftView()
{
	// TODO: add construction code here
	m_strRoot = "";      // Auf Leer setzen
}

CLeftView::~CLeftView()
{
	m_imgList.Detach();
}

BOOL CLeftView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CTreeView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView drawing

void CLeftView::OnDraw(CDC* pDC)
{
	CTxt2HtmlDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


void CLeftView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();
	
	DisplayTree("",true);
	// TODO: You may populate your TreeView with items by directly accessing
	//  its tree control through a call to GetTreeCtrl().
}

/////////////////////////////////////////////////////////////////////////////
// CLeftView diagnostics

#ifdef _DEBUG
void CLeftView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CLeftView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTxt2HtmlDoc* CLeftView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTxt2HtmlDoc)));
	return (CTxt2HtmlDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CLeftView message handlers

BOOL CLeftView::SetSelPath(LPCTSTR strPath)
{
	// Setting the Selection in the Tree
	HTREEITEM hParent  = TVI_ROOT;
	int       iLen    = strlen(strPath) + 2;
	char*     pszPath = new char[iLen];
	char*     pPath   = pszPath;
	BOOL      bRet    = FALSE;
    
	if ( !IsValidPath( strPath ) )
	{
		delete [] pszPath; // this must be added 29.03.99
		return FALSE;
	}
		
	strcpy( pszPath, strPath );
	strupr( pszPath );
	
	if ( pszPath[strlen(pszPath)-1] != '\\' )
		strcat( pszPath, "\\" );
    
	int iLen2 = strlen( pszPath );
	
	for (WORD i = 0; i < iLen2; i++ )
	{
		if ( pszPath[i] == '\\' )
		{
			SetRedraw( FALSE );
			pszPath[i] = '\0';
			hParent = SearchSiblingItem( hParent, pPath );
			if ( !hParent )  // Not found!
				break;
			else
			{				
				// Info:
				// the notification OnItemExpanded 
				// will not called every time 
				// after the call Expand. 
				// You must call Expand with TVE_COLLAPSE | TVE_COLLAPSERESET
				// to Reset the TVIS_EXPANDEDONCE Flag
				
				UINT uState;
				uState = GetItemState( hParent, TVIS_EXPANDEDONCE );
				if ( uState )
				{
					Expand( hParent, TVE_EXPAND );
					Expand( hParent, TVE_COLLAPSE | TVE_COLLAPSERESET );
					InsertItem("", hParent ); // insert a blank child-item
					Expand( hParent, TVE_EXPAND ); // now, expand send a notification
				}
				else
					Expand( hParent, TVE_EXPAND );
			}
			pPath += strlen(pPath) + 1;
		}
	}

	delete [] pszPath;
	
	if ( hParent ) // Ok the last subpath was found
	{		
		SelectItem( hParent ); // select the last expanded item
		bRet = TRUE;
	}
	else
	{
		bRet = FALSE;
	}
	
	SetRedraw( TRUE );

    return bRet;
}

CString CLeftView::GetFullPath(HTREEITEM hItem)
{
	// get the Full Path of the item
	CString strReturn;
	CString strTemp;
	HTREEITEM hParent = hItem;

	strReturn = "";

	while ( hParent )
	{
		
		strTemp  = GetItemText( hParent );
		strTemp += "\\";
		strReturn = strTemp + strReturn;
		hParent = GetParentItem( hParent );
	}
    
	strReturn.TrimRight( '\\' );

    return strReturn;
}

LPCTSTR CLeftView::GetSubPath(LPCTSTR strPath)
{
	//
	// getting the last SubPath from a PathString
	// e.g. C:\temp\readme.txt
	// the result = readme.txt
	static CString strTemp;
	int     iPos;

	strTemp = strPath;
	if ( strTemp.Right(1) == '\\' )
		 strTemp.SetAt( strTemp.GetLength() - 1, '\0' );
	iPos = strTemp.ReverseFind( '\\' );
	if ( iPos != -1 )
	    strTemp = strTemp.Mid( iPos + 1);

	return (LPCTSTR)strTemp;
}

BOOL CLeftView::DisplayTree(LPCTSTR strRoot, BOOL bFiles)
{
	DWORD dwStyle = GetStyle();   // read the windowstyle
	if ( dwStyle & TVS_EDITLABELS ) 
	{
		// Don't allow the user to edit ItemLabels
		ModifyStyle( TVS_EDITLABELS , 0 );
	}
	
	// Display the DirTree with the Rootname e.g. C:\
	// if Rootname == NULL then Display all Drives on this PC
    // First, we need the system-ImageList
	
	DeleteAllItems();

	if ( !GetSysImgList() )
		return FALSE;
    m_bFiles = bFiles;  // if TRUE, Display Path- and Filenames 
	if ( strRoot == NULL || strRoot[0] == '\0' )
	{
		if ( !DisplayDrives() )
			return FALSE;
		m_strRoot = "";
	}
    else
	{
		m_strRoot = strRoot;
		if ( m_strRoot.Right(1) != '\\' )
			m_strRoot += "\\";
		HTREEITEM hParent = AddItem( TVI_ROOT, m_strRoot );
		DisplayPath( hParent, strRoot );
	}
	return TRUE;
}

BOOL CLeftView::IsValidPath(LPCTSTR strPath)
{
	// This function check the Pathname
	
	HTREEITEM hChild;
	CString   strItem;
	CString   strTempPath = strPath;
	BOOL      bFound = FALSE;
	CFileFind find;

	hChild = GetChildItem( TVI_ROOT );
	strTempPath.MakeUpper();
	strTempPath.TrimRight('\\');

	while ( hChild )
	{
		strItem = GetItemText( hChild );
		strItem.MakeUpper();
		if ( strItem == strTempPath.Mid( 0, strItem.GetLength() ) )
		{
			bFound = TRUE;
			break;
		}
		hChild = GetNextItem( hChild, TVGN_NEXT );
	}
    
	if ( !bFound )
		return FALSE;

	strTempPath += "\\nul";
	if ( find.FindFile( strTempPath ) )
		return TRUE;
     
	return FALSE;
}

void CLeftView::ExpandItem(HTREEITEM hItem, UINT nCode)
{
	CString strPath;
	
	if ( nCode == TVE_EXPAND )
	{
		HTREEITEM hChild = GetChildItem( hItem );
		while ( hChild )
		{
			DeleteItem( hChild );
			hChild = GetChildItem( hItem );
		}
        
		strPath = GetFullPath( hItem );
		DisplayPath( hItem, strPath );
	}
}

HTREEITEM CLeftView::SearchSiblingItem(HTREEITEM hItem, LPCTSTR strText)
{
	HTREEITEM hFound = GetChildItem( hItem );
	CString   strTemp;
	while ( hFound )
	{
		strTemp = GetItemText( hFound );
        strTemp.MakeUpper();
		if ( strTemp == strText )
			return hFound;
		hFound = GetNextItem( hFound, TVGN_NEXT );
	}

	return NULL;
}

BOOL CLeftView::FindSubDir(LPCTSTR strPath)
{
	//
	// Are there subDirs ?
	//
	CFileFind find;
	CString   strTemp = strPath;
	BOOL      bFind;

	if ( strTemp[strTemp.GetLength()-1] == '\\' )
		strTemp += "*.*";
	else
		strTemp += "\\*.*";
		
	bFind = find.FindFile( strTemp );
	
	
	while ( bFind )
	{
		bFind = find.FindNextFile();

		if ( find.IsDirectory() && !find.IsDots() )
		{
			return TRUE;
		}
		if ( !find.IsDirectory() && m_bFiles && !find.IsHidden() )
			return TRUE;
		
	}

	return FALSE;
}

HTREEITEM CLeftView::AddItem(HTREEITEM hParent, LPCTSTR strPath)
{
	// Adding the Item to the TreeCtrl with the current Icons
	SHFILEINFO shFinfo;
	int iIcon, iIconSel;
    CString    strTemp = strPath;
    
	if ( strTemp.Right(1) != '\\' )
		 strTemp += "\\";
	if ( !SHGetFileInfo( strTemp,
						0,
						&shFinfo,
						sizeof( shFinfo ),
						SHGFI_ICON | 
					    SHGFI_SMALLICON ) )
	{
		m_strError = "Error Gettting SystemFileInfo!";
		return NULL;
	}

	iIcon = shFinfo.iIcon;

	// we only need the index from the system image list

	DestroyIcon( shFinfo.hIcon );

	if ( !SHGetFileInfo( strTemp,
						0,
						&shFinfo,
						sizeof( shFinfo ),
						SHGFI_ICON | SHGFI_OPENICON |
					    SHGFI_SMALLICON ) )
	{
		m_strError = "Error Gettting SystemFileInfo!";
		return NULL;
	}

	iIconSel = shFinfo.iIcon;

	// we only need the index of the system image list

	DestroyIcon( shFinfo.hIcon );

	if ( strTemp.Right(1) == "\\" )
		strTemp.SetAt( strTemp.GetLength() - 1, '\0' );
	
	if ( hParent == TVI_ROOT )
		return InsertItem( strTemp, iIcon, iIconSel, hParent );
	
	return InsertItem( GetSubPath( strTemp ), iIcon, iIconSel, hParent );
}

void CLeftView::DisplayPath(HTREEITEM hParent, LPCTSTR strPath)
{
	//
	// Displaying the Path in the TreeCtrl
	//
	CFileFind find;
	CString   strPathFiles = strPath;
	BOOL      bFind;
	CSortStringArray strDirArray;
	CSortStringArray strFileArray;
	
	if ( strPathFiles.Right(1) != "\\" )
		strPathFiles += "\\";
	strPathFiles += "*.*";

	bFind = find.FindFile( strPathFiles );

	while ( bFind )
	{
		bFind = find.FindNextFile();
		if ( find.IsDirectory() && !find.IsDots() )
		{		
			strDirArray.Add( find.GetFilePath() );
		}
		/*  //xcy ע
		if ( !find.IsDirectory() && m_bFiles )
			strFileArray.Add( find.GetFilePath() );
		*/
	}
    
	strDirArray.Sort();
	SetRedraw( FALSE );
	CWaitCursor wait;
    
	for ( int i = 0; i < strDirArray.GetSize(); i++ )
	{
			HTREEITEM hItem = AddItem( hParent, strDirArray.GetAt(i) );
			if ( FindSubDir( strDirArray.GetAt(i) ) )
				InsertItem( "", 0, 0, hItem );
	}

	if ( m_bFiles )
	{
		strFileArray.Sort();
		for ( i = 0; i < strFileArray.GetSize(); i++ )
		{
			HTREEITEM hItem = AddItem( hParent, strFileArray.GetAt(i) );
			
		}
	}
    
	SetRedraw( TRUE );
}

BOOL CLeftView::DisplayDrives()
{
	//
	// Displaying the Availible Drives on this PC
	// This are the First Items in the TreeCtrl
	//
	DeleteAllItems();
	char  szDrives[128];
	char* pDrive;

	if ( !GetLogicalDriveStrings( sizeof(szDrives), szDrives ) )
	{
		m_strError = "Error Getting Logical DriveStrings!";
		return FALSE;
	}

	pDrive = szDrives;
	while( *pDrive )
	{
		HTREEITEM hParent = AddItem( TVI_ROOT, pDrive );
		if ( FindSubDir( pDrive ) )
			InsertItem( "", 0, 0, hParent );
		pDrive += strlen( pDrive ) + 1;
	}


	return TRUE;
}

BOOL CLeftView::GetSysImgList()
{
	SHFILEINFO shFinfo;
	HIMAGELIST hImgList = NULL;

	if ( GetImageList( TVSIL_NORMAL ) )
		m_imgList.Detach();
	
	hImgList = (HIMAGELIST)SHGetFileInfo( "C:\\",
							  0,
							  &shFinfo,
							  sizeof( shFinfo ),
							  SHGFI_SYSICONINDEX | 
							  SHGFI_SMALLICON );
	if ( !hImgList )
	{
		m_strError = "Cannot retrieve the Handle of SystemImageList!";
		return FALSE;
	}

	m_imgList.m_hImageList = hImgList;    
    
	SetImageList( &m_imgList, TVSIL_NORMAL );
	return TRUE;   // OK
}

void CLeftView::OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	CString strPath;
	 
	if ( pNMTreeView->itemNew.state & TVIS_EXPANDED )
	{
		//UINT uTest = TVIS_EXPANDEDONCE;
		ExpandItem( pNMTreeView->itemNew.hItem, TVE_EXPAND );
	    /*
		//
		// Delete All items
		// And display the subpath
		//
		HTREEITEM hChild = GetChildItem( pNMTreeView->itemNew.hItem );
		while ( hChild )
		{
			DeleteItem( hChild );
			hChild = GetChildItem( pNMTreeView->itemNew.hItem );
		}
        
		strPath = GetFullPath( pNMTreeView->itemNew.hItem );
		DisplayPath( pNMTreeView->itemNew.hItem, strPath );
		*/
	}
	else
	{
		//
		// Delete the Items, but leave one there, for 
		// expanding the item next time
		//
		HTREEITEM hChild = GetChildItem( pNMTreeView->itemNew.hItem );
				
		while ( hChild ) 
		{
			DeleteItem( hChild );
			hChild = GetChildItem( pNMTreeView->itemNew.hItem );
		}
		InsertItem( "", pNMTreeView->itemNew.hItem );
	}

	*pResult = 0;
}

UINT CLeftView::GetItemState(HTREEITEM hItem, UINT nStateMask) const
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetItemState(hItem, nStateMask);
}

BOOL CLeftView::Expand(HTREEITEM hItem, UINT nCode)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.Expand(hItem, nCode);
}

HTREEITEM CLeftView::InsertItem(LPCTSTR lpszItem, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.InsertItem(lpszItem, hParent, hInsertAfter);
}

BOOL CLeftView::SelectItem(HTREEITEM hItem)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.SelectItem(hItem);
}

CString CLeftView::GetItemText(HTREEITEM hItem) const
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetItemText(hItem);
}

HTREEITEM CLeftView::GetParentItem(HTREEITEM hItem)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetParentItem(hItem);
}

BOOL CLeftView::DeleteAllItems()
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.DeleteAllItems();
}

HTREEITEM CLeftView::GetChildItem(HTREEITEM hItem)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetChildItem(hItem);
}

HTREEITEM CLeftView::GetNextItem(HTREEITEM hItem, UINT nCode)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetNextItem(hItem,nCode);
}

CImageList* CLeftView::GetImageList(UINT nImage)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.GetImageList(nImage);
}

CImageList* CLeftView::SetImageList(CImageList *pImageList, int nImageListType)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.SetImageList(pImageList,nImageListType);
}

BOOL CLeftView::DeleteItem(HTREEITEM hItem)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.DeleteItem(hItem);
}

HTREEITEM CLeftView::InsertItem(LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent, HTREEITEM hInsertAfter)
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	return TreeCtrl.InsertItem(lpszItem, nImage, nSelectedImage, hParent, hInsertAfter);
}

BOOL CLeftView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	dwStyle|=TVS_HASLINES|TVS_LINESATROOT|TVS_HASBUTTONS;
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

void CLeftView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	CMenu menu;
	if (menu.LoadMenu(IDR_POPUP))
	{
		TRACE("OnContextMenu");
		CMenu* pPopup = menu.GetSubMenu(0);
		ASSERT(pPopup != NULL);

		pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
							   point.x, point.y,
							   AfxGetMainWnd()); // route commands through main window
	}
}

void CLeftView::OnRclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CTreeCtrl& TreeCtrl=GetTreeCtrl();

	HTREEITEM hItem;
	CPoint point,cpt;
	if ( GetCursorPos( &point ) )
	{
		cpt=point;
		ScreenToClient(&cpt);
		UINT nFlags;
		hItem=TreeCtrl.HitTest(cpt, &nFlags);
		if( hItem!=NULL )
		{	
			SelectItem(hItem);
			CMenu menu;
			if (menu.LoadMenu(IDR_POPUP))
			{
				TRACE("OnContextMenu");
				CMenu* pPopup = menu.GetSubMenu(0);
				ASSERT(pPopup != NULL);

				pPopup->TrackPopupMenu(TPM_RIGHTBUTTON | TPM_LEFTALIGN,
									   point.x, point.y,
									   AfxGetMainWnd()); // route commands through main window
			}
		}
	}
	*pResult = 0;
}

void CLeftView::OnConvert()
{
	CMainFrame* pMainFrame=(CMainFrame*)theApp.m_pMainWnd;
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	CString strDir=GetFullPath(TreeCtrl.GetSelectedItem());
	pMainFrame->oTxtToHtml.ConvertDir(strDir,strDir);
}

void CLeftView::OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

	CMainFrame* pMainFrame=(CMainFrame*)theApp.m_pMainWnd;
	CTxt2HtmlView* pFileView=pMainFrame->GetFileView();
	CTreeCtrl& TreeCtrl=GetTreeCtrl();
	CString strDir=GetFullPath(TreeCtrl.GetSelectedItem());
	pFileView->RefreshDir(strDir);

	*pResult = 0;
}
