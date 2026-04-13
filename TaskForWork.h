
// TaskForWork.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CTaskForWorkApp:
// Сведения о реализации этого класса: TaskForWork.cpp
//

class CTaskForWorkApp : public CWinApp
{
public:
	CTaskForWorkApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация
	UINT nextDlgID;

	BOOL useCurl = FALSE;

	DECLARE_MESSAGE_MAP()
};

extern CTaskForWorkApp theApp;