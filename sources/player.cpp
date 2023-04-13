#include "player.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

namespace ariel
{
    //constructor
    Player::Player(string name){
        this->_name = name;
        this->_winNum = 0;
        
    };

    short Player::stacksize(){
        return this->playerDeck.size();
    }

    short Player::cardesTaken(){
        return this->takenDeck.size();
    }

    //getters & setters
    const string& Player::getName() const{
        return this->_name;
    }

    vector<Card>& Player::getDeck(){
        return this->playerDeck;
    }

    void Player::setDeck(vector<Card>& pack){
        this->playerDeck=pack;
    }

    void Player::setPlayerDeckCard(Card& card){
        this->playerDeck.push_back(card);
    }

    Card& Player::getPlayerDeckCard(){
        return this->playerDeck.back();
    }
    void Player::popPlayerDeckCard(){
        this->playerDeck.pop_back();
    }

    void Player::setTakenDeckCard(Card& card){
        this->takenDeck.push_back(card);
    }

    size_t Player::getPlayerDeckSize(){
        return this->playerDeck.size();
    }

    size_t Player::getTakenDeckSize(){
        return this->takenDeck.size();
    }

    void Player::increaseWinNum(){
        this->_winNum++;
    }
    int Player::getWinNum(){
        return this->_winNum;
    }

   
    

} // namespace ariel







