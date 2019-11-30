#include "Button.h"

Position Button::getButtPosition() const
{
	return buttPosition;
}

Size Button::getButtSize() const
{
	return buttSize;
}

void Button::drawButton() const
{
	al_draw_rectangle(buttPosition.x, buttPosition.y, buttPosition.x + buttSize.width, buttPosition.y + buttSize.height, RED, 2);
	al_draw_text(buttFont, RED, buttPosition.x + butt_text_x_offset, buttPosition.y, 0, buttText);
}

bool Button::isMouseInButt(ALLEGRO_MOUSE_STATE& mouse) const
{
	return mouse.x >= buttPosition.x && mouse.x <= buttPosition.x + buttSize.width &&
		mouse.y >= buttPosition.y && mouse.y <= buttPosition.y + buttSize.height;
}