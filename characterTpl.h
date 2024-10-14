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

            void takeDamage(int dmg) override;
            int getHealth() const override;
            int getHealthMax() const override;
            void setHealth(int health) override;
            void setHealthMax(int health) override;
	};

    template <typename T>
    CharacterTpl<T>::CharacterTpl(const char* name, int healthMax) :
            Character(name){
                m_health = m_healthMax = healthMax;
            };

    template <typename T>
    void CharacterTpl<T>::takeDamage(int dmg) {
        m_health -= dmg;
        if (m_health <= 0) {
            std::cout << this->getName() << " has been defeated!" << std::endl;
        }
        else {
            std::cout << this->getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
        }
    };

    template <typename T>
    int CharacterTpl<T>::getHealth() const  {
        return m_health;
    };

    template <typename T>
    int CharacterTpl<T>::getHealthMax() const  {
        return m_healthMax;
    };

    template <typename T>
    void CharacterTpl<T>::setHealth(int health)  {
        m_health = health;
    };

    template <typename T>
    void CharacterTpl<T>::setHealthMax(int health) {
        m_healthMax = health;
    };

};
#endif //SENECA_CHARACTERTPL_H