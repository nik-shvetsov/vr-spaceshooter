#include <GL/glew.h>
#include <windows.h>
#include <GL/freeglut.h>  
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include "Input.hpp"
#include "FpsCounter.hpp"
#include "GameManager.hpp"
#include "glm/glm.hpp"

#include <iostream>

std::shared_ptr<GameManager> gm;
siut::FpsCounter counter;

int window;

bool keyPressed[30];
int mousePosX, mousePosY; 
float moveX, moveY;

void init()
{
  glEnable(GL_PRIMITIVE_RESTART);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  //check versions

  char *buff = (char*)glGetString(GL_VERSION);
  std::cout << buff << std::endl;

  buff = (char*)glGetString(GL_VENDOR);
  std::cout << buff << std::endl;
  buff = (char*)glGetString(GL_RENDERER);
  std::cout << buff;

  //--

  auto error = glewInit();
  //std::cout << error << std::endl;

  counter.start();



  gm.reset(new GameManager());
  gm->init();

  for(int i=0; i<30; i++)
    keyPressed[i]=false;
}

void drawText(const char *text, int length, int x, int y, glm::vec3 color, int font)
{
	glColor3f(color[0],color[1],color[2]);
	glMatrixMode(GL_PROJECTION);
	double matrix[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 700, 0, 700, -5, 5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glLoadIdentity();
	glRasterPos2i(x, y);
	for (int i = 0; i < length; i++)
	{
		//glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]);

		if (font == 1)
		{
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);
		}
		else
		{
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, (int)text[i]);
		}
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}

void display()
{
	setlocale(0, "");
	counter.frame();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	////Error check
	//GLenum err = glGetError();
	//if (err != GL_NO_ERROR)
	//{
	//	std::cout << "OpenGL error dp: " << gluErrorString(err) << std::endl;
	//}
	//std::cout.flush();
	////

  gm->update(counter.fps());
  gm->render();

  //controls
  if(keyPressed[KEY_ID_W]==true)      gm->getCam()->moveForward();
  if(keyPressed[KEY_ID_A]==true)      gm->getCam()->moveLeft();
  if(keyPressed[KEY_ID_D]==true)      gm->getCam()->moveRight();
  if(keyPressed[KEY_ID_S]==true)      gm->getCam()->moveBackward();
  if(keyPressed[KEY_ID_SPACE]==true)  gm->getCam()->moveUp();
  if(keyPressed[KEY_ID_C]==true)      gm->getCam()->moveDown();

  //if (keyPressed[KEY_ID_H] == true)      gm->getSpaceship()->moveUp();
  if (keyPressed[KEY_ID_B] == true)      gm->getSpaceship()->moveLeft();
  //if (keyPressed[KEY_ID_J] == true)      gm->getSpaceship()->moveDown();
  if (keyPressed[KEY_ID_M] == true)      gm->getSpaceship()->moveRight();
  if (keyPressed[KEY_ID_N] == true)
  {
	  gm->playerShoot();
	  keyPressed[KEY_ID_N] = false;
  }
  if (keyPressed[KEY_ID_1])
  {
	  gm->setWeaponMinigun();
  }
  if (keyPressed[KEY_ID_2])
  {
	  gm->setWeaponRocket();
  }
  if (keyPressed[KEY_ID_I])
  {
	  gm->upgradeHp();
	  keyPressed[KEY_ID_I] = false;
  }
  if (keyPressed[KEY_ID_U])
  {
	  gm->upgradeDamage();
	  keyPressed[KEY_ID_U] = false;
  }
  
  //
  std::string selectedWeapon = gm->getSelectedWeapon();
  drawText(selectedWeapon.data(), selectedWeapon.length(), 250, 10, glm::vec3(0.0f, 1.0f, 1.0f), 1);

  //std::string weaponInfo =;
  //drawText(weaponInfo.data(), weaponInfo.length(), 30, 660);

  //std::string movementInfo =;
  //drawText(movementInfo.data(), movementInfo.length(), 30, 680);

  int score = gm->getSpaceship()->getScore();
  std::string scoreString;
  std::ostringstream convertScore;
  convertScore << score;
  scoreString = "Score: " + convertScore.str();
  drawText(scoreString.data(), scoreString.length(), 10, 650, glm::vec3(0.0f, 0.0f, 0.0f), 1);

  int hitpoints = gm->getSpaceship()->getHP();
  std::string hpString;
  std::ostringstream convertHp;
  convertHp << hitpoints;
  hpString = "HP: " + convertHp.str();
  std::string endgame = "Game over!";
  if (hitpoints > 0)
  { 
	  drawText(hpString.data(), hpString.length(), 10, 600, glm::vec3(1.0f, 0.0f, 0.0f), 1);
  }

  else
  {
	  hpString = "HP: 0";
	  drawText(hpString.data(), hpString.length(), 10, 600, glm::vec3(1.0f, 0.0f, 0.0f), 1);
	  drawText(endgame.data(), endgame.length(), 300, 400, glm::vec3(1.0f, 0.0f, 0.0f), 1);
  }

  float damage = gm->getWeaponDamage();
  std::string damageModString;
  std::ostringstream convertDamage;
  convertDamage << damage;
  damageModString = "Weapon damage: " + convertDamage.str();
  drawText(damageModString.data(), damageModString.length(), 500, 40, glm::vec3(0.0f, 1.0f, 1.0f), 0);

  glutSwapBuffers();
  glutPostRedisplay();
}



