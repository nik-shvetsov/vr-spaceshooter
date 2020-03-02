#include "GameManager.hpp"
#include <string>

GameManager::GameManager()
{
	playerBulletDamageModifier_ = 1.0f;
	setWeaponMinigun();
	selectedWeapon_ = "Selected weapon: MINIGUN";
	bossActive_ = false;
	bossLevel_ = 1;
	stopSpawn_ = false;
}

GameManager::~GameManager()
{
}

void GameManager::privateInit()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	// Set default OpenGL states
  glEnable(GL_CULL_FACE);

  // Adding the camera to the scene
  cam_.reset(new Camera());
  //  this->addSubObject(cam_);
  //  matrix_.translate(0.0f, 0.0f, -99.0f);

  bf_.reset(new BattleField());
  this->addSubObject(bf_);

  spaceship_.reset(new SpaceShip(150.0f, 150.0f, 5120.0f, 100.0f, loader_.getFighterModel()));
  this->addSubObject(spaceship_);

  skybox_.reset(new Skybox());
  this->addSubObject(skybox_);

  water_.reset(new Water());
  this->addSubObject(water_);

  water_->setMatrix(glm::translate(water_->getMatrix(), glm::vec3(0.0f, 20.0f, 0.0f)));

  //lifeBar_.reset(new HUD(0, -500, 60));
  //this->addSubObject(lifeBar_);

  //text_.reset(new Text("Level - Space - 1", 0, 900));
  //this->addSubObject(text_);

  //healthText_.reset(new Text("Health:", 5, 10));
  //this->addSubObject(healthText_);

  //explosion_.reset(new ParticleGenerator(1));
  //this->addSubObject(explosion_);

  beam_.reset(new ParticleGenerator(0));
  this->addSubObject(beam_);

  //PlaySound(TEXT("..\\SpaceShooter\\sounds\\mus.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);

}

