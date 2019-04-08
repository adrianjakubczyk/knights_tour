#include "logic.h"

void checkNewPos(int x,int y,int **board,struct knight_pos knight,struct knight_pos*new_pos, int *min)
{
	//decreasing possible moves from field
	board[knight.y + y][knight.x + x] -= 1;

	//setting new min and position
	if (board[knight.y + y][knight.x + x] < *min) 
	{
		*min = board[knight.y + y][knight.x + x];
		new_pos->x = knight.x + x;
		new_pos->y = knight.y + y;
	}
}

void moveKnight(int **board, int rows, int cols, struct knight_pos*knight, bool *simulation_ended)
{

	int min = 9; 
	struct knight_pos new_pos;
	new_pos.x = -1;
	new_pos.y = -1;

	//checking all positions
	if (knight->y - 2 >= 0 && knight->x - 1 >= 0 && board[knight->y - 2][knight->x - 1] != -1) 
	{
		checkNewPos(-1, -2, board, *knight, &new_pos, &min);
	}
	if (knight->y - 2 >= 0 && knight->x + 1<cols&&board[knight->y - 2][knight->x + 1] != -1) 
	{
		checkNewPos(1, -2, board, *knight, &new_pos, &min);
	}
	if (knight->x + 2<cols&&knight->y - 1 >= 0 && board[knight->y - 1][knight->x + 2] != -1) 
	{
		checkNewPos(2, -1, board, *knight, &new_pos, &min);
	}
	if (knight->x + 2<cols&&knight->y + 1<rows&&board[knight->y + 1][knight->x + 2] != -1) 
	{
		checkNewPos(2, 1, board, *knight, &new_pos, &min);
	}
	if (knight->y + 2<rows&&knight->x + 1<cols&&board[knight->y + 2][knight->x + 1] != -1) 
	{
		checkNewPos(1, 2, board, *knight, &new_pos, &min);
	}
	if (knight->y + 2<rows&&knight->x - 1 >= 0 && board[knight->y + 2][knight->x - 1] != -1)
	{
		checkNewPos(-1, 2, board, *knight, &new_pos, &min);
	}
	if (knight->x - 2 >= 0 && knight->y - 1 >= 0 && board[knight->y - 1][knight->x - 2] != -1) 
	{
		checkNewPos(-2, -1, board, *knight, &new_pos, &min);
	}
	if (knight->x - 2 >= 0 && knight->y + 1<rows&&board[knight->y + 1][knight->x - 2] != -1) 
	{
		checkNewPos(-2, 1, board, *knight, &new_pos, &min);
	}

	//check knight's field as visited
	board[knight->y][knight->x] = -1;

	//switch positions if new found
	if (new_pos.y != -1 && new_pos.x != -1)
	{
		knight->y = new_pos.y;
		knight->x = new_pos.x;
	}
	else *simulation_ended = true;
}

void checkPossibleMoves(int **board, int rows, int cols)
{
	for (int i = 0; i<rows; ++i)
	{
		for (int j = 0; j<cols; ++j)
		{
			int acc = 0;

			if (i - 2 >= 0 && j - 1 >= 0)		 acc++;
			if (i - 2 >= 0 && j + 1 < cols)		 acc++;
			if (j + 2 < cols && i - 1 >= 0)		 acc++;
			if (j + 2 < cols && i + 1 < rows)    acc++;
			if (i + 2 < rows && j + 1 < rows)    acc++;
			if (i + 2 < rows && j - 1 >= 0)		 acc++;
			if (j - 2 >= 0 && i - 1 >= 0)		 acc++;
			if (j - 2 >= 0 && i + 1 <  rows)	 acc++;

			board[i][j] = acc;
		}
	}
}

void saveKnightMovesToArray(int *possible_moves, int **knight_movement_history, int **board, int rows, int cols, struct knight_pos knight)
{
	bool simulation_ended = false;
	int knight_move_id = 0;

	//checking all fields for their possible moves
	checkPossibleMoves(board, rows, cols);

	//saving knight's move to history array
	while (!simulation_ended)
	{
		++(*possible_moves);
		knight_movement_history[knight_move_id][0] = knight.x;
		knight_movement_history[knight_move_id][1] = knight.y;
		moveKnight(board, rows, cols, &knight, &simulation_ended);
		++knight_move_id;
	}

	//clearing board
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
		{
			board[i][j] = 0;
		}
	}
}

void goForward(int *knight_move_id, struct knight_pos *knight, int **knight_movement_history, int **board, int*fields_not_visited)
{
	++(*knight_move_id);

	knight->x = knight_movement_history[*knight_move_id][0];
	knight->y = knight_movement_history[*knight_move_id][1];

	board[knight->y][knight->x] = -1;

	--(*fields_not_visited);
}

void goBack(int *knight_move_id, struct knight_pos *knight, int **knight_movement_history, int **board, int*fields_not_visited)
{
	--(*knight_move_id);

	board[knight->y][knight->x] = 0;

	knight->x = knight_movement_history[*knight_move_id][0];
	knight->y = knight_movement_history[*knight_move_id][1];

	++(*fields_not_visited);
}
