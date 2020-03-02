#pragma once
#include <GL/glew.h>
#include <memory>
#include <GL/gl.h>
#include <GL/glu.h>
#include "SceneObject.hpp"

class HealthBar : public SceneObject
{
public:
    HealthBar();
    ~HealthBar();

    void setPos(glm::vec3 position);
    void setHP(float val);
    void reduceHP(float val);

protected:
    void privateInit();
    void privateRender();
    void privateUpdate();

private:
    float hp_;
    glm::vec3 position_;
};
