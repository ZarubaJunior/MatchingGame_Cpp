#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <random>
using namespace std;

enum class CardType {
	None,
	AceOfSpades,
	TwoOfSpades,
	ThreeOfSpades,
	SevenOfDiamonds,
	AceOfDiamonds,
	TwoOfDiamonds,
	ThreeOfDiamonds,
	FourOfDiamonds

};

struct CardsParametres {
	int id;
};
inline CardsParametres getCardsParametres(CardType type) {
	switch (type)
	{
	case CardType::None:
		return { 0 };
		break;
	case CardType::AceOfSpades:
		return { 1 };
		break;
	case CardType::TwoOfSpades:
		break;
		return { 2 };
	case CardType::ThreeOfSpades:
		break;
		return { 3 };
	case CardType::SevenOfDiamonds:
		break;
		return { 4 };
	case CardType::AceOfDiamonds:
		break;
		return { 5 };
	case CardType::TwoOfDiamonds:
		break;
		return { 6 };
	case CardType::ThreeOfDiamonds:
		break;
		return { 7 };
	case CardType::FourOfDiamonds:
		break;
		return { 8 };
	default:
		break;
	}
}
inline CardType getCardTypeFromID(int id) {
	switch (id) {
	case 1: return CardType::AceOfSpades;
	case 2: return CardType::TwoOfSpades;
	case 3: return CardType::ThreeOfSpades;
	case 4: return CardType::SevenOfDiamonds;
	case 5: return CardType::AceOfDiamonds;
	case 6: return CardType::TwoOfDiamonds;
	case 7: return CardType::ThreeOfDiamonds;
	case 8: return CardType::FourOfDiamonds;
	default:
		// You can choose to throw an exception or return a default value
		return CardType::AceOfSpades;
	}
}
class Card
{
	std::vector<CardType> cards;
};

class Map
{
	
	//std::vector<width, height, CardType> cards;
	//std::vector<width, height> coords;
	//cards.resize()
public:
	int width = 4, height = 4;
	void SetMap();
	CardType GetRandomType();
	int ConsoleMapCreator(CardType type);
	//std::vector<std::vector<std::unique_ptr<CardType>>> tiles;

	std::vector<std::vector<CardType>> tiles;
	bool IsTwoCards(CardType type);
	bool IsTwoCardsV2(CardType type, int xMain, int yMain);
	int counter = 0;

};