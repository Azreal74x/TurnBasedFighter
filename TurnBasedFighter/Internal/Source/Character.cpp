#include <SFML/Graphics.hpp>
#include <iostream>
#include "Character.hpp"

Character::Character(const std::string name, const int health, const int healAmount, const int damageAmount) /*: m_damageAmount(damageAmount)*/ {
	m_health = health;
	m_name = name;
	m_healAmount = healAmount;
	m_damageAmount = damageAmount;
}

void Character::Attack(Character& otherCharacter) {
	//std::cout << m_name << " attacked " << otherCharacter.m_name << std::endl;
	otherCharacter.ReceiveDamage(m_damageAmount);
}

void Character::ReceiveDamage(int pDamageAmount) {
	//std::cout << m_name << ": health is " << m_health << std::endl;
	m_health -= pDamageAmount;
	//std::cout << m_name << ": health is now " << m_health << std::endl;
}

void Character::Heal() {
	if (m_health < m_maxHealth) {
		//std::cout << m_name << ": health is " << m_health << std::endl;
		m_health += m_healAmount;
		if (m_health > m_maxHealth) {
			m_health = m_maxHealth;
		}
		//std::cout << m_name << ": health is now " << m_health << std::endl;
	}
}

void Character::DoNothing() {
	//std::cout << m_name << ": did nothing" << std::endl;
}

int Character::GenerateRandomRange(int min, int range) const {
	int variable = min + rand() % range;
	//std::cout << "random number is " << variable << std::endl;
	return variable;
}

std::string Character::RandomTurn(Character& otherCharacter) {
	int random = GenerateRandomRange(0, 3);
	if (random == 0) {
		DoNothing();
		return "Enemy did nothing!";
	}
	else if (random == 1 && m_health != m_maxHealth) {
		Heal();
		return "Enemy healed!";
	}
	else {
		Attack(otherCharacter);
		return "Enemy attacked player!";
	}
}

const int Character::GetHealth() {
	return m_health;
}

void Character::ResetHealth() {
	m_health = m_maxHealth;
}

void Character::SetHealth(int newHealth) {
	m_health = newHealth;
}

void Character::SetDamageAmount(int newDamageAmount) {
	m_damageAmount = newDamageAmount;
}

void Character::SetHealAmount(int newHealAmount) {
	m_healAmount = newHealAmount;
}
