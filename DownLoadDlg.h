#pragma once
#include "afxdialogex.h"


// Диалоговое окно DownLoadDlg

class DownLoadDlg : public CDialogEx
{
	DECLARE_DYNAMIC(DownLoadDlg)

public:
	DownLoadDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~DownLoadDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DownLoadDlg };
#endif

private:
	CFont font_Expect;

protected:
	HICON m_hIcon;


	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
};
