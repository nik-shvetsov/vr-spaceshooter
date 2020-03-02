#include "BattleField.hpp"
#include "SOIL.h"
#include <iostream>

BattleField::BattleField()
{
}

BattleField::~BattleField()
{
}

void BattleField::privateInit()
{
	bfShader_.initShaders("shaders/bf");
	terrain_ = SOIL_load_OGL_texture("images/terrain.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, terrain_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	grass_ = SOIL_load_OGL_texture("images/grass.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, grass_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	heightMap_ = SOIL_load_OGL_texture("images/heights.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, heightMap_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	bfShader_.enable();
	glUniform1i(glGetUniformLocation(bfShader_.getProg(), "tex0"), 0);
	glUniform1i(glGetUniformLocation(bfShader_.getProg(), "tex1"), 1);
	glUniform1i(glGetUniformLocation(bfShader_.getProg(), "heightMap"), 2);
	bfShader_.disable();

	float x = 32.0f;
	float z = 512.0f;
	// Create vertex arrays
	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < x; j++)
		{
			float _x = 1.0f / (x - 1.0f) * j;
			float _y = 1.0f / (x - 1.0f) * (i % int(x));

			texCoordArray_.push_back(glm::vec2(_x, _y));
			vertexArray_.push_back(glm::vec3(j*10.0f, 0, i*10.0f));
			normalArray_.push_back(glm::vec3(0.0, 1.0, 0.0));
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

void BattleField::privateRender()
{
	// Render the battlefield
	bfShader_.enable();
	glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, terrain_);
	glActiveTexture(GL_TEXTURE1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass_);
	glActiveTexture(GL_TEXTURE2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, heightMap_);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	glNormalPointer(GL_FLOAT, 0, &normalArray_.front());
	glVertexPointer(3, GL_FLOAT, 0, &vertexArray_.front());
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoordArray_.front());
	glEnable(GL_PRIMITIVE_RESTART);
	glDrawElements(GL_QUAD_STRIP, indexArray_.size(), GL_UNSIGNED_INT, &indexArray_.front());
	glDisable(GL_PRIMITIVE_RESTART);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glActiveTexture(GL_TEXTURE2);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE1);
	glDisable(GL_TEXTURE_2D);
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
	bfShader_.disable();
}

void BattleField::privateUpdate()
{
}