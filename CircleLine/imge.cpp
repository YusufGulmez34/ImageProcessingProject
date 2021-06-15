#include "imge.h"
#include <iostream>

BYTE* LoadBMP(int% width, int% height, long% size, LPCTSTR bmpfile)
{
	// declare bitmap structures
	BITMAPFILEHEADER bmpheader;
	BITMAPINFOHEADER bmpinfo;
	// value to be used in ReadFile funcs
	DWORD bytesread;
	// open file to read from
	HANDLE file = CreateFile(bmpfile, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (NULL == file)
		return NULL; // coudn't open file

	// read file header
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false) {
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB') {
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB) {
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	/*
	if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);
		return NULL;
	}
	*/
	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false) {
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADP

BYTE* ConvertToIntensity(BYTE* Buffer, unsigned int width, unsigned int height)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// find the number of padding bytes

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;

	// create new buffer
	BYTE* newbuf = new BYTE[width * height];

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++) {
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11 * Buffer[bufpos + 2] + 0.59 * Buffer[bufpos + 1] + 0.3 * Buffer[bufpos]);
		}

	return newbuf;
}//ConvetToIntensity

int* Gradiant(BYTE* rawImage, int* colImage, int* rowImage, int width, int height)
{
	MASK rowMask(3, 1);
	MASK colMask(3, 2);
	int paddingWidth = (width + 2 * (rowMask.size / 2));
	int peddingHeight = (height + 2 * (colMask.size / 2));
	int peddingSize = paddingWidth * peddingHeight;
	BYTE* tempImage = new BYTE[peddingSize]{ 0 };
	int* gradiantImage = new int[width * height]{ 0 };



	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
		{
			int Index = (row + rowMask.size / 2) * paddingWidth + col + colMask.size / 2;
			tempImage[Index] = rawImage[row * width + col];
		}


	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int rowSum = 0;
			int colSum = 0;
			int maskIndex = 0;
			for (int i = row; i < row + rowMask.size; i++)
			{
				for (int j = col; j < col + rowMask.size; j++)
				{
					rowSum += tempImage[i * paddingWidth + j] * (int)rowMask.matris[maskIndex];
					colSum += tempImage[i * paddingWidth + j] * (int)colMask.matris[maskIndex++];

				}
			}
			rowImage[(row)*width + col] = rowSum;
			colImage[row * width + col] = colSum;
			gradiantImage[row * width + col] = abs(rowSum) + abs(colSum);
		}
	}

	delete tempImage;
	
	return gradiantImage;
}

BYTE* padding(BYTE* matris, int width, int height, int num)
{
	BYTE* temp = new BYTE[(2 * num + width) * (2 * num + height)]{ 0 };
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			temp[(i + num) * (width + num * 2) + j + num] = matris[i * width + j];

	return temp;
}

int* padding2(int* matris, int width, int height, int num)
{
	int* temp = new int[(2 * num + width) * (2 * num + height)]{ 0 };
	for (int i = 0; i < height; i++)
		for (int j = 0; j < width; j++)
			temp[(i + num) * (width + num * 2) + j + num] = matris[i * width + j];

	return temp;
}

BYTE* GaussianFilter(BYTE* img, int width, int height)
{
	MASK GaussianFilter(5, 3);

	BYTE* tempImg = padding(img, width, height, 5 / 2);


	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int index = row * width + col;

			int maskIndex = 0;
			double sum = 0;
			for (int i = row; i < row + GaussianFilter.size; i++)
			{
				for (int j = col; j < col + GaussianFilter.size; j++)
				{
					int scanIndex = i * (width + 2 * (5 / 2)) + j;
					sum += (GaussianFilter.matris[maskIndex++] * (double)tempImg[scanIndex]) / (double)159;
				}
			}
			img[index] = (BYTE)sum;
		}
	}
	delete tempImg;
	return img;
}

int* Angles( int* rowOutputs, int* colOutputs, int width, int height)
{

	int* angles = new int[width * height];

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (rowOutputs[i * width + j] == 0 && colOutputs[i * width + j] == 0) {
				angles[i * width + j] = -1;

			}
			else
			{
				double thisAngle = (atan2(rowOutputs[i * width + j], colOutputs[i * width + j]) / PI) * 180.0;
				int newAngle;
				if (((thisAngle < 22.5) && (thisAngle > -22.5)) || (thisAngle > 157.5) || (thisAngle < -157.5))
					newAngle = 0;
				if (((thisAngle > 22.5) && (thisAngle < 67.5)) || ((thisAngle < -112.5) && (thisAngle > -157.5)))
					newAngle = 45;
				if (((thisAngle > 67.5) && (thisAngle < 112.5)) || ((thisAngle < -67.5) && (thisAngle > -112.5)))
					newAngle = 90;
				if (((thisAngle > 112.5) && (thisAngle < 157.5)) || ((thisAngle < -22.5) && (thisAngle > -67.5)))
					newAngle = 135;

				angles[i * width + j] = newAngle;
			}

		}
	}
	return angles;
}

