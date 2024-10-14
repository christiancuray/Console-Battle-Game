#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H

#include "characterTpl.h"
#include "health.h"
#include "weapons.h"

namespace seneca {
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon;
    public:
        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon);
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const;
        void attack(Character* enemy);
        void takeDamage(int dmg);
    };

    // Constructor with 5 parameters
    template <typename Weapon_t>
    Archer<Weapon_t>::Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

     // Get the attack amount
    template <typename Weapon_t>
    int Archer<Weapon_t>::getAttackAmnt() const{
        return static_cast<int>( m_baseAttack *  1.3);
    }

    // Get the defense amount
    template <typename Weapon_t>
    int Archer<Weapon_t>::getDefenseAmnt() const{
        return static_cast<int>(m_baseDefense * 1.2);
    }

    // Dynamically allocate a new Archer object and return it
    template <typename Weapon_t>
    Character* Archer<Weapon_t>::clone() const{
        return new Archer<Weapon_t>(*this);
    }

    // Attack the enemy and calculate the damage
    template <typename Weapon_t>
    void Archer<Weapon_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // get the attack amount
        int dmg = this->getAttackAmnt();
        std::cout << " Archer deals " << dmg << " ranged damage!" << std::endl;

        // update the enemy's health by the damage amount
        enemy->takeDamage(dmg);

    }

    // Take damage and update the health of the character
    template <typename Weapon_t>
    void Archer<Weapon_t>::takeDamage(int dmg){
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "Archer has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // reduce the damage by the defense amount
        dmg -= this->getDefenseAmnt();

        // set the damage to 0 if it becomes negative
        if(dmg < 0)  dmg = 0;

        // take the damage and update the health of the character
        CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
    }


}

#endif //SENECA_ARCHER_H
