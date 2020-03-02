#include "Model.hpp"

class ModelLoader
{
public:
    ModelLoader();
    ~ ModelLoader();

	Model* getFighterModel();
	Model* getEnemyModel();
    Model* getBulletModel();
    Model* getBossModel();
    Model* getMissileModel();

private:
	void loadFighterModel();
	void loadEnemyModel();
    void loadBulletModel();
    void loadBossModel();
    void loadMissileModel();

	Model* fighterModel_;
	Model* enemyModel_;
    Model* bulletModel_;
    Model* missileModel_;
    Model* bossModel_;
};
