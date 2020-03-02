#include "Water.hpp"
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "glm/gtc/type_ptr.hpp"
#include <GL/freeglut.h>
#include "SOIL.h"
#include <iostream>

Water::Water()
{
	waveTime = 0.0;
	waveFreq = 0.01;

}
Water::~Water() {

}

void Water::privateInit()
{
	wShader_.initShaders("shaders/water");

	nmap_ = SOIL_load_OGL_texture("images/normalmap.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);
	
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, nmap_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// Set environment mode
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	texcube_ = SOIL_load_OGL_cubemap(
		"textures/skybox/skybox_west.bmp",
		"textures/skybox/skybox_east.bmp",
		"textures/skybox/skybox_up.bmp",
		"textures/skybox/skybox_down.bmp",
		"textures/skybox/skybox_south.bmp",
		"textures/skybox/skybox_north.bmp",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		0
	);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texcube_);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	wShader_.enable();
	glUniform1i(glGetUniformLocation(wShader_.getProg(), "normalMap"), 0);
	glUniform1i(glGetUniformLocation(wShader_.getProg(), "cubeMap"), 1);
	wShader_.disable();

	float x = 32.0f;
	float z = 512.0f;
	// Create vertex arrays
	for (int j = 0; j < z; j++)
	{
		for (int i = 0; i < x; i++)
		{
			texArray_.push_back(glm::vec2(((float)i / (x - 1))*10.0, ((float)j / (z - 1))*150.0));
			vertexArray_.push_back(glm::vec3(i * 10, 2, j * 10));
			normArray_.push_back(glm::vec3(0.0, 1.0, 0.0));
		}
	}

	for (int j = 0; j<z - 1; j++) 
	{
		for (int i = 0; i<x; i++) 
		{
			indexArray_.push_back(i + j*x);
			indexArray_.push_back(i + x + j*x);
		}
		indexArray_.push_back(highIntStop);
	}
	glPrimitiveRestartIndex(highIntStop);
}

void Water::privateRender()
{
	wShader_.enable();
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, nmap_);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texcube_);

	glUniform4f(glGetUniformLocation(wShader_.getProg(), "camPos"), camPos[0], camPos[1], camPos[2], 0.0f);
	glUniform1f(glGetUniformLocation(wShader_.getProg(), "waveTime"), waveTime);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glNormalPointer(GL_FLOAT, 0, &normArray_.front());
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_.front());
	glTexCoordPointer(2, GL_FLOAT, 0, &texArray_.front());
	glEnable(GL_PRIMITIVE_RESTART);
	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_.front());
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	waveTime += waveFreq;
	wShader_.disable();
}

void Water::privateUpdate()
{
	waveTime += waveFreq;
}
void Water::setCamPos(glm::vec3 pos) {
	camPos = pos;
}