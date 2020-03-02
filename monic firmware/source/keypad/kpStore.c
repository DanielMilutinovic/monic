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

//enter program/variable names

//includes

#include "../user.h"

#include <math.h>

//variables

extern unsigned char kpPlane;
extern unsigned char menu;

extern unsigned char keyHeldCtr;

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern unsigned int flag2;
extern unsigned int flag3;

extern unsigned char custMenuLbl[custMenuLength][6];
extern unsigned int custMenuFunc[custMenuLength];
extern unsigned int memAllocCtr;
extern unsigned char memAlloc[memAllocLength];

extern unsigned int *prg;
extern unsigned int prg1[numberOfPrgSteps];
extern unsigned int prg2[numberOfPrgSteps];
extern unsigned int prg3[numberOfPrgSteps];
extern unsigned int prg4[numberOfPrgSteps];
extern unsigned int prg5[numberOfPrgSteps];
extern unsigned int prg6[numberOfPrgSteps];

extern double prgConstants1[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF1[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants2[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF2[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants3[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF3[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants4[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF4[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants5[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF5[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double prgConstants6[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution

extern float prgConstantsF6[prgConstantsLength];                                         //array to store values pushed onto the stack during program
                                                                                         //execution (float)

extern double *prgConstants;
extern float *prgConstantsF;

extern unsigned int *labelAddress;
extern unsigned int labelAddress1[labelAddressLength];                                   //array to store program counter values corresponding to labels
extern unsigned int labelAddress2[labelAddressLength];                                   //array to store program counter values corresponding to labels
extern unsigned int labelAddress3[labelAddressLength];                                   //array to store program counter values corresponding to labels
extern unsigned int labelAddress4[labelAddressLength];                                   //array to store program counter values corresponding to labels
extern unsigned int labelAddress5[labelAddressLength];                                   //array to store program counter values corresponding to labels
extern unsigned int labelAddress6[labelAddressLength];                                   //array to store program counter values corresponding to labels

extern char (*varList)[varListStringLength];
extern char varList1[varListLength][varListStringLength];
extern char varList2[varListLength][varListStringLength];
extern char varList3[varListLength][varListStringLength];
extern char varList4[varListLength][varListStringLength];
extern char varList5[varListLength][varListStringLength];
extern char varList6[varListLength][varListStringLength];

//functions

void menuKey1_Store(void);
void menuKey2_Store(void);
void menuKey3_Store(void);

//////////////////////////////////////////////////////////////////////////////

void kpStore(unsigned int x) {
    unsigned char i;
    unsigned char j;

    switch (x) {
    case deleteStore:                                                          //DELETE
        cmdL_Term -= 1;
        cmdL_S[cmdL_Term] = 0x00;
        goto exit2;
    case AStore:
        cmdL_S[cmdL_Term] = 65;                                                //"A"
        break;
    case BStore:
        cmdL_S[cmdL_Term] = 66;                                                //"B"
        break;
    case CStore:
        cmdL_S[cmdL_Term] = 67;                                                //"C"
        break;
    case DStore:
        cmdL_S[cmdL_Term] = 68;                                                //"D"
        break;
    case EStore:
        cmdL_S[cmdL_Term] = 69;                                                //"E"
        break;
    case FStore:
        cmdL_S[cmdL_Term] = 70;                                                //"F"
        break;
    case GStore:
        cmdL_S[cmdL_Term] = 71;                                                //"G"
        break;
    case HStore:
        cmdL_S[cmdL_Term] = 72;                                                //"H"
        break;
    case IStore:
        cmdL_S[cmdL_Term] = 73;                                                //"I"
        break;
    case JStore:
        cmdL_S[cmdL_Term] = 74;                                                //"J"
        break;
    case KStore:
        cmdL_S[cmdL_Term] = 75;                                                //"K"
        break;
    case LStore:
        cmdL_S[cmdL_Term] = 76;                                                //"L"
        break;
    case MStore:
        cmdL_S[cmdL_Term] = 77;                                                //"M"
        break;
    case NStore:
        cmdL_S[cmdL_Term] = 78;                                                //"N"
        break;
    case OStore:
        cmdL_S[cmdL_Term] = 79;                                                //"O"
        break;
    case PStore:
        cmdL_S[cmdL_Term] = 80;                                                //"P"
        break;
    case QStore:
        cmdL_S[cmdL_Term] = 81;                                                //"Q"
        break;
    case RStore:
        cmdL_S[cmdL_Term] = 82;                                                //"R"
        break;
    case SStore:
        cmdL_S[cmdL_Term] = 83;                                                //"S"
        break;
    case TStore:
        cmdL_S[cmdL_Term] = 84;                                                //"T"
        break;
    case UStore:
        cmdL_S[cmdL_Term] = 85;                                                //"U"
        break;
    case VStore:
        cmdL_S[cmdL_Term] = 86;                                                //"V"
        break;
    case WStore:
        cmdL_S[cmdL_Term] = 87;                                                //"W"
        break;
    case XStore:
        cmdL_S[cmdL_Term] = 88;                                                //"X"
        break;
    case YStore:
        cmdL_S[cmdL_Term] = 89;                                                //"Y"
        break;
    case ZStore:
        cmdL_S[cmdL_Term] = 90;                                                //"Z"
        break;
    case menuKey1Store:                                                        //MENU KEY 1
        menuKey1_Store();
        goto exit;                                                             //so that cmdL_Term remains 0
    case menuKey2Store:                                                        //MENU KEY 2
        menuKey2_Store();
        goto exit;                                                             //so that cmdL_Term remains 0
    case menuKey3Store:                                                        //MENU KEY 3
        menuKey3_Store();
        goto exit;                                                             //so that cmdL_Term remains 0
    case oneStore:
        cmdL_S[cmdL_Term] = 49;                                                //"1"
        break;
    case twoStore:
        cmdL_S[cmdL_Term] = 50;                                                //"2"
        break;
    case threeStore:
        cmdL_S[cmdL_Term] = 51;                                                //"3"
        break;
    case fourStore:
        cmdL_S[cmdL_Term] = 52;                                                //"4"
        break;
    case clearStore:                                                           //CLEAR (do not store program/variable/folder)
        if (memAllocCtr > 100) {
            switch (memAllocCtr) {
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

            memAlloc[memAllocCtr] = 1;                                         //memory now available
            for (i = 0; i < 6; i++) custMenuLbl[0][i] = 32;                    //clear label
        }

        kpPlane = 0;
        for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;                   //clear command line
        cmdL_Term = 0;
        break;
    }
    cmdL_Term += 1;
    exit2:
    flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    exit:
	__asm volatile ("nop");
}

void menuKey1_Store(void) {
    unsigned char i;
    if (flag3 & newProgram) flag3 &= ~newProgram;                              //store program
    else {
        if (flag3 & newFolder) {
            flag3 &= ~newFolder;
            for (memAllocCtr = 201; memAllocCtr < 301; memAllocCtr++) {
                if (memAlloc[memAllocCtr]) break;
            }
            memAlloc[memAllocCtr] = 0;
        }
        else {

        }
    }
    if (menu) custMenuFunc[(menu - 200) * 6] = memAllocCtr; else custMenuFunc[0] = memAllocCtr;
    for (i = 0; i < 6; i++) custMenuLbl[0][i] = cmdL_S[i];                     //update custom menu
    kpPlane = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;                       //clear command line
    cmdL_Term = 0;
}

void menuKey2_Store(void) {
    unsigned char i;
    if (flag3 & newProgram) flag3 &= ~newProgram;                              //store program
    else {
        if (flag3 & newFolder) {
            flag3 &= ~newFolder;
            for (memAllocCtr = 201; memAllocCtr < 301; memAllocCtr++) {
                if (memAlloc[memAllocCtr]) break;
            }
            memAlloc[memAllocCtr] = 0;
        }
        else {

        }
    }
    custMenuFunc[1] = memAllocCtr;
    for (i = 0; i < 6; i++) custMenuLbl[1][i] = cmdL_S[i];                     //update custom menu
    kpPlane = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;                       //clear command line
    cmdL_Term = 0;
}

void menuKey3_Store(void) {
    unsigned char i;
    if (flag3 & newProgram) flag3 &= ~newProgram;                              //store program
    else {
        if (flag3 & newFolder) {
            flag3 &= ~newFolder;
            for (memAllocCtr = 201; memAllocCtr < 301; memAllocCtr++) {
                if (memAlloc[memAllocCtr]) break;
            }
            memAlloc[memAllocCtr] = 0;
        }
        else {

        }
    }
    custMenuFunc[2] = memAllocCtr;
    for (i = 0; i < 6; i++) custMenuLbl[2][i] = cmdL_S[i];                     //update custom menu
    kpPlane = 0;
    for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;                       //clear command line
    cmdL_Term = 0;
}
