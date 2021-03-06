//  This file was generated by LevelHelper
//  http://www.levelhelper.org
//
//  LevelHelperLoader.h
//  Created by Bogdan Vladu
//  Copyright 2011 Bogdan Vladu. All rights reserved.
//
////////////////////////////////////////////////////////////////////////////////
//
//  This software is provided 'as-is', without any express or implied
//  warranty.  In no event will the authors be held liable for any damages
//  arising from the use of this software.
//  Permission is granted to anyone to use this software for any purpose,
//  including commercial applications, and to alter it and redistribute it
//  freely, subject to the following restrictions:
//  The origin of this software must not be misrepresented; you must not
//  claim that you wrote the original software. If you use this software
//  in a product, an acknowledgment in the product documentation would be
//  appreciated but is not required.
//  Altered source versions must be plainly marked as such, and must not be
//  misrepresented as being the original software.
//  This notice may not be removed or altered from any source distribution.
//  By "software" the author refers to this code file and not the application 
//  that was used to generate this file.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef __LH_BEZIER_NODE__
#define __LH_BEZIER_NODE__

#include "../lhConfig.h"
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "../Utilities/LHDictionary.h"
#include "LHTouchMgr.h"

using namespace cocos2d;

class LHSprite;
class LHPathNode;
class LevelHelperLoader;
class LHAbstractClass;

typedef struct __LHBezierBlendingInfo{
  
    CCTexture2D* texture;
    GLenum blendSource;
    GLenum blendDestination;
    bool tile;
} LHBezierBlendingInfo;


class LHBezier : public CCNode, public CCStandardTouchDelegate
{
protected:
    
#if COCOS2D_VERSION >= 0x00020000
    CCGLProgram *mShaderProgram;
	GLint		mColorLocation;
#endif

	bool isClosed;
	bool isTile;
	bool isVisible;
	bool isLine;
	bool isPath;
    bool drawBorder;
    float opacity;
    std::string uniqueName;
	b2Body* body; //can be 0
    std::vector<CCPoint> pathPoints;
    //CCMutableArray<LHPathNode*> pathNodes;
	
	/////////for the tile feature
	CCTexture2D *texture;
	CCRect color;
	CCRect lineColor;
	float lineWidth;
	CCSize winSize;
    std::vector<std::vector<CCPoint> > trianglesHolder;
    std::vector<CCPoint> linesHolder;

    std::vector<LHBezierBlendingInfo> blendingTextures;
    
	CCSize imageSize;
    
    //static int numberOfBezierNodes;
    
    friend class LevelHelperLoader;    
    
    LHObserverPair* touchBeginObserver;
    LHObserverPair* touchMovedObserver;
    LHObserverPair* touchEndedObserver;
    bool swallowTouches;
    bool touchIsDisabled;
    int touchPriority;
    
    LHObserverPair* tagTouchBeginObserver;
    LHObserverPair* tagTouchMovedObserver;
    LHObserverPair* tagTouchEndedObserver;
    
     LHAbstractClass* userCustomInfo;
public:
    
    const std::vector<CCPoint>& getPathPoints(){return pathPoints;}
    
    bool getIsClosed(void){return isClosed;}
 
    bool getIsTile(void){return isTile;}
  
    bool getIsVisible(void){return isVisible;}
    void setIsVisible(const bool& v){isVisible = v;}
    
    bool getIsLine(void){return isLine;}

    std::string& getUniqueName(void){return uniqueName;}
  
    b2Body* getBody(void){return body;};
    
    
    void pushBlendingTextureNamed(const std::string& texName, 
                                  bool tile = true,
                                  GLenum blendSource = GL_DST_COLOR, 
                                  GLenum blendDestination = GL_ZERO);
    
    static bool isLHBezier(CCNode* obj);
    static std::string uniqueNameForBody(b2Body* body);
    static LHBezier* bezierForBody(b2Body* body);
    static int tagForBody(b2Body* body);
    
    virtual void init(void);
    virtual ~LHBezier(void);
    LHBezier(void);
    
    
    void removeSelf();//use this to remove the bezier node entirely;
    LevelHelperLoader* parentLoader();
    
    bool initWithDictionary(LHDictionary* properties);
    
    static LHBezier* bezierWithDictionary(LHDictionary* properties);
        
    virtual void draw(void);
    
    
    //USER DATA
    //--------------------------------------------------------------------------
    //will return "No Class" if no class is defined
    //will return the class name if a class is assigned to this sprite
    std::string userInfoClassName();
    
    //this will return an instance of the class defined in LH under Custom Class Properties
    //check for NULL to see if you have any info
    //use the class properties to read all your info
    //e.g MyClass* myInfo = (MyClass*)sprite->userInfo();  if(myInfo){ int life = myInfo.life); }
    
    //use the class properties to set new (other then the one set in LH) values
    //e.g MyClass* myInfo = (MyClass*)sprite->userInfo(); if(myInfo){ myInfo.life = 40; } )
    void* userInfo();
    

    
    
    
    //TOUCH METHODS
    //------------------------------------------------------------------------------
    //Touches are detected only on bezier tile shapes.
    //If the bezier is not a tile shape no touches events will be performed.
    bool isTouchedAtPoint(CCPoint point);
    
    //selector needs to have this signature void HelloWorldLayer::touchXXX:(LHTouchInfo*)info
    //in visual studio the method signature should be 
    //void HelloWorldLayer::touchXXX(CCObject* cinfo){LHTouchInfo* info = (LHTouchInfo*)info; ...} 
    //because compiler doesn't know how to cast
    //info will have all information regarding the touch (see API Documentation or top of this file)
    //for generic touch on sprites with tag use the observers from LevelHelperLoader
    LH_DEPRECATED_ATTRIBUTE void registerTouchBeginObserver(CCObject* observer, SEL_CallFuncO selector);

    void registerTouchBeganObserver(CCObject* observer, SEL_CallFuncO selector);
    void registerTouchMovedObserver(CCObject* observer, SEL_CallFuncO selector);
    void registerTouchEndedObserver(CCObject* observer, SEL_CallFuncO selector);

    void removeTouchObserver(); //once removed it cannot be added back - (error in Cocos2d) - use -(void)setTouchedDisabled:(bool)val;
    
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

    void setTouchedDisabled(bool val){touchIsDisabled = val;}
    bool getTouchedDisabled(){return touchIsDisabled;}
    
    void setSwallowTouches(bool val){swallowTouches = val;}
    bool getSwallowTouches(){return swallowTouches;}
    
    void setTouchPriority(int val){touchPriority = val;}
    int getTouchPriority(){return touchPriority;}

    virtual void touchDelegateRetain() {} //compatibility with old cocos2d-x version
    virtual void touchDelegateRelease() {}//compatibility with old cocos2d-x version
    virtual void onExit();
    
//    virtual void visit();
private:
    
    
    void loadUserCustomInfoFromDictionary(LHDictionary* dictionary);
    
    static CCPoint pointOnCurve(CCPoint p1, CCPoint p2, CCPoint p3, CCPoint p4, float t);
    
    void initTileVerticesFromDictionary(LHDictionary* dictionary, LHArray* fixtures);
//    void initTileVerticesFromDictionary(LHDictionary* bezierDict);
    void initPathPointsFromDictionary(LHDictionary* bezierDict);
    void createBodyFromDictionary(LHDictionary* bezierDict, b2World* world);
    
    void setTagTouchBeginObserver(LHObserverPair* pair);
    void setTagTouchMovedObserver(LHObserverPair* pair);
    void setTagTouchEndedObserver(LHObserverPair* pair);
};

#endif
