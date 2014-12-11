#include "stdafx.h"
#include "FileInfo.h"
#include "ViewFileInfo.h"
#include "ViewFileInfoDlg.h"
#include <string>
#include <iostream>
#include <fstream>
#include "parse.h"

ClsFileInfo *pCurFile = ClsFileInfo::getInstance();

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CViewFileInfoDlg::CViewFileInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CViewFileInfoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);	
}

void CViewFileInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CViewFileInfoDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DROPFILES()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_MY_MESSAGE, &CViewFileInfoDlg::OnMyMessage)
	ON_EN_CHANGE(IDC_EDIT4, &CViewFileInfoDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT1, &CViewFileInfoDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTON3, &CViewFileInfoDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT3, &CViewFileInfoDlg::OnEnChangeEdit3)
	ON_BN_CLICKED(IDC_BUTTON4, &CViewFileInfoDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CViewFileInfoDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CViewFileInfoDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

void CViewFileInfoDlg::OnStart(CString &cstrFilePath)
{
	SetDlgItemText(IDC_EDIT3,cstrFilePath);		
	SetDlgItemText(IDC_EDIT4,L"���ڴ������Ժ�......");

	// �������ļ�����Ῠ��
	// pCurFile->FileInfoInit(fileName,filePath);
	// ���Դ����߳�������

	ParseFile *pParseFile = new ParseFile;
	Param *pThisParam = new Param;
	pThisParam->cstrFilePath = cstrFilePath;
	pThisParam->hParentwnd = m_hWnd;

	pParseFile->Init(pThisParam);
	delete pParseFile;
	pParseFile = NULL;
}
void CViewFileInfoDlg::OnDropFiles(HDROP hDropInfo)
{
	TCHAR   szFilePathName[_MAX_PATH+1] = {0};

	UINT  nNumOfFiles = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0); //�õ��ļ�����

	for (UINT nIndex = 0 ; nIndex < nNumOfFiles; ++nIndex)
	{
		DragQueryFile(hDropInfo, nIndex, szFilePathName, _MAX_PATH);  //�õ��ļ���
		CString cstrFilePath(szFilePathName);
		OnStart(cstrFilePath);
	}

	DragFinish(hDropInfo);
}
LRESULT CViewFileInfoDlg::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
	CString cstrFileTemp(L"");
	CString strFileInfo(L"");
	CString extName(L"");

	bool isImage = false;

	pCurFile->GetFilePath(cstrFileTemp); 
	extName = cstrFileTemp.Right(3).MakeLower();

	isImage = ( 0 == extName.Compare(L"png") 
		|| 0 == extName.Compare(L"gif") 
		|| 0 == extName.Compare(L"jpg"));

	//�ļ�CRC
	strFileInfo += L"crc32   : ";
	pCurFile->GetFileCRC(cstrFileTemp);  
	strFileInfo += cstrFileTemp; 
	strFileInfo += L"\r\n";

	//�ļ�MD5
	strFileInfo += L"md5     : ";
	pCurFile->GetFileMD5(cstrFileTemp);   
	strFileInfo += cstrFileTemp;
	strFileInfo += L"\r\n";

	//�ļ���С
	strFileInfo += L"size    : ";
	pCurFile->GetFileSize(cstrFileTemp);  
	strFileInfo += cstrFileTemp; 
	strFileInfo += L" bytes\r\n";

	//�ļ��汾
	
	pCurFile->GetFileVersion(cstrFileTemp); 
	
	if(!cstrFileTemp.IsEmpty()){
		strFileInfo += L"version : ";
		strFileInfo += cstrFileTemp;   
		strFileInfo += L"\r\n";
	}
	
	pCurFile->GetFileBase64(cstrFileTemp); 
	
	if(!cstrFileTemp.IsEmpty() && isImage){
		strFileInfo += L"base64  : data:image/";
		strFileInfo += extName;
		strFileInfo += ";base64,";
		strFileInfo += cstrFileTemp;   
		strFileInfo += L"\r\n";
	}
	
	SetDlgItemText(IDC_EDIT4,strFileInfo);

	return TRUE;
}

BOOL CViewFileInfoDlg::OnInitDialog()
{
	DragAcceptFiles();
	CDialog::OnInitDialog();
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��
	return TRUE;					// ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CViewFileInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this);			// ���ڻ��Ƶ��豸������
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}
HCURSOR CViewFileInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CViewFileInfoDlg::OnEnChangeEdit4()
{}
void CViewFileInfoDlg::OnEnChangeEdit1()
{}
void CViewFileInfoDlg::OnBnClickedButton3()
{
	CFileDialog fileDlg (TRUE);
	if( IDOK == fileDlg.DoModal())
	{
		CString filePath;
		filePath = fileDlg.GetPathName();
		OnStart(filePath);
	}
}

void CViewFileInfoDlg::OnEnChangeEdit3()
{
	
}

void CViewFileInfoDlg::OnBnClickedButton4()
{
	CString   str;
	GetDlgItemText(IDC_EDIT4 ,str);       

	//���Ƶ�������
	if (OpenClipboard())
	{
		HGLOBAL clipBuffer;  
		EmptyClipboard();

#ifdef _UNICODE         //����Unicode�ַ�����������
		wchar_t * buffer;
		clipBuffer = GlobalAlloc(GMEM_DDESHARE, 2 * lstrlen(str) + sizeof(wchar_t));
		buffer = (wchar_t*)GlobalLock(clipBuffer);
		wcscpy(buffer,str);
		GlobalUnlock(clipBuffer);
		SetClipboardData(CF_UNICODETEXT,clipBuffer);
#else                         //����ANSI�ַ�����������
		char *pbuff;
		clipBuffer = GlobalAlloc(GMEM_DDESHARE,str.GetLength()+1);
		pbuff = (char*)GlobalLock(clipBuffer);
		strcpy(pbuff,LPCSTR(str));
		GlobalUnlock(clipBuffer);
		SetClipboardData(CF_TEXT,clipBuffer);
#endif

		CloseClipboard();
	}



}

void CViewFileInfoDlg::OnBnClickedButton1()
{
	CString cstrInputMD5;
	CString cstrFileMD5;
	pCurFile->GetFileMD5(cstrFileMD5);
	GetDlgItemText(IDC_EDIT1,cstrInputMD5);
	//��һ��Ϊ��
	if (cstrInputMD5.IsEmpty() || cstrFileMD5 .IsEmpty())
	{
		AfxMessageBox(TEXT("���������ļ�MD5��ѡ��Ҫ���бȽϵ��ļ���"));
		return ;
	}
	if(0 == cstrFileMD5.CompareNoCase(cstrInputMD5))
	{
		AfxMessageBox(TEXT("���ļ�MD5������ֵһ��"));
	}else
	{
		AfxMessageBox(TEXT("���ļ�MD5������ֵ��һ��"));
	}
}

void CViewFileInfoDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString cstrInputCRC;
	GetDlgItemText(IDC_EDIT2,cstrInputCRC);
	CString cstrFileCRC ;
	
	pCurFile->GetFileCRC(cstrFileCRC);
	//��һ��Ϊ��
	if(cstrInputCRC.IsEmpty() || cstrFileCRC.IsEmpty())
	{
		AfxMessageBox(TEXT("���������ļ�CRC��ѡ��Ҫ���бȽϵ��ļ���"));
		return ;
	}
	if( 0 == cstrInputCRC.CompareNoCase(cstrFileCRC) )
	{
		AfxMessageBox(TEXT("���ļ�CRC������ֵһ��"));
	}else
	{
		AfxMessageBox(TEXT("���ļ�CRC������ֵ��һ��"));
	}
}