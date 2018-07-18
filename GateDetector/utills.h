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
#include <cmath>
using namespace cv;

float calcLenght(const Vec4f& line);
float calcAngle(const Vec4f& line);

bool compare2Lines(const Vec4f line1,const Vec4f line2);
bool compare2LinesOnAngel(const Vec4f line1,const Vec4f line2);

bool compare2LinesOnDifference(const Vec4f line1,const Vec4f line2);

Vec4f join2LinesAVG(const Vec4f line1, const Vec4f line2);

Vec4f join2Lines(const Vec4f line1, const Vec4f line2);

bool compareLinesOnJoinVertical(const Vec4f& line1, const Vec4f& line2);

bool compareLinesOnAngleJoin(const Vec4f& line1, const Vec4f& line2);

void sortPointInLine(Vec4f& line1);

float angleBetween2Lines(const Vec4f& line1, const Vec4f& line2);

Vec3f calcEquation(const Vec4f& line);

bool compare2linesOnAlong(const Vec4f& line1, const Vec4f& line2);
bool compare2linesOnNeighbor(const Vec4f &line1, const Vec4f &line2);

#endif // UTILLS_H
