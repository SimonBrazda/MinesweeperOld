#pragma once
#include <string>

#include "Constants.h"

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

class Button
{
private:
	Position buttPosition{};
	Size buttSize;
	int fontSize;
	const char* buttText;
	ALLEGRO_FONT* buttFont = al_load_font("FFF.ttf", fontSize, 0);

public:
	Button(const Position& buttPosition, const Size& buttSize, int fontSize, const char* buttText) :
		buttPosition{ buttPosition }, buttSize{ buttSize }, fontSize{fontSize}, buttText{ buttText } {}

	Position getButtPosition() const;
	Size getButtSize() const;

	void drawButton() const;
	bool isMouseInButt(ALLEGRO_MOUSE_STATE& mouse) const;
};

