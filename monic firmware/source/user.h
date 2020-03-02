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

#define FIXED_WIDTH_FONT               //"FIXED_WIDTH_FONT" - IF USING ADAFRUIT "CLASSIC" FONT OR OTHER FIXED WIDTH FONT
                                       //"VARIABLE_WIDTH_FONT" - IF USING VARIABLE WIDTH FONT (USER SUPPLIED)

//flag1

#define SHIFT                   0x00000004
#define EXP                     0x00000001
#define DECPOINT                0x00000002
#define ZEROFIRST               0x00000020
#define NEGEXP                  0x00000008
#define NEGSIG                  0x00000010
#define ANS                     0x00000040

//flag2

#define EXACT                   0x00000001
//#define BACKLIGHTOFF            0x00000002
#define CeditorRefresh          0x00000004
#define CeditorArrow            0x00000008

#define STATUSLINEOFF           0x00000040
#define STACKOFF                0x00000080
#define MENUOFF                 0x00000100
#define COMMANDLINEOFF          0x40000000

#define DECIMAL                 0x00001000
#define BINARY                  0x00002000

#define DEGREE                  0x00000200
#define RADIAN                  0x00000400

#define RUN                     0x00080000

#define ALGENTRY                0x10000000

#define CURSORON                0x00000010
#define INTERRUPT               0x00000020

#define OPCODE                  0x08000000

//flag3
#define newProgram              0x00000001
#define saveConstant            0x00000002
#define eraseMemory             0x00000004
#define prgCplxStack            0x00000008
#define newFolder               0x00000080

//constants

#define Pi                      3.14159265358979323846
#define e                       2.718281828459045
#define significandStringLength 32
#define cmdL_SLength            15

//#define keyHeld                 30                                             //30 good
//#define keyHeldDelay            400000                                         //400,000 good

#define stackDDepth             100
//#define keyPressDebounce        600000                                         //900,000 good, 800000 very good
//#define keyReleaseDebounce      75000                                          //200,000 good?, 100000 very good

#define cmdL_ParsedLength       40

#define NOP                     184
#define END                     122

#define custMenuLength          20

#define memAllocLength          301

#define numberOfPrgSteps        500
#define prgConstantsLength      30
#define varListLength           30
#define varListStringLength     7
#define labelAddressLength      26
#define cmdLNumberLength        30
#define cmdLOprtLength          15

#define numberOfCPrgChars       1000

//display coordinates

#define statLfield0             0
#define statLfield1             100
#define statLfield2             240
#define statLfield3             335
#define statLfield4             380

#define yCoordStatLTop          0
#define yCoordStatLBottom       30                                             //for font 30 pixels high

#define yCoordLvl5Top           40
#define yCoordLvl5Bottom        79

#define yCoordLvl4Top           80
#define yCoordLvl4Bottom        119

#define yCoordLvl3Top           120
#define yCoordLvl3Bottom        159

#define yCoordLvl2Top           160
#define yCoordLvl2Bottom        199

#define yCoordLvl1Top           200
#define yCoordLvl1Bottom        239

#define yCoordCmdLTop           240
#define yCoordCmdLBottom        279

#define yCoordMenuTop           280
#define yCoordMenuBottom        319

#define yCoordMenuTextTop       286

#define pageWidth               40

#define max_xCoord              479
#define displayWidth            480

#define GOTOLabelOffsetFW       24
#define GOTOLabelOffsetVW       56

#define xCoordMenuField0        0
#define xCoordMenuField1        80
#define xCoordMenuField2        160
#define xCoordMenuField3        240
#define xCoordMenuField4        320
#define xCoordMenuField5        400

#define xCoordMenuFieldText0    4
#define xCoordMenuFieldText1    84
#define xCoordMenuFieldText2    164
#define xCoordMenuFieldText3    244
#define xCoordMenuFieldText4    324
#define xCoordMenuFieldText5    404

#define cursorRate              2000000                                          //1,000,000 too fast

//display colours and font No 1

#define StatLColour              BLUE
#define StackColour              RED
#define CmdLColour               YELLOW
#define MenuColour               MAGENTA
#define backgroundColour         BLACK
#define cursorColour             YELLOW

////////////////////////////////keypad allocation

//Main

#define equalMain               0

#define zeroMain                4
#define oneMain                 10
#define twoMain                 9
#define threeMain               8
#define fourMain                16
#define fiveMain                15
#define sixMain                 14
#define sevenMain               22
#define eightMain               21
#define nineMain                20
#define decimalPointMain        3

#define deleteMain              5
#define swapMain                23

