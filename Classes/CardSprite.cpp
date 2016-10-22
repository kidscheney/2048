//
//  CardSprite.cpp
//  text
//
//  Created by Cheney on 6/23/16.
//
//

#include "CardSprite.hpp"
using namespace cocos2d;

void CardSprite::initCard(int number,int weight,int height,float CardSpriteX,float CardSpriteY)
{
    this->number = number;
    
    //bg color layer
    this->colorBackground = LayerColor::create(Color4B(200,190,180,255),weight-15,height-15);
    colorBackground->setPosition(Point(CardSpriteX,CardSpriteY));
    
    //label
    if ( number>0 ) {
        this->labelCardNumber = Label::createWithSystemFont(__String::createWithFormat("%i",number)->getCString(),"Consolas",50);
        labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2,colorBackground->getContentSize().height/2));
        labelCardNumber->setTag(8);
        colorBackground->addChild(labelCardNumber);//add label as child to color layer
    }
    else
    {
        this->labelCardNumber = Label::createWithSystemFont("","Consolas",50);
        labelCardNumber->setPosition(Point(colorBackground->getContentSize().width/2,colorBackground->getContentSize().height/2));
        labelCardNumber->setTag(8);
        colorBackground->addChild(labelCardNumber);//add label as child to color layer
    }
    
    //add color bg as child to sprite
    this->addChild(colorBackground);
}

int CardSprite::getNumber()
{
    return number;
}

void CardSprite::setNumber(int num)
{
    this->number = num;
    
    //set label string
    if ( num>0 )
    {
        labelCardNumber->setString(__String::createWithFormat("%i",number)->getCString());
    }
    else
    {
        labelCardNumber->setString("");
    }
    
    //set system font size depends on num
    if ( num>=0 )
    {
        labelCardNumber->setSystemFontSize(50);
    }
    
    if ( num>99 )
    {
        labelCardNumber->setSystemFontSize(30);
    }
    
    if ( num>999 )
    {
        labelCardNumber->setSystemFontSize(20);
    }
    
    //set bg color depends on num
    if( number == 0 )
    {
        colorBackground->setColor(Color3B(200,190,180));
    }
    
    if( number == 2 )
    {
        colorBackground->setColor(Color3B(250,230,200));
    }
    
    if( number == 4 )
    {
        colorBackground->setColor(Color3B(250,220,180));
    }

    if( number == 8 )
    {
        colorBackground->setColor(Color3B(250,100,90));
    }

    if( number == 16 )
    {
        colorBackground->setColor(Color3B(250,90,70));
    }

    if( number == 32 )
    {
        colorBackground->setColor(Color3B(250,30,20));
    }

    if( number == 64 )
    {
        colorBackground->setColor(Color3B(200,240,180));
    }

    if( number == 128 )
    {
        colorBackground->setColor(Color3B(190,240,170));
    }

    if( number == 256 )
    {
        colorBackground->setColor(Color3B(160,250,140));
    }

    if( number == 512 )
    {
        colorBackground->setColor(Color3B(140,250,120));
    }

    if( number == 1024 )
    {
        colorBackground->setColor(Color3B(100,250,70));
    }

    if( number == 2048 )
    {
        colorBackground->setColor(Color3B(80,100,250));
    }

}
