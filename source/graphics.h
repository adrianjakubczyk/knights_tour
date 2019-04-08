#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#ifndef GRAPHICS_H
#define GRAPHICS_H

void drawRect(float x, float y, float width, float height, ALLEGRO_COLOR color);

void drawChessboard(int m, int n, float field_width, float field_height, ALLEGRO_COLOR line_color, ALLEGRO_COLOR black_field_color, ALLEGRO_COLOR knight_field_color, ALLEGRO_COLOR visited_field_color, struct knight_pos knight, int **board, ALLEGRO_BITMAP *knight_image);

void drawControls(ALLEGRO_FONT*font, ALLEGRO_COLOR text_color, ALLEGRO_COLOR active_text_color, bool automove, bool draw_path);

void drawInfo(ALLEGRO_FONT*font, ALLEGRO_COLOR text_color, ALLEGRO_COLOR success_text_color, ALLEGRO_COLOR failure_text_color, ALLEGRO_COLOR background_color, int m, int n, int fields_not_visited, int starting_position_x, int starting_position_y, struct knight_pos knight, int possible_moves, int moves_per_frame);

void drawPath(bool draw_path, int knight_move_id, int**knight_movement_history, float field_width, float field_height, ALLEGRO_COLOR color);

void drawHoveredField(int mouse_x, int mouse_y, float field_width, float field_height);


#endif