// Originally released under a custom license.
// This historical re-release is provided under the MIT License.
// See the LICENSE file in the repo root for details.
//
// https://github.com/nettlep
//
// ColorBox.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ColorBox.h"
#include "ColorBoxDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorBoxApp

BEGIN_MESSAGE_MAP(CColorBoxApp, CWinApp)
	//{{AFX_MSG_MAP(CColorBoxApp)
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorBoxApp construction

CColorBoxApp::CColorBoxApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CColorBoxApp object

CColorBoxApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CColorBoxApp initialization

BOOL CColorBoxApp::InitInstance()
{
	// Standard initialization

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	CColorBoxDlg dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
	}
	else if (nResponse == IDCANCEL)
	{
	}

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
