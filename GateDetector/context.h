#ifndef CONTEXT_H
#define CONTEXT_H
#include "opencv2/core/core.hpp"
#include "gobject.h"
#include "detection.h"

class Context
{
protected:
    Detection* detection;
    GObject* gobj;
public:
    virtual ~Context() {}
    virtual void useDetection(const cv::Mat& img) = 0;
    virtual void setDetection(Detection* d) = 0;
    virtual void setGObject(GObject* obj) = 0;
    virtual void useDraw(cv::Mat& img) = 0;
};
#endif // CONTEXT_H
