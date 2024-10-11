#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H

#include "character.h"
#include "health.h"
#include <string>
#include <iostream>

namespace seneca{
	template <typename T>
        class CharacterTpl : public Character {
            T m_healthMax{}; // maximum health
            T m_health{}; // current health
        public:
            CharacterTpl(const char* name, T healthMax);

            void takeDamage(int dmg) override;
            int getHealth() const override;
            int getHealthMax() const override;
            void setHealth(int health) override;
            void setHealthMax(int health) override;
	};


};
#endif //SENECA_CHARACTERTPL_H