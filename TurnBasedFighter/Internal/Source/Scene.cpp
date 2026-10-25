#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Scene.hpp"
#include "Button.hpp"
#include "MyText.hpp"

Scene::Scene(sf::RenderWindow& window) : m_window(window) {
  //m_window = window;
}

void Scene::AddSpriteToScene(const std::shared_ptr<MySprite>& sprite) {
  m_spritesToRender.push_back(sprite);
}

void Scene::AddButtonToScene(const std::shared_ptr<Button>& button) {
  m_buttonsToRender.push_back(button);
}

void Scene::AddTextToScene(const std::shared_ptr<MyText>& text) {
  m_textToRender.push_back(text);
}

void Scene::RemoveSpriteFromScene(const std::shared_ptr<MySprite>& sprite) {
  for (int i = 0; i < m_spritesToRender.size(); i++) {
    if (m_spritesToRender[i] == sprite) {
      m_spritesToRender.erase(m_spritesToRender.begin() + i);
      sprite->RemoveSprite();
    }
  }
}

void Scene::Render() const {
  for (const auto& sprite : m_spritesToRender) {
    if (sprite->IsVisible()) {
      sprite->Render(m_window);
    }
  }

  for (const auto& button : m_buttonsToRender) {
    button->Render(m_window);
  }

  for (const auto& text : m_textToRender) {
    text->Render(m_window);
  }
}
