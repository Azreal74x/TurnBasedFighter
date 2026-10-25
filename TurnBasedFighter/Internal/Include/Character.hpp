#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Character {

public:

	Character(const std::string name, const int health, const int healAmount, const int damageAmount);
	~Character() {}

	void Attack(Character& character);
	void ReceiveDamage(int damageAmount);
	void Heal();
	void DoNothing();

	int GenerateRandomRange(int min, int range) const;
	std::string RandomTurn(Character& otherCharacter);

	const int GetHealth();
	void ResetHealth();
	void SetHealth(int newHealth);
	void SetDamageAmount(int newDamageAmount);
	void SetHealAmount(int newHealAmount);

private:
		
	std::string m_name = " ";

	int m_health = 100;
	int m_maxHealth = 100;

	int m_healAmount = 20;
	int m_damageAmount = 20;


};
