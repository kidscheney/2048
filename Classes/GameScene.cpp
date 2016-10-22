//
//  GameScene.cpp
//  text
//
//  Created by Cheney on 6/23/16.
//
//

#include "GameScene.hpp"

//#include "PopLayer.hpp"

using namespace cocos2d;

Scene* GameScene::backupScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    layer->getData();
    
    scene->addChild(layer);
    
    return scene;
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = GameScene::create();
    
    scene->addChild(layer);
    
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() ) {
        return false;
    }
    
    //visibe size and log it
    Size visibleSize = Director::getInstance()->getVisibleSize();
    log("%f,%f",visibleSize.width,visibleSize.height);
    
    //BG color
    auto layerBG = LayerColor::create(Color4B(180, 170, 160, 255));
    this->addChild(layerBG);
    
    //MenuItemFont
    MenuItemFont::setFontName("Consolas");
    MenuItemFont::setFontSize(40);
    auto menuItemPause = MenuItemFont::create("PAUSE", CC_CALLBACK_1(GameScene::onPause, this));
    
    //Menu
    auto menu = Menu::create(menuItemPause, NULL);
    menu->setPosition(Point(visibleSize.width - 80, visibleSize.height/2 + 100));
    this->addChild(menu);
    
    //CardNumberTitle
    auto cardNumberTitle = Label::createWithSystemFont("SCORE","Consolas",40);
    cardNumberTitle->setPosition(Point(visibleSize.width - 80, visibleSize.height/2 + 10));
    this->addChild(cardNumberTitle);
    
    //score
    cardNumberTTF = Label::createWithSystemFont("0", "Consolas", 30);
    cardNumberTTF->setPosition(Point(visibleSize.width - 80, visibleSize.height/2 - 20));
    this->addChild(cardNumberTTF);
    
    //card
    shouldCreateCardNumber = true;
    this->createCardSprite(visibleSize);
    this->createCardNumber();
    this->createCardNumber();
    
    //event touch
    auto touchlistener = EventListenerTouchOneByOne::create();
    touchlistener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchlistener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchlistener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchlistener, this);
    
    
    //simple recognizer
    this->recognizer = new SimpleRecognizer;
    
    return true;
}

//////////////////////////////////////////////////////////
//event

void GameScene::onPause(Ref* pSender)
{
    Director::getInstance()->pause();
    
    PopLayer* poplayer = new PopLayer;
    poplayer->initWithColor(Color4B(0, 0, 0, 180));
    poplayer->setTag(1);
    this->addChild(poplayer, 1,1);
    
    //save status
    this->saveData();
}

bool GameScene::onTouchBegan(Touch *touch, Event * event)
{
    Point beginTouchPoint = touch->getLocation();
    this->recognizer->beginPoint(beginTouchPoint);
    
    return true;
}

void GameScene::onTouchMoved(Touch *touch, Event *event)
{
    Point posTouchPoint = touch->getLocation();
    recognizer->movePoint(posTouchPoint);
}

void GameScene::onTouchEnded(Touch *touch, Event *event)
{
    Point endTouchPoint = touch->getLocation();
    SimpleGestures rtn = recognizer->endPoint(endTouchPoint);
    
    switch ( rtn ) {
        case SimpleGesturesLeft:
            this->doLeft();
            this->doCheck();
            this->setScore();
            this->saveStatus();
            break;
            
        case SimpleGesturesRight:
            this->doRight();
            this->doCheck();
            this->setScore();
            this->saveStatus();
            break;
            
        case SimpleGesturesUp:
            this->doUp();
            this->doCheck();
            this->setScore();
            this->saveStatus();
            break;
        
        case SimpleGesturesDown:
            this->doDown();
            this->doCheck();
            this->setScore();
            this->saveStatus();
            break;
            
        default:
            break;
    }
}

/////////////////////////////////////////////////////////////
//do and check
bool GameScene::doLeft()
{
    isMove = false;
    
    for (int y=0; y<4; y++) {
        
        for (int x=0; x<4; x++) {
            
            for (int x1=x+1; x1<4; x1++) {
                
                if ( cardArr[x1][y]->getNumber() > 0 ) {
                    
                    if ( cardArr[x][y]->getNumber() <= 0 ) {
                        cardArr[x][y]->setNumber( cardArr[x1][y]->getNumber() );
                        cardArr[x1][y]->setNumber(0);
                        isMove = true;
                    }
                    
                    else if ( cardArr[x1][y]->getNumber() == cardArr[x][y]->getNumber() ) {
                        cardArr[x][y]->setNumber( cardArr[x1][y]->getNumber()*2 );
                        cardArr[x1][y]->setNumber(0);
                        
                        score += cardArr[x][y]->getNumber();
                        
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::doRight()
{
    isMove = false;
    
    for (int y=0; y<4; y++) {
        for (int x=3; x>=0; x--) {
            for (int x1=x-1; x1>=0; x1--) {
                if ( cardArr[x1][y]->getNumber()>0 ) {
                    if ( cardArr[x][y]->getNumber()<=0 ) {
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
                        cardArr[x1][y]->setNumber(0);
                        isMove = true;
                    }
                    else if ( cardArr[x1][y]->getNumber() == cardArr[x][y]->getNumber() ) {
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber()*2);
                        cardArr[x1][y]->setNumber(0);
                        
                        score += cardArr[x][y]->getNumber();
                        
                        isMove = true;
                    }
                    break;
                }
            }
        }
    }
    
    return isMove;
}

bool GameScene::doUp()
{
    isMove = false;
    
    for ( int x=0; x<4; x++) {
        for ( int y=3; y>=0; y--) {
            for ( int y1=y-1; y1>=0; y1-- ) {
                if ( cardArr[x][y1]->getNumber() > 0 ) {
                    if ( cardArr[x][y]->getNumber() <= 0  ) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        isMove = true;
                    }
                    else if ( cardArr[x][y1]->getNumber() == cardArr[x][y]->getNumber() ) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber()*2);
                        cardArr[x][y1]->setNumber(0);
                        
                        score += cardArr[x][y]->getNumber();
                    }
                    break;
                }
            }
        }
    }
    return isMove;
 
}

bool GameScene::doDown()
{
    isMove = false;
    
    for ( int x=0; x<4; x++) {
        for ( int y=0; y<4; y++) {
            for ( int y1=y+1; y1<4; y1++ ) {
                if ( cardArr[x][y1]->getNumber() > 0 ) {
                    if ( cardArr[x][y]->getNumber() <= 0  ) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        isMove = true;
                    }
                    else if ( cardArr[x][y1]->getNumber() == cardArr[x][y]->getNumber() ) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber()*2);
                        cardArr[x][y1]->setNumber(0);
                        
                        score += cardArr[x][y]->getNumber();
                    }
                    break;
                }
            }
        }
    }
    return isMove;
  
}

