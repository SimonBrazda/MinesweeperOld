#pragma once
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_primitives.h>

#include <string>
#include <vector>
#include <memory>
#include "Constants.h"

class TextBox
{
private:
	std::shared_ptr<std::string> textInTextBox;
	std::shared_ptr<int> cursorPos;
	const int numberSigns;
	ALLEGRO_FONT* textBoxFont = al_load_font("FFF.ttf", 24, 0);
	const int textBoxNumber;
	const int cursorShift;

	Position textBoxPos;
	Size textBoxSize;

public:
	inline static int numberOfTextBoxes;
	inline static std::vector<int> switch_text_boxes;

	TextBox(const int textBoxNumber, Position textBoxPos, Size textBoxSize, std::string textInTextBox, const int numberSigns)
		: textBoxNumber{ textBoxNumber }, textBoxPos{ textBoxPos }, textBoxSize{ textBoxSize }, cursorShift{ textBoxPos.x + 2 }, numberSigns{numberSigns}
	{
		this->textInTextBox = std::make_shared<std::string>(textInTextBox);
		++numberOfTextBoxes;
		for (int i = 0; i < numberOfTextBoxes; i++)
		{
			switch_text_boxes.push_back(0); // the textboxes are inactive 
		}

		cursorPos = std::make_shared<int>(textBoxPos.x + 18);
	}

	auto getTextIntextBox() const { return textInTextBox; }

	Position getTextBoxPos() const
	{
		return textBoxPos;
	}

	bool isMouseInTextBox(ALLEGRO_MOUSE_STATE& mouse)
	{
		if (mouse.x > textBoxPos.x && mouse.x < textBoxSize.width && mouse.y > textBoxPos.y && mouse.y < textBoxSize.height && mouse.buttons == 1)
			return true;
	}

	void switchCursor(ALLEGRO_MOUSE_STATE& mouse)
	{
		if (mouse.x > textBoxPos.x && mouse.x < textBoxPos.x + textBoxSize.width && mouse.y > textBoxPos.y && mouse.y < textBoxPos.y + textBoxSize.height)
		{
			for (int i = 0; i < numberOfTextBoxes; i++)
			{
				switch_text_boxes[i] = 0;
			}

			switch_text_boxes[textBoxNumber] = 1;		// activation of the textbox when press the rectangle  
			al_draw_line(*cursorPos, textBoxPos.y + 4, *cursorPos, textBoxPos.y + 34, RED, 1);
		}
		else
		{
			al_draw_line(*cursorPos, textBoxPos.y + 4, *cursorPos, textBoxPos.y + 34, BLACK, 1);
		}
	}

	void updateCursor()
	{
		if(switch_text_boxes[textBoxNumber])
			al_draw_line(*cursorPos, textBoxPos.y + 4, *cursorPos, textBoxPos.y + 34, RED, 1);
	}

	void updateTextBox()
	{
		al_draw_text(textBoxFont, RED, textBoxPos.x + 2, textBoxPos.y, 0, textInTextBox->c_str());
	}

	void updateTextBox(int keycode)
	{
		if (switch_text_boxes[textBoxNumber]) 		// active the textbox
		{
			al_draw_filled_rectangle(textBoxPos.x + 1, textBoxPos.y + 1, textBoxPos.x + textBoxSize.width - 2, textBoxPos.y + textBoxSize.height - 2, al_map_rgba(0, 0, 0, 255));	// border of the textbox
			al_flip_display();

				if ((keycode >= 37 && keycode <= 47) || (keycode >= 96 && keycode <= 105))
				{
					if (textInTextBox->length() < numberSigns)
					{
						if (keycode >= 96 && keycode <= 105) {
							textInTextBox->insert((*cursorPos - cursorShift) / 16, std::to_string(static_cast<char>(keycode - 96)));
							*cursorPos += 24;
							al_rest(0.15);
						}
						else if (keycode >= 37 && keycode <= 47) {
							textInTextBox->insert((*cursorPos - cursorShift) / 16, std::to_string(static_cast<char>(keycode - 37)));
							*cursorPos += 16;
							al_rest(0.15);
						}
						
					}
				}
			if (keycode == ALLEGRO_KEY_BACKSPACE)
			{
				if (textInTextBox->length() > 0 && *cursorPos != cursorShift)
				{
					*textInTextBox = textInTextBox->erase(((*cursorPos - cursorShift) / 16) - 1, 1);
				}

				if (*cursorPos > cursorShift + 15)
				{
					*cursorPos -= 16;
				}

				al_rest(0.15);
			}

			if (keycode == ALLEGRO_KEY_LEFT)
			{
				if (*cursorPos > cursorShift + 15)
				{
					*cursorPos -= 16;
				}
				al_rest(0.15);
			}

			if (keycode == ALLEGRO_KEY_RIGHT)
			{
				if (*cursorPos < cursorShift + 15 * textInTextBox->length())
				{
					*cursorPos += 16;
				}
				al_rest(0.15);
			}
			al_draw_text(textBoxFont, RED, textBoxPos.x + 2, textBoxPos.y, 0, textInTextBox->c_str());
		}
		else
		{
			al_draw_line(*cursorPos, textBoxPos.y + 4, *cursorPos, textBoxPos.y + 34, BLACK, 1);
		}
	}

	void drawTextBox()
	{
		al_draw_rectangle(textBoxPos.x, textBoxPos.y, textBoxPos.x + textBoxSize.width, textBoxPos.y + textBoxSize.height, RED, 2);	// border of the textbox
		updateTextBox();
	}
};

