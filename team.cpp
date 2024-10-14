
#include "team.h"

namespace seneca {

        // resize the array of characters
        void Team::resize() {
            // double the capacity and copy the data to the new array
            m_capacity *= 2;
            // create a new array with the new capacity
            Character **temp = new Character *[m_capacity];
            for (size_t i = 0; i < m_size; i++) {
                temp[i] = m_characters[i];
            }
            // delete the old array and set the new array
            delete[] m_characters;
            m_characters = temp;
        }

        // Constructor with team name as parameter
        Team::Team(const char* name) : m_TeamName(name), m_characters(nullptr), m_size(0), m_capacity(2) {
            m_characters = new Character*[m_capacity];
        }

        // Copy constructor. it calls the copy assignment operator
        Team::Team(const Team& other) {
            *this = other;
        }

        // Copy assignment operator
        Team& Team::operator=(const Team& other) {
            if (this != &other) {
                if(m_characters){
                    // delete the characters in the array
                    for(size_t i = 0; i < m_size; i++){
                        delete m_characters[i];
                    }
                    // delete the array
                    delete[] m_characters;
                }
                // copy the other team's data after deleting the current team's data
                m_TeamName = other.m_TeamName;
                m_size = other.m_size;
                m_capacity = other.m_capacity;

                // copy the characters from the other object to the current object
                m_characters = new Character*[m_capacity];
                for (size_t i = 0; i < m_size; i++) {
                    m_characters[i] = other.m_characters[i]->clone();
                }
            }
            return *this;
        }

        // Move constructor. it calls the move assignment operator
        Team::Team(Team&& other) noexcept {
            *this = std::move(other);
        }

        // Move assignment operator
        Team& Team::operator=(Team&& other) noexcept {
            if (this != &other) {
                if(m_characters){
                    // delete the characters in the array
                    for(size_t i = 0; i < m_size; i++){
                        delete m_characters[i];
                    }
                    // delete the array
                    delete[] m_characters;
                }
                // move the other team's data after deleting the current team's data
                m_TeamName = other.m_TeamName;
                m_size = other.m_size;
                m_capacity = other.m_capacity;
                m_characters = other.m_characters;

                // set the other team's data to default
                other.m_TeamName = "";
                other.m_size = 0;
                other.m_capacity = 0;
                other.m_characters = nullptr;
            }
            return *this;
        }

        // destructor
        Team::~Team() {
            // delete the characters in the array first
            for (size_t i = 0; i < m_size; ++i) {
                delete m_characters[i];
            }
            // delete the array
            delete[] m_characters;
        }

        // add a character member to the team
        void Team::addMember(const Character* c) {
            // check if the character is already in the team and return if it is
            for(size_t i = 0; i < m_size; i++) {
                if (m_characters[i]->getName() == c->getName()) {
                    return;
                }
            }
            // if the array is full, resize it
            if (m_size == m_capacity) {
                resize();
            }

            // add the character to the team
            m_characters[m_size++] = c->clone();
        }

        // remove a character member from the team
        void Team::removeMember(const std::string &c) {
            for (size_t i = 0; i < m_size; i++) {
                // check if the character is in the team and remove it if found
                if (m_characters[i]->getName() == c) {
                    delete m_characters[i];
                    m_characters[i] = nullptr;

                    // create a new array and copy the data after removing the character
                    Character** temp = nullptr;
                    if(m_size > 1){
                        temp = new Character* [m_size - 1];
                        for(size_t j = 0; j < i; ++j){
                            temp[j] = m_characters[j];
                        }
                        for(size_t j = i + 1; j < m_size - 1; ++j){
                            temp[j - 1] = m_characters[j];
                        }
                    }
                    // delete the old array and assign the new array after removing the character and adjust the size of the team
                    delete[] m_characters;
                    m_characters = temp;
                    --m_size;
                }
            }
        }

        // return the character at the given index
        Character* Team::operator[](size_t index) const {
            if (index < m_size) {
                return m_characters[index];
            }
            return nullptr;
        }

        // show the team members with their details
        void Team::showMembers() const {
            // print 'No team' if there are no members in the team
            if (m_size == 0) {
                std::cout << "No team." << std::endl;
            } else {
                // print the team name and all the members
                std::cout << "[Team] " << m_TeamName << std::endl;
                for (size_t i = 0; i < m_size; ++i) {
                    std::cout << "    " << (i + 1) << ": " << *m_characters[i] << std::endl;
                }
            }
        }

}