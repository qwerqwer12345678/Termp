
// TermpDlg.cpp: 구현 파일
//


#include "pch.h"
#include "framework.h"
#include "Termp.h"
#include "TermpDlg.h"
#include "afxdialogex.h"
#include "CTypeDB.h"
#include "opencv2/opencv.hpp"
#include <string>

#include <vtkLight.h>
#include <vtkSTLReader.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTermpDlg 대화 상자


CTermpDlg::CTermpDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TERMP_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

}

void CTermpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC1, m_static1);
	DDX_Control(pDX, IDC_STATIC2, m_static2);
	DDX_Control(pDX, IDC_STATIC3, m_static3);
	DDX_Control(pDX, IDC_STATIC4, m_static4);
	DDX_Control(pDX, IDC_STATIC5, m_static5);
	DDX_Control(pDX, IDC_STATIC6, m_static6);
	DDX_Control(pDX, IDC_PIC, m_pic1);
	DDX_Control(pDX, IDC_SPIN1, m_spin1);
	DDX_Control(pDX, IDC_STATIC9, m_static9);
	DDX_Control(pDX, IDC_STATIC10, m_static10);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_STATIC8, m_static8);
	DDX_Control(pDX, IDC_EDIT2, m_edit2);
	DDX_Control(pDX, IDC_PIC2, m_pic2);
	DDX_Control(pDX, IDC_STATIC_FRAME, m_VTK);
	DDX_Control(pDX, IDC_LIST2, m_list);
	DDX_Control(pDX, IDC_BUTTON1, m_bitmapbutton);
	DDX_Control(pDX, IDC_PIC3, m_pic3);
	DDX_Control(pDX, IDC_STATIC11, m_static11);
	DDX_Control(pDX, IDC_SPIN2, m_spin2);
	DDX_Control(pDX, IDC_EDIT3, m_edit3);
}

BEGIN_MESSAGE_MAP(CTermpDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTermpDlg::OnBnClickedButton1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &CTermpDlg::OnDeltaposSpin1)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &CTermpDlg::OnDeltaposSpin2)
	ON_NOTIFY(NM_CLICK, IDC_LIST2, &CTermpDlg::OnNMClickList2)
//	ON_NOTIFY(NM_SETFOCUS, IDC_LIST2, &CTermpDlg::OnNMSetfocusList2)
END_MESSAGE_MAP()


//-----------------------------------전역변수----------------------------------------
//-----------------------------------전역변수----------------------------------------
bool TF;
int presentPos, presentPos2;
int old_i;
int sheet1 = 0, sheet2 = 0, sheet3 = 0, skcount1 = 0, skcount2 = 0, skcount3 = 0, stcount1 = 0, stcount2 = 0, stcount3 = 0;
int idx1;
int idx2;
CString stl1 = _T("C:\\04_3d\\");
CString stl2 = _T(".stl");
CString stl0 = _T("000000000000.stl");
CString load1 = _T("C:\\월인천강지곡 권상\\03_type\\");
CString load2 = _T("\\");
CString load3 = _T("_");
CString load4 = _T(".png");
CString load;
CString loadtp;

