#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include "assert.h"
#include "string"
#include "game.hpp"
#include "card.hpp"
#include "player.hpp"

namespace ariel
{
   void makeDeck(vector<Card> &deck)
   {
      for (int i = 1; i < 14; i++)
      { // ♥
         deck.push_back(Card(i, "hearts"));
      }
      for (int i = 1; i < 14; i++)
      { // ♣
         deck.push_back(Card(i, "clubs"));
      }
      for (int i = 1; i < 14; i++)
      { // ◆
         deck.push_back(Card(i, "diamonds"));
      }
      for (int i = 1; i < 14; i++)
      { // ♠
         deck.push_back(Card(i, "spades"));
      }
   }

   // shuffleDeck function shuffles the deck using the Fisher-Yates shuffle algorithm,
   // seeded with the current system time to ensure randomness.
   void shuffleDeck(vector<Card> &deck)
   {
      unsigned seed = chrono::system_clock::now().time_since_epoch().count();
      shuffle(deck.begin(), deck.end(), default_random_engine(seed));
   }

   string Game::stringGenerate()
   {
      string lastTurn1 = _player1.getName() + " played ";
      string lastTurn2 = _player2.getName() + " played ";

      switch (this->_player1.getPlayerDeckCard().getCardValue())
      {
      case 1:
         lastTurn1 += "Ace";
         break;
      case 11:
         lastTurn1 += "Jack";
         break;
      case 12:
         lastTurn1 += "Queen";
         break;
      case 13:
         lastTurn1 += "King";
         break;
      default:
         lastTurn1 += to_string(_player1.getPlayerDeckCard().getCardValue());
         break;
      }
      lastTurn1 += " of " + _player1.getPlayerDeckCard().getCardSuit() + ". ";

      switch (_player2.getPlayerDeckCard().getCardValue())
      {
      case 1:
         lastTurn2 += "Ace";
         break;
      case 11:
         lastTurn2 += "Jack";
         break;
      case 12:
         lastTurn2 += "Queen";
         break;
      case 13:
         lastTurn2 += "King";
         break;
      default:
         lastTurn2 += to_string(_player2.getPlayerDeckCard().getCardValue());
         break;
      }

      lastTurn2 += " of " + _player2.getPlayerDeckCard().getCardSuit() + ". ";
      string lastTurn = lastTurn1 + lastTurn2;

      return lastTurn;
   }

   Game::Game(Player &player1, Player &player2) : _player1(player1), _player2(player2)
   {
      this->_totalTurns = 0;
      this->_drawCount = 0;

      makeDeck(this->_deck);
      assert(_deck.size() == 52); // deck size must be 52!
      shuffleDeck(this->_deck);   // shuffle the cards
      
      // add cards to players deck
      for (size_t i = 0; i < 52; i += 2)
      {
         _player1.setPlayerDeckCard(_deck[i]);
         _player2.setPlayerDeckCard(_deck[i+1]);
         
      }
   }
   // true p1 win false p2 win
   bool checkWinner(int p1Card, int p2Card)
   {
      if (p1Card == 1 && p2Card == 2)
         return false; // p1 have ace, p2 have 2,p2 win.
      if (p1Card == 1 && p2Card > 2)
         return true; // p1 win with ace
      if (p2Card == 1 && p1Card == 2)
         return true; // p1 win
      if (p2Card == 1 && p1Card > 2)
         return false; // p2 win
      if (p1Card < p2Card)
         return false; // p2 win
      return true;     // p1 win
   }
   // true - player 1 win , false - player 2 win
   void Game::popAndPush(bool flag)
   {
      if (flag)
      {
         _player1.setTakenDeckCard(_player1.getPlayerDeckCard());
         _player1.setTakenDeckCard(_player2.getPlayerDeckCard());
         _player1.popPlayerDeckCard();
         _player2.popPlayerDeckCard();
      }
      else
      {
         _player2.setTakenDeckCard(_player2.getPlayerDeckCard());
         _player2.setTakenDeckCard(_player1.getPlayerDeckCard());
         _player1.popPlayerDeckCard();
         _player2.popPlayerDeckCard();
      }
   }

