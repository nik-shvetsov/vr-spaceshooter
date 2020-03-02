#pragma once

#include <windows.h>
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include "SceneObject.hpp"

class Text : public SceneObject
{
public:
	Text(const char *string, float x, float y);
	~Text();
	
	
	 void drawBitmapText(const char *string, float x, float y);
protected:
	virtual void privateInit();
	virtual void privateRender();
	virtual void privateUpdate();
	void setText(const char *newString);
	
	
private:
	const char *string_;
	float x_;
	float y_;
};



