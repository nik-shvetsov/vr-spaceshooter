
#include "Enemy.h"
#include <glm/gtc/matrix_transform.hpp>
#include <time.h>

Enemy::Enemy(float rx, Model* model, float zPos, float velocity, float hp)
{
	rx_ = rx;
	model_ = model;
	zPos_ = zPos;
	velocity_ = velocity;

	rad_ = 5.0f;
	hp_ = hp; //100.0f;
	x_ = 1.0f;

	privateInit();
}

//Enemy::Enemy()
//{
//
//}

Enemy::~Enemy()
{

}

void Enemy::privateInit()
{
	float start = rand() % 320;
	position_ = glm::vec3(start, 150.0f, zPos_);
	matrix_ = glm::translate(glm::mat4(), glm::vec3(position_[0], position_[1], position_[2]));
}

void Enemy::privateRender()
{
	
	srand(time(NULL)); //init seed using time

	float rx = rand() % rx_;
	x_ = glm::sin(rx);
	float newX = glm::sin(x_);
	glm::vec3 newMovement;

	if (position_[0] > 5.0f && position_[0] < 305.0f)
	{
		newMovement = glm::vec3(newX, 0.0f, velocity_);
		matrix_ = glm::translate(matrix_, newMovement);
		position_ += newMovement;
	}
	else if (position_[0] <= 5.0f)
	{
		newMovement = glm::vec3(1.0f, 0.0f, velocity_);
		matrix_ = glm::translate(matrix_, newMovement);
		position_ += newMovement;
	}
	else if (position_[0] >= 305.0f)
	{
		newMovement = glm::vec3(-1.0f, 0.0f, velocity_);
		matrix_ = glm::translate(matrix_, newMovement);
		position_ += newMovement;
	}

	model_->Render();
	
}

void Enemy::privateUpdate()
{

}

float Enemy::getRad()
{
	return rad_;
}

glm::vec3 Enemy::getPosition()
{
	return position_;
}

float Enemy::getHP()
{
	return hp_;
}

void Enemy::reduceHP(float val)
{
	hp_ -= val;
}

void Enemy::setHP(float val)
{
	hp_ = val;
}
