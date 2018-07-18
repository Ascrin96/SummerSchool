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

Vec4f  join2Lines(const Vec4f line1, const Vec4f line2){
    Vec4f join1(line1), join2(line2), join;
    sortPointInLine(join1);
    sortPointInLine(join2);
    float tg;

    if(abs(join1[0] - join1[2]) < 7){
        tg = 1;
    }
    else{
        tg = (join1[3]-join1[1])/(join1[2]-join1[0]);
    }

    if(tg >  0){
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
    }
    else if (tg <= 0){
        if((join1[0] + join1[1]) < (join2[0] + join2[1])){
            join[0] = join1[0];
            join[1] = join1[1];
        }
        else{
            join[0] = join2[0];
            join[1] = join2[1];
        }
        if((join1[2] + join1[3]) < (join2[2] + join2[3])){
            join[2] = join1[2];
            join[3] = join1[3];
        }
        else{
            join[2] = join2[2];
            join[3] = join2[3];
        }

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
    float tg;

    if(abs(tmpLine[0] - tmpLine[2] < 7)){
        tg = 1;
    }
    else{
        tg = (tmpLine[3]-tmpLine[1])/(tmpLine[2]-tmpLine[0]);
    }

    if( tg >  0) {
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
    }
    else if (tg <= 0){
         if((line1[0] > line1[2]) && (line1[3] > line1[1])){
             tmpLine[0] = line1[0];
             tmpLine[1] = line1[1];
             tmpLine[2] = line1[2];
             tmpLine[3] = line1[3];
         }
         else{
             tmpLine[0] = line1[2];
             tmpLine[1] = line1[3];
             tmpLine[2] = line1[0];
             tmpLine[3] = line1[1];
         }
    }
    line1[0] = tmpLine[0];
    line1[1] = tmpLine[1];
    line1[2] = tmpLine[2];
    line1[3] = tmpLine[3];
}

float angleBetween2Lines(const Vec4f &line1, const Vec4f &line2){
    float angle = atan((line1[3]-line1[1])/(line1[2]-line1[0])) -
            atan((line2[3]-line2[1])/(line2[2]-line2[0]));
    return angle;
}

bool compareLinesOnAngleJoin(const Vec4f &line1, const Vec4f &line2){
    Vec4f tmpLine1(line1), tmpLine2(line2);
    sortPointInLine(tmpLine1);
    sortPointInLine(tmpLine2);
    const float compA = 5.0f, compB = 5.0f, compC = 5.0f;

    Vec3f equation1, equation2;

    equation1 = calcEquation(tmpLine1);
    equation2 = calcEquation(tmpLine2);

    if(abs(calcAngle(tmpLine1) - calcAngle(tmpLine2)) < 2.5f){
        return true;
    }
    else{
        return false;
    }
}

bool compare2linesOnNeighbor(const Vec4f &line1, const Vec4f &line2){
    Vec4f tmpLine1(line1), tmpLine2(line2);
    sortPointInLine(tmpLine1);
    sortPointInLine(tmpLine2);

    const float compA = 5.0f, compB = 5.0f, compC = 5.0f;

    Vec3f equation1, equation2;
    equation1 = calcEquation(tmpLine1);
    equation2 = calcEquation(tmpLine2);
//    if((abs(equation1[0] - equation2[0]) < compA)&&(abs(equation1[1] - equation2[1]) < compB)){
        std::cout << "\n";
        std::cout << "x1: " << tmpLine1[0] << " y1: " << tmpLine1[1] << " x2: " << tmpLine1[2] << " y2: " << tmpLine1[3] << "\n";
        std::cout << "x1: " << tmpLine2[0] << " y1: " << tmpLine2[1] << " x2: " << tmpLine2[2] << " y2: " << tmpLine2[3] << "\n";
        std::cout << "A: " <<equation1[0] << " B: " << equation1[1]<< " C: " << equation1[2] << " ";
         std::cout << "A: " <<equation2[0] << " B: " << equation2[1]<< " C: " << equation2[2] << "\n";
         std::cout << abs(equation1[0] - equation2[0]) << " " << abs(equation1[1] - equation2[1]) << " " << abs(equation1[2] - equation2[2]) << "\n";
        std::cout << "Condition: "<<(equation1[0]*equation2[1]) - (equation2[0]*equation1[1]) << "\n";
         //    }
}

Vec3f calcEquation(const Vec4f &line){
    Vec3f equation;

    equation[0] = line[1] - line[3];
    equation[1] = line[2] - line[0];
    equation[2] = (line[0]*line[3]) - (line[2]*line[1]);

    return equation;
}

float calcAngle(const Vec4f &line){
    return (atan(line[2]-line[0])/(line[3]-line[1])*180.0f)/3.14159265;
}

bool compare2LinesOnAngel(const Vec4f line1, const Vec4f line2)
{
    return (calcAngle(line1) < calcAngle(line2));
}
