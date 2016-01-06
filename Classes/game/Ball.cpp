#ifndef  _Ball_CPP_
#define  _Ball_CPP_

#include "Ball.h"
#include "SoundManager.h"
USING_NS_CC;
USING_NS_CC_EXT;


bool Ball::init(){

	if ( !Sprite::init() )
	{
		return FALSE;
	}
	
	m_collisionCount=0;
	return TRUE;

}

void Ball::onEnter(){
	Sprite::onEnter();
 }

void Ball::initWithType(int type){
	this->m_ballType=type;
	if(type==0){
		this->initWithFile("ball.png");
		this->setColor(ccc3(255,255,255));
		m_partical=ParticleSystemQuad::create("greenball.plist");
		m_partical->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
		m_partical->setPositionType(kCCPositionTypeFree);
		m_partical->setVisible(FALSE);
		addChild(m_partical);
	}
	if(type==1){
		this->initWithFile("ball.png");
		this->setColor(ccc3(255,0,0));
		m_partical=ParticleSystemQuad::create("fireball.plist");
		m_partical->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
		m_partical->setPositionType(kCCPositionTypeFree);
 
		addChild(m_partical);
	}


	if(type==11){
		this->initWithFile("ext_ball_11.png");
	}
	if(type==12){
		this->initWithFile("ext_ball_12.png");
	}
	if(type==13){
		this->initWithFile("ext_ball_13.png");
	}
	if(type==14){
		this->initWithFile("ext_ball_14.png");
	}

}


void Ball::onExit(){
	Sprite::onExit();
}

 

Ball::Ball(void)
{
}


Ball::~Ball(void)
{
}



#endif // _Ball_CPP_

