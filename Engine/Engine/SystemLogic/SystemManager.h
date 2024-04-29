#pragma once
#include "../GameObject.h"
#include "../FileOperations/FileManager.h"
#include <vector>

class SystemManager
{
public:
	static void Start();
	static void Update(float DeltaTime);
	static void Render(sf::RenderWindow& Window);

	static void CreateGameObject(const GameObject& Ob);

	static bool CheckForCollision(sf::Sprite Sprite, int index = 0, Collision::collisionLayer LayerToCollideWith = Collision::ALL, GameObject* CollideInfo = nullptr);

	static void RunInput(sf::Event event);

public:
	static std::vector <GameObject*> objects;
};

