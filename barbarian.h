#ifndef SENECA_BARBARIAN_H
#define SENECA_BARBARIAN_H

#include "characterTpl.h"
#include "character.h"

namespace seneca {
    template <typename T, typename Ability_t, typename Weapon_t>
    class Barbarian : public CharacterTpl<T>{
        int m_baseDefense{};
        int m_baseAttack{};
        Ability_t m_ability;
        Weapon_t m_weapon[2];
    public:
        Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon);
        int getAttackAmnt() const;
        int getDefenseAmnt() const;
        Character* clone() const;
        void attack(Character* enemy);
        void takeDamage(int dmg);
    };

    // Constructor with 6 parameters
    template <typename T, typename Ability_t, typename Weapon_t>
    Barbarian<T, Ability_t, Weapon_t>::Barbarian(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t primaryWeapon, Weapon_t secondaryWeapon)
            : CharacterTpl<T>(name, healthMax), m_baseDefense(baseDefense), m_baseAttack(baseAttack){
        m_weapon[0] = primaryWeapon;
        m_weapon[1] = secondaryWeapon;
    };

    // Get the attack amount by adding the base attack and  the two weapons
    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getAttackAmnt() const{
        return m_baseAttack + ((static_cast<double>(m_weapon[0]) / 2) + (static_cast<double>(m_weapon[1]) / 2));
    };

    // Get the defense amount
    template <typename T, typename Ability_t, typename Weapon_t>
    int Barbarian<T, Ability_t, Weapon_t>::getDefenseAmnt() const{
        return m_baseDefense;
    };

    // Dynamically allocate a new Barbarian object and return it
    template <typename T, typename Ability_t, typename Weapon_t>
    Character* Barbarian<T, Ability_t, Weapon_t>::clone() const {
        return new Barbarian<T, Ability_t, Weapon_t>(*this);
    };

    // Attack the enemy and calculate the damage
    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian< T, Ability_t, Weapon_t>::attack (Character* enemy){
        std::cout << this->getName() << " is attacking " << enemy->getName() << "." << std::endl;

        // use the special ability of the current character
        m_ability.useAbility(this);

        // get the attack amount
        int dmg = this->getAttackAmnt();
        // enhance the damage dealt by adding the special ability damage
        m_ability.transformDamageDealt(dmg);

        std::cout << "    Barbarian deals " << dmg << " melee damage!" << std::endl;
        // update the enemy's health by the damage amount
        enemy->takeDamage(dmg);
    };

    // Take damage and reduce the damage received
    template <typename T, typename Ability_t, typename Weapon_t>
    void Barbarian<T, Ability_t, Weapon_t>::takeDamage(int dmg){
        std::cout << this->getName() << " is attacked for " << dmg << " damage." << std::endl;
        std::cout << "    Barbarian has a defense of " << this->getDefenseAmnt() << ". Reducing damage received." << std::endl;

        // reduce the damage by the defense amount
        dmg -= this->getDefenseAmnt();
        //set the damage to 0 if it is negative
        if(dmg < 0) dmg = 0;

        // reduce the damage by the special ability
        m_ability.transformDamageReceived(dmg);
        // take the damage and update the health of the character
        CharacterTpl<T>::takeDamage(dmg);
    }

}

#endif //SENECA_BARBARIAN_H