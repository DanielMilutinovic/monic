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
#include <stdlib.h>

#include "user.h"

//variables

extern int width;
extern int height;

extern uint8_t const *fontData;
extern uint32_t const *fontOffset;

extern int16_t xCoordinate;
extern int16_t yCoordinate;

extern int16_t xCoordinateCursor;
extern int16_t yCoordinateCursor;

extern uint16_t fontColour;

extern uint8_t size;

//functions

void fillScreen(uint16_t);
void setAddrWindow(int, int, int, int);
void flood(uint16_t, uint32_t);
void drawLine(int16_t, int16_t, int16_t, int16_t, uint16_t);
void drawFastVLine(int16_t, int16_t, int16_t, uint16_t);
void drawFastHLine(int16_t, int16_t, int16_t, uint16_t);
void writeLine(int16_t, int16_t, int16_t, int16_t, uint16_t);
void drawPixel(int16_t, int16_t, uint16_t);
void drawRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void fillRect(int16_t, int16_t, int16_t, int16_t, uint16_t);
void setLR(void);
void fillCircle(int16_t, int16_t, int16_t, uint16_t);
void fillCircleHelper(int16_t, int16_t, int16_t, uint8_t, int16_t, uint16_t);
void drawCircle(int16_t, int16_t, int16_t, uint16_t);
void drawTriangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, uint16_t);
uint16_t colour565(uint8_t r, uint8_t g, uint8_t b);
void fillTriangle(int16_t, int16_t, int16_t, int16_t, int16_t, int16_t, uint16_t);
void drawRoundRect(int16_t, int16_t, int16_t, int16_t, int16_t, uint16_t);
void drawCircleHelper(int16_t, int16_t, int16_t, uint8_t, uint16_t);
void fillRoundRect(int16_t, int16_t, int16_t, int16_t, int16_t, uint16_t);

void printCharacter(char);
void printCharacterFW(char);
void printCharacterVW(char);

void printString(char*);
void printStringFW(char*);
void printStringVW(char*);

void printStringRight(char*);
void printStringRightFW(char*);
void printStringRightVW(char*);

void printCharactercmdL(char);
void printCharactercmdLFW(char);
void printCharactercmdLVW(char);

void printStringcmdL(char*);
void printStringcmdLFW(char*);
void printStringcmdLVW(char*);

///////////////////////////////////////////////////////////////////////////////

void testFillScreen(void) {
  fillScreen(BLACK);
  fillScreen(RED);
  fillScreen(GREEN);
  fillScreen(BLUE);
  fillScreen(BLACK);
}

void fillScreen(uint16_t colour) {
    setAddrWindow(0, 0, width - 1, height - 1);
    flood(colour, (long)TFTWIDTH * (long)TFTHEIGHT);
}

void testLines(uint16_t colour) {
  int           x1, y1, x2, y2,
                w = width,
                h = height;

  fillScreen(BLACK);

  x1 = y1 = 0;
  y2 = h - 1;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, colour);
  x2 = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, colour);

  fillScreen(BLACK);

  x1 = w - 1;
  y1 = 0;
  y2 = h - 1;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, colour);
  x2 = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, colour);

  fillScreen(BLACK);

  x1 = 0;
  y1 = h - 1;
  y2 = 0;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, colour);
  x2 = w - 1;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, colour);

  fillScreen(BLACK);

  x1 = w - 1;
  y1 = h - 1;
  y2 = 0;
  for(x2=0; x2<w; x2+=6) drawLine(x1, y1, x2, y2, colour);
  x2 = 0;
  for(y2=0; y2<h; y2+=6) drawLine(x1, y1, x2, y2, colour);
}

void testFastLines(uint16_t colour1, uint16_t colour2) {
  int x, y, w = width, h = height;

  fillScreen(BLACK);
  for(y=0; y<h; y+=5) drawFastHLine(0, y, w, colour1);
  for(x=0; x<w; x+=5) drawFastVLine(x, 0, h, colour2);
}

void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) {
    if(x0 == x1){
        if(y0 > y1) _swap_int16_t(y0, y1);
        drawFastVLine(x0, y0, y1 - y0 + 1, colour);
    } else if(y0 == y1){
        if(x0 > x1) _swap_int16_t(x0, x1);
        drawFastHLine(x0, y0, x1 - x0 + 1, colour);
    } else {
        writeLine(x0, y0, x1, y1, colour);
    }
}

void writeLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) {

    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        _swap_int16_t(x0, y0);
        _swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
        _swap_int16_t(x0, x1);
        _swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
            drawPixel(y0, x0, colour);
        } else {
            drawPixel(x0, y0, colour);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void testRects(uint16_t colour) {
    int n, i, i2, cx = width/2, cy = height/2;

    fillScreen(BLACK);
    n = min(width, height);
    for(i=2; i<n; i+=6) {
        i2 = i/2;
        drawRect(cx-i2, cy-i2, i, i, colour);
    }
}

void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour) {
    drawFastHLine(x, y, w, colour);
    drawFastHLine(x, y+h-1, w, colour);
    drawFastVLine(x, y, h, colour);
    drawFastVLine(x+w-1, y, h, colour);
}

void testFilledRects(uint16_t colour1, uint16_t colour2) {
    int n, i, i2, cx = width/2 - 1, cy = height/2 - 1;

    fillScreen(BLACK);
    n = min(width, height);
    for(i=n; i>0; i-=6) {
        i2 = i/2;
        fillRect(cx-i2, cy-i2, i, i, colour1);
        drawRect(cx-i2, cy-i2, i, i, colour2);
    }
}

void fillRect(int16_t x1, int16_t y1, int16_t w, int16_t h, uint16_t fillcolour) {
    int16_t  x2, y2;

    // Initial off-screen clipping
    if( (w <= 0) || (h <= 0) || (x1 >= width) || (y1 >= height) || ((x2 = x1+w-1) < 0) || ((y2  = y1+h-1) < 0)) return;
    if(x1 < 0) {                                                               //Clip left
        w += x1;
        x1 = 0;
    }
    if(y1 < 0) {                                                               //Clip top
        h += y1;
        y1 = 0;
    }
    if(x2 >= width) {                                                          //Clip right
        x2 = width - 1;
        w  = x2 - x1 + 1;
    }
    if(y2 >= height) {                                                         //Clip bottom
        y2 = height - 1;
        h  = y2 - y1 + 1;
    }

    setAddrWindow(x1, y1, x2, y2);
    flood(fillcolour, (uint32_t)w * (uint32_t)h);
    setLR();
}

void testFilledCircles(uint8_t radius, uint16_t colour) {

    int x, y, w = width, h = height, r2 = radius * 2;

    fillScreen(BLACK);

    for(x=radius; x<w; x+=r2) {
        for(y=radius; y<h; y+=r2) {
            fillCircle(x, y, radius, colour);
        }
    }
}

void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t colour) {
    drawFastVLine(x0, y0-r, 2*r+1, colour);
    fillCircleHelper(x0, y0, r, 3, 0, colour);
}

void fillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t corners, int16_t delta, uint16_t colour) {

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;
    int16_t px = x;
    int16_t py = y;

    delta++; // Avoid some +1's in the loop

    while(x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        // These checks avoid double-drawing certain lines, important
        // for the SSD1306 library which has an INVERT drawing mode.
        if(x < (y + 1)) {
            if(corners & 1) drawFastVLine(x0+x, y0-y, 2*y+delta, colour);
            if(corners & 2) drawFastVLine(x0-x, y0-y, 2*y+delta, colour);
        }
        if(y != py) {
            if(corners & 1) drawFastVLine(x0+py, y0-px, 2*px+delta, colour);
            if(corners & 2) drawFastVLine(x0-py, y0-px, 2*px+delta, colour);
            py = y;
        }
        px = x;
    }
}

void testCircles(uint8_t radius, uint16_t colour) {

    int x, y, r2 = radius * 2, w = width + radius, h = height + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.

    for(x=0; x<w; x+=r2) {
        for(y=0; y<h; y+=r2) {
            drawCircle(x, y, radius, colour);
        }
    }
}

void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t colour) {

    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    drawPixel(x0, y0+r, colour);
    drawPixel(x0, y0-r, colour);
    drawPixel(x0+r, y0, colour);
    drawPixel(x0-r, y0, colour);

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        drawPixel(x0 + x, y0 + y, colour);
        drawPixel(x0 - x, y0 + y, colour);
        drawPixel(x0 + x, y0 - y, colour);
        drawPixel(x0 - x, y0 - y, colour);
        drawPixel(x0 + y, y0 + x, colour);
        drawPixel(x0 - y, y0 + x, colour);
        drawPixel(x0 + y, y0 - x, colour);
        drawPixel(x0 - y, y0 - x, colour);
    }
}

void testTriangles(void) {

    int n, i, cx = width / 2 - 1, cy = height/ 2 - 1;

    fillScreen(BLACK);
    n = min(cx, cy);
    for(i=0; i<n; i+=5) {
        drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, colour565(0, 0, i));
    }
}

void drawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour) {
    drawLine(x0, y0, x1, y1, colour);
    drawLine(x1, y1, x2, y2, colour);
    drawLine(x2, y2, x0, y0, colour);
}

