#ifndef  _UFO_CPP_
#define  _UFO_CPP_

#include "UFO.h"
#include "GameScence.h"
#include "SoundManager.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool UFO::init(){

	if ( !Sprite::init() )
	{
		return false;
	}

	type=11;
	m_frameCount=0;
	count=1;
	frameIdx=std::vector<int>();
	return TRUE;

}

void UFO::onEnter(){
	Sprite::onEnter();
 
}

void UFO::initWithType(int t){
	type=t;
	char ufo_name[30];
	sprintf(ufo_name,"ufo_%d.png",t);
	this->initWithFile(ufo_name);
}


void UFO::onExit(){
 
	Sprite::onExit();
}
 
void UFO::startShake(){
	CCActionInterval* ca=CCRotateTo::create(0.5,-10);
	CCActionInterval* ca1=CCRotateTo::create(0.5,10);
    CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca,ca1,NULL));
	CCRepeatForever* actRep=CCRepeatForever::create(actSeq);
    runAction(actRep);

}

void UFO::startDrop(){


	for(int i=0;i<count;i++){
		float _seed=0.7+CCRANDOM_0_1()*2;
		int f_idx=(int)(_seed*60);
		frameIdx.push_back(f_idx);
	}

	this->scheduleUpdate();
 
}
 

void UFO::update(float delta){
	 m_frameCount++;
	 for(int i=0;i<frameIdx.size();i++){
		int idx=frameIdx.at(i);
		if(m_frameCount==idx){
			auto x=getPositionX();
			auto y=getPositionY()+this->getBoundingBox().size.height/2;
		 
			GameScence::sharedGameScence()->gameLayer->addBall(type,x/PTM_RATIO,y/PTM_RATIO);
			SoundManager::sharedSoundManager()->playEffect("ext_ball_drop");
		}
	 }

 
}

UFO::UFO(void)
{
}


UFO::~UFO(void)
{
}





#endif // _UFO_CPP_

