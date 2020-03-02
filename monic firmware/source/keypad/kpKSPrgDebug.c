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

//variables

extern unsigned int keyNumber;
extern unsigned int flag2;
extern unsigned char menu;

extern unsigned int *prg;
extern unsigned int prgIndex;
extern unsigned char prgMode;
extern unsigned char kpPlane;

extern unsigned int uStackIndex;                                               //user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix
extern unsigned int uStackDIndex;                                              //complex user stack index
extern double uStackD[stackDDepth];                                            //array to store real part
extern double uStackDIMAG[stackDDepth];                                        //array to store imaginary part
extern unsigned int indexLink[stackDDepth];

extern unsigned int cStackIndex;                                               //complex user stack index
extern double cStackD[stackDDepth];                                            //array to store real part on complex stack
extern double cStackDIMAG[stackDDepth];                                        //array to store imaginary part on complex stack

//functions

void runPrg(unsigned int);
void runPrgCplx(unsigned int);

void resetVar(void);

///////////////////////////////////////////////////////////////////////////////

void kpKSPrgDebug(unsigned int x) {
    switch (x) {
    case menuKey1KSPrgDebug:
        if (prg[prgIndex] != END) {                                            //if END program instruction not reached
            if (prgMode) runPrgCplx(prg[prgIndex]); else runPrg(prg[prgIndex]);
        }
        else {                                                                 //if END program instruction reached
//            uStackDIndex += 1;
//            uStackD[uStackDIndex] = cStackD[cStackIndex];
//            uStackDIMAG[uStackDIndex] = cStackDIMAG[cStackIndex];
//
//            uStackIndex += 1;
//            uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
//            indexLink[uStackIndex] = uStackDIndex;

            kpPlane = 0;
            flag2 |= CURSORON;
            menu = 0;
            resetVar();
        }
        break;
    case menuKey3KSPrgDebug:                                                   //INSTR/OPCODE toggle
        if (flag2 & OPCODE) flag2 &= ~OPCODE;
        else flag2 |= OPCODE;
        break;
    case exitKSPrgDebug:                                                       //EXIT
        kpPlane = 0;
        flag2 |= CURSORON;
        menu = 0;
        resetVar();
        break;
    }
}
