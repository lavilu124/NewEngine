#pragma once
#include "../Objects/GameObject.h"
#include "../FileOperations/FileManager.h"
#include <vector>

class SystemManager
{
public:
	static void StartUp();

	static void Start();
	static void Update();
	static void Render(sf::RenderWindow& Window);

	static void CreateGameObject(const GameObject& Ob);

	static bool CheckForCollision(sf::Sprite Sprite, int index = 0, Collision::collisionLayer LayerToCollideWith = Collision::ALL, GameObject* CollideInfo = nullptr);

	static void RunInput(sf::Event event);

public:
	static std::vector <GameObject*> objects;

	static sf::Clock clock;
	static sf::Time deltaTimeT;

	static float deltaTime;
};

