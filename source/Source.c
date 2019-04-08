#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "graphics.h"
#include "system.h"
#include "logic.h"

int main()
{
	ALLEGRO_EVENT_QUEUE* event_queue;
	ALLEGRO_DISPLAY* display;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* knight_image;

	bool done = true;
	bool redraw = false;
	bool action = false;
	bool automove = false;
	bool draw_path = true;

	//board height and width
	int m = 8;
	int n = 8;

	float width = 1280.0f;
	float height = 720.0f;

	float field_height = height / m;
	float field_width = height / n;

	//Allegro modules
	initAllegro(&timer, &display,&knight_image, &event_queue, &done, width, height);

	
	ALLEGRO_FONT* font = al_create_builtin_font();

	ALLEGRO_COLOR black = al_map_rgb(0, 0, 0);
	ALLEGRO_COLOR blue = al_map_rgb(50, 160, 255);
	ALLEGRO_COLOR green = al_map_rgb(40, 200, 90);
	ALLEGRO_COLOR white = al_map_rgb(220, 220, 210);
	ALLEGRO_COLOR grey = al_map_rgb(50, 50, 50);
	ALLEGRO_COLOR red = al_map_rgb(220, 70, 90);

	//calloc memory for board
	int **board;
	board = (int **)calloc(m, sizeof(int*));
	for (int i = 0; i < m; i++)
		board[i] = (int*)calloc(n, sizeof(int));

	//calloc memory for knight's movement history
	int **knight_movement_history;
	knight_movement_history = (int **)calloc(m*n, sizeof(int*));
	for (int i = 0; i < m*n; i++)
		knight_movement_history[i] = (int*)calloc(2, sizeof(int));


	int knight_move_id=0;
	int fields_not_visited=m*n-1;
	int possible_moves = -1;
	int moves_per_frame = 1;
	int moves_to_make = moves_per_frame;
	
	int mouse_x = -1;
	int mouse_y = -1;

	
	struct knight_pos knight;
	

	//save moves with starting position 0,0 and check field as visited
	knight.x = 0;
	knight.y = 0;
	saveKnightMovesToArray(&possible_moves, knight_movement_history, board,m,n,knight);
	board[knight.y][knight.x] = -1;

	al_start_timer(timer);
	
	

	while (!done)
	{
		
		//main rendering
		if (redraw && al_is_event_queue_empty(event_queue))
		{
			redraw = false;
			
			al_clear_to_color(white);
				
			drawChessboard(m, n, field_width, field_height, black, grey, blue, green, knight, board, knight_image);
			
			drawHoveredField(mouse_x, mouse_y, field_width, field_height);
			
			drawPath(draw_path,knight_move_id, knight_movement_history, field_width, field_height, black);

			drawInfo(font, black, green, red, white, m, n, fields_not_visited, knight_movement_history[0][0], knight_movement_history[0][1], knight, possible_moves, moves_per_frame);
			
			drawControls(font, black, green, automove, draw_path);

			//vertical line separatin board from info
			al_draw_line(height, 0, height, height, black, 2);
			
			al_flip_display();
			
		}

		//--------------------------------------------------
		// handling events (timer, keyboard, mouse)
		//--------------------------------------------------
		ALLEGRO_EVENT event;
		al_wait_for_event(event_queue, &event);
		
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			done = true;
		}
		else if (event.type == ALLEGRO_EVENT_TIMER) 
		{
			
			if (automove && !redraw && (knight_move_id < possible_moves))
			{
				//handle automove
				while (moves_to_make && (knight_move_id < possible_moves))
				{
					goForward(&knight_move_id, &knight, knight_movement_history, board, &fields_not_visited);
					moves_to_make -= 1;
				}
				moves_to_make = moves_per_frame;
				if (knight_move_id == possible_moves)
					automove = false;

				redraw = true;
			}
			else if (action && !redraw)
			{
				action = false;
				redraw = true;
			}	
			
		}
		else if (event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			
				if (event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					done = true;
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT && (knight_move_id < possible_moves))
				{
					goForward(&knight_move_id, &knight, knight_movement_history, board, &fields_not_visited);
					if (!action)
					{
						action = true;
					}
				}
				if ((event.keyboard.keycode == ALLEGRO_KEY_LEFT) && (knight_move_id > 0))
				{
					goBack(&knight_move_id, &knight, knight_movement_history, board, &fields_not_visited);
					if (!action)
					{
						action = true;
					}
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_SPACE)
				{
					if (automove == false)
					{
						automove = true;
					}
					else
					{
						automove = false;
					}
					if (!action)
					{
						action = true;
					}
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_ENTER || event.keyboard.keycode == ALLEGRO_KEY_PAD_ENTER)
				{
					if (draw_path == false)
					{
						draw_path = true;
					}
					else
					{
						draw_path = false;
					}
					if (!action)
					{
						action = true;
					}
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					moves_per_frame += 10;

					if (!action)
					{
						action = true;
					}
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					if (moves_per_frame >= 10)
					{
						moves_per_frame -= 10;
					}
					if (!action)
					{
						action = true;
					}
				}
				if (event.keyboard.keycode == ALLEGRO_KEY_R)
				{
					//reset do startowej pozycji

					for (int i = 0; i < m; ++i)
					{
						for (int j = 0; j < n; ++j)
						{
							board[i][j] = 0;
						}
					}

					knight_move_id = 0;
					knight.x = knight_movement_history[0][0];
					knight.y = knight_movement_history[0][1];
					board[knight.y][knight.x] = -1;
					fields_not_visited = m*n - 1;
					if (automove)
					{
						automove = false;
					}

					if (!action)
					{
						action = true;
					}
				}
			
			
		}
		else if(event.type==ALLEGRO_EVENT_MOUSE_AXES)
		{
			if (event.mouse.x < height&&event.mouse.x >= 0 && event.mouse.y<height&&event.mouse.y >= 0)
			{
				if (mouse_x != (int)(event.mouse.x / field_width) || mouse_y != (int)(event.mouse.y / field_height))
				{
					mouse_x = event.mouse.x / field_width;
					mouse_y = event.mouse.y / field_height;

					if (!action)
					{
						action = true;
					}
				}
				
			}
			else if (mouse_x!=-1 || mouse_y!=-1)
			{
				mouse_x = -1;
				mouse_y = -1;
				if (!action)
				{
					action = true;
				}
			}
		}
		else if (event.type== ALLEGRO_EVENT_MOUSE_BUTTON_DOWN&&event.mouse.button==1)
		{
			//choosing new knight's position
			if (event.mouse.x < height&&event.mouse.x>=0&&event.mouse.y<height&&event.mouse.y>=0)
			{
				knight.x = event.mouse.x / field_width;
				knight.y = event.mouse.y / field_height;
				knight_move_id = 0;
				fields_not_visited = m*n - 1;
				possible_moves = -1;

				saveKnightMovesToArray(&possible_moves, knight_movement_history, board, m, n, knight);

				board[knight.y][knight.x] = -1;
				if (automove)
				{
					automove = false;
				}
				if (!action)
				{
					action = true;
				}
			}
		}
		//--------------------------------------------------
		// end of events 
		//--------------------------------------------------

	}
	
	for (int i = 0; i < m; i++)
		free(board[i]);
	free(board);

	for (int i = 0; i < m*n; i++)
		free(knight_movement_history[i]);
	free(knight_movement_history);

	al_destroy_bitmap(knight_image);
	shutdownAllegro(&display, &timer, &event_queue);

	return 0;
}