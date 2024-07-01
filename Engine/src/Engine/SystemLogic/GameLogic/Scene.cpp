#include "Scene.h"
#include "..//..//FileOperations/FileManager.h"

Scene::Scene(sf::RenderWindow& window, float width, float height) : camera(width, height){
	camera.SetCam(window);
}

Scene::Scene(sf::RenderWindow& window, sf::Vector2f windowSize) :  camera(windowSize) {
	camera.SetCam(window);
}

std::vector<GameObject*>& Scene::getObjects() {
	return m_objects;
}

int Scene::addObject(GameObject* object) {
	m_objects.push_back(object);
	return (int) m_objects.size() - 1;
}

void Scene::DestroyObject(std::string name) {
	for (int i = 0; i < m_objects.size(); ++i) {
		if (m_objects[i]->GetName() == name) {
			m_objects[i] = nullptr;
			m_objects.erase(m_objects.cbegin() + i);
			m_objects.shrink_to_fit();
			break;
		}
	}
}

void Scene::DestroyObject(int index) {
	m_objects[index] = nullptr;
	m_objects.erase(m_objects.cbegin() + index);
	m_objects.shrink_to_fit();
}

int Scene::CheckExisitingObject(std::string name) {
	for (int i = 0; i < m_objects.size(); ++i) {
		if (m_objects[i]->GetName() == name) {
			return i;
		}
	}

	return -1;
}

void Scene::LoadSceneFromFile(std::string Scene) {
	for (int i = 0; i < m_objects.size(); i++) {
		if (m_objects[i]->GetIndex() != -1) {
			delete m_objects[i];
		}
	}
	m_objects.clear();
	
	m_objects = FileManager::GetObjects(Scene);
}