uint16_t colour565(uint8_t r, uint8_t g, uint8_t b) {
    //return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    return ((0xF8 - r) << 8);
	//return ((0xF8 - r) << 8) | 0x001F;
}

void testFilledTriangles(void) {

    int i, cx = width / 2 - 1, cy = height / 2 - 1;

    fillScreen(BLACK);
    for(i=min(cx,cy); i>10; i-=5) {
        fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, colour565(0, i, i));
        drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i, colour565(i, i, 0));
    }
}

void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t colour) {

    int16_t a, b, y, last;

    // Sort coordinates by Y order (y2 >= y1 >= y0)
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }
    if (y1 > y2) {
        _swap_int16_t(y2, y1); _swap_int16_t(x2, x1);
    }
    if (y0 > y1) {
        _swap_int16_t(y0, y1); _swap_int16_t(x0, x1);
    }


    if(y0 == y2) { // Handle awkward all-on-same-line case as its own thing
        a = b = x0;
        if(x1 < a)      a = x1;
        else if(x1 > b) b = x1;
        if(x2 < a)      a = x2;
        else if(x2 > b) b = x2;
        drawFastHLine(a, y0, b-a+1, colour);
        return;
    }

    int16_t
    dx01 = x1 - x0,
    dy01 = y1 - y0,
    dx02 = x2 - x0,
    dy02 = y2 - y0,
    dx12 = x2 - x1,
    dy12 = y2 - y1;
    int32_t
    sa   = 0,
    sb   = 0;

    // For upper part of triangle, find scanline crossings for segments
    // 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
    // is included here (and second loop will be skipped, avoiding a /0
    // error there), otherwise scanline y1 is skipped here and handled
    // in the second loop...which also avoids a /0 error here if y0=y1
    // (flat-topped triangle).
    if(y1 == y2) last = y1;   // Include y1 scanline
    else         last = y1-1; // Skip it

    for(y=y0; y<=last; y++) {
        a   = x0 + sa / dy01;
        b   = x0 + sb / dy02;
        sa += dx01;
        sb += dx02;
        /* longhand:
        a = x0 + (x1 - x0) * (y - y0) / (y1 - y0);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) _swap_int16_t(a,b);
        drawFastHLine(a, y, b-a+1, colour);
    }

    // For lower part of triangle, find scanline crossings for segments
    // 0-2 and 1-2.  This loop is skipped if y1=y2.
    sa = (int32_t)dx12 * (y - y1);
    sb = (int32_t)dx02 * (y - y0);
    for(; y<=y2; y++) {
        a   = x1 + sa / dy12;
        b   = x0 + sb / dy02;
        sa += dx12;
        sb += dx02;
        /* longhand:
        a = x1 + (x2 - x1) * (y - y1) / (y2 - y1);
        b = x0 + (x2 - x0) * (y - y0) / (y2 - y0);
         */
        if(a > b) _swap_int16_t(a,b);
        drawFastHLine(a, y, b-a+1, colour);
    }
}

void testRoundRects(void) {

    int w, i, i2, cx = width / 2 - 1, cy = height / 2 - 1;

    fillScreen(BLACK);
    w = min(width, height);

    for(i=0; i<w; i+=6) {
        i2 = i / 2;
        drawRoundRect(cx-i2, cy-i2, i, i, i/8, colour565(i, 0, 0));
    }
}

void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t colour) {
    int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if(r > max_radius) r = max_radius;
    // smarter version

    drawFastHLine(x+r, y, w-2*r, colour); // Top
    drawFastHLine(x+r, y+h-1, w-2*r, colour); // Bottom
    drawFastVLine(x, y+r, h-2*r, colour); // Left
    drawFastVLine(x+w-1, y+r, h-2*r, colour); // Right
    // draw four corners
    drawCircleHelper(x+r, y+r, r, 1, colour);
    drawCircleHelper(x+w-r-1, y+r, r, 2, colour);
    drawCircleHelper(x+w-r-1, y+h-r-1, r, 4, colour);
    drawCircleHelper(x+r, y+h-r-1, r, 8, colour);
}

void drawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername, uint16_t colour) {
    int16_t f = 1 - r;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * r;
    int16_t x = 0;
    int16_t y = r;

    while (x<y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (cornername & 0x4) {
            drawPixel(x0 + x, y0 + y, colour);
            drawPixel(x0 + y, y0 + x, colour);
        }
        if (cornername & 0x2) {
            drawPixel(x0 + x, y0 - y, colour);
            drawPixel(x0 + y, y0 - x, colour);
        }
        if (cornername & 0x8) {
            drawPixel(x0 - y, y0 + x, colour);
            drawPixel(x0 - x, y0 + y, colour);
        }
        if (cornername & 0x1) {
            drawPixel(x0 - y, y0 - x, colour);
            drawPixel(x0 - x, y0 - y, colour);
        }
    }
}

