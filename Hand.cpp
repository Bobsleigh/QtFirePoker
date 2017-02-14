#include "Hand.h"
#include "Card.h"
#include <iostream>

Hand::Hand() : m_handNumber(0), m_tournamentNumber(0), m_level(0), m_gain(0), m_loss(0)
{
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
    m_holeCards[0] = firstCard;
    m_holeCards[1] = secondCard;
}

void Hand::setHandNumber(long long handNumber)
{
    m_handNumber = handNumber;
}

long long Hand::handNumber() const
{
    return m_handNumber;
}

void Hand::setTournamentNumber(long long tournamentNumber)
{
    m_tournamentNumber= tournamentNumber;
}

long long Hand::tournamentNumber() const
{
    return m_tournamentNumber;
}

void Hand::setSmallBlind(int smallBlind)
{
    m_smallBlind= smallBlind;
}

int Hand::smallBlind() const
{
    return m_smallBlind;
}

void Hand::setBigBlind(int bigBlind)
{
    m_bigBlind = bigBlind;
}

int Hand::bigBlind() const
{
    return m_bigBlind;
}

void Hand::setYear(int year)
{
    m_year = year;
}

int Hand::year() const
{
    return m_year;
}

void Hand::setMonth(int month)
{
    m_month = month;
}

int Hand::month() const
{
    return m_month;
}

void Hand::setDay(int day)
{
    m_day = day;
}

int Hand::day() const
{
    return m_day;
}

int Hand::loss() const
{
    return m_loss;
}

int Hand::gain() const
{
    return m_gain;
}

Card Hand::firstHoleCard() const
{
    return m_holeCards[0];
}

Card Hand::secondHoleCard() const
{
    return m_holeCards[1];
}

std::ostream &operator<<(std::ostream &flux, Hand const& hand)
{
    flux << hand.net();
    return flux;
}
