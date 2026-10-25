#include <SFML/Graphics.hpp>
#include <iostream>
#include "Scene.hpp"
#include "Character.hpp"
#include "MyText.hpp"
#include "ScoreManager.hpp"

int main() {
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Chill Fight", sf::Style::Titlebar | sf::Style::Close);

	//load font
	sf::Font font;
	if (!font.loadFromFile("../../Media/JollyLodger.ttf")) {
		std::cout << "Failed to load font!" << std::endl;
		return -1;
	}

	ScoreManager scoreManager;
	scoreManager.LoadHighscores();

	//main menu
	Scene mainMenu(window);

	std::shared_ptr<MySprite> mainMenuBackground = std::make_shared<MySprite>();
	mainMenuBackground->CreateSprite("../../Media/MainMenuBackground.png", { 0, 0 }, { 1, 1 });
	mainMenu.AddSpriteToScene(mainMenuBackground);

	std::shared_ptr<MySprite> chillGuyRegular = std::make_shared<MySprite>();
	chillGuyRegular->CreateSprite("../../Media/ChillGuyRegular.png", { 800, 200 }, { 0.5f, 0.5f });
	mainMenu.AddSpriteToScene(chillGuyRegular);

	std::shared_ptr<Button> playButton = std::make_shared<Button>();
	playButton->CreateButton({ 200, 50 }, { 100, 400 }, sf::Color::White, "Play", font, 30);
	mainMenu.AddButtonToScene(playButton);

	std::shared_ptr<Button> clearDataButton = std::make_shared<Button>();
	clearDataButton->CreateButton({ 200, 50 }, { 100, 500 }, sf::Color::White, "Clear Data", font, 30);
	mainMenu.AddButtonToScene(clearDataButton);

	std::shared_ptr<Button> quitButton = std::make_shared<Button>();
	quitButton->CreateButton({ 200, 50 }, { 100, 600 }, sf::Color::White, "Quit", font, 30);
	mainMenu.AddButtonToScene(quitButton);

	std::shared_ptr<MyText> highScoresText = std::make_shared<MyText>();
	highScoresText->CreateText({ 50, 50 }, sf::Color::Black, "Highscores: ", font, 30);
	mainMenu.AddTextToScene(highScoresText);
	highScoresText->UpdateText(sf::Color::Black, scoreManager.FormatHighScores());

	//fight scene
	Scene fightScene(window);

	std::shared_ptr<MySprite> fightSceneBackground = std::make_shared<MySprite>();
	fightSceneBackground->CreateSprite("../../Media/FightSceneBackground.png", { 0, 0 }, { 1.0f, 1.0f });
	fightScene.AddSpriteToScene(fightSceneBackground);

	std::shared_ptr<MySprite> chillGuyMirrored = std::make_shared<MySprite>();
	chillGuyMirrored->CreateSprite("../../Media/ChillGuyMirrored.png", { 200, 200 }, { 0.5f, 0.5f });
	fightScene.AddSpriteToScene(chillGuyMirrored);

	std::shared_ptr<MySprite> chillGirl = std::make_shared<MySprite>();
	chillGirl->CreateSprite("../../Media/ChillGirl.png", { 200, 200 }, { 0.75f, 0.75f });
	fightScene.AddSpriteToScene(chillGirl);

	std::shared_ptr<MySprite> chillGuyEmo = std::make_shared<MySprite>();
	chillGuyEmo->CreateSprite("../../Media/ChillGuyEmo.png", { 800, 200 }, { 1.25f, 1.25f });
	fightScene.AddSpriteToScene(chillGuyEmo);

	std::shared_ptr<Button> attackButton = std::make_shared<Button>();
	attackButton->CreateButton({ 200, 50 }, { 500, 600 }, sf::Color::White, "Attack", font, 30);
	fightScene.AddButtonToScene(attackButton);

	std::shared_ptr<Button> healButton = std::make_shared<Button>();
	healButton->CreateButton({ 200, 50 }, { 750, 600 }, sf::Color::White, "Heal", font, 30);
	fightScene.AddButtonToScene(healButton);

	std::shared_ptr<Button> doNothingButton = std::make_shared<Button>();
	doNothingButton->CreateButton({ 200, 50 }, { 1000, 600 }, sf::Color::White, "Do nothing", font, 30);
	fightScene.AddButtonToScene(doNothingButton);

	std::shared_ptr<Button> backButton = std::make_shared<Button>();
	backButton->CreateButton({ 200, 50 }, { 50, 50 }, sf::Color::White, "Back", font, 30);
	fightScene.AddButtonToScene(backButton);

	std::shared_ptr<MyText> fightText = std::make_shared<MyText>();
	fightText->CreateText({ 500, 75 }, sf::Color::Black, "FIGHT!", font, 50);
	fightScene.AddTextToScene(fightText);

	std::shared_ptr<MyText> playerHealthText = std::make_shared<MyText>();
	playerHealthText->CreateText({ 350, 225 }, sf::Color::Black, "Health: 100", font, 30);
	fightScene.AddTextToScene(playerHealthText);

	std::shared_ptr<MyText> enemyHealthText = std::make_shared<MyText>();
	enemyHealthText->CreateText({ 800, 200 }, sf::Color::Black, "Health: 100", font, 30);
	fightScene.AddTextToScene(enemyHealthText);

	std::shared_ptr<MyText> scoreText = std::make_shared<MyText>();
	scoreText->CreateText({ 1100, 50 }, sf::Color::Black, "Score: 0", font, 30);
	fightScene.AddTextToScene(scoreText);

	Character* player = new Character("Player", 100, 20, 20);
	Character* enemy = new Character("Enemy", 100, 15, 15);

	Scene* currentScene = &mainMenu;

	int randomCharacter = player->GenerateRandomRange(0, 2);
	bool isButtonPressed = false;
	bool playerTurn = true;
	bool playerDead = false;
	bool canPlayerHeal = false;

	sf::Clock turnTimer;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (player->GetHealth() == 100) {
			healButton->ButtonDisabled(true);
		}

		if (player->GetHealth() <= 0) {
			player->SetHealth(0);
			playerHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(player->GetHealth()));
			fightText->UpdateText(sf::Color(128, 0, 0), "Game over!");
			scoreManager.CheckHighscore();
			scoreManager.SaveHighscores();
			enemy->ResetHealth();
			attackButton->ButtonDisabled(true);
			healButton->ButtonDisabled(true);
			doNothingButton->ButtonDisabled(true);
			playerDead = true;
		}
		else if (enemy->GetHealth() <= 0) {
			scoreManager.SetScore(scoreManager.GetScore() + 1);
			scoreManager.CheckHighscore();
			scoreManager.SaveHighscores();
			scoreText->UpdateText(sf::Color::Black, "Score: " + std::to_string(scoreManager.GetScore()));
			enemy->ResetHealth();
			enemyHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(enemy->GetHealth()));
			fightText->UpdateText(sf::Color::Black, "A new enemy!");
			playerTurn = true;
		}

		if (!playerTurn) {
			attackButton->ButtonDisabled(true);
			healButton->ButtonDisabled(true);
			doNothingButton->ButtonDisabled(true);

			if (!playerDead) {
				sf::Time elapsed = turnTimer.getElapsedTime();
				if (elapsed.asSeconds() >= 5.0f) {
					//std::cout << "5 seconds passed!" << std::endl;
					fightText->UpdateText(sf::Color::Black, enemy->RandomTurn(*player));
					playerHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(player->GetHealth()));
					enemyHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(enemy->GetHealth()));
					playerTurn = true;
					attackButton->ButtonDisabled(false);
					doNothingButton->ButtonDisabled(false);
					if (player->GetHealth() == 100) {
						healButton->ButtonDisabled(true);
					}
					else {
						healButton->ButtonDisabled(false);
					}
					turnTimer.restart();
				}
			}
		}

		//check menu button clicks
		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
			if (!isButtonPressed) {
				isButtonPressed = true;

				sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

				if (currentScene == &mainMenu) {
					highScoresText->UpdateText(sf::Color::Black, scoreManager.FormatHighScores());
					if (playButton->CheckForClick(mousePosition)) {
						currentScene = &fightScene;
						playerDead = false;

						randomCharacter = player->GenerateRandomRange(0, 2);
						if (randomCharacter == 0) {
							chillGirl->SetVisible(true);
							chillGuyMirrored->SetVisible(false);
							player->SetDamageAmount(25);
							player->SetHealAmount(20);
							//std::cout << "chill girl" << std::endl;
						}
						else {
							chillGuyMirrored->SetVisible(true);
							chillGirl->SetVisible(false);
							player->SetDamageAmount(20);
							player->SetHealAmount(25);
							//std::cout << "chill guy" << std::endl;
						}

						//std::cout << "Play button clicked!" << std::endl;
					}
					else if (clearDataButton->CheckForClick(mousePosition)) {
						scoreManager.ClearHighscores();
						highScoresText->UpdateText(sf::Color::Black, scoreManager.FormatHighScores());
						//std::cout << "Clear Data button clicked!" << std::endl;
					}
					else if (quitButton->CheckForClick(mousePosition)) {
						window.close();
						//std::cout << "Quit button clicked!" << std::endl;
					}
				}
				else if (currentScene == &fightScene && playerTurn) {
					if (healButton->CheckForClick(mousePosition) && player->GetHealth() != 100 && !playerDead) {
						playerTurn = false;
						player->Heal();
						fightText->UpdateText(sf::Color::Black, "Player healed!");
						playerHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(player->GetHealth()));
						turnTimer.restart();
						//std::cout << "Heal button clicked!" << std::endl;
					}
					else if (attackButton->CheckForClick(mousePosition) && !playerDead) {
						playerTurn = false;
						player->Attack(*enemy);
						fightText->UpdateText(sf::Color::Black, "Player attacked enemy!");
						enemyHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(enemy->GetHealth()));
						turnTimer.restart();
						//std::cout << "Attack button clicked!" << std::endl;
					}
					else if (doNothingButton->CheckForClick(mousePosition) && !playerDead) {
						playerTurn = false;
						player->DoNothing();
						fightText->UpdateText(sf::Color::Black, "Player did nothing!");
						turnTimer.restart();
						//std::cout << "Do nothing button clicked!" << std::endl;
					}
					else if (backButton->CheckForClick(mousePosition)) {
						scoreManager.SaveHighscores();
						currentScene = &mainMenu;
						highScoresText->UpdateText(sf::Color::Black, scoreManager.FormatHighScores());
						player->ResetHealth();
						enemy->ResetHealth();
						scoreManager.SetScore(0);
						fightText->UpdateText(sf::Color::Black, "FIGHT!");
						playerHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(player->GetHealth()));
						enemyHealthText->UpdateText(sf::Color::Black, "Health: " + std::to_string(enemy->GetHealth()));
						attackButton->ButtonDisabled(false);
						healButton->ButtonDisabled(false);
						doNothingButton->ButtonDisabled(false);
						turnTimer.restart();
						//std::cout << "Back button clicked!" << std::endl;
					}
				}
			}
		}

		if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left) {
			isButtonPressed = false;
		}

		window.clear();
		currentScene->Render();
		window.display();
	}

	delete player;
	delete enemy;

	return 0;
}