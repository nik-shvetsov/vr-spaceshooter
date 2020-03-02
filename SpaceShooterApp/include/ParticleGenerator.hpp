#pragma once

#include <windows.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"
#include "glm/glm.hpp"

class ParticleGenerator : public SceneObject {
public:
	ParticleGenerator(int mode);
	~ParticleGenerator();

protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();

private:

	virtual void up();
	virtual void down();

	int mode_;

	GLuint particleTexture_;

	#define	MAX_PARTICLES	1000		// Number Of Particles To Create

	typedef struct						// Create A Structure For Particle
	{
		bool	active;					// Active (Yes/No)
		float	life;					// Particle Life
		float	fade;					// Fade Speed
		float	r;						// Red Value
		float	g;						// Green Value
		float	b;						// Blue Value
		float	x;						// X Position
		float	y;						// Y Position
		float	z;						// Z Position
		float	xi;						// X Direction
		float	yi;						// Y Direction
		float	zi;						// Z Direction
		float	xg;						// X Gravity
		float	yg;						// Y Gravity
		float	zg;						// Z Gravity
	}
	particles;							// Particles Structure

	particles particle[MAX_PARTICLES];	// Particle Array (Room For Particle Info)

	GLfloat colors[12][3];		// Rainbow Of Colors
};