//---------------------------------CTermpDlg 메시지 처리기----------------------------
//---------------------------------CTermpDlg 메시지 처리기----------------------------
BOOL CTermpDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.
	DWORD cs = ::GetWindowLong(m_hWnd, GWL_STYLE);
	cs &= ~WS_THICKFRAME;
	::SetWindowLongA(m_hWnd, GWL_STYLE, cs);
	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	

	CRect list;
	m_list.GetClientRect(&list);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVIS_SELECTED | LVIS_FOCUSED);
	m_list.InsertColumn(0, _T("장"), LVCFMT_CENTER, list.Width() * 0.22);
	m_list.InsertColumn(1, _T("X"), LVCFMT_CENTER, list.Width()  * 0.33);
	m_list.InsertColumn(2, _T("Y"), LVCFMT_CENTER, list.Width() * 0.33);

	if (this->GetDlgItem(IDC_STATIC_FRAME))
	{
		this->InitVtkWindow(this->GetDlgItem(IDC_STATIC_FRAME)->GetSafeHwnd());
		this->ResizeVtkWindow();
	}
	CString stl = stl1 + stl0;
	STLReader(stl);

	m_bitmapbutton.LoadBitmaps(IDB_BITMAP1, NULL, NULL, NULL);
	m_bitmapbutton.SizeToContent();
	//m_spin2.SetRange(0,0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CTermpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CTermpDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CTermpDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTermpDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	sheet1 = 0, sheet2 = 0, sheet3 = 0, skcount1 = 0, skcount2 = 0, skcount3 = 0, stcount1 = 0, stcount2 = 0, stcount3 = 0;
	
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
		MessageBox(_T("읽기 성공"));

	TF = TypeDB.ReadCSVFile(dlg.GetPathName());
	if (TF == TRUE)
	{
		//m_spin1.SetRange(1, 3);
		m_edit1.SetWindowText(_T("월인천강지곡 권상"));
		m_edit3.SetWindowText(_T("1"));
		TypeDB.m_nChar = TypeDB.m_Chars.GetSize();
		CString acount, kcount1, kcount2, tcount;
		int tcount1 = 0, tcount2 = 0, mcount1 = 0, mcount2 = 0;
		int koverlapcount = 0, toverlapcount = 0;

		for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
		{
			SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
			if (TypeDB.m_nSheet <= pSCharInfo->m_sheet)
				TypeDB.m_nSheet = pSCharInfo->m_sheet;
			kcount1 = pSCharInfo->m_char;
			mcount1 = pSCharInfo->m_sheet;

			if (mcount1 == 1)
				sheet1++;
			else if (mcount1 == 2)
				sheet2++;
			else if (mcount1 == 3)
				sheet3++;

			for (int j = i - 1; j >= 0; j--)
			{
				if (i == 0)
					break;
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(j);
				kcount2 = pSCharInfo->m_char;
				if (kcount1 == kcount2)
				{
					koverlapcount++;
					break;
				}
			}
		}
		for (int i = 1; i < TypeDB.m_Chars.GetSize(); i++)
		{
			SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
			kcount1 = pSCharInfo->m_char;
			tcount1 = pSCharInfo->m_type;
			for (int j = i - 1; j >= 0; j--)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(j);
				kcount2 = pSCharInfo->m_char;
				tcount2 = pSCharInfo->m_type;
				if (kcount1 == kcount2 && tcount1 == tcount2)
				{
					toverlapcount++;
					if (pSCharInfo->m_sheet == 1)
						stcount1++;
					else if (pSCharInfo->m_sheet == 2)
						stcount2++;
					else if (pSCharInfo->m_sheet == 3)
						stcount3++;
				}
			}
		}

		for (int i = 1; i < TypeDB.m_Chars.GetSize(); i++)
		{
			SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
			kcount1 = pSCharInfo->m_char;
			mcount1 = pSCharInfo->m_sheet;

			for (int j = i - 1; j >= 0; j--)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(j);
				kcount2 = pSCharInfo->m_char;
				mcount2 = pSCharInfo->m_sheet;
				if (mcount1 == mcount2 && kcount1 == kcount2)
				{
					if (mcount2 == 1)
						skcount1++;
					else if (mcount2 == 2)
						skcount2++;
					else if (mcount2 == 3)
						skcount3++;
					break;
				}
			}
		}
		
		BeginWaitCursor();
		m_spin1.SetRange(1, 3);
		m_spin1.SetPos(1);
		m_spin2.SetRange(1, 3);
		m_spin1.SetPos(1);
		CString page = _T("C:\\월인천강지곡 권상\\01_scan\\001.jpg");
		imgload(m_pic1, page);

		CClientDC dc(this);
		CBrush brush(NULL_BRUSH);
		
		for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
		{
			SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
			if (pSCharInfo->m_sheet == 1)
			{
				Grectangle(pSCharInfo);
				//pSCharInfo->m_sx, pSCharInfo->m_sy, pSCharInfo->m_width, pSCharInfo->m_height
			}
		}

		acount.Format(_T("%d 개"), TypeDB.m_nChar);
		m_static1.SetWindowText(acount);
		kcount1.Format(_T("%d 종"), TypeDB.m_Chars.GetSize() - koverlapcount);
		m_static2.SetWindowText(kcount1);
		tcount.Format(_T("%d 개"), TypeDB.m_Chars.GetSize() - toverlapcount);
		m_static3.SetWindowText(tcount);

		CString set, set1, set2, set3;
		set1.Format(_T("%d 개"), sheet1);
		m_static4.SetWindowText(set1);
		set2.Format(_T("%d 종"), sheet1 - skcount1);
		m_static5.SetWindowText(set2);
		set3.Format(_T("%d 개"), sheet1 - stcount1);
		m_static6.SetWindowText(set3);
		CString str;
		str.Format(_T("/%d장"), TypeDB.m_nSheet);
		m_static8.SetWindowText(str);

		SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(0);
		Rrectangle(pSCharInfo);

		m_static9.SetWindowText(pSCharInfo->m_char);
		set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
		m_static10.SetWindowText(set);

		CString loadtype, loadsheet, loadsx, loadsy;
		loadtype.Format(_T("%d"), pSCharInfo->m_type);
		loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
		loadsx.Format(_T("%d"), pSCharInfo->m_sx);
		loadsy.Format(_T("%d"), pSCharInfo->m_sy);
		loadtype.Format(_T("%d"), pSCharInfo->m_type);
		loadtp = loadtype;

		CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
		imgload(m_pic2, load);
		imgload(m_pic3, load);

		FileFind(pSCharInfo);

		CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
		STLReader(stl);

		EndWaitCursor();
	}
	else
	{
		MessageBox(_T("읽기 실패"));
		m_edit1.SetWindowText(_T(""));
		m_static1.SetWindowText(_T("- 개"));
		m_static2.SetWindowText(_T("- 개"));
		m_static3.SetWindowText(_T("- 개"));
		m_static4.SetWindowText(_T("- 개"));
		m_static5.SetWindowText(_T("- 개"));
		m_static6.SetWindowText(_T("- 개"));
		m_static9.SetWindowText(_T("유니코드"));
		m_static10.SetWindowText(_T("장   행   번"));
		m_static11.SetWindowText(_T("/개"));
		TF = FALSE;
		CString str;
		str.Format(_T("/장"));
		m_list.DeleteAllItems();
		m_static8.SetWindowText(str);
		m_edit2.SetWindowText(_T("0"));
		m_edit3.SetWindowText(_T("0"));
		CString stl = stl1 + stl0;
		STLReader(stl);
		Invalidate();
		m_spin1.SetRange(0, 0);
		m_spin2.SetRange(0, 0);
	}
}


