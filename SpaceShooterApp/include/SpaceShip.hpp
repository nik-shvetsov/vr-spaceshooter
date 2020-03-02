#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Shader.hpp"
#include "Model.hpp"

class SpaceShip : public SceneObject
{
	public:
		//SpaceShip();
		SpaceShip(float x, float y, float z, float hitpoints, Model *model);
		~SpaceShip();
		void moveRight();
		void moveLeft();
		//void moveUp();
		//void moveDown();

		glm::vec3 getPosition();

		void reduceHP(float);
		void increaseHP(float);
		void setHP(float);
		float getHP();


		float getRad();
		void setCamPos(glm::vec3 vec);
		void setVelocity(float vel);

		int getScore();
		void addScore(int);
		void spendScore(int);

  protected:
		void privateInit();
		void privateRender();
		void privateUpdate();

	private:
	float velocity_;
    float hp_;
    float armor_;
	float rad_;
	int score_;
	
	int list_id;

	glm::vec3 position_;
	Shader sShader_;
	Model *model_;
	GLuint texcube_;
	glm::vec3 camPos_;

	//glm::vec3 translateVec_;
    
};

