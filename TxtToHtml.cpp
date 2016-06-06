// TxtToHtml.cpp: implementation of the CTxtToHtml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TxtToHtml.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTxtToHtml::CTxtToHtml()
{
	HFONT hFont;
	hFont=(HFONT)GetStockObject(SYSTEM_FONT);
	GetObject(hFont,sizeof(LOGFONT),&m_logfont);
	m_FontColor=0;
	m_BGColor=0x00FFFFFF;
}

CTxtToHtml::~CTxtToHtml()
{

}

bool CTxtToHtml::ConvertFile(const char *pszSrcFile, const char *pszDestFile)
{
	CStdioFile oTxtFile;
	CStdioFile oHtmlFile;
	if(TRUE!=oTxtFile.Open(pszSrcFile,CFile::modeRead | CFile::typeText))
	{
		return false;
	}
	if(TRUE!=oHtmlFile.Open(pszDestFile,CFile::modeCreate| CFile::modeWrite| CFile::typeText)) 
	{
		oTxtFile.Close();
		return false;
	}
	CString strLine;
	//写头
	oHtmlFile.WriteString("<HTML>\r\n");
	//标题
	m_Title="测试";
	strLine="<Title>";
	strLine+=m_Title+"</Title>";
	oHtmlFile.WriteString(strLine);
	oHtmlFile.WriteString("\r\n");
	
	strLine="<BODY bgColor=";
	strLine+=FormatColor(m_BGColor);
	strLine+=" leftMargin=40 link=#500000 vLink=#505050>\r\n";
	oHtmlFile.WriteString(strLine);
	
	//<FONT FACE="Verdana, Arial, Helvetica" SIZE=2>
	strLine="<FONT";
	strLine+=" FACE=";
	strLine+="\"";
	strLine+=m_logfont.lfFaceName;
	strLine+="\"";
	char czTemp[20]="";
	strLine+=" SIZE=";
	strLine+=itoa(HeightToSize(m_logfont.lfHeight),czTemp,10);//暂时这样
	strLine+=" Color=";
	strLine+="\"";
	strLine+=FormatColor(m_FontColor);
	strLine+="\"";
	oHtmlFile.WriteString(strLine);
	oHtmlFile.WriteString("\r\n");
	//主体
	
	while(oTxtFile.ReadString(strLine))
	{		
		//oHtmlFile.WriteString("<P>"+strLine);
		oHtmlFile.WriteString(strLine+"<br>");
		oHtmlFile.WriteString("\r\n");
	}
	oTxtFile.Close();

	//写尾
	oHtmlFile.WriteString("</FONT>\r\n");
	oHtmlFile.WriteString("</BODY>\r\n");
	oHtmlFile.WriteString("</HTML>\r\n");
	
	oHtmlFile.Close();
	return true;
}

void CTxtToHtml::ModifyFont()
{
	CFontDialog FontDialog(&m_logfont);
	FontDialog.m_cf.rgbColors=m_FontColor;
	if(IDOK==FontDialog.DoModal())
	{
		TRACE("%d\r\n",m_logfont.lfHeight);
		FontDialog.GetCurrentFont(&m_logfont);
		TRACE("%d\r\n",m_logfont.lfHeight);
		m_FontColor=FontDialog.GetColor();
	}
}

int CTxtToHtml::ConvertDir(const char *pszSrcDir, const char *pszDestDir)
{
	int iCount=0;
	CString strFilter = pszSrcDir;
	strFilter+=_T("\\*.txt");

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
				strSrcFile.Format("%s%s%s",pszSrcDir,_T("\\"),finddata.cFileName);
				strDestFile.Format("%s%s%s",pszDestDir, _T("\\"),finddata.cFileName);

				iCount+=ConvertDir(strSrcFile, strDestFile);
			}
		}else if(finddata.cFileName){
			strSrcFile.Format("%s%s%s",pszSrcDir,_T("\\"),finddata.cFileName);
			strDestFile.Format("%s%s%s",pszDestDir, _T("\\"),finddata.cFileName);

			int strDot=strDestFile.ReverseFind('.');
			strDestFile=strDestFile.Left(strDot)+_T(".html");
			if(ConvertFile(strSrcFile,strDestFile)==true)
			{
				iCount++;
			}
		}
		
	} while (FindNextFile(hFind, &finddata));

	FindClose(hFind);
	return iCount;
}
//转换字体高度为字体尺寸
int CTxtToHtml::HeightToSize(int Height)
{
	int iHeight=abs(Height);
	if(iHeight<=13)
	{
		return 1;
	}else if(iHeight<=18)
	{
		return 2;
	}else if(iHeight<=23)
	{
		return 3;
	}else if(iHeight<=27)
	{
		return 4;
	}else if(iHeight<=37)
	{
		return 5;
	}else if(iHeight<=43)
	{
		return 6;
	}else
	{
		return 7;
	}
}

CString CTxtToHtml::FormatColor(COLORREF rgbColor)
{
	CString szColor;
	BYTE byColor[4];
	memcpy(byColor,&rgbColor,4*sizeof(BYTE));
	szColor.Format("#%2x%02x%02x",byColor[0],byColor[1],byColor[2]);
	return szColor;
}

void CTxtToHtml::SetBGColor(COLORREF crColor)
{
	m_BGColor=crColor;
}

void CTxtToHtml::ModifyBGColor()
{
	CColorDialog ColorDialog(m_BGColor);
	if( IDOK==ColorDialog.DoModal())
	{
		m_BGColor=ColorDialog.GetColor();
	}
}
