/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupConnection();

	setupFontAndText(); // load font 
	setupSprite(); // load texture
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	sendCoords();
	recieveCoords();

	if (m_exitGame)
	{
		m_window.close();
	}
	if (m_window.hasFocus())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			m_player.move(0.f, -3.f);
			m_newPosition += sf::Vector2f(0.f, -3.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_player.move(0.f, 3.f);
			m_newPosition += sf::Vector2f(0.f, 3.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_player.move(-3.f, 0.f);
			m_newPosition += sf::Vector2f(-3.f, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_player.move(3.f, 0.f);
			m_newPosition += sf::Vector2f(3.f, 0.f);
		}
	}
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::White);
	m_window.draw(m_player);
	m_window.draw(m_otherPlayer);
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	/*if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);*/

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	m_player.setSize(sf::Vector2f(50.f, 50.f));
	m_player.setPosition(sf::Vector2f(50.f, 50.f));
	m_player.setFillColor(sf::Color::Cyan);
	m_otherPlayer.setSize(sf::Vector2f(50.f, 50.f));
	m_otherPlayer.setPosition(sf::Vector2f(50.f, 50.f));
	m_otherPlayer.setFillColor(sf::Color::Magenta);

	m_newPosition = m_player.getPosition();
}

void Game::setupConnection()
{
	int connectNum = 0;

	DEBUG_MSG("1 - HOST\n 2 - PEER\n");
	do {
		std::cin >> connectNum;
	} while (connectNum != 1 && connectNum != 2);

	if (connectNum == 1)
	{
		m_connector.listenOnPort();
	}
	if (connectNum == 2)
	{
		std::string listeningPort;
		DEBUG_MSG("IP ADDRESS: ");
		std::cin >> listeningPort;
		m_connector.connectToAddress(listeningPort);
	}
}

void Game::sendCoords()
{
	sf::Packet send;
	//DEBUG_MSG("x : " + std::to_string(m_newPosition.x) + " y : " + std::to_string(m_newPosition.y));
	send << m_newPosition.x << m_newPosition.y;
	m_connector.trySendPacket(send);
}

void Game::recieveCoords()
{
	m_otherPlayer.setPosition(m_connector.tryRecievePacket());
}
