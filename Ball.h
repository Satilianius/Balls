#pragma once
#ifndef __BALL_H_INCLUDED__
#define __BALL_H_INCLUDED__

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
using namespace sf;

	class Ball
	{
	private:
		Color color;
		float radius;
		//float mass;
		Vector2<float> position;
		Vector2<float> velocity;
		Vector2<float> acceleration;
		CircleShape ballShape;
		float energyLostCoef;

	public:
		Ball();
		Ball(Color initialColor, float initialRadius, float energyLostCoef, Vector2<float> initialPosition,Vector2<float> initialVelocity, Vector2<float> initialAcceleration);
		
		void setColor(Color newColor);
		void setRadius(float newRadius);
		void setPosition(Vector2<float> newPosition);
		void setVelocity(Vector2<float> newVelocity);
		void setAcceleration(Vector2<float> newAcceleration);
		void setEnergyLostCoef(float newEnergyLostCoef);
		//void setMass(float newMass);

		float getRadius();
		Color getColor();
		//float getMass();
		Vector2<float> getPosition();
		Vector2<float> getVelocity();
		Vector2<float> getAcceleration();
		CircleShape getShape();
		float getEnergyLostCoef();

		//void checkBorderCollisions(Vector2u borders);
		void move(float time);
		void update(float time);
		~Ball();
	};
#endif //__BALL_H_INCLUDED__

