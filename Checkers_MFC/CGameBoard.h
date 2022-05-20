#pragma once
#include <list>
#include <utility>

using namespace std;
class CGameBoard
{
public:
	bool can_bite = false;
	bool isBite = false;
	/* �������
	   -999: ����� �� ������� �������
	   -2: ����, ��������� ��� ����
	   -1: ������ ����� ����
	   0: ������ ������ ����
	   1: ׸���� ���� � ������ ������ 1 (�����)
	   2: ׸���� ���� � ������ ������ 2 (������) 
	   3: ׸���� ���� � ������ ������ 1 (�����)
	   4: ׸���� ���� � ������ ������ 2 (������)
	*/
	enum class Status { 
		out_matrix = -999,
		available_cell = -2, 
		white_empty = -1,
		black_empty = 0, 
		white_cell = 1, 
		black_cell = 2, 
		white_queen = 3,
		black_queen = 4};

	/*����������� �� ���������*/
	CGameBoard();

	/*����������*/
	~CGameBoard();

	/*��������� �����������*/
	void SetupBoard();

	/*��������� ��������� ����������� ����*/
	Status GetState(int row, int col);

	/*������� ��� ��������� ���������� � ���������� �������� ����*/
	int GetColumns() const { return m_nColumns; }
	int GetRows() const { return m_nRows; }
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }

	/*��������� ������*/
	int GetResult() const { return m_nResult; }

	/*���������� �������� �����*/
	int GetCurrRow() const { return m_nCurrentRow; }
	int GetCurrCol() const { return m_nCurrentCol; }

	/*��������� ���������� ����*/
	bool GetMove() const { return m_nMove; }

	/*���������� �������*/
	bool SetStatus(int row, int col, Status st);

	/*��������� �������� �����*/
	void SetCurrRow(int row);
	void SetCurrCol(int col);

	/*�������� ����� ���� � ���������� ������, ���� ���� �����������*/
	bool IsGameOver();

	/*�������� �������� ���� � ������������ ������*/
	void DeleteBoard();

	/*����� ��������� �����*/
	void ResetAvailable();

	/*����� ����*/
	void ChangeMove();

	/*�������� ����� �����*/
	void BitMiddle(int row_before, int col_before, int row_after, int col_after);

	/*��������� ������ ��������� �����*/
	list<pair<int, int>> getAvailableCellsList(int row, int col);

private:
	/*��������� �� ��������� ������*/
	int** m_arrBoard;

	/*������ ����*/
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	
	/*����� ������*/
	/*������:
	  1 - ������ �����
	  0 - �����
	  -1 - ������ ������*/
	int m_nResult;

	/*
	  ���������� ����:
	  true - �����
	  false - ׸����
	*/
	bool m_nMove;

	/*���������� �������� �����*/
	int m_nCurrentRow, m_nCurrentCol;

	/*�������� �����*/
	void CreateBoard();

	/*��������� ������ ��������� ����� �� ��������*/
	list<pair<int, int>> getAvailableCellsOffset(int row, int col, int row_offset, int col_offset, bool is_white);
};

