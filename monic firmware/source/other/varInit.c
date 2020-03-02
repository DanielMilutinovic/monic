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

#include <math.h>

#include <stdint.h>
#include <stdbool.h>

#include "../user.h"
#include "../header/globalVars.h"

//structures

//struct tt {
//	char question[6];
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

extern unsigned char cmdL_S[cmdL_SLength];
extern char custMenuLbl[custMenuLength][6];
extern unsigned int custMenuFunc[custMenuLength];
extern unsigned char memAlloc[memAllocLength];

extern unsigned int prg1[numberOfPrgSteps];
extern unsigned int prg2[numberOfPrgSteps];
extern unsigned int prg3[numberOfPrgSteps];
extern unsigned int prg4[numberOfPrgSteps];
extern unsigned int prg5[numberOfPrgSteps];
extern unsigned int prg6[numberOfPrgSteps];

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

extern char varList1[varListLength][varListStringLength];
extern char varList2[varListLength][varListStringLength];
extern char varList3[varListLength][varListStringLength];
extern char varList4[varListLength][varListStringLength];
extern char varList5[varListLength][varListStringLength];
extern char varList6[varListLength][varListStringLength];

extern uint8_t fontVW_1Data[];
extern uint32_t fontVW_1Offset[];

extern uint8_t AdafruitClassicData[];
extern uint8_t size;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

const struct at atquestions[] = {{.question = "1+1=",.answer = "2"}, {.question = "1+2=",.answer = "3"},
{.question = "1+3=",.answer = "4"}, {.question = "1+4=",.answer = "5"}, {.question = "2+1=",.answer = "3"},
{.question = "2+2=",.answer = "4"}, {.question = "2+3=",.answer = "5"}, {.question = "2+4=",.answer = "6"},
{.question = "3+1=",.answer = "4"}, {.question = "3+2=",.answer = "5"}, {.question = "3+3=",.answer = "6"},
{.question = "3+4=",.answer = "7"}, {.question = "4+1=",.answer = "5"}, {.question = "4+2=",.answer = "6"},
{.question = "4+3=",.answer = "7"}, {.question = "4+4=",.answer = "8"}, {.question = "END!",.answer = "END"}};

const struct st stquestions[] = {{.question = "1-1=",.answer = "0"}, {.question = "2-1=",.answer = "1"},
		{.question = "2-2=",.answer = "0"}, {.question = "3-1=",.answer = "2"}, {.question = "3-2=",.answer = "1"},
		{.question = "3-3=",.answer = "0"}, {.question = "4-1=",.answer = "3"}, {.question = "4-2=",.answer = "2"},
		{.question = "4-3=",.answer = "1"}, {.question = "4-4=",.answer = "0"}, {.question = "END!",.answer = "END"}};

const struct tt ttquestions[] = {{.question = "2*3=",.answer = "6"}, {.question = "9*8=",.answer = "72"},
{.question = "4*6=",.answer = "24"}, {.question = "5*7=",.answer = "35"}, {.question = "10*3=",.answer = "30"},
{.question = "12*6=",.answer = "72"}, {.question = "2*11=",.answer = "22"}, {.question = "4*12=",.answer = "48"},
{.question = "7*8=",.answer = "56"}, {.question = "10*11=",.answer = "110"}, {.question = "END!",.answer = "END"}};

const struct dt dtquestions[] = {{.question = "6/3=",.answer = "2"}, {.question = "72/8=",.answer = "9"},
{.question = "24/6=",.answer = "4"}, {.question = "35/7=",.answer = "5"}, {.question = "30/3=",.answer = "10"},
{.question = "72/6=",.answer = "12"}, {.question = "22/11=",.answer = "2"}, {.question = "48/12=",.answer = "4"},
{.question = "56/8=",.answer = "7"}, {.question = "110/11=",.answer = "10"}, {.question = "END!",.answer = "END"}};

////////////////////////////////////////////////////////////////////////////

