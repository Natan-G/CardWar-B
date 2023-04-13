#pragma once
#include <string>

using namespace std;

namespace ariel
{
    class Card
    {
    private:
        int _cardValue;
        string _suit;

    public:    
        Card(int value , string shape);
        int getCardValue();
        string getCardSuit();
        
    };
    

} // namespace ariel
