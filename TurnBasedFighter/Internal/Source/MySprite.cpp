#include <SFML/Graphics.hpp>
#include <iostream>
#include "MySprite.hpp"

void MySprite::CreateSprite(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& scale) {
  if (!m_texture.loadFromFile(texturePath)) {
    std::cerr << "Failed to load texture: " << texturePath << std::endl;
    return;
  }

  m_sprite = std::make_shared<sf::Sprite>(m_texture);
  m_sprite->setPosition(position);
  m_sprite->setScale(scale);
}

void MySprite::RemoveSprite() {
  m_sprite.reset(); 
  m_texture = sf::Texture();
}

void MySprite::SetVisible(bool visible) {
  m_visible = visible;
}

bool MySprite::IsVisible() const {
  return m_visible;
}

void MySprite::Render(sf::RenderWindow& window) const {
  if (m_sprite) {
    window.draw(*m_sprite);
  }
}