void GameScene::doCheck()
{
    isGameOVer = true;
    
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            
            if ( cardArr[x][y]->getNumber() == 0 ||
                (x<3 && cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber()) ||
                (x>0 && cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber()) ||
                (y<3 && cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()) ||
                (y>0 && cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()))
            {
                isGameOVer = false;
            }
        }
    }
    
    if ( isWin() ) {
        log("=====");
        log("win");
        log("=====");
        successLayer = LayerColor::create(Color4B(0, 0, 0, 180));
        
        Size size = Director::getInstance()->getWinSize();
        Point ceterPos = Point(size.width / 2,size.height / 2);
        
        auto gameoverTitle = Label::createWithSystemFont("You Win", "Consolas", 50);
        gameoverTitle->setPosition(ceterPos);
        
        successLayer->addChild(gameoverTitle);
        
        this->addChild(successLayer,1);
        
        scheduleOnce(SEL_SCHEDULE(&GameScene::removeSuccessLayer), 2);
    }
    
    if ( isGameOVer ) {
        log("Game Over");
        GameOverLayer* gameoverLayer = new GameOverLayer;
        gameoverLayer->initWithColor(Color4B(0, 0, 0, 180));
        this->addChild(gameoverLayer,1);
    }
    else
    {
        if ( isMove ) {
            createCardNumber();
        }
    }
    
}

bool GameScene::isWin()
{
    bool isWin = false;
    
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            if ( 2048 == cardArr[x][y]->getNumber() ) {
                isWin = true;
                break;
            }
        }
    }
    
    return isWin;
}

void GameScene::removeSuccessLayer()
{
    this->removeChild(successLayer);
}

////////////////////////////////////////////////////////////
//set score and status
void GameScene::setScore()
{
    cardNumberTTF->setString(__String::createWithFormat("%d",score)->getCString());
}

void GameScene::saveStatus()
{
    ScoreManager * SM = new ScoreManager;
    
    //set score
    SM->setScore(this->score);
    
    //set hight score
    int hightscore;
    hightscore = UserDefault::getInstance()->getIntegerForKey("hightscore");
    if ( this->score > hightscore ) {
        UserDefault::getInstance()->setIntegerForKey("hightscore", this->score);
    }
}

/////////////////////////////////////////////////////////////
//create sprite and card number

void GameScene::createCardSprite(Size size)
{
    int cardsize = (size.height-0) / 4;
    
    for ( int i=0; i<4; i++) {
        for ( int j=0; j<4; j++) {
            CardSprite * card = new CardSprite;
            card->initCard(0, cardsize, cardsize, cardsize*i+40, cardsize*j+35);//card sprite
            cardArr[i][j] = card;
            this->addChild(card);
        }
    }
}

void GameScene::createCardNumber()
{
    while (1) {
        int i = CCRANDOM_0_1() * 4;
        int j = CCRANDOM_0_1() * 4;
        
        //log i,j
        log("[%d][%d]",i,j);
        
        if ( cardArr[i][j]->getNumber() == 0 ) {
            cardArr[i][j]->setNumber( CCRANDOM_0_1()*10 < 1? 4:2 );
            break;
        }
        
        if ( !shouldCreateCardNumber ) {
            break;
        }
    }
}

///////////////////////////////////////
//save data and get data
void GameScene::saveData()
{
    char temp[10];
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            sprintf(temp, "%d%d",x,y);
            UserDefault::getInstance()->setIntegerForKey(temp, cardArr[x][y]->getNumber());
            log("%s: %d",temp,cardArr[x][y]->getNumber());
        }
    }

}

void GameScene::getData()
{
    char temp[10];
    for (int x=0; x<4; x++) {
        for (int y=0; y<4; y++) {
            sprintf(temp, "%d%d",x,y);
            int number = UserDefault::getInstance()->getIntegerForKey(temp);
            cardArr[x][y]->setNumber(number);
            log("%s: %d",temp,cardArr[x][y]->getNumber());
        }
    }

}
