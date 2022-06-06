
// TermpDlg.h: 헤더 파일
//

#pragma once
#include "CTypeDB.h"
#include "opencv2/opencv.hpp"

// CTermpDlg 대화 상자
class CTermpDlg : public CDialogEx
{
// 생성입니다.
public:
	CTermpDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.
	CTypeDB TypeDB;

	vtkSmartPointer<vtkRenderWindow> m_vtkWindow;
	void InitVtkWindow(void* hWnd);
	void ResizeVtkWindow();
	void STLReader(CString stl);

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TERMP_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CBitmapButton m_bitmapbutton;

	CEdit m_edit1;
	CEdit m_edit2;
	CEdit m_edit3;

	CListCtrl m_list;

	CStatic m_static1;
	CStatic m_static2;
	CStatic m_static3;
	CStatic m_static4;
	CStatic m_static5;
	CStatic m_static6;
	CStatic m_static8;
	CStatic m_static9;
	CStatic m_static10;
	CStatic m_static11;

	CStatic m_pic1;
	CStatic m_pic2;
	CStatic m_pic3;
	CStatic m_VTK;

	CSpinButtonCtrl m_spin1;
	CSpinButtonCtrl m_spin2;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDeltaposSpin1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	inline void Grectangle(SCharInfo* ppSCharInfo);
	inline void Rrectangle(SCharInfo* pSCharInfo);
	void imgload(CStatic& pic, CString load);
	void FileFind(SCharInfo* pSCharInfo);

	afx_msg void OnDeltaposSpin2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnNMClickList2(NMHDR* pNMHDR, LRESULT* pResult);
//	afx_msg void OnNMSetfocusList2(NMHDR* pNMHDR, LRESULT* pResult);
};