// LeftView.h : interface of the CLeftView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEFTVIEW_H__CB5180E1_EC63_4D9A_BAEE_5AD5210C7488__INCLUDED_)
#define AFX_LEFTVIEW_H__CB5180E1_EC63_4D9A_BAEE_5AD5210C7488__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTxt2HtmlDoc;

class CLeftView : public CTreeView
{
protected: // create from serialization only
	CLeftView();
	DECLARE_DYNCREATE(CLeftView)

// Attributes
public:
	CTxt2HtmlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLeftView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:	
	HTREEITEM InsertItem( LPCTSTR lpszItem, int nImage, int nSelectedImage, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
	BOOL DeleteItem( HTREEITEM hItem );
	CImageList* SetImageList( CImageList * pImageList, int nImageListType );
	CImageList* GetImageList( UINT nImage );
	HTREEITEM GetNextItem( HTREEITEM hItem, UINT nCode );
	HTREEITEM GetChildItem( HTREEITEM hItem );
	BOOL DeleteAllItems( );
	HTREEITEM GetParentItem( HTREEITEM hItem );
	CString GetItemText( HTREEITEM hItem ) const;
	BOOL SelectItem( HTREEITEM hItem );
	HTREEITEM InsertItem( LPCTSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST );
	BOOL Expand( HTREEITEM hItem, UINT nCode );
	UINT GetItemState( HTREEITEM hItem, UINT nStateMask ) const;
	BOOL DisplayDrives();
	BOOL DisplayTree( LPCTSTR strRoot, BOOL bFiles = FALSE );
	LPCTSTR GetSubPath( LPCTSTR strPath );
	CString GetFullPath( HTREEITEM hItem );
	BOOL SetSelPath( LPCTSTR strPath );
	virtual ~CLeftView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	BOOL m_bFiles;
	CString m_strError;
	CImageList m_imgList;
	CString m_strRoot;
// Generated message map functions
protected:
	BOOL GetSysImgList();
	void DisplayPath( HTREEITEM hParent, LPCTSTR strPath );
	BOOL FindSubDir( LPCTSTR strPath );
	HTREEITEM AddItem( HTREEITEM hParent, LPCTSTR strPath );
	HTREEITEM SearchSiblingItem( HTREEITEM hItem, LPCTSTR strText );
	void ExpandItem( HTREEITEM hItem, UINT nCode );
	BOOL IsValidPath( LPCTSTR strPath );
	//{{AFX_MSG(CLeftView)
		afx_msg void OnItemexpanded(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnRclick(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnConvert();
	afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);
};

#ifndef _DEBUG  // debug version in LeftView.cpp
inline CTxt2HtmlDoc* CLeftView::GetDocument()
   { return (CTxt2HtmlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LEFTVIEW_H__CB5180E1_EC63_4D9A_BAEE_5AD5210C7488__INCLUDED_)
