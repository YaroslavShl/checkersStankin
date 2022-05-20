#pragma once

#include "CGameBoard.h"
#include <string>

class CCheckersMFCDoc : public CDocument
{
protected: // создать только из сериализации
	CCheckersMFCDoc();
	virtual ~CCheckersMFCDoc();
	DECLARE_DYNCREATE(CCheckersMFCDoc)

// Атрибуты
public:

// Операции
public:
	CGameBoard::Status GetCellStatus(int row, int col) {
		return m_board.GetState(row, col);
	}

	void SetupBoard() {
		m_board.SetupBoard();
	}

	int GetColumns() {
		return m_board.GetColumns();
	}

	int GetRows() {
		return m_board.GetRows();
	}

	int GetHeight() {
		return m_board.GetHeight();
	}

	int GetWidth() {
		return m_board.GetWidth();
	}

	void DeleteBoard() {
		m_board.DeleteBoard();
	}

	bool SetCell(int row, int col, CGameBoard::Status st) {
		return m_board.SetStatus(row, col, st);
	}

	int GetResult() {
		return m_board.GetResult();
	}

	bool IsGameOver() {
		return m_board.IsGameOver();
	}

	list<pair<int, int>> getAvailableCellsList(int row, int col) {
		return m_board.getAvailableCellsList(row, col);
	}

	void ResetAvailable() {
		m_board.ResetAvailable();
	}

	void SetCurrCheckerRow(int row) {
		m_board.SetCurrRow(row);
	}

	void SetCurrCheckerCol(int col) {
		m_board.SetCurrCol(col);
	}

	int GetCurrCheckerRow() {
		return m_board.GetCurrRow();
	}

	int GetCurrCheckerCol() {
		return m_board.GetCurrCol();
	}

	void BittMiddle(int row_before, int col_before, int row_after, int col_after) {
		m_board.BitMiddle(row_before, col_before, row_after, col_after);
	}

	bool GetMove() {
		return m_board.GetMove();
	}

	void NextMove() {
		m_board.ChangeMove();
	}

	int CanBite() {
		return m_board.can_bite;
	}

	int IsBite() {
		return m_board.isBite;
	}

/*Переопределение*/
public:
	virtual BOOL OnNewDocument();

protected:
	/*Объект игровой доски*/
	CGameBoard m_board;

/*Генерация функции сообщений*/
protected:
	DECLARE_MESSAGE_MAP()
};
