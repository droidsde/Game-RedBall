#ifndef  _GameScence_CPP_
#define  _GameScence_CPP_

#include "GameScence.h"
#include "Telegraph.h"
USING_NS_CC;
USING_NS_CC_EXT;

static GameScence *m_Curent_GameScence = NULL;

GameScence* GameScence::sharedGameScence(void)
{
    return m_Curent_GameScence;
}

bool GameScence::init(){

	if ( !Scene::init() )
	{
		return FALSE;
	}
	
	m_Curent_GameScence=this;
	gameLayer = GameLayer::create();
	gameLayer->retain();
	addChild(GameScence::sharedGameScence()->gameLayer);
	

	return TRUE;

}

void GameScence::onEnter(){
	Scene::onEnter();
	
}




void GameScence::onExit(){
 
	Scene::onExit();
}

 

GameScence::GameScence(void)
{
}


GameScence::~GameScence(void)
{
}



#endif // _GameScence_CPP_

