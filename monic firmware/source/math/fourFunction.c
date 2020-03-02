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

//variables

extern unsigned int flag1;
extern unsigned int flag2;
extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern unsigned int uStackIndex;
extern unsigned int uStackDIndex;

extern unsigned char uStackType[stackDDepth];
extern double uStackD[stackDDepth];                                            //array to store real part
extern double uStackDIMAG[stackDDepth];                                        //array to store imaginary part
extern unsigned int indexLink[stackDDepth];
extern unsigned char uStackMDim[stackDDepth][2];

extern unsigned char sigLength;

//functions

void enterComplex(void);

void negateMatrix(void);
void addMatrices(void);
void subtractMatrices(void);
void multiplyMatrices(void);
void scalarMultiply(void);

///////////////////////////////////////////////////////////////////////////////

void negate(void) {                                                            //negate complex number/matrix
	unsigned char i;

	if (flag2 & ALGENTRY) {                                                    //algebraic entry
		//if (flag1 & NEGSIG) flag1 &= ~NEGSIG;
		//else flag1|= NEGSIG;
		cmdL_S[cmdL_Term] = 128;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
    else {                                                                     //RPN
//    	if (cmdL_Term) {                                                       //command line not empty
//    		if (flag1 & NEGSIG) flag1 &= ~NEGSIG;
//    		else flag1|= NEGSIG;
//    	}
//    	else {                                                                 //command line empty
//    		if (uStackIndex) {                                                 //if user stack not empty
//    			if (uStackType[uStackIndex]) negateMatrix();                   //if matrix
//    			else {                                                         //if complex number
//    				uStackD[uStackDIndex] = -uStackD[uStackDIndex];
//    				uStackDIMAG[uStackDIndex] = -uStackDIMAG[uStackDIndex];
//    			}
//    		}
//    	}
    //}
//        if (flag1 & EXP) {                                                     //if in exponent entry field
//            if (flag1 & NEGEXP) flag1 &= ~NEGEXP;
//            else flag1|= NEGEXP;
//            flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
//        }
        //else {
        	if (cmdL_Term) {                                                   //if command line not empty
//                if (flag1 & NEGSIG) flag1 &= ~NEGSIG;
//                else flag1|= NEGSIG;
//        		cmdL_S[cmdL_Term] = 128;
//        		cmdL_Term += 1;
        		if (cmdL_S[0] == '-') {
        			for (i=0;i<cmdL_Term-1;i++) cmdL_S[i] = cmdL_S[i+1];
        			cmdL_Term --;
        			cmdL_S[cmdL_Term]=0;
        		}
        		else {
        			for (i=cmdL_Term;i>0;i--) cmdL_S[i] = cmdL_S[i-1];
        			cmdL_S[0] = '-';
        			cmdL_Term ++;
        		}
                flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);                 //do not update status line, stack or menu (reduce flicker)
            }
            else {                                                             //if command line empty
                if (uStackIndex) {                                             //if user stack not empty
                    if (uStackType[uStackIndex]) negateMatrix();               //if matrix
                    else {                                                     //if complex number
                        uStackD[uStackDIndex] = -uStackD[uStackDIndex];
                        uStackDIMAG[uStackDIndex] = -uStackDIMAG[uStackDIndex];
                    }
                }
            }
        }
    //}
}

void negateMatrix(void) {
    unsigned int i;
    for (i = indexLink[uStackIndex - 1] + 1; i <= indexLink[uStackIndex]; i++) {
        uStackD[i] = -uStackD[i];
        uStackDIMAG[i] = -uStackDIMAG[i];
    }
}

void add(void) {                                                               //add complex numbers/matrices
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 43;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        //if (sigLength) enterComplex();                                         //if command line not empty
    	if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex > 1) {                                                 //if at least two values on the user stack
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
        }
    }
}

void addMatrices(void) {
    unsigned int i;
    unsigned int j;

    if ((uStackMDim[uStackIndex][0] == uStackMDim[uStackIndex - 1][0]) && (uStackMDim[uStackIndex][1] == uStackMDim[uStackIndex - 1][1])) {
        i = indexLink[uStackIndex - 2] + 1;
        j = indexLink[uStackIndex - 1] + 1;

        for (i = indexLink[uStackIndex - 2] + 1; i <= indexLink[uStackIndex - 1]; i++) {
            uStackD[i] = uStackD[i] + uStackD[j];
            uStackDIMAG[i] = uStackDIMAG[i] + uStackDIMAG[j];
            j += 1;
        }

        uStackDIndex = indexLink[uStackIndex - 1];
        uStackIndex -= 1;
    }
    else {                                                                     //display ERROR as cannot add matrices with different dimensions

    }
}

void subtract(void) {                                                          //subtract complex numbers/matrices
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 45;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        //if (sigLength) enterComplex();                                         //if command line not empty
    	if (cmdL_Term) enterComplex();
        if (uStackIndex > 1) {                                                 //if at least two values on the user stack
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
        }
    }
}

void subtractMatrices(void) {
    unsigned int i;
    unsigned int j;

    if ((uStackMDim[uStackIndex][0] == uStackMDim[uStackIndex - 1][0]) && (uStackMDim[uStackIndex][1] == uStackMDim[uStackIndex - 1][1])) {
        i = indexLink[uStackIndex - 2] + 1;
        j = indexLink[uStackIndex - 1] + 1;

        for (i = indexLink[uStackIndex - 2] + 1; i <= indexLink[uStackIndex - 1]; i++) {
            uStackD[i] = uStackD[i] - uStackD[j];
            uStackDIMAG[i] = uStackDIMAG[i] - uStackDIMAG[j];
            j += 1;
        }

        uStackDIndex = indexLink[uStackIndex - 1];
        uStackIndex -= 1;
    }
    else {                                                                     //display ERROR as cannot subtract matrices with different dimensions

    }
}

void multiply(void) {                                                          //multiply complex numbers/matrices
    double temp;

    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 42;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        //if (sigLength) enterComplex();                                         //if command line not empty
    	if (cmdL_Term) enterComplex();
        if (uStackIndex > 1) {                                                 //if at least two values on the user stack
            if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
                if ((uStackType[uStackIndex]) && (uStackType[uStackIndex - 1])) multiplyMatrices();  //if matrices on top two levels
                else scalarMultiply();                                         //if matrix and complex number on top two levels
            }
            else {                                                             //if both entries complex numbers
                temp = uStackD[uStackDIndex-1] * uStackD[uStackDIndex] - uStackDIMAG[uStackDIndex-1] * uStackDIMAG[uStackIndex];
                uStackDIMAG[uStackDIndex-1] = uStackD[uStackDIndex-1] * uStackDIMAG[uStackDIndex] +
                        uStackDIMAG[uStackDIndex-1] * uStackD[uStackDIndex];
                uStackD[uStackDIndex-1] = temp;

                uStackDIndex -= 1;
                uStackIndex -= 1;
            }
        }
    }
}

void multiplyMatrices(void) {

}

void scalarMultiply(void) {

}

void divide(void) {
    double temp;

    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 47;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        //if (sigLength) enterComplex();                                         //if command line not empty
    	if (cmdL_Term) enterComplex();
        if (uStackIndex > 1) {                                                 //if at least two values on the user stack
            if ((uStackType[uStackIndex]) || (uStackType[uStackIndex - 1])) {  //if at least one matrix on top two levels
                if ((uStackType[uStackIndex] == 0) && (uStackType[uStackIndex - 1])) { //if scalar on level 1  and matrix on level 2

                    scalarMultiply();

                }
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
        }
    }
}
