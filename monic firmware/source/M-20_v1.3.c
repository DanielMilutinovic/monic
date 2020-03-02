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
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MIMXRT1011.h"
#include "fsl_debug_console.h"
#include <stdint.h>
#include "user.h"

//variables

unsigned int keyNumber;                                                        //number of the key pressed
unsigned char kpPlane = 0;
unsigned int flag1 = 0;
unsigned int flag2 = 0x10001210;                                               //ALGENTRY, DECIMAL, DEGREE, APPROX modes, CURSORON
unsigned int flag3 = 0x00000008;                                               //prgCplxStack mode

char cmdL_S[cmdL_SLength];
unsigned char cmdL_Term = 0;

unsigned char keyHeldCtr = 0;

int32_t xCoordinate = 0;
int32_t yCoordinate;

int32_t cursorPageTop = yCoordCmdLTop;
int32_t cursorPageBottom = yCoordCmdLBottom;

unsigned int uStackIndex = 0;                                                  //user stack level index
unsigned char uStackType[stackDDepth];                                         //0 -> complex, 1 -> matrix

unsigned int uStackDIndex;                                                     //complex user stack index
double uStackD[stackDDepth];                                                   //array to store real part
double uStackDIMAG[stackDDepth];                                               //array to store imaginary part

unsigned int indexLink[stackDDepth];

unsigned char uStackMDim[stackDDepth][2];                                      //array to store matrix dimensions

unsigned int cStackIndex;                                                      //complex user stack index
double cStackD[stackDDepth];                                                   //array to store real part on complex stack
double cStackDIMAG[stackDDepth];                                               //array to store imaginary part on complex stack

unsigned int uStackFIndex;                                                     //float user stack index

unsigned int screenNumber = 0;

unsigned int matrixRow = 0;
unsigned int matrixColumn = 0;

unsigned char menu = 0;

char custMenuLbl[custMenuLength][6];
unsigned int custMenuFunc[custMenuLength];

unsigned char memAlloc[memAllocLength];
unsigned int memAllocCtr;

unsigned int prgIndex;
unsigned int *prg;
unsigned int prg1[numberOfPrgSteps];
unsigned int prg2[numberOfPrgSteps];
unsigned int prg3[numberOfPrgSteps];
unsigned int prg4[numberOfPrgSteps];
unsigned int prg5[numberOfPrgSteps];
unsigned int prg6[numberOfPrgSteps];

unsigned int CprgIndex;
unsigned int *Cprg;
unsigned int Cprg1[numberOfCPrgChars];

