#ifndef ClsFileInfo_H
#define ClsFileInfo_H
#define READ_BUF_SIZE	20480
#pragma   comment(lib,   "Version.lib") 
class ClsFileInfo
{
protected:
	ClsFileInfo():
	m_cstrFilePath(L""),
	m_cstrFileBase64(L""),
	m_cstrFileMD5(L""),
	m_cstrFileCRC(L""),
	m_cstrFileSize(L""),
	m_cstrFileVersion(L"")
	{}
public:
	static ClsFileInfo* getInstance(){
		static ClsFileInfo obj;
		return &obj;
	}

	//Îö¹¹º¯Êý
	~ClsFileInfo(){

	}

	BOOL FileInfoInit(CString &filePath);
	BOOL GetFileMD5(CString &fileMD5);
	BOOL GetFileCRC(CString &fileCRC);
	BOOL GetFileBase64(CString &fileBase64);	
	BOOL GetFilePath(CString &filePath);
	BOOL GetFileVersion(CString &fileVersion);
	BOOL GetFileSize(CString &fileSize);
	
private:
	BOOL SetFileCRCMD5SizeBase64();
	BOOL SetFileVerSion();
	
	CString m_cstrFilePath;
	CString m_cstrFileBase64;
	CString m_cstrFileMD5;
	CString m_cstrFileCRC;
	CString m_cstrFileSize;
	CString m_cstrFileVersion;
};
#endif