void keyDown(unsigned char key, int x, int y)
{
  switch (key) 
  {
//    case 'q':
//    case 27:
//      glutDestroyWindow(window);
//#ifndef _WIN32
//      // Must use this with regular glut, since it never returns control to main().
//      exit(0);
//#endif
      break;
      
    case 'w':
      keyPressed[KEY_ID_W] = true;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = true;
      break;
    case 's':
      keyPressed[KEY_ID_S] = true;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = true;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = true;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = true;
      break;
	case 'b':
		keyPressed[KEY_ID_B] = true;
		break;
	case 'n':
		keyPressed[KEY_ID_N] = true;
		break;
	case 'm':
		keyPressed[KEY_ID_M] = true;
		break;
	case '1':
		keyPressed[KEY_ID_1] = true;
		break;
	case '2':
		keyPressed[KEY_ID_2] = true;
		break;
	case 'i':
		keyPressed[KEY_ID_I] = true;
		break;
	case 'u':
		keyPressed[KEY_ID_U] = true;
		break;

    default:
      glutPostRedisplay();
  }
}

void keyUp(unsigned char key, int x, int y)
{
  switch (key) 
  {
    case 'w':
      keyPressed[KEY_ID_W] = false;
      break;
    case 'a':
      keyPressed[KEY_ID_A] = false;
      break;
    case 's':
      keyPressed[KEY_ID_S] = false;
      break;
    case 'd':
      keyPressed[KEY_ID_D] = false;
      break;
    case ' ':
      keyPressed[KEY_ID_SPACE] = false;
      break;
    case 'c':
      keyPressed[KEY_ID_C] = false;
      break;
	case 'b':
		keyPressed[KEY_ID_B] = false;
		break;
	case 'n':
		keyPressed[KEY_ID_N] = false;
		break;
	case 'm':
		keyPressed[KEY_ID_M] = false;
		break;
	case '1':
		keyPressed[KEY_ID_1] = false;
		break;
	case '2':
		keyPressed[KEY_ID_2] = false;
		break;
	case 'i':
		keyPressed[KEY_ID_I] = false;
		break;
	case 'u':
		keyPressed[KEY_ID_U] = false;
		break;
  }
}

void mousePressed(int button, int state, int posX, int posY)
{
  if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
  {
    mousePosX = posX;
    mousePosY = posY;
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = true;
  }  
  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    keyPressed[MOUSE_LEFT_BUTTON_DOWN] = false;
}

void mouseMoved(int posX, int posY)
{
  if(keyPressed[MOUSE_LEFT_BUTTON_DOWN])
  {
    int diffX = posX - mousePosX;
    mousePosX = posX;
    int diffY = posY - mousePosY;
    mousePosY = posY;
    
    // Implement quaternion based mouse move

  }
}

void addEnemy(int i)
{
	if (!(gm->isBossActive()))
	{
		gm->spawnEnemy(40);
		glutTimerFunc(4500.0f, addEnemy, 0.0f);
	}
	else
	{
		gm->spawnEnemy(40);
		glutTimerFunc(1000.0f, addEnemy, 0.0f);
	}
}
void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei) w, (GLsizei) h); 
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
//  glOrtho(-50, 700, -50, 700, -50, 50);
  gluPerspective(60.0f, float(w)/float(h) ,1.0f, 3000.0f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
//  gluLookAt(0.0, 0.0, 10.0,     0.0, 0.0, 0.0,    0.0, 1.0, 0.0);
}

int main(int argc, char** argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
  glutInitWindowSize(700, 700); 
  glutInitWindowPosition(10, 10);
  window = glutCreateWindow("SpaceShooterApp");
  init();
  glutIgnoreKeyRepeat(1);
  glutKeyboardFunc(keyDown);
  glutKeyboardUpFunc(keyUp);
  glutReshapeFunc(reshape);
  glutDisplayFunc(display);
  glutMouseFunc(mousePressed);
  glutMotionFunc(mouseMoved);

  glutTimerFunc(1000.0f, addEnemy, 0.0f);
  // Add other callback functions here..

  glutMainLoop();
  return 0;
}
