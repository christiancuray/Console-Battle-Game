#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include "health.h"
#include <string>
#include <iostream>

namespace seneca{
	template <typename T>
        class CharacterTpl : public Character {
            int m_healthMax{}; // maximum health
            T m_health{}; // current health
        public:
            CharacterTpl(const char* name, int healthMax);
            ~CharacterTpl() = default;
            void takeDamage(int dmg) override;
            int getHealth() const override;
            int getHealthMax() const override;
            void setHealth(int health) override;
            void setHealthMax(int health) override;
	};

    // Constructor with 2 parameters
    template <typename T>
    CharacterTpl<T>::CharacterTpl(const char* name, int healthMax) :
            Character(name){
                m_health = m_healthMax = healthMax;
            };

    // Take damage and update the health of the character and print the output
    template <typename T>
    void CharacterTpl<T>::takeDamage(int dmg) {
        // reduce the health by the damage amount
        m_health -= dmg;

        // health cannot be negative so set it to 0 if it becomes negative
        if (m_health < 0)  m_health = 0;

        // indent the output 4 spaces
        std::cout << "    ";
        if (m_health <= 0) {
            std::cout << this->getName() << " has been defeated!" << std::endl;
        }
        else {
            std::cout << this->getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
        }
    };

    // return the current health of the character
    template <typename T>
    int CharacterTpl<T>::getHealth() const  {
        return static_cast<int>(m_health);
    };

    // return the maximum health of the character
    template <typename T>
    int CharacterTpl<T>::getHealthMax() const  {
        return m_healthMax;
    };

    // set the health of the character
    template <typename T>
    void CharacterTpl<T>::setHealth(int health)  {
        m_health = health;
    };

    // set the maximum health of the character
    template <typename T>
    void CharacterTpl<T>::setHealthMax(int health) {
        m_healthMax = health;
    };

};
#endif //SENECA_CHARACTERTPL_H