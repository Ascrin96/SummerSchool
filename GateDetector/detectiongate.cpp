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
    cv::threshold(merge, merge, 200, 255, THRESH_TOZERO);
    imshow("Thresh", merge);
    ls->detect(merge, lines_std); // Detect the lines

    std::sort(lines_std.begin(), lines_std.end(), compare2Lines);

    for(int i = 0; i < lines_std.size(); i++){
        for(auto j = 0; j < lines_std.size(); j++){
            if(compareLinesOnJoinVertical( lines_std[i], lines_std[j])){
                Vec4f join = join2Lines(lines_std[i], lines_std[j]);
                lines_std[i][0] = join[0];
                lines_std[i][1] = join[1];
                lines_std[i][2] = join[2];
                lines_std[i][3] = join[3];
                lines_std.erase(lines_std.begin() + j);
            }
        }
    }


    std::vector<Vec4f>  whiteLinesVector, gateVector;

//    for(auto elem: lines_std){
//        std::cout<< elem[0] << "\t" <<  elem[1] << "\t" <<  elem[2] << "\t" << elem[3] << "\t" << "lenght: " <<calcLenght(elem) << "\n" ;
//    }
//    std::cout << "==================================================================================" << "\n";

//    cv::Mat line_mask(cv::Size(img.rows, img.cols), CV_8UC3);

    for(int i = 0; i < lines_std.size(); i++){
         if(calcLenght(lines_std[i]) < 20){
             continue;
         }
        whiteLinesVector.push_back(lines_std[i]);
    }

    for(int i = 0; i < whiteLinesVector.size(); i++){
        for(int j = 0; j < whiteLinesVector.size(); j++){
            if(i == j){
                continue;
            }
            if(((abs(whiteLinesVector[i][0] - whiteLinesVector[j][0]) < 160)
                    && (abs(whiteLinesVector[i][0] - whiteLinesVector[j][0]) > 140))
                    || ((abs(whiteLinesVector[i][0] - whiteLinesVector[j][0]) < 640)
                        && (abs(whiteLinesVector[i][0] - whiteLinesVector[j][0]) > 600))){
                Vec4f line1, line2;
                line1[0] = whiteLinesVector[i][0];
                line1[1] = whiteLinesVector[i][1];
                line1[2] = whiteLinesVector[j][0];
                line1[3] = whiteLinesVector[j][1];

                line2[0] = whiteLinesVector[i][2];
                line2[1] = whiteLinesVector[i][3];
                line2[2] = whiteLinesVector[j][2];
                line2[3] = whiteLinesVector[j][3];
                gateVector.push_back(whiteLinesVector[i]);
                gateVector.push_back(whiteLinesVector[j]);
                gateVector.push_back(line1);
                gateVector.push_back(line2);
            }
        }
    }

//     std::cout << "Size of gateVector " << gateVector.size() << "\n";
    Gate* gate = new Gate(gateVector);

    return gate;

}
