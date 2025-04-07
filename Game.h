#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Card.h"

class Game
{
public:
	Game();
	virtual ~Game();

	const bool isRunning() const;
	void updateEvents(float deltaTime);
	void update();
	void render();
private:
	void initWindow();
	void initVars();
	void initTilesMenu();
	void keyBoardInput();
//	void updateCamera(float deltaTime, sf::Vector2f mouse);
	void handleTileClick(const sf::Vector2f& worldPos);
private:
	sf::RenderWindow* window;
	sf::Event ev;
	sf::VideoMode videoMode;
	sf::Clock clock;
	sf::View view;
	float deltaTime;
	std::vector <Card> cards;
	Card card;
	MapGUI map;
	float currentZoom;
	float targetZoom;
};

