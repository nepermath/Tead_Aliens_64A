/*
 /////////////////////////////////////////////////////////////////////////////////////////
				 _____                       _  ______      _
				/  ___|                     | | |  _  \    (_)
				\ `--.  ___  _   _ _ __   __| | | | | |_ __ ___   _____ _ __
				 `--. \/ _ \| | | | '_ \ / _` | | | | | '__| \ \ / / _ \ '__|
				/\__/ / (_) | |_| | | | | (_| | | |/ /| |  | |\ V /  __/ |
				\____/ \___/ \__,_|_| |_|\__,_| |___/ |_|  |_| \_/ \___|_|
			
 /////////////////////////////////////////////////////////////////////////////////////////
  --------------------------------- IO C++ File (tab 4) ----------------------------------
  
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Sound_Driver.h"

/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/

const uint8_t SIN_TABLE[] PROGMEM =
{
	//SINE WAVE
// 	0x7F,0x82,0x85,0x88,0x8B,0x8F,0x92,0x95,0x98,0x9B,0x9E,0xA1,0xA4,0xA7,0xAA,0xAD,
// 	0xB0,0xB2,0xB5,0xB8,0xBB,0xBE,0xC0,0xC3,0xC6,0xC8,0xCB,0xCD,0xD0,0xD2,0xD4,0xD7,
// 	0xD9,0xDB,0xDD,0xDF,0xE1,0xE3,0xE5,0xE7,0xE9,0xEA,0xEC,0xEE,0xEF,0xF0,0xF2,0xF3,
// 	0xF4,0xF5,0xF7,0xF8,0xF9,0xF9,0xFA,0xFB,0xFC,0xFC,0xFD,0xFD,0xFD,0xFE,0xFE,0xFE,
// 	0xFE,0xFE,0xFE,0xFE,0xFD,0xFD,0xFD,0xFC,0xFC,0xFB,0xFA,0xF9,0xF9,0xF8,0xF7,0xF5,
// 	0xF4,0xF3,0xF2,0xF0,0xEF,0xEE,0xEC,0xEA,0xE9,0xE7,0xE5,0xE3,0xE1,0xDF,0xDD,0xDB,
// 	0xD9,0xD7,0xD4,0xD2,0xD0,0xCD,0xCB,0xC8,0xC6,0xC3,0xC0,0xBE,0xBB,0xB8,0xB5,0xB2,
// 	0xB0,0xAD,0xAA,0xA7,0xA4,0xA1,0x9E,0x9B,0x98,0x95,0x92,0x8F,0x8B,0x88,0x85,0x82,
// 	
// 	0x7F,0x7C,0x79,0x76,0x73,0x6F,0x6C,0x69,0x66,0x63,0x60,0x5D,0x5A,0x57,0x54,0x51,
// 	0x4E,0x4C,0x49,0x46,0x43,0x40,0x3E,0x3B,0x38,0x36,0x33,0x31,0x2E,0x2C,0x2A,0x27,
// 	0x25,0x23,0x21,0x1F,0x1D,0x1B,0x19,0x17,0x15,0x14,0x12,0x10,0x0F,0x0E,0x0C,0x0B,
// 	0x0A,0x09,0x07,0x06,0x05,0x05,0x04,0x03,0x02,0x02,0x01,0x01,0x01,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x02,0x02,0x03,0x04,0x05,0x05,0x06,0x07,0x09,
// 	0x0A,0x0B,0x0C,0x0E,0x0F,0x10,0x12,0x14,0x15,0x17,0x19,0x1B,0x1D,0x1F,0x21,0x23,
// 	0x25,0x27,0x2A,0x2C,0x2E,0x31,0x33,0x36,0x38,0x3B,0x3E,0x40,0x43,0x46,0x49,0x4C,
// 	0x4E,0x51,0x54,0x57,0x5A,0x5D,0x60,0x63,0x66,0x69,0x6C,0x6F,0x73,0x76,0x79,0x7C
	//SQUARE WAVE
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
// 	
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
// 	0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff
};

/*
 +--------------------------------------+
 |        FORWARDS						|
 +--------------------------------------+
*/
void soundProcess();

/*
 +--------------------------------------+
 |        VARIABLES					 	|
 +--------------------------------------+
*/
/*
 +--------------------------------------+
 |        STRUCTS               	 	|
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        LOCAL FLASH CONSTANTS		 	|
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS CONSTANTS 	|
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        STRUCTS AND UNIONS		    |
 +--------------------------------------+
*/
struct
{
	uint8_t						waveIndex;
	uint8_t						waveFreq;
	class_Timer					timer;
}_sound;
/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize Sound Driver				                            |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+


void    class_Sound::Initialize()
{
	uint8_t sreg=SREG;
	
	//disable interrupts
	cli();
	//overwrite port
 	_SOUND_PORT_DIR|=(1<<_SOUND_PIN);
	//add callback
	_sound.timer.setHandleCallBack(soundProcess);
	//restore SREG state
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize Sound Driver											|
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_Sound::UnInitialize()
{
	uint8_t sreg=SREG;
	cli();
	//unInitialize sound driver

	//restore SREG state
	SREG=sreg;

}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  TIMER0 ISR			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void soundProcess()
{
	//pump wave index
	_sound.waveIndex+=_sound.waveFreq;
	//OCR0A=pgm_read_byte_far(&SIN_TABLE[_sound.waveIndex]);
	//if (pgm_read_byte_far(&SIN_TABLE[_sound.waveIndex]) & 0x80)
	if (_sound.waveIndex>127)
	{
		_SOUND_PORT_OUTPUT|=(1<<_SOUND_PIN);
	}
	else
	{
		_SOUND_PORT_OUTPUT&=~(1<<_SOUND_PIN);
	}
}
/*
        +-----------------------------------------------+
        |       PUBLIC CONSTRUCTORS AND DESTRUCTORS     |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor                                                       |
//	| @NAME    :								  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Sound::class_Sound()
{
	static bool initialize=false;

	//Initialize PID
	if (initialize==false)
	{
		initialize=true;
		Initialize();
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Sound::~class_Sound()
{
	//Initialize PID
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Tone with a specific frequency			                    |
//	| @NAME    :  tone									                            |
//	| @INPUT   :  toneFrequency					                                    |
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Sound::tone(uint16_t toneFrequency)
{
	_sound.waveFreq=(toneFrequency*256L)/_TIMER_INTERRUPT_FREQUENCY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Stop Tone frequency												|
//	| @NAME    :  noTone									                        |
//	| @INPUT   :  																	|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Sound::noTone()
{
	_sound.waveFreq=0;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Make a 2000Hz tone with specific time duration in millisecond		|
//	| @NAME    :  beep											                        |
//	| @INPUT   :  																	|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Sound::beep(uint16_t durationInMsON/* =50 */,uint16_t durationInMSOFF/* =50 */,uint16_t frequency)
{
	tone(frequency);
	_sound.timer.delayMilliseconds(durationInMsON);
	noTone();
	_sound.timer.delayMilliseconds(durationInMSOFF);
}
