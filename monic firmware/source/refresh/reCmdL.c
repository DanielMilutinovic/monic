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

extern unsigned char matrixRow;
extern unsigned char matrixColumn;

extern unsigned char kpPlane;
extern unsigned int flag1;
extern unsigned int flag2;
extern unsigned int flag3;
extern char cmdL_S[cmdL_SLength];
extern int16_t xCoordinate;
extern int16_t xCoordinateCursor;
extern int16_t yCoordinateCursor;

extern int16_t yCoordinate;

extern unsigned int indexLink[stackDDepth];
extern double uStackD[stackDDepth];
extern unsigned int uStackIndex;
extern unsigned char uStackMDim[stackDDepth][2];
extern unsigned char uStackType[stackDDepth];

extern unsigned char annunciator;

extern unsigned int *prg;
extern unsigned int prgIndex;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

extern uint32_t fontColour;

//functions

void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);

void viewValueReal(void);
void enterMatrixDim(void);
void enterProgVarName(void);
void eraseProgVar(void);
void algEntry(void);
void RPN_Entry(void);

void print(const char*, int16_t, int16_t);
void printASCII(unsigned char);

void displayStringRight(void);
void doubleToString(double);

void printString(char*);
void printStringRight(char*);
void printStringcmdL(char*);
void printCharactercmdL(char);

///////////////////////////////////////////////////////////////////////////////

void reCmdL(void) {
    unsigned char i = 0;

    switch (kpPlane) {
    case 0:                                                                    //if in main mode
        yCoordinateCursor = yCoordCmdLTop;
        fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        fontColour = YELLOW;
        algEntry();
        break;
    case 2:                                                                    //if entering matrix dimensions
        //page = yCoordCmdLTop;
        //ClrCmdL();
        //RectFill(0, max_xCoord, yCoordCmdLTop, yCoordCmdLBottom, backgroundColour);
        //drawRect(max_xCoord, yCoordCmdLTop, max_xCoord, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        //GrContextForegroundSet(&sContext, CmdLColour);
        fontColour = YELLOW;
        enterMatrixDim();
        break;
    case 12:                                                                   //if in Keystroke program debug mode
        if (prgIndex) {                                                        //clear the command line after it is pushed onto cStack
            if (prg[prgIndex-1] == equalKSPrg)
            	//RectFill(0, max_xCoord, yCoordCmdLTop, yCoordCmdLBottom, backgroundColour); //ClrCmdL();
            	//drawRect(max_xCoord, yCoordCmdLTop, max_xCoord, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
            	fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        }
        break;
    case 15:                                                                   //if in Keystroke program edit Var mode
    case 16:                                                                   //if in Keystroke program edit STO mode
    case 5:                                                                    //if in Keystroke program edit mode
        if (flag2 & CURSORON) {
            //page = yCoordCmdLTop;
            xCoordinateCursor = 0;
            yCoordinateCursor = yCoordCmdLTop;
            //ClrCmdL();
            //RectFill(0, max_xCoord, yCoordCmdLTop, yCoordCmdLBottom, backgroundColour);
            //drawRect(max_xCoord, yCoordCmdLTop, max_xCoord, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
            fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
            //GrContextForegroundSet(&sContext, CmdLColour);
            fontColour = YELLOW;
            if (annunciator) {
                switch (annunciator) {
                case 1:
                    printStringcmdL("LABEL ");
                    break;
                case 2:
                    printStringcmdL("STORE IN: ");
                    break;
                case 3:
                    printStringcmdL("RECALL ");
                    break;
                case 4:
                    printStringcmdL("INCREMENT ");
                    break;
                case 5:
                    printStringcmdL("DECREMENT ");
                    break;
                case 6:
                    printStringcmdL("GOTO ");
                    break;
                case 7:
                    printStringcmdL("GOTOIF=0 ");
                    break;
                case 8:
                    printStringcmdL("GOTOIF!=0 ");
                    break;
                case 9:
                    printStringcmdL("GOTOIF<= ");
                    break;
                case 10:
                    printStringcmdL("GOTOIF< ");
                    break;
                case 11:
                    printStringcmdL("GOTOIF> ");
                    break;
                case 12:
                    printStringcmdL("GOTOIF= ");
                    break;
                }
            }
            else {
                xCoordinateCursor = 0;
                if (flag1 & NEGSIG) printStringcmdL("-");
            }
            while (cmdL_S[i]) {
                printASCII(cmdL_S[i]);
                i += 1;
            }
        }
        break;
    case 8:                                                                    //if viewing value
        xCoordinate = 319;
        yCoordinate = yCoordCmdLTop;
        fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        fontColour = YELLOW;
        viewValueReal();
        break;
    case 11:                                                                   //if entering program/variable/folder name
        yCoordinate = yCoordCmdLTop;
        fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        fontColour = YELLOW;
        enterProgVarName();
        break;
    case 14:                                                                   //if erasing program/variable
        fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
        fontColour = YELLOW;
        eraseProgVar();
        break;
    case 20:                                                                   //add tables
    case 21:                                                                   //subtract tables
    case 22:                                                                   //times tables
    case 23:                                                                   //division tables
    	flag2 &= ~INTERRUPT;
    	yCoordinateCursor = yCoordCmdLTop;
    	fillRect(0, yCoordCmdLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordCmdLTop, backgroundColour);
    	fontColour = YELLOW;
    	algEntry();
    	flag2 |= INTERRUPT;
    	break;
    default:
    	__asm volatile ("nop");
    }
}

