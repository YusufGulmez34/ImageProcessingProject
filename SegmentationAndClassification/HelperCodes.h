#include <stdio.h>
#include "Imge.h";
#pragma once

int smaller(int x, int y);

int bigger(int x, int y);

int arrayMax(int* arr, int size);

void CloningToExpandedImage(int width, int height, BYTE* expandedImage, BYTE* binaryImage, struct MASK mask, int expandedImageWidth);

void ReturnToUnexpandedSize(int width, int height, BYTE* binaryImage, BYTE* newBinaryImage, struct MASK mask, int expandedImageWidth);