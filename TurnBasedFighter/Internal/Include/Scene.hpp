#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MySprite.hpp"
#include "Button.hpp"
#include "MyText.hpp"

class Scene {

public:

	Scene(sf::RenderWindow& window);
	~Scene() {}

	void AddSpriteToScene(const std::shared_ptr<MySprite>& sprite);
	void AddButtonToScene(const std::shared_ptr<Button>& button);
	void AddTextToScene(const std::shared_ptr<MyText>& text);
	void RemoveSpriteFromScene(const std::shared_ptr<MySprite>& sprite);

	void Render() const;

private:

	sf::RenderWindow& m_window;
	std::vector<std::shared_ptr<MySprite>> m_spritesToRender;
	std::vector<std::shared_ptr<Button>> m_buttonsToRender;
	std::vector<std::shared_ptr<MyText>> m_textToRender;

};
