#pragma once
#include "afxdialogex.h"


// Диалоговое окно RunDlg

class RunDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RunDlg)

public:
	RunDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~RunDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RUN_DIALOG };
#endif

protected:
	HICON m_hIcon;

	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CButton installBt;
};