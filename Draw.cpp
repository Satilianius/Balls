#include "stdafx.h"
#include "Engine.h"

void Engine::draw()
{
	// Clear All
	m_Window.clear(Color::White);

	// Draw background
	//m_Window.draw(m_BackgroundSprite);
	for (Ball* ballIter : ballList)
	{
		m_Window.draw(ballIter->getShape());
	}

	m_Window.display();
}