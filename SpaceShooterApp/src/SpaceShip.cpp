#include "SpaceShip.hpp"
#include "SOIL.h"
#include "Shader.hpp"
#include <iostream>

SpaceShip::SpaceShip(float x, float y, float z, float hp, Model *model)
{
	position_ = glm::vec3(x, y, z);
	hp_ = hp;
	score_ = 0;
	rad_ = 5.0f;
	model_ = model;
	velocity_ = -0.5f;
}

//SpaceShip::SpaceShip()
//{
//}

SpaceShip::~SpaceShip()
{
}

void SpaceShip::privateInit()
{
	matrix_ = glm::translate(glm::mat4(), glm::vec3(position_[0], position_[1], position_[2]));
}


void SpaceShip::privateRender()
{

	glm::vec3 translateVec = glm::vec3(0.0f, 0.0f, velocity_);
	matrix_ = glm::translate(matrix_, translateVec);
	position_ += translateVec;
	model_->Render();
	
    /*
	//--activate fog
    glEnable(GL_FOG);
	// specify the equation to be used
	glFogi(GL_FOG_MODE, GL_LINEAR);
	// specify parameters
	glFogf(GL_FOG_START, 200.0f);
	glFogf(GL_FOG_END, 800.0f);
	// per-pixel fog calculations
	glHint(GL_FOG_HINT, GL_NICEST);
	//--end of fog
	
	glEnable(GL_TEXTURE_2D);
	// Activate texture object
	glBindTexture(GL_TEXTURE_2D, tex);
	
	//rendering of the spaceship

	//for transparency on texture
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(1.0, 1.0, 1.0, 1.0);

	glColor3f(1.0f, 0.0f, 0.0f);
	
	float x_place = 8.0f;
	float z_place = -47.0f;
	glBegin(GL_QUADS);
    // Near Face
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-x_place, 2.0f, z_place);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(x_place, 2.0f, z_place);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(x_place, 16.0f, z_place);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-x_place, 16.0f, z_place);
    glEnd();

	//glDisable(GL_TEXTURE_2D);

  //moving simulation
  //translateVec_[2] += 0.0003;
  //matrix_ = glm::translate(glm::mat4(), translateVec_); //for translate function
	shdr_.disable(); //shader test
	*/
}

void SpaceShip::privateUpdate()
{

}

void SpaceShip::setVelocity(float vel)
{
	velocity_ = vel;
}

void SpaceShip::setCamPos(glm::vec3 vec)
{
	camPos_ = vec;
}

void SpaceShip::moveRight()
{
	if (position_[0] < 300.0f)
	{
		glm::vec3 translateVec = glm::vec3(2.0f, 0.0f, 0.0f);
		matrix_ = glm::translate(matrix_, translateVec);
		position_ += translateVec;
	}

}

void SpaceShip::moveLeft()
{
	if (position_[0] > 10.0f)
	{
		glm::vec3 translateVec = glm::vec3(-2.0f, 0.0f, 0.0f);
		matrix_ = glm::translate(matrix_, translateVec);
		position_ += translateVec;
	}
}

glm::vec3 SpaceShip::getPosition()
{
	return position_;
}

float SpaceShip::getHP()
{
	return hp_;
}

void SpaceShip::reduceHP(float val)
{
	hp_ -= val;
}

void SpaceShip::increaseHP(float val)
{
	hp_ += val;
}

void SpaceShip::setHP(float val)
{
	hp_ = val;
}

float SpaceShip::getRad()
{
	return rad_;
}

int SpaceShip::getScore()
{
	return score_;
}

void SpaceShip::addScore(int score)
{
	score_ += score;
}

void SpaceShip::spendScore(int score)
{
	score_ -= score;
}