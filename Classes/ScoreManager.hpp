//
//  ScoreManager.hpp
//  text
//
//  Created by Cheney on 7/2/16.
//
//

#ifndef ScoreManager_hpp
#define ScoreManager_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

class ScoreManager: public Ref
{
public:
    void setScore(int score);
    int getScore();
    void setHightScore(int hightscore);
    int getHightScore();
    
protected:
};


#endif /* ScoreManager_hpp */
