// RunDlg.cpp: файл реализации
//

#include "pch.h"
#include "TaskForWork.h"
#include "afxdialogex.h"
#include "RunDlg.h"


// Диалоговое окно RunDlg

IMPLEMENT_DYNAMIC(RunDlg, CDialogEx)

RunDlg::RunDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RUN_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

RunDlg::~RunDlg()
{
}

void RunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_INSTALL_BUTTON, installBt);
}


BEGIN_MESSAGE_MAP(RunDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL RunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	CPngImage installImg;
	if (installImg.Load(IDB_INSTALL, nullptr))
	{
		installBt.SetBitmap((HBITMAP)installImg.Detach());
	}
	else
	{
		AfxMessageBox(_T("Не удалось загрузить PNG из ресурсов!"));
	}

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// Обработчики сообщений RunDlg