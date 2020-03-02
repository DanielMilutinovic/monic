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

//includes

#include <stdint.h>
#include "../user.h"
#include <math.h>

#include "board.h"
#include "pin_mux.h"

//variables

extern uint32_t fontColour;

extern unsigned int cStackIndex;                                               //complex user stack index
extern double cStackD[stackDDepth];                                            //array to store real part on complex stack
extern double cStackDIMAG[stackDDepth];                                        //array to store imaginary part on complex stack

extern unsigned int uStackDIndex;                                              //complex user stack index
extern double uStackD[stackDDepth];                                            //array to store real part
extern double uStackDIMAG[stackDDepth];                                        //array to store imaginary part
extern unsigned int indexLink[stackDDepth];
extern unsigned int uStackIndex;                                               ////user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix

extern unsigned int prgIndex;
unsigned int prgIndexOld;
extern unsigned int *prg;
unsigned int *prgOld;

extern unsigned int flag1;
extern unsigned int flag2;

extern double valueCmdL_SigD;
extern double valueCmdL_ExpD;
extern double valueCmdL_D;
extern double decDigits;

extern unsigned int prg1[numberOfPrgSteps];

extern unsigned int *labelAddress;
extern unsigned int labelAddress1[labelAddressLength];                                          //array to store program counter values corresponding to labels

extern double *prgConstants;
extern double prgConstants1[prgConstantsLength];                               //array to store values pushed onto the stack during program
                                                                               //execution
extern float *prgConstantsF;
extern float prgConstantsF1[prgConstantsLength];

extern unsigned char prgMode;
extern unsigned char prgMode1;

extern double varListDouble[varListLength];
extern double cmdLNumber[cmdLNumberLength];
extern unsigned int cmdL_Parsed[cmdL_ParsedLength];

//functions

void runPrg(unsigned int);
void scanKp(void);                                                             //scan the 8 row by 6 column keypad
void drawPixel(int16_t, int16_t, uint16_t);
void drawLine(int16_t, int16_t, int16_t, int16_t, uint16_t);
void fillScreen(uint16_t);
void enterAlgebraic(void);
void delayms(unsigned int);

///////////////////////////////////////////////////////////////////////////////

