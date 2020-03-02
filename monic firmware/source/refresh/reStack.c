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

#include <math.h>

#include "../user.h"
#include "../header/globalVars.h"

//variables

extern unsigned int flag1;
extern unsigned int flag2;

extern unsigned char kpPlane;

extern int16_t xCoordinate;
extern int16_t yCoordinate;
extern int16_t xCoordinateCursor;
extern int16_t yCoordinateCursor;
int16_t xCoordinateStart;

extern unsigned int screenNumber;

extern unsigned int uStackIndex;                                                      //user stack level index
extern unsigned char uStackType[stackDDepth];                                         //0 -> complex, 1 -> matrix

extern double uStackD[stackDDepth];                                                   //array to store real part
extern double uStackDIMAG[stackDDepth];                                               //array to store imaginary part

extern unsigned int indexLink[stackDDepth];

extern unsigned char uStackMDim[stackDDepth][2];                                      //array to store matrix dimensions

extern unsigned int matrixRow;
extern unsigned int matrixColumn;

extern unsigned int cStackIndex;                                                      //complex user stack index
extern double cStackD[stackDDepth];                                                   //array to store real part on complex stack
extern double cStackDIMAG[stackDDepth];                                               //array to store imaginary part on complex stack

extern unsigned int prgIndex;
extern unsigned int *prg;

extern double *prgConstants;
extern float *prgConstantsF;

extern unsigned char prgMode;

extern char custMenuLbl[custMenuLength][8];

extern unsigned int *labelAddress;

extern char (*varList)[varListStringLength];

unsigned char significandString[significandStringLength];
char exponentString[2];
signed int Exponent;

unsigned char lastNZPos;
//int16_t page;

extern unsigned char cmdL_S[cmdL_SLength];

extern uint32_t fontLength;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

extern uint32_t fontColour;

unsigned int opcode[6];

extern uint8_t size;

//functions

void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void printChar3(unsigned int);
void printChar4(unsigned int);
void displayValue(unsigned int);
void displayValueCplx(unsigned int);
void doubleToString(double);
//void doubleToStringF(float);
void roundString(unsigned char);
//void dispValueStringDigit(unsigned char);
void displayLabel(unsigned int);
void displayPrgStep(unsigned int);                                             //display program step on left side of display
void displayGOTOLabel(unsigned int);
void displayInstruction(unsigned int);
void displayOPCODE(unsigned int);
void printASCII(unsigned char);

void printStringRight(char*);
void printString(char*);
void printCharacter(char);

void displayStringRight(void);
void displayStringRightLimited(void);

void displayExponent(signed int);

void displayStringExpGreater12(void);
void displayString0Exp12(void);
void displayStringExpLessNeg12(void);
void displayStringNeg12Exp0(void);

void displayStringExpGreater12Limited(void);
void displayString0Exp12Limited(void);
void displayStringExpLessNeg12Limited(void);
void displayStringNeg12Exp0Limited(void);

void printCharactercmdL(char);
void refreshCeditor(void);

//external functions

extern double predecessor(double);
extern double successor(double);
//
//extern float predecessorF(float x);
//extern float successorF(float x);

//constants

const unsigned char letters[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

///////////////////////////////////////////////////////////////////////////////

void reStack(void) {
    unsigned int i = 0;
    unsigned char j;

    switch (kpPlane) {
    case 6:                                                                    //if in C program edit mode
        if (flag2 & CeditorRefresh) {
            refreshCeditor();
            flag2 &= ~CeditorRefresh;
        }
        else {
            if (flag2 & CeditorArrow) flag2 &= ~CeditorArrow;
            else {
                //printCharactercmdL(Cprg[CprgIndex - 1]);
                //xCoordinateCursor += 6;
            }
        }
        break;
    case 11:                                                                   //if in store mode
    case 0:                                                                    //if in main mode
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
        i = screenNumber * 5;
        yCoordinate = yCoordLvl1Top;
        for (j = 1; j < 6; j++) {
            fontColour = RED;
            xCoordinate = 0;
            displayLabel(i+1);                                                 //display stack label
            xCoordinate = max_xCoord;
            if (uStackIndex > i) displayValue(uStackIndex - i);                //display complex scalar/matrix on user stack
            yCoordinate  -= pageWidth;
            i += 1;
        }
        break;
    case 5:                                                                    //if in Keystroke programming edit mode
        if (!(flag2 & CURSORON)) {
        	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
            i = prgIndex / 7 * 7;
            yCoordinate = yCoordStatLTop;
            for (j = 0; j < 7; j++) {
                if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
                xCoordinate = 0;
                displayPrgStep(i+1);                                           //display program step
#ifdef FIXED_WIDTH_FONT
                xCoordinate = 3*5*size + GOTOLabelOffsetFW;
#else
                xCoordinate = GOTOLabelOffsetVW;
#endif
                displayGOTOLabel(i);                                           //display GOTO destination label
                xCoordinate = max_xCoord;
                displayInstruction(i);
                yCoordinate  += pageWidth;
                i += 1;
            }
        }
        break;
    case 8:                                                                    //if in view mode
    	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
        fontColour = RED;
        if (uStackType[uStackIndex]) {                                         //display row, column numbers if matrix
            xCoordinate = 0;
            xCoordinate += (uint32_t) fontData[fontOffset[40 - 32] + 1];
            xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) matrixRow + 48 - 32] + 1];
            xCoordinate += (uint32_t) fontData[fontOffset[44 - 32] + 1];
            xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) matrixColumn + 48 - 32] + 1];
        }
        break;
