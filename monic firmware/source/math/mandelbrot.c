/*Copyright 2020 Daniel Milutinovic

Redistribution and use in source and binary forms, with or without modification, are permitted provided
that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the
following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
following disclaimer in the documentation and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
products derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

//Program to plot the Mandelbrot set

//definitions

#define ImageWidth   480
#define ImageHeight  320

//includes

#include <stdint.h>
#include <stdbool.h>

#include "../user.h"

#include <math.h>

//variables

extern double uStackD[stackDDepth];
extern unsigned int uStackDIndex;

extern unsigned int flag1;

extern double valueCmdL_SigD;
extern double valueCmdL_ExpD;
extern double valueCmdL_D;
extern double decDigits;

extern uint32_t fontColour;

//functions

void fillScreen(uint16_t);
void drawPixel(int16_t, int16_t, uint16_t);
uint16_t colour565(uint8_t r, uint8_t g, uint8_t b);
void enterComplex(void);

///////////////////////////////////////////////////////////////////////////////

void mandelbrot(unsigned int MaxIterations, uint16_t colour) {
    double MinRe = -2.3;
    double MaxRe = 0.5;
    double MinIm = -0.933;
    double MaxIm = 0.933;

    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

    double c_im;
    double c_re;
    double Z_re;
    double Z_im;
    double Z_re2;
    double Z_im2;

    //unsigned int MaxIterations;
    unsigned int y;
    unsigned int x;
    unsigned int n;

    _Bool isInside;

    //MaxIterations = 60;

    //clear the display
    fillScreen(BLACK);

    for(y = 0; y < ImageHeight; y++)
    {
        c_im = MaxIm - y * Im_factor;
        for(x = 0; x < ImageWidth; x++)
        {
            c_re = MinRe + x * Re_factor;

            Z_re = c_re, Z_im = c_im;
            isInside = true;
            for(n = 0; n < MaxIterations; n++)
            {
                Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4) {
                    isInside = false;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            if(isInside) drawPixel(x,y,colour);
        }
    }
}

void mandelbrot2(unsigned int MaxIterations) {
    double MinRe = -2.3;
    double MaxRe = 0.5;
    double MinIm = -0.933;
    double MaxIm = 0.933;

    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

    double c_im;
    double c_re;
    double Z_re;
    double Z_im;
    double Z_re2;
    double Z_im2;

    //unsigned int MaxIterations = iter;
    unsigned int y;
    unsigned int x;
    unsigned int n;

    uint16_t colour;

    //_Bool isInside;

    //MaxIterations = 60;

    //clear the display
    //fillScreen(BLACK);

    for(y = 0; y < ImageHeight; y++)
    {
        c_im = MaxIm - y * Im_factor;
        for(x = 0; x < ImageWidth; x++)
        {
            c_re = MinRe + x * Re_factor;

            Z_re = c_re, Z_im = c_im;
            //isInside = true;
            for(n = 0; n < MaxIterations; n++)
            {
                Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4) {
                    //isInside = false;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            //if(isInside) drawPixel(x,y,colour);
            switch(n) {
            case 0: colour = BLUE;
            break;
            case 1: colour = RED;
            break;
            case 2: colour = YELLOW;
            break;
            case 3: colour = CYAN;
            break;
            case 4: colour = GREEN;
            break;
            case 5: colour = MAGENTA;
            break;
            //case MaxIterations: colour = BLACK;
            default:
                if (n == MaxIterations) colour = BLACK;
                else colour = WHITE;
            }
            drawPixel(x,y,colour);
        }
    }
}

void mandelbrot3(unsigned int MaxIterations) {
    double MinRe = -2.3;
    double MaxRe = 0.5;
    double MinIm = -0.933;
    double MaxIm = 0.933;

    double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
    double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

    double c_im;
    double c_re;
    double Z_re;
    double Z_im;
    double Z_re2;
    double Z_im2;

//	float MinRe = -2.3;
//	float MaxRe = 0.5;
//	float MinIm = -0.933;
//	float MaxIm = 0.933;
//
//	float Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
//	float Im_factor = (MaxIm-MinIm)/(ImageHeight-1);
//
//	float c_im;
//	float c_re;
//	float Z_re;
//	float Z_im;
//	float Z_re2;
//	float Z_im2;

    //unsigned int MaxIterations = iter;
    unsigned int y;
    unsigned int x;
    unsigned int n;

    uint16_t colour;

    //_Bool isInside;

    //MaxIterations = 60;

    //clear the display
    //fillScreen(BLACK);

    for(y = 0; y < ImageHeight; y++)
    {
        c_im = MaxIm - y * Im_factor;
        for(x = 0; x < ImageWidth; x++)
        {
            c_re = MinRe + x * Re_factor;

            Z_re = c_re, Z_im = c_im;
            //isInside = true;
            for(n = 0; n < MaxIterations; n++)
            {
                Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4) {
                    //isInside = false;
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }
            //if(isInside) drawPixel(x,y,colour);
//            switch(n) {
//            case 0: colour = BLUE;
//            break;
//            case 1: colour = GREEN;
//            break;
//            case 2: colour = YELLOW;
//            break;
//            case 3: colour = CYAN;
//            break;
//            case 4: colour = WHITE;
//            break;
//            case 5: colour = MAGENTA;
//            break;
//            //case MaxIterations: colour = BLACK;
//            default:
//                if (n == MaxIterations) colour = BLACK;
////                else colour = colour565(0, MaxIterations - n, MaxIterations - n);//green
////                else colour = colour565(0, MaxIterations - n, 0);//100 iterations olive with wisps, 300 iterations bright green outline
//                else colour = colour565(MaxIterations - n, 0, 0);// 100 iterations burgundy, 261 iterations red with wisps
//            }
//            if (n == MaxIterations) colour = BLACK;
            //colour = colour565(n, 0, 0);// 248 iterations red/yellow
            if (n == MaxIterations) colour = BLACK;
            else colour = colour565(n, 0, 0);//
            drawPixel(x,y,colour);
        }
    }
}

void mandelbrot4(unsigned int MaxIterations) {

	float MinRe = -2.3;
	float MaxRe = 0.5;
	float MinIm = -0.933;
	float MaxIm = 0.933;

	float Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
	float Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

	float c_im;
	float c_re;
	float Z_re;
	float Z_im;
	float Z_re2;
	float Z_im2;

    unsigned int y;
    unsigned int x;
    unsigned int n;

    uint16_t colour;

    for(y = 0; y < ImageHeight; y++)
    {
        c_im = MaxIm - y * Im_factor;
        for(x = 0; x < ImageWidth; x++)
        {
            c_re = MinRe + x * Re_factor;

            Z_re = c_re, Z_im = c_im;
            for(n = 0; n < MaxIterations; n++)
            {
                Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
                if(Z_re2 + Z_im2 > 4) {
                    break;
                }
                Z_im = 2*Z_re*Z_im + c_im;
                Z_re = Z_re2 - Z_im2 + c_re;
            }

            if (n == MaxIterations) colour = BLACK;
            else colour = colour565(n, 0, 0);
            drawPixel(x,y,colour);
        }
    }
}

void mandelbrot5(unsigned int MaxIterations) {

//	float MinRe = -2.3;
//	float MaxRe = 0.5;
//	float MinIm = -0.933;
//	float MaxIm = 0.933;

	enterComplex();

	float MinRe = (float) uStackD[uStackDIndex-1];
	float MaxRe = (float) uStackD[uStackDIndex];
	float MaxIm = 160.0/480.0 * (MaxRe-MinRe);
	float MinIm = -MaxIm;

	float Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
	float Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

	float c_im;
	float c_re;
	float Z_re;
	float Z_im;
	float Z_re2;
	float Z_im2;

	unsigned int y;
	unsigned int x;
	unsigned int n;

	uint16_t colour;

	for(y = 0; y < ImageHeight; y++)
	{
		c_im = MaxIm - y * Im_factor;
		for(x = 0; x < ImageWidth; x++)
		{
			c_re = MinRe + x * Re_factor;

			Z_re = c_re, Z_im = c_im;
			for(n = 0; n < MaxIterations; n++)
			{
				Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4) {
					break;
				}
				Z_im = 2*Z_re*Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}

			if (n == MaxIterations) colour = BLACK;
			else colour = colour565(n, 0, 0);
			drawPixel(x,y,colour);
		}
	}
}

void mandelbrot6(unsigned int MaxIterations) {

	enterComplex();

	double MinRe = uStackD[uStackDIndex-1];
	double MaxRe = uStackD[uStackDIndex];
	double MaxIm = 160.0/480.0 * (MaxRe-MinRe);
	double MinIm = -MaxIm;

	double Re_factor = (MaxRe-MinRe)/(ImageWidth-1);
	double Im_factor = (MaxIm-MinIm)/(ImageHeight-1);

	double c_im;
	double c_re;
	double Z_re;
	double Z_im;
	double Z_re2;
	double Z_im2;

	unsigned int y;
	unsigned int x;
	unsigned int n;

	uint16_t colour;

	for(y = 0; y < ImageHeight; y++)
	{
		c_im = MaxIm - y * Im_factor;
		for(x = 0; x < ImageWidth; x++)
		{
			c_re = MinRe + x * Re_factor;

			Z_re = c_re, Z_im = c_im;
			for(n = 0; n < MaxIterations; n++)
			{
				Z_re2 = Z_re*Z_re, Z_im2 = Z_im*Z_im;
				if(Z_re2 + Z_im2 > 4) {
					break;
				}
				Z_im = 2*Z_re*Z_im + c_im;
				Z_re = Z_re2 - Z_im2 + c_re;
			}

			if (n == MaxIterations) colour = BLACK;
			else colour = colour565(n, 0, 0);
			drawPixel(x,y,colour);
		}
	}
}

