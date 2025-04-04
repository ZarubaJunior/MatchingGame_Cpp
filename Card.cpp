#include "Card.h"

void Map::SetMap()
{
	tiles.resize(height);
	
	for (int y = 0; y < height; ++y) {
		tiles[y].resize(width, CardType::None);
		for (int x = 0; x < width; ++x) {
			tiles[x].resize(width, CardType::None);
		}
	}
	// Resize each row to have 'width' columns and initialize with Grass tiles
	for (int y = 0; y < height; ++y) {	
		
		for (int x = 0; x < width; ++x) {
		//	srand(time(NULL));
		//	tiles[x].resize(width, CardType::None);
			link:
			CardType type = GetRandomType();
			int catdID = getCardsParametres(type).id;
			std::cout << catdID << " : ID \n";
			tiles[y][x] = type;
			//if (!IsTwoCards(type)) {

			
		//	}
			if (!IsTwoCardsV2(type, x, y)) 
				goto link;
			
		}
		cout << endl;
	}
}

CardType Map::GetRandomType()
{
	std::random_device rd;
	// Use the Mersenne Twister engine (std::mt19937) seeded with the random device.
	std::mt19937 gen(rd());
	// Define a uniform distribution for integers in the range [1, 100].
	std::uniform_int_distribution<> dis(1, 8);

	
	CardType type = getCardTypeFromID(dis(gen));

	return type;
}

int Map::ConsoleMapCreator(CardType type)
{
	switch (type)
	{
	case CardType::AceOfSpades:
		return 0;
		break;
	case CardType::TwoOfSpades:
		return 1;
		break;
	case CardType::ThreeOfSpades:
		return 2;
		break;
	case CardType::SevenOfDiamonds:
		return 3;
		break;
	default:
		break;
	}
}

bool Map::IsTwoCards(CardType type)
{
	
	int step = 0;
	for (int y = 0; y < height; y++) {
		
		for (int x = 0; x < width; x++) {
		//	std::cout << "COUNTER:" << counter << endl;
			if (tiles[y][x] == type || counter < 2) 
				counter++;
			step++;
			//std::cout << "STEP: "<< x << endl;
			
		}
	}
	if (counter >= 2)
		return false;
	else
	return true;
}

bool Map::IsTwoCardsV2(CardType type, int xMain, int yMain)
{
	int step = 0;
	for (int y = 0; y < yMain; y++) {

		for (int x = 0; x < xMain; x++) {
			//	std::cout << "COUNTER:" << counter << endl;
			if (tiles[y][x] == tiles[xMain][yMain] || counter < 2)
				counter++;
			step++;
			//std::cout << "STEP: "<< x << endl;

		}
	}
	if (counter >= 2)
		return false;
	else
		return true;
}
