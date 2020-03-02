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

//variables

extern unsigned char kpPlane;

//extern int16_t page;

extern unsigned char matrixRow;
extern unsigned char matrixColumn;

extern unsigned int indexLink[stackDDepth];
extern double uStackDIMAG[stackDDepth];
extern unsigned int uStackIndex;
extern unsigned char uStackMDim[stackDDepth][2];
extern unsigned char uStackType[stackDDepth];
extern char cmdL_S[cmdL_SLength];

extern unsigned int flag1;
extern unsigned int flag2;
extern unsigned int flag3;

extern int16_t xCoordinate;
extern int16_t yCoordinate;

extern unsigned char menu;
extern char custMenuLbl[custMenuLength][6];

extern char (*varList)[varListStringLength];

extern const uint8_t fontVW_1Data[];
extern const uint32_t fontVW_1Offset[];

extern const uint8_t fontVW_2Data[];
extern const uint32_t fontVW_2Offset[];

extern uint8_t size;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

extern uint32_t fontColour;

//functions

void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void drawFastHLine(int16_t, int16_t, int16_t, uint16_t);
void drawFastVLine(int16_t, int16_t, int16_t, uint16_t);
//void viewValueComplex(void);

void displayStringRightSign(int16_t);
void doubleToString(double);

void print(const char*, int16_t, int16_t);
void printASCII(unsigned char);
void printString(char*);

void displayMenu(void);
void mainMenu(void);

///////////////////////////////////////////////////////////////////////////////

void reMenu(void){
    switch (kpPlane) {
    case 8:                                                                    //view matrix/complex number
    	fillRect(0, yCoordMenuTop, TFTHEIGHT, yCoordMenuBottom - yCoordMenuTop, backgroundColour);
    	yCoordinate = yCoordMenuTop;
        fontColour = YELLOW;
        //viewValueComplex();
        break;
    default:                                                                   //otherwise display the menu
    	fillRect(0, yCoordMenuTop, TFTHEIGHT, yCoordMenuBottom - yCoordMenuTop, backgroundColour);
        yCoordinate = yCoordMenuTextTop;

#ifdef FIXED_WIDTH_FONT
        size = 2;
#else
        fontData = fontVW_2data;
        fontOffset = fontVW_2Offset;
#endif

        displayMenu();

#ifdef FIXED_WIDTH_FONT
        size = 4;
#else
        fontData = fontVW_1data;
        fontOffset = fontVW_1Offset;
#endif
    }
}

//void viewValueComplex(void) {
//    print("i", (uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]), page);
//    if (uStackType[uStackIndex]) {                                             //if viewing matrix
//        switch (matrixRow) {
//        case 1:                                                                //row 1
//            switch (matrixColumn) {
//            case 1:                                                            //(1,1)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 1]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 1]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 2:                                                            //(1,2)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 2]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 2]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 3:                                                            //(1,3)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 3]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 3]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 4:                                                            //(1,4)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 4]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 4]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            }
//            break;
//        case 2:                                                                //row 2
//            switch (matrixColumn) {
//            case 1:                                                            //(2,1)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 1]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 1]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 2:                                                            //(2,2)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 2]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 2]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 3:                                                            //(2,3)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 3]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 3]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 4:                                                            //(2,4)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 4]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 4]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            }
//            break;
//        case 3:                                                                //row 3
//            switch (matrixColumn) {
//            case 1:                                                            //(3,1)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 1]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 1]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 2:                                                            //(3,2)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 2]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 2]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 3:                                                            //(3,3)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 3]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 3]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 4:                                                            //(3,4)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 4]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 4]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            }
//            break;
//        case 4:                                                                //row 4
//            switch (matrixColumn) {
//            case 1:                                                            //(4,1)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 1]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 1]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 2:                                                            //(4,2)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 2]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 2]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 3:                                                            //(4,3)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 3]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 3]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            case 4:                                                            //(4,4)
//                if (uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 4]) {
//                    doubleToString(uStackDIMAG[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 4]);
//                    displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//                }
//                print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//                break;
//            }
//            break;
//        }
//    }
//    else {                                                                     //if viewing complex number
//        if (uStackDIMAG[indexLink[uStackIndex]]) {
//            doubleToString(uStackDIMAG[indexLink[uStackIndex]]);
//            displayStringRightSign((uint32_t) (displayWidth - fontData[fontOffset[105 - 32] + 1]));
//        }
//        print("0", (uint32_t) (displayWidth - (fontData[fontOffset[48 - 32] + 1] + fontData[fontOffset[105 - 32] + 1])), page);
//    }
//}

