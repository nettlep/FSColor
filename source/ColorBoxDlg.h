// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// ColorBoxDlg.h : header file
//

#if !defined(AFX_COLORBOXDLG_H__D5B4A3E6_AEC9_11D1_940B_00A0C9697892__INCLUDED_)
#define AFX_COLORBOXDLG_H__D5B4A3E6_AEC9_11D1_940B_00A0C9697892__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

/////////////////////////////////////////////////////////////////////////////
// CColorBoxDlg dialog

class CColorBoxDlg : public CDialog
{
// Construction
public:
	CColorBoxDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CColorBoxDlg)
	enum { IDD = IDD_COLORBOX_DIALOG };
	CEdit	redTextHex;
	CEdit	redTextFloat;
	CEdit	greenTextHex;
	CEdit	greenTextFloat;
	CEdit	blueTextHex;
	CEdit	blueTextFloat;
	CEdit	redTextDec;
	CEdit	greenTextDec;
	CEdit	blueTextDec;
	CEdit	floatText;
	CEdit	hexidecimalText;
	CEdit	decimalText;
  CEdit psxText;
	CSliderCtrl	sliderR;
	CSliderCtrl	sliderG;
	CSliderCtrl	sliderB;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBoxDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CColorBoxDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCopydec();
	afx_msg void OnCopyhex();
	afx_msg void OnCopyfloat();
  afx_msg void OnCopypsx();
	afx_msg void OnChangeRedTextDec();
	afx_msg void OnChangeGreenTextDec();
	afx_msg void OnChangeBlueTextDec();
	afx_msg void OnChangeRedTextHex();
	afx_msg void OnChangeGreenTextHex();
	afx_msg void OnChangeBlueTextHex();
	afx_msg void OnChangeRedTextFloat();
	afx_msg void OnChangeGreenTextFloat();
	afx_msg void OnChangeBlueTextFloat();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void	DrawColorBox(const unsigned int color);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBOXDLG_H__D5B4A3E6_AEC9_11D1_940B_00A0C9697892__INCLUDED_)
