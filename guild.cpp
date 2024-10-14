
#include "guild.h"

namespace seneca{

    void Guild::resize() {
        // Double the capacity and copy the data to the new array
        m_capacity *= 2;
        // Create a new array with the new capacity
        auto new_characters = new Character*[m_capacity];
        // Copy the data from the old array to the new array
        for (size_t i = 0; i < m_size; ++i) {
            new_characters[i] = m_characters[i];
        }
        // Delete the old array and set the new array
        delete[] m_characters;
        m_characters = new_characters;
    }


    // Constructor with guild name as parameter
    Guild::Guild(const char* name) : m_guildName(name), m_characters(nullptr), m_size(0), m_capacity(2) {
        m_characters = new Character*[m_capacity];
    }

    // Copy constructor
    Guild::Guild(const Guild& other) {
        *this = other;
    }

    // Copy assignment operator
    Guild& Guild::operator=(const Guild& other) {
        if (this != &other) {
            // Delete the current array and copy the data from the other object
            delete[] m_characters;
            m_guildName = other.m_guildName;
            m_size = other.m_size;
            m_capacity = other.m_capacity;

            // Copy the characters from the other object to the current object
            m_characters = new Character*[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                m_characters[i] = other.m_characters[i];
            }
        }
        return *this;
    }

    // destructor
    Guild::~Guild(){
        delete[] m_characters;
    }

    // Move constructor. it calls the move assignment operator
    Guild::Guild(Guild &&other) noexcept {
       *this = std::move(other);
    }

    // Move assignment operator
    Guild &Guild::operator=(seneca::Guild &&other) noexcept {
        if (this != &other) {
            // Delete the current array and move the data from the other object
            delete[] m_characters;
            m_guildName = std::move(other.m_guildName);
            m_size = other.m_size;
            m_capacity = other.m_capacity;
            m_characters = other.m_characters;

            // Set the other object to a safe values
            other.m_guildName = "";
            other.m_size = 0;
            other.m_capacity = 0;
            other.m_characters = nullptr;
        }
        return *this;
    }

    // Add member to the guild and increase max health by 300
    void Guild::addMember(Character* c) {
        // Check if the character is already in the guild
        for (size_t i = 0; i < m_size; ++i) {
            if (m_characters[i]->getName() == c->getName()) {
                return;
            }
        }
        // Resize the array if it is full
        if (m_size == m_capacity) {
            resize();
        }

        // Increase max health by 300 and set health to max health
        c->setHealthMax(c->getHealthMax() +  300);
        c->setHealth( c->getHealthMax());
        m_characters[m_size++] = c;
    }

    // Remove member from the guild. decrease  max health by 300
    void Guild::removeMember(const std::string& c) {
        for (size_t i = 0; i < m_size; ++i) {
            // Check if the character is in the guild and remove it if found.
            if (m_characters[i] && m_characters[i]->getName() == c) {
                m_characters[i]->setHealthMax(m_characters[i]->getHealthMax() - 300);
                m_characters[i]->setHealth(m_characters[i]->getHealthMax());

                // Shift the elements to the left
                for ( size_t j = i; j < m_size - 1; ++j) {
                    m_characters[j] = m_characters[j + 1];
                }

                // Set the last element to nullptr
                m_characters[--m_size] = nullptr;
                return;
            }
        }
    }

    // Overloaded operator to get the character at index
    Character* Guild::operator[](size_t index) const {
        // Return the character at index if it is valid
        return (index < m_size) ? m_characters[index] : nullptr;
    }

    // Show all the members of the guild
    void Guild::showMembers() const {
        // print 'No guild' if there are no names in the guild
        if (m_guildName.empty()) {
            std::cout << "No guild." << std::endl;
        } else {
            // Print the guild name and all the members
            std::cout << "[Guild] " << m_guildName << std::endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *m_characters[i] << std::endl;
            }
        }
    }

} // namespace seneca