void CTermpDlg::OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult)
{

	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	presentPos = pNMUpDown->iPos + pNMUpDown->iDelta;
	CString set, scount1, scount2, scount3;
	

	CClientDC dc(this);
	CPen penG(PS_SOLID, 1, RGB(0, 255, 0));
	CPen penR(PS_SOLID, 1, RGB(255, 0, 0));
	CBrush brush(NULL_BRUSH);

	if (TF == TRUE)
	{
		BeginWaitCursor();
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

		if (presentPos <= 1)
		{
			CString page = _T("C:\\월인천강지곡 권상\\01_scan\\001.jpg");
			presentPos = 1;
			scount1.Format(_T("%d 개"), sheet1);
			m_static4.SetWindowText(scount1);
			scount1.Format(_T("%d 종"), sheet1 - skcount1);
			m_static5.SetWindowText(scount1);
			scount1.Format(_T("%d 개"), sheet1 - stcount1);
			m_static6.SetWindowText(scount1);
			imgload(m_pic1, page);
		}
		else if (presentPos == 2)
		{
			CString page = _T("C:\\월인천강지곡 권상\\01_scan\\002.jpg");
			scount2.Format(_T("%d 개"), sheet2);
			m_static4.SetWindowText(scount2);
			scount2.Format(_T("%d 종"), sheet2 - skcount2);
			m_static5.SetWindowText(scount2);
			scount2.Format(_T("%d 개"), sheet2 - stcount2);
			m_static6.SetWindowText(scount2);
			imgload(m_pic1, page);
		}
		else if (presentPos >= 3)
		{
			CString page = _T("C:\\월인천강지곡 권상\\01_scan\\003.jpg");
			presentPos = 3;
			scount3.Format(_T("%d 개"), sheet3);
			m_static4.SetWindowText(scount3);
			scount3.Format(_T("%d 종"), sheet3 - skcount3);
			m_static5.SetWindowText(scount3);
			scount3.Format(_T("%d 개"), sheet3 - stcount3);
			m_static6.SetWindowText(scount3);
			imgload(m_pic1, page);
		}

		if (presentPos <= 1)
		{
			int ii = 0;
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 1)
				{
					Grectangle(pSCharInfo);
					if (pSCharInfo->m_line == 1 && pSCharInfo->m_order == 1)
					{
						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						Rrectangle(pSCharInfo);

						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = ii;
					}
				}
				ii++;
			}
		}
		else if (presentPos == 2)
		{
			int ii = 0;
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 2)
				{
					Grectangle(pSCharInfo);
					if (pSCharInfo->m_sheet == 2 && pSCharInfo->m_line == 1 && pSCharInfo->m_order == 1)
					{
						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						Rrectangle(pSCharInfo);

						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = ii;
					}
				}
				ii++;
			}
		}
		else if (presentPos >= 3)
		{
			int ii = 0;
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 3)
				{
					Grectangle(pSCharInfo);
					if (pSCharInfo->m_line == 1 && pSCharInfo->m_order == 1)
					{
						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						Rrectangle(pSCharInfo);

						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = ii;
					}
				}
				ii++;
			}
		}

		EndWaitCursor();
	}
	else if (TF == FALSE)
	{
	m_spin1.SetRange(0, 0);
	m_spin2.SetRange(0, 0);
	}
	*pResult = 0;
}

void CTermpDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CString set;
	CClientDC dc(this);
	CPen penR(PS_SOLID, 1, RGB(255, 0, 0));
	CPen penG(PS_SOLID, 1, RGB(0, 255, 0));
	CBrush brush(NULL_BRUSH);
	
	if (TF == TRUE)
	{
		if (presentPos <= 1)
		{
			SCharInfo* ppSCharInfo = TypeDB.m_Chars.GetAt(old_i);
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 1)
					if ((26 + pSCharInfo->m_sx / 34 <= point.x) && (148 + pSCharInfo->m_sy / 34 <= point.y) && (26 + (pSCharInfo->m_sx + pSCharInfo->m_width) / 34 >= point.x) && (148 + (pSCharInfo->m_sy + pSCharInfo->m_height) / 34 >= point.y))
					{
						Grectangle(ppSCharInfo);
						Rrectangle(pSCharInfo);

						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = i;

						break;
					}
			}
		}
		else if (presentPos == 2)
		{
			SCharInfo* ppSCharInfo = TypeDB.m_Chars.GetAt(old_i);
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 2)
					if ((26 + pSCharInfo->m_sx / 34 <= point.x) && (148 + pSCharInfo->m_sy / 34 <= point.y) && (26 + (pSCharInfo->m_sx + pSCharInfo->m_width) / 34 >= point.x) && (148 + (pSCharInfo->m_sy + pSCharInfo->m_height) / 34 >= point.y))
					{
						Grectangle(ppSCharInfo);
						Rrectangle(pSCharInfo);

						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = i;
						break;
					}
			}
		}
		else if (presentPos == 3)
		{
			SCharInfo* ppSCharInfo = TypeDB.m_Chars.GetAt(old_i);
			for (int i = 0; i < TypeDB.m_Chars.GetSize(); i++)
			{
				SCharInfo* pSCharInfo = TypeDB.m_Chars.GetAt(i);
				if (pSCharInfo->m_sheet == 3)
					if ((26 + pSCharInfo->m_sx / 34 <= point.x) && (148 + pSCharInfo->m_sy / 34 <= point.y) && (26 + (pSCharInfo->m_sx + pSCharInfo->m_width) / 34 >= point.x) && (148 + (pSCharInfo->m_sy + pSCharInfo->m_height) / 34 >= point.y))
					{
						Grectangle(ppSCharInfo);
						Rrectangle(pSCharInfo);

						m_static9.SetWindowText(pSCharInfo->m_char);
						set.Format(_T("%d장   %d행   %d번"), pSCharInfo->m_sheet, pSCharInfo->m_line, pSCharInfo->m_order);
						m_static10.SetWindowText(set);
						CString loadtype, loadsheet, loadsx, loadsy;
						loadtype.Format(_T("%d"), pSCharInfo->m_type);
						loadsheet.Format(_T("%d"), pSCharInfo->m_sheet);
						loadsx.Format(_T("%d"), pSCharInfo->m_sx);
						loadsy.Format(_T("%d"), pSCharInfo->m_sy);
						loadtp = loadtype;
						CString load = load1 + pSCharInfo->m_char + load2 + loadtype + load2 + loadsheet + load3 + loadsx + load3 + loadsy + load4;
						imgload(m_pic2, load);
						imgload(m_pic3, load);

						FileFind(pSCharInfo);

						CString stl = stl1 + pSCharInfo->m_char + load3 + loadtype + stl2;
						STLReader(stl);
						old_i = i;
						break;
					}
			}
		}
		CDialogEx::OnLButtonDown(nFlags, point);
	}
}

