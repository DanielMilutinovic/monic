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

#include <stdint.h>
#include <stdbool.h>

#include "../user.h"

#include "clock_config.h"

//structures

//struct tt {
//	char question[5];
//	unsigned int answer;
//};

struct tt {
	char question[7];
	char answer[3];
};

//extern struct tt;

//variables

extern unsigned char kpPlane;
extern unsigned int flag2;

extern struct tt ttquestions[];
extern unsigned char QNO;

extern unsigned char cmdL_S[cmdL_SLength];
extern unsigned char cmdL_Term;

extern _Bool flag;

//extern unsigned int elapsedTime;
//
//extern int16_t xCoordinate;
//extern int16_t yCoordinate;

//functions

//void displayPrgStep(unsigned int);

///////////////////////////////////////////////////////////////////////////////

void kpTimesTables(unsigned int x) {
	unsigned char i;

	switch (x) {
	case zeroTimesTables:                                                      //ZERO
		cmdL_S[cmdL_Term] = '0';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case oneTimesTables:                                                       //ONE
		cmdL_S[cmdL_Term] = '1';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case twoTimesTables:                                                       //TWO
		cmdL_S[cmdL_Term] = '2';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case threeTimesTables:                                                     //THREE
		cmdL_S[cmdL_Term] = '3';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case fourTimesTables:                                                      //FOUR
		cmdL_S[cmdL_Term] = '4';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case fiveTimesTables:                                                      //FIVE
		cmdL_S[cmdL_Term] = '5';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case sixTimesTables:                                                       //SIX
		cmdL_S[cmdL_Term] = '6';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case sevenTimesTables:                                                     //SEVEN
		cmdL_S[cmdL_Term] = '7';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case eightTimesTables:                                                     //EIGHT
		cmdL_S[cmdL_Term] = '8';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case nineTimesTables:                                                      //NINE
		cmdL_S[cmdL_Term] = '9';
		cmdL_Term ++;
		flag2 |= STATUSLINEOFF;
		break;
	case deleteTimesTables:
		cmdL_Term --;
		cmdL_S[cmdL_Term] = 0;
		flag2 |= STATUSLINEOFF;
		break;
	case exitTimesTables:
		kpPlane = 0;
		SysTick->CTRL = 0x00;
		break;
	case enterTimesTables:
		flag = true;
		for(i=0;i<3;i++) {
			if (cmdL_S[i] != ttquestions[QNO].answer[i]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			for(i=0;i<3;i++) cmdL_S[i] = 0;
			cmdL_Term = 0;
			QNO++;
		}
		break;
	default:
		__asm volatile ("nop");
	}
}
