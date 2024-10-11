
#include "rogue.h"

namespace seneca {
    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Rogue<T, FirstAbility_t, SecondAbility_t>::Rogue(const char* name, int healthMax, int baseAttack, int baseDefense)
            : CharacterTpl<T>(name, healthMax), m_baseAttack(baseAttack), m_baseDefense(baseDefense) {};


    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getAttackAmnt() const{
        return static_cast<int>(2 * static_cast<double>(m_weapon));
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    int Rogue<T, FirstAbility_t, SecondAbility_t>::getDefenseAmnt() const{
        return m_baseDefense;
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    Character* Rogue<T, FirstAbility_t, SecondAbility_t>::clone() const{
        return new Rogue(*this);
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::attack(Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << std::endl;

        // use the first special ability of current character
        FirstAbility_t::useAbility(this);
        // use the second special ability of current character
        SecondAbility_t::useAbility(this);

        // get the attack amount
        int dmg = getAttackAmnt();

        // enhance the damage by adding the first special ability damage
        FirstAbility_t::transformDamageDealt(dmg);

        // enhance the damage by adding the second special ability damage
        SecondAbility_t::transformDamageDealt(dmg);

        std::cout << "Rogue deals " << dmg << " melee damage!" << std::endl;

        enemy->takeDamage(dmg);
    }

    template <typename T, typename FirstAbility_t, typename SecondAbility_t>
    void Rogue<T, FirstAbility_t, SecondAbility_t>::takeDamage(int dmg){
        std::cout << this->getName() << " is attacked for " << dmg << " damage.\n" <<
        "\tRogue has a defense of " << getDefenseAmnt() << ". Reducing damage received." << std::endl;

        dmg -= getDefenseAmnt();
        if (dmg < 0) {
            dmg = 0;
        }
        // enhance the damage by adding the first special ability damage
        FirstAbility_t::transaformDamageReceived(dmg);

        // enhance the damage by adding the second special ability damage
        SecondAbility_t::transaformDamageReceived(dmg);

        // take the damage and update the health
        CharacterTpl<T>::takeDamage(dmg);
    }
}