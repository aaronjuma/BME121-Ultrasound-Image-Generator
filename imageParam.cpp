/*
 * Assignment 4
 * imageParam.cpp
 * Aaron Jumarang
 * 21007028
 */
#include "imageParam.h"
using namespace std;

imageParam::imageParam()
{
    //Initializes the variables with their appropriate values
    numElement = 128;
    numSample = 3338;
    numScanline = 127;

    //Assigns elementPosition with an array containing the element positions
    elementPosition = genElementPosition();

    //Assigns scanlinePosition with an array containing the scanline positions
    scanlinePosition = genScanlinePosition(numScanline, PITCH, elementPosition);
}

imageParam::~imageParam()
{
    deletePositionArray();
}

// Create an array containing the element location (in x-direction) of the ultrasound transducer
float *imageParam::genElementPosition()
{

    //Creates an empty array
    float *elementArray = new float[numElement];

    //Populates the array with the element positions
    for(int i = 0; i < numElement; i++){
        elementArray[i] = (i - (numElement-1.0)/2.0) * PITCH;
    }

    //Returns the array
    return elementArray;
}

float2 **imageParam::genScanlinePosition(int numScanline, const float PITCH, float* elementLocation)
{
    //Prompts user for the depth and number of pixels
    cout << "Input desired depth: ";
    cin >> desiredDepth;
    cout << "Input desired number of pixels: ";
    cin >> numPixel;

    //Creates a 2D array
    float2 **scanlineArray = new float2*[numScanline];

    //Loops through the 2D array
    for(int i = 0; i < numScanline; ++i){

        //Initializes a new array for each index in the 2D array
        scanlineArray[i] = new float2[numPixel];

        //Populates the array with the scanline positions
        for(int j = 0; j < numPixel; ++j){
            scanlineArray[i][j].x = (i - (numScanline-1.0)/2.0) * PITCH;
            scanlineArray[i][j].y = (desiredDepth/(numPixel-1.0)) * j;
        }

    }

    //Returns the 2D array
    return scanlineArray;
}

float imageParam::getXPosition(int scanline, int pixel)
{
    //Returns the value of the x position of the corresponding scanline and pixel
    return scanlinePosition[scanline][pixel].x;
}

float imageParam::getYPosition(int scanline, int pixel)
{
    //Returns the value of the y position of the corresponding scanline and pixel
    return scanlinePosition[scanline][pixel].y;
}

float imageParam::getElementPosition(int element)
{
    //Returns the value of element position of the corresponding element
    return elementPosition[element];
}

int imageParam::getNumElement()
{
    //Returns the number of elements
    return numElement;
}

int imageParam::getNumSample()
{
    //Returns the number of samples
    return numSample;
}

int imageParam::getNumScanline() 
{
    //Returns the number of scanlines
    return numScanline;
}

int imageParam::getNumPixel() 
{
    //Returns the number of pixels
    return numPixel;
}

void imageParam::deletePositionArray()
{
    //Deletes the arrays
    delete [] elementPosition;
    for(int i = 0; i < numScanline; i++){
        delete [] scanlinePosition[i];
    }
    delete [] scanlinePosition;
}









