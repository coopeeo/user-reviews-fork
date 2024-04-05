#pragma once

#include <Geode/Geode.hpp>
#include <Geode/utils/web.hpp>
#include <Geode/ui/TextInput.hpp>
#include <matjson.hpp>
#include "ProfileReview.hpp"

using namespace geode::prelude;


class IconGetter : public UserInfoDelegate {
protected:

    static IconGetter* s_shared;

    GameLevelManager* m_glmgr;
    int m_accountID;
    //UserInfoDelegate* const m_oldUID;
    CCMenu* m_playerbundle;
    SimplePlayer* m_playericon;
    CCLabelBMFont* m_playername;

    void resetUID() {}//m_glmgr->m_userInfoDelegate = m_oldUID;}
    
    int getIcon(GJUserScore* score) {
        IconType type = score->m_iconType;
        switch(type) {
            default: return score->m_playerCube;
            case IconType::Cube: return score->m_playerCube;
            case IconType::Ship: return score->m_playerShip;
            case IconType::Ball: return score->m_playerBall;
            case IconType::Ufo: return score->m_playerUfo;
            case IconType::Wave: return score->m_playerWave;
            case IconType::Robot: return score->m_playerRobot;
            case IconType::Spider: return score->m_playerSpider;
            case IconType::Swing: return score->m_playerSwing; 
            case IconType::Jetpack: return score->m_playerJetpack;
    }
}

public:

    IconGetter() {log::debug("make shared thing of icongetter");}
    ~IconGetter() {}

    static IconGetter* shared();
    

    void setStuff(int accid, CCMenu* pbun) { // old: UserInfoDelegate* olduid, CCMenu* pbun) {
        m_accountID = accid;
        // m_oldUID = olduid;
        m_playerbundle = pbun;
        m_glmgr = GameLevelManager::sharedState();
        m_playericon = static_cast<SimplePlayer*>(pbun->getChildByID("playericon"));
        m_playername = static_cast<CCLabelBMFont*>(pbun->getChildByID("playername"));
        m_glmgr->getGJUserInfo(accid);
    }
    

    // Functions for UserInfoDelegate!
    void getUserInfoFinished(GJUserScore* score) {
        log::info("GetUserInfoFinished Started");
        log::info("{}", score->m_color1);
        log::info("{}", score->m_color2);
        log::info("{}", score->m_color3);
        auto gmgr = GameManager::sharedState();
        m_playericon->updatePlayerFrame(getIcon(score), static_cast<IconType>(score->m_iconType));
        m_playericon->setColor(gmgr->colorForIdx(score->m_color1));
		m_playericon->setSecondColor(gmgr->colorForIdx(score->m_color2));
		m_playericon->setGlowOutline(gmgr->colorForIdx(score->m_color3));
		m_playericon->enableCustomGlowColor(gmgr->colorForIdx(score->m_color3));
        if(!score->m_glowEnabled) m_playericon->disableGlowOutline();
        resetUID();
    }

    void getUserInfoFailed(int) {
        log::info("GetUserInfoFailed Started");
        auto gmgr = GameManager::sharedState();
        m_playericon->updatePlayerFrame(1, IconType::Cube);
        m_playericon->setColor(gmgr->colorForIdx(1));
		m_playericon->setSecondColor(gmgr->colorForIdx(3));
        m_playericon->disableGlowOutline();
        resetUID();
    }


    void userInfoChanged(GJUserScore* score) {
        log::info("UserInfoChanged Started");
        // do nothing
    }
    
    CCMenu* getPlayerBundle() const {return m_playerbundle;}

        



};