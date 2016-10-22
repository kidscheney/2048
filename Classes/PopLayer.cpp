//
//  PopupLayer.cpp
//  text
//
//  Created by Cheney on 7/3/16.
//
//

#include "PopLayer.hpp"
bool PopLayer::initWithColor(const Color4B & color)
{
    //get win size
    Size winsize = Director::getInstance()->getWinSize();
    Point centerPos = Point(winsize.width/2, winsize.height/2);
    
    //super init
    if ( !LayerColor::initWithColor(color, winsize.width, winsize.height)) {
            return false;
    }
    
    //menuItemFont
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(50);
    
    auto menuItemContinue = MenuItemFont::create("CONTINUE", CC_CALLBACK_1(PopLayer::onResume, this));
    auto menuItemRestart = MenuItemFont::create("RESTART", CC_CALLBACK_1(PopLayer::onRestart, this));
    auto menuItemExit = MenuItemFont::create("Exit", CC_CALLBACK_1(PopLayer::onExit, this));
    
    
    auto menu = Menu::create(menuItemContinue,menuItemRestart,menuItemExit, NULL);
    menu->alignItemsVertically();
    menu->setPosition(centerPos);
    this->addChild(menu);
    
    //swallow touches
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(PopLayer::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(PopLayer::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(PopLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
    
    touchlistener->setSwallowTouches(true);

    
    //
    return true;
}

/////////////////////////////////////////////////////////
//touch listerer
bool PopLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void PopLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void PopLayer::onTouchEnded(Touch* touch, Event* event)
{
    
}

/////////////////////////////////////////////////////////////
//Event

void PopLayer::onResume(Ref* pSender)
{
    //remove all children
    auto runningScene = Director::getInstance()->getRunningScene();
    runningScene->removeAllChildren();
    
    //get back data from user default
    auto scene = GameScene::backupScene();
    Director::getInstance()->replaceScene(scene);
}

void PopLayer::onExit(Ref* pSender)
{
    Director::getInstance()->end();
    exit(0);
}

void PopLayer::onRestart(Ref*pSender)
{
    //remove all children
        auto runningScene = Director::getInstance()->getRunningScene();
        runningScene->removeAllChildren();
    
    //    //new scene
        auto scene = GameScene::createScene();
        Director::getInstance()->replaceScene(scene);
}