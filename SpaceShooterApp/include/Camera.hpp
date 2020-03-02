#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>
#include "SceneObject.hpp"
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Camera : public SceneObject
{
	public:
		Camera();
		~Camera();

    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveBackward();
    void moveForward();

	void followSpaceship(float x, float y, float z);
    
  protected:
		void privateInit();
		void privateRender();
		void privateUpdate();

	private:
		float x_;
		float y_;
		float z_;
  
};


