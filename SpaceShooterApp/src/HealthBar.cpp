#include "HealthBar.hpp"
#include <iostream>

HealthBar::HealthBar()
{
    privateInit();
}
HealthBar::~HealthBar() {}

void HealthBar::privateInit()
{
    glBegin(GL_QUADS);
	
	if (hp_ > 50.0f)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
	}
	else glColor3f(1.0f, 0.0f, 0.0f);

      glVertex3f(position_[0]-15.0f, position_[1]+7.0f, position_[2]); 
      glVertex3f(position_[0]-14.0f + hp_/3.0, position_[1]+7.0f, position_[2]);
	  
      glVertex3f(position_[0]-14.0f + hp_/3.0, position_[1]+10.0f, position_[2]); 
      glVertex3f(position_[0]-15.0f, position_[1] + 10.0f, position_[2]); 
    glEnd();
}

void HealthBar::privateRender()
{
    //glCallList(list_id);

	/*GLenum err = glGetError();
	if (err != GL_NO_ERROR)
		std::cout << "Healthbar error: " << gluErrorString(err) << std::endl;
	std::cout.flush();*/
}

void HealthBar::privateUpdate() {}

void HealthBar::setPos(glm::vec3 position)
{
    position_ = position;
}

void HealthBar::setHP(float val)
{
	hp_ = val;
    privateInit();
}

void HealthBar::reduceHP(float val)
{
    hp_ -= val;
}
