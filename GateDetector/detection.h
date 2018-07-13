#ifndef DETECTION_H
#define DETECTION_H
#include "gobject.h"
#include "opencv2/core/core.hpp"

class Detection
{
public:
    virtual ~Detection(){}
    virtual GObject* detect(const cv::Mat& img) = 0;
};


#endif // DETECTION_H