double prgConstants1[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF1[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

double prgConstants2[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF2[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

double prgConstants3[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF3[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

double prgConstants4[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF4[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

double prgConstants5[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF5[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)

double prgConstants6[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution

float prgConstantsF6[prgConstantsLength];                                                //array to store values pushed onto the stack during program
                                                                                         //execution (float)
double *prgConstants;
float *prgConstantsF;

unsigned int *labelAddress;
unsigned int labelAddress1[labelAddressLength];                                          //array to store program counter values corresponding to labels
unsigned int labelAddress2[labelAddressLength];                                          //array to store program counter values corresponding to labels
unsigned int labelAddress3[labelAddressLength];                                          //array to store program counter values corresponding to labels
unsigned int labelAddress4[labelAddressLength];                                          //array to store program counter values corresponding to labels
unsigned int labelAddress5[labelAddressLength];                                          //array to store program counter values corresponding to labels
unsigned int labelAddress6[labelAddressLength];                                          //array to store program counter values corresponding to labels

char (*varList)[varListStringLength];
char varList1[varListLength][varListStringLength];
char varList2[varListLength][varListStringLength];
char varList3[varListLength][varListStringLength];
char varList4[varListLength][varListStringLength];
char varList5[varListLength][varListStringLength];
char varList6[varListLength][varListStringLength];

unsigned char varListCtr = 0;

double varListDouble[varListLength];

unsigned char prgMode = 0;

unsigned char annunciator = 0;

extern const uint8_t AdafruitClassicData[];
uint8_t size;

uint8_t const *fontData;
uint32_t const *fontOffset;

uint32_t fontColour;
uint32_t backgroundfontColour;

unsigned char QNO;

//functions

void initDisp(void);
void setRotation(uint8_t);
void fillScreen(uint16_t);

void varInit(void);                                                            //initialise variables
void scanKp(void);                                                             //scan the 8 row by 6 column keypad

void reStatL(void);                                                            //*refresh* functions
void reStack(void);
void reCmdL(void);
void reMenu(void);

void kpMain(unsigned int);                                                     //*keypad* functions
void kpGraph(unsigned int);
void kpMatrix(unsigned int);
void kpSolve(unsigned int);
void kpStat(unsigned int);
void kpKSPrg(unsigned int);
void kpHLPrg(unsigned int);
void kpTest(unsigned int);
void kpView(unsigned int);
void kpMode(unsigned int);
void kpSystem(unsigned int);
void kpStore(unsigned int);
void kpKSPrgDebug(unsigned int);
void kpKSPrgMenu(unsigned int);
void kpErase(unsigned int);
void kpKSPrgVar(unsigned int);
void kpKSPrgSTO(unsigned int);
void kpfont5x7(unsigned int);
void kpAddTables(unsigned int);
void kpSubtractionTables(unsigned int);
void kpTimesTables(unsigned int);
void kpDivisionTables(unsigned int);

void delay1ms(void);
void delayms(unsigned int);

///////////////////////////////////////////////////////////////////////////////

int main(void) {
	//unsigned int i;

  	BOARD_InitPins();
	BOARD_BootClockRUN();
    BOARD_InitDebugConsole();

    SysTick->CTRL = 0;                                                         //disable SysTick

//    for (i=0; i<10; i++) {                                                     //flash board LED 10 times
//    	GPIO_PinWrite(BOARD_LED_TEST_PERIPHERAL, BOARD_LED_TEST_CHANNEL, 1);
//    	delayms(500);
//    	GPIO_PinWrite(BOARD_LED_TEST_PERIPHERAL, BOARD_LED_TEST_CHANNEL, 0);
//    	delayms(500);
//    }

    initDisp();
    setRotation(3);
    fillScreen(BLACK);

    varInit();
    while (1) {

    	if (flag2 & STATUSLINEOFF) flag2 &= ~STATUSLINEOFF;
    	else reStatL();

    	if (flag2 & STACKOFF) flag2 &= ~STACKOFF;
    	else reStack();

    	if (flag2 & MENUOFF) flag2 &= ~MENUOFF;
    	else reMenu();

    	if (flag2 & COMMANDLINEOFF) flag2 &= ~COMMANDLINEOFF;
    	else reCmdL();

    	scanKp();

    	if (flag1 & SHIFT) {
    		keyNumber += 48;
    		flag1 &= ~SHIFT;
    	}
    	//if (keyHeldCtr == keyHeld) keyNumber += 96;

    	switch (kpPlane) {
    	case 0:
    		kpMain(keyNumber);
    		break;
    	case 1:
    		kpGraph(keyNumber);
    		break;
    	case 2:
    		kpMatrix(keyNumber);
    		break;
    	case 3:
    		kpSolve(keyNumber);
    		break;
    	case 4:
    		kpStat(keyNumber);
    		break;
    	case 5:
    		kpKSPrg(keyNumber);
    		break;
    	case 6:
    		kpHLPrg(keyNumber);
    		break;
    	case 7:
    		kpTest(keyNumber);
    		break;
    	case 8:
    		kpView(keyNumber);
    		break;
    	case 9:
    		kpMode(keyNumber);
    		break;
    	case 10:
    		kpSystem(keyNumber);
    		break;
    	case 11:
    		kpStore(keyNumber);
    		break;
    	case 12:
    		kpKSPrgDebug(keyNumber);
    		break;
    	case 13:
    		kpKSPrgMenu(keyNumber);
    		break;
    	case 14:
    		kpErase(keyNumber);
    		break;
    	case 15:
    		kpKSPrgVar(keyNumber);
    		break;
    	case 16:
    		kpKSPrgSTO(keyNumber);
    		break;
    	case 17:
    		kpfont5x7(keyNumber);
    		break;
    	case 18:
    		break;
    	case 19:
    		break;
    	case 20:
    		kpAddTables(keyNumber);
    		break;
    	case 21:
    		kpSubtractionTables(keyNumber);
    		break;
    	case 22:
    		kpTimesTables(keyNumber);
    		break;
    	case 23:
    		kpDivisionTables(keyNumber);
    		break;
    	}
    }
}

void delay1ms(void) {
	//SysTick->LOAD = 0x0007A120;

	SysTick->VAL = 0;
	SysTick->CTRL = 5;

    while((SysTick->CTRL & 0x00010000) == 0);

    SysTick->CTRL = 0;
}

void delayms(unsigned int max) {
	unsigned int i;

	SysTick->LOAD = 0x0007A120;                                                //reload value for 1ms

	for (i=0; i<max; i++) delay1ms();
}


