#include "stdafx.h"
#include "Engine.h"


void Engine::input()
{
	while (m_Window.pollEvent(m_inputEvent))
	{
		if ((Keyboard::isKeyPressed(Keyboard::Escape)) || (m_inputEvent.type == Event::Closed))
		{
			m_Window.close();
		}

		if ((m_inputEvent.type == Event::KeyReleased) && (m_inputEvent.key.code == Keyboard::Space))
		{
			pause();
		}

	}
}

