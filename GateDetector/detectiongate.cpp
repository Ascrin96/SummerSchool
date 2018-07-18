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
    std::vector<std::array <Vec4f, 2> > gates;

//    for(auto elem: lines_std){
//        std::cout<< elem[0] << "\t" <<  elem[1] << "\t" <<  elem[2] << "\t" << elem[3] << "\t" << "lenght: " <<calcLenght(elem) << "\n" ;
//    }
//    std::cout << "==================================================================================" << "\n";

//    cv::Mat line_mask(cv::Size(img.rows, img.cols), CV_8UC3);

    for(int i = 0; i < lines_std.size(); i++){
         if(calcLenght(lines_std[i]) < 20){
             continue;
         }
         Vec4f tmpLine(lines_std[i]);
         sortPointInLine(tmpLine);
         whiteLinesVector.push_back(tmpLine);
    }

    for(int i = 0; i < whiteLinesVector.size(); i++){
        for(int j = 0; j < whiteLinesVector.size(); j++){
            if(i == j){
                continue;
            }
            if(((abs(whiteLinesVector[i][0] - whiteLinesVector[j][0]) < 180)
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

                std::array <Vec4f, 2> ptrOfGate = {line1,line2};

                gates.push_back(ptrOfGate);
            }
        }
    }

    for(int i = 0; i < gates.size(); i++){
        Vec4f line1, line2, diag1, diag2;
        line1[0] = gates[i][0][0];
        line1[1] = gates[i][0][1];
        line1[2] = gates[i][1][0];
        line1[3] = gates[i][1][1];

        line2[0] = gates[i][0][2];
        line2[1] = gates[i][0][3];
        line2[2] = gates[i][1][2];
        line2[3] = gates[i][1][3];

        diag1[0] = gates[i][0][0];
        diag1[1] = gates[i][0][1];
        diag1[2] = gates[i][1][2];
        diag1[3] = gates[i][1][3];

        diag2[0] = gates[i][1][0];
        diag2[1] = gates[i][1][1];
        diag2[2] = gates[i][0][2];
        diag2[3] = gates[i][0][3];

        float p = (calcLenght(gates[i][0]) + calcLenght(gates[i][1]) + calcLenght(line1) + calcLenght(line2));
        float s = (calcLenght(diag1)*calcLenght(diag2)*abs(sin(angleBetween2Lines(diag1,diag2))))/2;

        float indexSP = s/p;

        if((indexSP > 22) && (indexSP< 36)){
            gateVector.push_back(gates[i][0]);
            gateVector.push_back(line1);
            gateVector.push_back(gates[i][1]);
            gateVector.push_back(line2);
        }
    }

    GObject* gate = new Gate(gateVector);

    return gate;

}
