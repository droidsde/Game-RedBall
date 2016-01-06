#ifndef  _GameLayer_CPP_
#define  _GameLayer_CPP_

#include "GameLayer.h"
#include "BlockBall.h"

#include "GameScence.h"
#include "GlobalRunTimeData.h"
#include "SoundManager.h"
#include "Telegraph.h"



USING_NS_CC;
USING_NS_CC_EXT;


bool GameLayer::init(){

	if ( !Layer::init() )
	{
		return FALSE;
	}
 
	WINSIZE;

	particleKilakila=ParticleSystemQuad::create("kilakila.plist");
	particleKilakila->setPosition(ccp(visibleSize.width/2,visibleSize.height/2));
	addChild(particleKilakila);

	setTouchEnabled(TRUE);//开启事件侦听  
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触摸 

	this->schedule(schedule_selector(GameLayer::addBallUpdater));

	b2Vec2 gravity;
	gravity.Set(0.0f, -13.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContactListener(this);
 
	initWalls();
	initBarrier();
	scheduleUpdate();
	initScoreLabel();


	m_HP_Bar=Vector<Sprite*>();
	setHPBar();
	this->schedule(schedule_selector(GameLayer::secondTick),1); 





	m_doubleTime=Sprite::create("double_time.png");
	m_doubleTime->setPosition(ccp(visibleSize.width/2,visibleSize.height/2+200));
	m_doubleTime->setScale(0);
	m_doubleTime->setOpacity(130);
	addChild(m_doubleTime,999);
	CCActionInterval * tinto = CCTintTo ::create(0.5, 255, 255, 0);
	CCActionInterval * tinto1 = CCTintTo ::create(0.5, 255, 0, 0);
 
	CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(tinto,tinto1,NULL));
	CCRepeatForever* ccrepf=CCRepeatForever::create(actSeq);
	m_doubleTime->runAction(ccrepf);



	ufo=NULL;


	

 

	return TRUE;

}


void GameLayer::initWalls(){
	WINSIZE;

	b2BodyDef m_b2BodyDefLeft;
	m_b2BodyDefLeft.type = b2_staticBody;
	m_b2BodyDefLeft.position.Set(0 / PTM_RATIO, (visibleSize.height*(4/4)) / PTM_RATIO);

	b2BodyDef m_b2BodyDefRight;
	m_b2BodyDefRight.type = b2_staticBody;
	m_b2BodyDefRight.position.Set(visibleSize.width / PTM_RATIO, (visibleSize.height*(4/4)) / PTM_RATIO);
	
	b2PolygonShape  dynamicBox;
	dynamicBox.SetAsBox(10.001/PTM_RATIO,(visibleSize.height/2)/PTM_RATIO);
	

	b2Body * wallLeft = m_world->CreateBody(&m_b2BodyDefLeft);
	b2Body * wallRight = m_world->CreateBody(&m_b2BodyDefRight);


	B2UserDataBase* b2Base= new B2UserDataBase();
	b2Base->m_type=0;
	b2Base->m_UserData=NULL;

	wallLeft->SetUserData(b2Base);


	B2UserDataBase* b2Base1= new B2UserDataBase();
	b2Base1->m_type=0;
	b2Base1->m_UserData=NULL;
	wallRight->SetUserData(b2Base1);


	b2FixtureDef m_b2FixtureDef;
	m_b2FixtureDef.shape = &dynamicBox;
	m_b2FixtureDef.density = 0.00101f;
	m_b2FixtureDef.friction = 0.4001f;
	m_b2FixtureDef.restitution = 0.5001f;


	wallLeft->CreateFixture(&m_b2FixtureDef);
	wallRight->CreateFixture(&m_b2FixtureDef);
}


