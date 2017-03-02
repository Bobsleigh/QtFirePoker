#include "Parsing/Player.h"

Player::Player(std::string name, long chips) : m_chips(chips), m_name(name)
{

}

long Player::chips()
{
    return m_chips;
}

std::string Player::name()
{
    return m_name;
}

void Player::setChips(long chips)
{
    if (chips > 0)
    {
        m_chips = chips;
    }
}

void Player::setName(std::string name)
{
    m_name = name;
}

void Player::addChips(long chips)
{
    m_chips += chips;
}

void Player::substractChips(long chips)
{
    m_chips -= chips;
}