void CTermpDlg::OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	presentPos2 = pNMUpDown->iPos + pNMUpDown->iDelta;
	if (TF == TRUE)
	{
		CString text;
		m_static9.GetWindowText(text);

		CFileFind finder;
		BOOL working = finder.FindFile(load1 + text + load2 + loadtp + _T("\\*.*"));
		int tt = -2;
		while (working)
		{
			working = finder.FindNextFile();
			tt++;
		}
		if (presentPos2 <= 1)
			presentPos2 = 1;
		else if (presentPos2 >= tt)
			presentPos2 = tt;

		m_spin2.SetRange(1, tt);

		CString listsheet = m_list.GetItemText(presentPos2 - 1, 0);
		CString listX = m_list.GetItemText(presentPos2 - 1, 1);
		CString listY = m_list.GetItemText(presentPos2 - 1, 2);
		CString Selectpng;

		Selectpng = load1 + text + load2 + loadtp + load2 + listsheet + load3 + listX + load3 + listY + load4;
		
		//TRACE(_T("%s  tt= %d  presentPos2= %d\n"), Selectpng, tt, presentPos2);
		imgload(m_pic3, Selectpng);

		*pResult = 0;
	}
}

void CTermpDlg::OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	idx2 = pNMListView->iItem;
	idx1 = idx2 + 1;

	CString listsheet = m_list.GetItemText(idx2, 0);
	CString listX = m_list.GetItemText(idx2, 1);
	CString listY = m_list.GetItemText(idx2, 2);
	CString text;
	CString Selectpng;
	m_static9.GetWindowText(text);
	m_spin2.SetPos(idx1);

	Selectpng = load1 + text + load2 + loadtp + load2 + listsheet + load3 + listX + load3 + listY + load4;
	imgload(m_pic3, Selectpng);
	//MessageBox(Selectpng);
	*pResult = 0;
}

//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수
//사용자 정의 멤버 함수