void runPrgCplx(unsigned int x) {
    double temp;
    //unsigned char i;

    switch (x) {
    case equalKSPrg:                                                           //PUSH COMMAND LINE

//        if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//        valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//        if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//        cStackIndex += 1;
//        cStackD[cStackIndex] = valueCmdL_D;
//        cStackDIMAG[cStackIndex] = 0.0;

    	prgIndexOld = prgIndex;
    	prgOld = prg;

        enterAlgebraic();
        prgIndex = 0;
        prg = cmdL_Parsed;
        while (prg[prgIndex] != END) runPrgCplx(prg[prgIndex]);
        cStackDIMAG[cStackIndex] = 0.0;

        prgIndex = prgIndexOld;
        prg = prgOld;
        break;
    case negateKSPrg:                                                          //NEGATE
        cStackD[cStackIndex] = -cStackD[cStackIndex];
        cStackDIMAG[cStackIndex] = -cStackDIMAG[cStackIndex];
        break;
    case deleteKSPrg:                                                          //DROP 1 complex stack level
        cStackIndex -= 1;
        break;
    case addKSPrg:                                                             //add complex numbers/matrices
//        if (sigLength) {                                                     //push command line if it is not empty
//            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//            cStackIndex += 1;
//            cStackD[cStackIndex] = valueCmdL_D;
//            cStackDIMAG[cStackIndex] = 0.0;
//
//            sigLength = 0;
//        }

        cStackD[cStackIndex - 1] = cStackD[cStackIndex - 1] + cStackD[cStackIndex];               //add real parts
        //cStackDIMAG[cStackIndex - 1] = cStackDIMAG[cStackIndex - 1] + cStackDIMAG[cStackIndex];   //add imaginary parts
        cStackIndex -= 1;
        break;
    case subtractKSPrg:
//        if (sigLength) {                                                   //if command line not empty
//            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//            cStackIndex += 1;
//            cStackD[cStackIndex] = valueCmdL_D;
//            cStackDIMAG[cStackIndex] = 0.0;
//
//            sigLength = 0;
//        }

        cStackD[cStackIndex - 1] = cStackD[cStackIndex - 1] - cStackD[cStackIndex];               //subtract real parts
        //cStackDIMAG[cStackIndex - 1] = cStackDIMAG[cStackIndex - 1] - cStackDIMAG[cStackIndex];   //subtract imaginary parts
        cStackIndex -= 1;

        break;
    case multiplyKSPrg:
//        if (sigLength) {                                                   //if command line not empty
//            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//            cStackIndex += 1;
//            cStackD[cStackIndex] = valueCmdL_D;
//            cStackDIMAG[cStackIndex] = 0.0;
//
//            sigLength = 0;
//        }
//
//        temp = cStackD[cStackIndex-1] * cStackD[cStackIndex] - cStackDIMAG[cStackIndex-1] * cStackDIMAG[cStackIndex];
//        cStackDIMAG[cStackIndex-1] = cStackD[cStackIndex-1] * cStackDIMAG[cStackIndex] +
//                cStackDIMAG[cStackIndex-1] * cStackD[cStackIndex];
//        cStackD[cStackIndex-1] = temp;
        cStackD[cStackIndex - 1] = cStackD[cStackIndex - 1] * cStackD[cStackIndex];

        cStackIndex -= 1;

        break;
    case divideKSPrg:
//        if (sigLength) {                                                   //if command line not empty
//            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//            cStackIndex += 1;
//            cStackD[cStackIndex] = valueCmdL_D;
//            cStackDIMAG[cStackIndex] = 0.0;
//
//            sigLength = 0;
//        }
//
//        temp = (cStackD[cStackIndex-1] * cStackD[cStackIndex] + cStackDIMAG[cStackIndex-1] * cStackDIMAG[cStackIndex])/
//                (cStackD[cStackIndex] * cStackD[cStackIndex] + cStackDIMAG[cStackIndex] * cStackDIMAG[cStackIndex]);
//
//        cStackDIMAG[cStackIndex-1] = (cStackDIMAG[cStackIndex-1] * cStackD[cStackIndex] -
//                cStackD[cStackIndex-1] * cStackDIMAG[cStackIndex])/
//                (cStackD[cStackIndex] * cStackD[cStackIndex] + cStackDIMAG[cStackIndex] * cStackDIMAG[cStackIndex]);
//
//        cStackD[cStackIndex-1] = temp;

        cStackD[cStackIndex - 1] = cStackD[cStackIndex - 1] / cStackD[cStackIndex];

        cStackIndex -= 1;
        break;
    case reciprocalKSPrg:                                                      //1/x
        cStackD[cStackIndex] = 1.0 / cStackD[cStackIndex];
        break;
    case powerKSPrg:                                                           //x^y
        cStackD[cStackIndex-1] = pow(cStackD[cStackIndex-1], cStackD[cStackIndex]);
        cStackIndex -= 1;
        break;
    case squareKSPrg:                                                          //SQUARE
        cStackD[cStackIndex] = cStackD[cStackIndex] * cStackD[cStackIndex];
        break;
    case sqrtKSPrg:                                                            //SQUARE ROOT
    	cStackD[cStackIndex] = sqrt(cStackD[cStackIndex]);
    	break;
    case A_SINKSPrg:                                                           //sine
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = sin(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = sin(cStackD[cStackIndex]/180.0*Pi);
    		else cStackD[cStackIndex] = sin(cStackD[cStackIndex]/200.0*Pi);
    	}
    	break;
    case B_COSKSPrg:                                                           //cosine
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = cos(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = cos(cStackD[cStackIndex]/180.0*Pi);
    		else cStackD[cStackIndex] = cos(cStackD[cStackIndex]/200.0*Pi);
    	}
    	break;
    case C_TANKSPrg:                                                           //tangent
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = tan(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = tan(cStackD[cStackIndex]/180.0*Pi);
    		else cStackD[cStackIndex] = tan(cStackD[cStackIndex]/200.0*Pi);
    	}
    	break;
    case arcSinKSPrg:                                                          //ASIN
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = asin(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = asin(cStackD[cStackIndex])*180.0/Pi;
    		else cStackD[cStackIndex] = asin(cStackD[cStackIndex])*200.0/Pi;
    	}
    	break;
    case arcCosKSPrg:                                                          //ACOS
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = acos(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = acos(cStackD[cStackIndex])*180.0/Pi;
    		else cStackD[cStackIndex] = acos(cStackD[cStackIndex])*200.0/Pi;
    	}
    	break;
    case arcTanKSPrg:                                                          //ATAN
    	if (flag2 & RADIAN)	cStackD[cStackIndex] = atan(cStackD[cStackIndex]);
    	else {
    		if (flag2 & DEGREE)	cStackD[cStackIndex] = atan(cStackD[cStackIndex])*180.0/Pi;
    		else cStackD[cStackIndex] = atan(cStackD[cStackIndex])*200.0/Pi;
    	}
    	break;
    case cubeRootKSPrg:                                                        //cube root
    	cStackD[cStackIndex] = pow(cStackD[cStackIndex], 0.3333333333333333);
    	break;
    case rootKSPrg:                                                            //root
    	cStackD[cStackIndex-1] = pow(cStackD[cStackIndex-1], 1.0/cStackD[cStackIndex]);
    	cStackIndex -= 1;
    	break;
    case E_PIKSPrg:                                                            //Pi
    	cStackIndex += 1;
    	cStackD[cStackIndex] = Pi;
    	break;
    case eulerPowerKSPrg:                                                      //e^x
    	cStackD[cStackIndex] = exp(cStackD[cStackIndex]);
    	break;
    case tenPowerKSPrg:                                                        //10^x
    	cStackD[cStackIndex] = pow(10.0,cStackD[cStackIndex]);
    	break;
    case logTenKSPrg:                                                          //log(x)
    	cStackD[cStackIndex] = log10(cStackD[cStackIndex]);
    	break;
    case lnKSPrg:                                                              //ln(x)
    	cStackD[cStackIndex] = log(cStackD[cStackIndex]);
    	break;
    case swapKSPrg:                                                            //SWAP
        temp = cStackD[cStackIndex-1];
        cStackD[cStackIndex-1] = cStackD[cStackIndex];
        cStackD[cStackIndex] = temp;
        break;
    case 162:                                                              //ROTATE
        temp = cStackD[cStackIndex-2];
        cStackD[cStackIndex-2] = cStackD[cStackIndex-1];
        cStackD[cStackIndex-1] = cStackD[cStackIndex];
        cStackD[cStackIndex] = temp;
        break;
    case 163:                                                              //DROP 2 complex stack levels
        cStackIndex -= 2;
        break;
    case 164:                                                              //UNROTATE
        temp = cStackD[cStackIndex];
        cStackD[cStackIndex] = cStackD[cStackIndex - 1];
        cStackD[cStackIndex - 1] = cStackD[cStackIndex - 2];
        cStackD[cStackIndex - 2] = temp;
        break;
    case 166:                                                              //DUPLICATE
        cStackIndex += 1;
        cStackD[cStackIndex] = cStackD[cStackIndex-1];
        //cStackDIMAG[cStackIndex] = cStackDIMAG[cStackIndex-1];
        break;
    case 172:                                                              //push user stack level 1 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex];
        break;
    case 173:                                                              //push user stack level 2 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex-1];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex-1];
        break;
    case 174:                                                              //push user stack level 3 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex-2];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex-2];
        break;
    case 175:                                                              //push user stack level 4 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex-3];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex-3];
        break;
    case 176:                                                              //push user stack level 5 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex-4];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex-4];
        break;
    case 177:                                                              //push user stack level 6 onto complex stack
        cStackIndex += 1;
        cStackD[cStackIndex] = uStackD[uStackDIndex-5];
        cStackDIMAG[cStackIndex] = uStackDIMAG[uStackDIndex-5];
        break;
    case 178:                                                              //push complex stack level 1 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 179:                                                              //push complex stack level 2 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex-1];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex-1];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 180:                                                              //push complex stack level 3 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex-2];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex-2];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 181:                                                              //push complex stack level 4 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex-3];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex-3];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 182:                                                              //push complex stack level 5 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex-4];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex-4];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 183:                                                              //push complex stack level 6 onto user stack
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cStackD[cStackIndex-5];
        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex-5];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 185:                                                              //BLUE COLOUR
        fontColour = BLUE;
        break;
    case 186:                                                              //RED COLOUR
        fontColour = RED;
        break;
    case 187:                                                              //YELLOW COLOUR
        fontColour = YELLOW;
        break;
    case 188:                                                              //MEDIUM ORCHID COLOUR
        fontColour = MAGENTA;
        break;
    case 189:                                                              //BLACK COLOUR
        fontColour = BLACK;
        break;
    case 190:                                                              //AQUA COLOUR
        fontColour = AQUA;
        break;
    case 191:                                                              //GREEN COLOUR
        fontColour = GREEN;
        break;
    case 192:                                                              //BROWN COLOUR
        fontColour = BROWN;
        break;
    case 193:                                                              //WHITE COLOUR
        fontColour = WHITE;
        break;
    case 194:                                                              //ORANGE COLOUR
        fontColour = ORANGE;
        break;
    case 195:                                                              //PINK COLOUR
        fontColour = PINK;
        break;
    case 196:                                                              //INDIGO COLOUR
        fontColour = INDIGO;
        break;
    case 400:                                                                  //20 ms delay;
    	delayms(20);
    	break;
    case 401:                                                                  //100 ms delay;
    	delayms(100);
    	break;
    case 402:                                                                  //500 ms delay;
    	delayms(500);
    	break;
    case 403:                                                                  //1 sec delay;
    	delayms(1000);
    	break;
    case 404:                                                                  //2 sec delay;
    	delayms(2000);
    	break;
    case 405:                                                                  //delay in ms;
    	delayms((unsigned int) cStackD[cStackIndex]);
    	cStackIndex--;
    	break;
    case 420:                                                                  //set GPIO1_11 (board LED) high
    	GPIO_PinWrite(BOARD_LED_TEST_PERIPHERAL, BOARD_LED_TEST_CHANNEL, 1);
    	break;
    case 421:                                                                  //set GPIO1_11 (board LED) low
    	GPIO_PinWrite(BOARD_LED_TEST_PERIPHERAL, BOARD_LED_TEST_CHANNEL, 0);
    	break;
    case 952:                                                              //HALT program execution
        scanKp();
        break;
    case 3000:                                                             //CLEAR DISPLAY
//        sRect.i16XMin = 0;
//        sRect.i16YMin = yCoordStatLTop;
//        sRect.i16XMax = max_xCoord;
//        sRect.i16YMax = yCoordMenuBottom;
//        GrContextForegroundSet(&sContext, backgroundColour);
//        GrRectFill(&sContext, &sRect);
    	fillScreen(BLACK);
        break;
    case 3001:                                                             //PIXEL ON
        //GrPixelDraw(&sContext, cStackD[cStackIndex - 1], cStackD[cStackIndex]);
        //PixelDrawFast(cStackD[cStackIndex - 1], cStackD[cStackIndex], fontColour);
    	drawPixel((int16_t) cStackD[cStackIndex - 1], (int16_t) cStackD[cStackIndex], fontColour);
        break;
    case 3002:                                                                 //LINE
    	drawLine((int16_t) cStackD[cStackIndex - 3], (int16_t) cStackD[cStackIndex - 2],
    			(int16_t) cStackD[cStackIndex - 1], (int16_t) cStackD[cStackIndex], fontColour);
    	cStackD[cStackIndex - 3] = cStackD[cStackIndex - 1];                   //copy x1,y1 to x0,y0 and drop 2 levels
    	cStackD[cStackIndex - 2] = cStackD[cStackIndex];
    	cStackIndex -= 2;
    	break;
    case 4000:                                                             //TEST
//        if (cStackD[cStackIndex]) {
//            prgIndex = 2;
//            goto startDebug;
//        }
        break;
    case 4001:                                                             //TEST
//        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) {
//            prgIndex = 59;
//            cStackIndex -= 1;
//            goto startDebug;
//        }
//        cStackIndex -= 1;
        break;
    case 4002:                                                             //TEST
//        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) {
//            prgIndex = 24;
//            cStackIndex -= 1;
//            goto startDebug;
//        }
//        cStackIndex -= 1;
        break;
    case 4003:                                                             //TEST
//        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) {
//            prgIndex = 13;
//            cStackIndex -= 1;
//            goto startDebug;
//        }
//        cStackIndex -= 1;
        break;
    case 4004:                                                             //TEST
//        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) {
//            prgIndex = 5;
//            cStackIndex -= 1;
//            goto startDebug;
//        }
//        cStackIndex -= 1;
        break;
    case 4005:                                                             //TEST
//        PixelDrawFast(cStackD[cStackIndex - 1], cStackD[cStackIndex], fontColour);
        break;
    case 6000:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[0];
    	break;
    case 6001:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[1];
    	break;
    case 6002:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[2];
    	break;
    case 6003:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[3];
    	break;
    case 6004:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[4];
    	break;
    case 6005:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[5];
    	break;
    case 6006:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[6];
    	break;
    case 6007:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[7];
    	break;
    case 6008:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[8];
    	break;
    case 6009:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[9];
    	break;
    case 6010:
    	cStackIndex += 1;
    	cStackD[cStackIndex] = cmdLNumber[10];
    	break;
    case 10000:                                                            //increment varListDouble[0] and push onto the user stack etc.
        varListDouble[0] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[0];
        break;
    case 10001:
        varListDouble[1] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[1];
        break;
    case 10002:
        varListDouble[2] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[2];
        break;
    case 10003:
        varListDouble[3] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[3];
        break;
    case 10004:
        varListDouble[4] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[4];
        break;
    case 10005:
        varListDouble[5] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[5];
        break;
    case 10006:
        varListDouble[6] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[6];
        break;
    case 10007:
        varListDouble[7] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[7];
        break;
    case 10008:
        varListDouble[8] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[8];
        break;
    case 10009:
        varListDouble[9] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[9];
        break;
    case 10010:
        varListDouble[10] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[10];
        break;
    case 10011:
        varListDouble[11] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[11];
        break;
    case 10012:
        varListDouble[12] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[12];
        break;
    case 10013:
        varListDouble[13] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[13];
        break;
    case 10014:
        varListDouble[14] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[14];
        break;
    case 10015:
        varListDouble[15] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[15];
        break;
    case 10016:
        varListDouble[16] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[16];
        break;
    case 10017:
        varListDouble[17] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[17];
        break;
    case 10018:
        varListDouble[18] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[18];
        break;
    case 10019:
        varListDouble[19] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[19];
        break;
    case 10020:
        varListDouble[20] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[20];
        break;
    case 10021:
        varListDouble[21] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[21];
        break;
    case 10022:
        varListDouble[22] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[22];
        break;
    case 10023:
        varListDouble[23] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[23];
        break;
    case 10024:
        varListDouble[24] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[24];
        break;
    case 10025:
        varListDouble[25] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[25];
        break;
    case 10026:
        varListDouble[26] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[26];
        break;
    case 10027:
        varListDouble[27] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[27];
        break;
    case 10028:
        varListDouble[28] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[28];
        break;
    case 10029:
        varListDouble[29] += 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[29];
        break;
    case 20000:                                                            //decrement varListDouble[0] and push onto the user stack etc.
    	varListDouble[0] -= 1.0;
    	cStackIndex += 1;
    	cStackD[cStackIndex] = varListDouble[0];
    	break;
    case 20001:
        varListDouble[1] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[1];
        break;
    case 20002:
        varListDouble[2] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[2];
        break;
    case 20003:
        varListDouble[3] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[3];
        break;
    case 20004:
        varListDouble[4] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[4];
        break;
    case 20005:
        varListDouble[5] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[5];
        break;
    case 20006:
        varListDouble[6] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[6];
        break;
    case 20007:
        varListDouble[7] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[7];
        break;
    case 20008:
        varListDouble[8] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[8];
        break;
    case 20009:
        varListDouble[9] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[9];
        break;
    case 20010:
        varListDouble[10] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[10];
        break;
    case 20011:
        varListDouble[11] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[11];
        break;
    case 20012:
        varListDouble[12] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[12];
        break;
    case 20013:
        varListDouble[13] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[13];
        break;
    case 20014:
        varListDouble[14] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[14];
        break;
    case 20015:
        varListDouble[15] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[15];
        break;
    case 20016:
        varListDouble[16] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[16];
        break;
    case 20017:
        varListDouble[17] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[17];
        break;
    case 20018:
        varListDouble[18] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[18];
        break;
    case 20019:
        varListDouble[19] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[19];
        break;
    case 20020:
        varListDouble[20] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[20];
        break;
    case 20021:
        varListDouble[21] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[21];
        break;
    case 20022:
        varListDouble[22] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[22];
        break;
    case 20023:
        varListDouble[23] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[23];
        break;
    case 20024:
        varListDouble[24] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[24];
        break;
    case 20025:
        varListDouble[25] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[25];
        break;
    case 20026:
        varListDouble[26] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[26];
        break;
    case 20027:
        varListDouble[27] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[27];
        break;
    case 20028:
        varListDouble[28] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[28];
        break;
    case 20029:
        varListDouble[29] -= 1.0;
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[29];
        break;
    case 30000:                                                            //GOTO A
        prgIndex = labelAddress[0];                                        //go to label A etc.
        break;
    case 30001:
        prgIndex = labelAddress[1];
        break;
    case 30002:
        prgIndex = labelAddress[2];
        break;
    case 30003:
        prgIndex = labelAddress[3];
        break;
    case 30004:
        prgIndex = labelAddress[4];
        break;
    case 30005:
        prgIndex = labelAddress[5];
        break;
    case 30006:
        prgIndex = labelAddress[6];
        break;
    case 30007:
        prgIndex = labelAddress[7];
        break;
    case 30008:
        prgIndex = labelAddress[8];
        break;
    case 30009:
        prgIndex = labelAddress[9];
        break;
    case 30010:
        prgIndex = labelAddress[10];
        break;
    case 30011:
        prgIndex = labelAddress[11];
        break;
    case 30012:
        prgIndex = labelAddress[12];
        break;
    case 30013:
        prgIndex = labelAddress[13];
        break;
    case 30014:
        prgIndex = labelAddress[14];
        break;
    case 30015:
        prgIndex = labelAddress[15];
        break;
    case 30016:
        prgIndex = labelAddress[16];
        break;
    case 30017:
        prgIndex = labelAddress[17];
        break;
    case 30018:
        prgIndex = labelAddress[18];
        break;
    case 30019:
        prgIndex = labelAddress[19];
        break;
    case 30020:
        prgIndex = labelAddress[20];
        break;
    case 30021:
        prgIndex = labelAddress[21];
        break;
    case 30022:
        prgIndex = labelAddress[22];
        break;
    case 30023:
        prgIndex = labelAddress[23];
        break;
    case 30024:
        prgIndex = labelAddress[24];
        break;
    case 30025:
        prgIndex = labelAddress[25];
        break;
    case 40000:                                                            //GOTOIF=0 A
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[0];         //go to label A address if complex stack value = 0 etc.
    	break;
    case 40001:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[1];
    	break;
    case 40002:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[2];
    	break;
    case 40003:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[3];
    	break;
    case 40004:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[4];
    	break;
    case 40005:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[5];
    	break;
    case 40006:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[6];
    	break;
    case 40007:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[7];
    	break;
    case 40008:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[8];
    	break;
    case 40009:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[9];
    	break;
    case 40010:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[10];
    	break;
    case 40011:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[11];
    	break;
    case 40012:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[12];
    	break;
    case 40013:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[13];
    	break;
    case 40014:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[14];
    	break;
    case 40015:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[15];
    	break;
    case 40016:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[16];
    	break;
    case 40017:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[17];
    	break;
    case 40018:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[18];
    	break;
    case 40019:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[19];
    	break;
    case 40020:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[20];
    	break;
    case 40021:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[21];
    	break;
    case 40022:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[22];
    	break;
    case 40023:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[23];
    	break;
    case 40024:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[24];
    	break;
    case 40025:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[25];
    	break;
    case 40026:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[26];
    	break;
    case 40027:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[27];
    	break;
    case 40028:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[28];
    	break;
    case 40029:
    	if (cStackD[cStackIndex] == 0) prgIndex = labelAddress[29];
    	break;
    case 50000:                                                            //GOTOIF!=0 A
        if (cStackD[cStackIndex]) prgIndex = labelAddress[0];              //go to label A address if complex stack value != 0 etc.
        break;
    case 50001:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[1];
        break;
    case 50002:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[2];
        break;
    case 50003:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[3];
        break;
    case 50004:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[4];
        break;
    case 50005:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[5];
        break;
    case 50006:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[6];
        break;
    case 50007:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[7];
        break;
    case 50008:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[8];
        break;
    case 50009:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[9];
        break;
    case 50010:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[10];
        break;
    case 50011:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[11];
        break;
    case 50012:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[12];
        break;
    case 50013:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[13];
        break;
    case 50014:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[14];
        break;
    case 50015:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[15];
        break;
    case 50016:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[16];
        break;
    case 50017:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[17];
        break;
    case 50018:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[18];
        break;
    case 50019:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[19];
        break;
    case 50020:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[20];
        break;
    case 50021:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[21];
        break;
    case 50022:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[22];
        break;
    case 50023:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[23];
        break;
    case 50024:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[24];
        break;
    case 50025:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[25];
        break;
    case 50026:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[26];
        break;
    case 50027:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[27];
        break;
    case 50028:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[28];
        break;
    case 50029:
        if (cStackD[cStackIndex]) prgIndex = labelAddress[29];
        break;
    case 60000:                                                                //GOTOIF= A and DROP 1 complex stack level
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[0]; //go to label A address if level (i-1) = level i etc.
        cStackIndex -= 1;
        break;
    case 60001:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[1];
        cStackIndex -= 1;
        break;
    case 60002:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[2];
        cStackIndex -= 1;
        break;
    case 60003:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[3];
        cStackIndex -= 1;
        break;
    case 60004:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[4];
        cStackIndex -= 1;
        break;
    case 60005:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[5];
        cStackIndex -= 1;
        break;
    case 60006:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[6];
        cStackIndex -= 1;
        break;
    case 60007:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[7];
        cStackIndex -= 1;
        break;
    case 60008:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[8];
        cStackIndex -= 1;
        break;
    case 60009:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[9];
        cStackIndex -= 1;
        break;
    case 60010:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[10];
        cStackIndex -= 1;
        break;
    case 60011:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[11];
        cStackIndex -= 1;
        break;
    case 60012:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[12];
        cStackIndex -= 1;
        break;
    case 60013:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[13];
        cStackIndex -= 1;
        break;
    case 60014:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[14];
        cStackIndex -= 1;
        break;
    case 60015:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[15];
        cStackIndex -= 1;
        break;
    case 60016:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[16];
        cStackIndex -= 1;
        break;
    case 60017:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[17];
        cStackIndex -= 1;
        break;
    case 60018:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[18];
        cStackIndex -= 1;
        break;
    case 60019:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[19];
        cStackIndex -= 1;
        break;
    case 60020:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[20];
        cStackIndex -= 1;
        break;
    case 60021:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[21];
        cStackIndex -= 1;
        break;
    case 60022:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[22];
        cStackIndex -= 1;
        break;
    case 60023:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[23];
        cStackIndex -= 1;
        break;
    case 60024:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[24];
        cStackIndex -= 1;
        break;
    case 60025:
        if (cStackD[cStackIndex-1] == cStackD[cStackIndex]) prgIndex = labelAddress[25];
        cStackIndex -= 1;
        break;
    case 80000:                                                                //GOTOIF> A and DROP 1 complex stack level
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[0]; //go to label A address if level (i-1) > level i etc.
        cStackIndex -= 1;
        break;
    case 80001:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[1];
        cStackIndex -= 1;
        break;
    case 80002:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[2];
        cStackIndex -= 1;
        break;
    case 80003:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[3];
        cStackIndex -= 1;
        break;
    case 80004:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[4];
        cStackIndex -= 1;
        break;
    case 80005:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[5];
        cStackIndex -= 1;
        break;
    case 80006:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[6];
        cStackIndex -= 1;
        break;
    case 80007:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[7];
        cStackIndex -= 1;
        break;
    case 80008:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[8];
        cStackIndex -= 1;
        break;
    case 80009:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[9];
        cStackIndex -= 1;
        break;
    case 80010:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[10];
        cStackIndex -= 1;
        break;
    case 80011:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[11];
        cStackIndex -= 1;
        break;
    case 80012:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[12];
        cStackIndex -= 1;
        break;
    case 80013:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[13];
        cStackIndex -= 1;
        break;
    case 80014:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[14];
        cStackIndex -= 1;
        break;
    case 80015:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[15];
        cStackIndex -= 1;
        break;
    case 80016:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[16];
        cStackIndex -= 1;
        break;
    case 80017:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[17];
        cStackIndex -= 1;
        break;
    case 80018:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[18];
        cStackIndex -= 1;
        break;
    case 80019:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[19];
        cStackIndex -= 1;
        break;
    case 80020:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[20];
        cStackIndex -= 1;
        break;
    case 80021:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[21];
        cStackIndex -= 1;
        break;
    case 80022:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[22];
        cStackIndex -= 1;
        break;
    case 80023:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[23];
        cStackIndex -= 1;
        break;
    case 80024:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[24];
        cStackIndex -= 1;
        break;
    case 80025:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[25];
        cStackIndex -= 1;
        break;
    case 80026:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[26];
        cStackIndex -= 1;
        break;
    case 80027:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[27];
        cStackIndex -= 1;
        break;
    case 80028:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[28];
        cStackIndex -= 1;
        break;
    case 80029:
        if (cStackD[cStackIndex-1] > cStackD[cStackIndex]) prgIndex = labelAddress[29];
        cStackIndex -= 1;
        break;
    case 90000:                                                                //GOTOIF< A and DROP 1 complex stack level
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[0]; //go to label A address if level (i-1) < level i etc.
        cStackIndex -= 1;
        break;
    case 90001:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[1];
        cStackIndex -= 1;
        break;
    case 90002:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[2];
        cStackIndex -= 1;
        break;
    case 90003:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[3];
        cStackIndex -= 1;
        break;
    case 90004:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[4];
        cStackIndex -= 1;
        break;
    case 90005:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[5];
        cStackIndex -= 1;
        break;
    case 90006:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[6];
        cStackIndex -= 1;
        break;
    case 90007:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[7];
        cStackIndex -= 1;
        break;
    case 90008:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[8];
        cStackIndex -= 1;
        break;
    case 90009:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[9];
        cStackIndex -= 1;
        break;
    case 90010:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[10];
        cStackIndex -= 1;
        break;
    case 90011:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[11];
        cStackIndex -= 1;
        break;
    case 90012:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[12];
        cStackIndex -= 1;
        break;
    case 90013:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[13];
        cStackIndex -= 1;
        break;
    case 90014:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[14];
        cStackIndex -= 1;
        break;
    case 90015:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[15];
        cStackIndex -= 1;
        break;
    case 90016:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[16];
        cStackIndex -= 1;
        break;
    case 90017:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[17];
        cStackIndex -= 1;
        break;
    case 90018:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[18];
        cStackIndex -= 1;
        break;
    case 90019:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[19];
        cStackIndex -= 1;
        break;
    case 90020:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[20];
        cStackIndex -= 1;
        break;
    case 90021:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[21];
        cStackIndex -= 1;
        break;
    case 90022:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[22];
        cStackIndex -= 1;
        break;
    case 90023:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[23];
        cStackIndex -= 1;
        break;
    case 90024:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[24];
        cStackIndex -= 1;
        break;
    case 90025:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[25];
        cStackIndex -= 1;
        break;
    case 90026:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[26];
        cStackIndex -= 1;
        break;
    case 90027:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[27];
        cStackIndex -= 1;
        break;
    case 90028:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[28];
        cStackIndex -= 1;
        break;
    case 90029:
        if (cStackD[cStackIndex-1] < cStackD[cStackIndex]) prgIndex = labelAddress[29];
        cStackIndex -= 1;
        break;
    case 150000:                                                           //push double prgConstants[0] onto the stack etc.
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[0];
        break;
    case 150001:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[1];
        break;
    case 150002:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[2];
        break;
    case 150003:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[3];
        break;
    case 150004:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[4];
        break;
    case 150005:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[5];
        break;
    case 150006:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[6];
        break;
    case 150007:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[7];
        break;
    case 150008:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[8];
        break;
    case 150009:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[9];
        break;
    case 150010:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[10];
        break;
    case 150011:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[11];
        break;
    case 150012:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[12];
        break;
    case 150013:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[13];
        break;
    case 150014:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[14];
        break;
    case 150015:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[15];
        break;
    case 150016:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[16];
        break;
    case 150017:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[17];
        break;
    case 150018:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[18];
        break;
    case 150019:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[19];
        break;
    case 150020:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[20];
        break;
    case 150021:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[21];
        break;
    case 150022:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[22];
        break;
    case 150023:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[23];
        break;
    case 150024:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[24];
        break;
    case 150025:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[25];
        break;
    case 150026:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[26];
        break;
    case 150027:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[27];
        break;
    case 150028:
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[28];
        break;
    case 150029:                                                           //push double prgConstants[29] onto the stack
        cStackIndex += 1;
        cStackD[cStackIndex] = prgConstants[29];
        break;
    case 190000:                                                           //STORE to varListDouble[0] etc.
        varListDouble[0] = cStackD[cStackIndex]; break;
    case 190001:
        varListDouble[1] = cStackD[cStackIndex]; break;
    case 190002:
        varListDouble[2] = cStackD[cStackIndex]; break;
    case 190003:
        varListDouble[3] = cStackD[cStackIndex]; break;
    case 190004:
        varListDouble[4] = cStackD[cStackIndex]; break;
    case 190005:
        varListDouble[5] = cStackD[cStackIndex]; break;
    case 190006:
        varListDouble[6] = cStackD[cStackIndex]; break;
    case 190007:
        varListDouble[7] = cStackD[cStackIndex]; break;
    case 190008:
        varListDouble[8] = cStackD[cStackIndex]; break;
    case 190009:
        varListDouble[9] = cStackD[cStackIndex]; break;
    case 190010:
        varListDouble[10] = cStackD[cStackIndex]; break;
    case 190011:
        varListDouble[11] = cStackD[cStackIndex]; break;
    case 190012:
        varListDouble[12] = cStackD[cStackIndex]; break;
    case 190013:
        varListDouble[13] = cStackD[cStackIndex]; break;
    case 190014:
        varListDouble[14] = cStackD[cStackIndex]; break;
    case 190015:
        varListDouble[15] = cStackD[cStackIndex]; break;
    case 190016:
        varListDouble[16] = cStackD[cStackIndex]; break;
    case 190017:
        varListDouble[17] = cStackD[cStackIndex]; break;
    case 190018:
        varListDouble[18] = cStackD[cStackIndex]; break;
    case 190019:
        varListDouble[19] = cStackD[cStackIndex]; break;
    case 190020:
        varListDouble[20] = cStackD[cStackIndex]; break;
    case 190021:
        varListDouble[21] = cStackD[cStackIndex]; break;
    case 190022:
        varListDouble[22] = cStackD[cStackIndex]; break;
    case 190023:
        varListDouble[23] = cStackD[cStackIndex]; break;
    case 190024:
        varListDouble[24] = cStackD[cStackIndex]; break;
    case 190025:
        varListDouble[25] = cStackD[cStackIndex]; break;
    case 190026:
        varListDouble[26] = cStackD[cStackIndex]; break;
    case 190027:
        varListDouble[27] = cStackD[cStackIndex]; break;
    case 190028:
        varListDouble[28] = cStackD[cStackIndex]; break;
    case 190029:
        varListDouble[29] = cStackD[cStackIndex]; break;
    case 200000:                                                               //PUSH varListDouble[0] etc.
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[0];
        break;
    case 200001:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[1];
        break;
    case 200002:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[2];
        break;
    case 200003:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[3];
        break;
    case 200004:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[4];
        break;
    case 200005:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[5];
        break;
    case 200006:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[6];
        break;
    case 200007:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[7];
        break;
    case 200008:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[8];
        break;
    case 200009:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[9];
        break;
    case 200010:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[10];
        break;
    case 200011:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[11];
        break;
    case 200012:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[12];
        break;
    case 200013:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[13];
        break;
    case 200014:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[14];
        break;
    case 200015:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[15];
        break;
    case 200016:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[16];
        break;
    case 200017:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[17];
        break;
    case 200018:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[18];
        break;
    case 200019:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[19];
        break;
    case 200020:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[20];
        break;
    case 200021:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[21];
        break;
    case 200022:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[22];
        break;
    case 200023:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[23];
        break;
    case 200024:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[24];
        break;
    case 200025:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[25];
        break;
    case 200026:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[26];
        break;
    case 200027:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[27];
        break;
    case 200028:
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[28];
        break;
    case 200029:                                                               //<-
        cStackIndex += 1;
        cStackD[cStackIndex] = varListDouble[29];
        break;
    case 280000:                                                               //execute prg1, etc. ->
        prgOld = prg;
        prgIndexOld = prgIndex;
        prgIndex = 0;
        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
        if (prgMode) runPrgCplx(prg[prgIndex]); else runPrg(prg[prgIndex]);
        prg = prgOld;
        prgIndex = prgIndexOld;
        break;
    }
    prgIndex += 1;
    //startDebug:
}
