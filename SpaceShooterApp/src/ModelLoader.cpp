#include "ModelLoader.hpp"

ModelLoader::ModelLoader()
{
	loadFighterModel();
	loadEnemyModel();
    loadBulletModel();
    loadBossModel();
    loadMissileModel();
}

ModelLoader::~ModelLoader()
{
	delete fighterModel_;
	delete enemyModel_;
    delete bulletModel_;
    delete bossModel_;
    delete missileModel_;
}

void ModelLoader::loadFighterModel()
{
	fighterModel_ = new Model();
	fighterModel_->loadModel("models/fighter/fighter.obj");
	fighterModel_->setTexture("models/fighter/fighter.png");
}
void ModelLoader::loadEnemyModel()
{
	enemyModel_ = new Model();
    enemyModel_->loadModel("models/enemy/enemy.obj");
    enemyModel_->setTexture("models/enemy/enemytex.png");
}

void ModelLoader::loadBulletModel()
{
    bulletModel_ = new Model();
	bulletModel_->loadModel("models/ammo/ammo.obj");
	bulletModel_->setTexture("models/ammo/ammo.png");
}

void ModelLoader::loadBossModel()
{
    bossModel_ = new Model();
    bossModel_->loadModel("models/boss/boss.obj");
    bossModel_->setTexture("models/boss/boss.png");
}

void ModelLoader::loadMissileModel()
{
    missileModel_ = new Model();
    missileModel_->loadModel("models/missile/missile.obj");
    missileModel_->setTexture("models/missile/missile.png");
}

Model *ModelLoader::getFighterModel()
{
	return fighterModel_;
}

Model *ModelLoader::getEnemyModel()
{
    return enemyModel_;
}

Model *ModelLoader::getBulletModel()
{
    return bulletModel_;
}

Model *ModelLoader::getBossModel()
{
    return bossModel_;
}

Model *ModelLoader::getMissileModel()
{
    return missileModel_;
}
