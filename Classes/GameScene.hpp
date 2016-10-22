//
//  GameScene.hpp
//  text
//
//  Created by Cheney on 6/23/16.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "CardSprite.hpp"
#include "SimpleRecognizer.hpp"
#include "CardSprite.hpp"
#include "ScoreManager.hpp"
#include "GameOverLayer.hpp"
#include "PopLayer.hpp"

using namespace cocos2d;

class GameScene: public Layer
{
public:
    //scene
    static Scene* createScene();
    CREATE_FUNC(GameScene);
    
    //init
    virtual bool init();
    
    void onPause(Ref* pSender);
    
    //card sprite
    void createCardSprite(Size size);
    
    void createCardNumber();
    
    //touch event
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    
    //do and check
    bool doLeft();
    bool doRight();
    bool doUp();
    bool doDown();
    void doCheck();
    bool isWin();
    void removeSuccessLayer();
    void setScore();
    void saveStatus();
    
    //save and get data
    void saveData();
    void getData();
    
    //return backup scene
    static Scene* backupScene();
    
protected:
    CardSprite * cardArr[4][4];
    bool shouldCreateCardNumber;
    Label *cardNumberTTF;
    SimpleRecognizer * recognizer;
    bool isMove;
    bool isGameOVer;
    int score=0;
    LayerColor * successLayer;
};

#endif /* GameScene_hpp */
