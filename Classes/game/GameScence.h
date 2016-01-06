#ifndef  _GameScence_H_
#define  _GameScence_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"
#include "GameLayer.h"
#include "GlobalRunTimeData.h"

USING_NS_CC;
USING_NS_CC_EXT;


class GameScence : public cocos2d::Scene
{
public:
	static GameScence* sharedGameScence(void);

	GameScence(void);
	CREATE_FUNC(GameScence);
	virtual bool init();
	void onEnter();
    void onExit();

	GameLayer* gameLayer;

	~GameScence(void);

};
#endif // _GameScence_H_

