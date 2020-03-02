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

#include "../user.h"

#include <math.h>

//variables

extern unsigned int prgIndex;
extern unsigned int *prg;

extern unsigned int flag1;

extern double valueCmdL_SigD;
extern double valueCmdL_ExpD;
extern double valueCmdL_D;
extern double decDigits;
extern unsigned char cmdL_S[cmdL_SLength];

extern unsigned int uStackIndex;                                               //user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix
extern unsigned int uStackDIndex;
extern double uStackD[stackDDepth];
extern double uStackDIMAG[stackDDepth];
extern unsigned int indexLink[stackDDepth];

extern unsigned char sigLength;

extern double cmdLNumber[cmdLNumberLength];

//functions

void negateMatrix(void);
void addMatrices(void);
void subtractMatrices(void);
void multiplyMatrices(void);
void scalarMultiply(void);

///////////////////////////////////////////////////////////////////////////////

void runPrg(unsigned int x) {
    double temp;
    unsigned char i;

    switch (x) {
    case equalKSPrg:                                                           //PUSH COMMAND LINE
        if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
        valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
        if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
        uStackDIndex += 1;
        uStackD[uStackDIndex] = valueCmdL_D;
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                           //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;

        sigLength = 0;
        for (i = 0; i < cmdL_SLength; i++) cmdL_S[i] = 0;
        break;
    case negateKSPrg:                                                          //NEGATE
        if (uStackType[uStackIndex]) negateMatrix();                           //if matrix
        else {                                                                 //if complex number
            uStackD[uStackDIndex] = -uStackD[uStackDIndex];
            uStackDIMAG[uStackDIndex] = -uStackDIMAG[uStackDIndex];
        }
        break;
    case addKSPrg:                                                             //add complex numbers/matrices
        if (sigLength) {                                                       //push command line if it is not empty
            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
            uStackDIndex += 1;
            uStackD[uStackDIndex] = valueCmdL_D;
            uStackDIMAG[uStackDIndex] = 0.0;

            uStackIndex += 1;
            uStackType[uStackIndex] = 0;                                   //0 -> type complex scalar
            indexLink[uStackIndex] = uStackDIndex;

            sigLength = 0;
        }

        if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
            if ((uStackType[uStackIndex]) && (uStackType[uStackIndex - 1])) addMatrices();     //if matrices on top two levels
            else {                                                         //display ERROR as cannot add matrix and complex number

            }
        }
        else {                                                             //if both entries complex numbers
            uStackD[uStackDIndex - 1] = uStackD[uStackDIndex - 1] + uStackD[uStackDIndex];               //add real parts
            uStackDIMAG[uStackDIndex - 1] = uStackDIMAG[uStackDIndex - 1] + uStackDIMAG[uStackDIndex];   //add imaginary parts
            uStackDIndex -= 1;
            uStackIndex -= 1;
        }
        break;
    case subtractKSPrg:                                                        //SUBTRACT
        if (sigLength) {                                                       //if command line not empty
            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
            uStackDIndex += 1;
            uStackD[uStackDIndex] = valueCmdL_D;
            uStackDIMAG[uStackDIndex] = 0.0;

            uStackIndex += 1;
            uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
            indexLink[uStackIndex] = uStackDIndex;

            sigLength = 0;
        }

        if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
            if ((uStackType[uStackIndex]) && (uStackType[uStackIndex - 1])) subtractMatrices();  //if matrices on top two levels
            else {                                                         //display ERROR as cannot add matrix and complex number

            }
        }
        else {                                                             //if both entries complex
            uStackD[uStackDIndex - 1] = uStackD[uStackDIndex - 1] - uStackD[uStackDIndex];               //subtract real parts
            uStackDIMAG[uStackDIndex - 1] = uStackDIMAG[uStackDIndex - 1] - uStackDIMAG[uStackDIndex];   //subtract imaginary parts
            uStackDIndex -= 1;
            uStackIndex -= 1;
        }
        break;
    case multiplyKSPrg:                                                        //MULTIPLY
        if (sigLength) {                                                       //if command line not empty
            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
            uStackDIndex += 1;
            uStackD[uStackDIndex] = valueCmdL_D;
            uStackDIMAG[uStackDIndex] = 0.0;

            uStackIndex += 1;
            uStackType[uStackIndex] = 0;                                   //0 -> type complex scalar
            indexLink[uStackIndex] = uStackDIndex;

            sigLength = 0;
        }

        if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
            if ((uStackType[uStackIndex]) && (uStackType[uStackIndex - 1])) multiplyMatrices();  //if matrices on top two levels
            else scalarMultiply();                                         //if matrix and complex number on top two levels
        }
        else {                                                             //if both entries complex numbers
            temp = uStackD[uStackDIndex-1] * uStackD[uStackDIndex] - uStackDIMAG[uStackDIndex-1] * uStackDIMAG[uStackDIndex];
            uStackDIMAG[uStackDIndex-1] = uStackD[uStackDIndex-1] * uStackDIMAG[uStackDIndex] +
                    uStackDIMAG[uStackDIndex-1] * uStackD[uStackDIndex];
            uStackD[uStackDIndex-1] = temp;

            uStackDIndex -= 1;
            uStackIndex -= 1;
        }
        break;
    case divideKSPrg:                                                          //DIVIDE
        if (sigLength) {                                                   //if command line not empty
            if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
            valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
            if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;
            uStackDIndex += 1;
            uStackD[uStackDIndex] = valueCmdL_D;
            uStackDIMAG[uStackDIndex] = 0.0;

            uStackIndex += 1;
            uStackType[uStackIndex] = 0;                                   //0 -> type complex scalar
            indexLink[uStackIndex] = uStackDIndex;

            sigLength = 0;
        }

        if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
            //if scalar on level 1  and matrix on level 2
            if ((uStackType[uStackIndex] == 0) && (uStackType[uStackIndex - 1])) scalarMultiply();
            else {                                                         //ERROR if matrices on top two levels or scalar on level 2

            }
        }
        else {                                                             //if both entries complex numbers
            temp = (uStackD[uStackDIndex-1] * uStackD[uStackDIndex] + uStackDIMAG[uStackDIndex-1] * uStackDIMAG[uStackDIndex])/
                    (uStackD[uStackDIndex] * uStackD[uStackDIndex] + uStackDIMAG[uStackDIndex] * uStackDIMAG[uStackDIndex]);

            uStackDIMAG[uStackDIndex-1] = (uStackDIMAG[uStackDIndex-1] * uStackD[uStackDIndex] -
                    uStackD[uStackDIndex-1] * uStackDIMAG[uStackDIndex])/
                    (uStackD[uStackDIndex] * uStackD[uStackDIndex] + uStackDIMAG[uStackDIndex] * uStackDIMAG[uStackDIndex]);

            uStackD[uStackDIndex-1] = temp;

            uStackDIndex -= 1;
            uStackIndex -= 1;
        }
        break;
    case 166:                                                                  //DUPLICATE
        uStackDIndex += 1;
        uStackD[uStackDIndex] = uStackD[uStackDIndex-1];
        uStackDIMAG[uStackDIndex] = uStackDIMAG[uStackDIndex-1];

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                           //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6000:                                                                 //instructions to push values onto the stack when evaluating
                                                                               //the command line in algebraic mode ->
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[0];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6001:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[1];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6002:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[2];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6003:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[3];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6004:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[4];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6005:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[5];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6006:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[6];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6007:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[7];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;
    case 6008:
        uStackDIndex += 1;
        uStackD[uStackDIndex] = cmdLNumber[8];
        uStackDIMAG[uStackDIndex] = 0.0;

        uStackIndex += 1;
        uStackType[uStackIndex] = 0;                                       //0 -> type complex scalar
        indexLink[uStackIndex] = uStackDIndex;
        break;                                                             //<-
    }
    prgIndex += 1;
}
