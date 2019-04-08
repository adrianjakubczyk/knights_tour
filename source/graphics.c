#include "graphics.h"
#include "logic.h"

void drawRect(float x, float y, float width, float height, ALLEGRO_COLOR color)
{
	al_draw_filled_rectangle(x, y, x + width, y + height, color);
}

void drawChessboard(int m, int n, float field_width, float field_height, ALLEGRO_COLOR line_color, ALLEGRO_COLOR black_field_color, ALLEGRO_COLOR knight_field_color, ALLEGRO_COLOR visited_field_color, struct knight_pos knight, int **board, ALLEGRO_BITMAP *knight_image)
{
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			float i_multiplied = i*field_height;
			float j_multiplied = j*field_width;
			//black fields
			if ((i + j + 1) & 1)
			{
				drawRect(j_multiplied, i_multiplied, field_width, field_height, black_field_color);
			}
			//knight's position
			if (i == knight.y&&j == knight.x)
			{
				drawRect(j_multiplied, i_multiplied, field_width, field_height, knight_field_color);
				if (n < 30 && m<30) {
					if (n<m)
						al_draw_scaled_bitmap(knight_image, al_get_bitmap_x(knight_image), al_get_bitmap_y(knight_image), al_get_bitmap_width(knight_image), al_get_bitmap_height(knight_image), knight.x*field_width + 5, knight.y*field_height + 5, field_height - 10, field_height - 10, 0);
					else
						al_draw_scaled_bitmap(knight_image, al_get_bitmap_x(knight_image), al_get_bitmap_y(knight_image), al_get_bitmap_width(knight_image), al_get_bitmap_height(knight_image), knight.x*field_width + 5, knight.y*field_height + 5, field_width - 10, field_width - 10, 0);
				}

			}
			//visited field
			else if (board[i][j] == -1)
			{
				drawRect(j_multiplied, i_multiplied, field_width, field_height, visited_field_color);

			}

			//lines
			al_draw_line(0, i_multiplied, 720, i_multiplied, line_color, 2);
			al_draw_line(j_multiplied, 0, j_multiplied, 720, line_color, 2);
		}
	}

}

void drawControls(ALLEGRO_FONT*font, ALLEGRO_COLOR text_color, ALLEGRO_COLOR active_text_color, bool automove, bool draw_path)
{
	al_draw_text(font, text_color, 760, 320, 0, "CONTROLS:");


	al_draw_text(font, text_color, 760, 360, 0, "LMB");
	al_draw_text(font, text_color, 880, 360, 0, "SET NEW HORSE POSITION");


	al_draw_text(font, text_color, 760, 380, 0, "SPACE");
	if (automove)
	{
		al_draw_text(font, active_text_color, 880, 380, 0, "AUTOPLAY");
	}
	else
		al_draw_text(font, text_color, 880, 380, 0, "AUTOPLAY");


	al_draw_text(font, text_color, 760, 400, 0, "RIGHT ARROW");
	al_draw_text(font, text_color, 880, 400, 0, "NEXT STEP");


	al_draw_text(font, text_color, 760, 420, 0, "LEFT ARROW");
	al_draw_text(font, text_color, 880, 420, 0, "PREVIOUS STEP");


	al_draw_text(font, text_color, 760, 440, 0, "ENTER");
	if (draw_path)
	{
		al_draw_text(font, active_text_color, 880, 440, 0, "DRAW PATH");
	}
	else
		al_draw_text(font, text_color, 880, 440, 0, "DRAW PATH");


	al_draw_text(font, text_color, 760, 460, 0, "UP ARROW");
	al_draw_text(font, text_color, 880, 460, 0, "INCREASE MOVES PER FRAME");


	al_draw_text(font, text_color, 760, 480, 0, "DOWN ARROW");
	al_draw_text(font, text_color, 880, 480, 0, "DECREASE MOVES PER FRAME");

	al_draw_text(font, text_color, 760, 500, 0, "R");
	al_draw_text(font, text_color, 880, 500, 0, "RESET");

	al_draw_text(font, text_color, 760, 520, 0, "ESC");
	al_draw_text(font, text_color, 880, 520, 0, "EXIT");
}

void drawInfo(ALLEGRO_FONT*font, ALLEGRO_COLOR text_color, ALLEGRO_COLOR success_text_color, ALLEGRO_COLOR failure_text_color, ALLEGRO_COLOR background_color, int m, int n, int fields_not_visited, int starting_position_x, int starting_position_y, struct knight_pos knight, int possible_moves, int moves_per_frame)
{
	al_draw_textf(font, text_color, 760, 20, 0, "Fields to visit: %d", m*n);
	al_draw_textf(font, text_color, 760, 40, 0, "Unvisited fields: %d", fields_not_visited);
	al_draw_textf(font, text_color, 760, 60, 0, "Visited fields: %d  |  %0.2f%%", (m*n - fields_not_visited), ((m*n - fields_not_visited) / (m*n / 100.0)));

	al_draw_textf(font, text_color, 760, 100, 0, "Starting position: ");
	al_draw_textf(font, text_color, 760, 120, 0, "x: %d", starting_position_x);
	al_draw_textf(font, text_color, 840, 120, 0, "y: %d", starting_position_y);
	al_draw_textf(font, text_color, 760, 160, 0, "knight.x = %d", knight.x);
	al_draw_textf(font, text_color, 760, 180, 0, "knight.y = %d", knight.y);
	al_draw_textf(font, text_color, 760, 200, 0, "Possible moves = %d", possible_moves);
	al_draw_textf(font, text_color, 760, 220, 0, "Moves per frame = %d", moves_per_frame);

	if (possible_moves < m*n - 1)
	{
		al_draw_text(font, failure_text_color, 760, 80, 0, "Solution not found");
	}
	else
		al_draw_text(font, success_text_color, 760, 80, 0, "Solution  found");

	if (m*n - fields_not_visited - 1 == possible_moves)
	{
		al_draw_filled_rounded_rectangle(900, 570, 1100, 620, 3, 3, success_text_color);
		al_draw_text(font, background_color, 1000, 592, ALLEGRO_ALIGN_CENTER, "FINISHED");
	}
}

void drawPath(bool draw_path,int knight_move_id, int**knight_movement_history, float field_width, float field_height, ALLEGRO_COLOR color)
{
	if (draw_path)
	{
		for (int i = 0; i < knight_move_id; ++i)
		{
			al_draw_line(knight_movement_history[i][0] * field_width + field_width / 2, knight_movement_history[i][1] * field_height + field_height / 2, knight_movement_history[i + 1][0] * field_width + field_width / 2, knight_movement_history[i + 1][1] * field_height + field_height / 2, color, (field_width + field_height) / 20);
			al_draw_filled_circle(knight_movement_history[i][0] * field_width + field_width / 2, knight_movement_history[i][1] * field_height + field_height / 2, (field_width + field_height) / 20, color);
		}
	}
}

void drawHoveredField(int mouse_x,int mouse_y,float field_width,float field_height)
{
	if (mouse_x != -1 && mouse_y != -1)
	{
		drawRect(mouse_x*field_width, mouse_y*field_height, field_width, field_height, al_premul_rgba(255, 255, 0, 150));
	}
}
