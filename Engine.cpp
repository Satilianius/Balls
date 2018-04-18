#include "stdafx.h"
#include "Engine.h"



Engine::Engine()
	//: m_FirstBall(nullptr)
	//, m_SecondBall(nullptr)
{
	m_Window.create(VideoMode(1000, 800), "Ball"),
	m_Window.setFramerateLimit(60);
}

void Engine::start()
{
	m_gravity = 0;	
	m_ballNumber = 10;

	for (int ballCount = 1; ballCount <= m_ballNumber; ballCount++)
	{
		ballList.push_back(new Ball(Color::Black, randInt(10, 70), 0.9f, Vector2<float>(randInt(50, 750), randInt(50, 550)), Vector2<float>(randInt(-300, 300), randInt(-300, 300)), Vector2<float>(0, 0 + m_gravity)));
	}

	Clock frameTimer; //launch timer for each frame
	Time frameTime; //time elapsed from previous frame
	m_paused = false;

	while (m_Window.isOpen())
	{

		frameTime = frameTimer.restart();
		float elapsedAsSeconds = frameTime.asSeconds();
		input();
		if (!m_paused)
		{
			update(elapsedAsSeconds);
		}
		draw();
	}
}

int Engine::randInt(int from, int to)
{
	return rand() % (to - from) + from;
}

float Engine::getLength(Vector2<float> vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

void Engine::pause() 
{
	m_paused = !m_paused;
}

Engine::~Engine()
{
	for (Ball* ballCount : ballList)
	{
		delete ballCount;
	}
	ballList.clear();
}