//    case 11:                                                                    //if in store mode
//        ClrStack();
//        i = screenNumber * 5;
//        page = yCoordLvl1Top;
//        for (j = 1; j < 6; j++) {
//            GrContextForegroundSet(&sContext, StackColour);
//            xCoordinate = 0;
//            displayLabel(i+1);                                                 //display stack label
//            if (uStackIndex > i) displayValue(uStackIndex - i);                //display complex scalar/matrix
//            page -= pageWidth;
//            i += 1;
//        }
//        break;
    case 12:                                                                    //if in KSPrgDebug mode
        //ClrStack();
        //RectFill(0, max_xCoord, yCoordLvl5Top, yCoordLvl1Bottom, backgroundColour);
    	//drawRect(max_xCoord, yCoordLvl5Top, max_xCoord, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
        i = screenNumber * 5;
        //page = yCoordLvl1Top;
        yCoordinate = yCoordLvl1Top;
        for (j = 1; j < 6; j++) {
            //GrContextForegroundSet(&sContext, StackColour);
            fontColour = RED;
            xCoordinate = 0;
            displayLabel(i+1);                                                 //display stack label
            xCoordinate = max_xCoord;
            if (prgMode) {
                if (cStackIndex > i) displayValueCplx(cStackIndex - i);        //display complex number on complex stack
            }
            else {
                if (uStackIndex > i) displayValue(uStackIndex - i);            //display complex scalar/matrix on user stack
            }
            yCoordinate -= pageWidth;
            i += 1;
        }
        break;
    case 16:                                                                   //if in Keystroke programming edit STO mode
    	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
        i = prgIndex / 7 * 7;
        yCoordinate = yCoordStatLTop;
        for (j = 0; j < 7; j++) {
            if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
            xCoordinate = 0;
            displayLabel(i+1);                                                 //display program step
#ifdef FIXED_WIDTH_FONT
            xCoordinate = 3*5*size + GOTOLabelOffsetFW;
#else
            xCoordinate = GOTOLabelOffsetVW;
#endif
            displayGOTOLabel(i);                                               //display GOTO destination label
            xCoordinate = max_xCoord;
            displayInstruction(i);
            yCoordinate += pageWidth;
            i += 1;
        }
        break;
    case 17:                                                                   //Adafruit "Classic" font mode
    	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
        fontColour = BLUE;
        xCoordinate = 0;
        yCoordinate =  yCoordStatLTop;
        printString("Adafruit Classic font");

        fontColour = RED;
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString(" !\"#$%&'()*+,-./");
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString("0123456789:;<=>?@");
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString("ABCDEFGHIJKLMNOP");
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString("QRSTUVWXYZ[\\]^_`");
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString("abcdefghijklmnop");
        xCoordinate = 0;
        yCoordinate += pageWidth;
        printString("qrstuvwxyz{|}~");
        break;
    default:
    	__asm volatile ("nop");
    }
}

//void displayValue(unsigned int x) {                                            //display on page user stack value at level x
//    GrContextForegroundSet(&sContext, CmdLColour);
//    if (uStackType[x]) {                                                       //display matrix
//        printChar(uStackMDim[x][0], xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) uStackMDim[x][0] + 48 - 32] + 1];
//        print(" x ", xCoordinate, page);
//        xCoordinate += (uint32_t) (2 * fontData[fontOffset[32 - 32] + 1] + fontData[fontOffset[120 - 32] + 1]);
//        printChar(uStackMDim[x][1], xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) uStackMDim[x][1] + 48 - 32] + 1];
//        print(" matrix", xCoordinate, page);
//    }
//    else {                                                                     //display complex scalar
//        if (uStackD[indexLink[x]] == 0.0) {                                    //if real part = 0 ->
//            if (uStackDIMAG[indexLink[x]] == 0.0) {                            //if imaginary part = 0
//                print("0", (uint32_t) (displayWidth - fontData[fontOffset[48 - 32] + 1]), page);  //display "0" and exit
//            }
//            else {                                                             //if imaginary part <> 0
//                print("i", (uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]), page);
//                doubleToString(uStackDIMAG[indexLink[x]]);
//                displayStringRight((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//            }
//        }                                                                      //<-
//        else {                                                                 //if real part <> 0 ->
//            if (uStackDIMAG[indexLink[x]] == 0.0) {                            //if imaginary part = 0, then display real part only
//                doubleToString(uStackD[indexLink[x]]);
//                displayStringRight(displayWidth);
//            }
//            else {                                                             //if imaginary part <> 0
//                print("i", (uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]), page);
//                doubleToString(uStackDIMAG[indexLink[x]]);
//                                                                               //display imaginary part with leading "+" or "-
//                displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                doubleToString(uStackD[indexLink[x]]);
//                displayStringRight(xCoordinateStart);                          //display real part
//            }
//        }
//    }
//}

void displayValue(unsigned int x) {
    fontColour = YELLOW;
    if (uStackType[x]) {                                                       //display matrix
        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) uStackMDim[x][0] + 48 - 32] + 1];
        //print(" x ", xCoordinate, page);
        xCoordinate += (uint32_t) (2 * fontData[fontOffset[32 - 32] + 1] + fontData[fontOffset[120 - 32] + 1]);
        //printChar(uStackMDim[x][1], xCoordinate, page);
        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) uStackMDim[x][1] + 48 - 32] + 1];
        //print(" matrix", xCoordinate, page);
    }
    else {
        if (uStackD[indexLink[x]] == 0.0) {                                    //if real part = 0
            if (uStackDIMAG[indexLink[x]] == 0.0) {                            //if imaginary part = 0, display "0" and exit
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[48 - 32] + 1] - 1;
#endif
            	printCharacter(48);
            }
            else {                                                             //if imaginary part <> 0
#ifdef FIXED_WIDTH_FONT                                                        //print "i"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(105);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[105 - 32] + 1] - 1;
            	printCharacter(105);
            	xCoordinate--;
#endif
            	doubleToString(uStackDIMAG[indexLink[x]]);
            	displayStringRight();

            	if (significandString[0]) {                                    //print "-"
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
            	printCharacter(45);
                }
            }
        }
        else {                                                                 //if real part <> 0
            if (uStackDIMAG[indexLink[x]] == 0.0) {                            //if imaginary part = 0, then display real part only
                doubleToString(uStackD[indexLink[x]]);
            	displayStringRight();

                if (significandString[0]) {                                    //print "-"
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
            	printCharacter(45);
                }
            }
            else {                                                             //if imaginary part <> 0
#ifdef FIXED_WIDTH_FONT                                                        //print "i"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(105);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[105 - 32] + 1] - 1;
            	printCharacter(105);
            	xCoordinate--;
#endif
                doubleToString(uStackDIMAG[indexLink[x]]);
                displayStringRight();                                          //display imaginary part

                //display leading "+" or "-
                if (significandString[0]) {
#ifdef FIXED_WIDTH_FONT                                                        //print "-"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(45);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
            	printCharacter(45);
            	xCoordinate--;
#endif
                }
                else {
#ifdef FIXED_WIDTH_FONT                                                        //print "+"
                	xCoordinate -= 5 * size - 1;
                	printCharacter(43);
                	xCoordinate -= size + 1;
#else
                	xCoordinate -= (uint32_t) fontData[fontOffset[43 - 32] + 1] - 1;
                	printCharacter(43);
                	xCoordinate--;
#endif
                }

                doubleToString(uStackD[indexLink[x]]);
                displayStringRightLimited();                                   //display real part, with "..." if string too long
                if (significandString[0]) {                                    //print "-"
#ifdef FIXED_WIDTH_FONT
                	xCoordinate -= 5 * size - 1;
#else
                	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
                	printCharacter(45);
                }
            }
        }
    }
}

