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

//Keystroke programming editor

//includes

#include "../user.h"

#include <math.h>

#include "pin_mux.h"
#include "board.h"

#include <stdint.h>
#include <stdbool.h>

//variables

extern unsigned int flag1;
extern unsigned int flag2;
extern unsigned int flag3;

extern unsigned int prgIndex;
extern unsigned int *prg;

extern unsigned char menu;

extern unsigned char kpPlane;

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern double *prgConstants;
extern float *prgConstantsF;

extern unsigned char sigLength;                                                //significand length (no. of digits)
extern unsigned char expLength;                                                //exponent length (no. of digits)

extern double valueCmdL_SigD;                                                  //command line significand value
extern double valueCmdL_ExpD;                                                  //command line exponent value
extern double valueCmdL_D;                                                     //command line value
extern double decDigits;

extern float valueCmdL_SigF;
extern float valueCmdL_ExpF;
extern float valueCmdL_F;
extern float decDigitsF;

extern unsigned int *labelAddress;

extern unsigned char varListCtr;
extern unsigned char (*varList)[varListStringLength];

extern unsigned char annunciator;

extern uint32_t fontColour;
extern int16_t xCoordinate;
extern int16_t yCoordinate;
extern uint8_t size;

//functions

void menuKey1_KSPrg(void);
void menuKey2_KSPrg(void);
void menuKey3_KSPrg(void);
void menuKey4_KSPrg(void);
void menuKey5_KSPrg(void);
void menuKey6_KSPrg(void);

void menuKey1Held_KSPrg(void);
void menuKey2Held_KSPrg(void);
void menuKey3Held_KSPrg(void);

void resetVar(void);

void updateValueCmdL_SigD(double);
void updateValueCmdL_ExpD(double);

void updateValueCmdL_SigF(float);
void updateValueCmdL_ExpF(float);

void enterDPrgEdit(void);
//void enterFPrgEdit(void);

void storeVarPrgEdit(void);
void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);

void displayPrgStep(unsigned int);
void displayGOTOLabel(unsigned int);
void deleteGOTOLabel(void);
void displayInstruction(unsigned int);

void annunFunc(unsigned int);

//constants
                                  //{0,1,2,3,4,5,6,7,8,9, 10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29}
const unsigned char nextPrgMenu[] = {1,2,3,0,5,6,4,7,8,10,22,12,11,14,13,16,15,18,19,20,17,24,23, 9,21,26,25,28,27,29};

                               //{0, 1, 2, 3, 4, 5,6, 7, 8, 9, 10,11}              //{18,19,20,21,22,23,24,25,26,27,28,29}
const unsigned int keyOffset[] = {25,24,23,22,21,0,20,19,18,17,16,0,15,14,13,12,11,0,10, 9, 8, 7, 6, 0, 5, 4, 3, 2, 1, 0};
                                                                 //{12,13,14,15,16,17}

///////////////////////////////////////////////////////////////////////////////

