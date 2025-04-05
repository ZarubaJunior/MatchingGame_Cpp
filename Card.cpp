#include "Card.h"

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
