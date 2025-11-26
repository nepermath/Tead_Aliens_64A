/*
+----------------------------------------------------------------------------------------------------------------------------------------
;| Generate C,C++ File 
;|
;| Source
;|     Path : C:\____NEPER\___PROJETOS\_______NP\____Games\_Game_Block\_Programa\C++\Game_TEAD_Aliens_64A\Game_TEAD_Aliens_64A\_Resources\Calendar.bmp
;|     File : Calendar.bmp
;|
;| Image Properties
;|     Size   :     8 Bytes
;|     Width  :     8 Pixels
;|     Height :     8 Pixels
;|     WidthB :     1 Bytes
;|     Colors :     2 Colors(1) Bit
;+----------------------------------------------------------------------------------------------------------------------------------------
;| Format 1 Bit 2 Colors or B/W
;|
;|  7 6 5 4 3 2 1 0  Each Bit(b) Represent One Pixel Bit=1 Pixel On Bit=0 Pixel Off
;| +-+-+-+-+-+-+-+-+ Pixel 0 iqual to Bit 7 and pixel 7 iqual to Bit 0
;| |b|b|b|b|b|b|b|b|
;| +-+-+-+-+-+-+-+-+
;|
;+----------------------------------------------------------------------------------------------------------------------------------------
*/

const uint8_t BMP_Calendar[] PROGMEM =
{
	//+------------+
	//| BMP Header |
	//+------------+
	0x42,0x4D,	// BitMap Header ASCII(B)+ASCII(M)
	0x12,0x00,	// BMP Header Size  18
	0x01,0x00,	//     1 Bits Deep
	0x00,0x00,	//     0 Color Type = BW or Color
	0x08,0x00,	//     8 Width in Pixels
	0x08,0x00,	//     8 Height in Pixels
	0x01,0x00,	//     1 Width in Bytes
	0x08,0x00,	//     8 Total Size in Bytes
	0x00,0x00,
	//+------------+
	//|  BMP Data  |
	//+------------+
	0x00,0x3E,0x6A,0x42,0x6A,0x42,0x7E,0x00 	//8

// Total Bytes          =  8
// Total Bytes + Header =  26

};
