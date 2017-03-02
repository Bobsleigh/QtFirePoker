#ifndef HAND_H
#define HAND_H

#include "Card.h"
#include "Parsing/HoleCards.h"


class Hand
{
    public:
        Hand();
        //Hand(int handNumber, int tournamentNumber);
        int net() const;
        void setGain(int gain);
        void setLoss(int loss);
        void setHoleCards(Card firstCard, Card secondCard);
        void setHandNumber(long long handNumber);
        void setTournamentNumber(long long tournamentNumber);
        void setSmallBlind(int smallBlind);
        void setBigBlind(int bigBlind);
        void setYear(int year);
        void setMonth(int month);
        void setDay(int day);
        int loss() const;
        int gain() const;
        long long handNumber() const;
        long long tournamentNumber() const;
        int smallBlind() const;
        int bigBlind() const;
        int year() const;
        int month() const;
        int day() const;
        Card firstHoleCard();
        Card secondHoleCard();
        HoleCards holeCards();

    private:
        long long m_handNumber;
        long long m_tournamentNumber;
        int m_smallBlind;
        int m_bigBlind;
        int m_year;
        int m_month;
        int m_day;
        HoleCards m_holeCards;
        int m_level;
        int m_gain;
        int m_loss;

    friend std::ostream &operator<<(std::ostream &flux, Hand const& hand);
};

#endif // HAND_H
