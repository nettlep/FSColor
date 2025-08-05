// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// ColorBox.h : main header file for the COLORBOX application
//

#if !defined(AFX_COLORBOX_H__D5B4A3E4_AEC9_11D1_940B_00A0C9697892__INCLUDED_)
#define AFX_COLORBOX_H__D5B4A3E4_AEC9_11D1_940B_00A0C9697892__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CColorBoxApp:
// See ColorBox.cpp for the implementation of this class
//

class CColorBoxApp : public CWinApp
{
public:
	CColorBoxApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorBoxApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CColorBoxApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


extern	CColorBoxApp theApp;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLORBOX_H__D5B4A3E4_AEC9_11D1_940B_00A0C9697892__INCLUDED_)
