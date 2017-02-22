#ifndef HOLECARDS_H
#define HOLECARDS_H

#include "Card.h"


class HoleCards
{
public:
    HoleCards();
    HoleCards(Card cardOne, Card cardTwo);
    bool isSuited();
    void setHoleCards(Card firstCard, Card secondCard);
    void getCardsRank();
    int higherValue();
    int lowerValue();
    Card firstCard();
    Card secondCard();

private:
    Card m_cards[2];
};

/* If ever needed:
enum CardsRank {
    AA, AKs, AQs, AJs, ATs, A9s, A8s, A7s, A6s, A5s, A4s, A3s, A2s,
    AKo, KK, KQs, KJs, KTs, K9s, K8s, K7s, K6s, K5s, K4s, K3s, K2s,
    AQo, KQo, QQ, QJs, QTs, Q9s, Q8s, Q7s, Q6s, Q5s, Q4s, Q3s, Q2s,
    QJo, KJo, QJo, JJ, JTs, J9s, J8s, J7s, J6s, J5s, J4s, J3s, J2s,
    ATo, KTo, QTo, JTo, TT, T9s, T8s, T7s, T6s, T5s, T4s, T3s, T2s,
    A9o, K9o, Q9o, J9o, T9o, 99, 98s, 97s,

};
*/
#endif // HOLECARDS_H
