// Main.cpp: определяет точку входа для консольного приложения.

#include "stdafx.h"
#include <iostream>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Clock.hpp>
#include "Main.h"
#include "Engine.h"
#include "Ball.h"
#include <cmath>

using namespace sf;

int main()
{
	Engine engine;

	engine.start();

	return 0;
}