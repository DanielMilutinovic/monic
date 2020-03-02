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

#include <stdint.h>

//variables

extern unsigned char matrixRow;
extern unsigned char matrixColumn;
extern unsigned char kpPlane;
extern unsigned int flag3;
extern int16_t xCoordinate;

extern unsigned int uStackIndex;                                               //user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix
extern unsigned int uStackDIndex;                                              //complex user stack index
extern unsigned int indexLink[stackDDepth];
extern unsigned char uStackMDim[stackDDepth][2];                               //array to store matrix dimensions

//functions

void enterMatrix(void);

///////////////////////////////////////////////////////////////////////////////

void kpMatrix (unsigned int x) {
    switch (x) {
    case equalMatrix:                                                          //EQUAL
        kpPlane = 0;
        enterMatrix();
        break;
    case oneMatrix:                                                            //ONE
//        if (flag3 & enterMatrixRow) {
//            flag3 &= ~enterMatrixRow;
//            flag3 |= enterMatrixColumn;
//            matrixRow = 1;
//        }
//        else {
//            flag3 &= ~enterMatrixColumn;
//            matrixColumn = 1;
//        }
        if (matrixRow) matrixColumn = 1;
        else matrixRow = 1;
        break;
    case twoMatrix:
//        if (flag3 & enterMatrixRow) {
//            flag3 &= ~enterMatrixRow;
//            flag3 |= enterMatrixColumn;
//            matrixRow = 2;
//        }
//        else {
//            flag3 &= ~enterMatrixColumn;
//            matrixColumn = 2;
//        }
        if (matrixRow) matrixColumn = 2;
        else matrixRow = 2;
        break;
    case threeMatrix:
        break;
    case fourMatrix:
        break;
    case fiveMatrix:
        break;
    case sixMatrix:
        break;
    case sevenMatrix:
        break;
    case eightMatrix:
        break;
    case nineMatrix:
        break;
    default:
    	__asm volatile ("nop");
    }
}

void enterMatrix(void) {
    uStackIndex = uStackIndex - matrixRow * matrixColumn + 1;
    uStackType[uStackIndex] = 1;
    indexLink[uStackIndex] = uStackDIndex;
    uStackMDim[uStackIndex][0] = matrixRow;
    uStackMDim[uStackIndex][1] = matrixColumn;

    matrixRow = 0;                                                             //reset
    matrixColumn = 0;
}
