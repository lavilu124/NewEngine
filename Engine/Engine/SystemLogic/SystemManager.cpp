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

void SystemManager::Render(sf::RenderWindow& Window) {
	if (objects.empty()) return;

	for (std::vector<GameObject*>::iterator it = objects.begin(); it != objects.end(); ++it)
		Window.draw((*it)->GetSprite());
}

void SystemManager::CreateGameObject(const GameObject& Ob) {
    objects.push_back(const_cast<GameObject*>(&Ob));
    objects.shrink_to_fit();
}

bool SystemManager::CheckForCollision(sf::Sprite Sprite, int index, Collision::collisionLayer LayerToCollideWith, GameObject* CollideInfo) {
    for (int i = 0; i < objects.size(); ++i) {
        if (i != index && (objects[i]->GetLayer() == LayerToCollideWith || (LayerToCollideWith == Collision::ALL && objects[i]->GetLayer() < 6))) {
            if (Collision::PixelPerfectCollision(Sprite, objects[i]->GetSprite())) {
                if (CollideInfo != nullptr) {
                    CollideInfo = objects[i];
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