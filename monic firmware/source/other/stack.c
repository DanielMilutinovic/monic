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

//functions to manipulate the user stack (SWAP, DUP etc.)

//includes

#include "../user.h"

//variables

extern unsigned int uStackIndex;
extern unsigned int uStackDIndex;

extern unsigned char uStackType[stackDDepth];
extern double uStackD[stackDDepth];                                            //array to store real part
extern double uStackDIMAG[stackDDepth];                                        //array to store imaginary part
extern unsigned int indexLink[stackDDepth];
extern unsigned char uStackMDim[stackDDepth][2];

//functions

void swap(void);

///////////////////////////////////////////////////////////////////////////////

void swap(void) {
    double tempReal;
    double tempImag;

    if (uStackIndex > 1) {                                                     //if at least two values on the user stack
        if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {      //if at least one matrix on top two levels
            if ((uStackType[uStackIndex]) && (uStackType[uStackIndex - 1])) {  //if matrices on top two levels

            }
            else {                                                             //if one matrix and one complex number on top two levels

            }
        }
        else {                                                                 //if both entries complex numbers
            tempReal = uStackD[uStackDIndex - 1];
            tempImag = uStackDIMAG[uStackDIndex - 1];

            uStackD[uStackDIndex - 1] = uStackD[uStackDIndex];
            uStackDIMAG[uStackDIndex - 1] = uStackDIMAG[uStackDIndex];

            uStackD[uStackDIndex] = tempReal;
            uStackDIMAG[uStackDIndex] = tempImag;
        }
    }
}