void displayValueCplx(unsigned int x) {                                        //display on page complex number at level x (debug mode)
    fontColour = YELLOW;

    if (cStackD[x] == 0.0) {                                                   //if real part = 0 ->
        if (cStackDIMAG[x] == 0.0) {                                           //if imaginary part = 0, display "0" and exit
#ifdef FIXED_WIDTH_FONT
        	xCoordinate -= 5 * size - 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[48 - 32] + 1] - 1;
#endif
        	printCharacter(48);
        }
        else {                                                                 //if imaginary part <> 0
#ifdef FIXED_WIDTH_FONT                                                        //print "i"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(105);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[105 - 32] + 1] - 1;
            	printCharacter(105);
            	xCoordinate--;
#endif
            doubleToString(cStackDIMAG[x]);
            displayStringRight();

            if (significandString[0]) {
#ifdef FIXED_WIDTH_FONT                                                        //print "-"
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
            	printCharacter(45);
            }
        }
    }                                                                          //<-
    else {                                                                     //if real part <> 0 ->
        if (cStackDIMAG[x] == 0.0) {                                           //if imaginary part = 0, then display real part only
            doubleToString(cStackD[x]);
            displayStringRight();

            if (significandString[0]) {
#ifdef FIXED_WIDTH_FONT                                                        //print "-"
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
            	printCharacter(45);
            }
        }
        else {                                                                 //if imaginary part <> 0
#ifdef FIXED_WIDTH_FONT                                                        //print "i"
        	xCoordinate -= 5 * size - 1;
        	printCharacter(105);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[105 - 32] + 1] - 1;
        	printCharacter(105);
        	xCoordinate--;
#endif

            doubleToString(cStackDIMAG[x]);
            displayStringRight();

            //display leading "+" or "-
            if (significandString[0]) {
#ifdef FIXED_WIDTH_FONT                                                        //print "-"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(45);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
            	printCharacter(45);
            	xCoordinate--;
#endif
            }
            else {
#ifdef FIXED_WIDTH_FONT                                                        //print "+"
            	xCoordinate -= 5 * size - 1;
            	printCharacter(43);
            	xCoordinate -= size + 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[43 - 32] + 1] - 1;
            	printCharacter(43);
            	xCoordinate--;
#endif
            }

            doubleToString(cStackD[x]);
            displayStringRightLimited();                                       //display real part, with "..." if string too long
            if (significandString[0]) {                                        //print "-"
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
            	printCharacter(45);
            }
        }
    }
}

void doubleToString(double x) {                                                //see page 45 of "Handbook of Floating Point Arithmetic" by Muller et al
    unsigned char i = 0;                                                       //double converted to string and stored in valueString
    unsigned char n = 2;
    double k;
    double m = 1.0;
    unsigned char dinteger;

    double xminus;
    double xplus;
    double l;
    double u;
    double W;
    double d;
    double ddigit;

    for (i = 1; i < significandStringLength; i++) {
        significandString[i] = 0;
    }

    if (x < 0.0) significandString[0] = 0x01;
    else significandString[0] = 0x00;

    x = fabs(x);

    xminus = predecessor(x);
    xplus = successor(x);

    l = (xminus + x)/2.0;
    u = (x + xplus)/2.0;

    k = floor(log10(x));

    while (u > pow(10.0,k)) {
        k += 1.0;
    }

    Exponent = (signed int) k;

    W = x / pow(10.0,k - 1);

    d = floor(W);

    W = W - d;

    dinteger = (unsigned char) d;

    significandString[n] = dinteger;

    while (((d * pow(10.0,k - m)) <= l) && (((d + 1.0) * pow(10.0,k - m)) >= u)) {
        m += 1.0;
        n += 1;

        ddigit = floor(10.0 * W);

        W = 10.0 * W - ddigit;

        d = 10.0 * d + ddigit;

        dinteger = (unsigned char) ddigit;

        significandString[n] = dinteger;
    }

    //if (n > test) test = n;                                                              //debugging

    if (((d * pow(10.0,k - m)) > l) && (((d + 1.0) * pow(10.0,k - m)) >= u)) {           // no change to valueString[n]
    }
    else {
        if (((d * pow(10.0,k - m)) <= l) && (((d + 1.0) * pow(10.0,k - m)) < u))
        significandString[n] = dinteger + 1;
        else {                                                                           //return the value closest to x
            if (fabs(d * pow(10.0,k - m) - x) > fabs((d + 1.0) * pow(10.0,k - m) - x))
            significandString[n] = dinteger + 1;
        }
    }

    for (i = significandStringLength - 1; i > 1; i--) {
        if (significandString[i] == 0x0A) {
            significandString[i] = 0;
            significandString[i-1] += 1;
        }
    }
}

//void doubleToStringF(float x) {                                                //see page 45 of "Handbook of Floating Point Arithmetic" by Muller et al
//    unsigned char i = 0;                                                       //float converted to string and stored in valueString
//    unsigned char n = 2;
//    float k;
//    float m = 1.0;
//    unsigned char dinteger;
//
//    float xminus;
//    float xplus;
//    float l;
//    float u;
//    float W;
//    float d;
//    float ddigit;
//
//    for (i = 1; i < significandStringLength; i++) {
//    	significandString[i] = 0;
//    }
//
//    if (x < 0.0) significandString[0] = 0x01;
//    else significandString[0] = 0x00;
//
//    x = fabsf(x);
//
//    xminus = predecessor(x);                                                   //should be predecessorF(x)
//    xplus = successor(x);                                                      //should be successorF(x)
//
//    l = (xminus + x)/2.0;
//    u = (x + xplus)/2.0;
//
//    k = floorf(log10f(x));
//
//    while (u > powf(10.0,k)) {
//        k += 1.0;
//    }
//
//    Exponent = (signed int) k;
//
//    W = x / powf(10.0,k - 1);
//
//    d = floorf(W);
//
//    W = W - d;
//
//    dinteger = (unsigned char) d;
//
//    significandString[n] = dinteger;
//
//    while (((d * powf(10.0,k - m)) <= l) && (((d + 1.0) * powf(10.0,k - m)) >= u)) {
//        m += 1.0;
//        n += 1;
//
//        ddigit = floorf(10.0 * W);
//
//        W = 10.0 * W - ddigit;
//
//        d = 10.0 * d + ddigit;
//
//        dinteger = (unsigned char) ddigit;
//
//        significandString[n] = dinteger;
//    }
//
//    if (((d * powf(10.0,k - m)) > l) && (((d + 1.0) * powf(10.0,k - m)) >= u)) {         // no change to valueString[n]
//    }
//    else {
//        if (((d * powf(10.0,k - m)) <= l) && (((d + 1.0) * powf(10.0,k - m)) < u))
//        	significandString[n] = dinteger + 1;
//        else {                                                                           //return the value closest to x
//            if (fabsf(d * powf(10.0,k - m) - x) > fabsf((d + 1.0) * powf(10.0,k - m) - x))
//            	significandString[n] = dinteger + 1;
//        }
//    }
//
//    for (i = significandStringLength - 1; i > 1; i--) {
//        if (significandString[i] == 0x0A) {
//        	significandString[i] = 0;
//        	significandString[i-1] += 1;
//        }
//    }
//}