   void Game::playTurn()
   {
      if (&this->_player1 == &this->_player2)
      {
         throw invalid_argument("cannot play with the same player!");
      }

      if (_player1.getPlayerDeckSize() == 0 || _player2.getPlayerDeckSize() == 0)
      {
         throw runtime_error("the game is already end!");
      }

      this->_totalTurns++;
      if (_player1.getPlayerDeckCard().getCardValue() != _player2.getPlayerDeckCard().getCardValue())
      {

         bool flag = checkWinner(_player1.getPlayerDeckCard().getCardValue(), _player2.getPlayerDeckCard().getCardValue());
         string temp = stringGenerate(); // generate the cards string
         // player 1 win
         if (flag)
         {
            temp = temp + _player1.getName() + " win.";
            this->turnPrint.push_back(temp);
            popAndPush(true);
            _player1.increaseWinNum();
         }
         // player2 win
         else
         {
            temp = temp + _player2.getName() + " win.";
            this->turnPrint.push_back(temp);
            popAndPush(false);
            _player2.increaseWinNum();
         }
      }
      // tie
      else
      {
         vector<Card> p1Deck = _player1.getDeck();
         vector<Card> p2Deck = _player2.getDeck();

         size_t index = p1Deck.size() - 1;

         int count = 0;
         bool cardEnds = false;
         string temp; // generate the cards string

         while (p1Deck[index].getCardValue() == p2Deck[index].getCardValue())
         {
            this->_drawCount++;
            if (index == 0)
            { // tie in last round

               this->turnPrint.push_back(temp);
               cardEnds = true;
               count++;

               break;
            }
            else if (index == 1)
            { // tie in last round

               this->turnPrint.push_back(temp);
               count = count + 2;
               cardEnds = true;
               break;
            }
            else
            {
               count = count + 2;
               index = index - 2;
            }
         }

         if (cardEnds)
         {
            while (count > 0)
            {
               _player1.setTakenDeckCard(_player1.getPlayerDeckCard());
               _player1.popPlayerDeckCard();
               _player2.setTakenDeckCard(_player2.getPlayerDeckCard());
               _player2.popPlayerDeckCard();
               if (count == 1)
               {
                  temp += " last card draw spilt the cards ";
               }
               count--;
            }
         }
         else
         {
            bool flag = checkWinner(p1Deck[index].getCardValue(), p2Deck[index].getCardValue());
            if (flag) // player 1 win
            {
               while (count > 0)
               {
                  temp = temp + stringGenerate();
                  popAndPush(true);
                  if (count > 1)
                     popAndPush(true);

                  if (count > 1)
                  {
                     temp += " Draw. ";
                  }
                  count--;
               }
               temp = temp + _player1.getName() + " win. ";
               this->turnPrint.push_back(temp);
               _player1.increaseWinNum();
            }
            else // player 2 win
            {
               while (count > 0)
               {
                  temp = temp + stringGenerate();
                  popAndPush(false);
                  if (count > 1)
                     popAndPush(false);

                  if (count > 1)
                  {
                     temp += " Draw. ";
                  }
                  count--;
               }
               temp = temp + _player2.getName() + " win. ";
               this->turnPrint.push_back(temp);
               _player2.increaseWinNum();
            }
         }
      }
   };

   void Game::printLastTurn()
   {
      if (_player1.getPlayerDeckSize() == 26 && _player1.getPlayerDeckSize() == 26)
      {
         throw runtime_error("the game didnt start yet!");
      }
      cout << this->turnPrint.back() << endl;
   };

   void Game::playAll()
   {
      if (_player1.getPlayerDeckSize() == 0)
      {
         throw runtime_error("the game is ended!");
      }
      while (_player1.getPlayerDeckSize() > 0)
      {
         playTurn();
      }
   }

   void Game::printWiner()
   {
      if (_player1.getPlayerDeckSize() != 0)
      {
         cout << "The game dont end yet!" << endl;
      }
      if (_player1.getTakenDeckSize() == _player2.getTakenDeckSize())
      {
         cout << "The game ended with Draw!" << endl;
      }
      else if (_player1.getTakenDeckSize() > _player2.getTakenDeckSize())
      {
         cout << "The winner is " << _player1.getName() << endl;
      }
      else
      {
         cout << "The winner is " << _player2.getName() << endl;
      }
   }

   void Game::printLog()
   {
      for (size_t i = 0; i < turnPrint.size(); i++)
      {
         cout << turnPrint[i] << endl;
      }
   }

   void Game::printStats()
   {
      float player1WinRate = (_player1.getWinNum() / (float)this->_totalTurns) * 100;
      float player2WinRate = (_player2.getWinNum() / (float)this->_totalTurns) * 100;
      float drawRate = ((float)this->_drawCount / this->_totalTurns) * 100;
      cout << "player 1 win rate: " + to_string(player1WinRate) + "% ";
      cout << "player 2 win rate: " + to_string(player2WinRate) + "% " << endl;
      cout << "player 1 win " << to_string(_player1.getTakenDeckSize()) << "cards ";
      cout << "player 2 win " << to_string(_player2.getTakenDeckSize()) << "cards " << endl;
      cout << "draw count : " + to_string(this->_drawCount) + " draw rate: " + to_string(drawRate) + "%" << endl;
   }

}
