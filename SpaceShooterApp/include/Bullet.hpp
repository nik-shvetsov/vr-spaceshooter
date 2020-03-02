#pragma once
#include <GL/glew.h>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include <iostream>
#include "Model.hpp"

class Bullet : public SceneObject
{
public:
	Bullet(float rad, Model* model);
	~Bullet();

	float getRad();
	glm::vec3 getPos();
	//glm::vec3 getDir();
	void setDir(glm::vec3 dir);
	void setPos(glm::vec3 dir);

	enum weapons {minigun, rockets};

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	int list_id;
	float rad_;
	float velocity_;
	float damage_;

	glm::vec3 position_;
	glm::vec3 direction_;
	Model* model_;
};


