#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>
#include <memory>
#include <utility>
#include <algorithm>
#include <cstdlib> //for random number generator
#include <ctime>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "Element.h"
#include "Scene.h"

size_t rand50()
{
	return rand() & 1;
}

bool rand25()
{
	return rand50() & rand50();
}

void loadInitialScene(ALLEGRO_BITMAP* hiddenElement, const unsigned& displayWidth, const unsigned& displayHeight)
{
	const int size{ 8 };
	const int elementSize = 16;
	const int offset{ -elementSize *  size / 2};
	al_clear_to_color(al_map_rgb_f(1, 1, 1));
	for (size_t n{}; n < size * elementSize; n += elementSize)
	{
		for (size_t i{}; i < size * elementSize; i += elementSize)
		{
			al_draw_bitmap(hiddenElement, (displayWidth / 2 + i + offset), (displayHeight / 2 + n + offset), 0);
		}
	}
	al_flip_display();

}

void generateMineField()
{

}
//bal
void countMines(std::vector<std::vector<Element>>& scene)
{
	for (size_t x{}; x < 8; x++)
	{
		for (size_t y{}; y < 8; y++)
		{
			if (x == 0 && y == 0)
			{
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				if(scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if(scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x == 7 && y == 0)
			{
				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x == 0 && y == 7)
			{
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x == 7 && y == 7)
			{
				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x > 0 && x < 7 && y == 0)
			{
				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x > 0 && x < 7 && y == 7)
			{
				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x == 7 && y > 0 && y < 7)
			{
				if (scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x - 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x == 0 && y > 0 && y < 7)
			{
				if (scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
			}

			if (x > 0 && x < 7 && y > 0 && y < 7)
			{
				if (scene[x - 1][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y + 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y + 1].getMine())
					scene[x][y].incrementMineCount();

				if (scene[x - 1][y].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y].getMine())
					scene[x][y].incrementMineCount();
				
				if (scene[x - 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x][y - 1].getMine())
					scene[x][y].incrementMineCount();
				if (scene[x + 1][y - 1].getMine())
					scene[x][y].incrementMineCount();
			}
		}
	}
}

struct Size
{
	size_t x;
	size_t y;
};

int main()
{
	srand(time(nullptr));

	const unsigned displayWidth{ 1024 }, displayHeight{ 768 };
	
	std::vector<std::vector<Element>> scene;
	scene.reserve(8);

	for (size_t i{}; i < 8; i++)
	{
		scene.push_back(std::vector<Element> { Element{rand25()}, Element{rand25()}, Element{rand25()}, Element{rand25()},
											   Element{rand25()}, Element{rand25()}, Element{rand25()}, Element{rand25()} });
	}
	
	enum class SizeOption { small = 16, medium = 32, large = 64 };

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;
	//ALLEGRO_FONT* font;
	ALLEGRO_BITMAP* hiddenElement = nullptr;
	ALLEGRO_BITMAP* element0 = nullptr;
	ALLEGRO_BITMAP* element1 = nullptr;
	ALLEGRO_BITMAP* element2 = nullptr;
	ALLEGRO_BITMAP* element3 = nullptr;
	ALLEGRO_BITMAP* element4 = nullptr;
	ALLEGRO_BITMAP* element5 = nullptr;
	ALLEGRO_BITMAP* element6 = nullptr;
	ALLEGRO_BITMAP* element7 = nullptr;
	ALLEGRO_BITMAP* element8 = nullptr;
	ALLEGRO_BITMAP* mineElement = nullptr;
	

	al_init();

	al_init_image_addon();
	al_init_primitives_addon();

	display = al_create_display(1024, 680);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);

	hiddenElement = al_load_bitmap(".\\default.png");
	assert(hiddenElement != nullptr);
	element0 = al_load_bitmap(".\\empty0.png");
	element1 = al_load_bitmap(".\\empty1.png");
	element2 = al_load_bitmap(".\\empty2.png");
	element3 = al_load_bitmap(".\\empty3.png");
	element4 = al_load_bitmap(".\\empty4.png");
	element5 = al_load_bitmap(".\\empty5.png");
	element6 = al_load_bitmap(".\\empty6.png");
	element7 = al_load_bitmap(".\\empty7.png");
	element8 = al_load_bitmap(".\\empty8.png");
	mineElement = al_load_bitmap(".\\mine.png");

	al_install_keyboard();
	al_install_mouse();

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool running = true;
	float x = 0, y = 0;
	int width = al_get_display_width(display);

	al_start_timer(timer);

	loadInitialScene(hiddenElement, displayWidth, displayHeight);

	while (running)
	{
		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);


		ALLEGRO_KEYBOARD_STATE keyState;
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;
		/*
		//mouse
		if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			x = event.mouse.x;
			y = event.mouse.y;
		}
		*/

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			
		}

		/*
		ALLEGRO_KEYBOARD_STATE keyState;
		al_get_keyboard_state(&keyState);

		if (al_key_down(&keyState, ALLEGRO_KEY_RIGHT))
			if (al_key_down(&keyState, ALLEGRO_KEY_LCTRL))
				x += 10;
			else
				x += 1;
		*/
		/*
		if (event.type == ALLEGRO_EVENT_TIMER)
		{
			al_clear_to_color(al_map_rgb_f(1, 1, 1));
			al_draw_bitmap(hiddenElement, (displayWidth / 2), (displayHeight / 2), 0);
			al_draw_bitmap(hiddenElement, 500, 0, 0);
			al_flip_display();
		}
		
		if (x > width)
			x = -al_get_bitmap_width(bitmap);
		*/
	}

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_destroy_bitmap(hiddenElement);
	al_destroy_bitmap(element0);
	al_destroy_bitmap(element1);
	al_destroy_bitmap(element2);
	al_destroy_bitmap(element3);
	al_destroy_bitmap(element4);
	al_destroy_bitmap(element5);
	al_destroy_bitmap(element6);
	al_destroy_bitmap(element7);
	al_destroy_bitmap(element8);
	al_destroy_bitmap(mineElement);
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

