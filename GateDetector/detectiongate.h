#ifndef DETECTIONGATE_H
#define DETECTIONGATE_H
#include "detection.h"
#include "gate.h"

class DetectionGate : public Detection {
public:
    GObject* detect(const cv::Mat& img);

};

#endif // DETECTIONGATE_H