void GameLayer::initBarrier(){
	WINSIZE;
	CCArray* arr=(CCArray*)GLOBAL_DATA->m_cfg_block->objectForKey("data");
	CCObject* obj;
    CCARRAY_FOREACH(arr,obj){
		

		CCDictionary* dict=(CCDictionary*)obj;
		float x=dict->valueForKey("x")->floatValue();
		float y=dict->valueForKey("y")->floatValue();
		float x_scope=dict->valueForKey("x_scope")->floatValue();
		float speed=dict->valueForKey("speed")->floatValue();

		BlockBall* block1=BlockBall::create();
		block1->m_x=x;
		block1->m_y=y;
		block1->m_x_scope=x_scope;
		block1->m_speed=speed;

		block1->setPosition(ccp(x*visibleSize.width,visibleSize.height-150-y));
		addChild(block1);

		B2UserDataBase* b2Base= new B2UserDataBase();
		b2Base->m_type=2;
		b2Base->m_UserData=block1;

		b2BodyDef m_b2BodyDef;
		m_b2BodyDef.type = b2_staticBody;
		m_b2BodyDef.position.Set(x*visibleSize.width / PTM_RATIO, y / PTM_RATIO);
		b2Body * b2body = m_world->CreateBody(&m_b2BodyDef);
		b2CircleShape dynamicBox;
		dynamicBox.m_radius=30.0001/PTM_RATIO;
		b2FixtureDef m_b2FixtureDef;
		m_b2FixtureDef.shape = &dynamicBox;
		m_b2FixtureDef.density = 0.00101f;
		m_b2FixtureDef.friction = 0.4001f;
		m_b2FixtureDef.restitution = 0.9001f;
		b2body->CreateFixture(&m_b2FixtureDef);
		b2body->SetUserData(b2Base);
		block1->m_body=b2body;
     
    }



}



void GameLayer::addBall(int tp,float x ,float y){
	WINSIZE;
	auto spriteBall=Ball::create();
	spriteBall->initWithType(tp);
	spriteBall->setPosition(ccp(-1000,-1000));
	addChild(spriteBall);

	B2UserDataBase* b2Base= new B2UserDataBase();
	b2Base->m_type=1;
	b2Base->m_UserData=spriteBall;

	b2BodyDef m_b2BodyDefBall;
	m_b2BodyDefBall.type = b2_dynamicBody;
	float margin_x=visibleSize.width/5.5;
	//m_b2BodyDefBall.position.Set(  (margin_x +  (visibleSize.width-margin_x*2) * CCRANDOM_0_1() )/ PTM_RATIO, b_height / PTM_RATIO);
	m_b2BodyDefBall.position.Set(x,y);
	b2CircleShape dynamicBox;
	dynamicBox.m_radius=30.00001/PTM_RATIO;

	b2Body * ball = m_world->CreateBody(&m_b2BodyDefBall);
	ball->SetUserData(b2Base);
	
	b2FixtureDef m_b2FixtureDef;
	m_b2FixtureDef.shape = &dynamicBox;
	m_b2FixtureDef.density = 0.00101f;
	m_b2FixtureDef.friction = 0.4001f;
	m_b2FixtureDef.restitution = 0.9001f;

	ball->CreateFixture(&m_b2FixtureDef);

}

void GameLayer::addBallUpdater(float fDelta){
	WINSIZE;
	GLOBAL_DATA->m_vernier+=1.00001;
	if(GLOBAL_DATA->m_vernier_max<GLOBAL_DATA->m_vernier){
		GLOBAL_DATA->m_vernier=0;
		float margin_x=visibleSize.width/5.5;
		addBall(GLOBAL_DATA->createBallType(),(margin_x +  (visibleSize.width-margin_x*2) * CCRANDOM_0_1() )/ PTM_RATIO,visibleSize.height/PTM_RATIO);
	}
}


void GameLayer::initScoreLabel(){
	m_scoreLabel=CCLabelBMFont::create("Score:", "word1.fnt");
	m_scoreLabel->setPosition(ccp(100,100));
	addChild(m_scoreLabel,100);
	m_scoreNum=CCLabelBMFont::create("0", "word1.fnt");
	m_scoreNum->setAnchorPoint(ccp(0,0.5));
	m_scoreNum->setPosition(ccpAdd(m_scoreLabel->getPosition(),ccp(m_scoreLabel->boundingBox().size.width/2+20,0)) );
	addChild(m_scoreNum,100);
}

