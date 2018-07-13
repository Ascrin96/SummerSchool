#ifndef GOBJECT_H
#define GOBJECT_H
#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

class GObject
{
public:
    virtual ~GObject(){}
    virtual void draw( cv::Mat &img) = 0;

};

#endif // GOBJECT_H
