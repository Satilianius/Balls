#pragma once
#include <SFML/Graphics.hpp>
#include "Ball.h"
#include <iostream>
#include <list>
#include <stdlib.h>

using namespace sf;

class Engine
{
public:
	Engine();

	void start();

	void pause();

	~Engine();

private:

	std::list<Ball*> ballList;
	RenderWindow m_Window;
	Event m_inputEvent;
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	float m_gravity;
	int m_ballNumber;
	bool m_paused;

	int randInt(int from, int to);
	float getLength(Vector2<float> vector);

	void input();
	void update(float elapsedAsSeconds);
	void draw();

	bool isIntersect(Ball* firstBall, Ball* secondBall);
	void resolveObjCollision(Ball* firstBall, Ball* secondBall);
	void pushObjects(Ball* firstBall, Ball* secondBall, float distanceBetweenBalls, float radiusSum);
	Vector2<float> calcNewVelocity(Ball* firstBall, Ball* secondBall, Vector2<float> unitNormal, Vector2<float> unitTangent, float radiusSum);
	void checkBorderCollisions(Ball* ball, Vector2u borders);


};

