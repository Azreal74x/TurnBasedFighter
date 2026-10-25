#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class MySprite {

public:

	MySprite() {}
	~MySprite() {}

	void CreateSprite(const std::string& texturePath, const sf::Vector2f& position, const sf::Vector2f& scale);
	void RemoveSprite();

	void SetVisible(bool visible);
	bool IsVisible() const;

	void Render(sf::RenderWindow& window) const;

private:

	std::shared_ptr<sf::Sprite> m_sprite = nullptr;
	sf::Texture m_texture; //has a default constructor
	bool m_visible = true;

};