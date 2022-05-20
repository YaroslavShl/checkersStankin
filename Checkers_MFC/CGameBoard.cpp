#include "pch.h"
#include "CGameBoard.h"
#include <string>
#include <math.h>

CGameBoard::CGameBoard() :
	m_arrBoard(NULL), m_nColumns(10), m_nRows(10), m_nHeight(60), m_nWidth(60), m_nResult(0), m_nMove(true) {}

CGameBoard::~CGameBoard() {
	/*Удаление доски*/
	DeleteBoard();
}

void CGameBoard::SetupBoard() {
	/*При необходимости создаём доску*/
	if (m_arrBoard == NULL) {
		CreateBoard();
	}

	/*Делаем начальную расстановку*/
	for (int row = 0; row < m_nRows; ++row) {
		for (int col = 0; col < m_nColumns; ++col) {
			if ((row + col) % 2 == 1) {
				if (row < 4) {
					m_arrBoard[row][col] = static_cast<int>(Status::black_cell);
				}
				else if (row > 5) {
					m_arrBoard[row][col] = static_cast<int>(Status::white_cell);
				}
				else {
					m_arrBoard[row][col] = static_cast<int>(Status::black_empty);
				}
			}
			else {
				m_arrBoard[row][col] = static_cast<int>(Status::white_empty);
			}
		}
	}
	m_nResult = 0;
	m_nMove = true;
}

CGameBoard::Status CGameBoard::GetState(int row, int col) {
	/*Проверка границ поля*/
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return Status::out_matrix;

	return Status(m_arrBoard[row][col]);
}

