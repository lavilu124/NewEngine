#include "Camera.h"

Camera::Camera(const sf::Vector2f WinodwSize) {
	pov = 75;
	m_spriteToFollow = nullptr;
	position = sf::Vector2f(0,0);
	rotation = 0;
	m_zoom = sf::Vector2f(WinodwSize.x * 75, WinodwSize.y * 75);
	m_view.setSize(m_zoom);
}

Camera::~Camera() {
	free(m_spriteToFollow);
}

void Camera::Follow(sf::Sprite SpriteToFollow) {
	m_spriteToFollow = &SpriteToFollow;
}

void Camera::Unfollow() {
	m_spriteToFollow = nullptr;
}

void Camera::SetCam(sf::RenderWindow& win) {
	win.setView(m_view);
}

void Camera::Update() {
	if (m_spriteToFollow != nullptr) {
		m_view.setCenter(m_spriteToFollow->getPosition());
	}
	else {
		m_view.setCenter(position);
	}
	m_view.setRotation(rotation);
	m_view.setSize(sf::Vector2f(m_zoom.x / pov, m_zoom.y / pov));
}