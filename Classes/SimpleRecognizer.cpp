//
//  SimpleRecognizer.cpp
//  text
//
//  Created by Cheney on 6/26/16.
//
//

#include "SimpleRecognizer.hpp"
using namespace std;
using namespace cocos2d;

void SimpleRecognizer::beginPoint(Point point)
{
    this->result = SimpleGesturesErrors;
    points.clear();
    points.push_back(point);
}

void SimpleRecognizer::movePoint(Point point)
{
    points.push_back(point);
}

SimpleGestures SimpleRecognizer::endPoint(Point point)
{
    points.push_back(point);
    
    if ( points.size()<3 ) {
        return SimpleGesturesErrors;
    }
    
    SimpleGestures newRtn = SimpleGesturesErrors;
    long len = this->points.size();
    
    double dx = this->points[len-1].x - this->points[0].x;
    double dy = this->points[len-1].y - this->points[0].y;
    
    if ( abs(dx) > abs(dy) ) {
        if ( dx>50 ) {
            newRtn = SimpleGesturesRight;
        }
        else if ( dx<-50 ) {
            newRtn = SimpleGesturesLeft;
        }
    }
    else {
        if ( dy>50 ) {
            newRtn = SimpleGesturesUp;
        }
        else if ( dy<-50 ) {
            newRtn = SimpleGesturesDown;
        }
    }
    
    if ( result == SimpleGesturesErrors ) {
        result = newRtn;
    }
    
    if ( result != newRtn ) {
        result = SimpleGesturesNotSupport;
    }
    
    return result;
}