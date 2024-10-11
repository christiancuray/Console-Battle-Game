

#ifndef SENECA_GUILD_H
#define SENECA_GUILD_H

#include "character.h"

namespace seneca{
    class Guild {
    std::string m_guildName{};
    Character** m_characters{};
    size_t m_size{};
    size_t m_capacity{};

    void resize();
    public:
    Guild();
    Guild(const char* name);

    ~Guild();
    Guild(const Guild& other);
    Guild& operator=(const Guild& other);
    Guild(Guild&& other) noexcept;
    Guild& operator=(Guild&& other) noexcept;

    void addMember(Character* c);
    void removeMember(const std::string& c);
    Character* operator[](size_t index) const;
    void showMembers() const;


    };
}

#endif //SENECA_GUILD_H
