#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <glm/glm.hpp>
#include "SceneObject.hpp"
#include "Shader.hpp"
#include <memory>


class BattleField : public SceneObject
{
public:
	BattleField();
	~BattleField();

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:
	std::vector<glm::vec3> vertexArray_;
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2> texCoordArray_;
	std::vector<glm::vec3> normalArray_;
	
	Shader bfShader_;
	GLuint terrain_, grass_, heightMap_;

	int highIntStop = 100000000;
};