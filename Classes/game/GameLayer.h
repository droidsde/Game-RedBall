#ifndef  _GameLayer_H_
#define  _GameLayer_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "user-macros.h"
#include "Box2D/Box2D.h"
#include "Cup.h"
#include "Ball.h"
#include "UFO.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

#define GREEN_STEP -10

USING_NS_CC;
USING_NS_CC_EXT;


class GameLayer : public cocos2d::Layer , public b2ContactListener
{
public:
	GameLayer(void);
	CREATE_FUNC(GameLayer);
	virtual bool init();

  
	
	void onEnter();
    void onExit();


	void initBarrier();
	void initWalls();
	void initCup();

	void addBall(int tp,float x ,float y);
	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);

	void initScoreLabel();
	void setScoreNum(int num);

	void addBallUpdater(float fDelta);
	void update(float delta);

	void addExtLabel(std::string labelStr ,Point p,float scale,float during,float height,int r,int g,int b);
	void addExtNum(int num ,Point p,float scale,float during,float height,int r,int g,int b,float margin_bottom);


	void animationEndAndRemoveCallback(CCNode* c);

	void againClick(Ref *pSender, TouchEventType type);
	void shareClick(Ref *pSender, TouchEventType type);
	b2World* m_world;
	void toGreen(Ball* sprite);
	 void gameOver();
	//Åö×²¿ªÊ¼
    void BeginContact(b2Contact* contact);
    //Åö×²½áÊø
    void EndContact(b2Contact* contact);


	void showNewRecord(CCNode* node);
	Cup* cup;
	CCLabelBMFont* m_scoreLabel;
	CCLabelBMFont* m_scoreNum;
	CCParticleSystem* particleKilakila;

	Layout* layout;

	float targetX;


	Sprite* m_doubleTime;
	

	UFO* ufo;
	Vector<Sprite*> m_HP_Bar;
	void setHPBar();
	void secondTick(float d);

	void antiRedBallExplode();
	void ufoComing();
	void ufoMoveOut(CCNode* c);

	Layout* m_volume;
	ui::Button* m_VolumeBtn;

	void initVolume();

	void volumeClick(Ref *pSender, TouchEventType type);


	~GameLayer(void);

};
#endif // _GameLayer_H_

