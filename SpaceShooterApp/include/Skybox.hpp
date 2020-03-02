#pragma once

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "SceneObject.hpp"
#include "Shader.hpp"

//class GameManager;
class Skybox : public SceneObject
{
public:
	Skybox();
	~Skybox();

protected:
	void privateInit();
	void privateRender();
	void privateUpdate();

private:
	GLuint tex;
	Shader skShader_;

	int list_id;

	float size;

	glm::vec3 position_;
};


