#pragma once
#include <Windows.h>
#include <wtypes.h>
#include <vector>
#include <tuple>
#include <algorithm>



#define PI 3.14159
//-1,-1,-1,0,0,0,1,1,1
//-1,0,1,-1,0,1,-1,0,1
struct MASK
{
	int size;
	double* matris;
	int width, height;

	MASK(int s, int status)
	{
		size = s;
		width = size;
		height = size;
		if (status == 1)
			matris = new double[size * size]{ -1,-1,-1,0,0,0,1,1,1 };

		else if (status == 2)
			matris = new double[size * size]{ -1,0,1,-1,0,1,-1,0,1 };
		else if (status == 3)
		{
			matris = new double[size * size];

			matris[0]  = 2; matris[1]  = 4;  matris[2]  = 5;  matris[3]  = 4;  matris[4] = 2;
			matris[5]  = 4; matris[6]  = 9;  matris[7]  = 12; matris[8]  = 9;  matris[9] = 4;
			matris[10] = 5; matris[11] = 12; matris[12] = 15; matris[13] = 12; matris[14] = 5;
			matris[15] = 4; matris[16] = 9;  matris[17] = 12; matris[18] = 9;  matris[19] = 4;
			matris[20] = 2; matris[21] = 4;  matris[22] = 5;  matris[23] = 4;  matris[24] = 2;

			/*for (int i = 0; i < size * size; i++)
			{
				matris[i] /=  (double)159;
			}*/

		}
	}

};
void histogram(int* array, int* img, int imgSize);
BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile);
BYTE* padding(BYTE* matris, int width, int height, int num);
int* padding2(int* matris, int width, int height, int num);
int* Gradiant(BYTE* rawImage, int* colImage, int* rowImage, int width, int height);
BYTE* ConvertToIntensity(BYTE* Buffer, unsigned int width, unsigned int height);
BYTE* GaussianFilter(BYTE* img, int width, int height);
int* Angles(int* rowOutputs, int* colOutputs, int width, int height);
int* NonMaxSupprising(int* angles, int* gradiantImage, int size, int width, int height);
void compareNgbr(int* paddingGradiantImage, int& changeValue, int gradiantIndex, int firstShift, int secondShift, int assigmentValue);
int OtsuThresholding(int* hist, int width, int height);
void followData(int* nonMaxSup, int index, int* angles, int Width, int Height, int tHigh, int tLow);

BYTE* LineDetection( int* BinaryEdgeInt, int Width, int Height, int Size, BYTE* rawIntensity);

BYTE* CircleDetection(int* BinaryEdgeInt, int Width, int Height, int Size, BYTE* raw_Intensity);