int* NonMaxSupprising(int* angles, int* gradiantImage, int size, int width, int height)
{
	int* paddingGradiantImage = padding2(gradiantImage, width, height, 1);
	int* nonMaxSup = new int[width * height]{ 0 };
	for (int row = 0; row < height; row++)
	{
		for (int col = 0; col < width; col++)
		{
			int currentIndex = row * width + col;
			int gradiantIndex = (row + 1) * (width+2) + (col + 1);
			int value = paddingGradiantImage[gradiantIndex];
			int firstPoint = 0, secondPoint = 0;



			int angle = angles[currentIndex];
			if (angle == 0)
			{
				compareNgbr(paddingGradiantImage, nonMaxSup[currentIndex], gradiantIndex, -1, +1, value);
			}
			else if (angle == 45)
			{
				compareNgbr(paddingGradiantImage, nonMaxSup[currentIndex], gradiantIndex, -width + 1, width - 1, value);
			}

			else if (angle == 90)
			{
				compareNgbr(paddingGradiantImage, nonMaxSup[currentIndex], gradiantIndex, -width, width, value);
			}

			else if (angle == 135)
			{
				compareNgbr(paddingGradiantImage, nonMaxSup[currentIndex], gradiantIndex, -width - 1, width + 1, value);
			}
			else nonMaxSup[currentIndex] = 0;
		}
	}

	return nonMaxSup;

}

int OtsuThresholding(int* hist, int width, int height)
{
	float sum = 0;
	float sumB = 0;
	int q1 = 0;
	int q2 = 0;
	float varMax = 0;
	int threshold = 0;
	int N = width * height;

	// Auxiliary value for computing m2
	for (int i = 0; i <= 1020; i++) {
		sum += i * hist[i];
	}

	for (int i = 0; i <= 1020; i++) {
		// Update q1
		q1 += hist[i];
		if (q1 == 0)
			continue;
		// Update q2
		q2 = N - q1;

		if (q2 == 0)
			break;
		// Update m1 and m2
		sumB += (float)(i * hist[i]);
		float m1 = sumB / q1;
		float m2 = (sum - sumB) / q2;

		// Update the between class variance
		float varBetween = (float)q1 * (float)q2 * (m1 - m2) * (m1 - m2);

		// Update the threshold if necessary
		if (varBetween > varMax) {
			varMax = varBetween;
			threshold = i;
		}
	}
	return threshold;
}

void histogram(int* array, int* img, int imgSize)
{
	for (int i = 0; i < imgSize; i++)
		array[img[i]] ++;
}

void compareNgbr(int* paddingGradiantImage, int& changeValue, int gradiantIndex, int firstShift, int secondShift, int assigmentValue)
{
	int firstNgbr = paddingGradiantImage[gradiantIndex + firstShift];
	int secondNgbr = paddingGradiantImage[gradiantIndex + secondShift];
	changeValue = (assigmentValue < firstNgbr || assigmentValue < secondNgbr) ? 0 : assigmentValue;

}

void followData(int* nonMaxSup, int index, int* angles, int Width, int Height, int tHigh, int tLow)
{
	using namespace std;
	vector<tuple<int, int>> keep;

	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			int point = nonMaxSup[i * Width + j];

			if (point > tHigh)
			{
				keep.push_back(make_tuple(i, j));
				nonMaxSup[i * Width + j] = 1020;
			}
			else if (point < tLow) {
				nonMaxSup[i * Width + j] = 0;
			}
		}
	}
	bool isNotEmpty = true;
	vector< tuple<int, int>> tempKeep = keep;
	while (!tempKeep.empty()) {

		vector< tuple<int, int>> newKeep;

		for (auto point : tempKeep)
		{
			int x = get<1>(point);
			int y = get<0>(point);
			for (int a = -1; a <= 1; a++)
			{
				for (int b = -1; b <= 1; b++)
				{
					if (a != 0 && b != 0)
					{
						int index = (y + b) * Width + x + a;
						if (index - y * Width < 0 || index - (y + 1) * Width == 0 || index < 0 || index > Width * Height)
							continue;

						if (nonMaxSup[index] > tLow && keep.end() == find(keep.begin(), keep.end(), make_tuple((y + b), (x + a)))) {

							newKeep.push_back(make_tuple((y + b), (x + a)));
						}
					}
				}

			}
		}

		keep.insert(keep.end(), newKeep.begin(), newKeep.end());


		tempKeep = newKeep;
	}

	for (auto point : keep)
	{

		int x = get<1>(point);
		int y = get<0>(point);
		nonMaxSup[y * Width + x] = 1020;
	}

	for (int i = 0; i < Height; i++)
		for (int j = 0; j < Width; j++)
		{
			if (nonMaxSup[i * Width + j] != 1020 && nonMaxSup[i * Width + j] != 0)
			{
				nonMaxSup[i * Width + j] = 0;
			}
		}
	

}

