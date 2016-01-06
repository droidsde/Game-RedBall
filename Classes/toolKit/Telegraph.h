#ifndef  _Telegraph_H_
#define  _Telegraph_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"

USING_NS_CC;
USING_NS_CC_EXT;

class Telegraph : public cocos2d::CCObject
{
public:
	static Telegraph* sharedTelegraph();
    
	void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
    
	void send(std::string deviceInfo, std::string UUID,std::string status,std::string lang,std::string autoStr, std::string recordId, std::string recordValue, std::string misc);
    void send1(std::string url);
	void sendWithUserDefault(std::string recordId, std::string recordValue, std::string misc);
    //void (*fp)(std::string);
	Telegraph(void);
	~Telegraph(void);
	bool m_TelegtaphStatus;

	CCArray* m_LogArray;
};


#endif // _Telegraph_H_

