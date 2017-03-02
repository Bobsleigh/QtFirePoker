#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
    public:
    Card();
    Card(int value, std::string color);
    Card(std::string value, std::string color);
    void setValue(int value);
    int value() const;
    std::string valueString();
    std::string color() const;
    static int cardLetterToNumber(std::string stringNumber);
    static int cardLetterToNumber(char stringNumber);
    static int cardLetterToNumber(int number);
    static std::string cardNumberToLetter(int number);
    static int cardSuitToNumber(std::string stringNumber);

    private:
    int m_value;
    std::string m_color; //Heart, Diamond, Spade or Clubs

    friend std::ostream& operator<< (std::ostream& flux, Card const& card);
};

#endif // CARD_H
