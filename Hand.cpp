#include "Hand.h"
#include "Card.h"
#include <iostream>

Hand::Hand() : m_handNumber(0), m_tournamentNumber(0), m_level(0), m_gain(0), m_loss(0)
{
    //m_holeCards[0] = Card();
    //m_holeCards[1] = Card();
}

/*
Hand::Hand(int handNumber, int tournamentNumber) : m_handNumber(handNumber), m_tournamentNumber(tournamentNumber), m_level(0), m_gain(0), m_loss(0)
{
}
*/

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

void Hand::setHoleCards(Card firstCard, Card secondCard)
{
    //m_holeCards[0] = firstCard;
    //m_holeCards[1] = secondCard;
}

int Hand::loss() const
{
    return m_loss;
}

int Hand::gain() const
{
    return m_gain;
}

std::ostream &operator<<(std::ostream &flux, Hand const& hand)
{
    flux << hand.net();
    return flux;
}