void viewValueReal(void) {
    if (uStackType[uStackIndex]) {                                             //if viewing matrix
        switch (matrixRow) {
        case 1:                                                                //row 1
            switch (matrixColumn) {
            case 1:                                                            //(1,1)
                if (uStackD[indexLink[uStackIndex - 1] + 1]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 1]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 2:                                                            //(1,2)
                if (uStackD[indexLink[uStackIndex - 1] + 2]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 2]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 3:                                                            //(1,3)
                if (uStackD[indexLink[uStackIndex - 1] + 3]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 3]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 4:                                                            //(1,4)
                if (uStackD[indexLink[uStackIndex - 1] + 4]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 4]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            }
            break;
        case 2:                                                                //row 2
            switch (matrixColumn) {
            case 1:                                                            //(2,1)
                if (uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 1]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 1]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 2:                                                            //(2,2)
                if (uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 2]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 2]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 3:                                                            //(2,3)
                if (uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 3]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 3]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 4:                                                            //(2,4)
                if (uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 4]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + uStackMDim[uStackIndex][1] + 4]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            }
            break;
        case 3:                                                                //row 3
            switch (matrixColumn) {
            case 1:                                                            //(3,1)
                if (uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 1]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 1]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 2:                                                            //(3,2)
                if (uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 2]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 2]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 3:                                                            //(3,3)
                if (uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 3]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 3]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 4:                                                            //(3,4)
                if (uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 4]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 2 * uStackMDim[uStackIndex][1] + 4]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            }
            break;
        case 4:                                                                //row 4
            switch (matrixColumn) {
            case 1:                                                            //(4,1)
                if (uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 1]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 1]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 2:                                                            //(4,2)
                if (uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 2]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 2]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 3:                                                            //(4,3)
                if (uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 3]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 3]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            case 4:                                                            //(4,4)
                if (uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 4]) {
                    doubleToString(uStackD[indexLink[uStackIndex - 1] + 3 * uStackMDim[uStackIndex][1] + 4]);
                    displayStringRight();
                }
                else printStringRight("0");
                break;
            }
            break;
        }
    }
    else {                                                                     //if viewing complex number
        if (uStackD[indexLink[uStackIndex]]) {
            doubleToString(uStackD[indexLink[uStackIndex]]);
            displayStringRight();
        }
        else printStringRight("0");
    }
}

void enterMatrixDim(void) {
    xCoordinate = 0;
    //print("MATRIX DIM:", xCoordinate, page);

    if (matrixRow) {
        xCoordinate += 100; //length of "MATRIX DIM:" - recalculate for different font
        //printChar(matrixRow, xCoordinate, page);
        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) matrixRow + 48 - 32] + 1];
        //print("x",xCoordinate, page);
    }
    else {
        xCoordinate += 100;            //length of "MATRIX DIM: " - recalculate for different font
        //print("x",xCoordinate, page);
    }
    xCoordinate += (uint32_t) fontData[fontOffset[120 - 32] + 1];

    if (matrixColumn) {
        //printChar(matrixColumn, xCoordinate, page);
        xCoordinate += (uint32_t) fontData[fontOffset[(uint32_t) matrixColumn + 48 - 32] + 1];
    }
//    if (flag3 & enterMatrixRow) xCoordinate = 12 * 16;
//    else {
//        //if (flag3 & enterMatrixColumn) xCoordinate = 14 * fontWidth;
//        //else xCoordinate = 15 * fontWidth;
//    }
}

void enterProgVarName(void) {
    unsigned char i = 0;

    fontColour = YELLOW;
    xCoordinateCursor = 0;
    if (flag3 & newProgram) printStringcmdL("PROGRAM NAME: ");
    else {
        if (flag3 & newFolder) printStringcmdL("FOLDER NAME: ");
        else printStringcmdL("VARIABLE NAME: ");
    }
    while (cmdL_S[i]) {
        printASCII(cmdL_S[i]);
        i += 1;
    }
}

