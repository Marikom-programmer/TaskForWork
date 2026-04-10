// DownLoadDlg.cpp: файл реализации
//

#include "pch.h"
#include "TaskForWork.h"
#include "afxdialogex.h"
#include "DownLoadDlg.h"


// Диалоговое окно DownLoadDlg

IMPLEMENT_DYNAMIC(DownLoadDlg, CDialogEx)

DownLoadDlg::DownLoadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DOWNLOAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

DownLoadDlg::~DownLoadDlg()
{
}

void DownLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(DownLoadDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL DownLoadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	LOGFONT lf = { 0 };
	lf.lfHeight = -16;
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	font_Expect.CreateFontIndirect(&lf);

	// Применяем шрифт к элементу управления (например, Static Text с ID IDC_STATIC_TEXT)
	GetDlgItem(IDC_EXPECT)->SetFont(&font_Expect);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// Обработчики сообщений DownLoadDlg