void GameLayer::setScoreNum(int num){
	char s_num[20];
	sprintf(s_num,"%d",num);
	m_scoreNum->setString(s_num);


}
void GameLayer::BeginContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
	B2UserDataBase* b2udbA=(B2UserDataBase*)bodyA->GetUserData();
	B2UserDataBase* b2udbB=(B2UserDataBase*)bodyB->GetUserData();

 
	bool isContainCup=FALSE;
	Ball* ballSprite=NULL;
	if(b2udbA->m_type==3 || b2udbB->m_type==3){
		isContainCup=TRUE;
		if(b2udbA->m_type==3){
			ballSprite=(Ball*)b2udbB->m_UserData;
		}else
		{
			ballSprite=(Ball*)b2udbA->m_UserData;
		}
		
	}
	if(isContainCup){
		SoundManager::sharedSoundManager()->playEffect("ball_ding");
		if(ballSprite->m_ballType==1){
			if(ballSprite->getPositionY()>cup->getPositionY()+cup->boundingBox().size.height/2.1){
				addExtLabel("danger",ccpAdd(cup->getPosition(),ccp(0,100)) ,0.5,1.2,200.0,255,100,100);
				addExtNum(6,ccpAdd(cup->getPosition(),ccp(0,100)),0.5,1.2,200.0,255,255,0,-50);
				SoundManager::sharedSoundManager()->playEffect("danger");
			}
			
		}
		
	}else
	{
		 
	}
	

	if(b2udbA->m_type==1){
		auto ballSpriteA=(Ball*)b2udbA->m_UserData;
		if(ballSpriteA->m_ballType==0){
			ballSpriteA->m_collisionCount++;
			toGreen(ballSpriteA);
			if(ballSpriteA->m_collisionCount>SHOW_GREEN_PARTICLE){
				ballSpriteA->m_partical->setVisible(TRUE);
			}
		}else
		{
			
		}
	}
	if(b2udbB->m_type==1){
		auto ballSpriteB=(Ball*)b2udbB->m_UserData;
		if(ballSpriteB->m_ballType==0){
			ballSpriteB->m_collisionCount++;
			toGreen(ballSpriteB);
			if(ballSpriteB->m_collisionCount>SHOW_GREEN_PARTICLE){
				ballSpriteB->m_partical->setVisible(TRUE);
			}
		}else
		{
			 
		}
	}
 
}
void GameLayer::toGreen(Ball* sprite){
	auto collisionCount=sprite->m_collisionCount;
	int colorRB=collisionCount*(GREEN_STEP);
	if(colorRB>-255){
		sprite->setColor(ccc3(255+colorRB,255,255+colorRB));
	}else
	{
		sprite->setColor(ccc3(0,255,0));
	}
	

}
 

void GameLayer::EndContact(b2Contact* contact)
{
    b2Body* bodyA = contact->GetFixtureA()->GetBody();
    b2Body* bodyB = contact->GetFixtureB()->GetBody();
 
}

