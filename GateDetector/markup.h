#ifndef MARKUP_H
#define MARKUP_H
#include "gobject.h"

class Markup : public GObject {
private:
    std::vector<cv::Vec4f> lines;
public:
    Markup(std::vector<cv::Vec4f> &v);
    void setVector(const std::vector<cv::Vec4f> &v);
    void draw(cv::Mat &img);
};

#endif // MARKUP_H