void kpKSPrg(unsigned int x) {
    unsigned int i;
    unsigned char j;

    switch (x) {
    case A_SINKSPrg:                                                           //LABEL A/SIN
        if (annunciator) annunFunc(x);                                         //LABEL A
        else {                                                                 //SIN
        	prg[prgIndex] = A_SINKSPrg;
        	prgIndex += 1;
        }
        flag2 |= MENUOFF;
        break;
    case B_COSKSPrg:                                                           //LABEL B/COS
        if (annunciator) annunFunc(x);                                         //LABEL B
        else {                                                                 //COS
        	prg[prgIndex] = B_COSKSPrg;
        	prgIndex += 1;
        }
        flag2 |= MENUOFF;
        break;
    case C_TANKSPrg:                                                           //LABEL C/TAN
        if (annunciator) annunFunc(x);                                         //LABEL C
        else {                                                                 //TAN
        	prg[prgIndex] = C_TANKSPrg;
        	prgIndex += 1;
        }
        flag2 |= MENUOFF;
        break;
    case D_ToDMSKSPrg:                                                         //LABEL D/ToDMS
        if (annunciator) annunFunc(x);                                         //LABEL D
        else {

        }
        flag2 |= MENUOFF;
        break;
    case E_PIKSPrg:                                                            //LABEL E/Pi
        if (annunciator) annunFunc(x);                                         //LABEL E
        else {                                                                 //Pi
        	prg[prgIndex] = E_PIKSPrg;
        	prgIndex += 1;
        }
        flag2 |= MENUOFF;
        break;
    case F_KSPrg:                                                              //LABEL F/
        if (annunciator) annunFunc(x);                                         //LABEL F
        else {

        }
        flag2 |= MENUOFF;
        break;
    case arcSinKSPrg:                                                          //ASIN
    	prg[prgIndex] = arcSinKSPrg;
    	prgIndex ++;
    	break;
    case arcCosKSPrg:                                                          //ACOS
    	prg[prgIndex] = arcCosKSPrg;
    	prgIndex ++;
    	break;
    case arcTanKSPrg:                                                          //ATAN
    	prg[prgIndex] = arcTanKSPrg;
    	prgIndex ++;
    	break;
    case cubeRootKSPrg:                                                        //cube root
    	prg[prgIndex] = cubeRootKSPrg;
    	prgIndex ++;
    	break;
    case rootKSPrg:                                                            //root
    	prg[prgIndex] = rootKSPrg;
    	prgIndex ++;
    	break;
    case equalKSPrg:                                                           //EQUAL
        if (sigLength) {                                                       //if the command line is not empty in program edit mode
            enterDPrgEdit();                                                   //store command line value in prgConstants and opcode in prg
            cmdL_Term = 0;
            for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;
            flag2 &= ~CURSORON;
        }
        else {
            prg[prgIndex] = equalKSPrg;                                        //PUSH COMMAND LINE program instruction
            prgIndex += 1;
        }
        break;
    case deleteKSPrg:                                                          //DELETE
        if (sigLength) {                                                       //delete character on command line if it is non-empty
            cmdL_Term -= 1;
            if ((cmdL_S[cmdL_Term] >= 48) && (cmdL_S[cmdL_Term] <= 57)) {      //if 0-9 digit
                if (flag1 & EXP) {
                    valueCmdL_ExpD = floor(valueCmdL_ExpD/10.0);
                    expLength -= 1;
                }
                else {
                    valueCmdL_SigD = floor(valueCmdL_SigD/10.0);
                    sigLength -= 1;
                    if (flag1 & DECPOINT) decDigits -= 1.0;
                }
            }
            else {
                if (cmdL_S[cmdL_Term] == 46) {                                 //decimal point
                    flag1 &= ~DECPOINT;
                    decDigits = 0.0;
                }
                if (cmdL_S[cmdL_Term] == 11) {                                 //"0."
                    flag1 &= ~DECPOINT;
                    decDigits = 0.0;
                    sigLength = 0;
                }
                if (cmdL_S[cmdL_Term] == 12) {                                 //exponent entry field
                    flag1 &= ~EXP;
                    flag1 &= ~NEGEXP;
                }
            }
            cmdL_S[cmdL_Term] = 0x00;
        }
        else {
            prg[prgIndex] = deleteKSPrg;
            prgIndex += 1;
        }
        flag2 |= MENUOFF;
        break;
//    case deletelineKSPrg:                                                      //DELETE program line
//        for (k = prgIndex; k < numberOfPrgSteps-1;k++) prg[k] = prg[k+1];
//        prg[numberOfPrgSteps-1] = NOP;
//        for (j = 0; j < 26; j++) {                                             //decrement program steps of labels
//            if ((labelAddress[j] != 0xFFFFFFFE) && (labelAddress[j] >= prgIndex)) labelAddress[j] -= 1;
//            if (labelAddress[j] == prgIndex - 1) labelAddress[j] = 0xFFFFFFFE;
//        }
//        flag2 |= MENUOFF;
//        break;
//    case insertKSPrg:                                                          //INSERT program line
//        for (k = numberOfPrgSteps-1; k > prgIndex; k--) prg[k] = prg[k-1];
//        prg[prgIndex] = NOP;
//        for (j = 0; j < 26; j++) {                                             //increment program steps of labels
//            if ((labelAddress[j] != 0xFFFFFFFE) && (labelAddress[j] >= prgIndex - 1)) labelAddress[j] += 1;
//        }
//        flag2 |= MENUOFF;
//        break;
    case eraseKSPrg:                                                           //NOP program instruction (delete the previous command)
        if (prgIndex) {
            prgIndex -= 1;
            prg[prgIndex] = NOP;
        }
        flag2 |= MENUOFF;
        break;
    case zeroKSPrg:                                                            //ZERO
        if (flag1 & EXP) {                                                     //if in exponent entry field
            cmdL_S[cmdL_Term] = 48;
            cmdL_Term += 1;
            updateValueCmdL_ExpD(0.0);
        }
        else {
            if ((flag1 & ZEROFIRST) == 0) {
                cmdL_S[cmdL_Term] = 48;
                cmdL_Term += 1;
                updateValueCmdL_SigD(0.0);
            }
            if (sigLength == 0) flag1 |= ZEROFIRST;
        }
        //flag2 |= CMDLINEPRGEDIT;
        flag2 |= CURSORON;
        flag2 |= MENUOFF;
        //flag2 |= STACKOFF;
        break;
    case oneKSPrg:                                                             //ONE/Q
        if (annunciator) annunFunc(x);                                         //LABEL Q
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 49;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(1.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 49;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(1.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case twoKSPrg:                                                             //TWO/R
        if (annunciator) annunFunc(x);                                         //LABEL R
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 50;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(2.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 50;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(2.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case threeKSPrg:                                                           //THREE/S
        if (annunciator) annunFunc(x);                                         //LABEL S
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 51;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(3.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 51;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(3.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case fourKSPrg:                                                            //FOUR/L
        if (annunciator) annunFunc(x);                                         //LABEL L
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 52;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(4.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 52;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(4.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case fiveKSPrg:                                                            //FIVE/M
        if (annunciator) annunFunc(x);                                         //LABEL M
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 53;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(5.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 53;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(5.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case sixKSPrg:                                                             //SIX/N
        if (annunciator) annunFunc(x);                                         //LABEL N
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 54;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(6.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 54;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(6.0);
                }
            }
            flag2 |= CURSORON;
            flag2 |= MENUOFF;
        }
        break;
    case sevenKSPrg:                                                           //LABEL G/SEVEN
        if (annunciator) annunFunc(x);                                         //LABEL G
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 55;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(7.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 55;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(7.0);
                }
            }
            flag2 |= CURSORON;
        }
        flag2 |= MENUOFF;
        break;
    case eightKSPrg:                                                           //LABEL H/EIGHT
        if (annunciator) annunFunc(x);                                         //LABEL H
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 56;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(8.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 56;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(8.0);
                }
            }
            flag2 |= CURSORON;
        }
        flag2 |= MENUOFF;
        break;
    case nineKSPrg:                                                            //LABEL I/NINE
        if (annunciator) annunFunc(x);                                         //LABEL I
        else {
            if (flag1 & EXP) {
                cmdL_S[cmdL_Term] = 57;
                cmdL_Term += 1;
                updateValueCmdL_ExpD(9.0);
            }
            else {
                if ((flag1 & ZEROFIRST) == 0) {
                    cmdL_S[cmdL_Term] = 57;
                    cmdL_Term += 1;
                    updateValueCmdL_SigD(9.0);
                }
            }
            flag2 |= CURSORON;
        }
        flag2 |= MENUOFF;
        break;
    case jKSPrg:                                                               //LABELJ/CAN ADD FUNCTION!!!!!!!!!!
        if (annunciator) annunFunc(x);                                         //LABEL J
        else {

        }
        break;
    case kKSPrg:                                                               //LABEL K/CAN ADD FUNCTION!!!!!!!!!!
        if (annunciator) annunFunc(x);                                         //LABEL K
        else {

        }
        break;
    case decimalPointKSPrg:                                                    //DECIMAL POINT
        if (sigLength) {
            if ((flag1 & DECPOINT) == 0) {
                flag1 |= DECPOINT;
                cmdL_S[cmdL_Term] = 46;
                cmdL_Term += 1;
            }
        }
        else {
            sigLength = 1;
            flag1 |= DECPOINT;
            cmdL_S[cmdL_Term] = 11;
            cmdL_Term += 1;
        }
        flag1 &= ~ZEROFIRST;
        flag2 |= CURSORON;
        flag2 |= MENUOFF;
        break;
    case negateKSPrg:                                                          //NEGATE
        if (flag1 & EXP) {                                                     //if in exponent entry field
            if (flag1 & NEGEXP) flag1 &= ~NEGEXP;
            else flag1|= NEGEXP;
        }
        else {
            if (sigLength) {                                                   //if command line not empty
                if (flag1 & NEGSIG) flag1 &= ~NEGSIG;
                else flag1|= NEGSIG;
            }
            else {                                                             //if command line empty then +/- instruction
                prg[prgIndex] = negateKSPrg;                                   // +/-
                prgIndex += 1;
            }
        }
        flag2 |= MENUOFF;
        break;
    case addKSPrg:                                                             //ADD
        prg[prgIndex] = addKSPrg;                                              //double addition
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case subtractKSPrg:                                                        //SUBTRACT
        prg[prgIndex] = subtractKSPrg;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case multiplyKSPrg:                                                        //MULTIPLY/O
        if (annunciator) annunFunc(x);                                         //LABEL O
        else {
            prg[prgIndex] = multiplyKSPrg;
            prgIndex += 1;
            flag2 |= MENUOFF;
        }
        break;
    case divideKSPrg:                                                          //DIVIDE/P
        if (annunciator) annunFunc(x);                                         //LABEL P
        else {
            prg[prgIndex] = divideKSPrg;
            prgIndex += 1;
            flag2 |= MENUOFF;
        }
        break;
    case reciprocalKSPrg:                                                      //1/x
        prg[prgIndex] = reciprocalKSPrg;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case powerKSPrg:                                                           //x^y
        prg[prgIndex] = powerKSPrg;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case squareKSPrg:                                                          //SQUARE
        prg[prgIndex] = squareKSPrg;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case sqrtKSPrg:                                                            //SQUARE ROOT
    	prg[prgIndex] = sqrtKSPrg;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case eulerPowerKSPrg:                                                      //e^x
    	prg[prgIndex] = eulerPowerKSPrg;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case tenPowerKSPrg:                                                        //10^x
    	prg[prgIndex] = tenPowerKSPrg;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case logTenKSPrg:                                                          //log(x)
    	prg[prgIndex] = logTenKSPrg;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case lnKSPrg:                                                              //ln(x)
    	prg[prgIndex] = lnKSPrg;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case shiftKSPrg:                                                           //SHIFT
        flag1 |= SHIFT;
        flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case shiftshiftKSPrg:                                                      //toggle SHIFT
        flag2 |= MENUOFF;
        break;
    case stackKSPrg:                                                           //STACK menu
        menu = 9;
        break;
    case graphKSPrg:                                                           //GRAPH menu
        menu = 8;
        break;
    case systemKSPrg:                                                          //SYSTEM menu
    	menu = 25;
    	break;
    case stoKSPrg:                                                             //STO
        kpPlane = 16;
        menu = 0;
        flag2 |= CURSORON;
        annunciator = 2;
        break;
    case exitKSPrg:                                                            //EXIT
        switch (menu) {
        case 0:
        case 1:
        case 2:                                                                //exit Keystroke program edit mode
            if (flag3 & newProgram) kpPlane = 11; else kpPlane = 0;
            menu = 0;
            flag2 |= CURSORON;
            resetVar();
            break;
        default:
            menu = 0;                                                          //return to Keystroke program edit home menu
        }
        break;
    case nextKSPrg:                                                            //NEXT
        menu = nextPrgMenu[menu];
        flag2 |= (STATUSLINEOFF | STACKOFF | COMMANDLINEOFF);
        break;
    case upKSPrg:                                                              //UP
        if (prgIndex) prgIndex -= 1;
        flag2 |= MENUOFF;
        break;
    case heldupKSPrg:                                                          //UP(held)
    	while (GPIO_PinRead(BOARD_DATA_56_04_PERIPHERAL, BOARD_DATA_56_04_CHANNEL) == 0) {
    		if (prgIndex > 9) prgIndex -= 10;
    		fillRect(0, yCoordStatLTop, max_xCoord, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
    		i = prgIndex / 7 * 7;
    		yCoordinate = yCoordStatLTop;
    		for (j = 0; j < 7; j++) {
    			if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
    			xCoordinate = 0;
    			displayPrgStep(i+1);
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
    case shiftheldupKSPrg:                                                     //UP(shift, held)
    	while (GPIO_PinRead(BOARD_DATA_56_04_PERIPHERAL, BOARD_DATA_56_04_CHANNEL) == 0) {
            if (prgIndex > 99) prgIndex -= 100;
            fillRect(0, yCoordStatLTop, max_xCoord, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
            i = prgIndex / 7 * 7;
            yCoordinate = yCoordStatLTop;
            for (j = 0; j < 7; j++) {
                if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
                xCoordinate = 0;
                displayPrgStep(i+1);
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
    case downKSPrg:                                                            //DOWN
        if (prgIndex < numberOfPrgSteps-1) prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case helddownKSPrg:                                                        //DOWN(held)
    	while (GPIO_PinRead(BOARD_DATA_56_04_PERIPHERAL, BOARD_DATA_56_04_CHANNEL) == 0) {
            if (prgIndex < numberOfPrgSteps - 10) prgIndex += 10;
            fillRect(0, yCoordStatLTop, max_xCoord, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
            i = prgIndex / 7 * 7;
            yCoordinate = yCoordStatLTop;
            for (j = 0; j < 7; j++) {
                if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
                xCoordinate = 0;
                displayPrgStep(i+1);
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
    case shifthelddownKSPrg:                                                   //DOWN(shift, held)
    	while (GPIO_PinRead(BOARD_DATA_56_04_PERIPHERAL, BOARD_DATA_56_04_CHANNEL) == 0) {
            if (prgIndex < numberOfPrgSteps - 100) prgIndex += 100;
            fillRect(0, yCoordStatLTop, max_xCoord, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
            i = prgIndex / 7 * 7;
            yCoordinate = yCoordStatLTop;
            for (j = 0; j < 7; j++) {
                if (i == prgIndex) fontColour = RED; else fontColour = BLUE;
                xCoordinate = 0;
                displayPrgStep(i+1);
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
    case menuKey1KSPrg:                                                        //MENU KEY 1
        menuKey1_KSPrg();
        break;
    case menuKey1HeldKSPrg:                                                    //MENU KEY 1 held
        menuKey1Held_KSPrg();
        break;
    case menuKey2KSPrg:                                                        //MENU KEY 2
        menuKey2_KSPrg();
        break;
    case menuKey2HeldKSPrg:                                                    //MENU KEY 2 held
    	menuKey2Held_KSPrg();
    	break;
    case menuKey3KSPrg:                                                        //MENU KEY 3
        menuKey3_KSPrg();
        break;
    case menuKey3HeldKSPrg:                                                    //MENU KEY 3 held
    	menuKey3Held_KSPrg();
    	break;
    case menuKey4KSPrg:                                                        //MENU KEY 4
        menuKey4_KSPrg();
        break;
    case menuKey5KSPrg:                                                        //MENU KEY 5
        menuKey5_KSPrg();
        break;
    case menuKey6KSPrg:                                                        //MENU KEY 6
        menuKey6_KSPrg();
        break;
    case swapKSPrg:                                                            //SWAP
        prg[prgIndex] = swapKSPrg;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    default:
        flag2 |= (STATUSLINEOFF | STACKOFF | COMMANDLINEOFF | MENUOFF);        //do not update status line, stack, command line or menu
    }
}

void menuKey1_KSPrg(void) {                                                    //MENU KEY 1
    switch (menu) {
    case 0:                                                                    //PUSH VARIABLE (RECALL)
        annunciator = 3;
        flag2 |= CURSORON;
        kpPlane = 15;                                                          //kpKSPrgVar
        menu = 0;                                                              //program variable menu
        break;
    case 1:                                                                    //INCREMENT variable
        annunciator = 4;
        kpPlane = 15;
        menu = 0;                                                              //program variable menu
        //flag2 |= CMDLINEPRGEDIT;
        flag2 |= CURSORON;
        break;
    case 2:                                                                    //MENU menu
        kpPlane = 13;
        menu = 0;                                                              //custom menu 0
        break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4000;
//        prgIndex += 1;
        break;
    case 4:                                                                    //BRANCH MENU - LABEL
        if (annunciator == 1) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 1;
            flag2 |= CURSORON;
        }
        //flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case 5:                                                                    //BRANCH MENU - GOTOIF>
        if (annunciator == 11) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 11;
            flag2 |= CURSORON;
        }
        //flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case 8:                                                                    //GRAPH menu - CLEAR DISPLAY
        prg[prgIndex] = 3000;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 9:                                                                    //STACK menu 1 - DUPLICATE
        prg[prgIndex] = 166;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 21:                                                                   //COLOUR menu - BLUE
        prg[prgIndex] = 185;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 1 onto complex stack
        prg[prgIndex] = 172;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 1 onto user stack
        prg[prgIndex] = 178;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - GREEN
        prg[prgIndex] = 191;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 25:                                                                   //SYSTEM/PIN menu
    	menu = 27;
    	break;
    case 27:                                                                   //PIN HIGH
    	prg[prgIndex] = 420;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case 29:                                                                   //DELAY menu - 20ms delay
    	prg[prgIndex] = 400;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void menuKey1Held_KSPrg(void) {                                                //MENU KEY 1 held
    switch (menu) {
    case 4:                                                                    //delete LABEL
        deleteGOTOLabel();
        break;
    }
}

void menuKey2Held_KSPrg(void) {                                                //MENU KEY 2 held
	unsigned char j;
	unsigned int k;

	for (k = numberOfPrgSteps-1; k > prgIndex; k--) prg[k] = prg[k-1];
	prg[prgIndex] = NOP;
	for (j = 0; j < 26; j++) {                                                 //increment program steps of labels
		if ((labelAddress[j] != 0xFFFFFFFE) && (labelAddress[j] >= prgIndex - 1)) labelAddress[j] += 1;
	}
	flag2 |= MENUOFF;
}

void menuKey3Held_KSPrg(void) {                                                //MENU KEY 3 held
	unsigned char j;
    unsigned int k;

	for (k = prgIndex; k < numberOfPrgSteps-1;k++) prg[k] = prg[k+1];
	prg[numberOfPrgSteps-1] = NOP;
	for (j = 0; j < 26; j++) {                                                 //decrement program steps of labels
		if ((labelAddress[j] != 0xFFFFFFFE) && (labelAddress[j] >= prgIndex)) labelAddress[j] -= 1;
		if (labelAddress[j] == prgIndex - 1) labelAddress[j] = 0xFFFFFFFE;
	}
	flag2 |= MENUOFF;
}

void menuKey2_KSPrg(void) {                                                    //MENU KEY 2
    switch (menu) {
    case 0:                                                                    //BRANCH MENU
        menu = 4;
        break;
    case 1:                                                                    //DECREMENT variable
        annunciator = 5;
        kpPlane = 15;
        menu = 0;                                                              //program variable menu
        flag2 |= CURSORON;
        break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4001;
//        prgIndex += 1;
        break;
    case 4:                                                                    //BRANCH menu - GOTO
        if (annunciator == 6) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 6;
            flag2 |= CURSORON;
        }
        //flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case 5:                                                                    //BRANCH MENU - GOTOIF<
        if (annunciator == 10) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 10;
            flag2 |= CURSORON;
        }
        //flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case 8:                                                                    //GRAPH menu - PIXEL ON
        prg[prgIndex] = 3001;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 9:                                                                    //STACK menu - ROTATE
        prg[prgIndex] = 162;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 10:                                                                   //STACK menu - DROP 2
        prg[prgIndex] = 163;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 21:                                                                   //COLOUR menu - RED
        prg[prgIndex] = 186;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 2 onto complex stack
        prg[prgIndex] = 173;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 2 onto user stack
        prg[prgIndex] = 179;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - BROWN
        prg[prgIndex] = 192;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 27:                                                                   //PIN LOW
    	prg[prgIndex] = 421;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case 29:                                                                   //DELAY menu - 100ms delay
    	prg[prgIndex] = 401;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void menuKey3_KSPrg(void) {                                                    //MENU KEY 3
    switch (menu) {
    case 0:                                                                    //INSTR/OPCODE toggle
        if (flag2 & OPCODE) flag2 &= ~OPCODE;
        else flag2 |= OPCODE;
        break;
    case 1:                                                                    //DELAY menu
    	menu = 29;
    	break;
    case 4:                                                                    //BRANCH menu - GOTOIF=0
    	if (annunciator == 7) {
    		annunciator = 0;
    		flag2 &= ~CURSORON;
    	}
    	else {
    		annunciator = 7;
    		flag2 |= CURSORON;
    	}
    	flag2 |= MENUOFF;
    	break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4002;
//        prgIndex += 1;
        break;
    case 8:                                                                    //GRAPH menu - LINE
    	prg[prgIndex] = 3002;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    case 9:                                                                    //STACK menu - UNROTATE
        prg[prgIndex] = 164;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 21:                                                                   //COLOUR menu - YELLOW
        prg[prgIndex] = 187;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 3 onto complex stack
        prg[prgIndex] = 174;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 3 onto user stack
        prg[prgIndex] = 180;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - WHITE
        prg[prgIndex] = 193;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 29:                                                                   //DELAY menu - 500ms delay
    	prg[prgIndex] = 402;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void menuKey4_KSPrg(void) {                                                    //MENU KEY 4
    switch (menu) {
    case 0:                                                                    //NOP program instruction (delete the previous command)
    	if (prgIndex) {
    		prgIndex -= 1;
    		prg[prgIndex] = 184;
    	}
    	flag2 |= MENUOFF;
    	break;
    case 1:                                                                    //HALT
        prg[prgIndex] = 952;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4003;
//        prgIndex += 1;
        break;
    case 4:                                                                    //BRANCH menu - GOTOIF!=0
        if (annunciator == 8) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 8;
            flag2 |= CURSORON;
        }
        flag2 |= MENUOFF;
        break;
    case 21:                                                                   //COLOUR menu - MEDIUM ORCHID
        prg[prgIndex] = 188;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 4 onto complex stack
        prg[prgIndex] = 175;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 4 onto user stack
        prg[prgIndex] = 181;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - ORANGE
        prg[prgIndex] = 194;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 29:                                                                   //DELAY menu - 1 sec delay
    	prg[prgIndex] = 403;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void menuKey5_KSPrg(void) {                                                    //MENU KEY 5
    switch (menu) {
    case 0:
        break;
    case 1:                                                                    //scan keypad program instruction
    	break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4004;
//        prgIndex += 1;
        break;
    case 4:                                                                    //BRANCH menu - GOTOIF=
        if (annunciator == 12) {
            annunciator = 0;
            flag2 &= ~CURSORON;
        }
        else {
            annunciator = 12;
            flag2 |= CURSORON;
        }
        //flag2 |= STACKOFF;
        flag2 |= MENUOFF;
        break;
    case 8:                                                                    //GRAPH -> COLOUR MENU
        menu = 21;
        break;
    case 21:                                                                   //COLOUR menu - BLACK
        prg[prgIndex] = 189;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 5 onto complex stack
        prg[prgIndex] = 176;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 5 onto user stack
        prg[prgIndex] = 182;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - PINK
        prg[prgIndex] = 195;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 29:                                                                   //DELAY menu - 2 sec delay
    	prg[prgIndex] = 404;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void menuKey6_KSPrg(void) {                                                    //MENU KEY 6
    switch (menu) {
    case 0:                                                                    //insert END program instruction
        prg[prgIndex] = END;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 3:                                                                    //TEST
//        prg[prgIndex] = 4005;
//        prgIndex += 1;
        break;
    case 21:                                                                   //COLOUR menu - AQUA
        prg[prgIndex] = 190;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 22:                                                                   //STACK menu 3 - push user stack level 6 onto complex stack
        prg[prgIndex] = 177;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 23:                                                                   //STACK menu 4 - push complex stack level 6 onto user stack
        prg[prgIndex] = 183;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 24:                                                                   //COLOUR menu - INDIGO
        prg[prgIndex] = 196;
        prgIndex += 1;
        flag2 |= MENUOFF;
        break;
    case 29:                                                                   //DELAY menu - delay in ms
    	prg[prgIndex] = 405;
    	prgIndex += 1;
    	flag2 |= MENUOFF;
    	break;
    }
}

void enterDPrgEdit(void) {
    unsigned int j;

    for (j = 0; j < prgConstantsLength; j++) {
        if (prgConstants[j] == HUGE_VAL) break;
    }

    if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
    valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
    if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
    prgConstants[j] = valueCmdL_D;

    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
    sigLength = 0;
    expLength = 0;
    valueCmdL_SigD = 0.0;
    valueCmdL_ExpD = 0.0;
    decDigits = 0.0;

    prg[prgIndex] = 150000 + j;
    prgIndex += 1;
}

//void enterFPrgEdit(void) {
//    unsigned int j;
//
//    for (j = 0; j < prgConstantsLength; j++) {
//        if (prgConstantsF[j] == HUGE_VALF) break;
//    }
//
//    if (flag1 & NEGEXP) valueCmdL_ExpF = -valueCmdL_ExpF;
//    valueCmdL_F = valueCmdL_SigF * powf(10.0f,valueCmdL_ExpF - decDigitsF);
//    if (flag1 & NEGSIG) valueCmdL_F = -valueCmdL_F;
//    prgConstantsF[j] = valueCmdL_F;
//
//    flag1 = 0;                                                                 //reset ready for next value to be entered on command line
//    sigLength = 0;
//    expLength = 0;
//    valueCmdL_SigF = 0.0f;
//    valueCmdL_ExpF = 0.0f;
//    decDigitsF = 0.0f;
//
//    prg[prgIndex] = 160000 + j;
//    prgIndex += 1;
//}

void storeVarPrgEdit(void) {
    unsigned char row;
    unsigned char i;
    unsigned char noMatch = true;

    for (row = 0; row < varListCtr; row++) {
        for (i = 0; i < 6; i++) {
            if (cmdL_S[i] != varList[row][i]) break;                           //if not the same compare to next variable in varList
        }
        if (i == 6) {
            noMatch = false;
            break;                                                             //exit if variable found
        }
    }
    if (noMatch) {
        for (i = 0; i < 6; i++) varList[row][i] = cmdL_S[i];                   //var is a new variable so add to list
        varListCtr += 1;
    }

    prg[prgIndex] = 190000 + row;
}

void deleteGOTOLabel(void) {
    unsigned char i;
    for (i = 0; i < labelAddressLength; i++) {
        if ((labelAddress[i] + 1) == prgIndex) break;
    }
    if (i != labelAddressLength) {
        labelAddress[i] = 0xFFFFFFFE;
    }
}

void annunFunc(unsigned int x) {
    switch (annunciator) {
    case 1:                                                            //if LABEL previous key pressed
        labelAddress[keyOffset[x]] = prgIndex - 1;
        break;
    case 6:                                                            //if GOTO previous key pressed
        prg[prgIndex] = 30000 + keyOffset[x];
        prgIndex += 1;
        break;
    case 7:                                                            //if GOTOIF=0 previous key pressed
    	prg[prgIndex] = 40000 + keyOffset[x];
    	prgIndex += 1;
        break;
    case 8:                                                            //if GOTOIF!=0 previous key pressed
        prg[prgIndex] = 50000 + keyOffset[x];
        prgIndex += 1;
        break;
    case 9:                                                            //if GOTOIF<= previous key pressed
        break;
    case 10:                                                           //if GOTOIF< previous key pressed
        prg[prgIndex] = 90000 + keyOffset[x];
        prgIndex += 1;
        break;
    case 11:                                                           //if GOTOIF> previous key pressed
        prg[prgIndex] = 80000 + keyOffset[x];
        prgIndex += 1;
        break;
    case 12:                                                           //if GOTOIF= previous key pressed
        prg[prgIndex] = 60000 + keyOffset[x];
        prgIndex += 1;
        break;
    }
    annunciator = 0;
    flag2 &= ~CURSORON;
}
