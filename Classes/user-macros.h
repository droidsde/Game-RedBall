#ifndef  _user_macros_H_
#define  _user_macros_H_

#define WINSIZE CCSize visibleSize = Director::getInstance()->getVisibleSize();\
	CCPoint origin = Director::getInstance()->getVisibleOrigin();

#define GLOBAL_DATA GlobalRunTimeData::sharedGlobalRunTimeData() 
#define TRUE 1
#define FALSE 0
#define PTM_RATIO 32
#define TOUCH_SPEED 30

#define SHOW_GREEN_PARTICLE 30
class B2UserDataBase 
{
public:
	int m_type;
	void* m_UserData;
	void* m_particle;
	B2UserDataBase(void){m_particle=NULL;};
	~B2UserDataBase(void){};
};
#endif // _user_macros_H_
