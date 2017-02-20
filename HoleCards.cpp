#include "HoleCards.h"

HoleCards::HoleCards()
{
    m_cards[0] = Card();
    m_cards[1] = Card();
}

HoleCards::HoleCards(Card cardOne, Card cardTwo)
{
    m_cards[0] = cardOne;
    m_cards[1] = cardTwo;
}

void HoleCards::setHoleCards(Card cardOne, Card cardTwo)
{
    m_cards[0] = cardOne;
    m_cards[1] = cardTwo;
}

Card HoleCards::firstCard()
{
    return m_cards[0];
}

Card HoleCards::secondCard()
{
    return m_cards[1];
}

void HoleCards::getCardsRank()
{
    std::string rank;
    rank = m_cards[0].valueString() + m_cards[1].valueString();

    if (m_cards[0].value() != m_cards[1].value())
    {
        if (m_cards[0].color() == m_cards[1].color())
        {
            rank += + "s";
        }
        else
        {
            rank += "o";
        }
    }
}

bool HoleCards::isSuited()
{
    if (m_cards[0].color() == m_cards[1].color())
    {
        return true;
    }
    else
    {
        return false;
    }
}
