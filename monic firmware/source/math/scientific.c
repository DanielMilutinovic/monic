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

extern unsigned char sigLength;

extern unsigned int uStackIndex;
extern unsigned int uStackDIndex;

extern unsigned char uStackType[stackDDepth];
extern double uStackD[stackDDepth];

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern unsigned int flag2;

//functions

void enterComplex(void);

///////////////////////////////////////////////////////////////////////////////

void reciprocal(void) {
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 49;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 47;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex) {                                                     //if user stack not empty
            if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = 1.0 / uStackD[uStackDIndex];
        }
        flag2 |= (STATUSLINEOFF | MENUOFF);
    }
}

void power(void) {
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 94;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex > 1) {                                                 //if at least two numbers on the stack
            if (uStackType[uStackIndex] == 0) {
                uStackD[uStackDIndex-1] = pow(uStackD[uStackDIndex-1], uStackD[uStackDIndex]);
                uStackDIndex--;
                uStackIndex--;
            }
        }
        flag2 |= (STATUSLINEOFF | MENUOFF);
    }
}

void powerR(void) {
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 94;                                                //CURRENTLY a^(1/, change to root symbol!!!!!!
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 40;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 49;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 47;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex > 1) {                                                 //if at least two numbers on the stack
            if (uStackType[uStackIndex] == 0) {
                uStackD[uStackDIndex-1] = pow(uStackD[uStackDIndex-1], 1.0 / uStackD[uStackDIndex]);
                uStackDIndex--;
                uStackIndex--;
            }
        }
        flag2 |= (STATUSLINEOFF | MENUOFF);
    }
}

void square(void) {
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 94;                                                //a^2
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 50;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex) {                                                     //if user stack not empty
            if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = uStackD[uStackDIndex] * uStackD[uStackDIndex];
        }
        flag2 |= (STATUSLINEOFF | MENUOFF);
    }
}

void squareRoot(void) {
    if (flag2 & ALGENTRY) {
        cmdL_S[cmdL_Term] = 94;                                                //a^(1/2)
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 40;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 49;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 47;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 50;
        cmdL_Term += 1;
        cmdL_S[cmdL_Term] = 41;
        cmdL_Term += 1;
        flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
    }
    else {
        if (cmdL_Term) enterComplex();                                         //if command line not empty
        if (uStackIndex) {                                                     //if user stack not empty
            if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = sqrt(uStackD[uStackDIndex]);
        }
        flag2 |= (STATUSLINEOFF | MENUOFF);
    }
}

void cubeRoot(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = '^';                                                //a^(1/3)
		cmdL_Term += 1;
		cmdL_S[cmdL_Term] = '(';
		cmdL_Term += 1;
		cmdL_S[cmdL_Term] = '1';
		cmdL_Term += 1;
		cmdL_S[cmdL_Term] = '/';
		cmdL_Term += 1;
		cmdL_S[cmdL_Term] = '3';
		cmdL_Term += 1;
		cmdL_S[cmdL_Term] = ')';
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = pow(uStackD[uStackIndex], 0.3333333333333333);
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void sine(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 129;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = sin(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = sin(uStackD[uStackIndex]/180.0*Pi);
					else uStackD[uStackIndex] = sin(uStackD[uStackIndex]/200.0*Pi);
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void cosine(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 130;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = cos(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = cos(uStackD[uStackIndex]/180.0*Pi);
					else uStackD[uStackIndex] = cos(uStackD[uStackIndex]/200.0*Pi);
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void tangent(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 131;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = tan(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = tan(uStackD[uStackIndex]/180.0*Pi);
					else uStackD[uStackIndex] = tan(uStackD[uStackIndex]/200.0*Pi);
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void arcsine(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 139;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = asin(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = asin(uStackD[uStackIndex])*180.0/Pi;
					else uStackD[uStackIndex] = asin(uStackD[uStackIndex])*200.0/Pi;
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void arccosine(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 140;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = acos(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = acos(uStackD[uStackIndex])*180.0/Pi;
					else uStackD[uStackIndex] = acos(uStackD[uStackIndex])*200.0/Pi;
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void arctangent(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 141;
		cmdL_Term += 1;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {
		if (cmdL_Term) enterComplex();                                         //if command line not empty
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) {
				if (flag2 & RADIAN)	uStackD[uStackIndex] = atan(uStackD[uStackIndex]);
				else {
					if (flag2 & DEGREE)	uStackD[uStackIndex] = atan(uStackD[uStackIndex])*180.0/Pi;
					else uStackD[uStackIndex] = atan(uStackD[uStackIndex])*200.0/Pi;
				}
			}
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void tenPower(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 135;
		cmdL_Term ++;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {                                                                     //RPN mode
		if (cmdL_Term) enterComplex();
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = pow(10.0,uStackD[uStackIndex]);
		}
	}
	flag2 |= (STATUSLINEOFF | MENUOFF);
}

void eulerPower(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 134;
		cmdL_Term ++;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {                                                                     //RPN mode
		if (cmdL_Term) enterComplex();
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = exp(uStackD[uStackIndex]);
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void PI(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 133;
		cmdL_Term ++;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {                                                                     //RPN mode
		if (cmdL_Term == 0) {
			cmdL_S[cmdL_Term] = 133;
			enterComplex();
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void logTen(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 137;
		cmdL_Term ++;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {                                                                     //RPN mode
		if (cmdL_Term) enterComplex();
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = log10(uStackD[uStackIndex]);
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}

void logEuler(void) {
	if (flag2 & ALGENTRY) {
		cmdL_S[cmdL_Term] = 138;
		cmdL_Term ++;
		flag2 |= (STATUSLINEOFF | STACKOFF | MENUOFF);
	}
	else {                                                                     //RPN mode
		if (cmdL_Term) enterComplex();
		if (uStackIndex) {                                                     //if user stack not empty
			if (uStackType[uStackIndex] == 0) uStackD[uStackDIndex] = log(uStackD[uStackIndex]);
		}
		flag2 |= (STATUSLINEOFF | MENUOFF);
	}
}
