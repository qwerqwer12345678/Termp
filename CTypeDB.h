#pragma once

#include "afxdialogex.h"
#include <locale.h>
#include "pch.h"
#include "framework.h"
#include "Termp.h"
#include "TermpDlg.h"


using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

struct SCharInfo
{
	CString m_char;
	int m_type, m_sheet, m_sx, m_sy, m_line, m_order, m_width, m_height;
};

class CTypeDB
{
public:
	int m_nSheet; 
	int m_nChar = m_Chars.GetSize();
	CArray<SCharInfo*, SCharInfo*> m_Chars;
	inline BOOL ReadCSVFile(CString filename);
	inline void    RemoveAll();
};

void CTypeDB::RemoveAll()
{
	for (int i = 0; i < m_Chars.GetSize(); ++i)
	{
		SCharInfo* pSCharInfo = m_Chars.GetAt(i);
		if (NULL == pSCharInfo)
			continue;
		delete pSCharInfo;

		pSCharInfo = NULL;
	}
	m_Chars.RemoveAll();
}


BOOL CTypeDB::ReadCSVFile(CString filename)
{
	RemoveAll();

	if (filename == _T("C:\\월인천강지곡 권상\\typeDB.csv"))
	{
		_tsetlocale(LC_ALL, "Korean");

		CString strFilePath = _T("");
		strFilePath.Format(filename);

		FILE* fp = NULL;
		fopen_s(&fp, strFilePath, "r");
		if (fp)
		{
			char szContent[2048] = { 0, };
			memset(szContent, NULL, 2048);

			while (fgets(szContent, 2048, fp))
			{
				CString strContent;
				strContent.Format("%s", szContent);
				memset(szContent, NULL, 2048);

				if (strContent.Find("#") >= 0) //만약 csv 파일 안의 데이터 중 #이 있으면 건너 뛰어라
					continue;
				if (strContent.Find("char") >= 0)
					continue;

				strContent.Remove('\r');
				strContent.Remove('\n');

				strContent = _T(strContent); //유니코드 변환하여 저장
				SCharInfo* pSCharInfo = new SCharInfo;
				CString rString;
				int nSubString = 0;

				while (AfxExtractSubString(rString, strContent, nSubString++, ','))
				{
					switch (nSubString)
					{
					case 1: pSCharInfo->m_char = _T(rString); break;
					case 2: pSCharInfo->m_type = _ttoi(rString); break;
					case 3: pSCharInfo->m_sheet = _ttoi(rString); break;
					case 4: pSCharInfo->m_sx = _ttoi(rString); break;
					case 5: pSCharInfo->m_sy = _ttoi(rString); break;
					case 6: pSCharInfo->m_line = _ttoi(rString); break;
					case 7: pSCharInfo->m_order = _ttoi(rString); break;
					case 8: pSCharInfo->m_width = _ttoi(rString); break;
					case 9: pSCharInfo->m_height = _ttoi(rString); break;
					}
				}
				m_Chars.Add(pSCharInfo);
			}
			fclose(fp);
		}
		return TRUE;
	}
	else
		return FALSE;
}