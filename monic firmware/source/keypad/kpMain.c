//Copyright 2020 Daniel Milutinovic

//Redistribution and use in source and binary forms, with or without modification, are permitted provided
//that the following conditions are met:

//1. Redistributions of source code must retain the above copyright notice, this list of conditions and the
//following disclaimer.

//2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the
//following disclaimer in the documentation and/or other materials provided with the distribution.

//3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote
//products derived from this software without specific prior written permission.

//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
//INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
//DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
//SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
//SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
//WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
//OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

//includes

#include <stdint.h>

#include <math.h>

#include "../user.h"
#include "../header/globalVars.h"

#include "clock_config.h"

//variables

double valueCmdL_SigD = 0.0;                                                   //command line significand value
double valueCmdL_ExpD = 0.0;                                                   //command line exponent value
double valueCmdL_D;                                                            //command line value
double decDigits = 0.0;                                                        //number of digits after decimal point
unsigned char sigLength = 0;                                                   //significand length (no. of digits)
unsigned char expLength = 0;                                                   //exponent length (no. of digits)

float valueCmdL_SigF = 0.0f;
float valueCmdL_ExpF = 0.0f;
float valueCmdL_F;
float decDigitsF = 0.0f;

extern unsigned char prgMode;
unsigned char prgMode1;
unsigned char prgMode2;
unsigned char prgMode3;
unsigned char prgMode4;
unsigned char prgMode5;
unsigned char prgMode6;

extern unsigned int flag1;
extern unsigned int flag2;
extern unsigned int flag3;

extern unsigned char keyHeldCtr;
extern unsigned int keyNumber;                                                 //number of the key pressed
extern unsigned char menu;

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern unsigned int uStackIndex;                                               //user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix
extern unsigned int uStackDIndex;                                              //complex user stack index
extern double uStackD[stackDDepth];                                            //array to store real part
extern double uStackDIMAG[stackDDepth];                                        //array to store imaginary part
extern unsigned int indexLink[stackDDepth];
extern unsigned char uStackMDim[stackDDepth][2];                               //array to store matrix dimensions

extern unsigned int cStackIndex;                                               //complex user stack index
extern double cStackD[stackDDepth];                                            //array to store real part on complex stack
extern double cStackDIMAG[stackDDepth];                                        //array to store imaginary part on complex stack

extern unsigned int uStackFIndex;

extern unsigned char screenNumber;

extern unsigned char kpPlane;

extern unsigned int matrixRow;
extern unsigned int matrixColumn;

extern unsigned char memAlloc[memAllocLength];
extern unsigned int memAllocCtr;

extern unsigned int *prg;
extern unsigned int prgIndex;
extern unsigned int prg1[numberOfPrgSteps];
extern unsigned int prg2[numberOfPrgSteps];
extern unsigned int prg3[numberOfPrgSteps];
extern unsigned int prg4[numberOfPrgSteps];
extern unsigned int prg5[numberOfPrgSteps];
extern unsigned int prg6[numberOfPrgSteps];

