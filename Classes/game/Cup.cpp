#ifndef  _Cup_CPP_
#define  _Cup_CPP_

#include "Cup.h"
#include "GameScence.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool Cup::init(){

	if ( !Sprite::init() )
	{
		return FALSE;
	}

	
	 
	return TRUE;

}

void Cup::onEnter(){
	Sprite::onEnter();
 
}




void Cup::onExit(){
	Sprite::onExit();
}
 
void Cup::addToLayer(){

	WINSIZE;
	auto gameScence= GameScence::sharedGameScence();
	this->setPosition(ccp(400,300));

	this->initWithFile("cup.png");
	gameScence->gameLayer->addChild(this);
 
	m_b2BodyDefLeft.type = b2_staticBody;
	m_b2BodyDefLeft.position.Set((this->getPositionX()-this->getBoundingBox().size.width/2) / PTM_RATIO, (this->getPositionY()-this->boundingBox().size.height/2) / PTM_RATIO);
	m_b2BodyDefLeft.bullet=true;
 
	m_b2BodyDefRight.type = b2_staticBody;
	m_b2BodyDefRight.position.Set((this->getPositionX()+ this->getBoundingBox().size.width/2)/ PTM_RATIO, (this->getPositionY()-this->boundingBox().size.height/2) / PTM_RATIO);
	m_b2BodyDefRight.bullet=true;
 
	b2PolygonShape  dynamicBox;
	dynamicBox.SetAsBox(1.001/PTM_RATIO,this->boundingBox().size.height/PTM_RATIO);
	
	
	wallLeft = gameScence->gameLayer->m_world->CreateBody(&m_b2BodyDefLeft);
	wallRight = gameScence->gameLayer->m_world->CreateBody(&m_b2BodyDefRight);

 

	B2UserDataBase* b2Base= new B2UserDataBase();
	b2Base->m_type=3;
	b2Base->m_UserData=NULL;

	wallLeft->SetUserData(b2Base);


	B2UserDataBase* b2Base1= new B2UserDataBase();
	b2Base1->m_type=3;
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


void Cup::setPosition1(Point p){
	this->setPosition(p);
	wallLeft->SetTransform(b2Vec2((p.x-this->boundingBox().size.width/2)/PTM_RATIO,(this->getPositionY()-this->boundingBox().size.height/2) / PTM_RATIO),wallLeft->GetAngle());
	wallRight->SetTransform(b2Vec2((p.x+this->boundingBox().size.width/2)/PTM_RATIO,(this->getPositionY()-this->boundingBox().size.height/2) / PTM_RATIO),wallLeft->GetAngle());
}

void Cup::showParticle(int id){
	if(id == 1){
		CCParticleSystem* particle=ParticleSystemQuad::create("star0.plist");
		particle->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2+100));
		particle->setPositionType(kCCPositionTypeRelative);
		addChild(particle);
	}

	if(id == 2){
		CCParticleSystem* particle=ParticleExplosion::create();
		particle->setPosition(ccp(this->getContentSize().width/2,this->getContentSize().height/2));
		particle->setPositionType(kCCPositionTypeRelative);
		//addChild(particle);
	}
}

Rect Cup::getBoundingBox1(){
	auto size=this->getBoundingBox();
	return CCRectMake(getPositionX()-size.size.width/2+15,getPositionY()-50,size.size.width-30,size.size.height/2);

}
Cup::Cup(void)
{
}


Cup::~Cup(void)
{
}



#endif // _Cup_CPP_

