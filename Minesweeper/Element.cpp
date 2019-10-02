#include "Element.h"

Element::Element(bool mine) : mine{ mine } {};

std::ostream& operator<<(std::ostream& stream, const Element& el)
{
	return stream << el.mine;
}

bool Element::getMine() const
{
	return mine;
}

size_t Element::getMineCount() const
{
	return mineCount;
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