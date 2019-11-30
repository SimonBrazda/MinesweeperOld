#pragma once


class MineField
{
private:
	int numberOfElementsInRow, numberOfElementsInColumn, numberOfMines;
	std::vector<std::vector<Element>> field;
	const std::array<ALLEGRO_BITMAP*, 12> skins{ al_load_bitmap(".\\empty0.png"), al_load_bitmap(".\\empty1.png"),
		al_load_bitmap(".\\empty2.png"), al_load_bitmap(".\\empty3.png"), al_load_bitmap(".\\empty4.png"),
		al_load_bitmap(".\\empty5.png"), al_load_bitmap(".\\empty6.png"), al_load_bitmap(".\\empty7.png"),
		al_load_bitmap(".\\empty8.png"), al_load_bitmap(".\\mine.png"), al_load_bitmap(".\\default.png"),
		al_load_bitmap(".\\flag.png") };
	int fieldSizeX;
	int fieldSizeY;
	int offsetX;
	int offsetY;
	bool isInitialFieldDrawn{ false };
	bool isEnabled{ true };
	Button newGameButton{ Position{window_width / 2 - 170, offsetY - 50}, Size{120, 25}, 18, "New Game" };
	Button menuButton{ Position{window_width / 2 + 50, offsetY - 50}, Size{120, 25}, 18, "Menu" };
	int minesRevealed{};
	int uncoveredElementsCount{};
	int totalNumberOfElements;
	ALLEGRO_FONT* buttFont = al_load_font("FFF.ttf", 24, 0);

public:
	MineField(int numberOfElementsInRow, int numberOfElementsInColumn, int numberOfMines)
		: numberOfElementsInRow{ numberOfElementsInRow }, numberOfElementsInColumn{ numberOfElementsInColumn }, numberOfMines{ numberOfMines },
		  fieldSizeX{ element_size * numberOfElementsInRow }, fieldSizeY{ element_size * numberOfElementsInColumn }, offsetX{ window_width / 2 - fieldSizeX / 2 - element_size },
		offsetY{ window_height / 2 - fieldSizeY / 2 - element_size }, totalNumberOfElements{numberOfElementsInRow * numberOfElementsInColumn}
	{
		this->createField();
	}

	Button getMenuButton() const
	{
		return menuButton;
	}

	Button getNewGameButton() const
	{
		return newGameButton;
	}

	bool getIsEnabled() const
	{
		return isEnabled;
	}

	void setIsEnabled(bool isEnabled)
	{
		this->isEnabled = isEnabled;
	}

	int getMinesRevealed() const
	{
		return minesRevealed;
	}

	int getUncoveredElementsCount() const
	{
		return uncoveredElementsCount;
	}

	int getTotalNumberOfElements() const
	{
		return totalNumberOfElements;
	}

	int getNumberOfMines() const
	{
		return numberOfMines;
	}

	bool getIsInitialFieldDrawn() const
	{
		return isInitialFieldDrawn;
	}

