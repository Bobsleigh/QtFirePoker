#include "Hand.h"
#include "Card.h"
#include <iostream>

Hand::Hand() : m_handNumber(0), m_tournamentNumber(0), m_level(0), m_gain(0), m_loss(0)
{
}

int Hand::net() const
{
    return m_gain - m_loss;
}

void Hand::setGain(int gain)
{
    if (gain > 0) m_gain = gain;
}

void Hand::setLoss(int loss)
{
    if (loss > 0) m_loss = loss;
}

std::ostream &operator<<(std::ostream &flux, Hand const& hand)
{
    flux << hand.net();
    return flux;
}
