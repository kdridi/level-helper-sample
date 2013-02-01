//
//  AppLevelHelper.cpp
//  sample
//
//  Created by Karim DRIDI on 1/2/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "AppLevelHelper.h"
#include "AppDebugDraw.h"

using namespace cocos2d;

bool AppLevelHelper::init(const char *file) {
    CC_SAFE_DELETE(mLoader);
    CC_SAFE_DELETE(mWorld);
    CC_SAFE_DELETE(mDraw);
    
    if (!CCLayer::init()) {
        return false;
    }
    
    if (!file) {
        return false;
    }
    
    uint32 flags = 0;
    flags += 1 * b2Draw::e_shapeBit;
    flags += 1 * b2Draw::e_jointBit;
    flags += 1 * b2Draw::e_aabbBit;
    flags += 1 * b2Draw::e_pairBit;
    flags += 1 * b2Draw::e_centerOfMassBit;
    
    mDraw = new GLESDebugDraw( LevelHelperLoader::meterRatio() );
    if (!mDraw) {
        return false;
    }
    mDraw->SetFlags(flags);
    
    mWorld = new b2World(b2Vec2_zero);
    if (!mWorld) {
        return false;
    }
    mWorld->SetAllowSleeping(true);
    mWorld->SetContinuousPhysics(true);
    mWorld->SetDebugDraw(mDraw);
    
    mLoader = new LevelHelperLoader(file);
    if (!mLoader) {
        return false;
    }
    mLoader->addObjectsToWorld(mWorld, this);
    mLoader->createGravity(mWorld);
    mLoader->createPhysicBoundaries(mWorld);

    scheduleUpdate();
    
    return true;
}

AppLevelHelper *AppLevelHelper::create(const char *file) {
    AppLevelHelper *result = new AppLevelHelper();
    if (result && result->init(file)) {
        result->autorelease();
    } else {
        CC_SAFE_DELETE(result);
    }
    return result;
}

void AppLevelHelper::draw() {
    CCLayer::draw();
    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
    kmGLPushMatrix();
    mWorld->DrawDebugData();
    kmGLPopMatrix();
}

void AppLevelHelper::update(float dt) {
    int velocityIterations = 8;
    int positionIterations = 1;
    
    mWorld->Step(dt, velocityIterations, positionIterations);
    for (b2Body* b = mWorld->GetBodyList(); b; b = b->GetNext()) {
        if (b->GetUserData() != NULL) {
            CCSprite *sprite = (CCSprite *) b->GetUserData();
            sprite->setPosition(LevelHelperLoader::metersToPoints(b->GetPosition()));
            sprite->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
        }
    }
}


CCScene* AppLevelHelper::scene(const char *file)
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = AppLevelHelper::create(file);
    if (layer) {
        scene->addChild(layer);
    }
    
    return scene;
}
