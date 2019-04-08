#include "system.h"

void abortGame(const char* message)
{
	MessageBox(0, message, "Error", MB_OK);
	exit(1);
}

void initAllegro(ALLEGRO_TIMER** timer, ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP**knight_image, ALLEGRO_EVENT_QUEUE** event_queue, bool * done, int width, int height)
{
	if (!al_init())
		abortGame("Failed to initialize allegro");

	if (!al_init_image_addon())
		abortGame("Failed to initialize images addon");

	if (!al_init_primitives_addon())
		abortGame("Failed to initialize primitives addon");

	if (!al_init_font_addon())
		abortGame("Failed to initialize font addon");


	if (!al_install_keyboard())
		abortGame("Failed to install keyboard");

	if (!al_install_mouse())
		abortGame("Failed to install mouse");

	(*timer) = al_create_timer(1.0 / 30);
	if (!(*timer))
		abortGame("Failed to create timer");

	al_set_new_window_title("Knight's tour");
	(*display) = al_create_display(width, height);
	if (!(*display))
		abortGame("Failed to create display");

	(*knight_image) = al_load_bitmap("knight.png");
	if (!(*knight_image))
		abortGame("Failed to load knight image");

	(*event_queue) = al_create_event_queue();
	if (!(*event_queue))
		abortGame("Failed to create event queue");

	al_register_event_source((*event_queue), al_get_keyboard_event_source());
	al_register_event_source((*event_queue), al_get_mouse_event_source());
	al_register_event_source((*event_queue), al_get_timer_event_source((*timer)));
	al_register_event_source((*event_queue), al_get_display_event_source((*display)));

	*done = false;
}

void shutdownAllegro(ALLEGRO_DISPLAY**display, ALLEGRO_TIMER**timer, ALLEGRO_EVENT_QUEUE**event_queue)
{
	al_destroy_display(*display);
	al_uninstall_keyboard();
	al_uninstall_mouse();
	al_destroy_timer(*timer);
	al_destroy_event_queue(*event_queue);
}
