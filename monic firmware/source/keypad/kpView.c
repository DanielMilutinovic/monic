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

extern unsigned int matrixRow;
extern unsigned int matrixColumn;

extern unsigned int uStackIndex;                                               //user stack level index
extern unsigned char uStackType[stackDDepth];                                  //0 -> complex, 1 -> matrix
extern unsigned char uStackMDim[stackDDepth][2];                               //array to store matrix dimensions

extern unsigned char kpPlane;

extern unsigned int flag2;

///////////////////////////////////////////////////////////////////////////////

void kpView (unsigned int x) {
    if (uStackType[uStackIndex]) {                                             //if viewing matrix
        switch (x) {
        case upView:                                                           //UP ARROW
            if (matrixRow == 1) matrixRow = uStackMDim[uStackIndex][0];
            else matrixRow -= 1;
            break;
        case downView:                                                         //DOWN ARROW
            if (matrixRow == uStackMDim[uStackIndex][0]) matrixRow = 1;
            else matrixRow += 1;
            break;
        case leftView:                                                         //LEFT ARROW
            if (matrixColumn == 1) matrixColumn = uStackMDim[uStackIndex][1];
            else matrixColumn -= 1;
            break;
        case rightView:                                                        //RIGHT ARROW
            if (matrixColumn == uStackMDim[uStackIndex][1]) matrixColumn = 1;
            else matrixColumn += 1;
            break;
        case exitView:                                                         //EXIT
            kpPlane = 0;
            matrixRow = 0;
            matrixColumn = 0;
            flag2 |= CURSORON;
            break;
        }
    }
    else {                                                                     //if viewing complex number
        switch (x) {
        case exitView:                                                         //EXIT
            kpPlane = 0;
            matrixRow = 0;
            matrixColumn = 0;
            flag2 |= CURSORON;                                                 //turn cursor on
            break;
        }
    }
}
