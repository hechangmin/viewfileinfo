#include <atlpath.h>
#include "FileInfo.h"

#define WM_MY_MESSAGE (WM_USER+100)

typedef struct Param
{
	Param():
	cstrFilePath(L""),
	hParentwnd(NULL)
	{
		
	}
	CString		cstrFilePath;
	HWND        hParentwnd;
}*pParam;

class ParseFile
{
public:
	ParseFile()
	{
		m_hThread			= NULL;
		m_bStop				= FALSE;
	}
public:   	
	BOOL Init(Param *pThisParam)
	{
		DWORD  nSta = 0;

		GetExitCodeThread(m_hThread,&nSta);

		if(STILL_ACTIVE == nSta)
		{
			Stop();
		}

		DWORD dwThreadId = 0;
		m_hThread = ::CreateThread(NULL, 0, AutoRun, (LPVOID)pThisParam, 0, &dwThreadId);
		return TRUE;
	}

	BOOL Stop()
	{
		::WaitForSingleObject(m_hThread, 1000);
		TerminateThread(m_hThread, 0);
		if( m_hThread )
		{
			::CloseHandle(m_hThread);
			m_hThread = NULL;
		}

		return TRUE;
	}
	/**
	* @brief	调用结束 回收资源
	*/
	BOOL ParseFile::UnInit()
	{
		::WaitForSingleObject(m_hThread, INFINITE);
		::CloseHandle(m_hThread);
		m_hThread = NULL;

		return TRUE;
	}

private:
	/**
	* @brief 新起一个线程
	*/
	 static DWORD WINAPI AutoRun(LPVOID lpParam )
	{
		Param* pThis = (Param*)lpParam;

		ClsFileInfo *pCurFile = ClsFileInfo::getInstance();

		pCurFile->FileInfoInit(pThis->cstrFilePath);

		::SendMessage(pThis->hParentwnd, WM_MY_MESSAGE, NULL, NULL);
		
		if( pThis )
		{
			delete pThis;
			pThis = NULL;
		}
		
		return 0;
	}

public:
	HANDLE		m_hThread;					// 线程句柄
	BOOL		m_bStop;					// 是否同步停止
};