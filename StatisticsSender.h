#pragma once
class StatisticsSender
{
public:
    BOOL SendStatisticsWinInet(const CString& ipServer, const CString& endPoint, const CString& mode, const CString& dateTime, const CString& elevationResult, const CString& launchResult);
};

struct StatisticsThreadParams{
    CString ipServer;
    CString endPoint;
    CString mode;
    CString dateTime;
    CString elevationResult;
    CString launchResult;
};