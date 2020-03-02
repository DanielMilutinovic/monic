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

#include "../user.h"
#include "../header/globalVars.h"

//variables

extern unsigned char menu;
extern unsigned char kpPlane;

extern unsigned int flag1;
extern unsigned int flag2;

extern int16_t xCoordinate;
extern int16_t yCoordinate;

extern int16_t xCoordinateCursor;
extern int16_t yCoordinateCursor;

//extern uint8_t const *fontData;
//extern uint32_t const *fontOffset;
//
//extern unsigned char cursorWidth;
//extern unsigned char cursorHeight;

extern uint32_t fontColour;

//functions

void drawRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void printString(char*);
void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);

//constants

extern const unsigned int keyOffset[];

///////////////////////////////////////////////////////////////////////////////

void kpHLPrg(unsigned int x) {
    switch (x) {
    case shiftKSPrg:                                                           //SHIFT
    	flag1 |= SHIFT;
    	flag2 |= (STACKOFF | MENUOFF | COMMANDLINEOFF);
    	break;
    case A_SINKSPrg:
    case B_COSKSPrg:
    case C_TANKSPrg:
    case D_ToDMSKSPrg:
    case E_PIKSPrg:
    case F_KSPrg:
        Cprg[CprgIndex] = keyOffset[x] + 65;
        CprgIndex++;
        if (xCoordinateCursor == 318) {
            xCoordinateCursor = 0;
            yCoordinateCursor += 8;
        }
        break;
    case leftArrow:
        if (xCoordinateCursor) {
            CprgIndex--;
            flag2 |= CeditorArrow;
            xCoordinateCursor -= 6;
        }
        break;
    case rigthArrow:
        if (xCoordinateCursor < 312) {
            CprgIndex++;
            flag2 |= CeditorArrow;
            xCoordinateCursor += 6;
        }
        break;
    case upKSPrg:
        if (yCoordinateCursor) {
            CprgIndex -= 53;
            flag2 |= CeditorArrow;
            yCoordinateCursor -= 8;
        }
        break;
    case downKSPrg:
        if (yCoordinateCursor < 232) {
            CprgIndex += 53;
            flag2 |= CeditorArrow;
            xCoordinateCursor += 8;
        }
        break;
    case mainHLPrg:                                                            //main()
    	fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordStatLBottom - yCoordStatLTop + 2, backgroundColour);
    	fontColour = WHITE;
    	yCoordinate = yCoordStatLTop;
    	xCoordinate = 0;
    	printString("int main(void) {");

    	yCoordinate = yCoordLvl4Top;
    	xCoordinate = 0;
    	printString("}");
    	yCoordinateCursor = yCoordLvl5Top;
    	xCoordinateCursor = 40;
    	break;
    case exitKSPrg:                                                            //EXIT
        switch (menu) {
        case 0:                                                                //exit C program edit mode
            kpPlane = 0;
            menu = 0;
            //fontData = cmss20bData;
            //fontOffset = cmss20bOffset;
            //cursorWidth = 16;
            //cursorHeight = 29;
            //RectFill(0, max_xCoord, yCoordStatLBottom + 1, yCoordLvl5Top - 1, backgroundColour);
            //fillRect(0, yCoordStatLTop, TFTHEIGHT, yCoordCmdLBottom - yCoordStatLTop, backgroundColour);
            break;
        default:
            menu = 0;                                                          //return to C program edit home menu
        }
        break;
    }
}
