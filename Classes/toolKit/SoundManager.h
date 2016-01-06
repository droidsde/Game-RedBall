#ifndef  _SoundManager_H_
#define  _SoundManager_H_

#include "cocos2d.h"
#include "cocos-ext.h"
#include "user-macros.h"

USING_NS_CC;
USING_NS_CC_EXT;


class SoundManager
{
public:

	static SoundManager* sharedSoundManager(void);

	SoundManager(void);
	unsigned int playEffect(const char* soundid, bool bLoop, float pitch, float pan, float gain);
	unsigned int playEffect(const char* soundid);
	void stopEffect(unsigned int sid);

	void playBg(const char* soundid, bool bLoop);
	void playBg(const char* soundid);

	std::string getSoundAbsolutePath(const char* soundid);
	std::string m_SoundType;
 
	~SoundManager(void);

};
#endif // _SoundManager_H_

