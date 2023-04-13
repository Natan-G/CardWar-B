#pragma once
#include "player.hpp"
#include "card.hpp"

using namespace std;

namespace ariel
{
    class Game
    {
    private:
        Player& _player1;
        Player& _player2;
        vector<Card> _deck;
        vector<string> turnPrint;
    
        short _totalTurns;
        short _drawCount;
        string stringGenerate();
        void popAndPush(bool flag);

        
    public:
        Game(Player& player1 , Player& player2);

        void playTurn();
        void printLastTurn();
        void playAll();
        void printWiner();
        void printLog();
        void printStats();

     
        
    };
    

    
} // namespace ariel
