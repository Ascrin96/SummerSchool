#ifndef IMAGEWORKER_H
#define IMAGEWORKER_H
#include "context.h"

class ImageWorker : public Context
{
public:
    ~ImageWorker();
    void useDetection(const cv::Mat& img);
    void setDetection(Detection* d);

    void useDraw(cv::Mat& img);
    void setGObject(GObject* obj);

};

#endif // IMAGEWORKER_H