void displayStringRight(void) {                                                //right justified, display sign only if negative
    roundString(12);

    if (Exponent > 0) {                                                        //if exponent > 0
        if (Exponent > 12) displayStringExpGreater12();                        //if exponent > 12
        else displayString0Exp12();                                            //if 0 < exponent <= 12
    }
    else {                                                                     //if exponent <= 0
        if (Exponent < -12) displayStringExpLessNeg12();                       //if exponent < -12
        else displayStringNeg12Exp0();                                         //if -12 =< exponent <= 0
    }
}

void displayStringExpGreater12(void) {                                         //if exponent > 12
    unsigned char i;

    roundString(10);

    displayExponent((unsigned int) (Exponent - 1));

#ifdef FIXED_WIDTH_FONT
    xCoordinate -= 5 * size - 1;
#else
    xCoordinate -= fontData[fontOffset[32 - 32] + 1];                          //backspace
#endif

    for (i = lastNZPos; i >= 3; i--) {                                         //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT
        xCoordinate -= 5 * size - 1;
        printCharacter(significandString[i] + 48);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        printCharacter(significandString[i] + 48);
        xCoordinate--;
#endif
    }

    if (lastNZPos > 2) {
#ifdef FIXED_WIDTH_FONT                                                        //print "."
    	xCoordinate -= 5 * size - 1;
    	printCharacter(46);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
    	printCharacter(46);
    	xCoordinate--;
#endif
    }

#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
        xCoordinate -= 5 * size - 1;
        printCharacter(significandString[2] + 48);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[significandString[2] + 48 - 32] + 1] - 1;
        printCharacter(significandString[2] + 48);
        xCoordinate--;
#endif
}

