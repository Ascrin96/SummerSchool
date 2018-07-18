#include <iostream>
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "detectiongate.h"
#include "gate.h"
#include "markup.h"
#include "detectionmarkup.h"
#include "imageworker.h"

using namespace cv;


int main(){
    VideoCapture cap("/home/misha/development/SummerSchool/Russia-Spain.mp4");

    ImageWorker imgWorkerGate;
    ImageWorker imgWorkerMarkup;

    DetectionMarkup detectionMarkup;
    imgWorkerMarkup.setDetection(&detectionMarkup);

    DetectionGate detectionGate;
    imgWorkerGate.setDetection(&detectionGate);

    while(1){
        Mat img;
        cap >> img;
        Mat imgGate, imgMarkup;

        cv::resize(img, img, cv::Size(800,600));
        img.copyTo(imgGate);
        img.copyTo(imgMarkup);

        imgWorkerGate.useDetection(imgGate);
        imgWorkerGate.useDraw(imgGate);

        imgWorkerMarkup.useDetection(imgMarkup);
        imgWorkerMarkup.useDraw(imgMarkup);


        cv::imshow("Gate", imgGate);
        cv::imshow("Markup", imgMarkup);


        if(waitKey(30) == 27) {
            break;
        }
    }

    return 0;
}
