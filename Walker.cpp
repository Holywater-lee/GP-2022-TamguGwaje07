#include "Walker.h"

const int WIDTH = 600;
const int HEIGHT = 400;

Walker::Walker(float x, float y) : location(x, y), velocity(0, 0), acceleration(0, 0), r(16), maxForce(0.25), maxSpeed(4)
{
	// commit test
	// �ѱ��׽�Ʈ
}

void Walker::update()
{
	velocity += acceleration;
	velocity.limit(maxSpeed);
	location += velocity;
	acceleration *= 0;

	heading = atan2(velocity.getY(), velocity.getX());
}

void Walker::seek(Vector2D target)
{
	Vector2D desiredForce = target - location;
	//desiredForce.normalize();
	//desiredForce *= maxSpeed;
	desiredForce = desiredForce.Normalized() * maxSpeed - velocity;
	//desiredForce -= velocity;
	
	desiredForce.limit(maxForce);
	applyForce(desiredForce);
}

void Walker::applyForce(Vector2D force)
{
	acceleration += force;
}

void Walker::edges()
{
	float buffer = r * 2;
	if (location.getX() > WIDTH + buffer) location.setX(-buffer);
	else if (location.getX() < -buffer) location.setX(WIDTH + buffer);
	if (location.getY() > HEIGHT + buffer) location.setY(-buffer);
	else if (location.getY() < -buffer) location.setY(HEIGHT + buffer);
}

void Walker::draw(SDL_Renderer* renderer)
{
	Vector2D vertex0 = Vector2D(r, 0).RotTranslate(heading, location.getX(), location.getY());
	Vector2D vertex1 = Vector2D(-r, -r / 2).RotTranslate(heading, location.getX(), location.getY());
	Vector2D vertex2 = Vector2D(-r, r / 2).RotTranslate(heading, location.getX(), location.getY());

	filledTrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 125, 125, 125, 255);
	aatrigonRGBA(renderer, vertex0.getX(), vertex0.getY(), vertex1.getX(), vertex1.getY(), vertex2.getX(), vertex2.getY(), 255, 255, 255, 255);
}
