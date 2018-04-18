#include "stdafx.h"
#include "Engine.h"
#include <iostream>

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	//update positions and velocities
	for (Ball* const &ballIter : ballList) 
	{
		ballIter->update(dtAsSeconds);
	}

	//check and resolve object-object collisions
	for (Ball* const &ballIter1 : ballList)
	{
		for (Ball* const &ballIter2 : ballList)
		{
			if ((ballIter1 != ballIter2) && (isIntersect(ballIter1, ballIter2)))
			{
				resolveObjCollision(ballIter1, ballIter2);
			}
		}
	}

	//check and resolve border collisions
	for (Ball* const &ballIter : ballList)
	{
		checkBorderCollisions(ballIter, m_Window.getSize());
	}

}

bool Engine::isIntersect(Ball* firstBall, Ball* secondBall)
{
	float distanceBetweenBalls = getLength(firstBall->getPosition() - secondBall->getPosition());
	float radiusSum = firstBall->getRadius() + secondBall->getRadius();
	if (distanceBetweenBalls < radiusSum) 
	{
		return true;
	}
	else 
	{
		return false;
	}
}

void Engine::resolveObjCollision(Ball* firstBall, Ball* secondBall)
{
	float distanceBetweenBalls = getLength(firstBall->getPosition() - secondBall->getPosition());
	float radiusSum = firstBall->getRadius() + secondBall->getRadius();

	//push objects back from each other to remove intersection
	pushObjects(firstBall, secondBall, distanceBetweenBalls, radiusSum);

	//calculate unit vectors for a further use
	Vector2<float> normal(secondBall->getPosition() - firstBall->getPosition());
	Vector2<float> unitNormal(normal / radiusSum);
	Vector2<float> unitTangent(unitNormal.y*(-1), unitNormal.x);

	//change velocities
	Vector2<float> firstBallNewVel(calcNewVelocity(firstBall, secondBall, unitNormal, unitTangent, radiusSum));
	Vector2<float> secondBallNewVel(calcNewVelocity(secondBall, firstBall, (-1.0f)*unitNormal, unitTangent, radiusSum));
	firstBall->setVelocity(firstBallNewVel);
	secondBall->setVelocity(secondBallNewVel);
}

void Engine::pushObjects(Ball* firstBall, Ball* secondBall, float distanceBetweenBalls, float radiusSum)
{
	//distance is inversly proportional to objects masses (ballMass/sumOfMasses)*distanceBetweenBalls
	//direction - normal (center to center vector)

	float distToPush = radiusSum - distanceBetweenBalls + 1; //+1 to prevent further intersection due to floating point numbers uncertainty
	float totalMass = firstBall->getRadius() + secondBall->getRadius();
	float firstBallPush = (secondBall->getRadius() / totalMass)*distToPush;
	float secondBallPush = (firstBall->getRadius() / totalMass)*distToPush;

	//calculating direction of push (vector points from 1st center to 2nd center)
	Vector2<float> normal(secondBall->getPosition() - firstBall->getPosition());
	Vector2<float> unitNormal(normal / distanceBetweenBalls);

	//calc actual vectors of push
	Vector2<float> firstBallpushVect(unitNormal*(-1.0f)*firstBallPush); // -1 for the opposite direction
	Vector2<float> secondBallpushVect(unitNormal*secondBallPush);

	//PUSH!
	firstBall->setPosition(firstBall->getPosition() + firstBallpushVect);
	secondBall->setPosition(secondBall->getPosition() + secondBallpushVect);
}

Vector2<float> Engine::calcNewVelocity(Ball* firstBall, Ball* secondBall, Vector2<float> unitNormal, Vector2<float> unitTangent, float radiusSum)
{

	//dot product of the old velocity and normal/tangent vector represent the magnitude of the old velocity in normal/tangent direction
	float initVelInNormal1 = (firstBall->getVelocity().x * unitNormal.x) + (firstBall->getVelocity().y*unitNormal.y);
	float initVelInNormal2 = (secondBall->getVelocity().x * unitNormal.x) + (secondBall->getVelocity().y*unitNormal.y);

	//new velocity in tangent dir = old velocity in tangent direction
	float VelInTangent = (firstBall->getVelocity().x * unitTangent.x) + (firstBall->getVelocity().y*unitTangent.y);

	//find the magnitude of new velocity in normal direction, using formula v1 = (u1(m1-m2)+2*m2*u2)/(m1+m2)
	float newVelInNormal1 = (initVelInNormal1*(firstBall->getRadius() - secondBall->getRadius()) + 2 * secondBall->getRadius()*initVelInNormal2) / (radiusSum);

	//multiply unit vectors by founded magnitudes to get vectors of new velocities in tang/normal coordinates
	//add tang/normal vectors to get velocitiy in global coordinates
	Vector2<float> firstBallNewVel(((unitNormal*newVelInNormal1) + (unitTangent*VelInTangent))*firstBall->getEnergyLostCoef());
	return firstBallNewVel;
}

void Engine::checkBorderCollisions(Ball* ball, Vector2u borders)
{
	//if going right and collided with the the right border
	if ((ball->getPosition().x + ball->getRadius() >= borders.x) and (ball->getVelocity().x > 0))
	{
		//push it back
		Vector2<float> newPosition(borders.x - ball->getRadius(), ball->getPosition().y);
		ball->setPosition(newPosition);

		//change horizontal velocity
		Vector2<float> newVelocity((-1.0f)*ball->getEnergyLostCoef() * ball->getVelocity().x, ball->getVelocity().y);
		ball->setVelocity(newVelocity);
	}

	//or going left and collided with the left border
	else if ((ball->getPosition().x - ball->getRadius() <= 0) and (ball->getVelocity().x < 0))
	{
		//push it back
		Vector2<float> newPosition(ball->getRadius(), ball->getPosition().y);
		ball->setPosition(newPosition);

		//change horizontal velocity
		Vector2<float> newVelocity((-1.0f)*ball->getEnergyLostCoef() * ball->getVelocity().x, ball->getVelocity().y);
		ball->setVelocity(newVelocity);
	}

	//if going down and collided with the bottom
	if ((ball->getPosition().y + ball->getRadius() >= borders.y) and (ball->getVelocity().y > 0))
	{
		//push it back
		Vector2<float> newPosition(ball->getPosition().x, borders.y - ball->getRadius());
		ball->setPosition(newPosition);

		//change vertical velocity
		Vector2<float> newVelocity(ball->getVelocity().x, (-1.0f)*ball->getEnergyLostCoef() * ball->getVelocity().y);
		ball->setVelocity(newVelocity);
	}

	// or going up and collided with the top
	else if ((ball->getPosition().y - ball->getRadius() <= 0) and (ball->getVelocity().y<0))
	{
		//push it back
		Vector2<float> newPosition(ball->getPosition().x, ball->getRadius());
		ball->setPosition(newPosition);

		//change vertical velocity
		Vector2<float> newVelocity(ball->getVelocity().x, (-1.0f)*ball->getEnergyLostCoef() * ball->getVelocity().y);
		ball->setVelocity(newVelocity);
	}

}