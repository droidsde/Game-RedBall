#ifndef  _Cup_H_
#define  _Cup_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"
#include "Box2D/Box2D.h"

USING_NS_CC;
USING_NS_CC_EXT;


class Cup : public cocos2d::Sprite
{
public:
	Cup(void);
	CREATE_FUNC(Cup);
	virtual bool init();
 
	void onEnter();
    void onExit();

	void addToLayer();
	void setPosition1(Point p);
	Rect getBoundingBox1();
	void showParticle(int id);
 
	b2Body * wallLeft;
	b2Body * wallRight;

	b2BodyDef m_b2BodyDefLeft;
	b2BodyDef m_b2BodyDefRight;
	~Cup(void);

};
#endif // _Cup_H_