#define alpha                   11
#define shiftMain               17

#define closeParenthesis        18
#define openParenthesis         19

#define negateMain              2
#define addMain                 7
#define subtractMain            6
#define multiplyMain            13
#define divideMain              12
#define exponentMain            1

#define sineMain                29
#define cosineMain              28
#define tangentMain             27
#define PIMain                  25
#define arcTanMain              75
#define arcCosMain              76
#define arcSinMain              77

#define squareMain              35
#define reciprocalMain          34
#define powerMain               33
#define tenPowerMain            32
#define eulerPowerMain          31
#define factorialMain           30

#define exitMain                36
#define downMain                37
#define upMain                  38
#define rightMain               39
#define leftMain                40
#define nextMain                41

#define menuKey1Main            47
#define menuKey2Main            46
#define menuKey3Main            45
#define menuKey4Main            44
#define menuKey5Main            43
#define menuKey6Main            42

//Main shifted key plane

#define ansMain                 48
#define clearMain               53
#define CAAMain                 54
#define mathMain                55
#define shiftshiftMain          65
#define matrixMain              66
#define graphMain               67
#define pickMain                71
#define degRadMain              72
#define folderMain              89

#define squareRootMain          83
#define cubeRootMain            82
#define powerRMain              81
#define log10Main               80
#define logEulerMain            79
#define randMain                78

#define systemMain              85
#define programMain             86
#define modeMain                87
#define approxExactMain         88

#define menuKey3Main_S          93
#define menuKey2Main_S          94
#define menuKey1Main_S          95

//Main held key plane

#define combMain                126                                            //96 + 30 = 126
#define norSciMain              136
#define decHexMain              135
#define stackMain               119                                            //96 + 23 = 119

#define eraseMain_H             101                                            //96 + 5
#define pushImagPartMain        116
#define viewMain                113                                            //96 + 17 = 113
#define menuKey3Main_H          141
#define menuKey2Main_H          142                                            //96 + 46 = 142
#define menuKey1Main_H          143                                            //96 + 47 = 143

//Main shifted, held key plane

#define permMain                174                                            //144 + 30 = 174
#define binaryMain              185                                            //144 + 41 = 185

//Store

#define deleteStore             5
#define AStore                  29
#define BStore                  28
#define CStore                  27
#define DStore                  26
#define EStore                  25
#define FStore                  24
#define GStore                  22
#define HStore                  21
#define IStore                  20
#define JStore                  19
#define KStore                  18
#define LStore                  16
#define MStore                  15
#define NStore                  14
#define OStore                  13
#define PStore                  12
#define QStore                  10
#define RStore                  9
#define SStore                  8
#define TStore                  7
#define UStore                  6
#define VStore                  4
#define WStore                  3
#define XStore                  2
#define YStore                  1
#define ZStore                  0

#define menuKey1Store           47
#define menuKey2Store           46
#define menuKey3Store           45

//Store shift key plane

#define clearStore              53

//Store held key plane

#define zeroStore               100                                            //96 + 4
#define oneStore                106                                            //96 + 10
#define twoStore                105
#define threeStore              104
#define fourStore               112
#define fiveStore               111
#define sixStore                110
#define sevenStore              118
#define eightStore              117
#define nineStore               116

//Erase

#define exitErase              36
#define menuKey1Erase          47
#define menuKey2Erase          46
#define menuKey3Erase          45

//Matrix

#define equalMatrix            0
#define oneMatrix              10
#define twoMatrix              9
#define threeMatrix            8
#define fourMatrix             16
#define fiveMatrix             15
#define sixMatrix              14
#define sevenMatrix            22
#define eightMatrix            21
#define nineMatrix             20

//View

#define upView                 38
#define downView               37
#define leftView               40
#define rightView              39

#define exitView               36

//KSPrg

#define equalKSPrg             0
#define deleteKSPrg            5
#define swapKSPrg              23

#define zeroKSPrg              4
#define oneKSPrg               10
#define twoKSPrg               9
#define threeKSPrg             8
#define fourKSPrg              16
#define fiveKSPrg              15
#define sixKSPrg               14
#define sevenKSPrg             22
#define eightKSPrg             21
#define nineKSPrg              20
#define decimalPointKSPrg      3

#define jKSPrg                 19
#define kKSPrg                 18

#define negateKSPrg            2
#define addKSPrg               7
#define subtractKSPrg          6
#define multiplyKSPrg          13
#define divideKSPrg            12

