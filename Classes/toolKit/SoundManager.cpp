#ifndef  _SoundManager_CPP_
#define  _SoundManager_CPP_

#include "SoundManager.h"
#include "SimpleAudioEngine.h"
#include "GlobalRunTimeData.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;

static SoundManager *m_SoundManager = NULL;

SoundManager* SoundManager::sharedSoundManager(void)
{
    
	 if (!m_SoundManager)
    {
		m_SoundManager =new SoundManager();
		m_SoundManager->m_SoundType="wav";
		#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
            m_SoundManager->m_SoundType="wav";
        #endif

    }
    return m_SoundManager;
}


unsigned int SoundManager::playEffect(const char* soundid, bool bLoop, float pitch, float pan, float gain){

	auto _sid=SimpleAudioEngine::getInstance()->playEffect(getSoundAbsolutePath(soundid).c_str(), bLoop, pitch, pan, gain);
	return _sid;

}
  
unsigned int SoundManager::playEffect(const char* soundid){
	if(GLOBAL_DATA->m_volume){
		auto _sid=SimpleAudioEngine::getInstance()->playEffect(getSoundAbsolutePath(soundid).c_str());
		return _sid;
	}
	return 0;
	

}

void SoundManager::playBg(const char* soundid, bool bLoop){

	SimpleAudioEngine::getInstance()->playBackgroundMusic(getSoundAbsolutePath(soundid).c_str(), bLoop);
	

}
  
void SoundManager::playBg(const char* soundid){
	SimpleAudioEngine::getInstance()->playEffect(getSoundAbsolutePath(soundid).c_str());
}

void SoundManager::stopEffect(unsigned int sid ){
	SimpleAudioEngine::getInstance()->stopEffect(sid); 
}


std::string SoundManager::getSoundAbsolutePath(const char* soundid){
	char absp[50];
	sprintf(absp,"gameSound/%s/%s.%s",m_SoundType.c_str(),soundid,m_SoundType.c_str());
	return absp;
}

SoundManager::SoundManager(void)
{
}


SoundManager::~SoundManager(void)
{
}



#endif // _SoundManager_CPP_