//------------------------------------------이미지불러오기-------------------------------------------
//------------------------------------------이미지불러오기-------------------------------------------
void CTermpDlg::imgload(CStatic& pic, CString load)
{
	cv::Mat img = cv::imread((LPCTSTR)load, cv::ImreadModes::IMREAD_UNCHANGED);

	CDC* pDC;
	CImage* mfcImg = nullptr;
	pDC = pic.GetDC();

	CRect rect;
	pic.GetClientRect(&rect);
	cv::resize(img, img, cv::Size(rect.Width(), rect.Height()));

	BITMAPINFO bitmapInfo;
	bitmapInfo.bmiHeader.biYPelsPerMeter = 0;
	bitmapInfo.bmiHeader.biBitCount = 24;
	bitmapInfo.bmiHeader.biWidth = img.cols;
	bitmapInfo.bmiHeader.biHeight = -img.rows;
	bitmapInfo.bmiHeader.biPlanes = 1;
	bitmapInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfo.bmiHeader.biCompression = BI_RGB;
	bitmapInfo.bmiHeader.biClrImportant = 0;
	bitmapInfo.bmiHeader.biClrUsed = 0;
	bitmapInfo.bmiHeader.biSizeImage = 0;
	bitmapInfo.bmiHeader.biXPelsPerMeter = 0;

	if (img.channels() == 3)
	{
		mfcImg = new CImage();
		mfcImg->Create(img.cols, img.rows, 24);
	}
	else if (img.channels() == 1)
	{
		cv::cvtColor(img, img, cv::COLOR_GRAY2RGB);
		mfcImg = new CImage();
		mfcImg->Create(img.cols, img.rows, 24);
	}
	else if (img.channels() == 4)
	{
		bitmapInfo.bmiHeader.biBitCount = 32;
		mfcImg = new CImage();
		mfcImg->Create(img.cols, img.rows, 32);
	}

	::StretchDIBits(mfcImg->GetDC(), 0, 0, img.cols, img.rows,
		0, 0, img.cols, img.rows, img.data, &bitmapInfo,
		DIB_RGB_COLORS, SRCCOPY);

	mfcImg->BitBlt(::GetDC(pic.m_hWnd), 0, 0);

	mfcImg->ReleaseDC();
	delete mfcImg;
	mfcImg = nullptr;
	img.release();
	ReleaseDC(pDC);
}

//-----------------------------------------------초록네모-----------------------------------------------------
//-----------------------------------------------초록네모-----------------------------------------------------
void CTermpDlg::Grectangle(SCharInfo* ppSCharInfo)
{
	CClientDC dc(this);
	CPen penG(PS_SOLID, 1, RGB(0, 255, 0));
	//CBrush brush(NULL_BRUSH);

	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(26 + ppSCharInfo->m_sx / 34, 148 + ppSCharInfo->m_sy / 34, 26 + (ppSCharInfo->m_sx + ppSCharInfo->m_width) / 34, 148 + (ppSCharInfo->m_sy + ppSCharInfo->m_height) / 34);
	dc.SelectObject(&penG);
	dc.Rectangle(26 + ppSCharInfo->m_sx / 34, 148 + ppSCharInfo->m_sy / 34, 26 + (ppSCharInfo->m_sx + ppSCharInfo->m_width) / 34, 148 + (ppSCharInfo->m_sy + ppSCharInfo->m_height) / 34);
}

//-------------------------------------------------빨간네모--------------------------------------------------
//-------------------------------------------------빨간네모--------------------------------------------------
void CTermpDlg::Rrectangle(SCharInfo* pSCharInfo)
{
	CClientDC dc(this);
	CPen penR(PS_SOLID, 1, RGB(255, 0, 0));
	//CBrush brush(NULL_BRUSH);

	dc.SelectStockObject(NULL_BRUSH);
	dc.Rectangle(26 + pSCharInfo->m_sx / 34, 148 + pSCharInfo->m_sy / 34, 26 + (pSCharInfo->m_sx + pSCharInfo->m_width) / 34, 148 + (pSCharInfo->m_sy + pSCharInfo->m_height) / 34);
	dc.SelectObject(&penR);
	dc.Rectangle(26 + pSCharInfo->m_sx / 34, 148 + pSCharInfo->m_sy / 34, 26 + (pSCharInfo->m_sx + pSCharInfo->m_width) / 34, 148 + (pSCharInfo->m_sy + pSCharInfo->m_height) / 34);
}

