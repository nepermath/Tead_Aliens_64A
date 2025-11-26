/*
;+-----------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File for Atmel AVR Studio 4..7
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : End_Game.bmp
;|
;| Destiny
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : BMP_End_Game.h
;|
;| Destiny Image Properties
;|     Size   :    28 Bytes
;|     Width  :    15 Pixels
;|     Height :    14 Pixels
;|     WidthB :     2 Bytes
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
;     012345678901234
;     |         |    
;0000- ### #  # ###  #-   0
;0001- #   ## # #  # #-   1
;0002- ### # ## #  # #-   2
;0003- #   #  # #  # #-   3
;0004- ### #  # ###  #-   4
;0005-               #-   5
;0006-               #-   6
;0007-### ### # # ####-   7
;0008-#   # # ### #  #-   8
;0009-# # ### # # ####-   9
;0010-# # # # # # #  #-  10
;0011-### # # # # ####-  11
;0012-               #-  12
;0013-               #-  13
;     |         |    
;                    
;               1    
;     012345678901234
*/

const uint8_t BMP_End_Game[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// Header Size 18
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//     0 BW 1 Color
	0x0F,0x00,	//    15 Width in Pixels
	0x0E,0x00,	//    14 Height in Pixels
	0x02,0x00,	//     2 Width in Bytes
	0x1C,0x00,	//    28 Size in Bytes
	0x00,0x00,	//	  Image Data Size
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x74,0xB8,0x46,0xA4,0x75,0xA4,0x44,0xA4,0x74,0xB8,0x00,0x00,0x00,0x00,0xEE,0xAE,	//7
	0x8A,0xE8,0xAE,0xAE,0xAA,0xA8,0xEA,0xAE,0x00,0x00,0x00,0x00 
};