void displayString0Exp12(void) {                                               //if 0 < exponent <= 12
    unsigned char i;

    if (lastNZPos <= (unsigned char) (Exponent + 1)) {                         //if value is an integer
        for (i = (unsigned char) (Exponent + 1); i >= 2; i--) {                //display value
#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }
    }
    else {                                                                     //if value is not an integer
        for (i = lastNZPos; i >= (unsigned char) (Exponent + 2); i--) {        //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }

#ifdef FIXED_WIDTH_FONT                                                        //display decimal point
        xCoordinate -= 5 * size - 1;
        printCharacter(46);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
        printCharacter(46);
        xCoordinate--;
#endif

        for (i = (unsigned char) (Exponent + 1); i >= 2; i--) {
#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
        xCoordinate -= 5 * size - 1;
        printCharacter(significandString[i] + 48);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        printCharacter(significandString[i] + 48);
        xCoordinate--;
#endif
        }
    }
}

void displayStringExpLessNeg12(void) {                                         //if exponent < -12
    unsigned char i;

    roundString(10);

    displayExponent((unsigned int) (1 - Exponent));

#ifdef FIXED_WIDTH_FONT                                                        //print "-"
        xCoordinate -= 5 * size - 1;
        printCharacter(45);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
        printCharacter(45);
        xCoordinate--;
#endif

        for (i = lastNZPos; i >= 3; i--) {                                         //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }

    if (lastNZPos > 2) {
#ifdef FIXED_WIDTH_FONT                                                        //print "."
    	xCoordinate -= 5 * size - 1;
    	printCharacter(46);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
    	printCharacter(46);
    	xCoordinate--;
#endif
    }

#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
    xCoordinate -= 5 * size - 1;
    printCharacter(significandString[2] + 48);
    xCoordinate -= size + 1;
#else
    xCoordinate -= (uint32_t) fontData[fontOffset[significandString[2] + 48 - 32] + 1] - 1;
    printCharacter(significandString[2] + 48);
    xCoordinate--;
#endif
}

void displayStringNeg12Exp0(void) {                                            //if -12 <= exponent <= 0
    unsigned char i;

    roundString(14 - (unsigned char) (-Exponent));

    for (i = lastNZPos; i>= 2; i--) {                                          //display significant digits
#ifdef FIXED_WIDTH_FONT
    	xCoordinate -= 5 * size - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate--;
#endif
    }

    i = (unsigned char) (-Exponent);
    while (i) {
#ifdef FIXED_WIDTH_FONT                                                        //print leading zeros
        xCoordinate -= 5 * size - 1;
        printCharacter(48);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[48 - 32] + 1] - 1;
        printCharacter(48);
        xCoordinate--;
#endif
        i -= 1;
    }

    printStringRight("0.");
}

void displayStringRightLimited(void) {                                         //right justified, display sign only if negative
                                                                               //and "..." if string too long
    roundString(12);

    if (Exponent > 0) {                                                        //if exponent > 0
        if (Exponent > 12) displayStringExpGreater12Limited();                 //if exponent > 12
        else displayString0Exp12Limited();                                     //if 0 < exponent <= 12
    }
    else {                                                                     //if exponent <= 0
        if (Exponent < -12) displayStringExpLessNeg12Limited();                //if exponent < -12
        else displayStringNeg12Exp0Limited();                                  //if -12 =< exponent <= 0
    }
}

void displayStringExpGreater12Limited(void) {                                  //if exponent > 12
    unsigned char i;

    roundString(10);

    displayExponent((unsigned int) (Exponent - 1));

#ifdef FIXED_WIDTH_FONT
    xCoordinate -= 5 * size - 1;
#else
    xCoordinate -= fontData[fontOffset[32 - 32] + 1];                          //backspace
#endif

    for (i = lastNZPos; i >= 3; i--) {                                         //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT
    	xCoordinate -= 5 * size - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate--;
#endif
    }

    if (lastNZPos > 2) {
#ifdef FIXED_WIDTH_FONT                                                        //print "."
        xCoordinate -= 5 * size - 1;
        printCharacter(46);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
        printCharacter(46);
        xCoordinate--;
#endif
    }

#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
    xCoordinate -= 5 * size - 1;
    printCharacter(significandString[2] + 48);
    xCoordinate -= size + 1;
#else
    xCoordinate -= (uint32_t) fontData[fontOffset[significandString[2] + 48 - 32] + 1] - 1;
    printCharacter(significandString[2] + 48);
    xCoordinate--;
#endif
}

void displayString0Exp12Limited(void) {                                        //if 0 < exponent <= 12
    unsigned char i;

    if (lastNZPos <= (unsigned char) (Exponent + 1)) {                         //if value is an integer
        for (i = (unsigned char) (Exponent + 1); i >= 2; i--) {                //display value
#ifdef FIXED_WIDTH_FONT
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }
    }
    else {                                                                     //if value is not an integer
        for (i = lastNZPos; i >= (unsigned char) (Exponent + 2); i--) {        //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }
#ifdef FIXED_WIDTH_FONT                                                        //print "."
        xCoordinate -= 5 * size - 1;
        printCharacter(46);
        xCoordinate -= size + 1;
#else
        xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
        printCharacter(46);
        xCoordinate--;
#endif

        for (i = (unsigned char) (Exponent + 1); i >= 2; i--) {                //display value to left of decimal point
#ifdef FIXED_WIDTH_FONT
        	xCoordinate -= 5 * size - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate -= size + 1;
#else
        	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
        	printCharacter(significandString[i] + 48);
        	xCoordinate--;
#endif
        }
    }
}

void displayStringExpLessNeg12Limited(void) {                                  //if exponent < -12
    unsigned char i;

    roundString(10);

    displayExponent((unsigned int) (1 - Exponent));

#ifdef FIXED_WIDTH_FONT                                                        //print "-"
    xCoordinate -= 5 * size - 1;
    printCharacter(45);
    xCoordinate -= size + 1;
#else
    xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
    printCharacter(45);
    xCoordinate--;
#endif

    for (i = lastNZPos; i >= 3; i--) {                                         //display value to right of decimal point
#ifdef FIXED_WIDTH_FONT
    	xCoordinate -= 5 * size - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate--;
#endif
    }

    if (lastNZPos > 2) {
#ifdef FIXED_WIDTH_FONT                                                        //print "."
    	xCoordinate -= 5 * size - 1;
    	printCharacter(46);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[46 - 32] + 1] - 1;
    	printCharacter(46);
    	xCoordinate--;
#endif
    }

#ifdef FIXED_WIDTH_FONT                                                        //display value to left of decimal point
    xCoordinate -= 5 * size - 1;
    printCharacter(significandString[2] + 48);
    xCoordinate -= size + 1;
#else
    xCoordinate -= (uint32_t) fontData[fontOffset[significandString[2] + 48 - 32] + 1] - 1;
    printCharacter(significandString[i] + 48);
    xCoordinate--;
#endif
}

void displayStringNeg12Exp0Limited(void) {                                     //if -12 <= exponent <= 0
    unsigned char i;

    roundString(14 - (unsigned char) (-Exponent));

    for (i = lastNZPos; i>= 2; i--) {                                          //display significant digits
#ifdef FIXED_WIDTH_FONT
    	xCoordinate -= 5 * size - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[significandString[i] + 48 - 32] + 1] - 1;
    	printCharacter(significandString[i] + 48);
    	xCoordinate--;
#endif
    }

    i = (unsigned char) (-Exponent);
    while (i) {
#ifdef FIXED_WIDTH_FONT                                                        //print leading zeros
    	xCoordinate -= 5 * size - 1;
    	printCharacter(48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[48 - 32] + 1] - 1;
    	printCharacter(48);
    	xCoordinate--;
#endif
        i -= 1;
    }
    printStringRight("0.");
}

void displayExponent(signed int x) {
    signed char i;

    //if (x < 0) x = -x;
    exponentString[0] = x / 10;
    exponentString[1] = x % 10;

    for (i = 1; i >= 0; i--) {
#ifdef FIXED_WIDTH_FONT
    	xCoordinate -= 5 * size - 1;
    	printCharacter(exponentString[i] + 48);
    	xCoordinate -= size + 1;
#else
    	xCoordinate -= (uint32_t) fontData[fontOffset[exponentString[i] + 48 - 32] + 1] - 1;
    	printCharacter(exponentString[i] + 48);
    	xCoordinate--;
#endif
    }
}

void roundString(unsigned char n) {
    unsigned char i;
    if (significandString[n+2] > 0x04) {                                       //round to n digits ->
        significandString[n+1] +=1;
        i = n+1;
        while (significandString[i] == 0x0A) {
            significandString[i] = 0;
            i -= 1;
            significandString[i] += 1;
        }
    }

    for (i = n+2; i < significandStringLength ; i++) {
        significandString[i] = 0;
    }                                                                          //<-

    if (significandString[1]) {                                                //shift one place to right if overflow
        for (i = significandStringLength - 1; i > 1; i--) significandString[i] = significandString[i-1];
        significandString[1] = 0;
        Exponent += 1;
    }

    lastNZPos = n+1;
    while (significandString[lastNZPos] == 0x00) lastNZPos -= 1;               //determine position of last non-zero digit
}

//void dispValueStringDigit(unsigned char i) {
//    //switch (valueString[i]) {
//    switch (significandString[i]) {
//    case 0:
//        print("0", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[48 - 32] + 1];
//        break;
//    case 1:
//        print("1", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[49 - 32] + 1];
//        break;
//    case 2:
//        print("2", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[50 - 32] + 1];
//        break;
//    case 3:
//        print("3", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[51 - 32] + 1];
//        break;
//    case 4:
//        print("4", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[52 - 32] + 1];
//        break;
//    case 5:
//        print("5", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[53 - 32] + 1];
//        break;
//    case 6:
//        print("6", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[54 - 32] + 1];
//        break;
//    case 7:
//        print("7", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[55 - 32] + 1];
//        break;
//    case 8:
//        print("8", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[56 - 32] + 1];
//        break;
//    case 9:
//        print("9", xCoordinate, page);
//        xCoordinate += (uint32_t) fontData[fontOffset[57 - 32] + 1];
//        break;
//    }
//}

void displayLabel(unsigned int x) {                                            //display up to 3 digits
    unsigned int hundreds;
    unsigned int tens;
    unsigned int ones;
    hundreds = x / 100;
    if (hundreds) printChar3(hundreds);
    x = x % 100;                                                               //remainder when divided by 100
    tens = x / 10;
    if ((hundreds != 0) || (tens !=0)) printChar3(tens);
    ones = x % 10;
    printChar3(ones);
}

void displayPrgStep(unsigned int x) {                                          //display 3 digits, including leading zeros
    unsigned int hundreds;
    unsigned int tens;
    unsigned int ones;
    hundreds = x / 100;
    printChar3(hundreds);
    x = x % 100;                                                               //remainder when divided by 100
    tens = x / 10;
    printChar3(tens);
    ones = x % 10;
    printChar3(ones);
}

void displayOPCODE(unsigned int x) {                                          //display 6 digits, including leading zeros

    opcode[0] = x / 100000;
    x = x % 100000;

    opcode[1] = x / 10000;
    x = x % 10000;

    opcode[2] = x / 1000;
    x = x % 1000;

    opcode[3] = x / 100;
    x = x % 100;

    opcode[4] = x / 10;
    x = x % 10;

    opcode[5] = x;

    printChar4(opcode[5]);
    printChar4(opcode[4]);
    printChar4(opcode[3]);
    printChar4(opcode[2]);
    printChar4(opcode[1]);
    printChar4(opcode[0]);
}

void printChar3(unsigned int z) {
	switch (z) {
	case 0:
		printString("0");
		break;
	case 1:
		printString("1");
		break;
	case 2:
		printString("2");
		break;
	case 3:
		printString("3");
		break;
	case 4:
		printString("4");
		break;
	case 5:
		printString("5");
		break;
	case 6:
		printString("6");
		break;
	case 7:
		printString("7");
		break;
	case 8:
		printString("8");
		break;
	case 9:
		printString("9");
		break;
	}
}

void printChar4(unsigned int z) {
	switch (z) {
	case 0:
		printStringRight("0");
		break;
	case 1:
		printStringRight("1");
		break;
	case 2:
		printStringRight("2");
		break;
	case 3:
		printStringRight("3");
		break;
	case 4:
		printStringRight("4");
		break;
	case 5:
		printStringRight("5");
		break;
	case 6:
		printStringRight("6");
		break;
	case 7:
		printStringRight("7");
		break;
	case 8:
		printStringRight("8");
		break;
	case 9:
		printStringRight("9");
		break;
	}
}

void displayGOTOLabel(unsigned int x) {
    unsigned char i;
    for (i = 0; i < labelAddressLength; i++) {
        if ((labelAddress[i] + 1) == x) break;
    }
    if (i != labelAddressLength) {
    	printCharacter(letters[i]);
    }
}

void displayInstruction (unsigned int x) {                                     //display Keystroke program OPCODE/instruction

    if (flag2 & OPCODE) {
        displayOPCODE(prg[x]);
    }
    else {
        switch (prg[x]) {
        case equalKSPrg:
        	printStringRight("CMD LINE->");
            break;
        case negateKSPrg:
        	printStringRight("+/-");
        	break;
        case decimalPointKSPrg:
        	printStringRight(".");
            break;
        case deleteKSPrg:
        	printStringRight("DROP");
            break;
        case subtractKSPrg:
        	printStringRight("-");
            break;
        case addKSPrg:
        	printStringRight("+");
            break;
        case swapKSPrg:
        	printStringRight("SWAP");
            break;
        case divideKSPrg:
        	printStringRight("/");
            break;
        case multiplyKSPrg:
        	printStringRight("*");
            break;
        case tenPowerKSPrg:
        	printStringRight("10^x");
            break;
        case eulerPowerKSPrg:
        	printStringRight("e^x");
            break;
        case E_PIKSPrg:
        	printStringRight("PI");
        	break;
        case D_ToDMSKSPrg:
        	printStringRight("->DMS");
            break;
        case C_TANKSPrg:
        	printStringRight("tan(x)");
            break;
        case B_COSKSPrg:
        	printStringRight("cos(x)");
            break;
        case A_SINKSPrg:
        	printStringRight("sin(x)");
            break;
        case reciprocalKSPrg:
        	printStringRight("1/x");
            break;
        case powerKSPrg:
        	printStringRight("x^y");
            break;
        case squareKSPrg:
        	printStringRight("x^2");
            break;
        case 53:
        	printStringRight("CLEAR");
            break;
        case logTenKSPrg:
        	printStringRight("log(x)");
            break;
        case lnKSPrg:
        	printStringRight("ln(x)");
            break;
        case arcTanKSPrg:
        	printStringRight("arctan(x)");
            break;
        case arcCosKSPrg:
        	printStringRight("arccos(x)");
            break;
        case arcSinKSPrg:
        	printStringRight("arcsin(x)");
            break;
        case factorialKSPrg:
        	printStringRight("!");
            break;
        case cubeRootKSPrg:
        	printStringRight("x^(1/3)");
        	break;
        case rootKSPrg:
        	printStringRight("x^(1/y)");
            break;
        case sqrtKSPrg:
        	printStringRight("sqrt(x)");
            break;
        case DMSToKSPrg:
        	printStringRight("DMS->");
            break;
        case END:
        	printStringRight("END");
            break;
        case 129:
        	printStringRight("REAL->CPLX");
            break;
        case 162:
        	printStringRight("ROT");
            break;
        case 163:
        	printStringRight("DROP 2");
            break;
        case 164:
        	printStringRight("UNROT");
            break;
        case 165:
        	printStringRight("DROP 3");
            break;
        case 166:
        	printStringRight("DUP");
            break;
        case 167:
        	printStringRight("ENTER 2");
            break;
        case 168:
        	printStringRight("ENTER 3");
            break;
        case 169:
        	printStringRight("ENTER 4");
            break;
        case 170:
        	printStringRight("OVER");
            break;
        case 171:
        	printStringRight("DEPTH");
            break;
        case 172:
        	printStringRight("USTK1->");
            break;
        case 173:
        	printStringRight("USTK2->");
            break;
        case 174:
        	printStringRight("USTK3->");
            break;
        case 175:
        	printStringRight("USTK4->");
            break;
        case 176:
        	printStringRight("USTK5->");
            break;
        case 177:
        	printStringRight("USTK6->");
            break;
        case 178:
        	printStringRight("CSTK1->");
            break;
        case 179:
        	printStringRight("CSTK2->");
            break;
        case 180:
        	printStringRight("CSTK3->");
            break;
        case 181:
        	printStringRight("CSTK4->");
            break;
        case 182:
        	printStringRight("CSTK5->");
            break;
        case 183:
        	printStringRight("CSTK6->");
            break;
        case 184:
        	printStringRight("NOP");
            break;
        case 185:
        	printStringRight("COLOUR BLUE");
            break;
        case 186:
        	printStringRight("COLOUR RED");
            break;
        case 187:
        	printStringRight("COLOUR YELLOW");
            break;
        case 188:
            printStringRight("COLOUR MED ORCH");
            break;
        case 189:
            printStringRight("COLOUR BLACK");
            break;
        case 190:
            printStringRight("COLOUR AQUA");
            break;
        case 191:
            printStringRight("COLOUR GREEN");
            break;
        case 192:
            printStringRight("COLOUR BROWN");
            break;
        case 193:
            printStringRight("COLOUR WHITE");
            break;
        case 194:
            printStringRight("COLOUR ORANGE");
            break;
        case 195:
            printStringRight("COLOUR PINK");
            break;
        case 196:
            printStringRight("COLOUR INDIGO");
            break;
        case 256:
            printStringRight("DROP f");
            break;
        case 257:
            printStringRight("+ f");
            break;
        case 258:
            printStringRight("- f");
            break;
        case 259:
            printStringRight("* f");
            break;
        case 260:
            printStringRight("/ f");
            break;
        case 261:
            printStringRight("sqrt(x) f");
            break;
        case 262:
            printStringRight("x^2 f");
            break;
        case 263:
            printStringRight("DROP 2 f");
            break;
        case 264:
            printStringRight("+/- f");
            break;
        case 265:
            printStringRight("PIXEL ON f");
            break;
        case 266:
            printStringRight("PIXEL OFF f");
            break;
        case 267:
            printStringRight("CMDLINE-> f");
            break;
        case 268:
            printStringRight("DUP f");
            break;
        case 269:
            printStringRight("ROT f");
            break;
        case 270:
            printStringRight("UNROT f");
            break;
        case 271:
            printStringRight("SWAP f");
            break;
        case 272:
            printStringRight("FLOAT->DOUBLE");
            break;
        case 300:
            printStringRight("CPLX +");
            break;
        case 301:
            printStringRight("CPLX +/-");
            break;
        case 302:
            printStringRight("CPLX -");
            break;
        case 303:
            printStringRight("CPLX *");
            break;
        case 400:
        	printStringRight("DELAY 20ms");
        	break;
        case 401:
        	printStringRight("DELAY 100ms");
        	break;
        case 402:
        	printStringRight("DELAY 500ms");
        	break;
        case 403:
        	printStringRight("DELAY 1 sec");
        	break;
        case 404:
        	printStringRight("DELAY 2 sec");
        	break;
        case 405:
        	printStringRight("DELAY in ms");
        	break;
        case 420:
        	printStringRight("LED PIN HIGH");
        	break;
        case 421:
        	printStringRight("LED PIN LOW");
        	break;
        case 952:
            printStringRight("HALT");
            break;
        case 3000:
            printStringRight("CLR DISP");
            break;
        case 3001:
            printStringRight("PIXEL ON");
            break;
        case 3002:
            printStringRight("LINE");
            break;
        case 4000:                                                             //TEST
//            printStringRight("GOTOIF!0 03");
            break;
        case 4001:                                                             //TEST
//            printStringRight("GOTOIF> 60");
            break;
        case 4002:                                                             //TEST
//            printStringRight("GOTOIF< 25");
            break;
        case 4003:                                                             //TEST
//            printStringRight("GOTOIF< 14");
            break;
        case 4004:                                                             //TEST
//            printStringRight("GOTOIF< 6");
            break;
        case 4005:                                                             //TEST
//            printStringRight("PIXEL ON FAST");
            break;
        default:
            if ((prg[x] >= 150000) && (prg[x] < 160000)) {                     //display constant stored in prgConstants
                if (prgConstants[prg[x] - 150000]) {                           //if constant is != 0
                    doubleToString(prgConstants[prg[x] - 150000]);
                    displayStringRight();
                    if (significandString[0]) {
#ifdef FIXED_WIDTH_FONT                                                        //print "-"
                    	xCoordinate -= 5 * size - 1;
#else
                    	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
#endif
                    	printCharacter(45);
                    }
                }
                else printStringRight("0");

            }
//            if ((prg[x] >= 160000) && (prg[x] < 170000)) {                     //display constant stored in prgConstantsF
//                if (prgConstantsF[prg[x] - 160000]) {                          //if constant is != 0
//                    doubleToStringF(prgConstantsF[prg[x] - 160000]);
//                    printStringRight("f");
//                    displayStringRight();
//                    if (significandString[0]) {
//#ifdef FIXED_WIDTH_FONT                                                        //print "-"
//                    	xCoordinate -= 5 * size - 1;
//#else
//                    	xCoordinate -= (uint32_t) fontData[fontOffset[45 - 32] + 1] - 1;
//#endif
//                    	printCharacter(45);
//                    }
//                }
//                else printStringRight("0 f");
//            }
            if ((prg[x] >= 190000) && (prg[x] < 200000)) {                     //STORE instruction
                printStringRight("<-");
#ifdef FIXED_WIDTH_FONT
                xCoordinate -= size + 1;
#else
                xCoordinate--;
#endif
                printStringRight(varList[prg[x] - 190000]);
            }
//            if ((prg[x] >= 210000) && (prg[x] < 220000)) {                               //STORE f instruction
//                i = 0;
//                while (varList[prg[x] - 210000][i]) i+=1;
//                j = i + 3;
//                gotoY(128 - 6*j);
//                for (j = 0; j < i; j++) {
//                    printc6x8(varList[prg[x] - 210000][j]);                              //print variable
//                }
//                prints6x8("<-f");
//            }
            if ((prg[x] >= 200000) && (prg[x] < 210000)) {                     //PUSH instruction
                printStringRight("->");
#ifdef FIXED_WIDTH_FONT
                xCoordinate -= size + 1;
#else
                xCoordinate--;
#endif
                printStringRight(varList[prg[x] - 200000]);
            }
//            if ((prg[x] >= 220000) && (prg[x] < 230000)) {                               //RECALL f instruction
//                i = 0;
//                while (varList[prg[x] - 220000][i]) i+=1;
//                j = i + 3;
//                gotoY(128 - 6*j);
//                for (j = 0; j < i; j++) {
//                    printc6x8(varList[prg[x] - 220000][j]);                              //print variable
//                }
//                prints6x8("->f");
//            }
            if ((prg[x] >= 10000) && (prg[x] < 20000)) {                       //INCREMENT instruction
                printStringRight("+1");
#ifdef FIXED_WIDTH_FONT
                xCoordinate -= size + 1;
#else
                xCoordinate--;
#endif
                printStringRight(varList[prg[x] - 10000]);
            }
//            if ((prg[x] >= 170000) && (prg[x] < 180000)) {                               //INCREMENT f instruction
//                i = 0;
//                while (varList[prg[x] - 170000][i]) i+=1;
//                j = i + 3;
//                gotoY(128 - 6*j);
//                for (j = 0; j < i; j++) {
//                    printc6x8(varList[prg[x] - 170000][j]);                              //print variable
//                }
//                prints6x8("+1f");
//            }
            if ((prg[x] >= 20000) && (prg[x] < 30000)) {                       //DECREMENT instruction
                printStringRight("-1");
#ifdef FIXED_WIDTH_FONT
                xCoordinate -= size + 1;
#else
                xCoordinate--;
#endif
                printStringRight(varList[prg[x] - 20000]);
            }
//            if ((prg[x] >= 180000) && (prg[x] < 190000)) {                               //DECREMENT f instruction
//                i = 0;
//                while (varList[prg[x] - 180000][i]) i+=1;
//                j = i + 3;
//                gotoY(128 - 6*j);
//                for (j = 0; j < i; j++) {
//                    printc6x8(varList[prg[x] - 180000][j]);                              //print variable
//                }
//                prints6x8("-1f");
//            }
            if ((prg[x] >= 30000) && (prg[x] < 40000)) {                                 //GOTO instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 30000] - 32] + 1] - 1;
#endif
            	printCharacter(letters[prg[x] - 30000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
            	printStringRight("GOTO");
            }
            if ((prg[x] >= 40000) && (prg[x] < 50000)) {                       //GOTOIF=0 instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 40000] - 32] + 1] - 1;
#endif
            	printCharacter(letters[prg[x] - 40000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
            	printStringRight("GOTOIF=0");
            }
            if ((prg[x] >= 50000) && (prg[x] < 60000)) {                       //GOTOIF!=0 instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 50000] - 32] + 1] - 1;
#endif
                printCharacter(letters[prg[x] - 50000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
                printStringRight("GOTOIF!=0");
            }
            if ((prg[x] >= 60000) && (prg[x] < 70000)) {                       //GOTOIF= instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 60000] - 32] + 1] - 1;
#endif
                printCharacter(letters[prg[x] - 60000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
                printStringRight("GOTOIF=");
            }
//            if ((prg[x] >= 250000) && (prg[x] < 260000)) {                               //GOTOIF!=0 f instruction
//                printsPrgInstruction("GOTOIF!=0 LBL    ",17);
//                gotoY(110);
//                printc6x8(letters[prg[x] - 250000]);
//                gotoY(122);
//                prints6x8("f");
//            }
            if ((prg[x] >= 80000) && (prg[x] < 90000)) {                                 //GOTOIF> instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 80000] - 32] + 1] - 1;
#endif
                printCharacter(letters[prg[x] - 80000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
                printStringRight("GOTOIF>");
            }
//            if ((prg[x] >= 230000) && (prg[x] < 240000)) {                               //GOTOIF> f instruction
//                printsPrgInstruction("GOTOIF> LBL    ",15);
//                gotoY(110);
//                printc6x8(letters[prg[x] - 230000]);
//                gotoY(122);
//                prints6x8("f");
//            }
            if ((prg[x] >= 90000) && (prg[x] < 100000)) {                                //GOTOIF< instruction
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[letters[prg[x] - 90000] - 32] + 1] - 1;
#endif
                printCharacter(letters[prg[x] - 90000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
                printStringRight("GOTOIF<");
            }
//            if ((prg[x] >= 240000) && (prg[x] < 250000)) {                               //GOTOIF< f instruction
//                printsPrgInstruction("GOTOIF< LBL    ",15);
//                gotoY(110);
//                printc6x8(letters[prg[x] - 240000]);
//                gotoY(122);
//                prints6x8("f");
//            }
//            if ((prg[x] >= 260000) && (prg[x] < 270000)) {                               //GOTOIF= f instruction
//                printsPrgInstruction("GOTOIF= LBL    ",15);
//                gotoY(110);
//                printc6x8(letters[prg[x] - 260000]);
//                gotoY(122);
//                prints6x8("f");
//            }
//            if ((prg[x] >= 110000) && (prg[x] < 120000)) {                               //GOTOIF<= instruction
//                printsPrgInstruction("GOTOIF<= LBL  ",14);
//                gotoY(122);
//                printc6x8(letters[prg[x] - 110000]);
//            }
//            if ((prg[x] >= 270000) && (prg[x] < 280000)) {                               //GOTOIF<= f instruction
//                printsPrgInstruction("GOTOIF<= LBL    ",16);
//                gotoY(110);
//                printc6x8(letters[prg[x] - 270000]);
//                gotoY(122);
//                prints6x8("f");
//            }
            if ((prg[x] >= 280000) && (prg[x] < 290000)) {                     //CALL PROGRAM instruction
                printStringRight(custMenuLbl[prg[x] - 280000]);
#ifdef FIXED_WIDTH_FONT
            	xCoordinate -= 5 * size - 1;
#else
            	xCoordinate -= (uint32_t) fontData[fontOffset[32 - 32] + 1];
#endif
                printStringRight("CALL PROGRAM");
            }
        }
    }
}

void refreshCeditor(void) {
    unsigned int i;

    xCoordinateCursor = 0;
    yCoordinateCursor = 0;

    //ClrStack2();
    //RectFill(0, max_xCoord, yCoordStatLTop, yCoordCmdLBottom, backgroundColour);
    //drawRect(max_xCoord, yCoordStatLTop, max_xCoord, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
    fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);

    for (i = 0; i < 53; i++) {
        printCharactercmdL(Cprg[i]);
        xCoordinateCursor += 6;
    }

    xCoordinateCursor = 0;
    yCoordinateCursor = 8;

    for (i = 53; i < 106; i++) {
        printCharactercmdL(Cprg[i]);
        xCoordinateCursor += 6;
    }

    xCoordinateCursor = 0;
    yCoordinateCursor = 0;
}
