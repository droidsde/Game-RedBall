#ifndef  _Ball_H_
#define  _Ball_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"

USING_NS_CC;
USING_NS_CC_EXT;


class Ball : public cocos2d::Sprite
{
public:
	Ball(void);
	CREATE_FUNC(Ball);
	virtual bool init();

	 
	//void myUpdate(float fDelta);
	//void callBack(CCNode* c);
	//void menuCloseCallback(CCObject* pSender);
	int m_collisionCount;
	void onEnter();
    void onExit();
	void initWithType(int type);

	CCParticleSystem* m_partical;

	int m_ballType;

	
	~Ball(void);

};
#endif // _Ball_H_

