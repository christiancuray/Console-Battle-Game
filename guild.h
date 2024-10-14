

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"

namespace seneca{
    class Guild {
    std::string m_guildName{};
    Character** m_characters{};
    size_t m_size{};
    size_t m_capacity{};
    // private member functions to help with resizing the array
    void resize();
    public:
   //constructors
    Guild() = default;
    Guild(const char* name);
    // destructor
    ~Guild();
    // copy constructor and assignment operator
    Guild(const Guild& other);
    Guild& operator=(const Guild& other);
    // move constructor and assignment operator
    Guild(Guild&& other) noexcept;
    Guild& operator=(Guild&& other) noexcept;
    // member functions
    void addMember(Character* c);
    void removeMember(const std::string& c);
    Character* operator[](size_t index) const;
    void showMembers() const;

    };

}

#endif //SENECA_GUILD_H
