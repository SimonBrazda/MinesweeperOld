#include "Element.h"

Element::Element(int x, int y) : elementPos{ x, y } {}


std::ostream& operator<<(std::ostream& stream, const Element& el)
{
	return stream << el.isMine;
}

bool Element::getIsMine() const
{
	return isMine;
}

void Element::setIsMine(bool isMine)
{
	this->isMine = isMine;
}

bool Element::getIsFlaged() const
{
	return isFlaged;
}

void Element::setIsFlaged(bool isFlaged)
{
	this->isFlaged = isFlaged;
}

bool Element::getIsRevealed() const
{
	return isRevealed;
}

void Element::setIsRevealed(bool isRevealed)
{
	this->isRevealed = isRevealed;
}

int Element::getMineCount() const
{
	return mineCount;
}

bool Element::getIsChecked() const
{
	return isChecked;
}

void Element::setIsChecked(bool isChecked)
{
	this->isChecked = isChecked;
}

void Element::incrementMineCount()
{
	if(mineCount < 8)
		++mineCount;
}

void Element::decrementMineCount()
{
	if(mineCount > 0)
		--mineCount;
}