#include <iostream>
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "detectiongate.h"
#include "gate.h"
#include "imageworker.h"

using namespace cv;


int main(){
    VideoCapture cap("/home/misha/development/SummerSchool/Russia-Spain.mp4");

    ImageWorker imgWorker;
    DetectionGate detectionGate;
    imgWorker.setDetection(&detectionGate);

    while(1){
        Mat img;
        cap >> img;
        cv::resize(img, img, cv::Size(800,600));
        imgWorker.useDetection(img);
        imgWorker.useDraw(img);
        cv::imshow("Image", img);


        if(waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
