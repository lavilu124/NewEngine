#include "SystemManager.h"


std::vector<GameObject*> SystemManager::objects;

sf::Clock SystemManager::clock;
sf::Time SystemManager::deltaTimeT;


float SystemManager::deltaTime = 0;

void SystemManager::StartUp() {
    FileManager::SetPaths();
    FileManager::LoadInput();
    
    deltaTime = 0;

}

void SystemManager::Start() {
	if (objects.empty()) return;

    for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Start();
}

void SystemManager::Update() {
	if (objects.empty()) return;

	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		(*it)->Update(deltaTime);

    deltaTimeT = clock.restart();
    deltaTime = deltaTimeT.asSeconds();
}

void SystemManager::Render(sf::RenderWindow& window) {

	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		window.draw((*it)->GetSprite());

}

void SystemManager::CreateGameObject(const GameObject& ob) {
    objects.push_back(const_cast<GameObject*>(&ob));
    objects.shrink_to_fit();
}

bool SystemManager::CheckForCollision(sf::Sprite sprite, int index, Collision::collisionLayer layerToCollideWith, GameObject* collideInfo) {
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