
#include "team.h"

namespace seneca {

        void Team::resize() {
            if (m_capacity == 0) {
                m_capacity = 1;
                m_characters = new Character*[m_capacity];
            }
            else {
                m_capacity *= 2;
                Character** temp = new Character*[m_capacity];
                for (size_t i = 0; i < m_size; i++) {
                    temp[i] = m_characters[i];
                }
                delete[] m_characters;
                m_characters = temp;
            }
        }

        Team::Team(const Team& other) {
            m_TeamName = other.m_TeamName;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = new Character*[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                m_characters[i] = other.m_characters[i]->clone();
            }
        }

        Team& Team::operator=(const Team& other) {
            if (this != &other) {
                delete[] m_characters;
                m_TeamName = other.m_TeamName;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_characters = new Character*[m_capacity];
                for (size_t i = 0; i < m_size; i++) {
                    m_characters[i] = other.m_characters[i]->clone();
                }
            }
            return *this;
        }

        Team::Team(Team&& other) noexcept {
            m_TeamName = other.m_TeamName;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = other.m_characters;
            other.m_TeamName = "";
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_characters = nullptr;
        }

        Team& Team::operator=(Team&& other) noexcept {
            if (this != &other) {
                delete[] m_characters;
                m_TeamName = other.m_TeamName;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_characters = other.m_characters;
                other.m_TeamName = "";
                other.m_size = 0;
                other.m_capacity = 0;
                other.m_characters = nullptr;
            }
            return *this;
        }

        Team::~Team() {
            for (size_t i = 0; i < m_size; i++) {
                delete m_characters[i];
            }
            delete[] m_characters;
        }

        void Team::addMember(const Character* c) {
            for(size_t i = 0; i < m_size; i++) {
                if (m_characters[i]->getName() == c->getName()) {
                    return;
                }
            }
            if (m_size == m_capacity) {
                resize();
            }
            // add the character to the team
            m_characters[m_size++] = c->clone();
        }

        void Team::removeMember(const std::string &c) {
            for (size_t i = 0; i < m_size; i++) {
                if (m_characters[i]->getName() == c) {
                    delete m_characters[i];
                    for (size_t j = i; j < m_size - 1; j++) {
                        m_characters[j] = m_characters[j + 1];
                    }
                    m_size--;
                    return;
                }
            }
        }

        Character* Team::operator[](size_t index) const {
            if (index < m_size) {
                return m_characters[index];
            }
            return nullptr;
        }

        void Team::showMembers() const {
            if (m_size == 0) {
                std::cout << "No team." << std::endl;
            } else {
                std::cout << "[Team] " << m_TeamName << std::endl;
                for (size_t i = 0; i < m_size; ++i) {
                    std::cout << "    " << (i + 1) << ": " << *m_characters[i] << std::endl;
                }
            }
        }

}