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


std::string Card::cardNumberToLetter(int number)
{
    std::string value;
    if (number == 1) value = "A";
    else if (number == 2) value =  "2";
    else if (number == 3) value =  "3";
    else if (number == 4) value =  "4";
    else if (number == 5) value =  "5";
    else if (number == 6) value =  "6";
    else if (number == 7) value =  "7";
    else if (number == 8) value =  "8";
    else if (number == 9) value =  "9";
    else if (number == 10) value = "T";
    else if (number == 11) value =  "J";
    else if (number == 12) value =  "Q";
    else if (number == 13) value =  "K";
    else return "";

    return value;
}

int Card::cardLetterToNumber(int number)
{
    return number;
}

int Card::cardSuitToNumber(std::string stringNumber)
{
    if (stringNumber == "o") return 0;
    else if (stringNumber == "s") return 1;

    return -1;
}

void Card::setValue(int value)
{
    m_value = cardLetterToNumber(value);
}

int Card::value() const
{
    return m_value;
}

std::string Card::valueString()
{
    return cardNumberToLetter(m_value);
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
