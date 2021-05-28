#pragma once
#ifndef HUMOMENTS_H
#define HUMOMENTS_H
#include <math.h>
class myHuMoments
{
private:
    int width, height;
    double orginOfX, orginOfY;
    unsigned char* object;
    double huMoments[7];
public:
    myHuMoments(unsigned char* binaryImage, int width, int height);
    ~myHuMoments();

    double calcMoment(double p, double q);
    void calcOrgins();
    double calcOrginMoment(double p, double q);
    double calcNormalizedMoment(double p, double q);
    void calcInvariantMoments();
    double* getHuMoments();
    void logTransform();
};
#endif // HUMOMENTS_H