void GameManager::privateRender()
{
	//delete player when hit points are reduced to zero
	if (spaceship_->getHP() < 1.0f)
	{
		this->removeSubObject(spaceship_);
		this->removeSubObject(beam_);
	}

	//delete bosses when their hit points are reduced to zero
	for (int i = 0; i < bosses_.size(); i++)
	{
		if (bosses_[i]->getHP() < 1.0f)
		{
			this->removeSubObject(bosses_[i]);
			bosses_.erase(bosses_.begin() + i);
			this->removeSubObject(bossHealthBars_[i]);
			bossHealthBars_.erase(bossHealthBars_.begin() + i);
			spaceship_->addScore(50);
		}
	}

	//delete enemies when their hit points are reduced to zero or go out of scope
	for (int i = 0; i < enemies_.size(); i++)
	{
		if (enemies_[i]->getHP() < 1.0f)
		{
			this->removeSubObject(enemies_[i]);
			enemies_.erase(enemies_.begin() + i);
			this->removeSubObject(enemyHealthBars_[i]);
			enemyHealthBars_.erase(enemyHealthBars_.begin() + i);
			spaceship_->addScore(20);
		}
		else if (enemies_[i]->getPosition()[2] > (spaceship_->getPosition()[2] + 200))
		{
			this->removeSubObject(enemies_[i]);
			enemies_.erase(enemies_.begin() + i);
			this->removeSubObject(enemyHealthBars_[i]);
			enemyHealthBars_.erase(enemyHealthBars_.begin() + i);
		}
	}


	//delete player bullets out of scope
	for (int i = 0; i < playerBullets_.size(); i++)
	{
		if (playerBullets_[i]->getPos()[2] < 0.0f)
		{
			this->removeSubObject(playerBullets_[i]);
			playerBullets_.erase((playerBullets_.begin() + i));
		}
	}


	for (int i = 0; i < enemies_.size(); i++)
	{
		enemyHealthBars_[i]->setPos(enemies_[i]->getPosition());
		enemyHealthBars_[i]->setHP(enemies_[i]->getHP());

		//collision between enemies and player
		if (collision(enemies_[i]->getRad(), spaceship_->getRad(), enemies_[i]->getPosition(), spaceship_->getPosition()))
		{
			spaceship_->reduceHP(20.0f);
			enemies_[i]->reduceHP(100);
		}

		//collision between enemies and player bullets
		for (int j = 0; j < playerBullets_.size(); j++)
		{
			if (collision(enemies_[i]->getRad(), playerBullets_[j]->getRad(), enemies_[i]->getPosition(), playerBullets_[j]->getPos()))
			{
				enemies_[i]->reduceHP(playerBulletDamage_);
				enemyHealthBars_[i]->reduceHP(playerBulletDamage_);
				this->removeSubObject(playerBullets_[j]);
				playerBullets_.erase((playerBullets_.begin() + j));
			}
		}
	}

	for (int i = 0; i < bosses_.size(); i++)
	{
		bossHealthBars_[i]->setPos(bosses_[i]->getPosition());
		bossHealthBars_[i]->setHP(bosses_[i]->getHP());

		//collision between bosses and player bullets
		for (int j = 0; j < playerBullets_.size(); j++)
		{
			if (collision(bosses_[i]->getRad(), playerBullets_[j]->getRad(), bosses_[i]->getPosition(), playerBullets_[j]->getPos()))
			{
				bosses_[i]->reduceHP(playerBulletDamage_);
				bossHealthBars_[i]->reduceHP(playerBulletDamage_);
				this->removeSubObject(playerBullets_[j]);
				playerBullets_.erase((playerBullets_.begin() + j));
			}
		}
	}

	for (int i = 0; i < bossBullets_.size(); i++)
	{

		//collision between boss bullets and player
		if (collision(bossBullets_[i]->getRad(), spaceship_->getRad(), bossBullets_[i]->getPos(), spaceship_->getPosition()))
		{
			spaceship_->reduceHP(20.0f);

			this->removeSubObject(bossBullets_[i]);
			bossBullets_.erase(bossBullets_.begin() + i);
		}
		//delete boss bullets out of scope
		else if (bossBullets_[i]->getPos()[2] > (spaceship_->getPosition()[2] + 200))
		{
			this->removeSubObject(bossBullets_[i]);
			bossBullets_.erase((bossBullets_.begin() + i));
		}
	}

	for (int i = 0; i < enemyBullets_.size(); i++)
	{

		//collision between enemy bullets and player
		if (collision(enemyBullets_[i]->getRad(), spaceship_->getRad(), enemyBullets_[i]->getPos(), spaceship_->getPosition()))
		{
			spaceship_->reduceHP(10.0f);

			//
			//float currhp = spaceship_->getHP();
			//std::string hpString = "Health: " + std::to_string(currhp);
			//healthText_->setText(hpString.c_str());

			this->removeSubObject(enemyBullets_[i]);
			enemyBullets_.erase(enemyBullets_.begin() + i);
		}
		//delete enemy bullets out of scope
		else if (enemyBullets_[i]->getPos()[2] > (spaceship_->getPosition()[2] + 200))
		{
			this->removeSubObject(enemyBullets_[i]);
			enemyBullets_.erase((enemyBullets_.begin() + i));
		}
	}

	//set camera to follow spaceship
	cam_->followSpaceship(spaceship_->getPosition()[0] * -1, (spaceship_->getPosition()[1] + 30.0f) *-1, (spaceship_->getPosition()[2] + 100.0f)*-1);
}

void GameManager::privateUpdate()
{
	if (spaceship_->getScore() >= 100 * bossLevel_)
	{
		bossActive_ = true;
	}

	if (bosses_.size() == bossLevel_)
	{
		stopSpawn_ = true;
	}
	// Instead of adding all objects in the scene as subobject to the camera they are added as subobjects
  // to the game manager. Therefore, we set the game manager matrix equal to the camera matrix. 
  this->matrix_ = cam_->getMatrix();

  glm::mat4 m = matrix_;
  m[3][0] = -matrix_[3][0];
  m[3][1] = -matrix_[3][1];
  m[3][2] = -matrix_[3][2];
  skybox_->setMatrix(m);

  skybox_->setMatrix(glm::translate(skybox_->getMatrix(), glm::vec3(0.0f, 0.0f, -150.0f)));

  glm::vec3 camPos = glm::vec3(m[3][0], m[3][1], m[3][2]);
  spaceship_->setCamPos(camPos);
  
  //beam connection
  beam_->setMatrix(glm::translate(spaceship_->getMatrix(), glm::vec3(0.0f, 2.0f, 50.0f)));

  //spaceship_->setMatrix(glm::translate(cam_->getMatrix(), glm::vec3(-0.1f, 6.0f, -7.0f)));

  //skybox connection to cam (or ship)
  //skybox_->setMatrix(glm::translate(spaceship_->getMatrix(), glm::vec3(0.0f, 250.0f, -100.0f)));
}

bool GameManager::isBossActive()
{
	return bossActive_;
}


std::shared_ptr<Camera> GameManager::getCam()
{
  return cam_;
}

std::shared_ptr<SpaceShip> GameManager::getSpaceship()
{
	return spaceship_;
}

