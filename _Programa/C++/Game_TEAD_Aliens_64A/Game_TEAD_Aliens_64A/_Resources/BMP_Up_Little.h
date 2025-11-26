/*
+-----------------------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File 
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\____Games\_Game_Block\_Programa\C++\Game_TEAD_Aliens_64A\Game_TEAD_Aliens_64A\_Resources\Up_Little.bmp
;|     File : Up_Little.bmp
;|
;| Image Properties
;|     Size   :     5 Bytes
;|     Width  :     5 Pixels
;|     Height :     5 Pixels
;|     WidthB :     1 Bytes
;|     Colors :     2 Colors(1) Bit
;+-----------------------------------------------------------------------------------------------------------------------------------------
;| Format 1 Bit 2 Colors or B/W
;|
;|  7 6 5 4 3 2 1 0  Each Bit(b) Represent One Pixel Bit=1 Pixel On Bit=0 Pixel Off
;| +-+-+-+-+-+-+-+-+ Pixel 0 iqual to Bit 7 and pixel 7 iqual to Bit 0
;| |b|b|b|b|b|b|b|b|
;| +-+-+-+-+-+-+-+-+
;|
;+-----------------------------------------------------------------------------------------------------------------------------------------
*/

const uint8_t BMP_Up_Little[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// BMP Header Size  18
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//     0 Color Type = BW or Color
	0x05,0x00,	//     5 Width in Pixels
	0x05,0x00,	//     5 Height in Pixels
	0x01,0x00,	//     1 Width in Bytes
	0x05,0x00,	//     5 Total Size in Bytes
	0x00,0x00,
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x00,0x20,0x70,0x20,0x20 	//5

// Total Bytes          =  5
// Total Bytes + Header =  23

};
