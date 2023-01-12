/*
 * Assignment 4
 * BmodeClass.cpp
 * Aaron Jumarang
 * 21007028
 */
#include "BmodeClass.h"

BmodeClass::BmodeClass()
{
    //Initializing the variables to default values
    imparams = NULL;
    RFData = NULL;
    next = NULL;
    line = 0;
}

BmodeClass::BmodeClass(imageParam *params,dataBuffer *data,int numline)
{
    //Initializing the variables based on the values of parameters
    imparams = params;
    RFData = data;
    line = numline;

    //Assigns scanline with a generated empty array
    scanline = createScanline(imparams->getNumPixel());

    //Performs the beamform
    beamform();
}

BmodeClass::~BmodeClass()
{
    //Calls the function responsible for deleting the arrays
    deleteScanline();
}

float *BmodeClass::createScanline(int numPixel)
{
    //Create and allocates an array
    float *mem = new float[numPixel];

    //Returns the array
    return mem;
}

void BmodeClass::beamform()
{
   //Create placeholder variables for the summed real and imaginary values for each iteration
    float real;
    float imag;

    //Placeholder variables for the speed of sound and the element value 
    float SoS = imparams->SOS;
    float element;
    
    //Placeholder variables for the x and y position of the scanline
    float x;
    float y;

    //Loops through each pixel
    for(int i = 0; i < imparams->getNumPixel(); ++i){

        //Resets the placeholder values
        real = 0;
        imag = 0;

        //Gets the new x and y positions
        x = imparams->getXPosition(line,i);
        y = imparams->getYPosition(line,i);

        //Loops through each element
        for(int k = 0; k < imparams->getNumElement(); ++k){

            //Gets the new element value
            element = imparams->getElementPosition(k);

            //Calculates the time taken
            float tForward = y / SoS;
            float tBackward = sqrt(pow(y,2) + pow(x-element,2)) / SoS;
            float tTotal = tForward+tBackward;


            //Calculates the sample value
            int sample = floor(tTotal * imparams->FS);

            //Sums up the values
            if(sample <= imparams->getNumSample()){
                real += RFData->getRealRFData(k, sample);
                imag += RFData->getImagRFData(k, sample);
            }
        }
        //Calculates the value of the magnitude and sets it to the scanline array
        scanline[i] = sqrt( pow(real, 2) + pow(imag, 2) );
    }
}

void BmodeClass::getScanline(float *data)
{
    //Populates the data array with the values from the scanline array
    for(int i = 0; i < imparams->getNumPixel(); ++i){
        data[i] = scanline[i];
    }
}

void BmodeClass::deleteScanline()
{
    //Deletes the array
    delete [] scanline;
}