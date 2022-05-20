
// Checkers_MFC.h: основной файл заголовка для приложения Checkers_MFC
//
#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CCheckersMFCApp:
// Сведения о реализации этого класса: Checkers_MFC.cpp
//

class CCheckersMFCApp : public CWinApp
{
public:
	CCheckersMFCApp() noexcept;


// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Реализация
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CCheckersMFCApp theApp;
