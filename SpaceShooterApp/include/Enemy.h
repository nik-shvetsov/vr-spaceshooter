#pragma once

#include <GL/glew.h>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include <iostream>
#include "Model.hpp"

class Enemy : public SceneObject
{
public:
	Enemy(float rx, Model * model, float zPos, float velocity, float hp);
	//Enemy();
	~Enemy();

	glm::vec3   getPosition();
	float		getRad();
	
	void        reduceHP(float val);
	void        setHP(float val);
	float       getHP();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	float rad_;
	float speed_;
	float hp_;
	float armor_;
	float velocity_;

	float x_;
	float y_;
	int rx_;
	int list_id;

	glm::vec3   position_;
	Model*      model_;
	float       zPos_;
	
	glm::vec3 translateVec_;

};