	void createField()
	{
		field.reserve(numberOfElementsInRow);
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			std::vector<Element> column;
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				column.push_back(Element{ offsetX + (x * element_size), offsetY + (y * element_size) });
			}
			field.push_back(column);
		}
		fillFieldWithMines();
		setElementsMineCounts();
	}

	void fillFieldWithMines()
	{
		int minesCount{};
		while (minesCount < numberOfMines)
		{
			Position minePosition{ rand() % (numberOfElementsInRow), rand() % (numberOfElementsInColumn) };
			if (field[minePosition.x][minePosition.y].getIsMine() != true)
			{
				field[minePosition.x][minePosition.y].setIsMine(true);
				++minesCount;
			}
		}
	}

	void drawInitialField()
	{
		al_clear_to_color(al_map_rgb_f(0, 0, 0));
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				al_draw_bitmap(skins[10], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
			}
		}
		newGameButton.drawButton();
		menuButton.drawButton();
		al_flip_display();
		isInitialFieldDrawn = true;
	}

	void setElementsMineCounts()
	{
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				for (int xx = std::max(0, x - 1); xx <= std::min(numberOfElementsInRow, x + 1); xx++)
				{
					for (int yy = std::max(0, y - 1); yy <= std::min(numberOfElementsInColumn, y + 1); yy++)
					{
						if (!(x == xx && y == yy) &&
							xx < numberOfElementsInRow && yy < numberOfElementsInColumn)
						{
							if (field[xx][yy].getIsMine() && field[x][y].getIsMine() == false)
							{
								field[x][y].incrementMineCount();
							}
						}
					}
				}
			}
		}
	}

	void uncoverAllMines()
	{
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				if (field[x][y].getIsMine() == true)
					al_draw_bitmap(skins[9], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
			}
		}
		al_flip_display();
	}

	void updateField(int x, int y)
	{
		for (int xx = std::max(0, x - 1); xx <= std::min(numberOfElementsInRow, x + 1); xx++) {
			for (int yy = std::max(0, y - 1); yy <= std::min(numberOfElementsInColumn, y + 1); yy++) {
				if (!(x == xx && y == yy) &&
						xx < numberOfElementsInRow && yy < numberOfElementsInColumn && !field[xx][yy].getIsChecked()) {
					if (field[xx][yy].getMineCount() > 0) {
						++uncoveredElementsCount;
						drawMineCount(xx, yy);
						field[xx][yy].setIsRevealed(true);
						field[xx][yy].setIsChecked(true);
						displayNumberOfUncoveredElements();
					}
					else {
						field[xx][yy].setIsChecked(true);
						al_draw_bitmap(skins[0], field[xx][yy].elementPos.x, field[xx][yy].elementPos.y, 0);
						al_flip_display();
						field[xx][yy].setIsRevealed(true);
						++uncoveredElementsCount;
						displayNumberOfUncoveredElements();
						updateField(xx, yy);
					}
				}
			}
		}
	}

	void countMines()
	{
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				for (int xx = std::max(0, x - 1); xx <= std::min(numberOfElementsInRow, x + 1); xx++)
				{
					for (int yy = std::max(0, y - 1); yy <= std::min(numberOfElementsInColumn, y + 1); yy++)
					{
						if (!(x == xx && y == yy) &&
							xx < numberOfElementsInRow && yy < numberOfElementsInColumn)
						{
							if (field[xx][yy].getIsMine() && field[x][y].getIsMine() == false)
							{
								field[x][y].incrementMineCount();
							}
						}
					}
				}
			}
		}
	}

	void drawMineCount(int x, int y)
	{
		for (int i{ 1 }; i <= 8; i++)
		{
			if (field[x][y].getMineCount() == i)
			{
				al_draw_bitmap(skins[i], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
				al_flip_display();
				break;
			}
		}
	}

	bool uncoverClearArea(bool& isFinded, const int& mouseX, const int& mouseY)
	{
		for (int x{}; x < numberOfElementsInRow && !isFinded; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				if (mouseX >= field[x][y].elementPos.x && mouseX < field[x][y].elementPos.x + element_size &&
					mouseY >= field[x][y].elementPos.y && mouseY < field[x][y].elementPos.y + element_size && field[x][y].getIsFlaged())
					break;
				if (mouseX >= field[x][y].elementPos.x && mouseX < field[x][y].elementPos.x + element_size &&
					mouseY >= field[x][y].elementPos.y && mouseY < field[x][y].elementPos.y + element_size)
				{
					if (field[x][y].getIsMine() == true)
					{
						isEnabled = false;
						uncoverAllMines();
					}
					else if (field[x][y].getMineCount() > 0 && !field[x][y].getIsChecked())
					{
						drawMineCount(x, y);
						field[x][y].setIsRevealed(true);
						field[x][y].setIsChecked(true);
						++uncoveredElementsCount;
						displayNumberOfUncoveredElements();
					}
					else if (!field[x][y].getIsChecked())
					{
						al_draw_bitmap(skins[0], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
						al_flip_display();
						field[x][y].setIsRevealed(true);
						field[x][y].setIsChecked(true);
						++uncoveredElementsCount;
						displayNumberOfUncoveredElements();
						updateField(x, y);
						
					}
					isFinded = true;
					break;
				}
			}
		}
		return isFinded;
	}

	void flagUpElement(const int& mouseX, const int& mouseY)
	{
		bool isDone{ false };
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				if (mouseX >= field[x][y].elementPos.x && mouseX < field[x][y].elementPos.x + element_size &&
					mouseY >= field[x][y].elementPos.y && mouseY < field[x][y].elementPos.y + element_size)
				{
					if (field[x][y].getIsFlaged() == true && field[x][y].getIsRevealed() == false)
					{
						al_draw_bitmap(skins[10], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
						al_flip_display();
						field[x][y].setIsFlaged(false);
						if(field[x][y].getIsMine())
							--minesRevealed;
						isDone = true;
						break;
					}
					else if (field[x][y].getIsFlaged() == false && field[x][y].getIsRevealed() == false)
					{
						al_draw_bitmap(skins[11], field[x][y].elementPos.x, field[x][y].elementPos.y, 0);
						al_flip_display();
						field[x][y].setIsFlaged(true);
						if (field[x][y].getIsMine())
							++minesRevealed;
						isDone = true;
						break;
					}
				}
			}
			if (isDone)
				break;
		}
	}

	void mineFieldCleared()
	{
		al_draw_text(buttFont, RED, window_width / 2 - 250, window_height / 2 + fieldSizeY + 50, 0, "Minefield succesfully cleared!");
		al_flip_display();
	}

	void displayNumberOfUncoveredElements() const
	{

		std::cout << uncoveredElementsCount << std::endl;
		/*
		al_draw_text(buttFont, RED, 200, 350, 0, (std::to_string(uncoveredElementsCount)).c_str());
		al_flip_display();
		*/
	}

	void printMineField()
	{
		for (int x{}; x < 8; x++)
		{
			for (int y{}; y < 8; y++)
			{
				std::cout << field[x][y].getIsMine() << " ";
			}
			std::cout << std::endl;
		}
	}

	void printMineCount()
	{
		for (int x{}; x < numberOfElementsInRow; x++)
		{
			for (int y{}; y < numberOfElementsInColumn; y++)
			{
				std::cout << field[x][y].getMineCount() << " ";
			}
			std::cout << std::endl;
		}
	}
};