void displayMenu(void) {

    fontColour = MAGENTA;

    drawFastHLine(0, yCoordMenuTop, max_xCoord, fontColour);
    drawFastVLine(xCoordMenuField1, yCoordMenuTop, yCoordMenuBottom - yCoordMenuTop, fontColour);
    drawFastVLine(xCoordMenuField2, yCoordMenuTop, yCoordMenuBottom - yCoordMenuTop, fontColour);
    drawFastVLine(xCoordMenuField3, yCoordMenuTop, yCoordMenuBottom - yCoordMenuTop, fontColour);
    drawFastVLine(xCoordMenuField4, yCoordMenuTop, yCoordMenuBottom - yCoordMenuTop, fontColour);
    drawFastVLine(xCoordMenuField5, yCoordMenuTop, yCoordMenuBottom - yCoordMenuTop, fontColour);

    switch (kpPlane) {
    case 0:                                                                    //if in main mode
        mainMenu();
        break;
    case 5:                                                                    //if in Keystroke programming mode
        switch (menu) {
        case 0:                                                                //program menu 1
            xCoordinate = xCoordMenuFieldText0;
            printString("VAR->");

            xCoordinate = xCoordMenuFieldText1;
            printString("BRANCH");

            xCoordinate = xCoordMenuFieldText2;
            if (flag2 & OPCODE) printString("INSTR");
            else printString("OPCDE");

            xCoordinate = xCoordMenuFieldText3;
            printString("DELETE");

            xCoordinate = xCoordMenuFieldText5;
            printString("END");
            break;
        case 1:                                                                //program menu 2
//            print("INCREM", xCoordMenuFieldText0, page); print("DECREM", xCoordMenuFieldText1, page);
//            print("DELAY", xCoordMenuFieldText2, page); print(" HALT", xCoordMenuFieldText3, page);
//            print("SCANKY", xCoordMenuFieldText4, page); print("KEYNUM", xCoordMenuFieldText5, page);
            xCoordinate = xCoordMenuFieldText0;
            printString("INCREM");

            xCoordinate = xCoordMenuFieldText1;
            printString("DECREM");

            xCoordinate = xCoordMenuFieldText2;
            printString("DELAY");

            xCoordinate = xCoordMenuFieldText3;
            printString("HALT");

            xCoordinate = xCoordMenuFieldText4;
            printString("SCANKY");

            xCoordinate = xCoordMenuFieldText5;
            printString("KEYNO");
            break;
        case 2:                                                                //program menu 3
            //xCoordinate = xCoordMenuFieldText0;
            //printString(" MENU");

            xCoordinate = xCoordMenuFieldText0;
            printString("SAVE");
            break;
        case 3:                                                                //program menu 4
            break;
        case 4:                                                                //BRANCH menu 1
//            print("LABEL", xCoordMenuFieldText0, page); print(" GOTO", xCoordMenuFieldText1, page);
//            print("GOTO=0", xCoordMenuFieldText2, page); print("GOTO!0", xCoordMenuFieldText3, page);
//            print("GOTO=", xCoordMenuFieldText4, page); print(" GOTO!", xCoordMenuFieldText5, page);

            xCoordinate = xCoordMenuFieldText0;
            printString("LABEL");

            xCoordinate = xCoordMenuFieldText1;
            printString("GOTO");

            xCoordinate = xCoordMenuFieldText2;
            printString("GOTO=0");

            xCoordinate = xCoordMenuFieldText3;
            printString("GOTO!0");

            xCoordinate = xCoordMenuFieldText4;
            printString("GOTO=");

            xCoordinate = xCoordMenuFieldText5;
            printString("GOTO!");
            break;
        case 5:                                                                //BRANCH menu 2
//            print("GOTO>", xCoordMenuFieldText0, page); print("GOTO<", xCoordMenuFieldText1, page);
//            print("GOTO>=", xCoordMenuFieldText2, page); print("GOTO<=", xCoordMenuFieldText3, page);
//            print(" CALL", xCoordMenuFieldText4, page); print("RETURN", xCoordMenuFieldText5, page);
            xCoordinate = xCoordMenuFieldText0;
            printString("GOTO>");

            xCoordinate = xCoordMenuFieldText1;
            printString("GOTO<");

            xCoordinate = xCoordMenuFieldText2;
            printString("GOTO>=");

            xCoordinate = xCoordMenuFieldText3;
            printString("GOTO<=");

            xCoordinate = xCoordMenuFieldText4;
            printString("CALL");

            xCoordinate = xCoordMenuFieldText5;
            printString("RETURN");
            break;
        case 6:                                                                //BRANCH menu 3
//            print("GCMDLE", xCoordMenuFieldText0, page); print("GKEYPR", xCoordMenuFieldText1, page);

            xCoordinate = xCoordMenuFieldText0;
            printString("GCMDEM");                                             //GOTO if command line empty

            xCoordinate = xCoordMenuFieldText1;
            printString("GKEYPR");                                             //GOTO if key pressed
            break;
        case 7:                                                                //COMPLEX menu
//            print("CONJUZ", xCoordMenuFieldText0, page); print(" |Z|", xCoordMenuFieldText1, page);
//            print("POLAR", xCoordMenuFieldText2, page); print("RECTAN", xCoordMenuFieldText3, page);

            xCoordinate = xCoordMenuFieldText0;
            printString("CONJUZ");

            xCoordinate = xCoordMenuFieldText1;
            printString("|Z|");

            xCoordinate = xCoordMenuFieldText2;
            printString("POLAR");

            xCoordinate = xCoordMenuFieldText3;
            printString("RECTAN");
            break;
        case 8:                                                                //GRAPH menu
//            print("CLRDISP", xCoordMenuFieldText0, page); print("PIXON", xCoordMenuFieldText1, page);
//            print("PIXOFF", xCoordMenuFieldText2, page); print(" LINE", xCoordMenuFieldText3, page);
//            print("COLOUR", xCoordMenuFieldText4, page);

            xCoordinate = xCoordMenuFieldText0;
            printString("CLRDSP");

            xCoordinate = xCoordMenuFieldText1;
            printString("PIXON");

            xCoordinate = xCoordMenuFieldText2;
            printString("LINE");

            xCoordinate = xCoordMenuFieldText4;
            printString("COLOUR");
            break;
        case 9:                                                                //STACK menu 1
            xCoordinate = xCoordMenuFieldText0;
            printString("DUPLIC");

            xCoordinate = xCoordMenuFieldText1;
            printString("ROTATE");

            xCoordinate = xCoordMenuFieldText2;
            printString("UNROTA");

            xCoordinate = xCoordMenuFieldText3;
            printString("ENTER2");

            xCoordinate = xCoordMenuFieldText4;
            printString("ENTER3");

            xCoordinate = xCoordMenuFieldText5;
            printString("ENTER4");
            break;
        case 10:                                                               //STACK menu 2
//            print(" OVER", xCoordMenuFieldText0, page); print("DROP2", xCoordMenuFieldText1, page);
//            print("DROP3", xCoordMenuFieldText2, page); print("DEPTH", xCoordMenuFieldText3, page);
//            print("FL>DO", xCoordMenuFieldText4, page);

            xCoordinate = xCoordMenuFieldText0;
            printString("OVER");

            xCoordinate = xCoordMenuFieldText1;
            printString("DROP2");

            xCoordinate = xCoordMenuFieldText2;
            printString("DROP3");

            xCoordinate = xCoordMenuFieldText3;
            printString("DEPTH");
            break;
        case 11:                                                               //STATISTICS menu 1
            break;
        case 12:                                                               //STATISTICS menu 2
            break;
        case 13:                                                               //SOLVE menu 1
            break;
        case 14:                                                               //SOLVE menu 2
            break;
        case 15:                                                               //MATRIX menu 1
            break;
        case 16:                                                               //MATRIX menu 2
            break;
        case 17:                                                               //MATH menu 1
            break;
        case 18:                                                               //MATH menu 2
            break;
        case 19:                                                               //MATH menu 3
            break;
        case 20:                                                               //MATH menu 4
            break;
        case 21:                                                               //GRAPH COLOUR MENU 1
            xCoordinate = xCoordMenuFieldText0;
            printString("BLUE");

            xCoordinate = xCoordMenuFieldText1;
            printString("RED");

            xCoordinate = xCoordMenuFieldText2;
            printString("YELLOW");

            xCoordinate = xCoordMenuFieldText3;
            printString("MEDOR");

            xCoordinate = xCoordMenuFieldText4;
            printString("BLACK");

            xCoordinate = xCoordMenuFieldText5;
            printString("AQUA");
            break;
        case 22:                                                               //STACK menu 3
            xCoordinate = xCoordMenuFieldText0;
            printString("USTK1");

            xCoordinate = xCoordMenuFieldText1;
            printString("USTK2");

            xCoordinate = xCoordMenuFieldText2;
            printString("USTK3");

            xCoordinate = xCoordMenuFieldText3;
            printString("USTK4");

            xCoordinate = xCoordMenuFieldText4;
            printString("USTK5");

            xCoordinate = xCoordMenuFieldText5;
            printString("USTK6");
            break;
        case 23:                                                               //STACK menu 4
            xCoordinate = xCoordMenuFieldText0;
            printString("CSTK1");

            xCoordinate = xCoordMenuFieldText1;
            printString("CSTK2");

            xCoordinate = xCoordMenuFieldText2;
            printString("CSTK3");

            xCoordinate = xCoordMenuFieldText3;
            printString("CSTK4");

            xCoordinate = xCoordMenuFieldText4;
            printString("CSTK5");

            xCoordinate = xCoordMenuFieldText5;
            printString("CSTK6");
            break;
        case 24:                                                               //GRAPH COLOUR MENU 2
            xCoordinate = xCoordMenuFieldText0;
            printString("GREEN");

            xCoordinate = xCoordMenuFieldText1;
            printString("BROWN");

            xCoordinate = xCoordMenuFieldText2;
            printString("WHITE");

            xCoordinate = xCoordMenuFieldText3;
            printString("ORANGE");

            xCoordinate = xCoordMenuFieldText4;
            printString("PINK");

            xCoordinate = xCoordMenuFieldText5;
            printString("INDIGO");
            break;
        case 25:                                                               //SYSTEM MENU 1
        	xCoordinate = xCoordMenuFieldText0;
        	printString("PIN");
        	break;
        case 26:                                                               //SYSTEM MENU 2
        	break;
        case 27:                                                               //PIN MENU 1
        	xCoordinate = xCoordMenuFieldText0;
        	printString("PIN H");
        	xCoordinate = xCoordMenuFieldText1;
        	printString("PIN L");
        	break;
        case 28:                                                               //PIN MENU 2
        	break;
        case 29:                                                               //DELAY MENU
        	xCoordinate = xCoordMenuFieldText0;
        	printString("20ms");

        	xCoordinate = xCoordMenuFieldText1;
        	printString("100ms");

        	xCoordinate = xCoordMenuFieldText2;
        	printString("500ms");

        	xCoordinate = xCoordMenuFieldText3;
        	printString("1 sec");

        	xCoordinate = xCoordMenuFieldText4;
        	printString("2 sec");

        	xCoordinate = xCoordMenuFieldText5;
        	printString("DLY ms");
        	break;
        }
        break;
    case 6:                                                                    //if in C programming mode
        break;
    case 11:                                                                   //if in store mode (same menu as when in main mode)
        mainMenu();
        break;
    case 12:                                                                   //if in KSPrgDEBUG mode
        xCoordinate = xCoordMenuFieldText0;
        printString("STEP");

        xCoordinate = xCoordMenuFieldText2;
        if (flag2 & OPCODE) printString("INSTR");
        else printString("OPCDE");
        break;
    case 13:                                                                   //if in KSPrgMenu mode (same menu as when in main mode)
        mainMenu();
        break;
    case 14:                                                                   //if in Erase mode (same menu as when in main mode)
        mainMenu();
        break;
    case 16:                                                                   //if in KSPrgSTO mode
    case 15:                                                                   //if in KSPrgVar mode
        switch (menu) {
        case 0:                                                                //var menu 1
            xCoordinate = xCoordMenuFieldText0;
            printString(varList[0]);

            xCoordinate = xCoordMenuFieldText1;
            printString(varList[1]);

            xCoordinate = xCoordMenuFieldText2;
            printString(varList[2]);

            xCoordinate = xCoordMenuFieldText3;
            printString(varList[3]);

            xCoordinate = xCoordMenuFieldText4;
            printString(varList[4]);

            xCoordinate = xCoordMenuFieldText5;
            printString(varList[5]);
            break;
        case 1:                                                                //var menu 2
            xCoordinate = xCoordMenuFieldText0;
            printString(varList[6]);

            xCoordinate = xCoordMenuFieldText1;
            printString(varList[7]);

            xCoordinate = xCoordMenuFieldText2;
            printString(varList[8]);

            xCoordinate = xCoordMenuFieldText3;
            printString(varList[9]);

            xCoordinate = xCoordMenuFieldText4;
            printString(varList[10]);

            xCoordinate = xCoordMenuFieldText5;
            printString(varList[11]);
            break;
        case 2:                                                                //var menu 3
            xCoordinate = xCoordMenuFieldText0;
            printString(varList[12]);

            xCoordinate = xCoordMenuFieldText1;
            printString(varList[13]);

            xCoordinate = xCoordMenuFieldText2;
            printString(varList[14]);

            xCoordinate = xCoordMenuFieldText3;
            printString(varList[15]);

            xCoordinate = xCoordMenuFieldText4;
            printString(varList[16]);

            xCoordinate = xCoordMenuFieldText5;
            printString(varList[17]);
            break;
        }
        break;
    case 17:                                                                   //if in font5x7 font mode
    case 18:                                                                   //if in fontVW_1 font mode
    case 19:                                                                   //if in fontVW_2 font mode
    	mainMenu();
    	break;
    case 20:                                                                   //add, sub, times and div tables
    case 21:
    case 22:
    case 23:
    	break;
    }
}

