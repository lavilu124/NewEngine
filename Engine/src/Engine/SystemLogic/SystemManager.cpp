#include "SystemManager.h"


sf::Clock SystemManager::clock;
sf::Time SystemManager::deltaTimeT;


float SystemManager::deltaTime = 0;

Scene* SystemManager::m_currentScene;

void SystemManager::StartUp(sf::RenderWindow& window) {
    FileManager::SetPaths();
    FileManager::LoadInput();
    
    deltaTime = 0;

	m_currentScene = new Scene(window, window.getSize().x, window.getSize().y);

	Start();
}

void SystemManager::Start() {
	std::vector<GameObject*>& objects = m_currentScene->getObjects();
	if (objects.empty()) return;

    for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Start();
}

void SystemManager::Update() {
    std::vector<GameObject*>& objects = m_currentScene->getObjects();
	if (objects.empty()) return;

	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Update(deltaTime);

    deltaTimeT = clock.restart();
    deltaTime = deltaTimeT.asSeconds();
}

void SystemManager::Render(sf::RenderWindow& window) {
	std::vector<GameObject*>& objects = m_currentScene->getObjects();
	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		window.draw((*it)->GetSprite());

}

int SystemManager::CreateGameObject(GameObject& ob) {
    if (m_currentScene->CheckExisitingObject(ob.GetName()) != -1) {
		return -1;
    }
	return m_currentScene->addObject(&ob);
}

bool SystemManager::CheckForCollision(sf::Sprite sprite, std::string name, Collision::collisionLayer layerToCollideWith, GameObject* collideInfo) {
    std::vector<GameObject*>& objects = m_currentScene->getObjects();
    for (int i = 0; i < objects.size(); ++i) {
        if (objects[i]->GetName().compare(name) && (objects[i]->GetLayer() == layerToCollideWith || (layerToCollideWith == Collision::ALL && objects[i]->GetLayer() < 6))) {
            if (Collision::PixelPerfectCollision(sprite, objects[i]->GetSprite())) {
                if (collideInfo != nullptr) {
                    collideInfo = objects[i];
                }
                return true;
            }
        }
    }
    return false;
}

void SystemManager::RunInput(sf::Event event) {
    for (std::map<std::string, Input::InputAction>::iterator Input = FileManager::inputs.begin(); Input != FileManager::inputs.end(); ++Input)
        (*Input).second.Active(event);

}

void SystemManager::LoadScene(std::string scene) {
    m_currentScene->LoadSceneFromFile(scene);
    
	Start();
}

Camera& SystemManager::GetCamera() { return m_currentScene->camera; }

GameObject* SystemManager::GetObjectbyName(const std::string& name) {
    int index = m_currentScene->CheckExisitingObject(name);
    if (index != -1) {
        return m_currentScene->getObjects()[index];
    }

    return nullptr;
}

void SystemManager::DestroyObject(std::string name) {
	m_currentScene->DestroyObject(name);
}

void SystemManager::DestroyObject(int index) {
    m_currentScene->DestroyObject(index);
}

void SystemManager::ClearSystem() {
	delete m_currentScene;
}