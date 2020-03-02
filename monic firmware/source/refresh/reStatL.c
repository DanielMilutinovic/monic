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

#include "clock_config.h"

//structures

//struct tt {
//	char question[5];
//	unsigned int answer;
//};

struct at {
	char question[6];
	char answer[3];
};

struct st {
	char question[6];
	char answer[3];
};

struct tt {
	char question[7];
	char answer[3];
};

struct dt {
	char question[8];
	char answer[3];
};

//variables

extern unsigned int flag1;
extern unsigned int flag2;

extern unsigned char kpPlane;

extern unsigned int prgIndex;

extern int16_t xCoordinate;
extern int16_t yCoordinate;

extern unsigned char cmdL_S[cmdL_SLength];

extern uint32_t fontColour;

extern uint8_t const *fontData;
extern const uint8_t AdafruitClassicData[];
extern uint8_t size;
extern const uint8_t fontVW_1[];

extern struct at atquestions[];
extern struct st stquestions[];
extern struct tt ttquestions[];
extern struct dt dtquestions[];

extern unsigned char QNO;
extern unsigned int elapsedTime;

//functions

void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void printString(char*);
void printStringRight(char*);
void printCharacterFW(char);
void displayPrgStep(unsigned int);
void displayGOTOLabel(unsigned int);
void displayInstruction(unsigned int);
void printASCII(unsigned char);
void drawFastHLine(int16_t, int16_t, int16_t, uint16_t);

///////////////////////////////////////////////////////////////////////////////

void reStatL(void) {

    switch (kpPlane) {
    case 0:                                                                    //main mode
    case 11:                                                                   //store mode
        fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
        fontColour = BLUE;
        drawFastHLine(0, yCoordStatLBottom, max_xCoord, fontColour);

        yCoordinate = yCoordStatLTop;
        xCoordinate = statLfield0;
        if (flag2 & DECIMAL) printString("DEC");
        else {
        	if (flag2 & BINARY) printString("BIN");
            else printString("HEX");
        }

        if (flag1 & SHIFT) {
            xCoordinate = statLfield1;
            printString("SHIFT");
        }

        xCoordinate = statLfield2;
        if (flag2 & DEGREE) printString("DEG");
        else {
        	if (flag2 & RADIAN) printString("RAD");
        	else printString("GRAD");
        }

        if (flag2 & RUN) {
            xCoordinate = statLfield3;
            flag2 &= ~RUN;
            printString("R");
        }

        xCoordinate = max_xCoord;
        if (flag2 & EXACT) printStringRight("=");
        else {
#ifndef FIXED_WIDTH_FONT
        	size = 4;
        	fontData = AdafruitClassicData;
#endif
        	xCoordinate -= 5 * size - 1;
        	printCharacterFW(255);
#ifndef FIXED_WIDTH_FONT
        	font = fontVW_1;
#endif
        }
        break;
    case 5:                                                                    //Keystroke program edit mode
    case 6:                                                                    //C program edit mode
        if (flag1 & SHIFT) {
        	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
            fontColour = BLUE;
            yCoordinate = yCoordStatLTop;
            xCoordinate = statLfield1;
            printString("SHIFT");
            flag2 |= (STACKOFF | COMMANDLINEOFF |MENUOFF);
        }
        break;
    case 12:                                                                   //Keystroke program debug mode
    	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
        fontColour = BLUE;
        yCoordinate =  yCoordStatLTop;
        xCoordinate = 0;
        displayPrgStep(prgIndex+1);
#ifdef FIXED_WIDTH_FONT
        xCoordinate = 3*5*size + GOTOLabelOffsetFW;
#else
        xCoordinate = GOTOLabelOffsetVW;
#endif
        displayGOTOLabel(prgIndex);
        xCoordinate = max_xCoord;
        displayInstruction(prgIndex);
        break;
    case 20:                                                                   //addition tables
    	//SysTick->CTRL = 5;
    	flag2 &= ~INTERRUPT;
    	fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 0;
    	printString(atquestions[QNO].question);
    	//SysTick->CTRL = 7;
    	if (atquestions[QNO].question[0] == 'E') {
    		SysTick->CTRL = 0x00;
    		fillRect(400, yCoordStatLTop, 80, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    		yCoordinate = yCoordStatLTop;
    		xCoordinate = 404;
    		displayPrgStep(elapsedTime);
    	}
    	flag2 |= INTERRUPT;
    	break;
    case 21:                                                                   //subtraction tables
    	//SysTick->CTRL = 5;
    	flag2 &= ~INTERRUPT;
    	fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 0;
    	printString(stquestions[QNO].question);
    	//SysTick->CTRL = 7;
    	if (stquestions[QNO].question[0] == 'E') {
    		SysTick->CTRL = 0x00;
    		fillRect(400, yCoordStatLTop, 80, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    		yCoordinate = yCoordStatLTop;
    		xCoordinate = 404;
    		displayPrgStep(elapsedTime);
    	}
    	flag2 |= INTERRUPT;
    	break;
    case 22:                                                                   //times tables
    	//SysTick->CTRL = 5;
    	flag2 &= ~INTERRUPT;
    	fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 0;
    	printString(ttquestions[QNO].question);
    	//SysTick->CTRL = 7;
    	if (ttquestions[QNO].question[0] == 'E') {
    		SysTick->CTRL = 0x00;
    		fillRect(400, yCoordStatLTop, 80, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    		yCoordinate = yCoordStatLTop;
    		xCoordinate = 404;
    		displayPrgStep(elapsedTime);
    	}
    	flag2 |= INTERRUPT;
    	break;
    case 23:                                                                   //division tables
    	//SysTick->CTRL = 5;
    	flag2 &= ~INTERRUPT;
    	fillRect(0, yCoordStatLTop, 280, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 0;
    	printString(dtquestions[QNO].question);
    	//SysTick->CTRL = 7;
    	if (dtquestions[QNO].question[0] == 'E') {
    		SysTick->CTRL = 0x00;
    		fillRect(400, yCoordStatLTop, 80, yCoordStatLBottom - yCoordStatLTop, backgroundColour);
    		yCoordinate = yCoordStatLTop;
    		xCoordinate = 404;
    		displayPrgStep(elapsedTime);
    	}
    	flag2 |= INTERRUPT;
    	break;
    default:
    	__asm volatile ("nop");
    }
}
