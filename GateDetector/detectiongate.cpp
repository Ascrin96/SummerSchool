#include "detectiongate.h"
#include "utills.h"

using namespace cv;

GObject *DetectionGate::detect(const cv::Mat &img){

    Ptr<LineSegmentDetector> ls = createLineSegmentDetector(LSD_REFINE_STD);
    Mat imgOrigin;
    img.copyTo(imgOrigin);
    std::vector<Vec4f> lines_std;



    Mat edge;
    imgOrigin.copyTo(edge);
    cvtColor(edge, edge, COLOR_BGR2GRAY );
    adaptiveThreshold(edge, edge, 255, CV_ADAPTIVE_THRESH_MEAN_C,THRESH_BINARY, 15, -2);

    Mat kernal = Mat::ones(2,2, CV_8UC1);
    dilate(edge, edge, kernal);

    int scale = 10;


    Mat vertical = edge.clone();

    int verticalSize = vertical.cols / scale;

    Mat verticalStructure = getStructuringElement(MORPH_RECT, Size(1, verticalSize));

    erode(vertical, vertical, verticalStructure, Point(-1,-1));
    dilate(vertical, vertical, verticalStructure, Point(-1,-1));


    Mat merge;
    bitwise_and(imgOrigin, imgOrigin, merge, vertical);
    cvtColor(merge, merge, COLOR_BGR2GRAY );
    ls->detect(merge, lines_std); // Detect the lines

    std::sort(lines_std.begin(), lines_std.end(), compare2Lines);
    std::vector<Vec4f> gateVector;

//    for(auto elem: lines_std){
//        std::cout<< elem[0] << "\t" <<  elem[1] << "\t" <<  elem[2] << "\t" << elem[3] << "\t" << "\n";
//    }
    cv::Mat line_mask(cv::Size(img.rows, img.cols), CV_8UC3);

//    for(auto elem: lines_std){

//        for(int i = elem[0]; i < ){
//            img.at<Vec3b>(elem)
//        }
//    }

    cv::bitwise_and(imgOrigin, imgOrigin, merge, vertical);

     for(int i = 0; i < lines_std.size(); i++){
        for(int j = 0; j < lines_std.size(); j++ ){
            if(i == j){
                continue;
            }
            if(compare2LinesOnDifference(lines_std[i], lines_std[j])){
                // if((abs(lines_std[i][0] - lines_std[j][0]) < 5)&&(abs(lines_std[i][2] - lines_std[j][2]) < 5)){
                    Vec4f mergeLine;
                    mergeLine[0] = (lines_std[i][0]+lines_std[j][2])/2;
                    mergeLine[1] = (lines_std[i][1]+lines_std[j][3])/2;
                    mergeLine[2] = (lines_std[i][2]+lines_std[j][0])/2;
                    mergeLine[3] = (lines_std[i][3]+lines_std[j][1])/2;
                    gateVector.push_back(mergeLine);
                // }
            }
        }
     }
    // std::cout << "Size of gateVector " << lines_std.size() << "\n";
    Gate* gate = new Gate(gateVector);

    return gate;

}
