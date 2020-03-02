#pragma once
#include "Skybox.hpp"
#include "SOIL.h"
#include <iostream>

Skybox::Skybox()
{
	size = 512.0f;
	position_ = glm::vec3(0.0f, 0.0f, 0.0f);
}

Skybox::~Skybox()
{

}

void Skybox::privateInit()
{
	list_id = glGenLists(1);

	glNewList(list_id, GL_COMPILE);
	glBegin(GL_QUADS); //East
	glNormal3f(1.0f, 0.0f, 0.0f);
	glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);
	glTexCoord3f(1.0f, 1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);
	glTexCoord3f(1.0f, 0.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glEnd();

	glBegin(GL_QUADS); //South
	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord3f(-1.0f, 1.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);
	glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);
	glTexCoord3f(1.0f, -1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glEnd();

	glBegin(GL_QUADS); //West
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glTexCoord3f(0.0f, 1.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);
	glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);
	glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glTexCoord3f(0.0f, 0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glEnd();

	glBegin(GL_QUADS); //North
	glNormal3f(0.0f, 0.0f, -1.0f);
	glTexCoord3f(1.0f, 1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);
	glTexCoord3f(0.0f, 1.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);
	glTexCoord3f(0.0f, 0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glTexCoord3f(1.0f, 0.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glEnd();

	glBegin(GL_QUADS); //Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glTexCoord3f(0.0f, 1.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] - size);
	glTexCoord3f(1.0f, 1.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] - size);
	glTexCoord3f(1.0f, 1.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] + size, position_[2] + size);
	glTexCoord3f(0.0f, 1.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] + size, position_[2] + size);
	glEnd();

	glBegin(GL_QUADS); //Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glTexCoord3f(0.0f, 0.0f, 1.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] + size);
	glTexCoord3f(1.0f, 0.0f, 1.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] + size);
	glTexCoord3f(1.0f, 0.0f, 0.0f); glVertex3f(position_[0] + size, position_[1] - size, position_[2] - size);
	glTexCoord3f(0.0f, 0.0f, 0.0f); glVertex3f(position_[0] - size, position_[1] - size, position_[2] - size);
	glEnd();
	glEndList();

	//=============================
	tex = SOIL_load_OGL_cubemap
	(
		"textures/skybox/skybox_west.bmp",
		"textures/skybox/skybox_east.bmp",
		"textures/skybox/skybox_up.bmp",
		"textures/skybox/skybox_down.bmp",
		"textures/skybox/skybox_south.bmp",
		"textures/skybox/skybox_north.bmp",
		SOIL_LOAD_RGB,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS //0
	);

	if (tex == 0)
	{
		std::cout << "SOIL loading error in skybox:" << SOIL_last_result() << std::endl;
	}

	//glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	//Enviroment
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	//======================================
	skShader_.initShaders("shaders/skybox");
	skShader_.enable();
	glUniform1i(glGetUniformLocation(skShader_.getProg(), "skybox"), 0);
	skShader_.disable();

	//matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 100.0f, -300.0f));
}

void Skybox::privateRender()
{
	skShader_.enable();
	glEnable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex);
	glCallList(list_id);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_CUBE_MAP);
	skShader_.disable();
}

void Skybox::privateUpdate()
{
	//glm::vec3 translateVector (0.0f, 0.0f, -0.9f);
	//position_ = gm->getPlayer()->getPosition();
	//matrix_ = glm::translate(matrix_, translateVector);

}



