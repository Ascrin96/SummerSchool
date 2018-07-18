#include "detectionmarkup.h"
#include "markup.h"
#include "utills.h"

using namespace cv;

//const float borderOfInterval = 2.50f;
//bool isLeftOfInterval(Vec4f line){
//    if(){

//    }
//}

GObject *DetectionMarkup::detect(const cv::Mat &img){
    Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
    Mat imgOrigin;
    img.copyTo(imgOrigin);
    std::vector<Vec4f> lines_std, lines_copy;
    std::vector<std::array<float,2> > anglesAndLenghts;

    Mat imgJoin, imgHVS;
//    imgOrigin.copyTo(edge);

    cvtColor(imgOrigin, imgHVS, COLOR_BGR2HSV);
    Mat imgThreshold, edge;


    bitwise_and(imgOrigin, imgOrigin, imgJoin, imgThreshold);

    cvtColor(imgOrigin,edge, COLOR_BGR2GRAY);
    threshold(edge,edge,150,240 , THRESH_TOZERO);


    ls->detect(edge, lines_std); // Detect the lines

    std::sort(lines_std.begin(), lines_std.end(), compare2LinesOnAngel);

    for(auto elem: lines_std){
        std::array<float, 2> arr = {calcAngle(elem), calcLenght(elem)};
        anglesAndLenghts.push_back(arr);
    }




    for(int i = 0; i < lines_std.size(); i++){
        if(calcLenght(lines_std[i]) > 50.0f){
            lines_copy.push_back(lines_std[i]);
        }
    }

    GObject* markup = new Markup(lines_copy);
    return markup;
}


//for(auto i = lines_copy.begin(); i != lines_copy.end(); i++){
////        int left = 0;
////        int right = lines_copy.size();
////        int search
////        auto it = lines_copy.begin() + i;
//    auto left = std::find_if(lines_copy.begin(), lines_copy.end(), [i](Vec4f line ){ return (abs(calcAngle(line) - calcAngle(it)) < 2.0f);});
//    std::cout << left[0] << left[1];
////        for(int j = 0; j < lines_copy.size(); j++){
////            if(i == j){
////                continue;
////            }

//////            compare2linesOnNeighbor(lines_copy[i], lines_copy[j]);
////            if(compareLinesOnAngleJoin( lines_copy[i], lines_copy[j])){
////                Vec4f join = join2Lines(lines_copy[i], lines_copy[j]);
////                lines_copy[i][0] = join[0];
////                lines_copy[i][1] = join[1];
////                lines_copy[i][2] = join[2];
////                lines_copy[i][3] = join[3];
////                lines_copy.erase(lines_copy.begin() + j);
////            }
////        }
//}
