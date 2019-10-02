#include "Scene.h"

Scene::Scene(size_t width, size_t height) : width{ width }, height{ height }
{
	for (size_t i{}; i < width; i++)
		scene.push_back(std::vector<Element>{rand25()});
}
