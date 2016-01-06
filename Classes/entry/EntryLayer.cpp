#ifndef  _EntryLayer_CPP_
#define  _EntryLayer_CPP_

#include "EntryLayer.h"
#include "GameScence.h"
#include "SoundManager.h"
#include "Telegraph.h"


USING_NS_CC;
USING_NS_CC_EXT;


bool EntryLayer::init(){

	if (!CCLayer::init())
	{
		return FALSE;
	}

	
	WINSIZE;

	CCParticleSystem* particle=ParticleSystemQuad::create("kilakila.plist");
	particle->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	addChild(particle);

	logo = CCSprite::create("title_cn.png");
	logo->setPosition(ccp(visibleSize.width/2,visibleSize.height-350));
	this->addChild(logo);


	startBtn = CCSprite::create("start_btn_cn.png");
	startBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height/2- 50));
	this->addChild(startBtn);

	infoBtn = CCSprite::create("info_btn_cn.png");
	infoBtn->setPosition(ccp(visibleSize.width/2,visibleSize.height/2-300));
	this->addChild(infoBtn);


	ufo_logo=UFO::create();
	ufo_logo->initWithType(0);
	auto p=logo->getPosition();
	auto p1=ccpAdd(p,ccp(-logo->boundingBox().size.width/2+100,logo->boundingBox().size.height/2+40));
	ufo_logo->setPosition(p1);
	addChild(ufo_logo);
	ufo_logo->startShake();

	



	setTouchEnabled(TRUE);
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	initJumpBall();



	layout= static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("InfoPanel/Export/InfoPanel_1/InfoPanel_1.json"));
	auto layoutSize=layout->getContentSize();
	layout->setPosition(CCPoint( visibleSize.width / 2-layoutSize.width/2, visibleSize.height / 2-layoutSize.height/2));
	layout->setVisible(FALSE);
	addChild(layout,50);

	ui::Button* closeBtn = static_cast<Button*>(Helper::seekWidgetByName(layout, "Button_Close"));
	closeBtn->addTouchEventListener(this, toucheventselector(EntryLayer::closeBtnClick));



	return TRUE;
 

}
void EntryLayer::closeBtnClick(Ref *pSender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
	layout->setVisible(FALSE);
	SoundManager::sharedSoundManager()->playEffect("btn_press");
	
	}
	
}

void EntryLayer::onEnter(){
	CCLayer::onEnter();
	
}




void EntryLayer::onExit(){
 
	CCLayer::onExit();
}

bool EntryLayer::onTouchBegan(Touch* pTouch, Event* pEvent){
	return TRUE;

}

void EntryLayer::onTouchMoved(Touch* pTouch, Event* pEvent){


}


void EntryLayer::onTouchEnded(Touch* pTouch, Event* pEvent){
	WINSIZE;
	auto touchPoint = pTouch->getLocation();
	if(startBtn->getBoundingBox().containsPoint(touchPoint)){
		SoundManager::sharedSoundManager()->playEffect("btn_press");
		auto gameScence= GameScence::create();
		auto director = Director::getInstance();
		Telegraph::sharedTelegraph()->send1("http://configcenter.sinaapp.com/ios_auto_share_show/");
		director->replaceScene(TransitionCrossFade::create(0.34f, gameScence));
	}

	if(ufo_logo->getBoundingBox().containsPoint(touchPoint)){
	
		CCActionInterval* ca=CCMoveBy::create(1.5,ccp(0,300));
		
		ufo_logo->runAction(ca);

		SoundManager::sharedSoundManager()->playEffect("ufo_short");
	
	}

	if(infoBtn->getBoundingBox().containsPoint(touchPoint)){
		layout->setVisible(TRUE);
		SoundManager::sharedSoundManager()->playEffect("btn_press");
	}




}

void EntryLayer::initJumpBall(){
	WINSIZE;
	Point p=ccpAdd(logo->getPosition(),ccp(250,70));
	jumpBall=Ball::create();
	jumpBall->initWithType(0);
	jumpBall->setColor(ccc3(255,0,0));
	jumpBall->setPosition(p);
	addChild(jumpBall);

	CCActionInterval* ca=CCJumpBy::create(0.5,ccp(0,0),100,1);
	CCActionInterval* ca1=CCJumpBy::create(0.3,ccp(0,0),50,1);
	CCActionInterval* delay=CCDelayTime::create(0.5);
	CCCallFuncN* cb=CCCallFuncN::create(this,callfuncN_selector(EntryLayer::ballJumpCB)); 
    CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(cb,ca,ca1,delay,NULL));

	CCRepeatForever* rep=CCRepeatForever::create(actSeq);
    jumpBall->runAction(rep);

}
void EntryLayer::ballJumpCB(CCNode* c){
	SoundManager::sharedSoundManager()->playEffect("entry_ball_jump");
}
EntryLayer::EntryLayer(void)
{
}


EntryLayer::~EntryLayer(void)
{
}



#endif // _EntryLayer_CPP_

