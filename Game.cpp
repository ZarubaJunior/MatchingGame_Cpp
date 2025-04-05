#include "Game.h"
void Game::initWindow()
{
	this->videoMode.height = 1000;
	this->videoMode.width = 1800;

	this->window = new sf::RenderWindow(this->videoMode, "Animation Program");
	this->window->setFramerateLimit(60);

	this->view = sf::View(sf::FloatRect(0.f, 0.f, this->videoMode.width, this->videoMode.height));
	this->window->setMouseCursorVisible(false);
}

void Game::initVars() {
	this->window = nullptr;


	this->mouseCircle.setFillColor(sf::Color(255, 242, 122));
	this->mouseCircle.setPosition(sf::Vector2f(0, 0));
	this->mouseCircle.setRadius(10.f);
	//this->mouseCircle.setOrigin(this->mouseCircle.getRadius(), this->mouseCircle.getRadius());
	this->mouseEntity.setFillColor(sf::Color(0, 0, 0, 20));
	this->mouseEntity.setPosition(sf::Vector2f(0, 0));
	this->mouseEntity.setRadius(10.f);
}

void Game::initTilesMenu()
{
}

void Game::keyBoardInput()
{
}

Game::Game()
{
	this->initVars();
	this->initWindow();
	this->initTilesMenu();

}

Game::~Game() { delete this->window; }

const bool Game::isRunning() const { return this->window && this->window->isOpen(); }

void Game::handleTileClick(const sf::Vector2f& worldPos)
{/*
	for (auto& cards : cards)
	{
		if (cards.tileRect.getGlobalBounds().contains(worldPos))
		{
			tile.init(
				tile.tileRect.getPosition().x,
				tile.tileRect.getPosition().y,
				tile.tileRect.getSize().x,
				tile.tileRect.getSize().y,
				TileType::Water
			);

			break;
		}
	}*/
}

void Game::updateEvents(float deltaTime)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(*this->window);
	while (this->window && this->window->pollEvent(this->ev)) {
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;

		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Num1)
				std::cout << "Dsdsn";
			break;

		case sf::Event::MouseWheelScrolled:
			if (this->ev.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
			{


				// 2) Decide how much to zoom
				float zoomFactor = (this->ev.mouseWheelScroll.delta > 0) ? 0.95f : 1.05f;

				sf::Vector2i windowCenterPx(
					this->window->getSize().x / 2,
					this->window->getSize().y / 2
				);

				// 3) Convert that center to world coords BEFORE zoom
				sf::Vector2f beforeZoomCenterWorld = this->window->mapPixelToCoords(windowCenterPx);

				// 4) Zoom the view
				this->view.zoom(zoomFactor);
				this->window->setView(this->view);

				// 5) Convert the same pixel center to world coords AFTER zoom
				sf::Vector2f afterZoomCenterWorld = this->window->mapPixelToCoords(windowCenterPx);

				// 6) Offset the view so the center stays the same
				sf::Vector2f offset = beforeZoomCenterWorld - afterZoomCenterWorld;
				this->view.move(offset);
				this->window->setView(this->view);
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (this->ev.mouseButton.button == sf::Mouse::Left) {
				sf::Vector2i pixelPos = sf::Mouse::getPosition(*this->window);
				sf::Vector2f worldPos = this->window->mapPixelToCoords(pixelPos);
				//this->mouseCircle.getPosition();
				this->handleTileClick(this->mouseEntity.getPosition());
			}
			break;
		}
	}

}

void Game::update()
{
	deltaTime = clock.restart().asSeconds();

	updateEvents(deltaTime);

	float cameraSpeed = 700.f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->view.move(0.f, -cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->view.move(0.f, cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->view.move(-cameraSpeed * deltaTime, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->view.move(cameraSpeed * deltaTime, 0.f);
	}

	// Update the window's active view
	this->window->setView(this->view);

	// 3) Now that the camera/view is updated, map mouse to world
	sf::Vector2i mousePixelPos = sf::Mouse::getPosition(*this->window);
	sf::Vector2f mouseWorldPos = this->window->mapPixelToCoords(mousePixelPos);

	// 4) Position the circle
	this->mouseEntity.setPosition(mouseWorldPos.x, mouseWorldPos.y);
	this->mouseCircle.setPosition(mouseWorldPos.x - 100, mouseWorldPos.y - 100);
}


void Game::updateCamera(float deltaTime, sf::Vector2f mouse)
{
	float cameraSpeed = 700.f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		this->mouseCircle.setPosition(mouse.x, -cameraSpeed * deltaTime);
		this->view.move(0.f, -cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		this->mouseCircle.setPosition(mouse.x, cameraSpeed * deltaTime);
		this->view.move(0.f, cameraSpeed * deltaTime);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		this->view.move(-cameraSpeed * deltaTime, 0.f);
		this->mouseCircle.setPosition(-cameraSpeed * deltaTime, mouse.y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->view.move(cameraSpeed * deltaTime, 0.f);
		this->mouseCircle.setPosition(cameraSpeed * deltaTime, mouse.y);
	}


	this->window->setView(this->view);
}
void Game::render()
{
	if (this->window) {
		this->window->clear(sf::Color(76, 120, 194));

		this->window->setView(this->view);
		/*
		for (auto& tile : tiles) {
			this->window->draw(tile.tileRect);
			this->window->draw(tile.tileSprite);
		}

		this->window->draw(this->mouseCircle);
		this->window->setView(this->window->getDefaultView());
		this->window->draw(tilesMenu);*/
		this->window->display();
	}
}
