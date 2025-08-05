// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// ----------------------------------------------------------------------------
// -
// -	Copyright (c) 1998 Terminal Reality Inc.  All Rights Reserved.
// -
// -	01/26/98 PDN Initial version
// -
// ----------------------------------------------------------------------------

#include "stdafx.h"
#include "ColorBox.h"
#include "ColorBoxDlg.h"

// ----------------------------------------------------------------------------

static	bool	skipRDec, skipGDec, skipBDec;
static	bool	skipRHex, skipGHex, skipBHex;
static	bool	skipRFlt, skipGFlt, skipBFlt;
static	bool	skipUpdate;

// ----------------------------------------------------------------------------

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// ----------------------------------------------------------------------------

CColorBoxDlg::CColorBoxDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CColorBoxDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CColorBoxDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CColorBoxDlg)
	DDX_Control(pDX, IDC_RED_TEXT_HEX, redTextHex);
	DDX_Control(pDX, IDC_RED_TEXT_FLOAT, redTextFloat);
	DDX_Control(pDX, IDC_GREEN_TEXT_HEX, greenTextHex);
	DDX_Control(pDX, IDC_GREEN_TEXT_FLOAT, greenTextFloat);
	DDX_Control(pDX, IDC_BLUE_TEXT_HEX, blueTextHex);
	DDX_Control(pDX, IDC_BLUE_TEXT_FLOAT, blueTextFloat);
	DDX_Control(pDX, IDC_RED_TEXT_DEC, redTextDec);
	DDX_Control(pDX, IDC_GREEN_TEXT_DEC, greenTextDec);
	DDX_Control(pDX, IDC_BLUE_TEXT_DEC, blueTextDec);
	DDX_Control(pDX, IDC_FLOAT_TEXT, floatText);
	DDX_Control(pDX, IDC_HEXIDECIMAL_TEXT, hexidecimalText);
	DDX_Control(pDX, IDC_DECIMAL_TEXT, decimalText);
	DDX_Control(pDX, IDC_PSX_TEXT, psxText);
	DDX_Control(pDX, IDC_SLIDER_R, sliderR);
	DDX_Control(pDX, IDC_SLIDER_G, sliderG);
	DDX_Control(pDX, IDC_SLIDER_B, sliderB);
	//}}AFX_DATA_MAP
}

// ----------------------------------------------------------------------------

BEGIN_MESSAGE_MAP(CColorBoxDlg, CDialog)
	//{{AFX_MSG_MAP(CColorBoxDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_COPYDEC, OnCopydec)
	ON_BN_CLICKED(IDC_COPYHEX, OnCopyhex)
	ON_BN_CLICKED(IDC_COPYFLOAT, OnCopyfloat)
	ON_BN_CLICKED(IDC_COPYPSX, OnCopypsx)
	ON_EN_CHANGE(IDC_RED_TEXT_DEC, OnChangeRedTextDec)
	ON_EN_CHANGE(IDC_GREEN_TEXT_DEC, OnChangeGreenTextDec)
	ON_EN_CHANGE(IDC_BLUE_TEXT_DEC, OnChangeBlueTextDec)
	ON_EN_CHANGE(IDC_RED_TEXT_HEX, OnChangeRedTextHex)
	ON_EN_CHANGE(IDC_GREEN_TEXT_HEX, OnChangeGreenTextHex)
	ON_EN_CHANGE(IDC_BLUE_TEXT_HEX, OnChangeBlueTextHex)
	ON_EN_CHANGE(IDC_RED_TEXT_FLOAT, OnChangeRedTextFloat)
	ON_EN_CHANGE(IDC_GREEN_TEXT_FLOAT, OnChangeGreenTextFloat)
	ON_EN_CHANGE(IDC_BLUE_TEXT_FLOAT, OnChangeBlueTextFloat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// ----------------------------------------------------------------------------

BOOL CColorBoxDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	GetDlgItem(IDOK)->SendMessage(BM_SETIMAGE, (WPARAM) IMAGE_ICON, (LPARAM) (HICON) theApp.LoadIcon(IDI_OK));

	// Init the sliders

	sliderR.SetRange(0, 255);
	sliderG.SetRange(0, 255);
	sliderB.SetRange(0, 255);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		OnHScroll(0, 0, NULL);
		CDialog::OnPaint();
	}
}

// ----------------------------------------------------------------------------

