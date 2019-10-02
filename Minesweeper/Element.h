#pragma once
#include <iostream>


class Element
{
private:
	bool mine{false};
	size_t mineCount{};
	//enum class Skin{};

public:
	Element(bool mine);
	friend std::ostream& operator<<(std::ostream& stream, const Element& el);
	bool getMine() const;
	size_t getMineCount() const;
	void incrementMineCount();
	void decrementMineCount();
};