extern unsigned int *labelAddress;
extern unsigned int labelAddress1[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress2[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress3[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress4[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress5[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress6[labelAddressLength];                                          //array to store program counter values corresponding to labels

extern double prgConstants1[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF1[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants2[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF2[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants3[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF3[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants4[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF4[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants5[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF5[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants6[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF6[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)
extern double *prgConstants;
extern float *prgConstantsF;

extern char (*varList)[varListStringLength];
extern char varList1[varListLength][varListStringLength];
extern char varList2[varListLength][varListStringLength];
extern char varList3[varListLength][varListStringLength];
extern char varList4[varListLength][varListStringLength];
extern char varList5[varListLength][varListStringLength];
extern char varList6[varListLength][varListStringLength];

extern unsigned int custMenuFunc[custMenuLength];
extern unsigned char custMenuLbl[custMenuLength][6];

extern uint32_t fontLength;

unsigned int cmdL_Parsed[cmdL_ParsedLength];

extern const uint8_t AdafruitClassicData[];
extern uint8_t size;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

extern int16_t xCoordinateCursor;
extern int16_t yCoordinateCursor;

extern unsigned char cursorWidth;
extern unsigned char cursorHeight;

extern unsigned char QNO;
unsigned int elapsedTime;
unsigned int counter;

extern int16_t xCoordinate;
extern int16_t yCoordinate;

//functions

void updateValueCmdL_SigD(double);
void updateValueCmdL_ExpD(double);

void delete(void);
void clear(void);
void swap(void);

void enterComplex(void);
void enterImaginaryPart(void);
void decimalPoint(void);
void resetVar(void);
void setForPrgEdit(void);
void setForHLPrgEdit(void);

void negate(void);
void add(void);
void subtract(void);
void multiply(void);
void divide(void);

void sine(void);
void cosine(void);
void tangent(void);
void arcsine(void);
void arccosine(void);
void arctangent(void);

void tenPower(void);
void eulerPower(void);
void PI(void);
void logTen(void);
void logEuler(void);

void reciprocal(void);
void power(void);
void powerR(void);
void squareRoot(void);
void cubeRoot(void);
void square(void);

void enterAlgebraic(void);

void runPrg(unsigned int);
void runPrgFast(void);
void runPrgCplx(unsigned int);
void runPrgCplxFast(void);

void menuKey1_Main(void);
void menuKey1_Main_S(void);
void menuKey1_Main_H(void);

void menuKey2_Main(void);
void menuKey2_Main_S(void);
void menuKey2_Main_H(void);

void menuKey3_Main(void);
void menuKey3_Main_S(void);
void menuKey3_Main_H(void);

void menuKey4_Main(void);

void menuKey5_Main(void);

void menuKey6_Main(void);

void reStatL(void);
void reCmdL(void);
void reStack(void);
void reMenu(void);
void scanKp(void);
void backlightOn(void);
void backlightOff(void);
void drawRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void fillScreen(uint16_t);

//void mandelbrot4(unsigned int);
void mandelbrot5(unsigned int);                                                //single precision
void mandelbrot6(unsigned int);                                                //double precision

void displayPrgStep(unsigned int);
void printString(char*);

//constants
                               //{0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31}
const unsigned char nextMenu[] = {1,0,3,4,5,6,7,8,9,10,11,12,13,14,2,16,15,18,17,20,21,22,19,24,23,26,25,28,27,30,29,32,
                          33,34,35,36,31,37,39,38,41,40,42,44,45,46,47,48,43};
                       //{32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48};

///////////////////////////////////////////////////////////////////////////////

void kpMain (unsigned int x) {
    //unsigned char i;
    switch (x) {
    case equalMain:                                                            //EQUAL
//        if (flag2 & ALGENTRY) {
//            enterAlgebraic();
//            prgIndex = 0;
//            prg = cmdL_Parsed;
//            while (prg[prgIndex] != END) runPrgCplx(prg[prgIndex]);
//
//            uStackDIndex += 1;                                                 //push complex stack level 1 onto user stack
//            uStackD[uStackDIndex] = cStackD[cStackIndex];
//            //uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//            uStackDIMAG[uStackDIndex] = 0.0;;
//
//            uStackIndex += 1;
//            uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
//            indexLink[uStackIndex] = uStackDIndex;
//
//            cmdL_Term = 0;
//            for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
//
//            screenNumber = 0;

            enterComplex();
        //}
        //else enterComplex();                                                   //RPN mode
        break;
    case ansMain:                                                              //ANS
        if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 132;
            cmdL_Term += 1;
        }
        break;
    case zeroMain:                                                             //ZERO
        //if (flag2 & ALGENTRY) {
    	if (cmdL_Term) {
            cmdL_S[cmdL_Term] = '0';
            cmdL_Term ++;
    	}
    	else {
    		cmdL_S[cmdL_Term] = '0';
    		cmdL_Term ++;
    		cmdL_S[cmdL_Term] = '.';
    		cmdL_Term ++;
    	}
        //}
//        else {
//            if (flag1 & EXP) {                                                 //if in exponent entry field
//                cmdL_S[cmdL_Term] = 48;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(0.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 48;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(0.0);
//                }
//                if (sigLength == 0) flag1 |= ZEROFIRST;
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);                         //do not update status line, stack or menu (reduce flicker)
        break;
    case oneMain:                                                              //ONE
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 49;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 49;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(1.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 49;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(1.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case twoMain:                                                              //TWO
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 50;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 50;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(2.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 50;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(2.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case threeMain:                                                            //THREE
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 51;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 51;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(3.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 51;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(3.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case fourMain:                                                             //FOUR
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 52;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 52;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(4.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 52;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(4.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case fiveMain:                                                             //FIVE
            //if (flag2 & ALGENTRY) {
                cmdL_S[cmdL_Term] = 53;
                cmdL_Term += 1;
            //}
//            else {
//                if (flag1 & EXP) {
//                    cmdL_S[cmdL_Term] = 53;
//                    cmdL_Term += 1;
//                    updateValueCmdL_ExpD(5.0);
//                }
//                else {
//                    if ((flag1 & ZEROFIRST) == 0) {
//                        cmdL_S[cmdL_Term] = 53;
//                        cmdL_Term += 1;
//                        updateValueCmdL_SigD(5.0);
//                    }
//                }
//            }
            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
            break;
    case sixMain:                                                              //SIX
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 54;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 54;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(6.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 54;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(6.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case sevenMain:                                                            //SEVEN
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 55;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 55;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(7.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 55;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(7.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case eightMain:                                                            //EIGHT
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 56;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 56;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(8.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 56;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(8.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case nineMain:                                                             //NINE
        //if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 57;
            cmdL_Term += 1;
        //}
//        else {
//            if (flag1 & EXP) {
//                cmdL_S[cmdL_Term] = 57;
//                cmdL_Term += 1;
//                updateValueCmdL_ExpD(9.0);
//            }
//            else {
//                if ((flag1 & ZEROFIRST) == 0) {
//                    cmdL_S[cmdL_Term] = 57;
//                    cmdL_Term += 1;
//                    updateValueCmdL_SigD(9.0);
//                }
//            }
//        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case decimalPointMain:                                                     //DECIMAL POINT
        decimalPoint();
        break;
    case deleteMain:                                                           //DELETE
        delete();
        break;
    case clearMain:                                                            //CLEAR
        clear();
        break;
    case folderMain:                                                           //FOLDER
        flag3 |= newFolder;
        kpPlane = 11;
        break;
    case shiftMain:                                                            //SHIFT
        flag1 |= SHIFT;
        flag2 |= (STACKOFF | MENUOFF | COMMANDLINEOFF);
        break;
    case shiftshiftMain:                                                       //TOGGLE SHIFT
        flag2 |= (STACKOFF | MENUOFF | COMMANDLINEOFF);
        break;
    case openParenthesis:                                                      //(
        if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 40;
            cmdL_Term += 1;
        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case closeParenthesis:                                                     //)
        if (flag2 & ALGENTRY) {
            cmdL_S[cmdL_Term] = 41;
            cmdL_Term += 1;
        }
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case matrixMain:                                                           //MATRIX KEY PLANE
        kpPlane = 2;
        //flag3 |= enterMatrixRow;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case pushImagPartMain:                                                     //push command line value onto uStackDIMAG
        enterImaginaryPart();
//        enterAlgebraic();
//        prgIndex = 0;
//        prg = cmdL_Parsed;
//        while (prg[prgIndex] != END) runPrgCplx(prg[prgIndex]);
//
//        uStackDIMAG[uStackDIndex] = cStackD[cStackIndex];
//
//        cmdL_Term = 0;
//        for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
//
//        screenNumber = 0;
        break;
    case negateMain:                                                           //NEGATE
        negate();
        break;
    case exponentMain:                                                         //EXPONENT
        //if ((flag1 & EXP) == 0) {
//            if (sigLength) {
//                if ((flag1 & EXP) == 0) {
//                    flag1 |= EXP;
//                    cmdL_S[cmdL_Term] = 12;
//                    cmdL_Term += 1;
//                }
//            }
        	cmdL_S[cmdL_Term] = '*';
        	cmdL_Term += 1;
        	cmdL_S[cmdL_Term] = '1';
        	cmdL_Term += 1;
        	cmdL_S[cmdL_Term] = '0';
        	cmdL_Term += 1;
        	cmdL_S[cmdL_Term] = '^';
        	cmdL_Term += 1;

//    	if (cmdL_Term) {
//    		cmdL_S[cmdL_Term] = 136;
//    		cmdL_Term ++;
//    	}

        //}
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        break;
    case addMain:                                                              //ADDITION
        add();
        break;
    case subtractMain:                                                         //SUBTRACTION
        subtract();
        break;
    case multiplyMain:                                                         //MULTIPLICATION
        multiply();
        break;
    case divideMain:                                                           //DIVISION
        divide();
        break;
    case sineMain:                                                             //sine
    	sine();
    	break;
    case cosineMain:                                                           //cosine
    	cosine();
    	break;
    case tangentMain:                                                          //tangent
    	tangent();
    	break;
    case arcSinMain:                                                           //arcsine
    	arcsine();
    	break;
    case arcCosMain:                                                           //arccosine
    	arccosine();
    	break;
    case arcTanMain:                                                           //arctangent
    	arctangent();
    	break;
    case reciprocalMain:                                                       //1/x
        reciprocal();
        break;
    case powerMain:                                                            //x^y
        power();
        break;
    case powerRMain:                                                           //x^(1/y)
        powerR();
        break;
    case squareMain:                                                           //x^2
        square();
        break;
    case squareRootMain:                                                       //SQUARE ROOT
        squareRoot();
        break;
    case cubeRootMain:                                                         //cube root
    	cubeRoot();
    	break;
    case tenPowerMain:                                                         //10^x
    	tenPower();
    	break;
    case eulerPowerMain:                                                       //e^x
    	eulerPower();
    	break;
    case PIMain:                                                               //PI
    	PI();
    	break;
    case log10Main:                                                            //log(x)
    	logTen();
    	break;
    case logEulerMain:                                                         //ln(x)
    	logEuler();
    	break;
    case viewMain:                                                             //VIEW
        kpPlane = 8;
        matrixRow = 1;
        matrixColumn = 1;
        flag2 &= ~CURSORON;                                                    //turn cursor off
        break;
    case programMain:                                                          //PROG menu
        menu = 1;
        break;
    case mathMain:                                                             //MATH menu
        menu = 19;
        break;
    case CAAMain:                                                              //Computer Aided Assessment menu
    	menu = 43;
    	break;
    case approxExactMain:                                                      //exact/approx mode toggle
    	if (flag2 & EXACT) flag2 &= ~EXACT;
    	else flag2 |= EXACT;
    	break;
    case degRadMain:                                                           //degree/radian toggle
    	if (flag2 & DEGREE) {
    		flag2 &= ~DEGREE;
    		flag2 |= RADIAN;
    	}
    	else {
    		flag2 &= ~RADIAN;
    		flag2 |= DEGREE;
    	}
    	break;
    case stackMain:                                                            //STACK menu
        menu = 29;
        break;
    case systemMain:                                                           //SYSTEM menu
        menu = 38;
        break;
    case modeMain:                                                             //MODE
        menu = 31;
        break;
    case exitMain:                                                             //M/EXIT
        //if (sigLength) {                                                       //M
        if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e6;
        }
        else {                                                                 //EXIT
            switch (menu) {
            case 15:                                                           //if in CPLX menu
                menu = 19;                                                     //return to MATH menu
                break;
            case 37:                                                           //if in TRIANGLE solver menu
                menu = 19;                                                     //return to MATH menu
                break;
            case 42:                                                           //if in FRACTAL menu
                menu = 19;                                                     //return to MATH menu
                break;
            default:
                menu = 0;                                                      //otherwise return to custom menu 0
            }
        }
        break;
    case downMain:                                                             //k/DOWN
        //if (sigLength) {                                                       //k
    	if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e3;
        }
        else {                                                                 //DOWN
            if (screenNumber > 0) screenNumber -= 1;
        }
        break;
    case upMain:                                                               //m/UP
        //if (sigLength) {                                                       //m
    	if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e-3;
        }
        else {                                                                 //UP
            if (screenNumber < 19) screenNumber += 1;
        }
        break;
    case rightMain:                                                            //u/RIGHT
        //if (sigLength) {                                                       //u
    	if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e-6;
        }
        break;
    case leftMain:                                                             //n/LEFT
        //if (sigLength) {                                                       //n
    	if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e-9;
        }
        break;
    case nextMain:                                                             //NEXT
        //if (sigLength) {
    	if (cmdL_Term) {
            enterComplex();
            uStackD[uStackDIndex] = uStackD[uStackDIndex] * 1.0e-12;
        }
        else menu = nextMenu[menu];
        break;
    case swapMain:                                                             //SWAP
        swap();
        break;
    case menuKey1Main:                                                         //MENU KEY 1
        menuKey1_Main();
        break;
    case menuKey1Main_S:                                                       //MENU KEY 1 SHIFTED
        menuKey1_Main_S();
        break;
    case menuKey1Main_H:                                                       //MENU KEY 1 HELD
        menuKey1_Main_H();
        break;
    case menuKey2Main:                                                         //MENU KEY 2
        menuKey2_Main();
        break;
    case menuKey2Main_S:                                                       //MENU KEY 2 SHIFTED
        menuKey2_Main_S();
        break;
    case menuKey2Main_H:                                                       //MENU KEY 2 HELD
        menuKey2_Main_H();
        break;
    case menuKey3Main:                                                         //MENU KEY 3
        menuKey3_Main();
        break;
    case menuKey3Main_S:                                                       //MENU KEY 3 SHIFTED
        menuKey3_Main_S();
        break;
    case menuKey3Main_H:                                                       //MENU KEY 3 HELD
        menuKey3_Main_H();
        break;
    case menuKey4Main:                                                         //MENU KEY 4
    	menuKey4_Main();
    	break;
    case menuKey5Main:                                                         //MENU KEY 5
    	menuKey5_Main();
    	break;
    case menuKey6Main:                                                         //MENU KEY 6
    	menuKey6_Main();
    	break;
    case eraseMain_H:                                                          //ERASE variable/program/folder
        menu = 0;
        kpPlane = 14;
        flag2 &= ~CURSORON;                                                    //turn cursor off
        break;
    default:
        flag2 |= (STATUSLINEOFF | STACKOFF | COMMANDLINEOFF | MENUOFF);        //do not update status line, stack, command line or menu
    }
}

void updateValueCmdL_SigD(double x) {
    valueCmdL_SigD = 10.0 * valueCmdL_SigD + x;
    sigLength += 1;
    if (flag1 & DECPOINT) {
        decDigits += 1.0;
    }
}

void updateValueCmdL_ExpD(double x) {
    valueCmdL_ExpD = 10.0 * valueCmdL_ExpD + x;
    expLength += 1;
}

void delete(void) {
    //if (flag2 & ALGENTRY) {
        if (cmdL_Term) {                                                       //delete character on command line if it is non-empty (Algebraic)
            cmdL_Term -= 1;
            cmdL_S[cmdL_Term] = 0x00;
            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        }
        else {                                                                 //otherwise drop one stack level (Algebraic)
            if (uStackIndex) {
                if (uStackType[uStackIndex]) {                                 //if matrix

                }
                else uStackDIndex -= 1;                                        //if complex scalar

                uStackIndex -= 1;
            }
        }
    //}
    //else {
//        if (sigLength) {                                                       //delete character on command line if it is non-empty (RPN)
//            cmdL_Term -= 1;
//            if ((cmdL_S[cmdL_Term] >= 48) && (cmdL_S[cmdL_Term] <= 57)) {      //if 0-9 digit
//                if (flag1 & EXP) {
//                    valueCmdL_ExpD = floor(valueCmdL_ExpD/10.0);
//                    expLength -= 1;
//                }
//                else {
//                    valueCmdL_SigD = floor(valueCmdL_SigD/10.0);
//                    sigLength -= 1;
//                    if (flag1 & DECPOINT) decDigits -= 1.0;
//                }
//            }
//            else {
//                if (cmdL_S[cmdL_Term] == 46) {                                 //decimal point
//                    flag1 &= ~DECPOINT;
//                    decDigits = 0.0;
//                }
//                if (cmdL_S[cmdL_Term] == 11) {                                 //"0."
//                    flag1 &= ~DECPOINT;
//                    decDigits = 0.0;
//                    sigLength = 0;
//                }
//                if (cmdL_S[cmdL_Term] == 12) {                                 //exponent entry field
//                    flag1 &= ~EXP;
//                    flag1 &= ~NEGEXP;
//                }
//            }
//            cmdL_S[cmdL_Term] = 0x00;
//            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
//        }
//        else {                                                                 //otherwise drop one stack level (RPN)
//            if (uStackIndex) {
//                if (uStackType[uStackIndex]) uStackDIndex = uStackDIndex - uStackMDim[uStackIndex][0] * uStackMDim[uStackIndex][1];
//                                                                               //if matrix
//                else uStackDIndex -= 1;                                        //if complex scalar
//
//                uStackIndex -= 1;
//            }
//        }
    //}
}

void clear(void) {
    unsigned char i;
    //if (flag2 & ALGENTRY) {
        if (cmdL_Term) {                                                       //clear command line if it is non-empty (Algebraic)
            cmdL_Term = 0;
            for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;

            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
        }
        else {                                                                 //otherwise clear the stack (Algebraic)
            uStackDIndex = 0;
            uStackIndex = 0;
        }
    //}
    //else {
//        if (sigLength) {                                                       //clear command line if it is non-empty (RPN)
//            flag1 = 0;                                                         //reset ready for next value to be entered on command line
//            sigLength = 0;
//            expLength = 0;
//            cmdL_Term = 0;
//            for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
//
//            valueCmdL_SigD = 0.0;
//            valueCmdL_ExpD = 0.0;
//            decDigits = 0.0;
//            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
//        }
//        else {                                                                 //otherwise clear the stack (RPN)
//            uStackDIndex = 0;
//            uStackIndex = 0;
//        }
    //}
}

void enterComplex(void) {
    unsigned char i;

//    if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//    valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//    if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//    uStackDIndex += 1;
//    uStackD[uStackDIndex] = valueCmdL_D;
//    uStackDIMAG[uStackDIndex] = 0.0;
//
//    uStackIndex += 1;
//    uStackType[uStackIndex] = 0;                                               //0 -> type complex scalar
//    indexLink[uStackIndex] = uStackDIndex;
//
//    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
//    sigLength = 0;
//    expLength = 0;
//    cmdL_Term = 0;
//    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
//
//    valueCmdL_SigD = 0.0;
//    valueCmdL_ExpD = 0.0;
//    decDigits = 0.0;
//
//    screenNumber = 0;

    enterAlgebraic();
    prgIndex = 0;
    prg = cmdL_Parsed;
    while (prg[prgIndex] != END) runPrgCplx(prg[prgIndex]);

    uStackDIndex += 1;                                                         //push complex stack level 1 onto user stack
    uStackD[uStackDIndex] = cStackD[cStackIndex];
    //uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
    uStackDIMAG[uStackDIndex] = 0.0;

    uStackIndex += 1;
    uStackType[uStackIndex] = 0;                                               //0 -> type complex scalar
    indexLink[uStackIndex] = uStackDIndex;

    cmdL_Term = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;

    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
    sigLength = 0;
    expLength = 0;

    valueCmdL_SigD = 0.0;
    valueCmdL_ExpD = 0.0;
    decDigits = 0.0;

    screenNumber = 0;
}

void enterImaginaryPart(void) {
    unsigned char i;

//    if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
//    valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
//    if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
//    uStackDIMAG[uStackDIndex] = valueCmdL_D;
//
//    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
//    sigLength = 0;
//    expLength = 0;
//    cmdL_Term = 0;
//    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
//
//    valueCmdL_SigD = 0.0;
//    valueCmdL_ExpD = 0.0;
//    decDigits = 0.0;

    enterAlgebraic();
    prgIndex = 0;
    prg = cmdL_Parsed;
    while (prg[prgIndex] != END) runPrgCplx(prg[prgIndex]);

    uStackDIMAG[uStackDIndex] = cStackD[cStackIndex];

    cmdL_Term = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;

    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
    sigLength = 0;
    expLength = 0;

    valueCmdL_SigD = 0.0;
    valueCmdL_ExpD = 0.0;
    decDigits = 0.0;

    screenNumber = 0;
}

void resetVar(void) {
    unsigned char i;

    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
    sigLength = 0;
    expLength = 0;
    cmdL_Term = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;

    valueCmdL_SigD = 0.0;
    valueCmdL_ExpD = 0.0;
    decDigits = 0.0;

//    valueCmdL_SigF = 0.0f;
//    valueCmdL_ExpF = 0.0f;
//    decDigitsF = 0.0f;
}

void setForPrgEdit(void) {
    kpPlane = 5; prgIndex = 0; flag2 &= ~CURSORON;
    menu = 0;
    resetVar();
}

void setForHLPrgEdit(void) {
    kpPlane = 6;
    flag2 |= CeditorRefresh;
    Cprg = Cprg1;
    CprgIndex = 0;
    xCoordinateCursor = 0;
    yCoordinateCursor = 0;
    menu = 0;
    //fontData = font6x8Data;
    //fontOffset = font6x8Offset;
    //cursorWidth = 6;
    //cursorHeight = 8;

    resetVar();
}

void decimalPoint(void) {
    //if (flag2 & ALGENTRY) {
	if (cmdL_Term) {
        cmdL_S[cmdL_Term] = '.';
        cmdL_Term ++;
	}
	else {
		cmdL_S[cmdL_Term] = '0';
		cmdL_Term ++;
		cmdL_S[cmdL_Term] = '.';
		cmdL_Term ++;
	}
    //}
//    else {
//        if (sigLength) {
//            if ((flag1 & DECPOINT) == 0) {
//                flag1 |= DECPOINT;
//                cmdL_S[cmdL_Term] = 46;
//                cmdL_Term += 1;
//            }
//        }
//        else {
//            sigLength = 1;
//            flag1 |= DECPOINT;
//            cmdL_S[cmdL_Term] = 11;
//            cmdL_Term += 1;
//        }
//        flag1 &= ~ZEROFIRST;
//    }
    flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);                             //do not update status line, stack or menu (reduce flicker)
}

void menuKey1_Main(void) {                                                     //MENU KEY 1
    //unsigned char i;

    switch (menu) {
    case 1:                                                                    //Keystroke program editor
        flag3 |= newProgram;
        for (memAllocCtr = 101; memAllocCtr < 201; memAllocCtr++) {
            if (memAlloc[memAllocCtr]) break;
        }
        memAlloc[memAllocCtr] = 0;
        switch (memAllocCtr) {
        case 101:                                                              //create KS program 1
            prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1;
            if (flag3 & prgCplxStack ) prgMode1 = 1; else prgMode1 = 0;
            break;
        case 102:                                                              //create KS program 2
            prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2;
            if (flag3 & prgCplxStack ) prgMode2 = 1; else prgMode2 = 0;
            break;
        case 103:                                                              //create KS program 3
            prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3;
            if (flag3 & prgCplxStack ) prgMode3 = 1; else prgMode3 = 0;
            break;
        case 104:                                                              //create KS program 4
            prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4;
            if (flag3 & prgCplxStack ) prgMode4 = 1; else prgMode4 = 0;
            break;
        case 105:                                                              //create KS program 5
            prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5;
            if (flag3 & prgCplxStack ) prgMode5 = 1; else prgMode5 = 0;
            break;
        case 106:                                                              //create KS program 6
            prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6;
            if (flag3 & prgCplxStack ) prgMode6 = 1; else prgMode6 = 0;
            break;
        }
        setForPrgEdit();                                                       //set for program editor
        break;
    case 0:                                                                    //execute program, push constant or open folder
        if (custMenuFunc[0]) {
            if (custMenuFunc[0] < 101) {                                       //push constant

            }
            else {
                if (custMenuFunc[0] < 201) {                                   //execute program
                    prgIndex = 0; flag2 |= RUN; flag2 &= ~CURSORON; uStackFIndex = 0;
                    reStatL();                                                 //to display "R"
                    switch (custMenuFunc[0]) {
                    case 101:
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
                        break;
                    case 102:
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; prgMode = prgMode2;
                        break;
                    case 103:
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; prgMode = prgMode3;
                        break;
                    case 104:
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; prgMode = prgMode4;
                        break;
                    case 105:
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; prgMode = prgMode5;
                        break;
                    case 106:
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; prgMode = prgMode6;
                        break;
                    }
                    if (prgMode) {
                        cStackIndex = 0;
                        runPrgCplxFast();
                        //push cStackD[cStackIndex] & cStackDIMAG[cStackIndex] onto the user stack
//                        uStackDIndex += 1;
//                        uStackD[uStackDIndex] = cStackD[cStackIndex];
//                        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//                        uStackIndex += 1;
//                        uStackType[uStackIndex] = 0;                           //0 -> type complex scalar
//                        indexLink[uStackIndex] = uStackDIndex;
                    }
                    else runPrgFast();
                    resetVar();
                    //clear portion of LCD not refreshed
                    //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
                    //fillRect(0, yCoordStatLBottom, TFTHEIGHT, yCoordLvl5Top - yCoordStatLBottom, backgroundColour);
                    fillScreen(BLACK);
                    flag2 |= CURSORON;
                }
                else menu = custMenuFunc[0];                                   //open folder
            }
        }
        break;
    case 15:                                                                   //CPLX menu - conjugate of Z
        if (uStackIndex) uStackDIMAG[uStackDIndex] = -uStackDIMAG[uStackDIndex];
        break;
    case 19:                                                                   //MATH menu
        menu = 15;                                                             //select CPLX menu
//            xcoord = 63;
//            ycoord = 32;
//            menu = 37;                                                                       //triangle solver
//
//            updateTriSolver(xcoord,ycoord);
//            updateMenu();
//
//            scanKeypad();
//            while (keyNumber != 36) {                                                        //loop until EXIT pressed
//                switch (keyNumber) {
//                case 37: ycoord -= 2; break;
//                case 38: ycoord += 2; break;
//                case 39: xcoord += 2; break;
//                case 40: xcoord -= 2; break;
//                }
//                updateTriSolver(xcoord,ycoord);
//
//                scanKeypad();
//            }
//            menu = 19;                                                                       //return to MATH menu
        break;
    case 29:                                                                   //DUPLICATE
        if (uStackIndex) {
            uStackDIndex += 1;
            uStackD[uStackDIndex] = uStackD[uStackDIndex-1];
            uStackDIMAG[uStackDIndex] = uStackDIMAG[uStackDIndex-1];

            uStackIndex += 1;
            uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
            indexLink[uStackIndex] = uStackDIndex;
        }
        break;
    case 30:                                                                   //OVER
//            if (uStackDDepth > 1) {
//                uStackDDepth += 1;
//                uStackD[uStackDDepth] = uStackD[uStackDDepth-2];
//            }
        break;
    case 31:                                                                   //MODE menu 1 - ALG/RPN toggle
        resetVar();

        if (flag2 & ALGENTRY) flag2 &= ~ALGENTRY;
        else flag2 |= ALGENTRY;
        break;
    case 38:                                                                   //SYS menu 1 - toggle GLCD backlight
        //if (flag2 & BACKLIGHTOFF) {
            //flag2 &= ~BACKLIGHTOFF;
            //backlightOn();
        //}
        //else {
            //flag2 |= BACKLIGHTOFF;
            //backlightOff();
        //}
        break;
    case 40:                                                                   //Adafruit "Classic" 5x7 font
        kpPlane = 17;
        fontData = AdafruitClassicData;
        size = 2;
        flag2 &= ~CURSORON;
        flag2 |= MENUOFF;
        break;
    case 42:                                                                   //MANDELBROT SET plot program
        mandelbrot5(248);
        flag2 &= ~CURSORON;
        scanKp();                                                              //HALT
        flag2 |= CURSORON;
        resetVar();
        fillScreen(BLACK);
        break;
    case 43:                                                                   //CAA menu 1 - add tables
    	QNO = 0;
    	//fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(280, yCoordStatLTop, 200, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 280;
    	printString("time=");
    	kpPlane = 20;
    	elapsedTime = 0;
    	counter = 1;
    	SysTick->LOAD = 0x0007A120 - 12;                                       //reload value for 1ms (subtract 12 to
    	                                                                       //compensate for interrupt latency)
    	SysTick->VAL = 0;
    	SysTick->CTRL = 0x07;
    	break;
    case 201:                                                                  //custom menu 1, MK1, i.e custMenuFunc[6]
        if (custMenuFunc[6]) {
            if (custMenuFunc[6] < 101) {                                       //push constant

            }
            else {
                if (custMenuFunc[6] < 201) {                                   //execute program
                    prgIndex = 0; flag2 |= RUN; flag2 &= ~CURSORON; uStackFIndex = 0;
                    reStatL();                                                 //to display "R"
                    switch (custMenuFunc[6]) {
                    case 101:
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
                        break;
                    case 102:
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; prgMode = prgMode2;
                        break;
                    case 103:
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; prgMode = prgMode3;
                        break;
                    case 104:
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; prgMode = prgMode4;
                        break;
                    case 105:
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; prgMode = prgMode5;
                        break;
                    case 106:
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; prgMode = prgMode6;
                        break;
                    }
                    if (prgMode) {
                        cStackIndex = 0;
                        runPrgCplxFast();
                        //push cStackD[cStackIndex] & cStackDIMAG[cStackIndex] onto the user stack
//                        uStackDIndex += 1;
//                        uStackD[uStackDIndex] = cStackD[cStackIndex];
//                        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//                        uStackIndex += 1;
//                        uStackType[uStackIndex] = 0;                           //0 -> type complex scalar
//                        indexLink[uStackIndex] = uStackDIndex;
                    }
                    else runPrgFast();
                    resetVar();
                    //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
                    //fillRect(0, yCoordStatLBottom, TFTHEIGHT, yCoordLvl5Top - yCoordStatLBottom, backgroundColour);
                    fillScreen(BLACK);
                    flag2 |= CURSORON;
                }
                else menu = custMenuFunc[6];                                   //open folder
            }
        }
        break;
    }
}

void menuKey1_Main_S(void) {                                                   //MENU KEY 1 SHIFTED
    switch (menu) {
    case 0:                                                                    //Edit program
        if (custMenuFunc[0]) {
            if (custMenuFunc[0] < 101) {                                       //variable

            }
            else {
                if (custMenuFunc[0] < 201) {                                   //program
                    switch (custMenuFunc[0]) {
                    case 101:                                                  //edit KS program 1
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1;
                        break;
                    case 102:                                                  //edit KS program 2
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2;
                        break;
                    case 103:                                                  //edit KS program 3
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3;
                        break;
                    case 104:                                                  //edit KS program 4
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4;
                        break;
                    case 105:                                                  //edit KS program 5
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5;
                        break;
                    case 106:                                                  //edit KS program 6
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6;
                        break;
                    }
                    setForPrgEdit();                                           //set for program editor
                }
                else {                                                         //folder

                }
            }
        }
        break;
    }
}

void menuKey1_Main_H(void) {                                                   //MENU KEY 1 HELD
    if (custMenuFunc[0] > 100) {                                               //debug KS program
        kpPlane = 12; flag2 &= ~CURSORON; prgIndex = 0; cStackIndex = 0;
        menu = 38;                                                             //DEBUG menu
        switch(custMenuFunc[0]) {
        case 101:                                                              //debug KS program 1
            prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1; prgMode = prgMode1;
            break;
        case 102:                                                              //debug KS program 2 etc.
            prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2; prgMode = prgMode2;
            break;
        case 103:
            prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3; prgMode = prgMode3;
            break;
        case 104:
            prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4; prgMode = prgMode4;
            break;
        case 105:
            prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5; prgMode = prgMode5;
            break;
        case 106:
            prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6; prgMode = prgMode6;
            break;
        }
    }
}

void menuKey2_Main(void) {                                                     //MENU KEY 2
    //unsigned char i;

    switch (menu) {
    case 0:                                                                    //execute program, push constant or open folder
        if (custMenuFunc[1]) {
            if (custMenuFunc[1] < 101) {                                       //push constant

            }
            else {
                if (custMenuFunc[1] < 201) {                                   //execute program
                    prgIndex = 0; flag2 |= RUN; flag2 &= ~CURSORON; uStackFIndex = 0;
                    reStatL();                                                 //to display "R"
                    switch (custMenuFunc[1]) {
                    case 101:
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
                        break;
                    case 102:
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; prgMode = prgMode2;
                        break;
                    case 103:
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; prgMode = prgMode3;
                        break;
                    case 104:
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; prgMode = prgMode4;
                        break;
                    case 105:
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; prgMode = prgMode5;
                        break;
                    case 106:
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; prgMode = prgMode6;
                        break;
                    }
                    if (prgMode) {
                        cStackIndex = 0;
                        runPrgCplxFast();
                        //push cStackD[cStackIndex] & cStackDIMAG[cStackIndex] onto the user stack
//                        uStackDIndex += 1;
//                        uStackD[uStackDIndex] = cStackD[cStackIndex];
//                        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//                        uStackIndex += 1;
//                        uStackType[uStackIndex] = 0;                           //0 -> type complex scalar
//                        indexLink[uStackIndex] = uStackDIndex;
                    }
                    else runPrgFast();
                    resetVar();
                    //clear portion of LCD not refreshed
                    //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
                    //fillRect(0, yCoordStatLBottom, TFTHEIGHT, yCoordLvl5Top - yCoordStatLBottom, backgroundColour);
                    fillScreen(BLACK);
                    flag2 |= CURSORON;
                }
                else menu = custMenuFunc[1];                                   //open folder
            }
        }
        break;
    case 1:                                                                    //C language program editor
        setForHLPrgEdit();
        break;
    case 15:                                                                   //CPLX menu - absolute value of Z
        if (uStackIndex) uStackD[uStackDIndex] = sqrt(uStackD[uStackDIndex] * uStackD[uStackDIndex] +
                                                      uStackDIMAG[uStackDIndex] * uStackDIMAG[uStackDIndex]);
        uStackDIMAG[uStackDIndex] = 0.0;
        break;
    case 19:                                                                   //MATH/FRACTAL menu
        menu = 42;
        break;
    case 31:                                                                   //MODE menu 1 - PROGDB/PROGMP toggle
    	if (flag3 & prgCplxStack) flag3 &= ~prgCplxStack;
    	else flag3 |= prgCplxStack;
    	break;
    case 38:                                                                   //SYS menu 2 - font
        menu = 40;
        break;
    case 40:                                                                   //fontVW_1
        break;
    case 42:                                                                   //MANDELBROT SET plot program (DOUBLE)
    	mandelbrot6(248);
    	flag2 &= ~CURSORON;
    	scanKp();                                                              //HALT
    	flag2 |= CURSORON;
    	resetVar();
    	fillScreen(BLACK);
    	break;
    case 43:                                                                   //CAA menu 1 - subtraction tables
    	QNO = 0;
    	//fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(280, yCoordStatLTop, 200, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 280;
    	printString("time=");
    	kpPlane = 21;
    	elapsedTime = 0;
    	counter = 1;
    	SysTick->LOAD = 0x0007A120 - 12;                                       //reload value for 1ms (subtract 12 to
    	//compensate for interrupt latency)
    	SysTick->VAL = 0;
    	SysTick->CTRL = 0x07;
    	break;
    }
}

void menuKey2_Main_S(void) {                                                   //MENU KEY 2 SHIFTED
    switch (menu) {
    case 0:                                                                    //Edit program
        if (custMenuFunc[1]) {
            if (custMenuFunc[1] < 101) {                                       //variable

            }
            else {
                if (custMenuFunc[1] < 201) {                                   //program
                    switch (custMenuFunc[1]) {
                    case 101:                                                  //edit KS program 1
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1;
                        break;
                    case 102:                                                  //edit KS program 2
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2;
                        break;
                    case 103:                                                  //edit KS program 3
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3;
                        break;
                    case 104:                                                  //edit KS program 4
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4;
                        break;
                    case 105:                                                  //edit KS program 5
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5;
                        break;
                    case 106:                                                  //edit KS program 6
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6;
                        break;
                    }
                    setForPrgEdit();                                           //set for program editor
                }
                else {                                                         //folder

                }
            }
        }
        break;
    }
}

void menuKey2_Main_H(void) {                                                   //MENU KEY 2 HELD
    if (custMenuFunc[1] > 100) {                                               //debug KS program
        kpPlane = 12; flag2 &= ~CURSORON; prgIndex = 0; cStackIndex = 0;
        menu = 38;                                                             //DEBUG menu
        switch (custMenuFunc[1]) {
        case 101:                                                              //debug KS program 1
            prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1; prgMode = prgMode1;
            break;
        case 102:                                                              //debug KS program 2 etc.
            prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2; prgMode = prgMode2;
            break;
        case 103:
            prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3; prgMode = prgMode3;
            break;
        case 104:
            prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4; prgMode = prgMode4;
            break;
        case 105:
            prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5; prgMode = prgMode5;
            break;
        case 106:
            prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6; prgMode = prgMode6;
            break;
        }
    }
}

void menuKey3_Main(void) {                                                     //MENU KEY 3
    switch (menu) {
    case 0:                                                                    //execute program, push constant or open folder
        if (custMenuFunc[2]) {
            if (custMenuFunc[2] < 101) {                                       //push constant

            }
            else {
                if (custMenuFunc[2] < 201) {                                   //execute program
                    prgIndex = 0; flag2 |= RUN; flag2 &= ~CURSORON; uStackFIndex = 0;
                    reStatL();                                                 //to display "R"
                    switch (custMenuFunc[2]) {
                    case 101:
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
                        break;
                    case 102:
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; prgMode = prgMode2;
                        break;
                    case 103:
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; prgMode = prgMode3;
                        break;
                    case 104:
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; prgMode = prgMode4;
                        break;
                    case 105:
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; prgMode = prgMode5;
                        break;
                    case 106:
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; prgMode = prgMode6;
                        break;
                    }
                    if (prgMode) {
                        cStackIndex = 0;
                        runPrgCplxFast();
                        //push cStackD[cStackIndex] & cStackDIMAG[cStackIndex] onto the user stack
//                        uStackDIndex += 1;
//                        uStackD[uStackDIndex] = cStackD[cStackIndex];
//                        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//                        uStackIndex += 1;
//                        uStackType[uStackIndex] = 0;                           //0 -> type complex scalar
//                        indexLink[uStackIndex] = uStackDIndex;
                    }
                    else runPrgFast();
                    resetVar();
                    //clear portion of LCD not refreshed
                    //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
                    //fillRect(0, yCoordStatLBottom, TFTHEIGHT, yCoordLvl5Top - yCoordStatLBottom, backgroundColour);
                    fillScreen(BLACK);
                    flag2 |= CURSORON;
                }
                else menu = custMenuFunc[2];                                   //open folder
            }
        }
        break;
    case 15:                                                                   //CPLX menu - polar form of Z
        break;
    case 38:                                                                   //SYSTEM menu
        break;
    case 40:                                                                   ////fontVW_2
        break;
    case 43:                                                                   //CAA menu 1 - times tables
    	QNO = 0;
    	//fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(280, yCoordStatLTop, 200, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 280;
    	printString("time=");
    	kpPlane = 22;
    	elapsedTime = 0;
    	counter = 1;
    	SysTick->LOAD = 0x0007A120 - 12;                                       //reload value for 1ms (subtract 12 to
    	//compensate for interrupt latency)
    	SysTick->VAL = 0;
    	SysTick->CTRL = 0x07;
    	break;
    }
}

void menuKey3_Main_S(void) {                                                   //MENU KEY 3 SHIFTED
    switch (menu) {
    case 0:                                                                    //Edit program
        if (custMenuFunc[2]) {
            if (custMenuFunc[2] < 101) {                                       //variable

            }
            else {
                if (custMenuFunc[2] < 201) {                                   //program
                    switch (custMenuFunc[2]) {
                    case 101:                                                  //edit KS program 1
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1;
                        break;
                    case 102:                                                  //edit KS program 2
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2;
                        break;
                    case 103:                                                  //edit KS program 3
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3;
                        break;
                    case 104:                                                  //edit KS program 4
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4;
                        break;
                    case 105:                                                  //edit KS program 5
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5;
                        break;
                    case 106:                                                  //edit KS program 6
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6;
                        break;
                    }
                    setForPrgEdit();                                           //set for program editor
                }
                else {                                                         //folder

                }
            }
        }
        break;
    }
}

void menuKey3_Main_H(void) {                                                   //MENU KEY 3 HELD
    if (custMenuFunc[2] > 100) {                                               //debug KS program
        kpPlane = 12; flag2 &= ~CURSORON; prgIndex = 0; cStackIndex = 0;
        menu = 38;                                                             //DEBUG menu
        switch (custMenuFunc[2]) {
        case 101:                                                              //debug KS program 1
            prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1; prgMode = prgMode1;
            break;
        case 102:                                                              //debug KS program 2 etc.
            prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2; prgMode = prgMode2;
            break;
        case 103:
            prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3; prgMode = prgMode3;
            break;
        case 104:
            prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4; prgMode = prgMode4;
            break;
        case 105:
            prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5; prgMode = prgMode5;
            break;
        case 106:
            prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6; prgMode = prgMode6;
            break;
        }
    }
}

void menuKey4_Main(void) {                                                     //MENU KEY 4
    switch (menu) {
    case 0:                                                                    //execute program, push constant or open folder
        if (custMenuFunc[2]) {
            if (custMenuFunc[2] < 101) {                                       //push constant

            }
            else {
                if (custMenuFunc[2] < 201) {                                   //execute program
                    prgIndex = 0; flag2 |= RUN; flag2 &= ~CURSORON; uStackFIndex = 0;
                    reStatL();                                                 //to display "R"
                    switch (custMenuFunc[2]) {
                    case 101:
                        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; prgMode = prgMode1;
                        break;
                    case 102:
                        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; prgMode = prgMode2;
                        break;
                    case 103:
                        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; prgMode = prgMode3;
                        break;
                    case 104:
                        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; prgMode = prgMode4;
                        break;
                    case 105:
                        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; prgMode = prgMode5;
                        break;
                    case 106:
                        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; prgMode = prgMode6;
                        break;
                    }
                    if (prgMode) {
                        cStackIndex = 0;
                        runPrgCplxFast();
                        //push cStackD[cStackIndex] & cStackDIMAG[cStackIndex] onto the user stack
//                        uStackDIndex += 1;
//                        uStackD[uStackDIndex] = cStackD[cStackIndex];
//                        uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//                        uStackIndex += 1;
//                        uStackType[uStackIndex] = 0;                           //0 -> type complex scalar
//                        indexLink[uStackIndex] = uStackDIndex;
                    }
                    else runPrgFast();
                    resetVar();
                    //clear portion of LCD not refreshed
                    //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
                    //fillRect(0, yCoordStatLBottom, TFTHEIGHT, yCoordLvl5Top - yCoordStatLBottom, backgroundColour);
                    fillScreen(BLACK);
                    flag2 |= CURSORON;
                }
                else menu = custMenuFunc[2];                                   //open folder
            }
        }
        break;
    case 15:                                                                   //CPLX menu - polar form of Z
        break;
    case 38:                                                                   //SYSTEM menu
        break;
    case 40:                                                                   ////fontVW_2
        break;
    case 43:                                                                   //CAA menu 1 - division tables
    	QNO = 0;
    	//fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(280, yCoordStatLTop, 200, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	fillRect(0, yCoordLvl5Top, TFTHEIGHT, yCoordLvl1Bottom - yCoordLvl5Top, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 280;
    	printString("time=");
    	kpPlane = 23;
    	elapsedTime = 0;
    	counter = 1;
    	SysTick->LOAD = 0x0007A120 - 12;                                       //reload value for 1ms (subtract 12 to
    	//compensate for interrupt latency)
    	SysTick->VAL = 0;
    	SysTick->CTRL = 0x07;
    	break;
    }
}

void menuKey5_Main(void) {                                                     //MENU KEY 5

}

void menuKey6_Main(void) {                                                     //MENU KEY 6

}

void SysTick_Handler(void) {
	//SysTick->CTRL = 0x00;
	//SCB->ICSR |= 1<<25;

	counter--;
	if (counter == 0) {
		counter = 999;
		if (flag2 & INTERRUPT) {
			fillRect(400, yCoordStatLTop, 80, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
			yCoordinate = yCoordStatLTop;
			xCoordinate = 404;
			displayPrgStep(elapsedTime);
		}
		elapsedTime++;
	}

	SCB->ICSR |= 1<<25;

	//SysTick->CTRL = 0x07;
}

