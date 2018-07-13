#ifndef GOBJECT_H
#define GOBJECT_H
#include "opencv2/core/core.hpp"

class GObject
{
public:
    virtual ~GObject(){}
    virtual void draw( cv::Mat &img) = 0;

};

#endif // GOBJECT_H
