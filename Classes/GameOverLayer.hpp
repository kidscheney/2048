//
//  GameOverLayer.hpp
//  text
//
//  Created by Cheney on 7/2/16.
//
//

#ifndef GameOverLayer_hpp
#define GameOverLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameScene.hpp"
using namespace cocos2d;

class GameOverLayer: public LayerColor
{
public:
    bool initWithColor(const Color4B & color);
    void onRestart(Ref * pSender);
    
//    virtual bool init();
    CREATE_FUNC(GameOverLayer);
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

};

#endif /* GameOverLayer_hpp */
