#ifndef  _BlockBall_CPP_
#define  _BlockBall_CPP_

#include "BlockBall.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool BlockBall::init(){

	if ( !Sprite::init() )
	{
		return false;
	}
	initWithFile("ball.png");


	auto seed=CCRANDOM_0_1()*6;
	int idx=(int)seed;
	char name[30];
	sprintf(name,"block_%d.png",idx);
	initWithFile(name);
	scheduleUpdate();

	return TRUE;

}

void BlockBall::onEnter(){
	Sprite::onEnter();
	WINSIZE;
	float halfScopeWidth=visibleSize.width*m_x_scope*0.5;
	m_x_min=visibleSize.width*m_x-halfScopeWidth;
	m_x_max=visibleSize.width*m_x+halfScopeWidth;
}


void BlockBall::update(float delta){
	auto x= getPositionX();
	if(x+m_speed>m_x_max || x+m_speed<m_x_min){
		m_speed=-m_speed;
	}
	x+=m_speed;
	setPositionX(x);
	m_body->SetTransform(b2Vec2(x/PTM_RATIO,getPositionY()/PTM_RATIO),m_body->GetAngle());

}


void BlockBall::onExit(){
	Sprite::onExit();
}

 

BlockBall::BlockBall(void)
{
}


BlockBall::~BlockBall(void)
{
}



#endif // _BlockBall_CPP_

