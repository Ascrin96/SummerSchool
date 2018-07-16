#include "utills.h"


float calcLenght(const Vec4f &line){
    float lenghtLine = sqrt((line[2]-line[0])*(line[2]-line[0]) + (line[3]-line[1])*(line[3]-line[1]));
    return lenghtLine;
}

bool compare2Lines(const Vec4f line1, const Vec4f line2){
    return (calcLenght(line1) < calcLenght(line2));
}

bool compare2LinesOnDifference(const Vec4f line1, const Vec4f line2){
    if(abs(calcLenght(line1) - calcLenght(line2)) < 15 ) {
        return true;
    }
    else{
        return false;
    }
}

Vec4f join2LinesAVG(const Vec4f line1, const Vec4f line2){
    Vec4f join1, join2, join;
    if((line1[0]+ line1[1]) > (line1[2] + line1[3])){
        join1[0] = line1[2];
        join1[1] = line1[3];
        join1[2] = line1[0];
        join1[3] = line1[1];
    }
    else{
        join1[0] = line1[0];
        join1[1] = line1[1];
        join1[2] = line1[2];
        join1[3] = line1[3];
    }

    if((line2[0]+ line2[1]) > (line2[2] + line2[3])){
        join2[0] = line2[2];
        join2[1] = line2[3];
        join2[2] = line2[0];
        join2[3] = line2[1];
    }
    else{
        join2[0] = line2[0];
        join2[1] = line2[1];
        join2[2] = line2[2];
        join2[3] = line2[3];
    }
    join[0] = (join1[0] + join2[0])/2;
    join[1] = (join1[1] + join2[1])/2;
    join[2] = (join1[2] + join2[2])/2;
    join[3] = (join1[3] + join2[3])/2;

    return join;
}

Vec4f join2Lines(const Vec4f line1, const Vec4f line2){
    Vec4f join1(line1), join2(line2), join;
    sortPointInLine(join1);
    sortPointInLine(join2);

    if((join1[0] + join1[1]) > (join2[0] + join2[1])){
        join[0] = join1[0];
        join[1] = join1[1];
    }
    else{
        join[0] = join2[0];
        join[1] = join2[1];
    }

    if((join1[2] + join1[3]) > (join2[2] + join2[3])){
        join[2] = join1[2];
        join[3] = join1[3];
    }
    else{
        join[2] = join2[2];
        join[3] = join2[3];
    }
    return join;
}

bool compareLinesOnJoinVertical(const Vec4f &line1, const Vec4f &line2){
    Vec4f tmpLine1(line1), tmpLine2(line2);
    sortPointInLine(tmpLine1);
    sortPointInLine(tmpLine2);

    if((abs(line1[0] - line2[0]) < 7) && (abs(line1[2] - line2[2]) < 7)){
        return true;
    }
    else{
        return false;
    }
}

void sortPointInLine(Vec4f &line1){
    Vec4f tmpLine;
    if((line1[0]+ line1[1]) > (line1[2] + line1[3])){
        tmpLine[0] = line1[2];
        tmpLine[1] = line1[3];
        tmpLine[2] = line1[0];
        tmpLine[3] = line1[1];
    }
    else{
        tmpLine[0] = line1[0];
        tmpLine[1] = line1[1];
        tmpLine[2] = line1[2];
        tmpLine[3] = line1[3];
    }
    line1[0] = tmpLine[0];
    line1[1] = tmpLine[1];
    line1[2] = tmpLine[2];
    line1[3] = tmpLine[3];
}
