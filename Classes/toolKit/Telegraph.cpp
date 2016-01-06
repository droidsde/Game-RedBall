#ifndef  _Telegraph_CPP_
#define  _Telegraph_CPP_


#include "Telegraph.h"
#include "GlobalRunTimeData.h"
#include "user-macros.h"
#include "UriHelper.h"


USING_NS_CC;
USING_NS_CC_EXT;

using namespace cocos2d::network;

#define DC_URL "http://dcrecord.sinaapp.com/dctest/?di=%s&uuid=%s&status=%s&lang=%s&auto=%s&rid=%s&rv=%s&&misc=%s"

static Telegraph* m_telegraph=NULL;

Telegraph* Telegraph::sharedTelegraph(){
	 if (!m_telegraph)
    {
		m_telegraph = new Telegraph();
    }
    return m_telegraph;
}

Telegraph::Telegraph(void){}
Telegraph::~Telegraph(void){}


void Telegraph::send1(std::string url){
	
	HttpRequest* request = new HttpRequest();
	// required fields
	request->setUrl(url.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(Telegraph::onHttpRequestCompleted));
	// optional fields                            
	request->setTag("GET_test2");

	HttpClient::getInstance()->send(request);

	//// don't forget to release it, pair to new
	request->release();

}


void Telegraph::send(std::string deviceInfo, std::string UUID,std::string status,std::string lang,std::string autoStr, std::string recordId, std::string recordValue, std::string misc) {
	char dc_data[256];
	sprintf(dc_data, DC_URL, deviceInfo.c_str(), UUID.c_str(), status.c_str(),lang.c_str(),autoStr.c_str(), recordId.c_str(), recordValue.c_str(), misc.c_str());
	HttpRequest* request = new HttpRequest();
	// required fields
	request->setUrl(dc_data);
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback(this, httpresponse_selector(Telegraph::onHttpRequestCompleted));
	// optional fields                            
	request->setTag("GET_test2");

	HttpClient::getInstance()->send(request);

	//// don't forget to release it, pair to new
	request->release();
}


void Telegraph::sendWithUserDefault(std::string recordId, std::string recordValue, std::string misc){
    
    this->send(
               UriHelper::sharedUriHelper()->urlencode(GLOBAL_DATA->m_device),
               GLOBAL_DATA->m_uuid,
               "1",
               GLOBAL_DATA->m_lang,
               "2015",
               recordId,
               recordValue,
               misc)
    ;
}

void Telegraph::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	log("response code: %ld", statusCode);

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	std::string str(buffer->begin(), buffer->end());

	CCUserDefault* userDefault=CCUserDefault::sharedUserDefault();
	if (str=="100"){
		userDefault->setIntegerForKey("autoShareShow", 100);
		GLOBAL_DATA->m_autoShareShow=100;
		userDefault->flush();
	 
	}else if(str=="101"){
		userDefault->setIntegerForKey("autoShareShow", 101);
		GLOBAL_DATA->m_autoShareShow=101;
		userDefault->flush();
	}
		
	printf("\n");
}




#endif // _Telegraph_CPP_

