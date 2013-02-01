//
//  sampleAppDelegate.cpp
//  sample
//
//  Created by Karim DRIDI on 1/2/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "AppLevelHelper.h"
#include "LHSettings.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize s = CCEGLView::sharedOpenGLView()->getFrameSize();
    if (s.width == 480 || s.height == 480) {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("sd");
        pDirector->setContentScaleFactor(1.0f);
    } else if (s.width == 640 || s.height == 640) {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        pDirector->setContentScaleFactor(2.0f);
    } else if (s.width == 1024 || s.height == 1024) {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("hd");
        pDirector->setContentScaleFactor(2.0f);
    } else if (s.width == 2048 || s.height == 2048) {
        CCFileUtils::sharedFileUtils()->setResourceDirectory("ipadhd");
        pDirector->setContentScaleFactor(4.0f);
    }

    // turn on display FPS
    pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // run Level Helper scene.
    this->runLevel("01.plhs");

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}

void AppDelegate::runLevel(const char *file) {
    CCScene *pScene = AppLevelHelper::scene(file);
    CCDirector *pDirector = CCDirector::sharedDirector();
    if (pDirector->getRunningScene()) {
        pDirector->replaceScene(pScene);
    } else {
        pDirector->runWithScene(pScene);
    }
}