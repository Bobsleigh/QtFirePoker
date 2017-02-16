#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player
{
    public:
    Player(std::string name, long chips);
    long chips();
    std::string name();
    void setChips(long chips);
    void setName(std::string name);
    void addChips(long chips);
    void substractChips(long chips);

    private:
    long m_chips;
    std::string m_name;

};

#endif // PLAYER_H
