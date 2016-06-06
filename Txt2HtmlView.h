// Txt2HtmlView.h : interface of the CTxt2HtmlView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TXT2HTMLVIEW_H__17D7D4D2_0673_47D0_98AD_8A4BA551055D__INCLUDED_)
#define AFX_TXT2HTMLVIEW_H__17D7D4D2_0673_47D0_98AD_8A4BA551055D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTxt2HtmlView : public CListView
{
protected: // create from serialization only
	CTxt2HtmlView();
	DECLARE_DYNCREATE(CTxt2HtmlView)

// Attributes
public:
	CTxt2HtmlDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxt2HtmlView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTxt2HtmlView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTxt2HtmlView)
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	//}}AFX_MSG
	afx_msg void OnStyleChanged(int nStyleType, LPSTYLESTRUCT lpStyleStruct);
	DECLARE_MESSAGE_MAP()
public:
	// ¸üÐÂÄ¿Â¼
	int RefreshDir(const char * pszDir);
	void AddItem(WIN32_FIND_DATA finddata);
	afx_msg void OnConvert();
protected:
	CString m_szDir;
public:
	afx_msg void OnConvfile();
};

#ifndef _DEBUG  // debug version in Txt2HtmlView.cpp
inline CTxt2HtmlDoc* CTxt2HtmlView::GetDocument()
   { return (CTxt2HtmlDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXT2HTMLVIEW_H__17D7D4D2_0673_47D0_98AD_8A4BA551055D__INCLUDED_)
