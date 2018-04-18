#include "stdafx.h"
#include "Ball.h"

using namespace sf;

Ball::Ball()
{
};

Ball::Ball(Color initialColor,
			float initialRadius, 
			float energyLostCoef, 
			Vector2<float> initialPosition, 
			Vector2<float> initialVelocity, 
			Vector2<float> initialAcceleration)
{

	this->setColor(initialColor);
	this->setRadius(initialRadius);
	this->setPosition(initialPosition);
	this->setVelocity(initialVelocity);
	this->setAcceleration(initialAcceleration);
	this->setEnergyLostCoef(energyLostCoef);

	ballShape.setOrigin(initialRadius, initialRadius);
}

void Ball::setColor(Color newColor) 
{
	this->color = newColor;
}

void Ball::setRadius(float newRadius)
{
	this->radius = newRadius;
}

void Ball::setPosition(Vector2<float> newPosition)
{
	this->position = newPosition;
}

void Ball::setVelocity(Vector2<float> newVelocity)
{
	this->velocity = newVelocity;
}

void Ball::setAcceleration(Vector2<float> newAcceleration)
{
	this->acceleration = newAcceleration;
}

void Ball::setEnergyLostCoef(float newEnergyLostCoef)
{
	this->energyLostCoef = newEnergyLostCoef;
}

float Ball::getRadius()
{
	return this->radius;
}

Color Ball::getColor()
{
	return this->color;
}

Vector2<float> Ball::getPosition()
{
	return position;
}

Vector2<float> Ball::getVelocity()
{
	return velocity;
}

Vector2<float> Ball::getAcceleration()
{
	return acceleration;
}

CircleShape Ball::getShape()
{
	ballShape.setFillColor(color);
	ballShape.setRadius(radius);
	ballShape.setPosition(position);
	return ballShape;
}

float Ball::getEnergyLostCoef()
{
	return this->energyLostCoef;
}

void Ball::move(float time)
{
	position = (position) + (velocity * time) + (acceleration * (time * time / 2));
	velocity = (velocity) + (acceleration * time);

	ballShape.setPosition(position);
}

void Ball::update(float time) 
{
	move(time);
	//checkBorderCollisions();
}

Ball::~Ball()
{
}
