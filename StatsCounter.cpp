#include "StatsCounter.h"

StatsCounter::StatsCounter()
{

}

int StatsCounter::showdowns() const
{
    return m_showdowns;
}

int StatsCounter::foldPreflop() const
{
    return m_foldPreflop;
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
void StatsCounter::reset()
{
    m_showdowns = 0;
    m_foldPreflop = 0;
    m_foldTurn = 0;
    m_foldRiver = 0;
}
void StatsCounter::updateTotal()
{
    m_total = m_showdowns + m_foldPreflop + m_foldTurn + m_foldRiver;
}

