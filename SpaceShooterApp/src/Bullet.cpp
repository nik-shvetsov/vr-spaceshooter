#include "Bullet.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "SOIL.h"

Bullet::Bullet(float rad, Model* model)
{
	rad_ = rad;
	model_ = model;
}

Bullet::~Bullet()
{
}

void Bullet::privateInit()
{
	float size = rad_;
	list_id = glGenLists(1);

	glNewList(list_id, GL_COMPILE);
	glColor3f(1, 1, 0);
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);

	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);

	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);

	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);

	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);

	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glColor4f(1, 1, 1, 1);
	glEnd();
	glEndList();

	matrix_ = glm::translate(glm::mat4(), glm::vec3(position_[0], position_[1], position_[2]));
}

void Bullet::privateRender()
{
	matrix_ = glm::translate(matrix_, direction_);
	glCallList(list_id);
	position_ += direction_;
	model_->Render();
}

void Bullet::privateUpdate()
{

}

void Bullet::setPos(glm::vec3 pos)
{
	position_ = pos;
	privateInit();
}

void Bullet::setDir(glm::vec3 dir)
{
	direction_ = dir;
	privateInit();
}

float Bullet::getRad()
{
	return rad_;
}

glm::vec3 Bullet::getPos()
{
	return position_;
}