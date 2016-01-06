//
//  UriHelper.h
//  NoOneCanLive
//
//  Created by 王少星 on 14-7-24.
//
//

#ifndef __NoOneCanLive__UriHelper__
#define __NoOneCanLive__UriHelper__

#include "cocos2d.h"

class UriHelper
{
public:
	static UriHelper* sharedUriHelper();
    std::string char2hex(char dec);
    std::string urlencode(const std::string &c);
	UriHelper(void){};
	~UriHelper(void){};
 
};


#endif /* defined(__NoOneCanLive__UriHelper__) */
