//
//  ScoreManager.cpp
//  text
//
//  Created by Cheney on 7/2/16.
//
//

#include "ScoreManager.hpp"

void ScoreManager::setScore(int score)
{
    UserDefault::getInstance()->setIntegerForKey("score", score);
}

int ScoreManager::getScore()
{
    int score = UserDefault::getInstance()->getIntegerForKey("score");
    return score;
}

void ScoreManager::setHightScore(int hightscore)
{
    UserDefault::getInstance()->setIntegerForKey("hightscore", hightscore);
}

int ScoreManager::getHightScore()
{
    int hightscore = UserDefault::getInstance()->getIntegerForKey("hightscore");
    return hightscore;
}