//-----------------------------------------파일명찾기/리스트셋-----------------------------------------------
//-----------------------------------------파일명찾기/리스트셋-----------------------------------------------
CString typestr;
void  CTermpDlg::FileFind(SCharInfo* pSCharInfo)
{
	m_list.DeleteAllItems();
	CString typecode;
	typecode.Format(_T("%d"), pSCharInfo->m_type);
	CFileFind finder;
	BOOL working = finder.FindFile(load1 + pSCharInfo->m_char + load2 + typecode + _T("\\*.*"));
	int type = -2;
	int select = 0;
	while (working)
	{
		working = finder.FindNextFile();
		CString png_dot = (LPCTSTR)finder.GetFileName();
		CString png, png_sheet, png_sx, png_sy;

		AfxExtractSubString(png, png_dot, 0, '.');
		AfxExtractSubString(png_sheet, png, 0, '_');
		AfxExtractSubString(png_sx, png, 1, '_');
		AfxExtractSubString(png_sy, png, 2, '_');

		m_list.InsertItem(type, png_sheet);
		m_list.SetItemText(type, 1, png_sx);
		m_list.SetItemText(type, 2, png_sy);
		m_list.SendMessage(WM_VSCROLL, SB_TOP);
		type++;
		int psheet = _ttoi(png_sheet);
		int sx = _ttoi(png_sx);
		int sy = _ttoi(png_sy);

		if ((pSCharInfo->m_sheet == psheet) && (pSCharInfo->m_sx == sx) && (pSCharInfo->m_sy == sy))
			select = type;
		//TRACE(_T("%d  %d     %d_%d_%d   %s\n"), type, select, psheet, sx, sy, (LPCTSTR)finder.GetFileName());
	}

	CString typestr;
	typestr.Format(_T("/%d개"), type);
	m_spin2.SetRange(1, type);
	m_spin2.SetPos(select);

	m_static11.SetWindowText(typestr);
}

//-----------------------------------------------VTK----------------------------------------------------
//-----------------------------------------------VTK----------------------------------------------------
void CTermpDlg::InitVtkWindow(void* hWnd)
{
	if (m_vtkWindow == NULL)
	{
		vtkSmartPointer<vtkRenderWindowInteractor> interactor =
			vtkSmartPointer<vtkRenderWindowInteractor>::New();
		interactor->SetInteractorStyle(
			vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New());
		vtkSmartPointer<vtkRenderer> renderer =
			vtkSmartPointer<vtkRenderer>::New();
		renderer->SetBackground(0.0, 0.0, 0.0);
		m_vtkWindow = vtkSmartPointer<vtkRenderWindow>::New();
		m_vtkWindow->SetParentId(hWnd);
		m_vtkWindow->SetInteractor(interactor);
		m_vtkWindow->AddRenderer(renderer);
		m_vtkWindow->Render();
	}
}
void CTermpDlg::ResizeVtkWindow()
{
	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_FRAME);
	if (pWnd)
	{
		pWnd->GetClientRect(rc);
		m_vtkWindow->SetSize(rc.Width(), rc.Height());
	}
}
void CTermpDlg::STLReader(CString stl)
{
	vtkSmartPointer<vtkSTLReader> pSTLReader =
		vtkSmartPointer<vtkSTLReader>::New();
	pSTLReader->SetFileName(stl);
	pSTLReader->Update();

	vtkSmartPointer<vtkPolyData> pPolyData =
		pSTLReader->GetOutput();

	vtkSmartPointer<vtkPolyDataMapper> mapper =
		vtkSmartPointer<vtkPolyDataMapper>::New();
	mapper->SetInputData(pPolyData);
	vtkSmartPointer<vtkActor> actor =
		vtkSmartPointer<vtkActor>::New();
	actor->SetMapper(mapper);

	vtkSmartPointer<vtkRenderer> renderer =
		vtkSmartPointer<vtkRenderer>::New();
	renderer->AddActor(actor);
	renderer->SetBackground(0.94, 0.94, 0.94);
	renderer->ResetCamera();

	vtkSmartPointer<vtkLight> newLight = vtkSmartPointer<vtkLight>::New();
	newLight->SetColor(0.5, 0.5, 0.5);
	newLight->SetFocalPoint(0, 0, 0);
	newLight->SetPosition(-3, 0, 5);

	vtkSmartPointer<vtkLight> newLight2 = vtkSmartPointer<vtkLight>::New();
	newLight2->SetColor(0.5, 0.5, 0.5);
	newLight2->SetFocalPoint(0, 0, 0);
	newLight2->SetPosition(3, 0, 5);

	renderer->AddLight(newLight);
	renderer->AddLight(newLight2);

	m_vtkWindow->AddRenderer(renderer);
	m_vtkWindow->Render();
}