#define shiftKSPrg             17
#define F_KSPrg                24
#define E_PIKSPrg              25
#define D_ToDMSKSPrg           26
#define C_TANKSPrg             27
#define B_COSKSPrg             28
#define A_SINKSPrg             29
#define eulerPowerKSPrg        31
#define tenPowerKSPrg          32
#define reciprocalKSPrg        34
#define powerKSPrg             33
#define squareKSPrg            35
#define factorialKSPrg         30
#define exitKSPrg              36
#define downKSPrg              37
#define upKSPrg                38
#define nextKSPrg              41

#define menuKey1KSPrg          47
#define menuKey2KSPrg          46
#define menuKey3KSPrg          45
#define menuKey4KSPrg          44
#define menuKey5KSPrg          43
#define menuKey6KSPrg          42

//KSPrg shifted key plane

#define DMSToKSPrg             74
#define arcTanKSPrg            75
#define arcCosKSPrg            76
#define arcSinKSPrg            77
#define lnKSPrg                79
#define logTenKSPrg            80

#define stoKSPrg               49
#define shiftshiftKSPrg        65
#define graphKSPrg             67
#define rootKSPrg              81
#define cubeRootKSPrg          82
#define sqrtKSPrg              83
#define systemKSPrg            85

//KSPrg held key plane

#define stackKSPrg             119                                             //96 + 23 = 119
#define helddownKSPrg          133
#define heldupKSPrg            134
#define eraseKSPrg             101                                             //96 + 5 = 101
//#define deletelineKSPrg        135
//#define insertKSPrg            136
#define menuKey1HeldKSPrg      143
#define menuKey2HeldKSPrg      142
#define menuKey3HeldKSPrg      141

//KSPrg shifted, held key plane

#define shifthelddownKSPrg     181                                             //144+37
#define shiftheldupKSPrg       182

//KSPrgMenu

#define exitKSPrgMenu          36
#define menuKey1KSPrgMenu      47

//KSPrgVar

#define exitKSPrgVar           36
#define nextKSPrgVar           41

#define menuKey1KSPrgVar       47
#define menuKey2KSPrgVar       46
#define menuKey3KSPrgVar       45
#define menuKey4KSPrgVar       44
#define menuKey5KSPrgVar       43
#define menuKey6KSPrgVar       42

//runPrg, runPrgFast, runPrgCplx & runPrgCplxFast - refer to KSPrg

//KSPrgDebug

#define menuKey1KSPrgDebug     47
#define menuKey3KSPrgDebug     45
#define exitKSPrgDebug         36

//KSPrgSTO

#define equalKSPrgSTO          0
#define deletelKSPrgSTO        5
#define nextKSPrgSTO           41
#define menuKey6KSPrgSTO       42
#define menuKey5KSPrgSTO       43
#define menuKey4KSPrgSTO       44
#define menuKey3KSPrgSTO       45
#define menuKey2KSPrgSTO       46
#define menuKey1KSPrgSTO       47

//KSPrgSTO held

#define zKSPrgSTO              96

//font5x7

#define exitfont5x7            36

//HLPrg

#define leftArrow              40
#define rigthArrow             39

//HLPrg shifted

#define mainHLPrg              70

//TimesTables

#define zeroTimesTables                4
#define oneTimesTables                 10
#define twoTimesTables                 9
#define threeTimesTables               8
#define fourTimesTables                16
#define fiveTimesTables                15
#define sixTimesTables                 14
#define sevenTimesTables               22
#define eightTimesTables               21
#define nineTimesTables                20
#define decimalPointTimesTables        3

#define deleteTimesTables              5
#define exitTimesTables                36
#define enterTimesTables               0

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////

//defines for LCD

#define HX8347G_COLADDRSTART_HI    0x02
#define HX8347G_COLADDRSTART_LO    0x03
#define HX8347G_COLADDREND_HI      0x04
#define HX8347G_COLADDREND_LO      0x05
#define HX8347G_ROWADDRSTART_HI    0x06
#define HX8347G_ROWADDRSTART_LO    0x07
#define HX8347G_ROWADDREND_HI      0x08
#define HX8347G_ROWADDREND_LO      0x09
#define HX8347G_MEMACCESS          0x16

#define HX8357_NOP     0x00
#define HX8357_SWRESET 0x01
#define HX8357_RDDID   0x04
#define HX8357_RDDST   0x09

#define HX8357B_RDPOWMODE  0x0A
#define HX8357B_RDMADCTL  0x0B
#define HX8357B_RDCOLMOD  0x0C
#define HX8357B_RDDIM  0x0D
#define HX8357B_RDDSDR  0x0F

#define HX8357_SLPIN   0x10
#define HX8357_SLPOUT  0x11
#define HX8357B_PTLON   0x12
#define HX8357B_NORON   0x13

