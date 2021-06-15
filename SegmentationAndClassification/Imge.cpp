#include "Imge.h"
#include "HelperCodes.h"
#include "Hu_Moments.h"

#include "Modules.h"

//Load BMP from File
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
	if (ReadFile(file, &bmpheader, sizeof(BITMAPFILEHEADER), &bytesread, NULL) == false)
	{
		CloseHandle(file);
		return NULL;
	}
	//read bitmap info
	if (ReadFile(file, &bmpinfo, sizeof(BITMAPINFOHEADER), &bytesread, NULL) == false)
	{
		CloseHandle(file);
		return NULL;
	}
	// check if file is actually a bmp
	if (bmpheader.bfType != 'MB')
	{
		CloseHandle(file);
		return NULL;
	}
	// get image measurements
	width = bmpinfo.biWidth;
	height = abs(bmpinfo.biHeight);

	// check if bmp is uncompressed
	if (bmpinfo.biCompression != BI_RGB)
	{
		CloseHandle(file);
		return NULL;
	}
	// check if we have 24 bit bmp
	/*if (bmpinfo.biBitCount != 24) {
		CloseHandle(file);

		return NULL;
	}*/

	// create buffer to hold the data
	size = bmpheader.bfSize - bmpheader.bfOffBits;
	BYTE* Buffer = new BYTE[size];
	// move file pointer to start of bitmap data
	SetFilePointer(file, bmpheader.bfOffBits, NULL, FILE_BEGIN);
	// read bmp data
	if (ReadFile(file, Buffer, size, &bytesread, NULL) == false)
	{
		delete[] Buffer;
		CloseHandle(file);
		return NULL;
	}
	// everything successful here: close file and return buffer
	CloseHandle(file);

	return Buffer;
}//LOADPMB

//Convert BMP file to 8 byte Gray format
BYTE* ConvertBMPToIntensity(BYTE* Buffer, int width, int height, long% size)
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
	size = width * height;

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			newpos = row * width + column;
			bufpos = (height - row - 1) * psw + column * 3;
			newbuf[newpos] = BYTE(0.11 * Buffer[bufpos + 2] + 0.59 * Buffer[bufpos + 1] + 0.3 * Buffer[bufpos]);
		}

	return newbuf;
}//ConvetBMPToIntensity

//Convert Gray BMP file to 24 bit RGB format
BYTE* ConvertIntensityToBMP(BYTE* Buffer, int width, int height, long% newsize)
{
	// first make sure the parameters are valid
	if ((NULL == Buffer) || (width == 0) || (height == 0))
		return NULL;

	// now we have to find with how many bytes
	// we have to pad for the next DWORD boundary	

	int padding = 0;
	int scanlinebytes = width * 3;
	while ((scanlinebytes + padding) % 4 != 0)     // DWORD = 4 bytes
		padding++;
	// get the padded scanline width
	int psw = scanlinebytes + padding;
	// we can already store the size of the new padded buffer
	newsize = height * psw;

	// and create new buffer
	BYTE* newbuf = new BYTE[newsize];

	// fill the buffer with zero bytes then we dont have to add
	// extra padding zero bytes later on
	memset(newbuf, 0, newsize);

	// now we loop trough all bytes of the original buffer, 
	// swap the R and B bytes and the scanlines
	long bufpos = 0;
	long newpos = 0;
	for (int row = 0; row < height; row++)
		for (int column = 0; column < width; column++)
		{
			bufpos = row * width + column;     // position in original buffer
			newpos = (height - row - 1) * psw + column * 3;           // position in padded buffer
			newbuf[newpos] = Buffer[bufpos];       //  blue
			newbuf[newpos + 1] = Buffer[bufpos];   //  green
			newbuf[newpos + 2] = Buffer[bufpos];   //  red
		}

	return newbuf;
} //ConvertIntensityToBM