void eraseProgVar(void) {
    //print("ERASE VAR/PROG/FOLD", 0, page);
}

void algEntry(void) {
    unsigned char i = 0;
    xCoordinateCursor = 0;
    //if (flag1 & NEGSIG) printStringcmdL("-");
    while (cmdL_S[i]) {
        printASCII(cmdL_S[i]);
        i += 1;
    }
}

void RPN_Entry(void) {
    unsigned char i = 0;
    xCoordinateCursor = 0;
    //if (flag1 & NEGSIG) printStringcmdL("-");                                  //print "-" sign
    while (cmdL_S[i]) {
        printASCII(cmdL_S[i]);
        i += 1;
    }
}

void printASCII(unsigned char x) {
    switch (x) {
    case 11:
        printStringcmdL("0.");
        break;
    case 12:                                                                   //exponent sign
        if (flag1 & NEGEXP) printStringcmdL("-");
        else printStringcmdL(" ");
        break;
    case 32:                                                                   //SPACE
        break;
    case 33:
        printStringcmdL("!");
        break;
    case 40:
        printStringcmdL("(");
        break;
    case 41:
        printStringcmdL(")");
        break;
    case 42:
        printStringcmdL("*");
        break;
    case 43:
        printStringcmdL("+");
        break;
    case 45:
        printStringcmdL("-");
        break;
    case 46:
        printStringcmdL(".");
        break;
    case 47:
        printStringcmdL("/");
        break;
    case 48:
        printStringcmdL("0");
        break;
    case 49:
        printStringcmdL("1");
        break;
    case 50:
        printStringcmdL("2");
        break;
    case 51:
        printStringcmdL("3");
        break;
    case 52:
        printStringcmdL("4");
        break;
    case 53:
        printStringcmdL("5");
        break;
    case 54:
        printStringcmdL("6");
        break;
    case 55:
        printStringcmdL("7");
        break;
    case 56:
        printStringcmdL("8");
        break;
    case 57:
        printStringcmdL("9");
        break;
    case 58:
        printStringcmdL(":");
        break;
    case 60:
        printStringcmdL("<");
        break;
    case 61:
        printStringcmdL("=");
        break;
    case 62:
        printStringcmdL(">");
        break;
    case 65:
        printStringcmdL("A");
        break;
    case 66:
        printStringcmdL("B");
        break;
    case 67:
        printStringcmdL("C");
        break;
    case 68:
        printStringcmdL("D");
        break;
    case 69:
        printStringcmdL("E");
        break;
    case 70:
        printStringcmdL("F");
        break;
    case 71:
        printStringcmdL("G");
        break;
    case 72:
        printStringcmdL("H");
        break;
    case 73:
        printStringcmdL("I");
        break;
    case 74:
        printStringcmdL("J");
        break;
    case 75:
        printStringcmdL("K");
        break;
    case 76:
        printStringcmdL("L");
        break;
    case 77:
        printStringcmdL("M");
        break;
    case 78:
        printStringcmdL("N");
        break;
    case 79:
        printStringcmdL("O");
        break;
    case 80:
        printStringcmdL("P");
        break;
    case 81:
        printStringcmdL("Q");
        break;
    case 82:
        printStringcmdL("R");
        break;
    case 83:
        printStringcmdL("S");
        break;
    case 84:
        printStringcmdL("T");
        break;
    case 85:
        printStringcmdL("U");
        break;
    case 86:
        printStringcmdL("V");
        break;
    case 87:
        printStringcmdL("W");
        break;
    case 88:
        printStringcmdL("X");
        break;
    case 89:
        printStringcmdL("Y");
        break;
    case 90:
        printStringcmdL("Z");
        break;
    case 94:
        printStringcmdL("^");
        break;
    case 128:                                                                  //display "-", may change later to special +/- sign
        printStringcmdL("-");
        break;
    case 129:
        printStringcmdL("sin");
        break;
    case 130:
        printStringcmdL("cos");
        break;
    case 131:
        printStringcmdL("tan");
        break;
    case 132:
        printStringcmdL("ans");
        break;
    case 133:
    	printStringcmdL("PI");
    	break;
    case 134:
    	printStringcmdL("e^");
    	break;
    case 135:
    	printStringcmdL("10^");
    	break;
    case 136:
    	printStringcmdL("*10^");
    	break;
    case 137:
    	printStringcmdL("log");
    	break;
    case 138:
    	printStringcmdL("ln");
    	break;
    case 139:
    	printStringcmdL("asin");
    	break;
    case 140:
    	printStringcmdL("acos");
    	break;
    case 141:
    	printStringcmdL("atan");
    	break;
    }
}

