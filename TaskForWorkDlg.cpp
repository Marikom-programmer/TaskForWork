
// TaskForWorkDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "TaskForWork.h"
#include "TaskForWorkDlg.h"
#include "afxdialogex.h"

#include <afxinet.h>
#include <afxtoolbarimages.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CAboutDlg используется для описания сведений о приложении

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

// Реализация
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Диалоговое окно CTaskForWorkDlg



CTaskForWorkDlg::CTaskForWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TASKFORWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTaskForWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZIPLOGO, ZipLogo);
	DDX_Control(pDX, IDC_BUTDOWNLOAD, ButtonDownLoad);
}

BEGIN_MESSAGE_MAP(CTaskForWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()


// Обработчики сообщений CTaskForWorkDlg

BOOL CTaskForWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Добавление пункта "О программе..." в системное меню.

	// IDM_ABOUTBOX должен быть в пределах системной команды.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

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

	// Применяем шрифт к элементу управления (например, Static Text с ID IDC_STATIC_TEXT)
	GetDlgItem(IDC_DESCRIPTION)->SetFont(&font_Description);

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

void CTaskForWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CTaskForWorkDlg::OnPaint()
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
HCURSOR CTaskForWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}