void testFilledRoundRects(void) {

    int i, i2, cx = width / 2 - 1, cy = height / 2 - 1;

    fillScreen(BLACK);

    for(i=min(width, height); i>20; i-=6) {
        i2 = i / 2;
        fillRoundRect(cx-i2, cy-i2, i, i, i/8, colour565(0, i, 0));
    }
}

void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t colour) {
    int16_t max_radius = ((w < h) ? w : h) / 2; // 1/2 minor axis
    if(r > max_radius) r = max_radius;
    // smarter version
    fillRect(x+r, y, w-2*r, h, colour);
    // draw four corners
    fillCircleHelper(x+w-r-1, y+r, r, 1, h-2*r-1, colour);
    fillCircleHelper(x+r, y+r, r, 2, h-2*r-1, colour);
}

void printString(char* string) {
#ifdef FIXED_WIDTH_FONT
	printStringFW(string);
#else
    printStringVW(string);
#endif
}

void printStringFW(char* string) {
    while (*(string)) {
        printCharacter(*(string));
        xCoordinate += 6*size;
        string++;
    }
}

void printStringVW(char* string) {
    while (*(string)) {
        printCharacter(*(string));
        xCoordinate += fontData[fontOffset[*string - 32] + 1];
        string++;
    }
}

void printStringRight(char* string) {
#ifdef FIXED_WIDTH_FONT
	printStringRightFW(string);
#else
    printStringRightVW(string);
#endif
}

void printStringRightFW(char* string) {
    signed int i = 0;
    signed int j;

    //find end of string
    while (*string) {
        i++;
    string++;
    }
    string--;

    //print characters in reverse
    for (j = i - 1; j >= 0; j--) {
        xCoordinate -= 5 * size - 1;
        printCharacter(*(string--));
        xCoordinate -= size + 1;
    }
}

void printStringRightVW(char* string) {
    signed int i = 0;
    signed int j;

    //find end of string
    while (*string) {
        i++;
    string++;
    }
    string--;

    //print characters in reverse
    for (j = i - 1; j >= 0; j--) {
        xCoordinate -= fontData[fontOffset[*string - 32] + 1] - 1;
        printCharacter(*(string--));
        xCoordinate--;
    }
}

void printCharacter(char z) {
#ifdef FIXED_WIDTH_FONT
	printCharacterFW(z);
#else
    printCharacterVW(z);
#endif
}

void printCharacterFW(char z) {
	uint8_t i;
	uint8_t j;
	uint8_t line;

	for(i=0; i<5; i++ ) {                                                      //Adafruit "Classic" font = 5 columns
		line = fontData[z * 5 + i];
		for(j=0; j<8; j++, line >>= 1) {
			if(line & 1) {
				if(size == 1)
					drawPixel(xCoordinate+i, yCoordinate+j, fontColour);
				else
					fillRect(xCoordinate+i*size, yCoordinate+j*size, size, size, fontColour);
			}
		}
	}
}

void printCharacterVW(char z) {                                                  //print variable-width font

}

void printStringcmdL(char* string) {
#ifdef FIXED_WIDTH_FONT
	printStringcmdLFW(string);
#else
	printStringcmdLVW(string);
#endif
}

void printStringcmdLFW(char* string) {
    while (*(string)) {
        printCharactercmdL(*(string));
        xCoordinateCursor += 6*size;
        string++;
    }
}

void printStringcmdLVW(char* string) {
    while (*(string)) {
        printCharactercmdL(*(string));
        xCoordinateCursor += fontData[fontOffset[*string - 32] + 1];
        string++;
    }
}

void printCharactercmdL(char z) {
#ifdef FIXED_WIDTH_FONT
	printCharactercmdLFW(z);
#else
    printCharactercmdLVW(z);
#endif
}

void printCharactercmdLFW(char z) {
	uint8_t i;
	uint8_t j;
	uint8_t line;

	for(i=0; i<5; i++ ) {                                                      //Adafruit "Classic" font = 5 columns
		line = fontData[z * 5 + i];
		for(j=0; j<8; j++, line >>= 1) {
			if(line & 1) {
				if(size == 1)
					drawPixel(xCoordinateCursor+i, yCoordinateCursor+j, fontColour);
				else
					fillRect(xCoordinateCursor+i*size, yCoordinateCursor+j*size, size, size, fontColour);
			}
		}
	}
}

void printCharactercmdLVW(char z) {

}

