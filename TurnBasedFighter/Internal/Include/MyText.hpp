#pragma once
#include <SFML/Graphics.hpp>

class MyText {

public:

	MyText() {}
	~MyText() {}

	void CreateText(const sf::Vector2f& position, const sf::Color& color, const sf::String& text, const sf::Font& font, int textSize);
	void UpdateText(const sf::Color& color, const sf::String& text);

	void Render(sf::RenderWindow& window) const;

private:

	sf::Text m_text;

};
