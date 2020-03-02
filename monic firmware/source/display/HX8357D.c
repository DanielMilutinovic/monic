//Port of Adafruit code to i.MX RT1010

/*Copyright (c) 2013 Adafruit Industries.  All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

- Redistributions of source code must retain the above copyright notice,
  this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.*/

//includes

#include <stdint.h>
#include <stdbool.h>

#include "board.h"

#include "pin_mux.h"
#include "clock_config.h"

#include "user.h"

//variables

int width;
int height;

//functions

void writeRegister32(uint8_t, uint32_t);
void writeRegister8(uint8_t, uint8_t);
void setAddrWindow(int, int, int, int);
void flood(uint16_t, uint32_t);
void setLR(void);
void writeRegisterPair(uint8_t, uint8_t, uint16_t);
void displayPortWrite(unsigned int);
void delayms(unsigned int);

///////////////////////////////////////////////////////////////////////////////

void initDisp(void) {
    uint8_t i;

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);
    GPIO_PinWrite(BOARD_WR_26_04_PERIPHERAL, BOARD_WR_26_04_CHANNEL, 1U);
    //GPIO_PinWrite(BOARD_RD_26_06_PERIPHERAL, BOARD_RD_26_06_CHANNEL, 1U);    //may be commented out if RD tied to 3.3V

    //reset

//    GPIO_PinWrite(BOARD_RST_56_04_PERIPHERAL, BOARD_RST_56_04_CHANNEL, 1U);  //block may be commented out if RST tied to 3.3V ->
//    //SysTick_DelayTicks(100U);
//    SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
//    GPIO_PinWrite(BOARD_RST_56_04_PERIPHERAL, BOARD_RST_56_04_CHANNEL, 0U);
//    //SysTick_DelayTicks(100U);
//    SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
//    GPIO_PinWrite(BOARD_RST_56_04_PERIPHERAL, BOARD_RST_56_04_CHANNEL, 1U);
//    //SysTick_DelayTicks(100U);
//    SDK_DelayAtLeastUs(100000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);  //<-

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(0x00);
    for (i = 0; i < 3; i++) displayPortWrite(0x00);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    //write to LCD registers

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SWRESET);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357D_SETC);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0xFF);
    displayPortWrite(0x83);
    displayPortWrite(0x57);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    //SysTick_DelayTicks(250U);
    //SDK_DelayAtLeastUs(250000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    delayms(250);

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SETRGB);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x00);
    displayPortWrite(0x00);
    displayPortWrite(0x06);
    displayPortWrite(0x06);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357D_SETCOM);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x25);                                                           //-1.52V
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SETOSC);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x68);                                                           //Normal mode 70Hz, Idle mode 55 Hz
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SETPANEL);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x05);                                                           //BGR, gate direction swapped
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SETPWR1);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x00);
    displayPortWrite(0x15);
    displayPortWrite(0x1C);
    displayPortWrite(0x1C);
    displayPortWrite(0x83);
    displayPortWrite(0xAA);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357D_SETSTBA);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x50);
    displayPortWrite(0x50);
    displayPortWrite(0x01);
    displayPortWrite(0x3C);
    displayPortWrite(0x1E);
    displayPortWrite(0x08);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357D_SETCYC);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x02);
    displayPortWrite(0x40);
    displayPortWrite(0x00);
    displayPortWrite(0x2A);
    displayPortWrite(0x2A);
    displayPortWrite(0x0D);
    displayPortWrite(0x78);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_COLMOD);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x55);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_MADCTL);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0xC0);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_TEON);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x00);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_TEARLINE);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(0x00);
    displayPortWrite(0x02);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_SLPOUT);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    //SysTick_DelayTicks(150U);
    //SDK_DelayAtLeastUs(150000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    delayms(150);

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(HX8357_DISPON);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE

    //SysTick_DelayTicks(50U);
    //SDK_DelayAtLeastUs(50000, SDK_DEVICE_MAXIMUM_CPU_CLOCK_FREQUENCY);
    delayms(50);
}

