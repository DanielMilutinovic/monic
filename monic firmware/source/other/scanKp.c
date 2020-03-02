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

#include <stdint.h>
#include <stdbool.h>
#include "pin_mux.h"
#include "board.h"

#include "../user.h"
#include "../header/globalVars.h"

//variables

unsigned char cursorWidth = 32;
unsigned char cursorHeight = 31;

int16_t xCoordinateCursor;
int32_t yCoordinateCursor;

extern int16_t page;

unsigned int cursorRateCtr;
_Bool cursorDisplayed;

uint32_t test;

extern unsigned int flag2;
extern unsigned char kpPlane;
extern unsigned int keyNumber;

//functions

void hideCursor(void);
void printCharactercmdL(char);
void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);

///////////////////////////////////////////////////////////////////////////////

void scanKp(void) {
	unsigned int i;
	cursorRateCtr = 1;
    cursorDisplayed = false;

	keyNumber = 0;

	for (i=0; i<8; i++) {
		test = GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN);
		//exit when GATE HIGH
		while (GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN)==0) {
			test = GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN);
			cursorRateCtr -= 1;
			if (cursorRateCtr == 0) {
				if (flag2 & CURSORON) {
					cursorRateCtr = cursorRate;
					if (cursorDisplayed) hideCursor();
					else {
						cursorDisplayed = true;
						fillRect(xCoordinateCursor, yCoordinateCursor, cursorWidth, cursorWidth, cursorColour);
					}
				}
			}
		}
		if (GPIO_PinRead(BOARD_DATA_56_04_PERIPHERAL, BOARD_DATA_56_04_CHANNEL)) {
			keyNumber = keyNumber>>1;
			keyNumber = keyNumber|0x80;          //DATA HIGH
		}
		else keyNumber = keyNumber>>1;           //DATA LOW

		test = GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN);
		//exit when GATE LOW
		while (GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN)) {
			test = GPIO_PinRead(BOARD_GATE_57_02_GPIO, BOARD_GATE_57_02_PIN);
		}
	}

	//keyNumber = 47 - keyNumber;   //keypad upside down
	///////////////////////////////////////////////////////////////////////////
	if (keyNumber > 47) keyNumber = 239 - keyNumber;                           //key held - keypad upside down
	else keyNumber = 47 - keyNumber;                                           //key not held - keypad upside down

	///////////////////////////////////////////////////////////////////////////
}

void hideCursor(void) {
    cursorDisplayed = false;

    fillRect(xCoordinateCursor, yCoordinateCursor, cursorWidth, cursorWidth, backgroundColour);

    switch (kpPlane) {
    case 6:
        printCharactercmdL(Cprg[CprgIndex]);
        break;
    default:
    	__asm volatile ("nop");
    }
}