void varInit(void) {
    unsigned int i;
    unsigned char j;

#ifdef FIXED_WIDTH_FONT
    fontData = AdafruitClassicData;
    size = 4;
#else
    fontData = fontVW_1data;
    fontOffset = fontVW_1Offset;
#endif

    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;                       //no characters entered on command line

    for (i = 0; i < custMenuLength; i++) {
        for (j = 0; j < 6; j++) custMenuLbl[i][j] = 0x00;                      //custMenuLbl[0][0] = ... = custMenuLbl[custMenuLength][5] =
    }                                                                          //0 (space)

    for (i = 0; i < custMenuLength; i++) {
        custMenuFunc[i] = 0;                                                   //custMenuFunc[0] = ... = custMenuFunc[custMenuLength] = 0
    }

    for (i = 0; i < memAllocLength; i++) {
        memAlloc[i] = 1;                                                       //memAlloc[0] = ... = memAlloc[memAllocLength] = 1
    }

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg1[i] = 184;                                                         //prg1[0] = ... = NOP
    }
    prg1[numberOfPrgSteps-1] = 122;                                            //prg1[last] = END

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg2[i] = 184;                                                         //prg2[0] = ... = NOP
    }
    prg2[numberOfPrgSteps-1] = 122;                                            //prg2[last] = END

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg3[i] = 184;                                                         //prg3[0] = ... = NOP
    }
    prg3[numberOfPrgSteps-1] = 122;                                            //prg3[last] = END

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg4[i] = 184;                                                         //prg4[0] = ... = NOP
    }
    prg4[numberOfPrgSteps-1] = 122;                                            //prg4[last] = END

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg5[i] = 184;                                                         //prg5[0] = ... = NOP
    }
    prg5[numberOfPrgSteps-1] = 122;                                            //prg5[last] = END

    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg6[i] = 184;                                                         //prg6[0] = ... = NOP
    }
    prg6[numberOfPrgSteps-1] = 122;                                            //prg6[last] = END

    for (i = 0; i < numberOfCPrgChars; i++) {
        Cprg1[i] = 32;                                                         //Cprg1[0] = ... = 32 (space)
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress1[i] = 0xFFFFFFFE;                                         //labelAddress1[0] = ... = labelAddress1[] = 0xFFFFFFFE
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress2[i] = 0xFFFFFFFE;                                         //labelAddress2[0] = ... = labelAddress2[] = 0xFFFFFFFE
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress3[i] = 0xFFFFFFFE;                                         //labelAddress3[0] = ... = labelAddress3[] = 0xFFFFFFFE
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress4[i] = 0xFFFFFFFE;                                         //labelAddress4[0] = ... = labelAddress4[] = 0xFFFFFFFE
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress5[i] = 0xFFFFFFFE;                                         //labelAddress5[0] = ... = labelAddress5[] = 0xFFFFFFFE
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress6[i] = 0xFFFFFFFE;                                         //labelAddress6[0] = ... = labelAddress6[] = 0xFFFFFFFE
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants1[i] = HUGE_VAL;                                           //prgConstants1[0] = ... = prgConstants1[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants2[i] = HUGE_VAL;                                           //prgConstants2[0] = ... = prgConstants2[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants3[i] = HUGE_VAL;                                           //prgConstants3[0] = ... = prgConstants3[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants4[i] = HUGE_VAL;                                           //prgConstants4[0] = ... = prgConstants4[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants5[i] = HUGE_VAL;                                           //prgConstants5[0] = ... = prgConstants5[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants6[i] = HUGE_VAL;                                           //prgConstants6[0] = ... = prgConstants6[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF1[i] = HUGE_VALF;                                         //prgConstantsF1[0] = ... = prgConstantsF1[] = HUGE_VALF
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF2[i] = HUGE_VALF;                                         //prgConstantsF2[0] = ... = prgConstantsF2[] = HUGE_VALF
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF3[i] = HUGE_VALF;                                         //prgConstantsF3[0] = ... = prgConstantsF3[] = HUGE_VALF
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF4[i] = HUGE_VALF;                                         //prgConstantsF4[0] = ... = prgConstantsF4[] = HUGE_VALF
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF5[i] = HUGE_VALF;                                         //prgConstantsF5[0] = ... = prgConstantsF5[] = HUGE_VALF
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF6[i] = HUGE_VALF;
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList1[i][j] = 0x00;       //varList1[0][0] = ... = varList1[varListLength][] = 0x00
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList2[i][j] = 0x00;       //varList2[0][0] = ... = varList2[varListLength][] = 0x00
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList3[i][j] = 0x00;       //varList3[0][0] = ... = varList3[varListLength][] = 0x00
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList4[i][j] = 0x00;       //varList4[0][0] = ... = varList4[varListLength][] = 0x00
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList5[i][j] = 0x00;       //varList5[0][0] = ... = varList5[varListLength][] = 0x00
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < varListStringLength; j++) varList6[i][j] = 0x00;       //varList6[0][0] = ... = varList6[varListLength][] = 0x00
    }


}




