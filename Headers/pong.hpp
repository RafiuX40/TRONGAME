#ifndef pong_hpp
#define pong_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "sticks.hpp"
#include "ball.hpp"
#include "collision.hpp"
#include "score.hpp"
#include "GameOver.hpp"

using namespace sf;
int W = 1280, H = 720;

void pong() {
	// Sound Effects
	SoundBuffer buf_0, buf_1, buf_2;
	buf_0.loadFromFile("Assets/paddle.wav");
	buf_1.loadFromFile("Assets/wall.wav");
	buf_2.loadFromFile("Assets/score.wav");
	Sound paddle, wall, score;
	paddle.setBuffer(buf_0);
	wall.setBuffer(buf_1);
	score.setBuffer(buf_2);

	// Window
	RenderWindow window(VideoMode(W, H), "Pong!");
	window.setFramerateLimit(500);
	window.setKeyRepeatEnabled(true);
	window.setVerticalSyncEnabled(false);

	auto image = sf::Image{};
    if (!image.loadFromFile("Assets/pong_logo.jfif"))
    {
    // Error handling...
    }

    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


	// Initilaizing Paddles
	Paddle paddles[2];
	paddles[0].pos = Vector2f((20), (305));
	paddles[1].pos = Vector2f((W-20-20), (305));
	paddles[0].initPaddles("Assets/stick_1.png");
	paddles[1].initPaddles("Assets/stick_2.png");
	paddles[0].speed = 1.f;
	paddles[1].speed = 1.f;
	paddles[0].dir = 2;
	paddles[1].dir = 2;
	paddles[0].score = 0;
	paddles[1].score = 0;

	// Initializing Ball
	Ball ball;
	ball.pos = Vector2f((626), (346));
	ball.initBall("Assets/ball.png");
	ball.speed = Vector2f(0,0);

	// Score Text
	Texture scText;
	Sprite scoreSprite;
	scText.loadFromFile("Assets/score.png");
	scoreSprite.setTexture(scText);
	scoreSprite.setPosition((546), (35));
	createNumberSprites(window);

	while (window.isOpen() && !Keyboard::isKeyPressed(Keyboard::BackSpace))
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape)) window.close();
		}

		window.clear(Color::Black);

		// Game Input Logic
		if (Keyboard::isKeyPressed(Keyboard::W)) paddles[0].dir = 0;
		else if (Keyboard::isKeyPressed(Keyboard::S)) paddles[0].dir = 1;
		else paddles[0].dir = 2;

		if (Keyboard::isKeyPressed(Keyboard::Up)) paddles[1].dir = 0;
		else if (Keyboard::isKeyPressed(Keyboard::Down)) paddles[1].dir = 1;
		else paddles[1].dir = 2;

			// Start The Game By Pressing "SPACE"
		if (Keyboard::isKeyPressed(Keyboard::Space))
		{
			whoStartsTheGame(paddles[0], paddles[1], ball);
		}

			// Check Collision
		Collision(ball, paddles[1],paddles[0],paddle,score, paddles[0].score, paddles[1].score);

		paddles[0].movePaddles(ball); 
		paddles[1].movePaddles(ball);
		ball.moveBall();
		gameOver(ball, paddles[0], paddles[1]);
		updateScore(paddles[0].score, paddles[1].score,window);
		// Draw
		paddles[0].drawPaddles(window);
		paddles[1].drawPaddles(window);
		ball.drawBall(window);
		window.draw(scoreSprite);
		
		// Display
		window.display();
	}
}

#endif