std::shared_ptr<ParticleGenerator> GameManager::getParticle()
{
	return beam_;
}

std::shared_ptr<Skybox> GameManager::getSkybox()
{
	return skybox_;
}

void GameManager::spawnEnemy(int sq)
{
	if (enemies_.size() < 10 && !(bossActive_))
	{
		float rx = float(rand() % sq + 5.0f);
		std::shared_ptr<Enemy> _enemy;
		_enemy.reset(new Enemy(rx, loader_.getEnemyModel(), spaceship_->getPosition()[2] - 500.0f, 0.7f, 80.0f));
		this->addSubObject((_enemy));
		enemies_.push_back(_enemy);
		std::shared_ptr<HealthBar> health;
		health.reset(new HealthBar());
		this->addSubObject(health);
		enemyHealthBars_.push_back(health);
	}
	if (bossActive_ && bosses_.size() < bossLevel_ && !(stopSpawn_))
	{
		float rx = float(rand() % sq + 5.0f);
		std::shared_ptr<Enemy> _boss;
		_boss.reset(new Enemy(rx, loader_.getBossModel(), spaceship_->getPosition()[2] - 300.0f, 0.0f, 400.0f));
		this->addSubObject((_boss));
		spaceship_->setVelocity(0.0f);
		bosses_.push_back(_boss);
		std::shared_ptr<HealthBar> health;
		health.reset(new HealthBar());
		this->addSubObject(health);
		bossHealthBars_.push_back(health);
	}
	enemyShoot();
}

void GameManager::playerShoot()
{
	std::shared_ptr<Bullet> bullet;
	if (playerBulletRadius_ == 1.5f)
	{
		bullet.reset(new Bullet(playerBulletRadius_, loader_.getBulletModel()));
	}
	else
	{
		bullet.reset(new Bullet(playerBulletRadius_, loader_.getMissileModel()));
	}
	bullet->setPos(spaceship_->getPosition());
	bullet->setDir(glm::vec3(0, 0, playerBulletVelocity_));
	this->addSubObject(bullet);
	playerBullets_.push_back(bullet);
}

void GameManager::enemyShoot()
{
	for (int i = 0; i < enemies_.size(); i++)
	{
		std::shared_ptr<Bullet> bullet;
		bullet.reset(new Bullet(1.0, loader_.getBulletModel()));
		bullet->setPos(enemies_[i]->getPosition());
		bullet->setDir(glm::vec3(0, 0, 5));
		this->addSubObject(bullet);
		enemyBullets_.push_back(bullet);
	}
	for (int i = 0; i < bosses_.size(); i++)
	{
		std::shared_ptr<Bullet> bullet;
		bullet.reset(new Bullet(1.0, loader_.getBulletModel()));
		bullet->setPos(bosses_[i]->getPosition());
		bullet->setDir(glm::vec3(0, 0, 5));
		this->addSubObject(bullet);
		bossBullets_.push_back(bullet);
	}
	if (bossActive_ && bosses_.size() == 0)
	{
		bossActive_ = false;
		stopSpawn_ = false;
		spaceship_->setVelocity(-0.5f);
		bossLevel_++;
	}
}

bool GameManager::collision(float radius1, float radius2, glm::vec3 position1, glm::vec3 position2)
{
	float d = glm::length(position1 - position2);
	if (d < radius1 + radius2) return true;
	return false;
}

//change weapons

void GameManager::setWeaponMinigun()
{
	playerBulletRadius_ = 1.5f;
	playerBulletVelocity_ = -3.0f;
	playerBulletDamage_ = 25.0f * playerBulletDamageModifier_;
	selectedWeapon_ = "Selected weapon: MINIGUN";
}

void GameManager::setWeaponRocket()
{
	playerBulletRadius_ = 3.5f;
	playerBulletVelocity_ = -1.5f;
	playerBulletDamage_ = 55.0f * playerBulletDamageModifier_;
	selectedWeapon_ = "Selected weapon: ROCKET LAUNCHER";
}

void GameManager::upgradeHp()
{
	int score = spaceship_->getScore();
	if (score >= 100)
	{
		spaceship_->increaseHP(20.0f);
		spaceship_->spendScore(100);
	}
}

void GameManager::upgradeDamage()
{
	int score = spaceship_->getScore();
	if (score >= 100)
	{
		playerBulletDamageModifier_ += 0.2f;
		spaceship_->spendScore(100);
	}
}

float GameManager::getWeaponDamage()
{
	return playerBulletDamage_;
}

std::string GameManager::getSelectedWeapon()
{
	return selectedWeapon_;
}