HCURSOR CColorBoxDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	unsigned int	r = (int) sliderR.GetPos();
	unsigned int	g = (int) sliderG.GetPos();
	unsigned int	b = (int) sliderB.GetPos();
	unsigned int	color = (b << 16) | (g << 8) | r;

	DrawColorBox(color);

	if (pScrollBar) CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

// ----------------------------------------------------------------------------

void	CColorBoxDlg::DrawColorBox(const unsigned int color)
{
	// Get the Window & DC

	CWnd	&colorBox = *GetDlgItem(IDC_COLORBOX);
	CDC	&dc = *colorBox.GetDC();

	// Client rect

	CRect	rect;
	colorBox.GetClientRect(rect);
	rect.DeflateRect(2, 2, 2, 2);

	// Brush

	CBrush	brush;
	brush.CreateSolidBrush(COLORREF(color));

	// Draw

	dc.FillRect(rect, &brush);

	// Restore

	brush.DeleteObject();
	colorBox.ReleaseDC(&dc);

	// Update the numbers

	unsigned int	b = (color >> 16) & 0xff;
	unsigned int	g = (color >> 8) & 0xff;
	unsigned int	r = color & 0xff;

	char	disp[90];
	sprintf(disp, "%d", r);					if (!skipRDec) SetDlgItemText(IDC_RED_TEXT_DEC, disp);
	sprintf(disp, "%d", g);					if (!skipGDec) SetDlgItemText(IDC_GREEN_TEXT_DEC, disp);
	sprintf(disp, "%d", b);					if (!skipBDec) SetDlgItemText(IDC_BLUE_TEXT_DEC, disp);
	sprintf(disp, "%d", (r << 16) | (g << 8) | b);		SetDlgItemText(IDC_DECIMAL_TEXT, disp);

	sprintf(disp, "%02X", r);				if (!skipRHex) SetDlgItemText(IDC_RED_TEXT_HEX, disp);
	sprintf(disp, "%02X", g);				if (!skipGHex) SetDlgItemText(IDC_GREEN_TEXT_HEX, disp);
	sprintf(disp, "%02X", b);				if (!skipBHex) SetDlgItemText(IDC_BLUE_TEXT_HEX, disp);
	sprintf(disp, "%02X%02X%02X", r, g, b);			SetDlgItemText(IDC_HEXIDECIMAL_TEXT, disp);

  // without STP-bit set:
//	sprintf(disp, "%04X", ((b>>3)<<10)|((g>>3)<<5)|((r>>3)<<0));	SetDlgItemText(IDC_PSX_TEXT, disp);

  // with STP-bit set:
  sprintf(disp, "%04X", (0x8000)|((b>>3)<<10)|((g>>3)<<5)|((r>>3)<<0));	SetDlgItemText(IDC_PSX_TEXT, disp);


  double	fr = (double) r / 255.0;
	double	fg = (double) g / 255.0;
	double	fb = (double) b / 255.0;
	sprintf(disp, "%.3f", fr);				if (!skipRFlt) SetDlgItemText(IDC_RED_TEXT_FLOAT, disp);
	sprintf(disp, "%.3f", fg);				if (!skipGFlt) SetDlgItemText(IDC_GREEN_TEXT_FLOAT, disp);
	sprintf(disp, "%.3f", fb);				if (!skipBFlt) SetDlgItemText(IDC_BLUE_TEXT_FLOAT, disp);
	sprintf(disp, "%.3f, %.3f, %.3f", fr, fg, fb);		SetDlgItemText(IDC_FLOAT_TEXT, disp);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnCopydec() 
{
	decimalText.SetSel(0xffff0000);
	decimalText.Copy();
	decimalText.SetSel(0xffff);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnCopyhex() 
{
	hexidecimalText.SetSel(0xffff0000);
	hexidecimalText.Copy();
	hexidecimalText.SetSel(0xffff);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnCopypsx() 
{
	psxText.SetSel(0xffff0000);
	psxText.Copy();
	psxText.SetSel(0xffff);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnCopyfloat() 
{
	floatText.SetSel(0xffff0000);
	floatText.Copy();
	floatText.SetSel(0xffff);
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeRedTextDec() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	redTextDec.GetWindowText(str, sizeof(str) - 1);
	int	val = atoi(str);
	if (lastValue != val)
	{
		skipRDec = true;
		skipUpdate = true;
		lastValue = val;
		sliderR.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipRDec = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeGreenTextDec() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	greenTextDec.GetWindowText(str, sizeof(str) - 1);
	int	val = atoi(str);
	if (lastValue != val)
	{
		skipGDec = true;
		skipUpdate = true;
		lastValue = val;
		sliderG.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipGDec = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeBlueTextDec() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	blueTextDec.GetWindowText(str, sizeof(str) - 1);
	int	val = atoi(str);
	if (lastValue != val)
	{
		skipBDec = true;
		skipUpdate = true;
		lastValue = val;
		sliderB.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipBDec = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeRedTextHex() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	redTextHex.GetWindowText(str, sizeof(str) - 1);
	int	val = 0;
	sscanf(str, "%X", &val);
	if (lastValue != val)
	{
		skipRHex = true;
		skipUpdate = true;
		lastValue = val;
		sliderR.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipRHex = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeGreenTextHex() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	greenTextHex.GetWindowText(str, sizeof(str) - 1);
	int	val = 0;
	sscanf(str, "%X", &val);
	if (lastValue != val)
	{
		skipGHex = true;
		skipUpdate = true;
		lastValue = val;
		sliderG.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipGHex = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeBlueTextHex() 
{
	if (skipUpdate) return;
	static	int	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	blueTextHex.GetWindowText(str, sizeof(str) - 1);
	int	val = 0;
	sscanf(str, "%X", &val);
	if (lastValue != val)
	{
		skipBHex = true;
		skipUpdate = true;
		lastValue = val;
		sliderB.SetPos(val);
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipBHex = false;
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeRedTextFloat() 
{
	if (skipUpdate) return;
	static	float	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	redTextFloat.GetWindowText(str, sizeof(str) - 1);
	float	val = 0;
	sscanf(str, "%f", &val);
	if (lastValue != val)
	{
		skipRFlt = true;
		skipUpdate = true;
		lastValue = val;
		sliderR.SetPos((int) (val * 255.0));
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipRFlt = false;

		char	disp[90];
		unsigned int	r = (int) sliderR.GetPos();
		unsigned int	g = (int) sliderG.GetPos();
		unsigned int	b = (int) sliderB.GetPos();
		double	fr = (double) r / 255.0;
		double	fg = (double) g / 255.0;
		double	fb = (double) b / 255.0;
		sprintf(disp, "%.3f, %.3f, %.3f", val, fg, fb);		SetDlgItemText(IDC_FLOAT_TEXT, disp);
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeGreenTextFloat() 
{
	if (skipUpdate) return;
	static	float	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	greenTextFloat.GetWindowText(str, sizeof(str) - 1);
	float	val = 0;
	sscanf(str, "%f", &val);
	if (lastValue != val)
	{
		skipGFlt = true;
		skipUpdate = true;
		lastValue = val;
		sliderG.SetPos((int) (val * 255.0));
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipGFlt = false;

		char	disp[90];
		unsigned int	r = (int) sliderR.GetPos();
		unsigned int	g = (int) sliderG.GetPos();
		unsigned int	b = (int) sliderB.GetPos();
		double	fr = (double) r / 255.0;
		double	fg = (double) g / 255.0;
		double	fb = (double) b / 255.0;
		sprintf(disp, "%.3f, %.3f, %.3f", fr, val, fb);		SetDlgItemText(IDC_FLOAT_TEXT, disp);
	}
}

// ----------------------------------------------------------------------------

void CColorBoxDlg::OnChangeBlueTextFloat() 
{
	if (skipUpdate) return;
	static	float	lastValue = 0;
	char	str[90];
	memset(str, 0, sizeof(str));
	blueTextFloat.GetWindowText(str, sizeof(str) - 1);
	float	val = 0;
	sscanf(str, "%f", &val);
	if (lastValue != val)
	{
		skipBFlt = true;
		skipUpdate = true;
		lastValue = val;
		sliderB.SetPos((int) (val * 255.0));
		OnHScroll(0, 0, NULL);
		skipUpdate = false;
		skipBFlt = false;

		char	disp[90];
		unsigned int	r = (int) sliderR.GetPos();
		unsigned int	g = (int) sliderG.GetPos();
		unsigned int	b = (int) sliderB.GetPos();
		double	fr = (double) r / 255.0;
		double	fg = (double) g / 255.0;
		double	fb = (double) b / 255.0;
		sprintf(disp, "%.3f, %.3f, %.3f", fr, fg, val);		SetDlgItemText(IDC_FLOAT_TEXT, disp);
	}
}

// ----------------------------------------------------------------------------
//	[colorboxdlg.cpp] end of file
// ----------------------------------------------------------------------------


