#include "markup.h"


Markup::Markup(std::vector<cv::Vec4f> &v){
    std::copy(v.begin(), v.end(), std::back_inserter(lines));
}

void Markup::setVector(const std::vector<cv::Vec4f> &v){
    std::copy(v.begin(), v.end(), lines.begin());
}

void Markup::draw(cv::Mat &img){
    if(!lines.empty()){
        for(auto elem: lines){
            line(img, cv::Point(elem[0], elem[1]), cv::Point(elem[2], elem[3]), cv::Scalar(0, 0, 255), 1, 8, 0);
        }
    }
    else{
        return;
    }
}
