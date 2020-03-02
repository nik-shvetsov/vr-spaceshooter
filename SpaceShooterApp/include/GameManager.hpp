#pragma once

#include <GL/glew.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "SceneObject.hpp"
#include "BattleField.hpp"
#include "SpaceShip.hpp"
#include "Camera.hpp"
#include "Enemy.h"
#include "Text.hpp"
#include "ParticleGenerator.hpp"
#include "Shader.hpp"
#include "Skybox.hpp"
#include "HealthBar.hpp"
#include "SkyBox.hpp"
#include "ModelLoader.hpp"
#include "Water.hpp"
#include "Bullet.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class GameManager : public SceneObject
{
	public:
		GameManager();
		~GameManager();
    
    std::shared_ptr<Camera> getCam();
	std::shared_ptr<SpaceShip> getSpaceship();

	std::shared_ptr<ParticleGenerator> getParticle();
	std::shared_ptr<Skybox> getSkybox();

	void spawnEnemy(int);
	void playerShoot();
	void enemyShoot();
	void setWeaponMinigun();
	void setWeaponRocket();
	void upgradeHp();
	void upgradeDamage();
	float getWeaponDamage();
	std::string getSelectedWeapon();
	bool isBossActive();

  protected:
    virtual void privateInit();
		virtual void privateRender();
		virtual void privateUpdate();

	private:
    std::shared_ptr<BattleField> bf_;
    std::shared_ptr<SpaceShip> spaceship_;
    std::shared_ptr<Camera> cam_;
	std::shared_ptr<Skybox> skybox_;
	std::shared_ptr<Text> healthText_;
	
	std::shared_ptr<ParticleGenerator> explosion_;
	std::shared_ptr<ParticleGenerator> beam_;

	std::shared_ptr<Water> water_;

	std::vector<std::shared_ptr<Enemy>> enemies_;
	std::vector<std::shared_ptr<Enemy>> bosses_;
	std::vector<std::shared_ptr<Bullet>> playerBullets_;
	std::vector<std::shared_ptr<Bullet>> enemyBullets_;
	std::vector<std::shared_ptr<HealthBar>> enemyHealthBars_;
	std::vector<std::shared_ptr<HealthBar>> bossHealthBars_;
	std::vector<std::shared_ptr<Bullet>> bossBullets_;

	//private game logic
	//void updateEnemies();
	//void renderEnemies();
	bool collision(float, float, glm::vec3, glm::vec3);
	bool bossActive_;
	int bossLevel_;
	bool stopSpawn_;

	//weapon modifiers
	float playerBulletRadius_;
	float playerBulletVelocity_;
	float playerBulletDamage_;
	float playerBulletDamageModifier_;
	std::string selectedWeapon_;

	//loader
	ModelLoader loader_;

};

