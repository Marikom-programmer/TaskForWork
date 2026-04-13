
// StartDlg.h: файл заголовка
//

#pragma once


// Диалоговое окно StartDlg
class StartDlg : public CDialogEx
{
// Создание
public:
	StartDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_START_DIALOG };
#endif

private:
	CFont font_Description;

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CStatic ZipLogo;
	CButton ButtonDownLoad;
	afx_msg void OnBnClickedButdownload();
};