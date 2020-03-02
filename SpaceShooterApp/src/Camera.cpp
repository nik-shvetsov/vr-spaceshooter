#include "Camera.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#define PIOVER180 0.0174532925199

Camera::Camera()
{
  matrix_ = glm::translate(glm::mat4(), glm::vec3(-160.0f, -50.0f, -500.0f)); //0.0f, 0.0f, -50.0f
}

Camera::~Camera()
{
}

void Camera::privateInit()
{
	matrix_ = glm::translate(glm::mat4(), glm::vec3(x_, y_, z_));
}


void Camera::privateRender()
{
  // not drawing any camera geometry
}

void Camera::privateUpdate()
{

}

void Camera::moveRight()
{
  matrix_ = glm::translate(matrix_, glm::vec3(-25.0f, 0.0f, 0.0f));
}
void Camera::moveLeft()
{
  matrix_ = glm::translate(matrix_, glm::vec3(25.0f, 0.0f, 0.0f));
}
void Camera::moveUp()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, -25.0f, 0.0f));
}
void Camera::moveDown()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 25.0f, 0.0f));
}
void Camera::moveForward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, 25.0f));
}
void Camera::moveBackward()
{
  matrix_ = glm::translate(matrix_, glm::vec3(0.0f, 0.0f, -25.0f));
}

void Camera::followSpaceship(float x, float y, float z)
{
	x_ = x;
	y_ = y;
	z_ = z;
	privateInit();
}