
// Checkers_MFCView.h: интерфейс класса CCheckersMFCView
//

#pragma once


class CCheckersMFCView : public CView
{
protected: // создать только из сериализации
	CCheckersMFCView();
	DECLARE_DYNCREATE(CCheckersMFCView)

// Атрибуты
public:
	CCheckersMFCDoc* GetDocument() const;
	bool ExtraMove = false;

// Операции
public:

// Переопределение
public:
	virtual void OnDraw(CDC* pDC);  // переопределено для отрисовки этого представления
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Реализация
public:
	void ResizeWindow();
	virtual ~CCheckersMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnNewGame();
};

#ifndef _DEBUG  // версия отладки в Checkers_MFCView.cpp
inline CCheckersMFCDoc* CCheckersMFCView::GetDocument() const
   { return reinterpret_cast<CCheckersMFCDoc*>(m_pDocument); }
#endif

