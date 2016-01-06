#ifndef  _GlobalRunTimeData_H_
#define  _GlobalRunTimeData_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"
#include "user-macros.h"

using namespace std;
using namespace cocos2d;
using namespace cocostudio;
using namespace ui;

class GlobalRunTimeData 
{

public:
	//void saveToFile();
	//void loadFromFile();

	GlobalRunTimeData(void);
 
	~GlobalRunTimeData(void);
	static GlobalRunTimeData* sharedGlobalRunTimeData(void);
	void loadFile();
	void saveFile();
	int createBallType();


	std::string m_uuid;
    std::string m_device;
    std::string m_lang;


	float m_vernier;
	float m_vernier_max;
	int m_user_score;
	int m_user_best;
	float m_redBallPercent;
	
	int m_comboTriger;
	int m_comboCount;

	void initNumberic();
	CCDictionary* m_cfg_block;
	CCDictionary* m_const_var;

	int m_ComboTime;
	float m_RedBallPercentAddonPerFrame;
	float m_RedBallPercentMax;
	float m_VernierAddonPerFrame;
	float m_VernierMin;
	

	int m_autoShareShow;
	int m_isAutoShareShowed;

	std::string getScore(){
		char score[20];
		sprintf(score,"%d",m_user_score);
		return score;
	}

	std::string getBest(){
		char best[20];
		sprintf(best,"%d",m_user_best);
		return best;
	}

	int getRandomBetween(int a , int b){
		auto seed=(int)(CCRANDOM_0_1()*(b-a));
		int result=a+seed;
		return result;
	}



	//----------------



	int m_HP;
	int m_doubleTime;

	bool m_volume;

};
#endif // _GlobalRunTimeData_H_

