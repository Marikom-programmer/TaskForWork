#include "pch.h"
#include "StatisticsSender.h"
#include <afxinet.h>
#include <afx.h>

BOOL StatisticsSender::SendStatisticsWinInet(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult)
{
    CString url = ipServer + endPoint + _T("?mode=") + mode + _T("&dateTime=") + dateTime + _T("&elevationResult=") + elevationResult + _T("&launchResult=") + launchResult;

    for (unsigned i = 0; i < 2; ++i)
    {
        try
        {
            CInternetSession session(_T("MyInstaller"), 1, INTERNET_OPEN_TYPE_PRECONFIG);
            DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;

            CStdioFile* file = session.OpenURL(url, 1, flags);
            if (!file) {
                return false;
            }

            file->Close();
            delete file;

            return true;
        }
        catch (CInternetException* pEx)
        {
            pEx->Delete();
            if (i == 0)
            {
                Sleep(2000);
                continue;
            }
            return false;
        }
    }
    return false;
}