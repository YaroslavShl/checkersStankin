#pragma once
#include <list>
#include <utility>

using namespace std;
class CGameBoard
{
public:
	bool can_bite = false;
	bool isBite = false;
	/* Статусы
	   -999: Выход за пределы массива
	   -2: Поле, доступное для хода
	   -1: Пустое белое поле
	   0: Пустое чёрное поле
	   1: Чёрное поле с шашкой Игрока 1 (белые)
	   2: Чёрное поле с шашкой Игрока 2 (чёрные) 
	   3: Чёрное поле с дамкой Игрока 1 (белые)
	   4: Чёрное поле с дамкой Игрока 2 (чёрные)
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

	/*Конструктор по умолчанию*/
	CGameBoard();

	/*Деструктор*/
	~CGameBoard();

	/*Начальная расстановка*/
	void SetupBoard();

	/*Получение состояния конкретного поля*/
	Status GetState(int row, int col);

	/*Геттеры для получения информации о параметрах игрового поля*/
	int GetColumns() const { return m_nColumns; }
	int GetRows() const { return m_nRows; }
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }

	/*Результат партии*/
	int GetResult() const { return m_nResult; }

	/*Координаты активной шашки*/
	int GetCurrRow() const { return m_nCurrentRow; }
	int GetCurrCol() const { return m_nCurrentCol; }

	/*Получение очерёдности хода*/
	bool GetMove() const { return m_nMove; }

	/*Обновление статуса*/
	bool SetStatus(int row, int col, Status st);

	/*Установка активной шашки*/
	void SetCurrRow(int row);
	void SetCurrCol(int col);

	/*Проверка конца игры и сохранение исхода, если игра завершилась*/
	bool IsGameOver();

	/*Удаление игрового поля и освобождение памяти*/
	void DeleteBoard();

	/*Сброс доступных полей*/
	void ResetAvailable();

	/*Смена хода*/
	void ChangeMove();

	/*Удаление битых шашек*/
	void BitMiddle(int row_before, int col_before, int row_after, int col_after);

	/*Получение списка доступных полей*/
	list<pair<int, int>> getAvailableCellsList(int row, int col);

private:
	/*Указатель на двумерный массив*/
	int** m_arrBoard;

	/*Размер поля*/
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	
	/*Исход партии*/
	/*Исходы:
	  1 - Победа белых
	  0 - Ничья
	  -1 - Победа чёрных*/
	int m_nResult;

	/*
	  Очерёдность хода:
	  true - Белые
	  false - Чёрные
	*/
	bool m_nMove;

	/*Координаты активной шашки*/
	int m_nCurrentRow, m_nCurrentCol;

	/*Создание доски*/
	void CreateBoard();

	/*Получение списка доступных ходов по смещению*/
	list<pair<int, int>> getAvailableCellsOffset(int row, int col, int row_offset, int col_offset, bool is_white);
};