void GameLayer::update(float fDelta){
	WINSIZE;

	float x=cup->getPositionX();

	if(x<targetX){
		if(x+TOUCH_SPEED<=targetX){
			x+=TOUCH_SPEED;
		}else
		{
			x=targetX;
		}
	}
	else
	{
		if(x-TOUCH_SPEED>targetX){
			x-=TOUCH_SPEED;
		}else
		{
			x=targetX;
		}
	}



	if(x-cup->boundingBox().size.width/2<0){
		x=cup->boundingBox().size.width/2;
	}
	if(x+cup->boundingBox().size.width/2>visibleSize.width){
		x=visibleSize.width- cup->boundingBox().size.width/2;
	}
	
	cup->setPosition1(ccp(x,250));


	 
	if(GLOBAL_DATA->m_redBallPercent<GLOBAL_DATA->m_RedBallPercentMax){
		GLOBAL_DATA->m_redBallPercent+=GLOBAL_DATA->m_RedBallPercentAddonPerFrame;
	}

	if(GLOBAL_DATA->m_vernier_max>GLOBAL_DATA->m_VernierMin){
		GLOBAL_DATA->m_vernier_max+=GLOBAL_DATA->m_VernierAddonPerFrame;
	}
	

	int velocityIterations = 10;
	int positionIterations = 8;
	m_world->Step(fDelta, velocityIterations, positionIterations);

	if(GLOBAL_DATA->m_comboTriger>0){
		GLOBAL_DATA->m_comboTriger--;
	}


	if(GLOBAL_DATA->m_comboCount>1 && GLOBAL_DATA->m_comboTriger<=0){
		addExtLabel("combo",cup->getPosition(),0.5,1.2,200.00,238,90,238);
		addExtNum(GLOBAL_DATA->m_comboCount*10,cup->getPosition(),0.5,1.2,200.00,255,0,255,-50);
		SoundManager::sharedSoundManager()->playEffect("combo");
		GLOBAL_DATA->m_comboCount=0;
	}
	


 for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext()) {
		float positionX=b->GetPosition().x*PTM_RATIO;
		float positionY=b->GetPosition().y*PTM_RATIO;
		float rotation=CC_RADIANS_TO_DEGREES(b->GetAngle());

		B2UserDataBase* b2UserDataBase=(B2UserDataBase*)b->GetUserData();
		if(b2UserDataBase->m_type==1){
			Ball* s=(Ball*)b2UserDataBase->m_UserData;
		 
			s->setPosition(ccp(positionX, positionY));
			if(s->m_ballType>10){
				s->setRotation(-1 * rotation);
			}
			
		}
		
	}

 	b2Body *node = m_world->GetBodyList();
	while( node!=NULL )
	 {
		 b2Body *body = node;
		 node = node->GetNext();
		 B2UserDataBase* b2Base=static_cast<B2UserDataBase*>(body->GetUserData());
		 if(b2Base->m_type==1){
			Ball* s=(Ball*)b2Base->m_UserData;
			if(cup->getBoundingBox1().containsPoint(s->getPosition())){
				
				if(s->m_ballType==0){
				 
					int addion=0;
					if(GLOBAL_DATA->m_doubleTime>0){
						addion=s->m_collisionCount*2;
						SoundManager::sharedSoundManager()->playEffect("under_double_ball_get");
						 
					}else{
						addion=s->m_collisionCount;
						SoundManager::sharedSoundManager()->playEffect("cup_catch_ball");
					}
					if(s->m_collisionCount>30){
						ufoComing();
					}else{
						auto __seed=CCRANDOM_0_1();
						if(__seed<0.15){
							ufoComing();
						}
					}

					

					GLOBAL_DATA->m_user_score+=addion;
					
					auto colorRB=255+(GREEN_STEP*s->m_collisionCount);
					auto scaleSize=0.5;
					if(s->m_collisionCount>16){
						scaleSize=0.8;
					}
					addExtNum(addion,cup->getPosition(),scaleSize,0.4,150.0,colorRB,255,colorRB,80);
					
					setScoreNum(GLOBAL_DATA->m_user_score);
					cup->showParticle(1);
					s->removeFromParent();
					m_world->DestroyBody(body);
					
					

					if(GLOBAL_DATA->m_comboTriger>0){
						GLOBAL_DATA->m_comboCount++;
					}
					GLOBAL_DATA->m_comboTriger=GLOBAL_DATA->m_ComboTime;
				}
				if(s->m_ballType==1){
					
					body->SetTransform(b2Vec2(
					-999 / PTM_RATIO,
					-999 / PTM_RATIO),body->GetAngle());
					GLOBAL_DATA->m_HP--;
					if(GLOBAL_DATA->m_HP<=0){
						
							setHPBar();
						gameOver();
					}else
					{
						SoundManager::sharedSoundManager()->playEffect("get_red_ball");
						setHPBar();
					}
				}

				if(s->m_ballType==11){
					GLOBAL_DATA->m_HP=0;
					setHPBar();
					gameOver();
					s->removeFromParent();
					m_world->DestroyBody(body);
 
				}

				if(s->m_ballType==12){
					SoundManager::sharedSoundManager()->playEffect("double_time");
					m_doubleTime->setScale(1);
					GLOBAL_DATA->m_doubleTime+=10;
					s->removeFromParent();
					m_world->DestroyBody(body);
 
				}

				if(s->m_ballType==13){
					SoundManager::sharedSoundManager()->playEffect("anti_red_ball");
					antiRedBallExplode();
					s->removeFromParent();
					m_world->DestroyBody(body);
 
				}

				if(s->m_ballType==14){
					SoundManager::sharedSoundManager()->playEffect("life_add");
					GLOBAL_DATA->m_HP=3;
					setHPBar();
					s->removeFromParent();
					m_world->DestroyBody(body);
 
				}


			}else
			{
				if(s->getPositionY()<-200){
					s->removeFromParent();
					m_world->DestroyBody(body);
					break;
				}
			}
		 }
	}
}

