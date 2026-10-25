#include <SFML/Graphics.hpp>
#include <iostream>
#include "MyText.hpp"

void MyText::CreateText(const sf::Vector2f& position, const sf::Color& color, const sf::String& text, const sf::Font& font, int textSize) {
  m_text.setFont(font);
  m_text.setString(text);
  m_text.setCharacterSize(textSize);
  m_text.setFillColor(color);
  m_text.setPosition(position.x, position.y);
}

void MyText::UpdateText(const sf::Color& color, const sf::String& text) {
  m_text.setString(text);
  m_text.setFillColor(color);
}

void MyText::Render(sf::RenderWindow& window) const{
  window.draw(m_text);
}

