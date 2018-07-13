#include "imageworker.h"

ImageWorker::~ImageWorker(){delete gobj;}

void ImageWorker::useDetection(const cv::Mat &img){
    GObject* obj = detection->detect(img);
    setGObject(obj);
}

void ImageWorker::setDetection(Detection *d){
    detection = d;
}

void ImageWorker::useDraw(cv::Mat &img){
    gobj->draw(img);
}

void ImageWorker::setGObject(GObject *obj){
    gobj = obj;
}
