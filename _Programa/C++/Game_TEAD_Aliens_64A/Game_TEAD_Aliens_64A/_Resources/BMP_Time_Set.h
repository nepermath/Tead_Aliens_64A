/*
;+-----------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File for Atmel AVR Studio 4..7
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : Time_Set.bmp
;|
;| Destiny
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : BMP_Time_Set.h
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
;+-----------------------------------------------------------------------------------------------------------------------------

;( IMAGE CONTENTS )

;                         
;               1         
;     01234567890123456789
;     |         |         
;0000-  ### # #   # ###   ####-   0
;0001-   #  # ## ## #     ####-   1
;0002-   #  # # # # ##    ####-   2
;0003-   #  # #   # #     ####-   3
;0004-   #  # #   # ###   ####-   4
;0005-                    ####-   5
;0006-                    ####-   6
;0007-### ### ###   # # # ####-   7
;0008-#   #    #    # # # ####-   8
;0009-### ##   #    # # # ####-   9
;0010-  # #    #    # # # ####-  10
;0011-### ###  #  # # # # ####-  11
;0012-                    ####-  12
;0013-              # # # ####-  13
;     |         |         
;                         
;               1         
;     01234567890123456789
*/

const uint8_t BMP_Time_Set[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// Header Size 18
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//	0 bw 1 color
	0x14,0x00,	//    20 Width in Pixel
	0x0E,0x00,	//    14 Height in Pixels
	0x03,0x00,	//     3 Width in Bytes
	0x2A,0x00,	//    42 Size in Bytes
	0x00,0x00,	//
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x3A,0x8B,0x80,0x12,0xDA,0x00,0x12,0xAB,0x00,0x12,0x8A,0x00,0x12,0x8B,0x80,0x00,	//5
	0x00,0x00,0x00,0x00,0x00,0xEE,0xE2,0xA0,0x88,0x42,0xA0,0xEC,0x42,0xA0,0x28,0x42,	//10
	0xA0,0xEE,0x4A,0xA0,0x00,0x00,0x00,0x00,0x02,0xA0 
};
