#pragma once
#include <GL/glew.h>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

#include "Shader.hpp"


class Water : public SceneObject
{
public:
	Water();
	~Water();

	void setCamPos(glm::vec3 pos);

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:
	std::vector<glm::vec3> vertexArray_;
	std::vector<unsigned int> indexArray_;
	std::vector<glm::vec2> texArray_;
	std::vector<glm::vec3> normArray_;

	GLuint nmap_, texcube_;

	Shader wShader_;

	int highIntStop = 100000000;
	GLfloat waveTime, waveFreq;
	glm::vec3 camPos;

};
