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

//store values on the stack into variables

//includes

#include "../user.h"

//variables

extern unsigned int flag2;

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern unsigned int *prg;
extern unsigned int prgIndex;

extern unsigned char kpPlane;

extern unsigned char menu;

extern unsigned char annunciator;

//functions

void storeVarPrgEdit(void);

//constants

extern const unsigned char nextVarMenu[3];

///////////////////////////////////////////////////////////////////////////////

void kpKSPrgSTO(unsigned int x) {
    unsigned char i;

    switch(x) {
    case menuKey1KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190000;                                            //store into var1
            break;
        case 1:
            prg[prgIndex] = 190006;                                            //store into var7
            break;
        case 2:
            prg[prgIndex] = 190012;                                            //store into var13
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case menuKey2KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190001;                                            //store into var2
            break;
        case 1:
            prg[prgIndex] = 190007;                                            //store into var8
            break;
        case 2:
            prg[prgIndex] = 190013;                                            //store into var14
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case menuKey3KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190002;                                            //store into var3
            break;
        case 1:
            prg[prgIndex] = 190008;                                            //store into var9
            break;
        case 2:
            prg[prgIndex] = 190014;                                            //store into var15
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case menuKey4KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190003;                                            //store into var4
            break;
        case 1:
            prg[prgIndex] = 190009;                                            //store into var10
            break;
        case 2:
            prg[prgIndex] = 190015;                                            //store into var16
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case menuKey5KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190004;                                            //store into var5
            break;
        case 1:
            prg[prgIndex] = 190010;                                            //store into var11
            break;
        case 2:
            prg[prgIndex] = 190016;                                            //store into var17
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case menuKey6KSPrgSTO:
        switch (menu) {
        case 0:
            prg[prgIndex] = 190005;                                            //store into var6
            break;
        case 1:
            prg[prgIndex] = 190011;                                            //store into var12
            break;
        case 2:
            prg[prgIndex] = 190017;                                            //store into var18
            break;
        }
        annunciator = 0;
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        prgIndex += 1;
        goto exit2;
    case deletelKSPrgSTO:                                                      //DELETE
        cmdL_Term -= 1;
        cmdL_S[cmdL_Term] = 0x00;
        flag2 |= MENUOFF;
        goto exit;                                                             //so that cmdL_Term is not incremented
    case nextKSPrgSTO:                                                         //NEXT
        //menu = nextVarMenu2[menu];
        menu = nextVarMenu[menu];
        goto exit;                                                             //so that cmdL_Term is not incremented
    case equalKSPrgSTO:
        storeVarPrgEdit();                                                     //STORE to variable and return to KSPrg
        cmdL_Term = 0;
        for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0x00;
        prgIndex += 1;
        //flag2 &= ~CMDLINEPRGEDIT;
        flag2 &= ~CURSORON;
        annunciator = 0;
        kpPlane = 5;
        //flag2 |= MENUOFF;
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
    case zKSPrgSTO:
        cmdL_S[cmdL_Term] = 90;                                                //"Z"
        break;
    case zeroStore:
        cmdL_S[cmdL_Term] = 48;                                                //"0"
        break;
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
    case fiveStore:
        cmdL_S[cmdL_Term] = 53;                                                //"5"
        break;
    case sixStore:
        cmdL_S[cmdL_Term] = 54;                                                //"6"
        break;
    case sevenStore:
        cmdL_S[cmdL_Term] = 55;                                                //"7"
        break;
    case eightStore:
        cmdL_S[cmdL_Term] = 56;                                                //"8"
        break;
    case nineStore:
        cmdL_S[cmdL_Term] = 57;                                                //"9"
        break;
    }
    cmdL_Term += 1;
    flag2 |= MENUOFF;
    exit:
    flag2 |= STACKOFF;
    exit2:
	__asm volatile ("nop");
}





