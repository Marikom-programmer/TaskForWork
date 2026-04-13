#include "pch.h"
#include "DownLoadFile.h"

#pragma comment(lib, "wininet.lib")
#include <wininet.h>
#include <afxinet.h>
#include <afxtempl.h>
#include <curl/curl.h>

DownLoadFile::DownLoadFile(){
	cancel = FALSE;
	useCurl = FALSE;

	notifyWnd = FALSE;
}
DownLoadFile::~DownLoadFile(){}

BOOL DownLoadFile::StartDownload(CWnd* pNotifyWnd, const CString& strURL, const CString& strLocalPath, BOOL useCurl){
    notifyWnd = pNotifyWnd;
    this->strURL = strURL;
    this->strLocalPath = strLocalPath;
    this->useCurl = useCurl;
    cancel = FALSE;

    AfxBeginThread(DownloadThread, this);

    return TRUE;
}

void DownLoadFile::Cancel(){
    cancel = TRUE;
}

UINT DownLoadFile::DownloadThread(LPVOID param){
    DownLoadFile* pThis = static_cast<DownLoadFile*>(param);
    BOOL success = FALSE;

    if (pThis->useCurl)
        success = pThis->DownloadFileCurl(pThis->strURL, pThis->strLocalPath);
    else
        success = pThis->DownLoadFileWinInet(pThis->strURL, pThis->strLocalPath);

    pThis->PostComplete(success);

    return 0;
}

BOOL DownLoadFile::DownLoadFileWinInet(const CString& strURL, const CString& strLocalPath){
    for (unsigned i = 0; i < 2; ++i) {
        try {
            CInternetSession session(_T("Task"), 1, INTERNET_OPEN_TYPE_PRECONFIG);
            CStdioFile* file = session.OpenURL(strURL, 1, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD, nullptr, 0);

            if (!file) {
                return FALSE;
            }

            DWORD totalSize = 0;
            file->Seek(0, CFile::end);
            totalSize = file->Seek(0, CFile::current);
            file->SeekToBegin();

            CFile localFile;
            if (!localFile.Open(strLocalPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
                delete file;
                return FALSE;
            }

            const UINT bufferSize = 8192;
            BYTE buffer[bufferSize];
            UINT bytesRead = 0;
            DWORD totalRead = 0;

            while (!cancel) {
                bytesRead = file->Read(buffer, bufferSize);
                if (bytesRead == 0) {
                    break;
                }

                localFile.Write(buffer, bytesRead);
                totalRead += bytesRead;

                PostProgress(totalRead, totalSize);

                if (cancel) {
                    ::DeleteFile(strLocalPath);

                    localFile.Close();
                    file->Close();

                    return FALSE;
                }
            }

            localFile.Close();
            file->Close();
            delete file;

            return (totalRead > 0);
        }
        catch (CInternetException* ex) {
            ex->Delete();
            if (i == 0){
                Sleep(5000);
                continue;
            }
        }
        break;
    }
    return FALSE;
}

BOOL DownLoadFile::DownloadFileCurl(const CString& strURL, const CString& strLocalPath){
    AfxMessageBox(_T("Временно не работает..."));

	return FALSE;
}

void DownLoadFile::PostProgress(DWORD bytesRead, DWORD totalSize){
    if (notifyWnd && ::IsWindow(notifyWnd->m_hWnd))
    {
        ::PostMessage(notifyWnd->m_hWnd, WM_DOWNLOAD_PROGRESS,
            (WPARAM)bytesRead, (LPARAM)totalSize);
    }
}

void DownLoadFile::PostComplete(BOOL success, LPCTSTR error){
    if (notifyWnd && ::IsWindow(notifyWnd->m_hWnd))
    {
        ::PostMessage(notifyWnd->m_hWnd, WM_DOWNLOAD_COMPLETE,
            (WPARAM)success, (LPARAM)error);
    }
}

BOOL ExtractFileFromResource(UINT resID, LPCTSTR resType, LPCTSTR outputPath){
    HINSTANCE inst = AfxGetResourceHandle();
    HRSRC hRes = FindResource(inst, MAKEINTRESOURCE(resID), resType);

    if (!hRes) {
        return FALSE;
    }

    HGLOBAL hGlobal = LoadResource(inst, hRes);
    DWORD size = SizeofResource(inst, hRes);
    LPVOID data = LockResource(hGlobal);

    CFile file;
    if (file.Open(outputPath, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))
    {
        file.Write(data, size);
        file.Close();
        return TRUE;
    }
    return FALSE;
}