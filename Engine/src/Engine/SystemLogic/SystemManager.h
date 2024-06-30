#pragma once
#include "GameLogic//Scene.h"
#include "../FileOperations/FileManager.h"
#include "LightSystem.h"
#include <vector>

class SystemManager
{
public:
	static void StartUp();

	static void Start();
	static void Update();
	static void Render(sf::RenderWindow& Window);

	static int CreateGameObject(GameObject& ob);

	static void DestroyObject(std::string name);
	static void DestroyObject(int index);

	static bool CheckForCollision(sf::Sprite Sprite, int index = 0, Collision::collisionLayer LayerToCollideWith = Collision::ALL, GameObject* CollideInfo = nullptr);

	static void RunInput(sf::Event event);

	static void LoadScene(std::string scene);

public:

	static sf::Clock clock;
	static sf::Time deltaTimeT;

	static float deltaTime;

private:
	static Scene m_currentScene;
};

