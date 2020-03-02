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

//Dijkstra's shunting yard algorithm to parse ASCII string when in algebraic entry mode

//includes

#include <math.h>

#include "../user.h"

//variables

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

double cmdLNumber[cmdLNumberLength];

extern unsigned int cmdL_Parsed[cmdL_ParsedLength];

extern unsigned int flag1;

extern double valueCmdL_SigD;
extern double valueCmdL_ExpD;
extern double valueCmdL_D;
extern double decDigits;
extern unsigned char sigLength;
extern unsigned char expLength;

unsigned char cmdLNumberCtr;
unsigned char cmdL_ParsedCtr;

unsigned char cmdLOprt[cmdLOprtLength];
unsigned char cmdLOprtCtr;

extern unsigned int uStackDIndex;                                              //complex user stack index
extern double uStackD[stackDDepth];                                            //array to store real part

//functions

void updateValueCmdL_SigD(double);
void updateValueCmdL_ExpD(double);

void shuntLA(unsigned char);
void shuntRA(unsigned char);
void shuntRA_Unary(unsigned char);

void pushCmdLNumb(void);

unsigned char priority(unsigned char);
unsigned int ASCII_toIstr(unsigned char);

///////////////////////////////////////////////////////////////////////////////

void enterAlgebraic(void) {
    unsigned char i;

    cmdL_Term = 0;
    cmdLNumberCtr = 0;
    cmdL_ParsedCtr = 0;
    cmdLOprtCtr = 0;

    while (cmdL_S[cmdL_Term]) {
        switch (cmdL_S[cmdL_Term]) {
        case 40:                                                                         //(
            cmdLOprtCtr += 1;
            cmdLOprt[cmdLOprtCtr] = 40;
            break;
        case 41:                                                                         //)
            pushCmdLNumb();
            while (cmdLOprt[cmdLOprtCtr]!= 40) {
                cmdL_Parsed[cmdL_ParsedCtr] = ASCII_toIstr(cmdLOprt[cmdLOprtCtr]);
                cmdL_ParsedCtr += 1;
                cmdLOprtCtr -= 1;
            }
            cmdLOprtCtr -= 1;
            break;
        case 42:                                                                         //*
            shuntLA(cmdL_S[cmdL_Term]);
            break;
        case 43:                                                                         //+
            shuntLA(cmdL_S[cmdL_Term]);
            break;
        case 45:                                                                         //-
            shuntLA(cmdL_S[cmdL_Term]);
            break;
        case 47:                                                                         //division
            shuntLA(cmdL_S[cmdL_Term]);
            break;
        case 46:                                                                         //decimal point
            if (sigLength == 0) {
                sigLength = 1;
                flag1 |= DECPOINT;
            }
            else {
                if ((flag1 & DECPOINT) == 0) flag1 |= DECPOINT;
            }
            flag1 &= ~ZEROFIRST;
            break;
        case 48:                                                                         //0
            if (flag1 & EXP) updateValueCmdL_ExpD(0.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(0.0);
                if (sigLength == 0) flag1 |= ZEROFIRST;
            }
            break;
        case 49:                                                                         //1
            if (flag1 & EXP) updateValueCmdL_ExpD(1.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(1.0);
            }
            break;
        case 50:                                                                         //2
            if (flag1 & EXP) updateValueCmdL_ExpD(2.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(2.0);
            }
            break;
        case 51:                                                                         //3
            if (flag1 & EXP) updateValueCmdL_ExpD(3.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(3.0);
            }
            break;
        case 52:                                                                         //4
            if (flag1 & EXP) updateValueCmdL_ExpD(4.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(4.0);
            }
            break;
        case 53:                                                                         //5
            if (flag1 & EXP) updateValueCmdL_ExpD(5.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(5.0);
            }
            break;
        case 54:                                                                         //6
            if (flag1 & EXP) updateValueCmdL_ExpD(6.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(6.0);
            }
            break;
        case 55:                                                                         //7
            if (flag1 & EXP) updateValueCmdL_ExpD(7.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(7.0);
            }
            break;
        case 56:                                                                         //8
            if (flag1 & EXP) updateValueCmdL_ExpD(8.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(8.0);
            }
            break;
        case 57:                                                                         //9
            if (flag1 & EXP) updateValueCmdL_ExpD(9.0);
            else {
                if ((flag1 & ZEROFIRST) == 0) updateValueCmdL_SigD(9.0);
            }
            break;
        case 94:                                                                         //^
            shuntRA(cmdL_S[cmdL_Term]);
            break;
        case 128:                                                                        //+/-
            //if (flag1 & NEGSIG) flag1 &= ~NEGSIG;
            //else flag1|= NEGSIG;
        	shuntRA_Unary(cmdL_S[cmdL_Term]);
            break;
        case 129:                                                                        //sin(x)
            shuntRA_Unary(cmdL_S[cmdL_Term]);
            break;
        case 130:                                                                        //cos(x)
            shuntRA_Unary(cmdL_S[cmdL_Term]);
            break;
        case 131:                                                                        //tan(x)
            shuntRA_Unary(cmdL_S[cmdL_Term]);
            break;
        case 132:                                                                        //ans
            flag1|= ANS;
            break;
        case 133:                                                                        //PI
        	valueCmdL_SigD = Pi;
        	break;
        case 134:                                                              //e^x
        	//valueCmdL_SigD = e;
        	//shuntRA(94);
        	shuntRA(cmdL_S[cmdL_Term]);
        	break;
        case 135:                                                              //10^x
        	//valueCmdL_SigD = 10.0;
        	//shuntRA(94);
        	shuntRA(cmdL_S[cmdL_Term]);
        	break;
        case 136:                                                              //exponent = *10^x
        	shuntLA(42);
        	//valueCmdL_SigD = 10.0;
        	//shuntRA(94);
        	shuntRA(135);
        	break;
        case 137:                                                              //log(x)
			shuntRA_Unary(cmdL_S[cmdL_Term]);
        	break;
        case 138:                                                              //ln(x)
        	shuntRA_Unary(cmdL_S[cmdL_Term]);
        	break;
        case 139:                                                              //asin(x)
        	shuntRA_Unary(cmdL_S[cmdL_Term]);
        	break;
        case 140:                                                              //acos(x)
        	shuntRA_Unary(cmdL_S[cmdL_Term]);
        	break;
        case 141:                                                              //atan(x)
        	shuntRA_Unary(cmdL_S[cmdL_Term]);
        	break;
        }
        cmdL_Term += 1;
    }

    if (cmdL_S[cmdL_Term-1] != 41) pushCmdLNumb();                             //if does not end with ")"

    for(i = cmdLOprtCtr; i > 0; i--) {
        cmdL_Parsed[cmdL_ParsedCtr] = ASCII_toIstr(cmdLOprt[i]);
        cmdL_ParsedCtr += 1;
    }
    cmdL_Parsed[cmdL_ParsedCtr] = END;
}

