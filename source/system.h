#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>
#include <Windows.h>

#ifndef SYSTEM_H
#define SYSTEM_H

void abortGame(const char* message);

void initAllegro(ALLEGRO_TIMER** timer, ALLEGRO_DISPLAY** display, ALLEGRO_BITMAP**knight_image, ALLEGRO_EVENT_QUEUE** event_queue, bool * done, int width, int height);

void shutdownAllegro(ALLEGRO_DISPLAY**display, ALLEGRO_TIMER**timer, ALLEGRO_EVENT_QUEUE**event_queue);

#endif
