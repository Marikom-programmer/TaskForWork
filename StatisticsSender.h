#pragma once
class StatisticsSender
{
public:
    BOOL StartSendStatistics(LPVOID pParam, BOOL useCurl = FALSE);

private:
    BOOL SendStatisticsWinInet(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult);

    BOOL SendStatisticsWithRetry(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult);
    BOOL SendStatisticsCurl(const CString& url);

    static size_t CurlWriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};

struct StatisticsThreadParams{
    CString ipServer;
    CString endPoint;
    CString mode;
    CString dateTime;
    CString elevationResult;
    CString launchResult;
};

CString UrlEncodeASCII(const CString& str);
CString BuildStatisticsUrl(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult);