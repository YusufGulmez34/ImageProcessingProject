#include <wtypes.h>
#include <string>
#include <Windows.h>
#include <string>
#pragma once

struct KVALUES
{
	int brightnessAssignment;
	float kValue;
	int sumOfCloseValues;
	float extentValue;
	bool isEqualToAverage;
};

struct OBJECT
{
	int minColumnValue;
	int minRowValue;
	int maxColumnValue;
	int maxRowValue;
	int itemSize;
	int itemWidth;
	int itemHeight;
	int objectLabel;
	int objectName;
	BYTE* image;
};
struct EXP_OBJECT 
{
	int name;
	double moments[7];
};

struct MASK
{
	int width;
	int height;
};