//void displayPortWrite(uint8_t x) {
//    GPIOPinWrite(LCD_8bitParallel_BASE, cd0|cd1|cd2|cd3|cd4|cd5|cd6|cd7, x);
//    GPIOPinWrite(LCD_control_BASE, LCD_WR , 0);
//    GPIOPinWrite(LCD_control_BASE, LCD_WR , LCD_WR);
//}

void setAddrWindow(int x1,int y1, int x2, int y2) {
    uint32_t t;

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE

    t = x1;
    t <<= 16;
    t |= x2;
    writeRegister32(ILI9341_COLADDRSET, t);                                    // HX8357D uses same registers!
    t = y1;
    t <<= 16;
    t |= y2;
    writeRegister32(ILI9341_PAGEADDRSET, t);                                   // HX8357D uses same registers!

    //GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void writeRegister8(uint8_t a, uint8_t d) {
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(a);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(d);
}

void writeRegister32(uint8_t r, uint32_t d) {
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(r);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    //SysCtlDelay(10 * delay1us);
    //SysTick_DelayTicks(10U);
    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    //__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    displayPortWrite(d >> 24);
    //SysCtlDelay(10 * delay1us);
    //SysTick_DelayTicks(10U);
    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    //__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    displayPortWrite(d >> 16);
    //SysCtlDelay(10 * delay1us);
    //SysTick_DelayTicks(10U);
    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    //__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    displayPortWrite(d >> 8);
    //SysCtlDelay(10 * delay1us);
    //SysTick_DelayTicks(10U);
    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    //__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
//    __asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");__asm volatile ("nop");
    displayPortWrite(d);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void flood(uint16_t colour, uint32_t len) {
    uint16_t blocks;
    uint8_t  i, hi = colour >> 8, lo = colour;

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND

    displayPortWrite(HX8357_RAMWR);

    // Write first pixel normally, decrement counter by 1
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(hi);
    displayPortWrite(lo);
    len--;

    blocks = (uint16_t)(len / 64);                                             //64 pixels/block
    if(hi == lo) {
        // High and low bytes are identical.  Leave prior data
        // on the port(s) and just toggle the write strobe.
        while(blocks--) {
            i = 16;                                                            //64 pixels/block/4 pixels/pass
            do {
                displayPortWrite(lo); displayPortWrite(lo); displayPortWrite(lo); displayPortWrite(lo);    //2 bytes/pixel
                displayPortWrite(lo); displayPortWrite(lo); displayPortWrite(lo); displayPortWrite(lo);    //x 4 pixels
            } while(--i);
        }
        // Fill any remaining pixels (1 to 64)
        for(i = (uint8_t)len & 63; i--; ) {
            displayPortWrite(lo);
            displayPortWrite(lo);
        }
    } else {
        while(blocks--) {
            i = 16; // 64 pixels/block / 4 pixels/pass
            do {
                displayPortWrite(hi); displayPortWrite(lo); displayPortWrite(hi); displayPortWrite(lo);
                displayPortWrite(hi); displayPortWrite(lo); displayPortWrite(hi); displayPortWrite(lo);
            } while(--i);
        }
        for(i = (uint8_t)len & 63; i--; ) {
            displayPortWrite(hi);
            displayPortWrite(lo);
        }
    }
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void drawFastVLine(int16_t x, int16_t y, int16_t length, uint16_t colour) {
    int16_t y2;

    // Initial off-screen clipping
    if((length <= 0) || (x<0) || ( x>= width) || (y>= height) || ((y2 = (y+length-1)) < 0)) return;
    if(y < 0) {                                                                // Clip top
        length += y;
        y = 0;
    }

    if(y2 >= height) {                                                      // Clip bottom
        y2 = height - 1;
        length  = y2 - y + 1;
    }

    setAddrWindow(x, y, x, y2);
    flood(colour, length);
    setLR();
}

void drawFastHLine(int16_t x, int16_t y, int16_t length, uint16_t colour) {
    int16_t x2;

    // Initial off-screen clipping
    if((length <= 0) || (y<0) || (y>= height) || (x>= width) || ((x2 = (x+length-1)) <  0)) return;
    if(x < 0) {                                                                // Clip left
        length += x;
        x = 0;
    }
    if(x2 >= width) {                                                       // Clip right
        x2 = width - 1;
        length = x2 - x + 1;
    }

    setAddrWindow(x, y, x2, y);
    flood(colour, length);
    setLR();
}

void setLR(void) {
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    writeRegisterPair(HX8347G_COLADDREND_HI, HX8347G_COLADDREND_LO, width  - 1);
    writeRegisterPair(HX8347G_ROWADDREND_HI, HX8347G_ROWADDREND_LO, height - 1);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void writeRegisterPair(uint8_t aH, uint8_t aL, uint16_t d) {
    uint8_t hi = (d) >> 8, lo = (d);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(aH);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(hi);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(aL);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(lo);
}

void drawPixel(int16_t x, int16_t y, uint16_t colour) {

    // Clip
    if((x < 0) || (y < 0) || (x >= width) || (y >= height)) return;

    setAddrWindow(x, y, width-1, height-1);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 0U);                                 //COMMAND
    displayPortWrite(0x2C);
    GPIO_PinWrite(BOARD_CD_26_08_PERIPHERAL, BOARD_CD_26_08_CHANNEL, 1U);                           //DATA
    displayPortWrite(colour >> 8);
    displayPortWrite(colour);

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void setRotation(uint8_t x) {
    uint8_t t;

    x = (x & 3);

    switch (x) {
    case 0:
    case 2:
        width = TFTWIDTH;
        height = TFTHEIGHT;
        break;
    case 1:
    case 3:
        width = TFTHEIGHT;
        height = TFTWIDTH;
        break;
    }

    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 0U);                                //CS ACTIVE

    //HX8357D uses same registers as 9341 but different values
    switch (x) {
    case 2:
        t = HX8357B_MADCTL_RGB;
        break;
    case 3:
        t = HX8357B_MADCTL_MX | HX8357B_MADCTL_MV | HX8357B_MADCTL_RGB;
        break;
    case 0:
        t = HX8357B_MADCTL_MX | HX8357B_MADCTL_MY | HX8357B_MADCTL_RGB;
        break;
    case 1:
        t = HX8357B_MADCTL_MY | HX8357B_MADCTL_MV | HX8357B_MADCTL_RGB;
        break;
    }
    writeRegister8(ILI9341_MADCTL, t);                                         //MADCTL

    // For 8357, init default full-screen address window:
    setAddrWindow(0, 0, width - 1, height - 1);
    GPIO_PinWrite(BOARD_CS_26_2_PERIPHERAL, BOARD_CS_26_2_CHANNEL, 1U);                            //CS IDLE
}

void displayPortWrite(unsigned int x) {
	uint32_t setBitMask;
	uint32_t clrBitMask;

    setBitMask = ((x & 0x01) << 1) | ((x & 0x02) << (2-1)) | ((x & 0x04) << (15-2)) | ((x & 0x08) << (16-3)) | ((x & 0x10) << (17-4)) | ((x & 0x20) << (18-5)) | ((x & 0x40) << (19-6)) | ((x & 0x80) << (20-7));
    clrBitMask = ((~x & 0x01) << 1) | ((~x & 0x02) << (2-1)) | ((~x & 0x04) << (15-2)) | ((~x & 0x08) << (16-3)) | ((~x & 0x10) << (17-4)) | ((~x & 0x20) << (18-5)) | ((~x & 0x40) << (19-6)) | ((~x & 0x80) << (20-7));

	GPIO_PortSet(GPIO1, setBitMask);
	GPIO_PortClear(GPIO1, clrBitMask);

	//__asm volatile ("nop");

    GPIO_PinWrite(BOARD_WR_26_04_PERIPHERAL, BOARD_WR_26_04_CHANNEL, 0U);
    //__asm volatile ("nop");
    GPIO_PinWrite(BOARD_WR_26_04_PERIPHERAL, BOARD_WR_26_04_CHANNEL, 1U);
}