#define HX8357_INVOFF  0x20
#define HX8357_INVON   0x21
#define HX8357_DISPOFF 0x28
#define HX8357_DISPON  0x29

#define HX8357_CASET   0x2A
#define HX8357_PASET   0x2B
#define HX8357_RAMWR   0x2C
#define HX8357_RAMRD   0x2E

#define HX8357B_PTLAR   0x30
#define HX8357_TEON  0x35
#define HX8357_TEARLINE  0x44
#define HX8357_MADCTL  0x36
#define HX8357_COLMOD  0x3A

#define HX8357_SETOSC 0xB0
#define HX8357_SETPWR1 0xB1
#define HX8357B_SETDISPLAY 0xB2
#define HX8357_SETRGB 0xB3
#define HX8357D_SETCOM  0xB6

#define HX8357B_SETDISPMODE  0xB4
#define HX8357D_SETCYC  0xB4
#define HX8357B_SETOTP 0xB7
#define HX8357D_SETC 0xB9

#define HX8357B_SET_PANEL_DRIVING 0xC0
#define HX8357D_SETSTBA 0xC0
#define HX8357B_SETDGC  0xC1
#define HX8357B_SETID  0xC3
#define HX8357B_SETDDB  0xC4
#define HX8357B_SETDISPLAYFRAME 0xC5
#define HX8357B_GAMMASET 0xC8
#define HX8357B_SETCABC  0xC9
#define HX8357_SETPANEL  0xCC

#define HX8357B_SETPOWER 0xD0
#define HX8357B_SETVCOM 0xD1
#define HX8357B_SETPWRNORMAL 0xD2

#define HX8357B_RDID1   0xDA
#define HX8357B_RDID2   0xDB
#define HX8357B_RDID3   0xDC
#define HX8357B_RDID4   0xDD

#define HX8357D_SETGAMMA 0xE0

#define HX8357B_SETGAMMA 0xC8
#define HX8357B_SETPANELRELATED  0xE9

#define HX8357B_MADCTL_MY  0x80
#define HX8357B_MADCTL_MX  0x40
#define HX8357B_MADCTL_MV  0x20
#define HX8357B_MADCTL_ML  0x10
#define HX8357B_MADCTL_RGB 0x00
#define HX8357B_MADCTL_BGR 0x08
#define HX8357B_MADCTL_MH  0x04

#define ILI9341_SOFTRESET          0x01
#define ILI9341_SLEEPIN            0x10
#define ILI9341_SLEEPOUT           0x11
#define ILI9341_NORMALDISP         0x13
#define ILI9341_INVERTOFF          0x20
#define ILI9341_INVERTON           0x21
#define ILI9341_GAMMASET           0x26
#define ILI9341_DISPLAYOFF         0x28
#define ILI9341_DISPLAYON          0x29
#define ILI9341_COLADDRSET         0x2A
#define ILI9341_PAGEADDRSET        0x2B
#define ILI9341_MEMORYWRITE        0x2C
#define ILI9341_PIXELFORMAT        0x3A
#define ILI9341_FRAMECONTROL       0xB1
#define ILI9341_DISPLAYFUNC        0xB6
#define ILI9341_ENTRYMODE          0xB7
#define ILI9341_POWERCONTROL1      0xC0
#define ILI9341_POWERCONTROL2      0xC1
#define ILI9341_VCOMCONTROL1      0xC5
#define ILI9341_VCOMCONTROL2      0xC7
#define ILI9341_MEMCONTROL      0x36
#define ILI9341_MADCTL  0x36

#define ILI9341_MADCTL_MY  0x80
#define ILI9341_MADCTL_MX  0x40
#define ILI9341_MADCTL_MV  0x20
#define ILI9341_MADCTL_ML  0x10
#define ILI9341_MADCTL_RGB 0x00
#define ILI9341_MADCTL_BGR 0x08
#define ILI9341_MADCTL_MH  0x04

//colours

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
//////////////////////COLOURS NOT YET IMPLEMENTED - DEFAULT TO COLOUR SHOWN
#define ORANGE  0xF800 //RED
#define PINK    0xFFE0 //YELLOW
#define INDIGO  0xF81F //MAGENTA
#define AQUA    0x07FF //CYAN
#define BROWN   0x0000 //BLACK

//display dimensions

#define TFTWIDTH   320
#define TFTHEIGHT  480

//macros

#define _swap_int16_t(a, b) { int16_t t = a; a = b; b = t; }
#define min(a,b) (((a) < (b)) ? (a) : (b))

