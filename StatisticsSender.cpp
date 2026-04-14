#include "pch.h"
#include "StatisticsSender.h"
#include <afxinet.h>
#include <afx.h>
#include <curl/curl.h>
#include <memory>

BOOL StatisticsSender::StartSendStatistics(LPVOID pParam, BOOL useCurl) {
    BOOL success = FALSE;

    std::unique_ptr<StatisticsThreadParams> p(static_cast<StatisticsThreadParams*>(pParam));

    if (useCurl) {
        success = SendStatisticsWithRetry(p->ipServer, p->endPoint, p->mode, p->dateTime, p->elevationResult, p->launchResult);
    }
    else {
        success = SendStatisticsWinInet(p->ipServer, p->endPoint, p->mode, p->dateTime, p->elevationResult, p->launchResult);
    }
    return success;
}

BOOL StatisticsSender::SendStatisticsWinInet(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult){
    CString url = ipServer + endPoint + _T("?mode=") + mode + _T("&dateTime=") + dateTime + _T("&elevationResult=") + elevationResult + _T("&launchResult=") + launchResult;

    for (unsigned i = 0; i < 2; ++i)
    {
        try
        {
            CInternetSession session(_T("MyInstaller"), 1, INTERNET_OPEN_TYPE_PRECONFIG);
            DWORD flags = INTERNET_FLAG_RELOAD | INTERNET_FLAG_NO_CACHE_WRITE;

            CStdioFile* file = session.OpenURL(url, 1, flags);
            if (!file) {
                return FALSE;
            }

            file->Close();
            delete file;

            return TRUE;
        }
        catch (CInternetException* pEx)
        {
            pEx->Delete();
            if (i == 0)
            {
                Sleep(2000);
                continue;
            }
            return FALSE;
        }
    }
    return FALSE;
}

BOOL StatisticsSender::SendStatisticsWithRetry(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult){
    CString url = BuildStatisticsUrl(ipServer, endPoint, mode, dateTime, elevationResult, launchResult);
    for (unsigned i = 0; i < 2; ++i)
    {
        if (SendStatisticsCurl(url)) {
            return true;
        }
        if (i == 0) {
            Sleep(2000);
        }
    }
    return FALSE;
}

BOOL StatisticsSender::SendStatisticsCurl(const CString& url) {
    CStringA strUrlA(url);

    CURL* curl = curl_easy_init();

    if (!curl) {
        return FALSE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, strUrlA.GetString());
    curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWriteCallback);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
    curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
    
    CURLcode res = curl_easy_perform(curl);

    curl_easy_cleanup(curl);
    return (res == CURLE_OK);
}

size_t StatisticsSender::CurlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    return size * nmemb;
}

CString UrlEncodeASCII(const CString& str) {
    CString result;
    for (int i = 0; i < str.GetLength(); ++i)
    {
        TCHAR ch = str[i];
        if ((ch >= _T('A') && ch <= _T('Z')) ||
            (ch >= _T('a') && ch <= _T('z')) ||
            (ch >= _T('0') && ch <= _T('9')) ||
            ch == _T('-') || ch == _T('_') || ch == _T('.') || ch == _T('~'))
        {
            result += ch;
        }
        else
        {
            result.AppendFormat(_T("%%%02X"), (unsigned int)ch);
        }
    }
    return result;
}
CString BuildStatisticsUrl(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult) {
    CString url;
    url.Format(_T("%s?mode=%s&dateTime=%s&elevationResult=%s&launchResult=%s"),
        ipServer + endPoint,
        UrlEncodeASCII(mode),
        UrlEncodeASCII(dateTime),
        UrlEncodeASCII(elevationResult),
        UrlEncodeASCII(launchResult));
    return url;
}