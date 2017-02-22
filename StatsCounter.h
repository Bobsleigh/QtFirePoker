#ifndef STATSCOUNTER_H
#define STATSCOUNTER_H


class StatsCounter
{
public:
    StatsCounter();
    void incrShowdowns();
    void incrWins();
    void incrFoldPreflop();
    void incrFoldTurn();
    void incrFoldRiver();
    int showdowns() const;
    int wins() const;
    int foldPreflop() const;
    int foldTurn() const;
    int foldRiver() const;
    int total() const;
    void reset();
    void updateTotal();

private:
    int m_showdowns;
    int m_wins;
    int m_foldPreflop;
    int m_foldTurn;
    int m_foldRiver;
    int m_total;
};

#endif // STATSCOUNTER_H
