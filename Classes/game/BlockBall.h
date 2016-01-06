#ifndef  _BlockBall_H_
#define  _BlockBall_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;


class BlockBall : public cocos2d::Sprite
{
public:
	BlockBall(void);
	CREATE_FUNC(BlockBall);
	virtual bool init();
	 void update(float delta);
	
	void onEnter();
    void onExit();
	b2Body* m_body;

	float m_x;
	float m_y;
	float m_x_scope;
	float m_speed;

	float m_x_min;
	float m_x_max;

	~BlockBall(void);

};
#endif // _BlockBall_H_

