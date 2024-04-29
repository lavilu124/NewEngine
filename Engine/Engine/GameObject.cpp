#include "GameObject.h"
#include "SystemLOgic//SystemManager.h"

GameObject::GameObject(const sf::Sprite& ObjectSprite, Collision::collisionLayer Layer) 
	: m_objectSprite(ObjectSprite), m_layer(Layer), m_rotation(ObjectSprite.getRotation()), m_position(ObjectSprite.getPosition()), m_scale(ObjectSprite.getScale())
{
	
	SystemManager::CreateGameObject(*this);
    m_index = (int) SystemManager::objects.size() - 1;
	

	SetCenter();
}

void GameObject::Flip() {
    m_scale = sf::Vector2f(m_scale.x * -1, m_scale.y);
}

bool GameObject::IsFacingRight() {
    return m_scale.x >= 0;
}


const sf::Sprite& GameObject::GetSprite() const {
    return m_objectSprite;
}

void GameObject::SetCenter() {
    const sf::Texture* texture = m_objectSprite.getTexture();

    sf::Vector2u textureSize = texture->getSize();

    int minX = textureSize.x;
    int minY = textureSize.y;
    int maxX = -1;
    int maxY = -1;

    // Iterate through pixels to find non-transparent coordinates
    for (unsigned int x = 0; x < textureSize.x; ++x) {
        for (unsigned int y = 0; y < textureSize.y; ++y) {
            sf::Color pixelColor = texture->copyToImage().getPixel(x, y);
            if (pixelColor.a > 0) {
                // Update min and max coordinates
                minX = std::min(minX, static_cast<int>(x));
                minY = std::min(minY, static_cast<int>(y));
                maxX = std::max(maxX, static_cast<int>(x));
                maxY = std::max(maxY, static_cast<int>(y));
            }
        }
    }

    // Calculate the center based on the non-transparent coordinates
    float centerX = static_cast<float>(minX + maxX) / 2.0f;
    float centerY = static_cast<float>(minY + maxY) / 2.0f;

    m_objectSprite.setOrigin(sf::Vector2f(centerX, centerY));
}

void GameObject::SetSprite(const sf::Sprite& Sprite) {
    m_objectSprite = Sprite;
}

void GameObject::Delete() {
    if (m_index >= 0 && m_index < SystemManager::objects.size()) {
        // Use unique_ptr to manage memory and set it to nullptr after deletion
        SystemManager::objects[m_index] = nullptr;

        SystemManager::objects.erase(SystemManager::objects.cbegin() + m_index);
        SystemManager::objects.shrink_to_fit();
    }
}

void GameObject::OnCollision(GameObject* HitInfo) {}

void GameObject::OnTrigger(GameObject* HitInfo) {}


void GameObject::HandlePositionChange(sf::Vector2f NewPosition) {
    m_objectSprite.setPosition(NewPosition);

    GameObject* HitInfo = this;

    //checking if the new position collides with anything
    if (SystemManager::CheckForCollision(m_objectSprite, m_index, Collision::ALL, HitInfo)) {
        if (HitInfo == this) {}
        else if (m_layer < 6 && HitInfo->m_layer < 6) {
            OnCollision(HitInfo);
			m_objectSprite.setPosition(m_position);
        }
        else if (m_layer > 6) {
            OnTrigger(HitInfo);
            m_position = NewPosition;
            return;
        }


        //testing if the object can move only along the x axies
        sf::Vector2f TestX = sf::Vector2f(NewPosition.x, NewPosition.y);
        m_objectSprite.setPosition(TestX);

        Collision::collisionLayer LayerToCollideWith = Collision::ALL;
        //checking collison for the movement along the x axies
        if (!SystemManager::CheckForCollision(m_objectSprite, this->GetIndex(), LayerToCollideWith)) {
            m_position = m_objectSprite.getPosition();
            return;
        }

        //testing if the object can move only along the y axies
        sf::Vector2f TestY = sf::Vector2f(m_position.x, NewPosition.y);
        m_objectSprite.setPosition(TestY);

        //checking collison for the movement along the y axies
        if (!SystemManager::CheckForCollision(m_objectSprite, this->GetIndex(), LayerToCollideWith)) {
            m_position = m_objectSprite.getPosition();
        }
    }
    else {
        m_position = NewPosition;
    }
}

void GameObject::HandleRotationChange(float NewRotation) {
    m_objectSprite.setRotation(NewRotation);

    GameObject* HitInfo = this;

    //checking if the new position collides with anything
    if (SystemManager::CheckForCollision(m_objectSprite, this->GetIndex(), Collision::ALL, HitInfo)) {
        if (HitInfo == this) {}
        else if (m_layer < 6 && HitInfo->m_layer < 6) {
            OnCollision(HitInfo);
			m_objectSprite.setRotation(m_rotation);
        }
        else if (m_layer > 6) {
            OnTrigger(HitInfo);
            m_rotation = NewRotation;
        }
    }
    else {
        m_rotation = NewRotation;
    }
}

void GameObject::HandleScaleChange(sf::Vector2f NewScale) {
    m_objectSprite.setScale(NewScale);

    GameObject* HitInfo = this;

    //checking if the new position collides with anything
    if (SystemManager::CheckForCollision(m_objectSprite, this->GetIndex(), Collision::ALL, HitInfo)) {
        if (HitInfo == this) {}
        else if (m_layer < 6 && HitInfo->m_layer < 6) {
            OnCollision(HitInfo);
			m_objectSprite.setScale(m_scale);
        }
        else if (m_layer > 6) {
            OnTrigger(HitInfo);
			m_scale = NewScale;
            return;
        }


    }
    else {
        m_scale = NewScale;
    }
}

sf::Vector2f GameObject::GetPosition() const {
    return m_position;
}

void GameObject::SetPosition(sf::Vector2f NewPosition) {
    if (NewPosition != m_position) {
        HandlePositionChange(NewPosition);
    }
}

sf::Vector2f GameObject::GetScale() const {
    return m_scale;
}

void GameObject::SetScale(sf::Vector2f NewScale) {
    if (NewScale != m_scale) {
        HandleScaleChange(NewScale);
    }
}

float GameObject::GetRotation() const {
    return m_rotation;
}

void GameObject::SetRotation(float NewRotation) {
    if (NewRotation != m_rotation) {
        HandleRotationChange(NewRotation);
    }
}



int GameObject::GetIndex() const {
    return m_index;
}


void GameObject::Start() {

}

void GameObject::Update(float DeltaTime) {
}

Collision::collisionLayer GameObject::GetLayer() const {
	return m_layer;
}