/*
;+--------------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File for Atmel AVR Studio 4..7
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : Game_Over_3.bmp
;|
;| Destiny
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : BMP_Game_Over_3.h
;|
;| Destiny Image Properties
;|     Size   :    42 Bytes
;|     Width  :    20 Pixels
;|     Height :    14 Pixels
;|     WidthB :     3 Bytes
;|     Colors :     2 Colors(1) Bit
;|
;| Define a below typedef in C,C++ code to accept BitMap resource
;|
;|	typedef const uint8_t BitMap;
;|
;+--------------------------------------------------------------------------------------------------------------------------------

;( IMAGE CONTENTS )

;                         
;               1         
;     01234567890123456789
;     |         |         
;0000- ###  ##  #   # ########-   0
;0001-#    #  # ## ## #   ####-   1
;0002-# ## #  # # # # ### ####-   2
;0003-#  # #### #   # #   ####-   3
;0004- ### #  # #   # ########-   4
;0005-                    ####-   5
;0006-                    ####-   6
;0007- ##  #   # #### ### ####-   7
;0008-#  # #   # #    #  #####-   8
;0009-#  # #   # #### ### ####-   9
;0010-#  #  # #  #    # # ####-  10
;0011- ##    #   #### #  #####-  11
;0012-                    ####-  12
;0013-                    ####-  13
;     |         |         
;                         
;               1         
;     01234567890123456789
*/

const uint8_t BMP_Game_Over_3[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// Header Size 14
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//	0 bw 1 color
	0x14,0x00,	//    20 Width in Pixels
	0x0E,0x00,	//    14 Height in Pixels
	0x03,0x00,	//     3 Width in Bytes
	0x2A,0x00,	//    42 Size in Bytes
	0x00,0x00,
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x73,0x22,0xF0,0x84,0xB6,0x80,0xB4,0xAA,0xE0,0x97,0xA2,0x80,0x74,0xA2,0xF0,0x00,	//5
	0x00,0x00,0x00,0x00,0x00,0x64,0x5E,0xE0,0x94,0x50,0x90,0x94,0x5E,0xE0,0x92,0x90,	//10
	0xA0,0x61,0x1E,0x90,0x00,0x00,0x00,0x00,0x00,0x00 
};
