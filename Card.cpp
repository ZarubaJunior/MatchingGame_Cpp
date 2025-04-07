#include "Card.h"

void Map::SetMapSize(int x, int y)
{
    width = x;
    height = y;
}

void Map::SetMap()
{
    // Initialize the 2D grid: each row gets resized once with CardType::None.
    tiles.resize(height);
    for (int y = 0; y < height; ++y) {
        tiles[y].resize(width, CardType::None);
    }

    // Fill the grid in row-major order.
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
        link:
            CardType type = GetRandomType();
            int cardID = getCardsParametres(type).id;
            
            // Tentatively assign the card type.
            tiles[y][x] = type;
            // Check if placing this card makes more than two copies up to (y,x).
            if (!IsTwoCardsV2(type, x, y))
                goto link;

            std::cout << cardID << " ";
        }
        std::cout << std::endl;
    }
}

std::vector<std::vector<CardType>> Map::GetMap()
{
    return tiles;
}

CardType Map::GetRandomType()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 8);
    return getCardTypeFromID(dis(gen));
}

int Map::ConsoleMapCreator(CardType type)
{
    // For displaying purposes, simply return the card's ID.
    return getCardsParametres(type).id;
}

bool Map::IsTwoCardsV2(CardType type, int xMain, int yMain)
{
    int counter = 0;
    // Count occurrences in all rows before the current one.
    for (int y = 0; y < yMain; y++) {
        for (int x = 0; x < width; x++) {
            if (tiles[y][x] == type)
                counter++;
        }
    }
    // In the current row, count only the columns before the current cell.
    for (int x = 0; x < xMain; x++) {
        if (tiles[yMain][x] == type)
            counter++;
    }
    // Allow placement if there are fewer than 2 occurrences so far.
    return (counter < 2);
}

CardType Map::getCardType(int x, int y)
{
    return (tiles[y][x]);
}

std::string MapGUI::getTexture(CardType type)
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

    cardSprites.resize(width, std::vector<sf::Sprite>(height));
    cardTextures.resize(width, std::vector<sf::Texture>(height));
    cardRect.resize(width, std::vector<sf::RectangleShape>(height));
    isOpened.resize(width, std::vector<bool>(height));
    isSkipped.resize(width, std::vector<bool>(height));

    backSprites.resize(width, std::vector<sf::Sprite>(height));
    backTextures.resize(width, std::vector<sf::Texture>(height));
   // for (std::vector <sf::Sprite> cardSprites in *cardSprites)
  //  int xCounter = 0, yCounter = 0;
    float scaleX = 5, scaleY = 5;
        for (int x = 0; x < width; ++x) {
            for (int y = 0; y < height; ++y) {
                        
            if (!cardTextures[x][y].loadFromFile(getTexture(map.getCardType(x,y))))
                std::cout << "TEXTURE ERROR \n";
            cardSprites[x][y].setTexture(cardTextures[x][y]);
            cardSprites[x][y].setPosition(sf::Vector2f(32.f * x * scaleX, 32.f * y * scaleY));
            cardSprites[x][y].setScale(scaleX, scaleY);

            cardRect[x][y].setPosition(sf::Vector2f(32.f * x * scaleX, 32.f * y * scaleY));
            cardRect[x][y].setSize(sf::Vector2f(32 * scaleX, 32 * scaleX));

            isOpened[x][y] = false;
            isSkipped[x][y] = false;

            if (!backTextures[x][y].loadFromFile(getTexture(CardType::None)))
                std::cout << "TEXTURE ERROR \n";
            backSprites[x][y].setTexture(backTextures[x][y]);
            backSprites[x][y].setPosition(sf::Vector2f(32.f * x * scaleX, 32.f * y * scaleY));
            backSprites[x][y].setScale(scaleX, scaleY);


       
            //cardRect.setOrigin(tileSize.x / 2.f, tileSize.y / 2.f);
        }
    }
  //  cardSprites[width, height];
}

void MapGUI::drawMapGUI(sf::RenderWindow& window)
{
    for (int x = 0; x < width; ++x) 
        for (int y = 0; y < height; ++y) 
            window.draw(cardSprites[x][y]); 

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y) 
            if (isOpened[x][y] != true)
                window.draw(backSprites[x][y]);
      
}

void MapGUI::HandleClick(const sf::Vector2f& worldPos)
{
    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
            if (cardRect[x][y].getGlobalBounds().contains(worldPos)) {

                if (isOpened[x][y])
                    continue;

                isOpened[x][y] = true;
                clickCounter++;
                if (clickCounter >= 3) 
                    resetMapAfterClick();
 
                if (clickCounter == 1)
                {
                    previousCardClicked = map.getCardType(x, y);
                    prevCardPos = sf::Vector2i(x, y);
                }
                std::cout << clickCounter << endl;
                std::cout << x << ":" << x << endl;
                if (previousCardClicked == map.getCardType(x, y) && clickCounter == 2) {
                    isSkipped[x][y] = true;
                    isSkipped[prevCardPos.x][prevCardPos.y] = true;
                }

                //previousCardClicked = map.getCardType(x,y);
            }
                
}

void MapGUI::resetMapAfterClick()
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