void GameLayer::addExtLabel(std::string labelStr, Point p,float scale,float during,float height, int r,int g,int b){
	WINSIZE;
	auto extLabel=CCLabelBMFont::create(labelStr, "panel_font.fnt");
	extLabel->setPosition(p);
	extLabel->setScale(scale);
	extLabel->setColor(ccc3(r,g,b));
	addChild(extLabel);
	CCActionInterval* ca1=CCMoveBy::create(during,ccp(0,height));
	CCActionInterval* ca2=CCFadeOut::create(0.3);
    CCCallFuncN* cb3=CCCallFuncN::create(this,callfuncN_selector(GameLayer::animationEndAndRemoveCallback)); 
    CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca1,ca2,cb3,NULL));
    extLabel->runAction(actSeq);

}


void GameLayer::addExtNum(int num ,Point p,float scale,float during,float height, int r,int g,int b,float margin_bottom){
	WINSIZE;
	char s_num[30];
	sprintf(s_num,"+%d",num);
	auto extLabel=CCLabelBMFont::create(s_num, "panel_font.fnt");
	extLabel->setScale(scale);
	extLabel->setPosition(ccpAdd(p,ccp(0,margin_bottom)));
	extLabel->setColor(ccc3(r,g,b));
	addChild(extLabel);
	CCActionInterval* ca1=CCMoveBy::create(during,ccp(0,height));
	CCActionInterval* ca2=CCFadeOut::create(0.3);
    CCCallFuncN* cb3=CCCallFuncN::create(this,callfuncN_selector(GameLayer::animationEndAndRemoveCallback)); 
    CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca1,ca2,cb3,NULL));
    extLabel->runAction(actSeq);
	GLOBAL_DATA->m_user_score+=6;
	setScoreNum(GLOBAL_DATA->m_user_score);
}



void GameLayer::animationEndAndRemoveCallback(CCNode* c){
	c->removeFromParent();

}

void GameLayer::initCup(){
	cup=Cup::create();
	cup->addToLayer();
	cup->setPosition1(ccp(300,250));
	targetX=300;
}




void GameLayer::onEnter(){
	Layer::onEnter();
	initCup();
	GLOBAL_DATA->initNumberic();

	CCActionInterval * tinto = CCTintTo ::create(1, 255, 255, 0);
	CCActionInterval * tinto1 = CCTintTo ::create(1, 255, 0, 0);
	CCActionInterval * tinto2 = CCTintTo ::create(1, 0, 255, 0);
	CCActionInterval * tinto3 = CCTintTo ::create(1, 0, 255, 255);
	CCActionInterval * tinto4 = CCTintTo ::create(1, 255, 0, 255);
	CCActionInterval * tinto5 = CCTintTo ::create(1, 255, 255, 255);
	CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(tinto,tinto1,tinto2,tinto3,tinto4,tinto5,NULL));
	CCRepeatForever* ccrepf=CCRepeatForever::create(actSeq);
	cup->runAction(ccrepf);
	setHPBar();
	initVolume();

}




void GameLayer::onExit(){
	Layer::onExit();
}

 

GameLayer::GameLayer(void)
{

}

bool GameLayer::onTouchBegan(Touch* pTouch, Event* pEvent){
	CCPoint cp = pTouch->getLocation();
	targetX=cp.x;
	return TRUE;
}


void GameLayer::onTouchMoved(Touch* pTouch, Event* pEvent){
	WINSIZE;
	CCPoint cp = pTouch->getLocation();
	targetX=cp.x;
}



void GameLayer::onTouchEnded(Touch* pTouch, Event* pEvent){
	CCPoint cp = pTouch->getLocation();
	targetX=cp.x;
}



void GameLayer::againClick(Ref *pSender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
		auto gameScence= GameScence::create();
		auto director = Director::getInstance();
		director->replaceScene(TransitionCrossFade::create(0.34f, gameScence));
		SoundManager::sharedSoundManager()->playEffect("btn_press");
	}


}

void GameLayer::shareClick(Ref *pSender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED)
	{
	 SoundManager::sharedSoundManager()->playEffect("btn_press");
	 GLOBAL_DATA->m_isAutoShareShowed=1;
	}
}



