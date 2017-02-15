#include "Card.h"
#include <iostream>

Card::Card() : m_value(0), m_color("Heart")
{

}

Card::Card(int value, std::string color) : m_value(value), m_color(color)
{

}

Card::Card(std::string value, std::string color) : m_value(cardLetterToNumber(value)), m_color(color)
{

}


int Card::cardLetterToNumber(std::string stringNumber)
{
    if (stringNumber == "A") return 1;
    else if (stringNumber == "1") return 1;
    else if (stringNumber == "2") return 2;
    else if (stringNumber == "3") return 3;
    else if (stringNumber == "4") return 4;
    else if (stringNumber == "5") return 5;
    else if (stringNumber == "6") return 6;
    else if (stringNumber == "7") return 7;
    else if (stringNumber == "8") return 8;
    else if (stringNumber == "9") return 9;
    else if (stringNumber == "10") return 10;
    else if (stringNumber == "T") return 10;
    else if (stringNumber == "J") return 11;
    else if (stringNumber == "Q") return 12;
    else if (stringNumber == "K") return 13;

    return -1;
}

int Card::cardLetterToNumber(int number)
{
    return number;
}

void Card::setValue(int value)
{
    m_value = cardLetterToNumber(value);
}

int Card::value() const
{
    return m_value;
}

std::string Card::color() const
{
    return m_color;
}

std::ostream &operator<<(std::ostream &flux, Card const& card)
{
    flux << card.m_value << card.m_color;
    return flux;
}
