#pragma once
#include "Button.h"
#include <string>

class Difficulty
{
private:
	int width, height;
	int minesCount;
	Button button;

public:
	Difficulty(int width, int height, int minesCount, const Button& button)
		: width{ width }, height{ height }, minesCount{ minesCount }, button{button} {}

	Difficulty(const Button& button)
		: button{ button } {}

	Button getButton() const
	{
		return button;
	}

	int getWidth() const
	{
		return width;
	}
	int getHeight() const
	{
		return height;
	}
	int getMinesCount() const
	{
		return minesCount;
	}
	void setHeight(int height)
	{
		this->height = height;
	}
	void setWidth(int width)
	{
		this->width = width;
	}
	void setMinesCount(int minesCount)
	{
		this->minesCount = minesCount;
	}
};