#ifndef CARD_H
#define CARD_H

#include <string>

class Card
{
    public:
    Card();
    Card(int value, std::string color);
    void setValue(int value);
    int value() const;
    std::string color() const;
    int cardLetterToNumber(std::string stringNumber);
    int cardLetterToNumber(int number);

    private:
    int m_value;
    std::string m_color; //Heart, Diamond, Spade or Clubs

    friend std::ostream& operator<< (std::ostream& flux, Card const& card);
};

#endif // CARD_H
