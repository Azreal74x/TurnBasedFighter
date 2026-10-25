#include <SFML/Graphics.hpp>
#include <string>
#include "Button.hpp"

void Button::CreateButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::String& text, const sf::Font& font, int textSize) {
  m_color = color;
  m_shape = std::make_shared<sf::RectangleShape>(size);
  m_shape->setPosition(position);
  m_shape->setFillColor(m_color);

  //text
  m_text.setFont(font);
  m_text.setString(text);
  m_text.setCharacterSize(textSize);
  m_text.setFillColor(sf::Color::Black);

  //center text
  sf::FloatRect textBounds = m_text.getLocalBounds();
  m_text.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
  m_text.setPosition(position.x + size.x / 2.0f, position.y + size.y / 2.0f);
}

bool Button::CheckForClick(const sf::Vector2i& mousePosition) {
  if (!m_shape) return false;

  //get the button bounds
  sf::FloatRect buttonBounds = m_shape->getGlobalBounds();

  //check if the mouse position is within the bounds
  return buttonBounds.contains(mousePosition.x, mousePosition.y);
}

void Button::ButtonDisabled(bool disabled) {
  if (disabled) {
    m_shape->setFillColor(sf::Color(128, 128, 128));
  }
  else {
    m_shape->setFillColor(sf::Color(m_color));
  }
}

void Button::Render(sf::RenderWindow& window) const {
  if (m_shape) {
    window.draw(*m_shape);
  }

  window.draw(m_text);
}

