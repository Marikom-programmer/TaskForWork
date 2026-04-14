
// TaskForWork.cpp: определяет поведение классов для приложения.
//

#include "pch.h"
#include "framework.h"
#include "TaskForWork.h"
#include "StartDlg.h"
#include "DownLoadDlg.h"
#include "RunDlg.h"
#include <memory>
#include <curl/curl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTaskForWorkApp

BEGIN_MESSAGE_MAP(CTaskForWorkApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// Создание CTaskForWorkApp

CTaskForWorkApp::CTaskForWorkApp()
{
	// поддержка диспетчера перезагрузки
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: добавьте код создания,
	// Размещает весь важный код инициализации в InitInstance

	nextDlgID = 0;
}


// Единственный объект CTaskForWorkApp

CTaskForWorkApp theApp;


// Инициализация CTaskForWorkApp

BOOL CTaskForWorkApp::InitInstance()
{
	// InitCommonControlsEx() требуется для Windows XP, если манифест
	// приложения использует ComCtl32.dll версии 6 или более поздней версии для включения
	// стилей отображения.  В противном случае будет возникать сбой при создании любого окна.
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// Выберите этот параметр для включения всех общих классов управления, которые необходимо использовать
	// в вашем приложении.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// Создать диспетчер оболочки, в случае, если диалоговое окно содержит
	// представление дерева оболочки или какие-либо его элементы управления.
	CShellManager *pShellManager = new CShellManager;

	// Активация визуального диспетчера "Классический Windows" для включения элементов управления MFC
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// Стандартная инициализация
	// Если эти возможности не используются и необходимо уменьшить размер
	// конечного исполняемого файла, необходимо удалить из следующих
	// конкретных процедур инициализации, которые не требуются
	// Измените раздел реестра, в котором хранятся параметры
	// TODO: следует изменить эту строку на что-нибудь подходящее,
	// например на название организации
	SetRegistryKey(_T("TaskForWork"));

	dateTime = CTime::GetCurrentTime().Format(_T("%Y-%m-%d %H:%M:%S"));

	for (unsigned i = 1; i < __argc; ++i){
		if (_tcsicmp(__targv[i], _T("--use-curl")) == 0 ||
			_tcsicmp(__targv[i], _T("/use-curl")) == 0){

			curl_global_init(CURL_GLOBAL_ALL);

			useCurl = TRUE;
			break;
		}
		else if (_tcsicmp(__targv[i], _T("--use-wininet")) == 0 ||
				 _tcsicmp(__targv[i], _T("/use-wininet")) == 0) {
			useCurl = FALSE;
			break;
		}
		else {
			useCurl = FALSE;
		}
	}

	UINT nDlgID = IDD_START_DIALOG;

	while(nDlgID != 0){
		std::unique_ptr<CDialogEx> dlg;

		switch (nDlgID){
			case IDD_START_DIALOG:
				dlg = std::make_unique<StartDlg>();
				break;
			case IDD_DOWNLOAD_DIALOG:
				dlg = std::make_unique<DownLoadDlg>();
				break;
			case IDD_RUN_DIALOG:
				dlg = std::make_unique<RunDlg>();
				break;
			default:
				break;
		}

		if (!dlg){
			break;
		}

		INT_PTR nResponse = dlg->DoModal();

		nDlgID = nextDlgID;
		nextDlgID = 0;
	}

	// Удалить диспетчер оболочки, созданный выше.
	if (pShellManager != nullptr)
	{
		delete pShellManager;
	}

#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
	ControlBarCleanUp();
#endif

	// Поскольку диалоговое окно закрыто, возвратите значение FALSE, чтобы можно было выйти из
	//  приложения вместо запуска генератора сообщений приложения.
	return FALSE;
}

BOOL CTaskForWorkApp::ExitInstance() {
	if (useCurl) {
		curl_global_cleanup();
	}

	CWinApp::ExitInstance();

	return TRUE;
}