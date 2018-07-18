#ifndef DETECTIONMARKUP_H
#define DETECTIONMARKUP_H
#include "detection.h"
#include "markup.h"

class DetectionMarkup : public Detection {
public:
    GObject* detect(const cv::Mat& img);
};

#endif // DETECTIONMARKUP_H
