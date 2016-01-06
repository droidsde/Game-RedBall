#ifndef  _EntryScence_CPP_
#define  _EntryScence_CPP_

#include "EntryScence.h"
#include "Telegraph.h"

USING_NS_CC;
USING_NS_CC_EXT;


bool EntryScence::init(){

	if ( !Scene::init() )
	{
		return FALSE;
	}
	GLOBAL_DATA;
	EntryLayer* entryLayer = EntryLayer::create();
	addChild(entryLayer);
 
	return TRUE;

}

void EntryScence::onEnter(){
	Scene::onEnter();
}




void EntryScence::onExit(){
 
	Scene::onExit();
}


EntryScence::EntryScence(void)
{
}


EntryScence::~EntryScence(void)
{
}



#endif // _EntryScence_CPP_

