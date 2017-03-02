#ifndef STATSCOUNTER_H
#define STATSCOUNTER_H

enum class Street {PREFLOP, FLOP, TURN, RIVER, SHOWDOWN};

class StatsCounter
{
public:
    StatsCounter();
    void incrShowdowns();
    void incrWins();
    void incrFoldPreflop();
    void incrFoldFlop();
    void incrFoldTurn();
    void incrFoldRiver();
    void incrFold(Street currentStreet);
    int showdowns() const;
    int wins() const;
    int foldPreflop() const;
    int foldFlop() const;
    int foldTurn() const;
    int foldRiver() const;
    int total() const;
    void reset();
    void updateTotal();

private:
    int m_showdowns;
    int m_wins;
    int m_foldPreflop;
    int m_foldFlop;
    int m_foldTurn;
    int m_foldRiver;
    int m_total;
};

#endif // STATSCOUNTER_H
