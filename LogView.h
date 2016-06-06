#if !defined(AFX_LOGVIEW_H__CC8ED00D_3B05_4EFB_A6D9_6C0FE84E4D36__INCLUDED_)
#define AFX_LOGVIEW_H__CC8ED00D_3B05_4EFB_A6D9_6C0FE84E4D36__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogView view

class CLogView : public CListView
{
protected:
	CLogView();           // protected constructor used by dynamic creation
	DECLARE_DYNCREATE(CLogView)

// Attributes
public:

// Operations
public:
	void Add(CString szMsg,int iType);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogView)
	public:
	virtual void OnInitialUpdate();
	protected:
	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:
	//{{AFX_MSG(CLogView)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGVIEW_H__CC8ED00D_3B05_4EFB_A6D9_6C0FE84E4D36__INCLUDED_)
