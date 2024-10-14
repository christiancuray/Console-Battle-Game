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

    template <typename Weapon_t>
    Archer<Weapon_t>::Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack), m_weapon(weapon) {}

    template <typename Weapon_t>
    int Archer<Weapon_t>::getAttackAmnt() const{
        return static_cast<int>( m_baseAttack *  1.3);
    }

    template <typename Weapon_t>
    int Archer<Weapon_t>::getDefenseAmnt() const{
        return static_cast<int>(m_baseDefense * 1.2);
    }

    template <typename Weapon_t>
    Character* Archer<Weapon_t>::clone() const{
        return new Archer<Weapon_t>(*this);
    }

    template <typename Weapon_t>
    void Archer<Weapon_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;
        int dmg = this->getAttackAmnt();
        std::cout << " Archer deals " << dmg << " ranged damage!" << std::endl;
        enemy->takeDamage(dmg);

    }

    template <typename Weapon_t>
    void Archer<Weapon_t>::takeDamage(int dmg){
        std::cout << this->getName() << " is attacked for " << dmg << " damage.\n" <<
                  "\tArcher has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;

        dmg -= this->getDefenseAmnt();
        if(dmg < 0)  dmg = 0;
        CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
    }


}

#endif //SENECA_ARCHER_H