//Save BMP to File
bool SaveBMP(BYTE* Buffer, int width, int height, long paddedsize, LPCTSTR bmpfile)
{
	// declare bmp structures 
	BITMAPFILEHEADER bmfh;
	BITMAPINFOHEADER info;

	// andinitialize them to zero
	memset(&bmfh, 0, sizeof(BITMAPFILEHEADER));
	memset(&info, 0, sizeof(BITMAPINFOHEADER));

	// fill the fileheader with data
	bmfh.bfType = 0x4d42;       // 0x4d42 = 'BM'
	bmfh.bfReserved1 = 0;
	bmfh.bfReserved2 = 0;
	bmfh.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + paddedsize;
	bmfh.bfOffBits = 0x36;		// number of bytes to start of bitmap bits

	// fill the infoheader

	info.biSize = sizeof(BITMAPINFOHEADER);
	info.biWidth = width;
	info.biHeight = height;
	info.biPlanes = 1;			// we only have one bitplane
	info.biBitCount = 24;		// RGB mode is 24 bits
	info.biCompression = BI_RGB;
	info.biSizeImage = 0;		// can be 0 for 24 bit images
	info.biXPelsPerMeter = 0x0ec4;     // paint and PSP use this values
	info.biYPelsPerMeter = 0x0ec4;
	info.biClrUsed = 0;			// we are in RGB mode and have no palette
	info.biClrImportant = 0;    // all colors are important

	// now we open the file to write to
	HANDLE file = CreateFile(bmpfile, GENERIC_WRITE, FILE_SHARE_READ,
		NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file == NULL)
	{
		CloseHandle(file);
		return false;
	}
	// write file header
	unsigned long bwritten;
	if (WriteFile(file, &bmfh, sizeof(BITMAPFILEHEADER), &bwritten, NULL) == false) {
		CloseHandle(file);
		return false;
	}
	// write infoheader
	if (WriteFile(file, &info, sizeof(BITMAPINFOHEADER), &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}
	// write image data
	if (WriteFile(file, Buffer, paddedsize, &bwritten, NULL) == false)
	{
		CloseHandle(file);
		return false;
	}

	// and close file
	CloseHandle(file);

	return true;
} // SaveBMP

//Find the index of the closest k value to the value. 
int Closest(int value, struct KVALUES* array, int kSize)
{
	int IndexOfClosestValue = 0;
	float firstDistance;
	float secondDistance;

	struct KVALUES closestValue = array[0];

	for (int kIndex = 1; kIndex < kSize; kIndex++)
	{
		firstDistance = abs(closestValue.kValue - value);
		secondDistance = abs(array[kIndex].kValue - value);

		if (firstDistance > secondDistance)
		{
			closestValue = array[kIndex];
			IndexOfClosestValue = kIndex;
		}
	}

	return IndexOfClosestValue;
}

//Create Histogram Data array
void createHistogramDatas(int* histogramDatas, BYTE* img, long imageSize)
{
	for (int pixelValue = 0; pixelValue < 256; pixelValue++)
	{
		int sum = 0;
		for (int imageDataIndex = 0; imageDataIndex < imageSize; imageDataIndex++)
			if (pixelValue == img[imageDataIndex]) sum++;

		histogramDatas[pixelValue] = sum;
	}
}

//K-Means Alghorithm
struct KVALUES* KMeans(int* histogram, long size, int kSize)
{
	struct KVALUES* kValues = (struct KVALUES*)malloc(sizeof(struct KVALUES) * kSize);

	srand(time(0));

	for (int kIndex = 0; kIndex < kSize; kIndex++)
	{
		kValues[kIndex].sumOfCloseValues = 0;
		kValues[kIndex].extentValue = 0;
		kValues[kIndex].kValue = rand() % 256;
		kValues[kIndex].brightnessAssignment = rand() % 256;
		kValues[kIndex].isEqualToAverage = false;
	}

	if (kSize == 2)
	{
		kValues[0].brightnessAssignment = 255;
		kValues[1].brightnessAssignment = 0;
	}

	while (true)
	{
		for (int value = 0; value < 256; value++)
		{
			int kIndex = Closest(value, kValues, kSize);
			kValues[kIndex].sumOfCloseValues += histogram[value];
			kValues[kIndex].extentValue += histogram[value] * value;
		}

		if (CompareWithCenterOfMass(kValues, kSize)) break;
	}

	return kValues;
}

//Compare K Values with Center of Mass
bool CompareWithCenterOfMass(struct KVALUES* kValues, int kSize)
{
	//center of mass that values of close to k value
	float centerOfMass;

	//between center of mass with k value
	float distance;
		 
	float extent_value;
	float sum_of_close_values; 

	for (int kIndex = 0; kIndex < kSize; kIndex++)
	{
		centerOfMass = 0;

		//denominator can not be zero
		if (kValues[kIndex].sumOfCloseValues != 0)
		{
			extent_value = kValues[kIndex].extentValue;				//numerator
			sum_of_close_values = kValues[kIndex].sumOfCloseValues; //denominator
			centerOfMass = extent_value / sum_of_close_values;
		}

		//between center of mass with k value
		distance = abs(centerOfMass - kValues[kIndex].kValue);

		if (kValues[kIndex].isEqualToAverage == false)
		{
			if (distance <= 0.001/*deviation value*/) kValues[kIndex].isEqualToAverage = true;
			else kValues[kIndex].kValue = centerOfMass;
		}

	}
	//check all of them are equal whit their k value
	bool isEqual = true;
	for (int kIndex = 0; kIndex < kSize; kIndex++)
		if (kValues[kIndex].isEqualToAverage == false) isEqual = false;

	return isEqual;
}

//Object Detection with bounding boxes
struct OBJECT* ObjectDetection(BYTE* labeledImage, int width, long size, int height, int numOfObject)
{
	struct OBJECT* objects = (struct OBJECT*)malloc(sizeof(struct OBJECT) * numOfObject);

	int labelValue;
	for (int i = 0; i < numOfObject; i++)
	{
		labelValue = i + 1;
		objects[i].objectLabel = labelValue;
	}//Setting label label value to objects

	int min_col;
	int min_row;
	int max_col;
	int max_row;
	int label;

	//Bounding Box
	for (int objectIndex = 0; objectIndex < numOfObject; objectIndex++)
	{
		label = objectIndex + 1;

		// Finding bounding box 
		bool isStarting = false;//the begining point of Object
		int index;
		for (int row = 0; row < height; row++)
			for (int col = 0; col < width; col++)
			{
				index = row * width + col;

				if (labeledImage[index] == label && !isStarting)
				{
					min_col = col;		// First value of min_col
					max_col = col;		// First value of max_col
					min_row = row;		// First value of min_row
					max_row = row;		// First value of max_row
					isStarting = true;
				}
				else if (labeledImage[index] == label && isStarting) 
				{
					min_col = min_col < col ? min_col : col;
					max_col = max_col > col ? max_col : col;
					min_row = min_row < row ? min_row : row;
					max_row = max_row > row ? max_col : row;
				}
			}
		
		//setting bounding box infos and object images
		objects[objectIndex].maxColumnValue = max_col;
		objects[objectIndex].minColumnValue = min_col;
		objects[objectIndex].maxRowValue = max_row;
		objects[objectIndex].minRowValue = min_row;
		objects[objectIndex].itemWidth = max_col - min_col + 1;
		objects[objectIndex].itemHeight = max_row - min_row + 1;
		objects[objectIndex].itemSize = (max_col - min_col + 1) * (max_row - min_row + 1);
		objects[objectIndex].image = (BYTE*)malloc(sizeof(BYTE) * objects[objectIndex].itemSize);

		// Setting image info of per object
		int imageIndex = 0;
		for (int i = min_row; i < max_row + 1; i++)
			for (int j = min_col; j < max_col + 1; j++)
			{
				if (labeledImage[i * width + j] == objects[objectIndex].objectLabel)
					objects[objectIndex].image[imageIndex++] = 255;

				else objects[objectIndex].image[imageIndex++] = 0;
			}

	}//Bounding Box

	free(labeledImage);
	return objects;
} 

//Object labeling
BYTE* Labeling(BYTE* img, long size, int width, int height, int %numOfObject)
{
	
	int sizeOfTable = (height + 1) * (width + 1);					/// The table to be labeled is the
	BYTE* labelTable = (BYTE*)malloc(sizeof(BYTE) * sizeOfTable);	///	enlargement of the main picture by
	memset(labelTable, 0, sizeOfTable);								/// 1 unit from the upper and left.


	int index;		// index of Main picture
	int tableIndex; // index of labeling table
	int label = 0;	// assigment label value
	int upperNeighbor;
	int leftNeighbor;

	/// Labeling
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
		{
			index = row * width + col;							
			tableIndex = (row + 1) * (width + 1) + (col + 1);  // The place where the index value corresponds to the label table

			upperNeighbor = labelTable[tableIndex - width - 1];
			leftNeighbor = labelTable[tableIndex - 1];

			
			if (img[index] == 255) {

				if (leftNeighbor == 0 && upperNeighbor == 0)
					labelTable[tableIndex] = ++label; // new label value

				//Collision Case
				else if (upperNeighbor != 0 && leftNeighbor != 0 && upperNeighbor != leftNeighbor)
				{
					int smallValue = smaller(leftNeighbor, upperNeighbor);
					int bigValue = bigger(leftNeighbor, upperNeighbor);

					labelTable[tableIndex] = smallValue; // assign small value

					//scan previous values
					for (int i = 0; i <= tableIndex; i++) 
					{
						if (bigValue == labelTable[i])	//Set small value to
							labelTable[i] = smallValue; //big value

						if (bigValue < labelTable[i])	// label values must be 
							labelTable[i]--;			// consecutive

					}// Scan previous values

					label--;
				}//Colision Case

				else if (leftNeighbor != 0)
					labelTable[tableIndex] = leftNeighbor;

				else if (upperNeighbor != 0)
					labelTable[tableIndex] = upperNeighbor;
			}


		}
	numOfObject = label;
	//return to the unexpanded size
	BYTE* newLabelTable = (BYTE*)malloc(sizeof(BYTE) * size);
	for (int row = 0; row < height; row++)
		for (int col = 0; col < width; col++)
			newLabelTable[row * width + col] = labelTable[(row + 1) * (width + 1) + col + 1];

	free(labelTable);
	return newLabelTable;
}

//Apply erosion to the image
void Erosion(BYTE* binaryImage, int width, int height, struct MASK mask)
{
	int expandedImageWidth = (width + 2 * (mask.width / 2));			// The image to be scanned should be
	int expandedImageHeight = (height + 2 * (mask.height / 2));			// enlarged from the edges
	int expandedImageSize = expandedImageHeight * expandedImageWidth;	// according to the size of the mask.
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	BYTE* expandedImage = (BYTE*)malloc(sizeof(BYTE) * expandedImageSize); 
	BYTE* newBinaryImage = (BYTE*)malloc(sizeof(BYTE) * expandedImageSize);   

	memset(expandedImage, 0, expandedImageWidth * expandedImageHeight);
	memset(newBinaryImage, 0, expandedImageWidth * expandedImageHeight);

	CloningToExpandedImage(width, height, expandedImage, binaryImage, mask, expandedImageWidth);

	
	
	//Erosion
	int currentIndex;
	for (int row = 0; row < expandedImageHeight; row++)
		for (int col = 0; col < expandedImageWidth; col++)
		{
			currentIndex = row * (expandedImageWidth) + col;

			if (expandedImage[currentIndex] == 255) {

				bool areAllOfThemOne = true;
				int scanIndex;
				int startRow = row - (mask.height / 2); 
				int startCol = col - (mask.width / 2);

				//Scaning area
				for (int scanRow = startRow; scanRow < startRow + mask.height; scanRow++)
					for (int scanCol = startCol; scanCol < startCol + mask.width; scanCol++)
					{
						scanIndex = scanRow * (expandedImageWidth) + scanCol;

						if (expandedImage[scanIndex] == 0)
						{
							newBinaryImage[currentIndex] = 0;
							areAllOfThemOne = false;
						}
					}

				if (areAllOfThemOne) newBinaryImage[currentIndex] = 255;
			}
		}
	
	ReturnToUnexpandedSize(width, height, binaryImage, newBinaryImage, mask, expandedImageWidth);

	free(expandedImage);
	free(newBinaryImage);
}

//Apply dilation to the image
void Dilation(BYTE* binaryImage, int width, int height, struct MASK mask)
{
	int expandedImageWidth = (width + 2 * (mask.width / 2));			// The image to be scanned should be
	int expandedImageHeight = (height + 2 * (mask.height / 2));			// enlarged from the edges
	int expandedImageSize = expandedImageHeight * expandedImageWidth;	// according to the size of the mask.

	BYTE* expandedImage = (BYTE*)malloc(sizeof(BYTE) * expandedImageSize);
	BYTE* newBinaryImage = (BYTE*)malloc(sizeof(BYTE) * expandedImageSize);
	memset(expandedImage, 0, expandedImageWidth * expandedImageHeight);
	memset(newBinaryImage, 0, expandedImageWidth * expandedImageHeight);

	CloningToExpandedImage(width, height, expandedImage, binaryImage, mask, expandedImageWidth);

	//Dilation
	int currentIndex;
	for (int row = 0; row < expandedImageHeight; row++)
		for (int col = 0; col < expandedImageWidth; col++)
		{
			currentIndex = row * (expandedImageWidth)+col;

			if (expandedImage[currentIndex] == 255)
			{
				int scanIndex;
				int startRow = row - (mask.height / 2);
				int startCol = col - (mask.width / 2);

				for (int scanRow = startRow; scanRow < startRow + mask.height; scanRow++)
					for (int scanCol = startCol; scanCol < startCol + mask.width; scanCol++)
					{
						scanIndex = scanRow * (expandedImageWidth)+scanCol;
						newBinaryImage[scanIndex] = 255;
					}
			}
		}
	
	ReturnToUnexpandedSize(width, height, binaryImage, newBinaryImage, mask, expandedImageWidth);

	free(expandedImage);
	free(newBinaryImage);
}

//Show objects from inside of image 
BYTE* ShowObjects(struct OBJECT* object, struct EXP_OBJECT exp_object, int width, int height, int numOfObject)
{
	BYTE* newImage = (BYTE*)malloc(sizeof(BYTE) * width * height);
	memset(newImage, 0, width * height);

	struct OBJECT obj;

	for (int i = 0; i < numOfObject; i++)
	{
		obj = object[i];
		if (obj.objectName == exp_object.name)
		{
			int imageIndex = 0;
			for (int row = obj.minRowValue; row < obj.maxRowValue + 1; row++)
				for (int col = obj.minColumnValue; col < obj.maxColumnValue + 1; col++)
					newImage[row * width + col] = obj.image[imageIndex++];
		}
	}

	return newImage;
}

//Finding feature vectors and Save
double* Training(int itemSize, int objIndex, OBJECT* object, EXP_OBJECT* exp)
{
	double* arraySum = new double[7]{0};
	int temp = itemSize;

	for (int i = 0; i < itemSize; i++)
	{
		struct OBJECT obj = object[i];

		myHuMoments* moment = new myHuMoments(obj.image, obj.itemWidth, obj.itemHeight);
		double* momentFi = moment->getHuMoments();
		moment->logTransform();
		for (int j = 0; j < 7; j++) {
			arraySum[j] += fabs(momentFi[j]);
		}

	}

	for (int i = 0; i < 7; i++) {
		arraySum[i] /= temp;
		exp[objIndex].moments[i] = arraySum[i];
	}
	exp[objIndex].name = objIndex;

	return arraySum;
}

//Finding feature vectors and compare 
void Matching(int itemSize, OBJECT *object, int expObjectSize, EXP_OBJECT *exp)
{
	double distance;
	double minDis;
	int objectName;
	for (int i = 0; i < itemSize; i++)
	{
		OBJECT obj = object[i];

		myHuMoments* huMoments = new myHuMoments(obj.image, obj.itemWidth, obj.itemHeight);

		double* fiMoments = huMoments->getHuMoments();

		huMoments->logTransform();

		minDis = System::Double::MaxValue;

		objectName = 0;

		for (int j = 0; j < expObjectSize; j++)
		{
			distance = 0;
			for (int k = 0; k < 7; k++)
			{
				distance += pow(fabs(fiMoments[k]) - fabs(exp[j].moments[k]), 2);
			}
			distance = sqrt(distance);
			if (minDis >= distance)
			{
				minDis = distance;
				objectName = j;
			}
		}
		object[i].objectName = objectName;
		
	}
}