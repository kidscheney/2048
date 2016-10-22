//
//  CardSprite.hpp
//  text
//
//  Created by Cheney on 6/23/16.
//
//

#ifndef CardSprite_hpp
#define CardSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class CardSprite: public Sprite
{
public:
    void initCard(int number,int weight,int height,float CardSpriteX,float CardSpriteY);
    
    int getNumber();
    void setNumber(int num);
    
protected:
    int number;
    LayerColor * colorBackground;
    Label * labelCardNumber;
};

#endif /* CardSprite_hpp */
