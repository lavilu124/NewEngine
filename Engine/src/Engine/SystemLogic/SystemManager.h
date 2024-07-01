#pragma once
#include "GameLogic//Scene.h"
#include "../FileOperations/FileManager.h"
#include "LightSystem.h"
#include <vector>

class SystemManager
{
public:
	static void StartUp(sf::RenderWindow& window);

	static void ClearSystem();

	static void Update();
	static void Render(sf::RenderWindow& window);

	static int CreateGameObject(GameObject& ob);

	static void DestroyObject(std::string name);
	static void DestroyObject(int index);

	static bool CheckForCollision(sf::Sprite sprite, int index = 0, Collision::collisionLayer layerToCollideWith = Collision::ALL, GameObject* collideInfo = nullptr);

	static void RunInput(sf::Event event);

	static void LoadScene(std::string scene);

	static Camera& GetCamera();


	static GameObject* GetObjectbyName(const std::string& name);

private:
	static void Start();
public:

	static sf::Clock clock;
	static sf::Time deltaTimeT;

	static float deltaTime;

private:
	static Scene* m_currentScene;
};

