#ifndef  _GlobalRunTimeData_CPP_
#define  _GlobalRunTimeData_CPP_

#include "GlobalRunTimeData.h"

USING_NS_CC;


static GlobalRunTimeData *m_GlobalRunTimeData = NULL;

GlobalRunTimeData* GlobalRunTimeData::sharedGlobalRunTimeData(void)
{
    
	 if (!m_GlobalRunTimeData)
    {
		m_GlobalRunTimeData =new GlobalRunTimeData();
		m_GlobalRunTimeData->loadFile();
    }
    return m_GlobalRunTimeData;
}

 

void GlobalRunTimeData::loadFile(){
	CCUserDefault* userDefault=CCUserDefault::sharedUserDefault();
	m_uuid=userDefault->getStringForKey("uuid", "none");
    m_device=userDefault->getStringForKey("device", "none");
    m_lang=userDefault->getStringForKey("lang", "none");
	m_user_best=userDefault->getIntegerForKey("best", 0);
	m_autoShareShow=userDefault->getIntegerForKey("autoShareShow", 100);
	m_volume=userDefault->getBoolForKey("m_volume", TRUE);
	
}


void GlobalRunTimeData::saveFile(){

	CCUserDefault* userDefault=CCUserDefault::sharedUserDefault();
	userDefault->setIntegerForKey("best", m_user_best);
	userDefault->setBoolForKey("m_volume", m_volume);
 
	userDefault->flush();
}


GlobalRunTimeData::GlobalRunTimeData(void)
{


	m_cfg_block=CCDictionary::createWithContentsOfFile("CFG_block.plist");
	m_cfg_block->retain();

	m_const_var=CCDictionary::createWithContentsOfFile("CFG_const.plist");
	m_const_var->retain();

	m_autoShareShow=100;
	m_isAutoShareShowed=0;

	initNumberic();
}
void GlobalRunTimeData::initNumberic(){
	m_comboTriger=0;
	m_comboCount=0;

	m_user_score=0;
	m_vernier=0;
	

	m_HP=3;
	m_doubleTime=0;
	m_vernier_max=m_const_var->valueForKey("VernierMaxStart")->floatValue();
	m_redBallPercent=m_const_var->valueForKey("RedBallPercentStart")->floatValue();

 

	m_ComboTime=m_const_var->valueForKey("COMBO_TIME")->intValue();
	m_RedBallPercentAddonPerFrame=m_const_var->valueForKey("RedBallPercentAddonPerFrame")->floatValue();
	m_RedBallPercentMax=m_const_var->valueForKey("RedBallPercentMax")->floatValue();
	m_VernierAddonPerFrame=m_const_var->valueForKey("VernierAddonPerFrame")->floatValue();
	m_VernierMin=m_const_var->valueForKey("VernierMin")->floatValue();






}

int GlobalRunTimeData::createBallType(){
	float seed=CCRANDOM_0_1();
	int tp=0;
	if(seed<m_redBallPercent){
		tp=1;
	}
	return tp;
}
GlobalRunTimeData::~GlobalRunTimeData(void)
{
}



#endif // _GlobalRunTimeData_CPP_

