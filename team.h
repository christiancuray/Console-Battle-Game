#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"

namespace seneca{

    class Team {
        std::string m_TeamName{};
        Character** m_characters{};
        size_t m_size{};
        size_t m_capacity{};

        void resize();
    public:
        Team() : m_TeamName{}, m_characters(nullptr), m_size(0), m_capacity(0) {};
        Team(const char* name) : m_TeamName(name), m_characters(nullptr), m_size(0), m_capacity(0) {};

        Team(const Team& other);
        Team& operator=(const Team& other);

        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        ~Team();

        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };
}

#endif //SENECA_TEAM_H
