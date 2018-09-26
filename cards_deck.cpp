#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int N_OF_FACES = 13;
const int N_OF_SUITS = 4;
const int N_OF_HANDS = 7; //number of poker hands
const int DECK_SIZE = N_OF_SUITS * N_OF_FACES;
const int HAND_SIZE = 5;

const string faceValues[N_OF_FACES] =
    {"Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King", "Ace"};

const string suitValues[N_OF_SUITS] = {"Spades", "Clubs", "Hearts", "Diamonds"};

const string handsOrdered[N_OF_HANDS] = {"High Card", "Pair", "Two Pair", "Three of a Kind", "Four of a Kind", "Flush", "Straight"};


/* A class to represent a single card */
class Card{

  int face;
  int suit;

 public:
  Card(){
  }
  
  Card(int aFace, int  aSuit){
    face = aFace;
    suit = aSuit;
  }

  bool operator>(Card card2){
    if (this->face > card2.face) return true;
    return false;
  }

  int getFace(){
    return face;
  }

  int getSuit(){
    return suit;
  }

  string toString(){
    return faceValues[face] + " of " + suitValues[suit];
  }
};


/* A class to represent a deck of cards */
class DeckOfCards{
  int currentCard = 0;
  
 public:
  Card deck[DECK_SIZE];

  static void swap(Card& card1, Card& card2){
    Card temp = card1;
    card1 = card2;
    card2 = temp;
  }

  DeckOfCards(){
    for(int i = 0; i < N_OF_SUITS; i++)
      {
	for(int j = 0; j < N_OF_FACES; j++)
	  {
	    int curr = j + N_OF_FACES * i;
	    Card tempCard(j,i);
	    deck[curr] = tempCard;
	  }
      }
  }

  void shuffle(){
    currentCard = 0;
    
    srand(time(NULL));
    for(int i = 0; i < DECK_SIZE; i++)
      {
	swap(deck[i], deck[rand() % DECK_SIZE]);
      }
  }

  Card dealCard(){
    return deck[currentCard++];
  }

  bool moreCards(){
    if (currentCard < DECK_SIZE) return true;
    return false;
  }
  
};

void order(Card hand[HAND_SIZE]){
  for(int i = 0; i < HAND_SIZE; i++)
    {
      for(int j = i + 1; j < HAND_SIZE; j++)
	{
	  if (hand[i] > hand[j]) swap(hand[i], hand[j]);
	}
    }
}

bool hasPair(Card hand[HAND_SIZE]){
  for(int i = 0; i < HAND_SIZE - 1; i++)
    {
      if (hand[i].getFace() == hand[i+1].getFace()) return true;
    }
  return false;
}

bool hasTwoPair(Card hand[HAND_SIZE]){
  for(int i = 0; i < HAND_SIZE - 3; i++)
    {
      if (hand[i].getFace() == hand[i+1].getFace()){
	for(int j = i + 2; j < HAND_SIZE - 1; j++)
	  {
	    if (hand[j].getFace() == hand[j+1].getFace()) return true;
	  }
      }
    }
  return false;
}

bool hasThreeOfAKind(Card hand[HAND_SIZE]){
  for (int i = 0; i < HAND_SIZE - 2; i++)
    {
      if ((hand[i].getFace() == hand[i+1].getFace()) && (hand[i+1].getFace() == hand[i+2].getFace())) return true;
    }
  return false;
}

bool hasFourOfAKind(Card hand[HAND_SIZE]){
  if ((hand[0].getFace() == hand[1].getFace()) && (hand[1].getFace() == hand[2].getFace()) && (hand[2].getFace() == hand[3].getFace())) return true;
  else if ((hand[1].getFace() == hand[2].getFace()) && (hand[2].getFace() == hand[3].getFace()) && (hand[3].getFace() == hand[4].getFace())) return true;
  else return false;
}

bool hasFlush(Card hand[HAND_SIZE]){
  int suit = hand[0].getSuit();
  if ((hand[1].getSuit() == suit) && (hand[2].getSuit() == suit) && (hand[3].getSuit() == suit) && (hand[4].getSuit() == suit)) return true;
  return false;
}

bool hasStraight(Card hand[HAND_SIZE]){
  if ((hand[0].getFace() + 1 == hand[1].getFace()) && (hand[1].getFace() + 1 == hand[2].getFace()) && (hand[2].getFace() + 1 == hand[3].getFace()) && (hand[3].getFace() + 1 == hand[4].getFace())) return true;
  return false;
}

int evaluateHand(Card hand[HAND_SIZE]){
  if (hasStraight(hand)) return 6;
  if (hasFlush(hand)) return 5;
  if (hasFourOfAKind(hand)) return 4;
  if (hasThreeOfAKind(hand)) return 3;
  if (hasTwoPair(hand)) return 2;
  if (hasPair(hand)) return 1;
  return 0;
}


int main(){
  DeckOfCards cardDeck;
  Card hand1[HAND_SIZE];
  Card hand2[HAND_SIZE];
  
  cardDeck.shuffle();
  
  /*Deal both poker hands*/
  for(int i = 0; i < HAND_SIZE; i++){
    hand1[i] = cardDeck.dealCard();
    hand2[i] = cardDeck.dealCard();
  }

  order(hand1);
  order(hand2);

  cout <<  "This is hand one: \n";
  for (int i = 0; i < HAND_SIZE; i++){
    cout << hand1[i].toString() + "\n";
  }
  cout << "Hand one has a " << handsOrdered[evaluateHand(hand1)] << endl;

  cout << "\nThis is hand two :\n";
  for (int i = 0; i < HAND_SIZE; i++){
    cout << hand2[i].toString() + "\n";
  }
  cout << "Hand two has a " << handsOrdered[evaluateHand(hand2)] << endl << endl;

  if (evaluateHand(hand1) > evaluateHand(hand2))
    {
      cout << "Hand one is the mighty victor.  Good game!" << endl;
    }

  else if (evaluateHand(hand2) > evaluateHand(hand1))
    {
      cout << "Hand two wins!  Isn't gambling fun?" << endl;
    }

  else cout << "It's a tie." << endl;
  
}

