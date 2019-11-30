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
#include <exception>

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include "Constants.h"

#include "Difficulty.h"
#include "TextBox.h"
#include "Menu.h"
#include "Button.h"
#include "Skin.h"
#include "Element.h"
#include "MineField.h"

int main()
{
	srand(time(nullptr));

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_TIMER* timer;

	al_init();
	al_init_image_addon();
	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_install_keyboard();
	al_install_mouse();

	display = al_create_display(1024, 680);
	queue = al_create_event_queue();
	timer = al_create_timer(1.0 / 60.0);
	
	al_set_window_title(display, "Minesweeper");

	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_mouse_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	bool running = true;
	bool isMenu = false;
	bool isMenuDrawned = false;
	bool isDifficulty = false;
	float x = 0, y = 0;
	unsigned mouseX = 0, mouseY = 0;
	int width = al_get_display_width(display);

	ALLEGRO_KEYBOARD_STATE keyboard;
	ALLEGRO_MOUSE_STATE mouse;

	al_start_timer(timer);

	Menu menu;

	std::shared_ptr<MineField> mineFieldPtr(nullptr);
	
	while (running)
	{
		ALLEGRO_EVENT event;
		if (isMenuDrawned == false)
		{
			menu.drawMenu();
			isMenuDrawned = true;
		}

		while (!isMenu && running)
		{
			while (!isDifficulty && running)
			{
				
					al_get_next_event(queue, &event);
					if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) return 0;
					al_get_mouse_state(&mouse);

					ALLEGRO_EVENT ev;
					al_wait_for_event(queue, &ev);
					
					if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
					{
						running = false;
						break;
					}

					if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
					{
						mouseX = event.mouse.x;
						mouseY = event.mouse.y;
						al_get_keyboard_state(&keyboard);

						menu.getWidthTextBox().switchCursor(mouse);
						menu.getHeightTextBox().switchCursor(mouse);
						menu.getNumberOfMinesTextBox().switchCursor(mouse);
						
						if (menu.getBegginerDifficulty().getButton().isMouseInButt(mouse))
						{
							menu.setSelectedDifficulty(menu.getBegginerDifficulty());
							isDifficulty = true;
						}
						if (menu.getIntermediateDifficulty().getButton().isMouseInButt(mouse))
						{
							menu.setSelectedDifficulty(menu.getIntermediateDifficulty());
							isDifficulty = true;
						}
						if (menu.getExpertDifficulty().getButton().isMouseInButt(mouse))
						{
							menu.setSelectedDifficulty(menu.getExpertDifficulty());
							isDifficulty = true;
						}
						if (menu.getCustomDifficulty().getButton().isMouseInButt(mouse))
						{
							try
							{
								menu.setCustomDifficulty(Difficulty{ std::stoi(*(menu.getWidthTextBox().getTextIntextBox())), std::stoi(*(menu.getHeightTextBox().getTextIntextBox())), std::stoi(*(menu.getNumberOfMinesTextBox().getTextIntextBox())), menu.getCustomButton() }, display);
							}
							catch (std::invalid_argument ex) 
							{
								al_show_native_message_box(display, "Error MessageBox", "Error 2", "TextBox value must have a value", NULL, ALLEGRO_MESSAGEBOX_ERROR);
								menu.setCustomDifficulty(Difficulty{ 2, 2, 1, menu.getCustomButton() }, display);
							}
							menu.setSelectedDifficulty(menu.getCustomDifficulty());
							isDifficulty = true;
						}
					}
					if (ev.type == ALLEGRO_EVENT_KEY_DOWN) {
						menu.getWidthTextBox().updateTextBox(ev.keyboard.keycode);
						menu.getWidthTextBox().updateCursor();
						menu.getHeightTextBox().updateTextBox(ev.keyboard.keycode);
						menu.getHeightTextBox().updateCursor();
						menu.getNumberOfMinesTextBox().updateTextBox(ev.keyboard.keycode);
						menu.getNumberOfMinesTextBox().updateCursor();
					}
					al_flip_display();
				
			}
			isMenu = true;
		}

		if (menu.getIsMineFieldCreated() != true)
		{
			auto mineFieldPtr1 = std::make_shared<MineField>(menu.getSelectedDifficulty().getWidth(), menu.getSelectedDifficulty().getHeight(), menu.getSelectedDifficulty().getMinesCount());
			mineFieldPtr = mineFieldPtr1;
			mineFieldPtr->drawInitialField();
			menu.setIsMineFieldCreated(true);
		}

		al_wait_for_event(queue, &event);

		ALLEGRO_KEYBOARD_STATE keyState;
		if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
			running = false;

		if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			al_get_mouse_state(&mouse);
			al_get_keyboard_state(&keyboard);
			mouseX = event.mouse.x;
			mouseY = event.mouse.y;
			if (event.mouse.button & 1)
			{
				if (mineFieldPtr->getIsEnabled())
				{
					bool isFinded = false;
					isFinded = mineFieldPtr->uncoverClearArea(isFinded, mouseX, mouseY);
					if (mineFieldPtr->getNumberOfMines() + mineFieldPtr->getUncoveredElementsCount() == mineFieldPtr->getTotalNumberOfElements())
					{
						mineFieldPtr->mineFieldCleared();
					}
				}
				if (mineFieldPtr)
				{
					if (mineFieldPtr->getNewGameButton().isMouseInButt(mouse))
					{
						menu.setIsMineFieldCreated(false);
						mineFieldPtr.reset();
					}
				}
				if (mineFieldPtr)
				{
					if (mineFieldPtr->getMenuButton().isMouseInButt(mouse))
					{
						isDifficulty = false;
						isMenu = false;
						isMenuDrawned = false;
						menu.setIsMineFieldCreated(false);
						mineFieldPtr.reset();
					}
				}
			}
			else if (event.mouse.button & 2 && mineFieldPtr->getIsEnabled())
			{
				mineFieldPtr->flagUpElement(mouseX, mouseY);
			}
		}

		
	}

	al_destroy_display(display);
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	
	al_uninstall_keyboard();
	al_uninstall_mouse();
}

