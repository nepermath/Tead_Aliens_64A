/*
;+--------------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File for Atmel AVR Studio 4..7
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : Mother_Ship.bmp
;|
;| Destiny
;|     Path : C:\____NEPER\___PROJETOS\_______NP\_____Graph_LED_Display\_Progamas\C++\MAIN\Display_Main\Display_Main\Resources\
;|     File : BMP_Mother_Ship.h
;|
;| Destiny Image Properties
;|     Size   :     2 Bytes
;|     Width  :     6 Pixels
;|     Height :     2 Pixels
;|     WidthB :     1 Bytes
;|     Colors :     2 Colors(1) Bit
;|
;| Define a below typedef in C,C++ code to accept BitMap resource
;|
;|	typedef const uint8_t BitMap;
;|
;+--------------------------------------------------------------------------------------------------------------------------------

;( IMAGE CONTENTS )

;           
;           
;     012345
;     |     
;0000-  ##  ##-   0
;0001- #### ##-   1
;     |     
;           
;           
;     012345
*/

const uint8_t BMP_Mother_Ship[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// Header Size 18
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//		0 bw 1 color
	0x06,0x00,	//     6 Width in Pixels
	0x02,0x00,	//     2 Height in Pixels
	0x01,0x00,	//     1 Width in Bytes
	0x02,0x00,	//     2 Size in Bytes
	0x00,0x00,
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x30,0x78 
};
