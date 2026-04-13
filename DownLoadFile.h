#pragma once

#define WM_DOWNLOAD_PROGRESS (WM_USER + 100)
#define WM_DOWNLOAD_COMPLETE (WM_USER + 101)
#define WM_DOWNLOAD_ERROR    (WM_USER + 102)

class DownLoadFile
{
public:
	DownLoadFile();
	~DownLoadFile();

    // Запуск загрузки. bUseCurl - выбор режима (true = curl, false = wininet)
    BOOL StartDownload(CWnd* pNotifyWnd, const CString& strURL, const CString& strLocalPath, BOOL useCurl = FALSE);

    void Cancel();

    static UINT DownloadThread(LPVOID pParam);

private:
    BOOL DownLoadFileWinInet(const CString& strURL, const CString& strLocalPath);
    BOOL DownloadFileCurl(const CString& strURL, const CString& strLocalPath);

    void PostProgress(DWORD bytesRead, DWORD totalSize);
    void PostComplete(BOOL success, LPCTSTR error = nullptr);

    CWnd* notifyWnd;
    CString strURL;
    CString strLocalPath;
    BOOL useCurl;
    volatile BOOL cancel;
};

BOOL ExtractFileFromResource(UINT resID, LPCTSTR resType, LPCTSTR outputPath);