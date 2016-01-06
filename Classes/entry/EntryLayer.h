#ifndef  _EntryLayer_H_
#define  _EntryLayer_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "Ball.h"
#include "user-macros.h"
#include "UFO.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;


USING_NS_CC;
USING_NS_CC_EXT;


class EntryLayer : public cocos2d::CCLayer
{
public:
	EntryLayer(void);
	CREATE_FUNC(EntryLayer);
	virtual bool init();

	virtual bool onTouchBegan(Touch* pTouch, Event* pEvent);
	virtual void onTouchMoved(Touch* pTouch, Event* pEvent);
	virtual void onTouchEnded(Touch* pTouch, Event* pEvent);
	
	void onEnter();
    void onExit();

	void ballJumpCB(CCNode* c);
	void initJumpBall();
	Sprite* logo;
	Sprite* startBtn;
	Sprite* infoBtn;

	UFO* ufo_logo;

	Ball* jumpBall;

	Layout* layout;
	void closeBtnClick(Ref *pSender, TouchEventType type);

	~EntryLayer(void);

};
#endif // _EntryLayer_H_

