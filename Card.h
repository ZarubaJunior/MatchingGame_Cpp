#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>     /* srand, rand */
#include <time.h>  
#include <random>
#include <SFML/Graphics.hpp>
using namespace std;

enum class CardType {
	None,
	AceOfSpades,
	AceOfTrumpets,
	AceOfHearts,
	AceOfDiamonds,
	KingHearts,
	KingTrumpets,
	BlackJoker,
	WhiteJoker

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
	case CardType::AceOfTrumpets:
		break;
		return { 2 };
	case CardType::AceOfHearts:
		break;
		return { 3 };
	case CardType::AceOfDiamonds:
		break;
		return { 4 };
	case CardType::KingHearts:
		break;
		return { 5 };
	case CardType::KingTrumpets:
		break;
		return { 6 };
	case CardType::BlackJoker:
		break;
		return { 7 };
	case CardType::WhiteJoker:
		break;
		return { 8 };
	default:
		break;
	}
}


struct CardsTextureParametres {
	std::string texturePath;
};
inline CardsTextureParametres getCardsTextureParametres(CardType type) {
	switch (type)
	{
	case CardType::None:
		return { "Res//Textures//Back.png" };
		break;
	case CardType::AceOfSpades:
		return { "Res//Textures//Spades.png" };
		break;
	case CardType::AceOfTrumpets:
		return { "Res//Textures//Trumpets.png" };
		break;		
	case CardType::AceOfHearts:
		break;
		return { "Res//Textures//Hearts.png" };
	case CardType::AceOfDiamonds:
		break;
		return { "Res//Textures//Diamonds.png" };
	case CardType::KingHearts:
		break;
		return { "Res//Textures//KingHearts.png" };
	case CardType::KingTrumpets:
		break;
		return {"Res//Textures//KingTrumpets.png" };
	case CardType::BlackJoker:
		break;
		return { "Res//Textures//BlackJoker.png" };
	case CardType::WhiteJoker:
		break;
		return { "Res//Textures//Back" };
	default:
		return { "Res//Textures//Back" };
		break;
	}
}

inline CardType getCardTypeFromID(int id) {
	switch (id) {
	case 1: return CardType::AceOfSpades;
	case 2: return CardType::AceOfTrumpets;
	case 3: return CardType::AceOfHearts;
	case 4: return CardType::AceOfDiamonds;
	case 5: return CardType::KingHearts;
	case 6: return CardType::KingTrumpets;
	case 7: return CardType::BlackJoker;
	case 8: return CardType::WhiteJoker;
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
	
public:
	int width = 4, height = 4;
	void SetMapSize(int x, int y);
	void SetMap();
	std::vector<std::vector<CardType>> GetMap();
	CardType GetRandomType();
	int ConsoleMapCreator(CardType type); 

	std::vector<std::vector<CardType>> tiles;
	bool IsTwoCards(CardType type);
	bool IsTwoCardsV2(CardType type, int xMain, int yMain);
	int counter = 0;


	CardType getCardType(int x, int y);

	
};
class MapGUI {
public:
	std::vector < std::vector<sf::Sprite>> cardSprites;
	std::vector < std::vector<sf::Texture>> cardTextures;
	std::vector < std::vector<sf::RectangleShape>> cardRect;
	std::vector < std::vector<bool>> isOpened;
	std::vector < std::vector<bool>> isSkipped;
	std::vector < std::vector<sf::Sprite>> backSprites;
	std::vector < std::vector<sf::Texture>> backTextures;
	std::string getTexture(CardType type);
	void initSprites();
	Map map;
	void drawMapGUI(sf::RenderWindow& window);
	int width = 4, height = 4;

	void HandleClick(const sf::Vector2f& worldPos);
	int clickCounter = 0;
	void resetMapAfterClick();
	CardType previousCardClicked =CardType::None;
	sf::Vector2i prevCardPos = { 0,0 };
};