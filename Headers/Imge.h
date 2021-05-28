#include <Windows.h>
#include <cstdlib>
#include <stdio.h>
#include <time.h>
#include <string>
#include "Modules.h";

#pragma once

//Load BMP from File
BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);

//Convert BMP file to 8 byte Gray format
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height, long% size);

//Convert Gray BMP file to 24 bit RGB format
BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long% newsize);

//Save BMP to File
bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile);

//Find the index of the closest k value to the value. 
int Closest(int value, struct KVALUES* array, int size);

//Compare K Values with Center of Mass
bool CompareWithCenterOfMass(struct KVALUES* kValues, int kSize);

//Create Histogram Data array
void createHistogramDatas(int* histogramDatas, BYTE* img, long imageSize);

//K-Means Alghorithm
struct KVALUES* KMeans(int* histogram, long size, int k);

//Object labeling
BYTE* Labeling(BYTE* img, long size, int width, int height, int% numOfObject);

//Object Detection with bounding boxes
struct OBJECT* ObjectDetection(BYTE* labeledImage, int width, long size, int height, int numOfObject);

//Apply erosion to the image
void Erosion(BYTE* binaryImage, int width, int height, struct MASK mask);

//Apply dilation to the image
void Dilation(BYTE* binaryImage, int width, int height, struct MASK mask);

//Show objects from inside of image 
BYTE* ShowObjects(struct OBJECT* object, struct EXP_OBJECT exp_object, int width, int height, int numOfObject);

//Finding feature vectors and Save
double* Training(int itemSize, int objIndex, OBJECT* object, EXP_OBJECT* exp);

//Finding feature vectors and compare 
void Matching(int itemSize, OBJECT* object, int expObjectSize, EXP_OBJECT* exp);