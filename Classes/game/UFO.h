#ifndef  _UFO_H_
#define  _UFO_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"

USING_NS_CC;
USING_NS_CC_EXT;


class UFO : public cocos2d::Sprite
{
public:
	UFO(void);
	CREATE_FUNC(UFO);
	virtual bool init();
 
	
	void onEnter();
    void onExit();

	int type;
	int count;
	int m_frameCount;
	void initWithType(int t);
	void startShake();
	void stopShake();

 
	void startDrop();
	void update(float delta);
	~UFO(void);

	std::vector<int> frameIdx;

};



#endif // _UFO_H_
 