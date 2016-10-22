//
//  SimpleRecognizer.hpp
//  text
//
//  Created by Cheney on 6/26/16.
//
//

#ifndef SimpleRecognizer_hpp
#define SimpleRecognizer_hpp

#include <stdio.h>
#include "cocos2d.h"
using namespace cocos2d;

enum SimpleGestures {SimpleGesturesErrors = 0,SimpleGesturesNotSupport = 1, SimpleGesturesLeft = 2,SimpleGesturesRight = 3,SimpleGesturesUp = 4,SimpleGesturesDown = 5};

class SimpleRecognizer: public Ref
{
public:
    void beginPoint(Point point);
    void movePoint(Point point);
    SimpleGestures endPoint(Point point);
    
protected:
    SimpleGestures result;
    std::vector<Point> points;
};


#endif /* SimpleRecognizer_hpp */
