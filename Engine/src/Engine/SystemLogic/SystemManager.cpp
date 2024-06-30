#include "SystemManager.h"




sf::Clock SystemManager::clock;
sf::Time SystemManager::deltaTimeT;


float SystemManager::deltaTime = 0;

void SystemManager::StartUp() {
    FileManager::SetPaths();
    FileManager::LoadInput();
    
    deltaTime = 0;

}

void SystemManager::Start() {
    std::vector<GameObject*>& objects = m_currentScene.getObjects();
	if (objects.empty()) return;

    for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Start();
}

void SystemManager::Update() {
    std::vector<GameObject*>& objects = m_currentScene.getObjects();
	if (objects.empty()) return;

	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Update(deltaTime);

    deltaTimeT = clock.restart();
    deltaTime = deltaTimeT.asSeconds();
}

void SystemManager::Render(sf::RenderWindow& window) {
	std::vector<GameObject*>& objects = m_currentScene.getObjects();
	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		window.draw((*it)->GetSprite());

}

int SystemManager::CreateGameObject(GameObject& ob) {
    if (m_currentScene.CheckExisitingObject(ob.GetName())) {
		return -1;
    }
	return m_currentScene.addObject(&ob);
}

bool SystemManager::CheckForCollision(sf::Sprite sprite, int index, Collision::collisionLayer layerToCollideWith, GameObject* collideInfo) {
    std::vector<GameObject*>& objects = m_currentScene.getObjects();
    for (int i = 0; i < objects.size(); ++i) {
        if (i != index && (objects[i]->GetLayer() == layerToCollideWith || (layerToCollideWith == Collision::ALL && objects[i]->GetLayer() < 6))) {
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
    m_currentScene.LoadSceneFromFile(scene);
}

void SystemManager::DestroyObject(std::string name) {
	m_currentScene.DestroyObject(name);
}

void SystemManager::DestroyObject(int index) {
    m_currentScene.DestroyObject(index);
}