BYTE* LineDetection( int* BinaryEdgeInt, int Width, int Height, int Size, BYTE* rawIntensity)
{
	int houghWidth = 180;
	int houghArray[1000][181]{ 0 };
	int a = 0, b = 0;
	std::vector<std::tuple<int, int, int>> houghVec;
	for (int row = 0; row < Height; row++)
		for (int col = 0; col < Width ; col++)
		{
			if (BinaryEdgeInt[row * Width + col] == 1020) {
				for (int t = 0; t <= 180; t++)
				{
					int d = (int)abs(col * cos(t) + row * sin(t));
					houghArray[d][t]++;
				}
			}
		}

	//reduct d values
	for (int d = 0; d < 1000; d++)
		for (int t = 0; t <= houghWidth; t++)
		{
			if (houghArray[d][t] != 0)
			{
				int newD = d - d % 3;
				houghArray[newD][t] += houghArray[d][t];
				houghArray[d][t] = 0;

			}

		}


	for (int i = 0; i < 1000; i++) {

		for (int j = 0; j <= houghWidth; j++) {

			if (houghArray[i][j] != 0) {

				houghVec.push_back(std::make_tuple(houghArray[i][j], i, j));

			}
		}
	}


	sort(houghVec.begin(), houghVec.end());
	for (int i = houghVec.size() - 1; i > houghVec.size() - 6; i--)
	{
		int d = std::get<1>(houghVec[i]);
		int t = std::get<2>(houghVec[i]);
		for (int x = 0; x < Width; x++) {

			int y = (int)(d - x * cos(t)) / sin(t);
			rawIntensity[y * Width + x] = 255;
		}
	}

	return rawIntensity;
}

BYTE* CircleDetection(int* BinaryEdge, int Width, int Height, int Size, BYTE* raw_Intensity)
{
	int maxRadius = Width / 4;
	std::vector<std::tuple<int, int, int, int> > hougchVec;
	int* houghArray = new int[Width * Height * maxRadius]{ 0 };
	for (int row = 0; row < Height; row++)
		for (int col = 0; col < Width; col++)
		{
			int index = row * Width + col;
			if (BinaryEdge[index] == 1020) {

				for (int radius = 10; radius < maxRadius; radius++)
					for (int angle = 0; angle <= 360; angle++)
					{
						int a = (int)(col - radius * cos(angle * PI / 180));
						int b = (int)(row + radius * sin(angle * PI / 180));
						if (a >= 0 && a < Width && b >= 0 && b < Height) {
							int houghArrayIndex = (b * Width * maxRadius) + (a * maxRadius) + radius;
							houghArray[houghArrayIndex]++;
						}
					}
			}
		}



	int maxValue = 0, r = 0, a = 0, b = 0;

	for (int row = 0; row < Height; row++)
		for (int col = 0; col < Width; col++) 

			for (int radius = 10; radius < maxRadius; radius++)
			{
				int index = (row * Width * maxRadius) + (col * maxRadius) + radius;
				if (houghArray[index] > 0)
				{
					hougchVec.push_back(std::make_tuple(houghArray[index], row, col, radius));
				}

			}

		
	sort(hougchVec.begin(), hougchVec.end());
	int x, y;

	for (int i = hougchVec.size() - 1; i > hougchVec.size() - 10; i--) {
		b = std::get<1>(hougchVec[i]);
		a = std::get<2>(hougchVec[i]);
		r = std::get<3>(hougchVec[i]);
		for (int j = 0; j <= 360; j++) {
			x = a + r * cos(j);
			y = b - r * sin(j);
			raw_Intensity[y * Width + x] = 255;
		}

	}

	return raw_Intensity;
}