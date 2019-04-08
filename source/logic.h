#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>

#ifndef LOGIC_H
#define LOGIC_H

struct knight_pos {
	///position x in board fields unit (0 is left)
	int x;
	///position y in board fields unit (0 is top)
	int y;
};

void checkNewPos(int x, int y, int **board, struct knight_pos knight, struct knight_pos*new_pos, int *min);

void moveKnight(int **board, int rows, int cols, struct knight_pos*knight, bool *simulation_ended);

void checkPossibleMoves(int **board, int rows, int cols);

void saveKnightMovesToArray(int *possible_moves, int **knight_movement_history, int **board, int rows, int cols, struct knight_pos knight);

void goForward(int *knight_move_id, struct knight_pos *knight, int **knight_movement_history, int **board, int*fields_not_visited);

void goBack(int *knight_move_id, struct knight_pos *knight, int **knight_movement_history, int **board, int*fields_not_visited);

#endif
