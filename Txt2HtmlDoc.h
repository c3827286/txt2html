// Txt2HtmlDoc.h : interface of the CTxt2HtmlDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TXT2HTMLDOC_H__0F0F09FC_D8C8_42BF_8CFD_76B44ACCF818__INCLUDED_)
#define AFX_TXT2HTMLDOC_H__0F0F09FC_D8C8_42BF_8CFD_76B44ACCF818__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CTxt2HtmlDoc : public CDocument
{
protected: // create from serialization only
	CTxt2HtmlDoc();
	DECLARE_DYNCREATE(CTxt2HtmlDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTxt2HtmlDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTxt2HtmlDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTxt2HtmlDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TXT2HTMLDOC_H__0F0F09FC_D8C8_42BF_8CFD_76B44ACCF818__INCLUDED_)
