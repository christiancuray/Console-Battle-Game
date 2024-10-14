#ifndef SENECA_TEAM_H
#define SENECA_TEAM_H

#include "character.h"

namespace seneca{

    class Team {
        std::string m_TeamName{};
        Character** m_characters{};
        size_t m_size{};
        size_t m_capacity{};

        // private member functions to help with resizing the array
        void resize();
    public:
        // Constructors
        Team();
        Team(const char* name);
        // Copy constructor and assignment operator
        Team(const Team& other);
        Team& operator=(const Team& other);

        // Move constructor and assignment operator
        Team(Team&& other) noexcept;
        Team& operator=(Team&& other) noexcept;
        // Destructor
        ~Team();

        // Member functions
        void addMember(const Character* c);
        void removeMember(const std::string& c);
        Character* operator[](size_t index) const;
        void showMembers() const;
    };
}

#endif //SENECA_TEAM_H
