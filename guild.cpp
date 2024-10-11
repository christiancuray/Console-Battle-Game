
#include "guild.h"

namespace seneca{

    void Guild::resize() {
        m_capacity *= 2;
        Character** new_characters = new Character*[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            new_characters[i] = m_characters[i];
        }
        delete[] m_characters;
        m_characters = new_characters;
    }

    Guild::Guild() : m_guildName("No guild"), m_characters(nullptr), m_size(0), m_capacity(2) {
        m_characters = new Character*[m_capacity];
    }

    // Constructor with guild name
    Guild::Guild(const char* name) : m_guildName(name), m_characters(nullptr), m_size(0), m_capacity(2) {
        m_characters = new Character*[m_capacity];
    }

    Guild::Guild(const Guild& other) {
        if(other.m_characters != nullptr) {

            m_guildName = other.m_guildName;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = new Character *[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_characters[i] = other.m_characters[i];
            }
        }
    }

    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            delete[] m_characters;
            m_guildName = other.m_guildName;
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = new Character*[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_characters[i] = other.m_characters[i]->clone();
            }
        }
        return *this;
    }

    Guild::~Guild(){
        delete[] m_characters;
    }

    Guild::Guild(Guild &&other) noexcept {
        if(other.m_characters != nullptr) {
            m_guildName = std::move(other.m_guildName);
            m_size = std::move(other.m_size);
            m_capacity = std::move(other.m_capacity);
            m_characters = std::move(other.m_characters);
            other.m_guildName = "";
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_characters = nullptr;
        }
    }

    Guild &Guild::operator=(seneca::Guild &&other) noexcept {
        if (this != &other) {
            delete[] m_characters;
            m_guildName = std::move(other.m_guildName);
            m_size = std::move(other.m_size);
            m_capacity = std::move(other.m_capacity);
            m_characters = std::move(other.m_characters);
            other.m_guildName = "";
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_characters = nullptr;
        }
        return *this;
    }

    void Guild::addMember(Character* c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_characters[i]->getName() == c->getName()) {
                return;
            }
        }
        if (m_size == m_capacity) {
            resize();
        }
        c->setHealthMax(c->getHealthMax() + 300);
        m_characters[m_size++] = c->clone();
    }

    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            if (m_characters[i]->getName() == c) {
                m_characters[i]->setHealthMax(m_characters[i]->getHealthMax() - 300);
                for (size_t j = i; j < m_size - 1; ++j) {
                    m_characters[j] = m_characters[j + 1];
                }
                --m_size;
                return;
            }
        }
    }

    Character* Guild::operator[](size_t index) const {
        if (index < m_size) {
            return m_characters[index];
        }
        return nullptr;
    }

    void Guild::showMembers() const {
        if (m_size == 0) {
            std::cout << "No guild." << std::endl;
        } else {
            std::cout << "[Guild] " << m_guildName << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *m_characters[i] << std::endl;
            }
        }
    }

}