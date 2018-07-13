#ifndef UTILLS_H
#define UTILLS_H

#include <iostream>
#include <cmath>

#include "opencv2/core/core.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "gobject.h"
using namespace cv;

float calcLenght(const Vec4f& line);

bool compare2Lines(const Vec4f line1,const Vec4f line2);

bool compare2LinesOnDifference(const Vec4f line1,const Vec4f line2);
#endif // UTILLS_H