void shuntLA(unsigned char x) {
    if (cmdL_S[cmdL_Term-1] != 41) pushCmdLNumb();                             //push if previous token not ")"

    while (cmdLOprtCtr) {
        if (cmdLOprt[cmdLOprtCtr] == 40) break;
        if (priority(cmdLOprt[cmdLOprtCtr]) >= priority(x)) {
            cmdL_Parsed[cmdL_ParsedCtr] = ASCII_toIstr(cmdLOprt[cmdLOprtCtr]);
            cmdL_ParsedCtr += 1;
            cmdLOprtCtr -= 1;
        }
        else break;
    }

    cmdLOprtCtr += 1;
    cmdLOprt[cmdLOprtCtr] = x;
}

void shuntRA(unsigned char x) {
    if (cmdL_S[cmdL_Term-1] != 41) pushCmdLNumb();                             //push if previous token not ")"

    while (cmdLOprtCtr) {
        if (cmdLOprt[cmdLOprtCtr] == 40) break;
        if (priority(cmdLOprt[cmdLOprtCtr]) > priority(x)) {
            cmdL_Parsed[cmdL_ParsedCtr] = ASCII_toIstr(cmdLOprt[cmdLOprtCtr]);
            cmdL_ParsedCtr += 1;
            cmdLOprtCtr -= 1;
        }
        else break;
    }

    cmdLOprtCtr += 1;
    cmdLOprt[cmdLOprtCtr] = x;
}

void shuntRA_Unary(unsigned char x) {
    while (cmdLOprtCtr) {
        if (cmdLOprt[cmdLOprtCtr] == 40) break;
        if (priority(cmdLOprt[cmdLOprtCtr]) > priority(x)) {
            cmdL_Parsed[cmdL_ParsedCtr] = ASCII_toIstr(cmdLOprt[cmdLOprtCtr]);
            cmdL_ParsedCtr += 1;
            cmdLOprtCtr -= 1;
        }
        else break;
    }

    cmdLOprtCtr += 1;
    cmdLOprt[cmdLOprtCtr] = x;
}

