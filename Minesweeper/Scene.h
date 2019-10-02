#pragma once
#include <vector>

class Scene
{
private:
	size_t width, height;
	std::vector<std::vector<Element> > scene;
public:
	Scene(size_t width = 2, size_t height = 2);
	//void drawScene() const;
};

