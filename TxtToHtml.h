// TxtToHtml.h: interface for the CTxtToHtml class.
//
//////////////////////////////////////////////////////////////////////

#ifndef _TXTTOHTML_H_
#define _TXTTOHTML_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTxtToHtml : public CObject  
{
public:
	CString		m_Title;
	LOGFONT		m_logfont;
	COLORREF    m_FontColor;//rgb
	COLORREF    m_BGColor;//rgb
public:
	void ModifyBGColor();
	void SetBGColor(COLORREF crColor);
	static CString FormatColor(COLORREF rgbColor);
	static int HeightToSize(int Height);
	int ConvertDir(const char *pszSrcDir, const char *pszDestDir);
	void ModifyFont();
	
	bool ConvertFile(const char* pszSrcFile,const char* pszDestFile);
	
	CTxtToHtml();
	virtual ~CTxtToHtml();

};

#endif 
