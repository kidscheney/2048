//
//  PopupLayer.hpp
//  text
//
//  Created by Cheney on 7/3/16.
//
//

#ifndef PopLayer_hpp
#define PopLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "GameScene.hpp"

using namespace cocos2d;

class PopLayer:public LayerColor
{
public:
    bool initWithColor(const Color4B & color) ;
    void onResume(Ref* pSender);
    void onRestart(Ref* pSender);
    void onExit(Ref* pSender);
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};

#endif /* PopLayer_hpp */

