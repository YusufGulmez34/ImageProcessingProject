#include "HelperCodes.h"
#include "Modules.h"

int smaller(int x, int y) { return x < y ? x : y; }

int bigger(int x, int y) { return x > y ? x : y; }

int arrayMax(int* arr, int size)
{
	int max = arr[0];
	for (int i = 1; i < size; i++)
		if (max < arr[i]) max = arr[i];

	return max;
}

void CloningToExpandedImage(int width, int height, BYTE* expandedImage, BYTE* binaryImage, struct MASK mask, int expandedImageWidth)
{
	// Cloning image values to expanded image
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			expandedImage[(row + mask.height / 2) * (expandedImageWidth)+col + mask.width / 2] = binaryImage[row * width + col];
}

void ReturnToUnexpandedSize(int width, int height, BYTE* binaryImage, BYTE* newBinaryImage, struct MASK mask, int expandedImageWidth)
{
	//return to unexpanded size
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			binaryImage[i * width + j] = newBinaryImage[(i + mask.height / 2) * (expandedImageWidth)+j + mask.width / 2];
}