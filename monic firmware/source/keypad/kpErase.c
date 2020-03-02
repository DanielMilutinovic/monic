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

#include "../user.h"
#include <math.h>

//variables

extern unsigned char kpPlane;
extern unsigned int flag2;

extern unsigned int custMenuFunc[custMenuLength];
extern unsigned char memAlloc[memAllocLength];
extern unsigned char custMenuLbl[custMenuLength][8];

extern unsigned char menu;

extern unsigned int *prg;
extern unsigned int prg1[numberOfPrgSteps];
extern unsigned int prg2[numberOfPrgSteps];
extern unsigned int prg3[numberOfPrgSteps];
extern unsigned int prg4[numberOfPrgSteps];
extern unsigned int prg5[numberOfPrgSteps];
extern unsigned int prg6[numberOfPrgSteps];

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

extern unsigned int *labelAddress;
extern unsigned int labelAddress1[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress2[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress3[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress4[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress5[labelAddressLength];                                          //array to store program counter values corresponding to labels
extern unsigned int labelAddress6[labelAddressLength];                                          //array to store program counter values corresponding to labels

extern char (*varList)[varListStringLength];
extern char varList1[varListLength][varListStringLength];
extern char varList2[varListLength][varListStringLength];
extern char varList3[varListLength][varListStringLength];
extern char varList4[varListLength][varListStringLength];
extern char varList5[varListLength][varListStringLength];
extern char varList6[varListLength][varListStringLength];

//functions

void setPrgVars(unsigned int);

//////////////////////////////////////////////////////////////////////////////

void kpErase(unsigned int x) {
    unsigned char i;

    switch (x) {
    case menuKey1Erase:                                                        //erase program/variable at Menu Key 1
        if (custMenuFunc[0] > 100) {
            setPrgVars(custMenuFunc[0]);
            custMenuFunc[0] = 0;

            for (i = 0; i < 6; i++) custMenuLbl[0][i] = 32;                    //clear label
        }
        break;
    case menuKey2Erase:                                                        //erase program/variable at Menu Key 2
        if (custMenuFunc[1] > 100) {
            setPrgVars(custMenuFunc[1]);
            custMenuFunc[1] = 0;

            for (i = 0; i < 6; i++) custMenuLbl[1][i] = 32;                    //clear label
        }
        break;
    case menuKey3Erase:                                                        //erase program/variable at Menu Key 3
        if (custMenuFunc[2] > 100) {
            setPrgVars(custMenuFunc[2]);
            custMenuFunc[2] = 0;

            for (i = 0; i < 6; i++) custMenuLbl[2][i] = 32;                    //clear label
        }
        break;
    }
    kpPlane = 0;                                                               //return to kpMain
    menu = 0;
    flag2 |= CURSORON;                                                         //turn cursor on
}

void setPrgVars(unsigned int x) {
    unsigned char i;
    unsigned char j;

    switch (x) {
    case 101:                                                          //erase KS program 1 etc.
        prg = prg1; prgConstants = prgConstants1; prgConstantsF = prgConstantsF1; labelAddress = labelAddress1; varList = varList1;
        break;
    case 102:
        prg = prg2; prgConstants = prgConstants2; prgConstantsF = prgConstantsF2; labelAddress = labelAddress2; varList = varList2;
        break;
    case 103:
        prg = prg3; prgConstants = prgConstants3; prgConstantsF = prgConstantsF3; labelAddress = labelAddress3; varList = varList3;
        break;
    case 104:
        prg = prg4; prgConstants = prgConstants4; prgConstantsF = prgConstantsF4; labelAddress = labelAddress4; varList = varList4;
        break;
    case 105:
        prg = prg5; prgConstants = prgConstants5; prgConstantsF = prgConstantsF5; labelAddress = labelAddress5; varList = varList5;
        break;
    case 106:
        prg = prg6; prgConstants = prgConstants6; prgConstantsF = prgConstantsF6; labelAddress = labelAddress6; varList = varList6;
        break;
    }
    for (i = 0; i < numberOfPrgSteps-1; i++) {
        prg[i] = 184;                                                  //prg[0] = ... = NOP
    }
    prg[numberOfPrgSteps-1] = 122;

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstants[i] = HUGE_VAL;                                    //prgConstants[0] = ... = prgConstants[] = HUGE_VAL
    }

    for (i = 0; i < prgConstantsLength; i++) {
        prgConstantsF[i] = HUGE_VALF;                                  //prgConstantsF[0] = ... = prgConstantsF[] = HUGE_VALF
    }

    for (i = 0; i < labelAddressLength; i++) {
        labelAddress[i] = 0xFFFFFFFE;                                  //labelAddress[0] = ... = labelAddress[] = 0xFFFFFFFE
    }

    for (i = 0; i < varListLength; i++) {
        for (j = 0; j < 8; j++) varList[i][j] = 0x00;                  //varList[0][0] = ... = varList[varListLength][6] = 0x00
    }

    memAlloc[x] = 1;                                                   //memory now available
}

