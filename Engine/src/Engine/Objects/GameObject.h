 #pragma once
#include <SFML/Graphics.hpp>
#include "..//SystemLogic//GameLogic/Collision.hpp"

class GameObject
{
public:
	GameObject(const sf::Sprite& ObjectSprite, Collision::collisionLayer Layer = Collision::collisionLayer::COLLIDER);

	int GetIndex() const;

	bool IsFacingRight();

	void Flip();

	void Delete();

	sf::Vector2f GetPosition() const;
	void SetPosition(sf::Vector2f NewPosition);

	sf::Vector2f GetScale() const;
	void SetScale(sf::Vector2f NewScale);

	float GetRotation() const;
	void SetRotation(float Rotation);

	const sf::Sprite& GetSprite() const;
	void SetSprite(const sf::Sprite& Sprite);

	Collision::collisionLayer GetLayer() const;

	virtual void Start();
	virtual void Update(float DeltaTime);

private:
	void SetCenter();

	void HandlePositionChange(sf::Vector2f NewPosition);
	void HandleRotationChange(float NewRotation);
	void HandleScaleChange(sf::Vector2f NewScale);

protected: 
	Collision::collisionLayer m_layer;
	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	float m_rotation;

	int m_index = 0;

	sf::Sprite m_objectSprite;

	virtual void OnCollision(GameObject* HitInfo);
	virtual void OnTrigger(GameObject* HitInfo);
};

