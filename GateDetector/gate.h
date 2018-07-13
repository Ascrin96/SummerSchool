#ifndef GATE_H
#define GATE_H
#include "gobject.h"

class Gate : public GObject
{
private:
    std::vector<cv::Vec4f> lines;
public:
    Gate(std::vector<cv::Vec4f> &v);
    void setVector(const std::vector<cv::Vec4f> &v);
    void draw(cv::Mat &img);
};

#endif // GATE_H