void GameLayer::gameOver(){
	WINSIZE;

	SoundManager::sharedSoundManager()->playEffect("cup_break");
	Telegraph::sharedTelegraph()->sendWithUserDefault("21",GLOBAL_DATA->getScore(),"");

	this->unscheduleAllSelectors();
	setTouchEnabled(FALSE); 
	layout= static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Panel/Export/CatchTheBallPanel/CatchTheBallPanel.json"));
	auto layoutSize=layout->getContentSize();
	layout->setPosition(CCPoint( visibleSize.width / 2-layoutSize.width/2, visibleSize.height / 2-layoutSize.height/2));
	addChild(layout,9999);
	bool isNewRecord=FALSE;
	if(GLOBAL_DATA->m_user_score>GLOBAL_DATA->m_user_best){
		GLOBAL_DATA->m_user_best=GLOBAL_DATA->m_user_score;
		GLOBAL_DATA->saveFile();
		isNewRecord=TRUE;
	}

 	 
	ui::TextAtlas* textTip = static_cast<TextAtlas*>(Helper::seekWidgetByName(layout, "Label_Tip"));
	CCActionInterval* ca0=CCDelayTime::create(0.5);
	CCActionInterval* ca1=CCScaleTo::create(0.2,1.5);
	CCActionInterval* ca2=CCScaleTo::create(0.2,1.0);
	CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca0,ca1,ca2,NULL));
	textTip->runAction(actSeq);

	ui::TextAtlas* textScore = static_cast<TextAtlas*>(Helper::seekWidgetByName(layout, "AtlasLabel_Score"));
	textScore->setString(GLOBAL_DATA->getScore());

	ui::TextAtlas* textBest = static_cast<TextAtlas*>(Helper::seekWidgetByName(layout, "AtlasLabel_Best"));
	textBest->setString(GLOBAL_DATA->getBest());
 


	ui::Button* againBtn = static_cast<Button*>(Helper::seekWidgetByName(layout, "Button_Again"));
	againBtn->addTouchEventListener(this, toucheventselector(GameLayer::againClick));


	ui::Button* shareBtn = static_cast<Button*>(Helper::seekWidgetByName(layout, "Button_Share"));
	shareBtn->addTouchEventListener(this, toucheventselector(GameLayer::shareClick));
	
	if(isNewRecord){
		showNewRecord(textBest);
	}

}


void GameLayer::showNewRecord(CCNode* node){
	Sprite* newRecordSprite=Sprite::create("newrecordbg.png");
	newRecordSprite->setRotation(-45);
	newRecordSprite->setScale(0.8);
	auto p=node->getPosition();
	p=ccpAdd(p,ccp(-200,200));
	newRecordSprite->setPosition(p);
	node->getParent()->addChild(newRecordSprite);
	CCParticleSystem* particle= ParticleSystemQuad::create("newrecord.plist");
	particle->setPosition(p);
	node->getParent()->addChild(particle); //p


	if(GLOBAL_DATA->m_autoShareShow==101){
		if(GLOBAL_DATA->m_isAutoShareShowed==0){
			GLOBAL_DATA->m_isAutoShareShowed=1;
			//show
		}
	}
}

void GameLayer::setHPBar(){
	WINSIZE;
	int hp=GLOBAL_DATA->m_HP;
 
	for(int _i=0;_i<m_HP_Bar.size();_i++){
		m_HP_Bar.at(_i)->removeFromParent();
	}
	m_HP_Bar.clear();
 

	for(int i=0;i<hp;i++){
		Sprite* heart=Sprite::create("heart.png");
		heart->setPosition(ccp(visibleSize.width-(m_HP_Bar.size()*80+60),100));
		addChild(heart);
		m_HP_Bar.pushBack(heart);
	}

}

void GameLayer::secondTick(float d){
	if(GLOBAL_DATA->m_doubleTime>0){
		GLOBAL_DATA->m_doubleTime=GLOBAL_DATA->m_doubleTime-1;
	
	}else{
		GLOBAL_DATA->m_doubleTime=0;
		m_doubleTime->setScale(0);
	}
}

void GameLayer::antiRedBallExplode(){
	CCParticleSystem* particle= ParticleSystemQuad::create("user_bomb_aobao.plist");
	particle->setPosition(cup->getPosition());
	addChild(particle);

	b2Body *node = m_world->GetBodyList();
	while( node!=NULL )
	 {
		 b2Body *body = node;
		 node = node->GetNext();
		 B2UserDataBase* b2Base=static_cast<B2UserDataBase*>(body->GetUserData());
		 if(b2Base->m_type==1){
			 
			 Ball* s=(Ball*)b2Base->m_UserData;
			 if(s->m_ballType==1){
				body->SetTransform(b2Vec2(
				-999 / PTM_RATIO,
				-999 / PTM_RATIO),body->GetAngle());
			 } 
		 }
	}
}

