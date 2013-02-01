//
//  AppLevelHelper.h
//  sample
//
//  Created by Karim DRIDI on 1/2/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

#include "LevelHelperLoader.h"

class AppLevelHelper : public cocos2d::CCLayer {
    inline AppLevelHelper() : CCLayer(), mDraw(NULL), mWorld(NULL), mLoader(NULL) {}
    inline ~AppLevelHelper() { init(NULL); }
    bool init(const char *file);
    static AppLevelHelper *create(const char *file);
public:

    // returns a Scene that contains the AppLevelHelper as the only child
    static cocos2d::CCScene* scene(const char *file);

    virtual void draw();
    void update(float dt);
    
private:
    b2Draw *mDraw;
    b2World* mWorld;
    LevelHelperLoader *mLoader;
};

#endif // __HELLO_WORLD_H__
