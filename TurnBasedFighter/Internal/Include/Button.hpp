#pragma once
#include <SFML/Graphics.hpp>

class Button {

public:

	Button() {}
	~Button() {}

	void CreateButton(const sf::Vector2f& size, const sf::Vector2f& position, const sf::Color& color, const sf::String& text, const sf::Font& font, int textSize);

	bool CheckForClick(const sf::Vector2i& mousePosition);
	void ButtonDisabled(bool disabled);

	void Render(sf::RenderWindow& window) const;

	void Something(const Button& nd);

private:

	std::shared_ptr<sf::RectangleShape> m_shape = nullptr;
	sf::Text m_text; //has a default constructor
	sf::Color m_color = sf::Color::Black;
};