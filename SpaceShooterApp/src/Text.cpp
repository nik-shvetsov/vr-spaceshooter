#include "Text.hpp"
#include <GL/glew.h>
#include <iostream>
#include <string>


Text::Text(const char *string, float x, float y)
{
	string_ = string;
	x_ = x;
	y_ = y;
}


Text::~Text()
{
}
void Text::privateInit()
{

}
void Text::drawBitmapText(const char *string, float x, float y)
{
	glWindowPos2d(x, y);
	const char *c;
	for (c = string; *c != '\0'; c++)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
	}
} 
void Text::setText(const char *newString)
{
	string_ = newString;
}

void Text::privateRender()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	drawBitmapText(string_, x_, y_);

}

void Text::privateUpdate()
{
	
}