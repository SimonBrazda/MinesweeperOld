#pragma once
#include <iostream>
#include <allegro5/allegro_image.h>

#include "Constants.h"

class Element
{
private:
	bool isMine{ false };
	bool isFlaged{ false };
	bool isRevealed{ false };
	int mineCount{};
	bool isChecked{ false };

public:
	Element(int x, int y);

	bool getIsMine() const;
	void setIsMine(bool isMine);
	bool getIsFlaged() const;
	void setIsFlaged(bool isFlaged);
	bool getIsRevealed() const;
	void setIsRevealed(bool isRevealed);
	int getMineCount() const;
	bool getIsChecked() const;
	void setIsChecked(bool isChecked);

	void incrementMineCount();
	void decrementMineCount();

	Position elementPos;
	friend std::ostream& operator<<(std::ostream& stream, const Element& el);
};