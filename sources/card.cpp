
#include <string>
#include "card.hpp"
#include "execinfo.h"

using namespace std;

namespace ariel
{
    Card::Card(int value , string suit){//no need to check argumants
        this->_cardValue = value;
        this->_suit = suit;
    };

    int Card::getCardValue(){
        return this->_cardValue;
    }

    string Card::getCardSuit(){
        return this->_suit;
    }

} // namespace ariel



