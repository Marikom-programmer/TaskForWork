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
	DDX_Control(pDX, IDC_INSTALL_BUTTON, installBut);
	DDX_Control(pDX, IDC_INFO, infoText);
}


BEGIN_MESSAGE_MAP(RunDlg, CDialogEx)
	ON_BN_CLICKED(IDC_INSTALL_BUTTON, &RunDlg::OnBnClickedInstallButton)
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
		installBut.SetBitmap((HBITMAP)installImg.Detach());
	}
	else
	{
		AfxMessageBox(_T("Не удалось загрузить PNG из ресурсов!"));
	}

	LOGFONT lf = { 0 };
	lf.lfHeight = -16;
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	fontInfo.CreateFontIndirect(&lf);

	infoText.SetFont(&fontInfo);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// Обработчики сообщений RunDlg
void RunDlg::OnBnClickedInstallButton()
{
	// TODO: добавьте свой код обработчика уведомлений
	infoText.SetWindowText(_T("Установка началась"));

	CTaskForWorkApp* app = static_cast<CTaskForWorkApp*>(AfxGetApp());

	DWORD result = LaunchAndWait(app->strLocalPath);
	CString str;

	if (result == ERROR_SUCCESS) {
		str = (_T("Установка завершена успешно."));
	}
	else if (result == ERROR_FILE_NOT_FOUND) {
		str = (_T("Файл ненайден. Попробуйте запустить установщик заново."));
	}
	else if (result == ERROR_CANCELLED) {
		str = (_T("Для установки требуются права администратора. Операция отменена пользователем."));
	}
	else if (result == 1) {
		str = (_T("Установка отменена пользователем."));
	}
	else {
		str.Format(_T("Неизвестная ошибка. Код ишибки - %u"), result);
	}
	infoText.SetWindowText(str);
}

UINT LaunchAndWait(LPCTSTR filePath){
	SHELLEXECUTEINFO sei = { sizeof(sei) };
	sei.lpFile = filePath;
	sei.nShow = SW_SHOW;
	sei.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOCLOSEPROCESS;
	sei.lpVerb = _T("runas");

	DWORD error = UINT_MAX;

	if (ShellExecuteEx(&sei))
	{
		if (sei.hProcess)
		{
			WaitForSingleObject(sei.hProcess, INFINITE);
			DWORD exitCode;
			GetExitCodeProcess(sei.hProcess, &exitCode);
			CloseHandle(sei.hProcess);
			return exitCode;
		}
	}

	error = GetLastError();

	return error;
}