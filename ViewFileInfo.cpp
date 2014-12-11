#include "stdafx.h"

#include "ViewFileInfo.h"
#include "ViewFileInfoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CViewFileInfoApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()

CViewFileInfoApp::CViewFileInfoApp()
{
}
CViewFileInfoApp theApp;
BOOL CViewFileInfoApp::InitInstance()
{
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);
	CWinApp::InitInstance();
	AfxEnableControlContainer();
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	CViewFileInfoDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{		
	}
	else if (nResponse == IDCANCEL)
	{
	}
	return FALSE;
}
