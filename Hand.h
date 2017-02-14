#ifndef HAND_H
#define HAND_H

#include "Card.h"


class Hand
{
    public:
        Hand();
        //Hand(int handNumber, int tournamentNumber);
        int net() const;
        void setGain(int gain);
        void setLoss(int loss);
        void setHoleCards(Card firstCard, Card secondCard);
        int loss() const;
        int gain() const;

    private:
        long m_handNumber;
        long m_tournamentNumber;
        //Card m_holeCards[2];
        int m_level;
        int m_gain;
        int m_loss;

    friend std::ostream &operator<<(std::ostream &flux, Hand const& hand);
};

#endif // HAND_H
