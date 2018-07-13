#include "utills.h"


float calcLenght(const Vec4f &line){
    float lenghtLine = sqrt((line[2]-line[0])*(line[2]-line[0]) + (line[3]-line[1])*(line[3]-line[1]));
    return lenghtLine;
}

bool compare2Lines(const Vec4f line1, const Vec4f line2){
    return (calcLenght(line1) < calcLenght(line2));
}

bool compare2LinesOnDifference(const Vec4f line1, const Vec4f line2){
    if(abs(calcLenght(line1) - calcLenght(line2)) < 10 ) {
        return true;
    }
    else{
        return false;
    }
}
