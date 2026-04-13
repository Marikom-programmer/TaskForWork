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

	CTaskForWorkApp* app = static_cast<CTaskForWorkApp*>(AfxGetApp());

	useCurl = app->useCurl;
}

DownLoadDlg::~DownLoadDlg()
{
}

void DownLoadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CANCEL, cancelButton);
	DDX_Control(pDX, IDC_NEXT, nextBut);
	DDX_Control(pDX, IDC_PROG_DOWNLOAD, progBarDownLoad);
	DDX_Control(pDX, IDC_STATUS, status);
	DDX_Control(pDX, IDC_BACK, backBut);
}


BEGIN_MESSAGE_MAP(DownLoadDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CANCEL, &DownLoadDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_NEXT, &DownLoadDlg::OnBnClickedNext)
	ON_MESSAGE(WM_DOWNLOAD_PROGRESS, &DownLoadDlg::OnDownLoadProgress)
	ON_MESSAGE(WM_DOWNLOAD_COMPLETE, &DownLoadDlg::OnDownLoadComplete)
	ON_BN_CLICKED(IDC_BACK, &DownLoadDlg::OnBnClickedBack)
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

	status.SetFont(&font_Expect);

	progBarDownLoad.SetRange(0, 100);
	progBarDownLoad.SetPos(0);
	status.SetWindowText(_T("Подготовка к загрузке..."));


	CFileDialog fileDlg(
		FALSE,
		_T("exe"),
		_T("7Zip.exe"),
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("Файлы запуска (*.exe)|*.exe"),
		this);

	INT_PTR nResponse = fileDlg.DoModal();
	if (nResponse == IDOK)
	{
		strLocalPath = fileDlg.GetPathName();

		strUrl = _T("https://github.com/ip7z/7zip/releases/download/26.00/7z2600-x64.exe");

		downLoader.StartDownload(this, strUrl, strLocalPath, useCurl);
	}
	else if (nResponse == IDCANCEL) {
		status.SetWindowText(_T("Загрузка отменена..."));

		cancelButton.EnableWindow(FALSE);
		cancelButton.ShowWindow(SW_HIDE);

		backBut.EnableWindow(TRUE);
		backBut.ShowWindow(SW_SHOW);
	}


	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}
void DownLoadDlg::OnBnClickedCancel(){
	// TODO: добавьте свой код обработчика уведомлений
	downLoader.Cancel();
	status.SetWindowText(_T("Отмена загрузки..."));
}

LRESULT DownLoadDlg::OnDownLoadProgress(WPARAM wParam, LPARAM lParam){
	DWORD read = (DWORD)wParam;
	DWORD total = (DWORD)lParam;

	if (total > 0)
	{
		int percent = (int)((read * 100) / total);
		progBarDownLoad.SetPos(percent);
		CString strStatus;
		strStatus.Format(_T("Загружено %u из %u байт (%d%%)"), read, total, percent);
		status.SetWindowText(strStatus);
	}
	else
	{
		CString strStatus;
		strStatus.Format(_T("Загружено %u байт..."), read);
		status.SetWindowText(strStatus);
	}
	return 0;
}
LRESULT DownLoadDlg::OnDownLoadComplete(WPARAM wParam, LPARAM lParam)
{
	BOOL success = (BOOL)wParam;
	if (success)
	{
		status.SetWindowText(_T("Загрузка завершена успешно!"));

		cancelButton.EnableWindow(FALSE);

		nextBut.EnableWindow(TRUE);
	}
	else
	{
		status.SetWindowText(_T("Ошибка загрузки. Используется локальная копия из ресурсов."));

		CString str = ExtractFileFromResource(IDR_INSTALLER, _T("INSTALLER"), strLocalPath) ? _T("Успешно распаковано...") : _T("Что-то пошло не так");

		status.SetWindowText(str);

		cancelButton.EnableWindow(FALSE);
		cancelButton.ShowWindow(SW_HIDE);

		backBut.EnableWindow(TRUE);
		backBut.ShowWindow(SW_SHOW);

		nextBut.EnableWindow(TRUE);
	}

	return 0;
}
void DownLoadDlg::OnBnClickedNext()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTaskForWorkApp* app = static_cast<CTaskForWorkApp*>(AfxGetApp());

	app->nextDlgID = IDD_RUN_DIALOG;

	EndDialog(IDOK);
}
void DownLoadDlg::OnBnClickedBack()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTaskForWorkApp* app = static_cast<CTaskForWorkApp*>(AfxGetApp());

	app->nextDlgID = IDD_START_DIALOG;

	EndDialog(IDOK);
}