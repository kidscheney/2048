//
//  GameOverLayer.cpp
//  text
//
//  Created by Cheney on 7/2/16.
//
//

#include "GameOverLayer.hpp"
#include "ScoreManager.hpp"

bool GameOverLayer::initWithColor(const Color4B & color)
{
    
    //win size
    Size winSize = Director::getInstance()->getWinSize();
    Point centerPos = Point(winSize.width / 2, winSize.height / 2);
    
    if ( !LayerColor::initWithColor(color,winSize.width,winSize.height) ) {
        return false;
    }
    
    //game over title
    auto gameOverTitle = Label::createWithSystemFont("GAME OVER","Consolas",50);
    gameOverTitle->setPosition(Point(centerPos.x, centerPos.y + 50));
    this->addChild(gameOverTitle);
    
    //score title
    ScoreManager * SM = new ScoreManager;
    int score = SM->getScore();
    auto scoreTitle = Label::createWithSystemFont(__String::createWithFormat("Score: %d",score)->getCString(), "Consolas", 30);
    scoreTitle->setPosition(centerPos.x, centerPos.y);
    this->addChild(scoreTitle);
    
    //hight score title
    int highscore = SM->getHightScore();
    auto highscoreTitle = Label::createWithSystemFont(__String::createWithFormat("Best: %d",highscore)->getCString(), "Consolas", 20);
    highscoreTitle->setPosition(centerPos.x, centerPos.y -50);
    this->addChild(highscoreTitle);
    
    //Menu restart
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(50);
    auto menuItemRestart = MenuItemFont::create("RESTART", CC_CALLBACK_1(GameOverLayer::onRestart, this));
    
    auto menu = Menu::create(menuItemRestart,NULL);
    menu->setPosition(centerPos.x,centerPos.y - 100);
    this->addChild(menu);
    
    //swallow touches
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(GameOverLayer::onTouchBegan, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(GameOverLayer::onTouchEnded, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(GameOverLayer::onTouchMoved, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
    
    touchlistener->setSwallowTouches(true);
    
    //
    return true;
}

/////////////////////////////////////////////////////////
//touch listerer
bool GameOverLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}
void GameOverLayer::onTouchMoved(Touch* touch, Event* event)
{
    
}
void GameOverLayer::onTouchEnded(Touch* touch, Event* event)
{
    
}

/////////////////////////////////////////////////////////
//on Restart
void GameOverLayer::onRestart(Ref* pSender)
{
    //remove all children
    auto runningScene = Director::getInstance()->getRunningScene();
    runningScene->removeAllChildren();
    
    //new scene
    auto scene = GameScene::createScene();
    Director::getInstance()->replaceScene(scene);
}