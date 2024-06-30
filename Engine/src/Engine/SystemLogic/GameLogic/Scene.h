#pragma once
#include "..//..//Objects/Camera.h"
#include "..//..//Objects/GameObject.h"


class Scene
{
public:
	Scene(sf::RenderWindow& window, float width, float height);
	Scene(sf::RenderWindow& window, sf::Vector2f windowSize);

	std::vector<GameObject*>& getObjects();

	int addObject(GameObject*);

	void DestroyObject(int index);
	void DestroyObject(std::string name);
	bool CheckExisitingObject(std::string name);

	void LoadSceneFromFile(std::string Scene);

public:
	Camera camera;

private:
	std::vector<GameObject*> m_objects;
	std::string name;
};