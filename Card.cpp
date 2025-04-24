#include "Card.h"

// Sets map size by width(x) and hight(y)
void Map::SetMapSize(int x, int y)
{
    width = x;
    height = y;
}

void Map::SetMap()
{
    tiles.resize(height); // Resizing Vector
    for (int y = 0; y < height; ++y) 
        tiles[y].resize(width, CardType::None); // Changing size by height and Seting card type to None for all card

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        link: // Bad Code            
            CardType type = GetRandomType(); // Getting random number for card
            int cardID = getCardsParametres(type).id;
            tiles[y][x] = type;            
            if (!IsTwoCardsV2(type, x, y))  // Is theere two same cards getrandom number again
                goto link;   
            std::cout << cardID << " "; // Console check
        }
        std::cout << std::endl;
    }

}

std::vector<std::vector<CardType>> Map::GetMap() // Get Masp Array 
{
    return tiles; 
}

CardType Map::GetRandomType() // Get Random Number
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);
    return getCardTypeFromID(dis(gen));
}

int Map::ConsoleMapCreator(CardType type) // Returns id of field
{
    return getCardsParametres(type).id;
}

bool Map::IsTwoCardsV2(CardType type, int xMain, int yMain) // Checks for two same cards
{
    int counter = 0;
    for (int y = 0; y < yMain; y++) 
        for (int x = 0; x < width; x++) 
            if (tiles[y][x] == type)
                counter++;

    for (int x = 0; x < xMain; x++) 
        if (tiles[yMain][x] == type)
            counter++;

    return (counter < 2);
}

CardType Map::getCardType(int x, int y) // Returns CardType using x and y coords
{
    return (tiles[y][x]);
}

std::string MapGUI::getTexture(CardType type) // Getting Path tp texture using CardType
{
    switch (type)
    {
    case CardType::None:
        return "Res//Textures//Back.png";
    case CardType::AceOfSpades:
        return "Res//Textures//Spades.png";
    case CardType::AceOfTrumpets:
        return "Res//Textures//Trumpets.png";
    case CardType::AceOfHearts:
        return "Res//Textures//Hearts.png";
    case CardType::AceOfDiamonds:
        return "Res//Textures//Diamonds.png";
    case CardType::KingHearts:
        return "Res//Textures//KingHearts.png";
    case CardType::KingTrumpets:
        return "Res//Textures//KingTrumpets.png";
    case CardType::BlackJoker:
        return "Res//Textures//BlackJoker.png";
    case CardType::WhiteJoker:
        return "Res//Textures//WhiteJoker.png";
    default:
        return "Res//Textures//Back.png";
    }
}

void MapGUI::initSprites()
{
   
    CardType type;
    map.SetMapSize(width, height);
    map.SetMap();

    // Resizing Vectors
    cardSprites.resize(width, std::vector<sf::Sprite>(height));
    cardTextures.resize(width, std::vector<sf::Texture>(height));
    cardRect.resize(width, std::vector<sf::RectangleShape>(height));
    isOpened.resize(width, std::vector<bool>(height));
    isSkipped.resize(width, std::vector<bool>(height));

    backSprites.resize(width, std::vector<sf::Sprite>(height));
    backTextures.resize(width, std::vector<sf::Texture>(height));

    // Setting background square
    float scaleX = 5, scaleY = 5;   // Setting scale
    background.setPosition(sf::Vector2f(mapOffstet.x-10, mapOffstet.x - 10));
    background.setSize(sf::Vector2f(32 * scaleX *4 + 20 , 32 * scaleX * 4 + 20 ));
    background.setFillColor(sf::Color(97, 97, 97));

    // Setting CardSprites
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                        
            if (!cardTextures[x][y].loadFromFile(getTexture(map.getCardType(x,y))))
                std::cout << "TEXTURE ERROR \n";
            cardSprites[x][y].setTexture(cardTextures[x][y]);
            cardSprites[x][y].setPosition(sf::Vector2f(32.f * x * scaleX + mapOffstet.x, 32.f * y * scaleY + mapOffstet.y));
            cardSprites[x][y].setScale(scaleX, scaleY);

            cardRect[x][y].setPosition(sf::Vector2f(32.f * x * scaleX + mapOffstet.x, 32.f * y * scaleY + mapOffstet.y));
            cardRect[x][y].setSize(sf::Vector2f(32 * scaleX, 32 * scaleX));

            isOpened[x][y] = false;
            isSkipped[x][y] = false;

            if (!backTextures[x][y].loadFromFile(getTexture(CardType::None)))
                std::cout << "TEXTURE ERROR \n";
            backSprites[x][y].setTexture(backTextures[x][y]);
            backSprites[x][y].setPosition(sf::Vector2f(32.f * x * scaleX + mapOffstet.x, 32.f * y * scaleY + mapOffstet.y));
            backSprites[x][y].setScale(scaleX, scaleY);
        }
    }
}
 
void MapGUI::drawMapGUI(sf::RenderWindow& window) // Draws Sprites / RENDER
{
    window.draw(background);

    for (int x = 0; x < width; ++x) 
        for (int y = 0; y < height; ++y) 
            window.draw(cardSprites[x][y]); 

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y) 
            if (isOpened[x][y] != true)
                window.draw(backSprites[x][y]);
}

void MapGUI::HandleClick(const sf::Vector2f& worldPos) // Handle Mouse click
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            // Checking where user made his click
            if (cardRect[x][y].getGlobalBounds().contains(worldPos)) {

                if (isOpened[x][y])   // If the card is already open - skip it
                    continue;

                isOpened[x][y] = true; // open card
                clickCounter++;
                if (clickCounter >= 3)  // Closing all not skipped cards on the map if user didn't guess the card
                    resetMapAfterClick(); 
 
                if (clickCounter == 1)  // Checking if prev. card is same as present card resetMapAfterClick
                { 
                    previousCardClicked = map.getCardType(x, y);
                    prevCardPos = sf::Vector2i(x, y);
                }
                std::cout << x << ":" << x << endl;
                // If User guessed the second card both of them will be skipped while 
                if (previousCardClicked == map.getCardType(x, y) && clickCounter == 2) { 
                    isSkipped[x][y] = true;
                    isSkipped[prevCardPos.x][prevCardPos.y] = true;
                }
            }         
}

void MapGUI::resetMapAfterClick()   // Closing all not skipped cards on the map
{
    clickCounter = 0;

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y) {
            if (!isSkipped[x][y])
                isOpened[x][y] = false;
            else
                isOpened[x][y] = true;
        }
          
}