void CGameBoard::DeleteBoard() {
	if (m_arrBoard != NULL) {
		for (int row = 0; row < m_nRows; ++row) {
			if (m_arrBoard[row] != NULL) {
				delete[] m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		delete[] m_arrBoard;
		m_arrBoard = NULL;
	}
}

void CGameBoard::CreateBoard() {
	if (m_arrBoard != NULL) {
		DeleteBoard();
	}

	m_arrBoard = new int* [m_nRows];

	for (int row = 0; row < m_nRows; ++row) {
		m_arrBoard[row] = new int[m_nColumns];

		for (int col = 0; col < m_nColumns; ++col) {
			m_arrBoard[row][col] = static_cast<int>(Status::white_empty);
		}
	}
}

bool CGameBoard::SetStatus(int row, int col, Status st) {
	/*Проверка на выход за пределы доски*/
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns)
		return false;

	/*Нельзя изменить поле на белое*/
	if (st == Status::white_empty)
		return false;

	m_arrBoard[row][col] = static_cast<int>(st);
	return true;
}

bool CGameBoard::IsGameOver() {
	bool is_white = false, is_black = false;

	for (int row = 0; row < m_nRows; ++row) {
		for (int col = 0; col < m_nColumns; ++col) {
			if (!is_white) {
				if (m_arrBoard[row][col] == static_cast<int>(Status::white_cell)) {
					is_white = true;
					if (is_black) {
						break;
					}
				}
			}
			if (!is_black) {
				if (m_arrBoard[row][col] == static_cast<int>(Status::black_cell)) {
					is_black = true;
					if (is_white) {
						break;
					}
				}
			}
		}
		if (is_white && is_black) {
			break;
		}
	}

	/*Обновляем исход партии*/
	if (!is_white) {
		m_nResult = -1; /*Победа чёрных*/
	}
	else if (!is_black) {
		m_nResult = 1; /*Победа белых*/
	}

	return !(is_white && is_black);
}

list<pair<int, int>> CGameBoard::getAvailableCellsOffset(int row, int col, int row_offset, int col_offset, bool is_white) {
	list<pair<int, int>> av_cells;
	int row_loc = row, col_loc = col;
	bool is_bit = false;
	Status st_check;
	while (true) {
		row_loc += row_offset;
		col_loc += col_offset;
		if ((st_check = GetState(row_loc, col_loc)) == Status::black_empty) {
			av_cells.push_back({ row_loc, col_loc });
		}
		else if ((st_check == (is_white ? Status::black_cell : Status::white_cell) 
			|| st_check == (is_white ? Status::black_queen : Status::white_queen)) && !is_bit) {
			is_bit = true;
		}
		else {
			break;
		}
	}
	return av_cells;
}


list<pair<int, int>> CGameBoard::getAvailableCellsList(int row, int col) {
	list<pair<int, int>> av_cells, list_temp;
	Status st = GetState(row, col), st_check;
	can_bite = false;

	/*Чёрная шашка*/
	if (st == CGameBoard::Status::black_cell) {
		if ((st_check = GetState(row + 1, col + 1)) == Status::black_empty) {
			can_bite = can_bite || false;
			av_cells.push_back({ row + 1, col + 1 });
		}
		else if ((st_check == Status::white_cell || st_check == Status::white_queen) && GetState(row + 2, col + 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row + 2, col + 2 });
		}

		if ((st_check = GetState(row + 1, col - 1)) == Status::black_empty) {
			can_bite = can_bite || false;
			av_cells.push_back({ row + 1, col - 1 });
		}
		else if ((st_check == Status::white_cell || st_check == Status::white_queen) && GetState(row + 2, col - 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row + 2, col - 2 });
		}

		st_check = GetState(row - 1, col - 1);
		if ((st_check == Status::white_cell || st_check == Status::white_queen) && GetState(row - 2, col - 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row - 2, col - 2 });
		}

		st_check = GetState(row - 1, col + 1);
		if ((st_check == Status::white_cell || st_check == Status::white_queen) && GetState(row - 2, col + 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row - 2, col + 2 });
		}
	}
	/*Белая шашка*/
	else if (st == CGameBoard::Status::white_cell) {
		if ((st_check = GetState(row - 1, col - 1)) == Status::black_empty) {
			can_bite = can_bite || false;
			av_cells.push_back({ row - 1, col - 1 });
		}
		else if ((st_check == Status::black_cell || st_check == Status::black_queen) && GetState(row - 2, col - 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row - 2, col - 2 });
		}

		if ((st_check = GetState(row - 1, col + 1)) == Status::black_empty) {
			can_bite = can_bite || false;
			av_cells.push_back({ row - 1, col + 1 });
		}
		else if ((st_check == Status::black_cell || st_check == Status::black_queen) && GetState(row - 2, col + 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row - 2, col + 2 });
		}

		st_check = GetState(row + 1, col + 1);
		if ((st_check == Status::black_cell || st_check == Status::black_queen) && GetState(row + 2, col + 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row + 2, col + 2 });
		}

		st_check = GetState(row + 1, col - 1);
		if ((st_check == Status::black_cell || st_check == Status::black_queen) && GetState(row + 2, col - 2) == Status::black_empty) {
			can_bite = can_bite || true;
			av_cells.push_back({ row + 2, col - 2 });
		}
	}
	/*Чёрная дамка*/
	else if (st == CGameBoard::Status::black_queen) {
		list_temp = getAvailableCellsOffset(row, col, -1, -1, false);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, -1, 1, false);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, 1, -1, false);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, 1, 1, false);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
	}
	/*Белая дамка*/
	else if (st == CGameBoard::Status::white_queen) {
		list_temp = getAvailableCellsOffset(row, col, -1, -1, true);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, -1, 1, true);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, 1, -1, true);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
		list_temp = getAvailableCellsOffset(row, col, 1, 1, true);
		av_cells.insert(av_cells.end(), list_temp.begin(), list_temp.end());
	}

	return av_cells;
}



void CGameBoard::ResetAvailable() {
	for (int row = 0; row < m_nRows; ++row) {
		for (int col = 0; col < m_nColumns; ++col) {
			if (GetState(row, col) == Status::available_cell) {
				SetStatus(row, col, Status::black_empty);
			}
		}
	}
}

void CGameBoard::SetCurrRow(int row) {
	m_nCurrentRow = row;
}

void CGameBoard::SetCurrCol(int col) {
	m_nCurrentCol = col;
}


void CGameBoard::BitMiddle(int row_before, int col_before, int row_after, int col_after) {
	int row_offset = (row_before > row_after) ? -1 : 1;
	int col_offset = (col_before > col_after) ? -1 : 1;
	int l_row = row_before, l_col = col_before;

	if (fabs(row_before - row_after) == 2) {
		isBite = true;
	}
	else {
		isBite = false;
	}

	do {
		l_row += row_offset;
		l_col += col_offset;
		SetStatus(l_row, l_col, Status::black_empty);
	} while (l_row != row_after && l_col != col_after);
}

void CGameBoard::ChangeMove() {
	m_nMove = !m_nMove;
}