void pushCmdLNumb(void) {
    if (flag1 & ANS) {                                                         //ANS
        cmdLNumber[cmdLNumberCtr] = uStackD[uStackDIndex];
        cmdL_Parsed[cmdL_ParsedCtr] = 6000 + cmdLNumberCtr;
        cmdLNumberCtr += 1;
        cmdL_ParsedCtr += 1;

        flag1 &= ~ANS;
    }
    else {
    if (flag1 & NEGEXP) valueCmdL_ExpD = -valueCmdL_ExpD;
    valueCmdL_D = valueCmdL_SigD * pow(10.0,valueCmdL_ExpD - decDigits);
    if (flag1 & NEGSIG) valueCmdL_D = -valueCmdL_D;

    flag1 = 0;                                                                 //reset ready for next value to be entered
    sigLength = 0;
    expLength = 0;
    valueCmdL_SigD = 0.0;
    valueCmdL_ExpD = 0.0;
    decDigits = 0.0;                                                           //<-

    cmdLNumber[cmdLNumberCtr] = valueCmdL_D;
    cmdL_Parsed[cmdL_ParsedCtr] = 6000 + cmdLNumberCtr;
    cmdLNumberCtr += 1;
    cmdL_ParsedCtr += 1;
    }
}

unsigned char priority(unsigned char x) {
    unsigned char i;
    switch (x) {
    case 40:                                                                             //(
        i = 5;
        break;
    case 41:                                                                             //)
        i = 5;
        break;
    case 42:                                                                             //*
        i = 2;
        break;
    case 43:                                                                             //+
        i = 1;
        break;
    case 45:                                                                             //-
        i = 1;
        break;
    case 47:                                                                             // /
        i = 2;
        break;
    case 94:                                                                             //^
        i = 4;
        break;
    case 128:                                                                            //+/-
    	i = 3;
    	break;
    case 129:                                                                            //sin(x)
        i = 3;
        break;
    case 130:                                                                            //cos(x)
        i = 3;
        break;
    case 131:                                                                            //tan(x)
        i = 3;
        break;
    case 134:                                                                            //e^x
    	i = 4;
    	break;
    case 135:                                                                            //10^x
    	i = 4;
    	break;
    case 137:                                                                  //log(x)
    	i = 3;
    	break;
    case 138:                                                                  //ln(x)
    	i = 3;
    	break;
    case 139:                                                                  //asin(x)
    	i = 3;
    	break;
    case 140:                                                                  //acos(x)
    	i = 3;
    	break;
    case 141:                                                                  //atan(x)
    	i = 3;
    	break;
    }
    return i;
}

unsigned int ASCII_toIstr(unsigned char x) {
    unsigned char i;
    switch (x) {
    case 42:                                                                             //*
        i = multiplyKSPrg;
        break;
    case 43:                                                                             //+
        i = addKSPrg;
        break;
    case 45:                                                                             //-
        i = subtractKSPrg;
        break;
    case 47:                                                                             // /
        i = divideKSPrg;
        break;
    case 94:                                                                             // ^
        i = powerKSPrg;
        break;
    case 128:                                                                            //+/-
    	i = negateKSPrg;
    	break;
    case 129:                                                                            //sin(x)
        i = A_SINKSPrg;
        break;
    case 130:                                                                            //cos(x)
        i = B_COSKSPrg;
        break;
    case 131:                                                                            //tan(x)
        i = C_TANKSPrg;
        break;
    case 134:                                                                            //e^x
    	i = eulerPowerKSPrg;
    	break;
    case 135:                                                                            //10^x
    	i = tenPowerKSPrg;
    	break;
    case 137:                                                                  //log(x)
    	i = logTenKSPrg;
    	break;
    case 138:                                                                  //ln(x)
    	i = lnKSPrg;
    	break;
    case 139:                                                                  //asin(x)
    	i = arcSinKSPrg;
    	break;
    case 140:                                                                  //acos(x)
    	i = arcCosKSPrg;
    	break;
    case 141:                                                                  //atan(x)
    	i = arcTanKSPrg;
    	break;
    }
    return i;
}
