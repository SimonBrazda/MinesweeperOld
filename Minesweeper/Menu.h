#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>

#include "Constants.h"
#include "Difficulty.h"
#include "TextBox.h"

class Menu
{
private:
	const Button begginerButton{ Position{window_width / 2 - 150, window_height / 2 - 150}, Size{180, 40}, 24, buttText1 };
	const Button intermediateButton{ Position{ window_width / 2 - 150, begginerButton.getButtPosition().y + 75 }, Size{180, 40}, 24, buttText2 };
	const Button expertButton{ Position{ window_width / 2 - 150, intermediateButton.getButtPosition().y + 75 }, Size{180, 40}, 24, buttText3 };
	const Button customButton{ Position{ window_width / 2 - 150, expertButton.getButtPosition().y + 75 }, Size{180, 40}, 24, buttText4 };
	const Difficulty begginerDifficulty{ begginer_field_width, begginer_field_height, begginer_mines_count, begginerButton};
	const Difficulty intermediateDifficulty{ intermediate_field_width, intermediate_field_height, intermediate_mines_count, intermediateButton };
	const Difficulty expertDifficulty{ expert_field_width, expert_field_height, expert_mines_count, expertButton };
	Difficulty customDifficulty{ 2, 2, 1, customButton };
	Difficulty selectedDifficulty{ begginer_field_width, begginer_field_height, begginer_mines_count, begginerButton };
	bool isMineFieldCreated{ false };
	std::shared_ptr<TextBox> widthTextBox = std::make_shared<TextBox>(0, Position{customDifficulty.getButton().getButtPosition().x + customDifficulty.getButton().getButtSize().width + 20, customDifficulty.getButton().getButtPosition().y}, Size{40, 40}, "2", 2 );
	std::shared_ptr<TextBox> heightTextBox = std::make_shared<TextBox>(1, Position{customDifficulty.getButton().getButtPosition().x + customDifficulty.getButton().getButtSize().width + 90, customDifficulty.getButton().getButtPosition().y}, Size{40, 40}, "2", 2 );
	std::shared_ptr<TextBox> numberOfMinesTextBox = std::make_shared<TextBox>(2, Position{customDifficulty.getButton().getButtPosition().x + customDifficulty.getButton().getButtSize().width + 160, customDifficulty.getButton().getButtPosition().y}, Size{60, 40}, "1", 3 );
	ALLEGRO_FONT* font = al_load_font("FFF.ttf", 20, 0);
	ALLEGRO_FONT* font1 = al_load_font("FFF.ttf", 24, 0);

public:
	
	void drawMenu()
	{
		al_clear_to_color(al_map_rgb_f(0, 0, 0));
		al_draw_rectangle(window_width / 2 - 302, window_height / 2 - 202, window_width / 2 + 302, window_height / 2 + 202, RED, 4);
		getBegginerDifficulty().getButton().drawButton();
		getIntermediateDifficulty().getButton().drawButton();
		getExpertDifficulty().getButton().drawButton();
		customDifficulty.getButton().drawButton();
		widthTextBox->drawTextBox();
		heightTextBox->drawTextBox();
		numberOfMinesTextBox->drawTextBox();
		al_draw_text(font, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 0, getBegginerDifficulty().getButton().getButtPosition().y - 40, 0, label1);
		al_draw_text(font, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 70, getBegginerDifficulty().getButton().getButtPosition().y - 40, 0, label2);
		al_draw_text(font, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 140, getBegginerDifficulty().getButton().getButtPosition().y - 40, 0, label3);

		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 20, getBegginerDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getBegginerDifficulty().getWidth())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 90, getBegginerDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getBegginerDifficulty().getHeight())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 160, getBegginerDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getBegginerDifficulty().getMinesCount())).c_str());
						 
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 20, getIntermediateDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getIntermediateDifficulty().getWidth())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 90, getIntermediateDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getIntermediateDifficulty().getHeight())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 160, getIntermediateDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getIntermediateDifficulty().getMinesCount())).c_str());
						 
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 20, getExpertDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getExpertDifficulty().getWidth())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 90, getExpertDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getExpertDifficulty().getHeight())).c_str());
		al_draw_text(font1, RED, getBegginerDifficulty().getButton().getButtPosition().x + 180 + 160, getExpertDifficulty().getButton().getButtPosition().y, 0, (std::to_string(getExpertDifficulty().getMinesCount())).c_str());
		al_flip_display();
	}
	
	TextBox getWidthTextBox() const { return *widthTextBox; }
	TextBox getHeightTextBox() const { return *heightTextBox; }
	TextBox getNumberOfMinesTextBox() const { return *numberOfMinesTextBox; }
	
	Difficulty getCustomDifficulty() const { return customDifficulty; }

	bool getIsMineFieldCreated() const
	{
		return isMineFieldCreated;
	}

	Button getCustomButton() const
	{
		return customButton;
	}

	bool setCustomDifficulty(Difficulty customDifficulty, ALLEGRO_DISPLAY* display)
	{
		if (customDifficulty.getWidth() <= 0 || customDifficulty.getWidth() > 60)
		{
			al_show_native_message_box(display, "Error MessageBox", "Error 0", "Width must be in range 1 to 60", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}
		else if(customDifficulty.getHeight() <= 0 || customDifficulty.getHeight() > 35)
		{
			al_show_native_message_box(display, "Error MessageBox", "Error 1", "Width must be in range 1 to 35", NULL, ALLEGRO_MESSAGEBOX_ERROR);
			return false;
		}
		else if (customDifficulty.getMinesCount() <= 0 || customDifficulty.getMinesCount() >= customDifficulty.getHeight() * customDifficulty.getWidth())
		{
			std::string range = "   Number of mines too high\nAdjusted to max amount" + (customDifficulty.getHeight() * customDifficulty.getWidth() - 1);
			al_show_native_message_box(display, "Warning MessageBox", "Warning 0", range.c_str() , NULL, ALLEGRO_MESSAGEBOX_WARN);
			customDifficulty.setMinesCount(customDifficulty.getHeight() * customDifficulty.getWidth() - 1);
			this->customDifficulty = customDifficulty;
			return false;
		}
		else
		{
			this->customDifficulty = customDifficulty;
			return true;
		}
	}

	void setIsMineFieldCreated(bool isMineFieldCreated)
	{
		this->isMineFieldCreated = isMineFieldCreated;
	}

	Difficulty getBegginerDifficulty() const
	{
		return begginerDifficulty;
	}
	Difficulty getIntermediateDifficulty() const
	{
		return intermediateDifficulty;
	}
	Difficulty getExpertDifficulty() const
	{
		return expertDifficulty;
	}
	Difficulty getSelectedDifficulty() const
	{
		return selectedDifficulty;
	}
	void setSelectedDifficulty(const Difficulty& selectedDifficulty)
	{
		this->selectedDifficulty = selectedDifficulty;
	}
};

