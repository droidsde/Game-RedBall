#ifndef  _EntryScence_H_
#define  _EntryScence_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"
#include "EntryLayer.h"
#include "GlobalRunTimeData.h"

USING_NS_CC;
USING_NS_CC_EXT;


class EntryScence : public cocos2d::Scene
{
public:
	EntryScence(void);
	CREATE_FUNC(EntryScence);
	virtual bool init();

	void onEnter();
    void onExit();

	~EntryScence(void);

};
#endif // _EntryScence_H_

