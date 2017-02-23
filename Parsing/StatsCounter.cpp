#include "Parsing/StatsCounter.h"
#include "Parsing/PokerTextFile.h"

StatsCounter::StatsCounter() : m_showdowns(0), m_wins(0), m_foldPreflop(0), m_foldFlop(0), m_foldTurn(0), m_foldRiver(0), m_total(0)
{

}

int StatsCounter::showdowns() const
{
    return m_showdowns;
}

int StatsCounter::wins() const
{
    return m_wins;
}

int StatsCounter::foldPreflop() const
{
    return m_foldPreflop;
}
int StatsCounter::foldFlop() const
{
    return m_foldFlop;
}
int StatsCounter::foldTurn() const
{
    return m_foldTurn;
}
int StatsCounter::foldRiver() const
{
    return m_foldRiver;
}
int StatsCounter::total() const
{
    return m_total;
}
void StatsCounter::incrShowdowns()
{
    m_showdowns++;
    updateTotal();
}
void StatsCounter::incrWins()
{
    m_wins++;
    updateTotal();
}
void StatsCounter::incrFoldPreflop()
{
    m_foldPreflop++;
    updateTotal();
}
void StatsCounter::incrFoldFlop()
{
    m_foldFlop++;
    updateTotal();
}
void StatsCounter::incrFoldTurn()
{
    m_foldTurn++;
    updateTotal();
}
void StatsCounter::incrFoldRiver()
{
    m_foldRiver++;
    updateTotal();
}

void StatsCounter::incrFold(Street currentStreet)
{
    if (currentStreet == Street::PREFLOP)
    {
        incrFoldPreflop();
    }
    else if (currentStreet == Street::FLOP)
    {
        incrFoldFlop();
    }
    else if (currentStreet == Street::TURN)
    {
        incrFoldTurn();
    }
    else if (currentStreet == Street::RIVER)
    {
        incrFoldRiver();
    }

}
void StatsCounter::reset()
{
    m_showdowns = 0;
    m_foldPreflop = 0;
    m_foldFlop = 0;
    m_foldTurn = 0;
    m_foldRiver = 0;
    m_total = 0;
}
void StatsCounter::updateTotal()
{
    m_total = m_showdowns + m_foldPreflop + m_foldFlop + m_foldTurn + m_foldRiver;
}

