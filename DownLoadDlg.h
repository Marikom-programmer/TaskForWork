#pragma once
#include "afxdialogex.h"
#include "DownLoadFile.h"


// Диалоговое окно DownLoadDlg

class DownLoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DownLoadDlg)

public:
	DownLoadDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DownLoadDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DOWNLOAD_DIALOG };
#endif

private:
	CFont fontExpect;

protected:
	HICON m_hIcon;


	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	virtual BOOL OnInitDialog();

public:
	CButton cancelButton;
	CProgressCtrl progBarDownLoad;
	CStatic status;
	CButton nextBut;
	CButton backBut;

	DownLoadFile downLoader;
	CString strUrl;
	CString strLocalPath;
	BOOL useCurl;

	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedBack();
	afx_msg LRESULT OnDownLoadProgress(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnDownLoadComplete(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

CString GetTempDirectory();