void GameLayer::ufoComing(){
	WINSIZE;
	ufo=UFO::create();
	ufo->initWithType(GLOBAL_DATA->getRandomBetween(0,9));
	ufo->startShake();
	addChild(ufo,999);

	auto seed=CCRANDOM_0_1();
	if(seed<0.5){
		ufo->setPosition(ccp(- ufo->getBoundingBox().size.width,  visibleSize.height-ufo->getBoundingBox().size.height/2-CCRANDOM_0_1()*ufo->getBoundingBox().size.height));
		CCActionInterval* ca=CCMoveBy::create(4,ccp(visibleSize.width+ufo->getBoundingBox().size.width*2,0));
		CCCallFuncN* cb=CCCallFuncN::create(this,callfuncN_selector(GameLayer::ufoMoveOut)); // void userSelectedQuanCallback(CCNode* c);
		CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca,cb,NULL));
		ufo->runAction(actSeq);
	}else
	{
		ufo->setPosition(ccp( visibleSize.width,visibleSize.height-ufo->getBoundingBox().size.height/2-CCRANDOM_0_1()*ufo->getBoundingBox().size.height));
		CCActionInterval* ca=CCMoveBy::create(4,ccp(-visibleSize.width-ufo->getBoundingBox().size.width*2,0));
		CCCallFuncN* cb=CCCallFuncN::create(this,callfuncN_selector(GameLayer::ufoMoveOut)); // void userSelectedQuanCallback(CCNode* c);
		CCActionInterval* actSeq=(CCActionInterval*)(CCSequence::create(ca,cb,NULL));
		ufo->runAction(actSeq);
	}
	auto _seed=GLOBAL_DATA->getRandomBetween(0,4);
	auto count=0;
	auto _ball_type=0;
	switch (_seed)
	{
	case 0:count=GLOBAL_DATA->getRandomBetween(3,7);_ball_type=11;break;
	case 1:count=GLOBAL_DATA->getRandomBetween(3,5);_ball_type=12;break;
	case 2:count=GLOBAL_DATA->getRandomBetween(3,6);_ball_type=13;break;
	case 3:count=GLOBAL_DATA->getRandomBetween(3,5);_ball_type=14;break;
	default:
		break;
	}
	ufo->type=_ball_type;

	if(count<=0){count=2;}
	ufo->count=count;
	
	ufo->startDrop();


	auto __soundSeed=CCRANDOM_0_1();
	if(__soundSeed>0.5){
		SoundManager::sharedSoundManager()->playEffect("ufo_0");
	}else
	{
		SoundManager::sharedSoundManager()->playEffect("ufo_1");
	}
}

void GameLayer::initVolume(){
	WINSIZE;
	m_volume= static_cast<Layout*>(cocostudio::GUIReader::getInstance()->widgetFromJsonFile("Volume/Export/Volume_1/Volume_1.json"));
	auto layoutSize=m_volume->getContentSize();
	m_volume->setPosition(CCPoint( visibleSize.width - m_volume->getBoundingBox().size.width/2-60, visibleSize.height-120));
	addChild(m_volume,9999);

 
	m_VolumeBtn = static_cast<Button*>(Helper::seekWidgetByName(m_volume, "Button_Volume"));
	m_VolumeBtn->addTouchEventListener(this, toucheventselector(GameLayer::volumeClick));

	if(GLOBAL_DATA->m_volume){
			 
			m_VolumeBtn->loadTextureNormal("volume.png");
			
		}else{
			m_VolumeBtn->loadTextureNormal("volume_close.png");
		}

}

void GameLayer::volumeClick(Ref *pSender, TouchEventType type){
	if (type == TOUCH_EVENT_ENDED){
		GLOBAL_DATA->m_volume=!GLOBAL_DATA->m_volume;
		GLOBAL_DATA->saveFile();
		if(GLOBAL_DATA->m_volume){
			SoundManager::sharedSoundManager()->playEffect("btn_press");
			m_VolumeBtn->loadTextureNormal("volume.png");
			
		}else{
			m_VolumeBtn->loadTextureNormal("volume_close.png");
		}
	}


}

void GameLayer::ufoMoveOut(CCNode* c){

 
		c->removeFromParent();
 
	 
}


GameLayer::~GameLayer(void)
{

}



#endif // _GameLayer_CPP_

