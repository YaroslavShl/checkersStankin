#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "Checkers_MFC.h"
#endif

#include "Checkers_MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
// CCheckersMFCDoc

IMPLEMENT_DYNCREATE(CCheckersMFCDoc, CDocument)
BEGIN_MESSAGE_MAP(CCheckersMFCDoc, CDocument)
END_MESSAGE_MAP()


// Создание или уничтожение CCheckersMFCDoc

CCheckersMFCDoc::CCheckersMFCDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CCheckersMFCDoc::~CCheckersMFCDoc()
{
}

BOOL CCheckersMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_board.SetupBoard();

	return TRUE;
}

