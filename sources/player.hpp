#pragma once
#include <string>
#include "card.hpp"
#include <vector>

using namespace std;

namespace ariel
{
    class Player
    {
    private:
        string _name;
        vector <Card> playerDeck;
        vector <Card> takenDeck;
        int _winNum;
   
    public:
        
        Player(string Name);//constructor
        short stacksize();
        short cardesTaken();
       
        //getters & setters
        const string& getName() const;
        size_t getPlayerDeckSize();
        size_t getTakenDeckSize();       
        void setPlayerDeckCard(Card& card);
        Card& getPlayerDeckCard();
        void popPlayerDeckCard();
        void setTakenDeckCard(Card& card);
        vector<Card>& getDeck();
        void setDeck(vector<Card>& pack);
        int getWinNum();
        void increaseWinNum();
          
    };
    
          
}// namespace ariel
    