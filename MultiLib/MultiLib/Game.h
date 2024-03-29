/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>
#include <SFML/Graphics.hpp>
#include "server.hpp"

class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();

private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	
	void setupFontAndText();
	void setupSprite();

	void setupConnection();

	void sendCoords();
	void recieveCoords();

	sf::RenderWindow m_window; // main SFML window

	sf::RectangleShape m_player;
	sf::RectangleShape m_otherPlayer;

	sf::Vector2f m_newPosition;

	bool m_exitGame; // control exiting game

	ServerConnecter m_connector;
};

#endif // !GAME_HPP

