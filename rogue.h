#ifndef SENECA_ROGUE_H
#define SENECA_ROGUE_H

#include "characterTpl.h"
#include "weapons.h"
#include "abilities.h"

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    class Rogue : public CharacterTpl<T> {
        int m_baseDefense{};
        int m_baseAttack{};
        FirstAbility_t m_firstAbility;
        SecondAbility_t m_secondAbility;
        seneca::Dagger m_weapon;
    public:
        Rogue(const char* name, int healthMax, int baseAttack, int baseDefense);
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const;
        void attack(Character* enemy);
        void takeDamage(int dmg);
    };

    // Constructor with 4 parameters
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(seneca::Dagger()) {}

    // Get the attack amount
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const{
        return static_cast<int>(2 * static_cast<double>(m_weapon.m_damage)) + m_baseAttack;
    }

    // Get the defense amount
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const{
        return m_baseDefense;
    }

    // Dynamically allocate a new Rogue object and return it
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const{
        return new Rogue<T, FirstAbility_t, SecondAbility_t>(*this);
    }

    // Attack the enemy with abilties and calculate the damage
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // use the first special ability of current character
        m_firstAbility.useAbility(this);
        // use the second special ability of current character
        m_secondAbility.useAbility(this);

        // get the attack amount
        int dmg = getAttackAmnt();

        // enhance the damage by adding the first special ability damage
        m_firstAbility.transformDamageDealt(dmg);

        // enhance the damage by adding the second special ability damage
        m_secondAbility.transformDamageDealt(dmg);

        std::cout << "Rogue deals " << dmg << " melee damage!" << std::endl;

        // update the enemy's health by the damage amount
        enemy->takeDamage(dmg);
    }

    // Take the damage and update the health of the character
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg){
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "Rogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // reduce the damage by the defense amount
        dmg -= getDefenseAmnt();
        // set the damage to 0 if it is negative
        if (dmg < 0) dmg = 0;
        // enhance the damage by adding the first special ability damage
        m_firstAbility.transformDamageReceived(dmg);

        // enhance the damage by adding the second special ability damage
        m_secondAbility.transformDamageReceived(dmg);

        // take the damage and update the health of the character
        CharacterTpl<T>::takeDamage(dmg);
    }
}

#endif //SENECA_ROGUE_H