void mainMenu(void) {
    switch (menu) {
    case 1:                                                                    //program menu 0
    	xCoordinate = xCoordMenuFieldText0;
    	printString("MONIC");

    	xCoordinate = xCoordMenuFieldText1;
    	printString("C");

    	xCoordinate = xCoordMenuFieldText2;
    	printString("BASIC");

    	xCoordinate = xCoordMenuFieldText3;
    	printString("FORTRN");

    	xCoordinate = xCoordMenuFieldText4;
    	printString("PYTHON");

    	xCoordinate = xCoordMenuFieldText5;
    	printString("ASM");
        break;
    //case 1:                                                                    //program menu 1
        //break;
    case 0:                                                                    //custom menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString(custMenuLbl[0]);

        xCoordinate = xCoordMenuFieldText1;
        printString(custMenuLbl[1]);

        xCoordinate = xCoordMenuFieldText2;
        printString(custMenuLbl[2]);

        xCoordinate = xCoordMenuFieldText3;
        printString(custMenuLbl[3]);

        xCoordinate = xCoordMenuFieldText4;
        printString(custMenuLbl[4]);

        xCoordinate = xCoordMenuFieldText5;
        printString(custMenuLbl[5]);
        break;
    case 3:                                                                    //custom menu 2
        break;
    case 4:                                                                    //custom menu 3
        break;
    case 5:                                                                    //custom menu 4
        break;
    case 6:                                                                    //custom menu 5
        break;
    case 7:                                                                    //custom menu 6
        break;
    case 8:                                                                    //custom menu 7
        break;
    case 9:                                                                    //custom menu 8
        break;
    case 10:                                                                   //custom menu 9
        break;
    case 11:                                                                   //custom menu 10
        break;
    case 12:                                                                   //custom menu 11
        break;
    case 13:                                                                   //custom menu 12
        break;
    case 14:                                                                   //custom menu 13
        break;
    case 15:                                                                   //COMPLEX menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString("CONJUZ");

        xCoordinate = xCoordMenuFieldText1;
        printString("|Z|");

        xCoordinate = xCoordMenuFieldText2;
        printString("POLAR");

        xCoordinate = xCoordMenuFieldText3;
        printString("RECTAN");
        break;
    case 16:                                                                   //COMPLEX menu 2
        break;
    case 17:                                                                   //GRAPH menu 1
        break;
    case 18:                                                                   //GRAPH menu 2
        break;
    case 19:                                                                   //MATH menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString("CMPLEX");

        xCoordinate = xCoordMenuFieldText1;
        printString("FRCTAL");
        break;
    case 20:                                                                   //MATH menu 2
        break;
    case 21:                                                                   //MATH menu 3
        break;
    case 22:                                                                   //MATH menu 4
        break;
    case 23:                                                                   //MATRIX menu 1
        break;
    case 24:                                                                   //MATRIX menu 2
        break;
    case 25:                                                                   //SOLVE menu 1
        break;
    case 26:                                                                   //SOLVE menu 2
        break;
    case 27:                                                                   //STATISTICS menu 1
        break;
    case 28:                                                                   //STATISTICS menu 2
        break;
    case 29:                                                                   //STACK menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString("DUPLIC");

        xCoordinate = xCoordMenuFieldText1;
        printString("ROTATE");

        xCoordinate = xCoordMenuFieldText2;
        printString("UNROTA");

        xCoordinate = xCoordMenuFieldText3;
        printString("ENTER2");

        xCoordinate = xCoordMenuFieldText4;
        printString("ENTER3");

        xCoordinate = xCoordMenuFieldText5;
        printString("ENTER4");
        break;
    case 30:                                                                   //STACK menu 2
        xCoordinate = xCoordMenuFieldText0;
        printString("OVER");

        xCoordinate = xCoordMenuFieldText1;
        printString("DROP2");

        xCoordinate = xCoordMenuFieldText2;
        printString("DROP3");

        xCoordinate = xCoordMenuFieldText3;
        printString("DEPTH");
        break;
    case 31:                                                                   //MODE menu 1
        xCoordinate = xCoordMenuFieldText0;
        if (flag2 & ALGENTRY) printString("ALGEBR");
        else printString("RPN");

        xCoordinate = xCoordMenuFieldText1;
        if (flag3 & prgCplxStack) printString("DOUBLE");                       //IEEE double program mode
        else printString("MULPRE");                                            //multiple-precision program mode
        break;
    case 32:                                                                   //MODE menu 2
        break;
    case 33:                                                                   //MODE menu 3
        break;
    case 34:                                                                   //MODE menu 4
        break;
    case 35:                                                                   //MODE menu 5
        break;
    case 36:                                                                   //MODE menu 6
        break;
    case 37:                                                                   //TRN menu
        xCoordinate = xCoordMenuFieldText0;
        printString("A");

        xCoordinate = xCoordMenuFieldText1;
        printString("B");

        xCoordinate = xCoordMenuFieldText2;
        printString("C");
        break;
    case 38:                                                                   //SYSTEM menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString("BKLOFF");

        xCoordinate = xCoordMenuFieldText1;
        printString("FONT");
        break;
    case 39:                                                                   //SYSTEM menu 2
        break;
    case 40:                                                                   //FONT menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString("AF 5x7");

        xCoordinate = xCoordMenuFieldText1;
        printString("");

        xCoordinate = xCoordMenuFieldText2;
        printString("");
        break;
    case 41:                                                                   //FONT menu 2
        break;
    case 42:                                                                   //FRACTAL menu
        xCoordinate = xCoordMenuFieldText0;
        printString("MANFLT");

        xCoordinate = xCoordMenuFieldText1;
        printString("MANDBL");
        break;
    case 43:                                                                   //CAA menu 1
    	xCoordinate = xCoordMenuFieldText0;
    	printString("ADDT");

    	xCoordinate = xCoordMenuFieldText1;
    	printString("SUBT");

    	xCoordinate = xCoordMenuFieldText2;
    	printString("TIMEST");

    	xCoordinate = xCoordMenuFieldText3;
    	printString("DIVT");
    	break;
    case 44:                                                                   //CAA menu 2
    	break;
    case 45:                                                                   //CAA menu 3
    	break;
    case 46:                                                                   //CAA menu 4
    	break;
    case 201:                                                                  //custom menu 1
        xCoordinate = xCoordMenuFieldText0;
        printString(custMenuLbl[6]);

        xCoordinate = xCoordMenuFieldText1;
        printString(custMenuLbl[7]);

        xCoordinate = xCoordMenuFieldText2;
        printString(custMenuLbl[8]);

        xCoordinate = xCoordMenuFieldText3;
        printString(custMenuLbl[9]);

        xCoordinate = xCoordMenuFieldText4;
        printString(custMenuLbl[10]);

        xCoordinate = xCoordMenuFieldText5;
        printString(custMenuLbl[11]);
        break;
    }
}



