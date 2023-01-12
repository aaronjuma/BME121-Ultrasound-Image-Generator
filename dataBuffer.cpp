/*
 * Assignment 4
 * dataBuffer.cpp
 * Aaron Jumarang
 * 21007028
 */
#include "dataBuffer.h"
using namespace std;

dataBuffer::dataBuffer()
{
    //Initializing the variables to default values
    numElement = 0;
    numSample = 0;
    scanline = 0;
    dataMatrix = NULL;
    next = NULL;
}

dataBuffer::dataBuffer( std::ifstream *imagFile, std::ifstream *realFile, int inputNumElement, int inputNumSample, int inputScanline)
{
    //Initializing the variables based on the values of parameters
    numElement = inputNumElement;
    numSample = inputNumSample;
    scanline = inputScanline;
    dataMatrix = createDataMatrix();
    loadRFData(dataMatrix, imagFile, realFile);
} 

dataBuffer::~dataBuffer()
{
    //Calls the function responsible for deleting the array
    deleteDataMatrix();
}

complex **dataBuffer::createDataMatrix()
{
    //Creates an empty 2D complex array
    complex **dataArray = new complex*[numElement];
    for(int i = 0; i < numElement; ++i){
        dataArray[i] = new complex[numSample];
    }

    //Returns the array
    return dataArray;
}

int dataBuffer::loadRFData(complex **RFData, std::ifstream *imagFile, std::ifstream *realFile) 
{ 
    //Creates placeholder array for input
    const int inputSize = 100;
    char input[inputSize];

    //Loops through each element and sample of the scanline 
    for(int i = 0; i < numElement; ++i){
        for(int j = 0; j < numSample; ++j){

            //Reads the imaginary data line, converts it to float, and assigned to the RFData array
            imagFile->getline(input, inputSize);
            RFData[i][j].imag = atof(input);

            //Reads the real data line, converts it to float, and assigned to the RFData array
            realFile->getline(input, inputSize);
            RFData[i][j].real = atof(input);
        }
    }

    //Returns 0 for success
    return 0;
}

float dataBuffer::getRealRFData(int element,int sample)
{
    //Returns the real value of the chosen element and sample
    return dataMatrix[element][sample].real;
}

float dataBuffer::getImagRFData(int element,int sample)
{
    //Returns the imaginary value of the chosen element and sample
    return dataMatrix[element][sample].imag;
}

void dataBuffer::deleteDataMatrix()
{
    //Deletes the data arrays
    for(int i = 0; i < numElement; ++i){
        delete [] dataMatrix[i];
    }
    delete [] dataMatrix;
}




