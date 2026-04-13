
// StartDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "TaskForWork.h"
#include "StartDlg.h"
#include "afxdialogex.h"
#include <afxtoolbarimages.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Диалоговое окно StartDlg

StartDlg::StartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_START_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void StartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZIPLOGO, ZipLogo);
	DDX_Control(pDX, IDC_BUTDOWNLOAD, ButtonDownLoad);
}

BEGIN_MESSAGE_MAP(StartDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTDOWNLOAD, &StartDlg::OnBnClickedButdownload)
END_MESSAGE_MAP()


// Обработчики сообщений CTaskForWorkDlg

BOOL StartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	CPngImage zipLogoImage;
	if (zipLogoImage.Load(IDB_ZIPLOGO, nullptr))
	{
		ZipLogo.SetBitmap((HBITMAP)zipLogoImage.Detach());
	}
	else
	{
		AfxMessageBox(_T("Не удалось загрузить PNG из ресурсов!"));
	}

	CPngImage downLoadImageButton;
	if (downLoadImageButton.Load(IDB_DOWNLOAD, nullptr))
	{
		ButtonDownLoad.SetBitmap((HBITMAP)downLoadImageButton.Detach());
	}
	else
	{
		AfxMessageBox(_T("Не удалось загрузить PNG из ресурсов!"));
	}

	LOGFONT lf = { 0 };
	lf.lfHeight = -16;
	lf.lfWeight = FW_BOLD;
	_tcscpy_s(lf.lfFaceName, _T("Arial"));

	font_Description.CreateFontIndirect(&lf);

	GetDlgItem(IDC_DESCRIPTION)->SetFont(&font_Description);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void StartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR StartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void StartDlg::OnBnClickedButdownload()
{
	// TODO: добавьте свой код обработчика уведомлений
	CTaskForWorkApp* app = static_cast<CTaskForWorkApp*>(AfxGetApp());

	app->nextDlgID = IDD_DOWNLOAD_DIALOG;

	EndDialog(IDOK);
}