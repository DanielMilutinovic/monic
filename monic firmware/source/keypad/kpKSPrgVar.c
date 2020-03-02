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

//pushing variable in Keystroke programming editor

//includes

#include "../user.h"

//variables

extern unsigned int flag2;
extern unsigned int prgIndex;
extern unsigned int *prg;
extern unsigned int custMenuFunc[custMenuLength];
extern unsigned char menu;
extern unsigned char kpPlane;
extern unsigned char annunciator;

//constants
                                  //{0,1,2}
const unsigned char nextVarMenu[3] = {1,2,0};

///////////////////////////////////////////////////////////////////////////////

void kpKSPrgVar(unsigned int x) {
    switch(x) {
    case menuKey1KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10000;                           //increment var1 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20000;                       //decrement var1 and PUSH it onto the stack
                else prg[prgIndex] = 200000;                                       //otherwise PUSH var1 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10006;                           //increment var7 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20006;                       //decrement var7 and PUSH it onto the stack
                else prg[prgIndex] = 200006;                                       //otherwise PUSH var7 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10012;                           //increment var13 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20012;                       //decrement var13 and PUSH it onto the stack
                else prg[prgIndex] = 200012;                                       //otherwise PUSH var13 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case menuKey2KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10001;                           //increment var2 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20001;                       //decrement var2 and PUSH it onto the stack
                else prg[prgIndex] = 200001;                                       //otherwise PUSH var2 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10007;                           //increment var8 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20007;                       //decrement var8 and PUSH it onto the stack
                else prg[prgIndex] = 200007;                                       //otherwise PUSH var8 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10013;                           //increment var14 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20013;                       //decrement var14 and PUSH it onto the stack
                else prg[prgIndex] = 200013;                                       //otherwise PUSH var14 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case menuKey3KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10002;                           //increment var3 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20002;                       //decrement var3 and PUSH it onto the stack
                else prg[prgIndex] = 200002;                                       //otherwise PUSH var3 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10008;                           //increment var9 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20008;                       //decrement var9 and PUSH it onto the stack
                else prg[prgIndex] = 200008;                                       //otherwise PUSH var9 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10014;                           //increment var15 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20014;                       //decrement var15 and PUSH it onto the stack
                else prg[prgIndex] = 200014;                                       //otherwise PUSH var15 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case menuKey4KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10003;                           //increment var4 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20003;                       //decrement var4 and PUSH it onto the stack
                else prg[prgIndex] = 200003;                                       //otherwise PUSH var4 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10009;                           //increment var10 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20009;                       //decrement var10 and PUSH it onto the stack
                else prg[prgIndex] = 200009;                                       //otherwise PUSH var10 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10015;                           //increment var16 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20015;                       //decrement var16 and PUSH it onto the stack
                else prg[prgIndex] = 200015;                                       //otherwise PUSH var16 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case menuKey5KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10004;                           //increment var5 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20004;                       //decrement var5 and PUSH it onto the stack
                else prg[prgIndex] = 200004;                                       //otherwise PUSH var5 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10010;                           //increment var11 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20010;                       //decrement var11 and PUSH it onto the stack
                else prg[prgIndex] = 200010;                                       //otherwise PUSH var11 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10016;                           //increment var17 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20016;                       //decrement var17 and PUSH it onto the stack
                else prg[prgIndex] = 200016;                                       //otherwise PUSH var17 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case menuKey6KSPrgVar:
        switch (menu) {
        case 0:
            if (annunciator == 4) prg[prgIndex] = 10005;                           //increment var6 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20005;                       //decrement var6 and PUSH it onto the stack
                else prg[prgIndex] = 200005;                                       //otherwise PUSH var6 onto the stack etc.
            }
            break;
        case 1:
            if (annunciator == 4) prg[prgIndex] = 10011;                           //increment var12 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20011;                       //decrement var12 and PUSH it onto the stack
                else prg[prgIndex] = 200011;                                       //otherwise PUSH var12 onto the stack etc.
            }
            break;
        case 2:
            if (annunciator == 4) prg[prgIndex] = 10017;                           //increment var18 and PUSH it onto the stack
            else {
                if (annunciator == 5) prg[prgIndex] = 20017;                       //decrement var18 and PUSH it onto the stack
                else prg[prgIndex] = 200017;                                       //otherwise PUSH var18 onto the stack etc.
            }
            break;
        }
        flag2 &= ~CURSORON;
        kpPlane = 5;                                                           //return to Keystroke programming editor
        menu = 0;
        break;
    case nextKSPrgVar:
        menu = nextVarMenu[menu];
        goto exit;                                                             //so that prgIndex is not incremented
    case exitKSPrgVar:                                                         //return to Keystroke program editor
        kpPlane = 5;
        menu = 0;
        annunciator = 0;
        goto exit;                                                             //so that prgIndex is not incremented
    }
    prgIndex += 1;
    annunciator = 0;
    exit:
	__asm volatile ("nop");
}
