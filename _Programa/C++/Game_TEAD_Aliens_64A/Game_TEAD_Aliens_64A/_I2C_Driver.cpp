/*	
	//////////////////////////////////////////////////////////////////////////////////////////
			  _____ _                 _____ ___   _____   _____       _
			 / ____| |               |_   _|__ \ / ____| |  __ \     (_)
			| |    | | __ _ ___ ___    | |    ) | |      | |  | |_ __ ___   _____
			| |    | |/ _` / __/ __|   | |   / /| |      | |  | | '__| \ \ / / _ \
			| |____| | (_| \__ \__ \  _| |_ / /_| |____  | |__| | |  | |\ V /  __/
			 \_____|_|\__,_|___/___/ |_____|____|\_____| |_____/|_|  |_| \_/ \___|

	//////////////////////////////////////////////////////////////////////////////////////////
	-------------------------------------- C++ FILE (tab 4)-----------------------------------
*/



/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/

#include "_I2C_Driver.h"

/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/
#if defined(ESP8266)
	#define _I2C_DELAY	2
#else
	#define _I2C_DELAY   1
#endif
/*
 +--------------------------------------+
 |        VARIABLES					 	|
 +--------------------------------------+
*/
struct  
{
	uint8_t		delay=1;			//i2c delay in microseconds
	I2CSpeed	speed;				//default speed 100Kbps
}_i2c;
/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/


//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize I2C Drive				                                |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+


void    class_I2C::Initialize()
{
#ifdef ESP8266
	pinMode(_I2C_SCL_PIN, OUTPUT);
	pinMode(_I2C_SDA_PIN, INPUT);
#else
	uint8_t sreg;
	//save SREG
	sreg=SREG;
	//SCL high by external resistor
	_I2C_PORT_OUTPUT&=~(1<<_I2C_SCL);
	//SDA input
	_I2C_PORT_OUTPUT&=~(1<<_I2C_SDA);
	//SLC hibh by external resistor
	_I2C_PORT_DIR   &=~(1<<_I2C_SCL);
	//SDA AS INPUT
	_I2C_PORT_DIR	&=~(1<<_I2C_SDA);
	//set 100kps
	setSpeed(I2CSpeed::CLOCK_100KHZ);
	//restore SREG state
	SREG=sreg;
#endif
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ZERO Cross Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_I2C::UnInitialize()
{
	uint8_t sreg;
#ifdef ESP8266
	pinMode(_I2C_SCL_PIN, INPUT);
	pinMode(_I2C_SDA_PIN, INPUT);
#else
	//save SREG
	sreg=SREG;
	//disable interrupts
	cli();
	//SCL AND SDA LOW
	_I2C_PORT_OUTPUT&=~((1<<_I2C_SCL)|(1<<_I2C_SDA));
	//SLC AND SDA AS INPUT HI IMPEDANCE
	_I2C_PORT_OUTPUT&=~((1<<_I2C_SCL)|(1<<_I2C_SDA));
	//restore SREG state
	SREG=sreg;
#endif
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
class_I2C::class_I2C()
{
	//Initialize i2c
    //Initialize();
	//SCL high by external resistor
	_I2C_PORT_OUTPUT&=~(1<<_I2C_SCL);
	//portAndBit(this->output,(1<<this->pinSLC));
	//SDA input
	_I2C_PORT_OUTPUT&=~(1<<_I2C_SDA);
	//portAndBit(this->output,(1<<this->pinSDA));
	//SLC hibh by external resistor
	_I2C_PORT_DIR   &=~(1<<_I2C_SCL);
	//portAndBit(this->dir,(1<<this->pinSLC));
	//SDA AS INPUT
	_I2C_PORT_DIR	&=~(1<<_I2C_SDA);
	//portAndBit(this->dir,(1<<this->pinSDA));

}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_I2C::~class_I2C()
{
	//Initialize i2c
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set I2C Delay in microseconds					                    |
//	| @NAME    :  I2C_Delay															|
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  This function determine I2C speed				                    |
//	+-------------------------------------------------------------------------------+
void class_I2C::setDelay(uint8_t delayInMicroseconds)
{
	_i2c.delay=delayInMicroseconds;
	_i2c.speed=I2CSpeed::CLOCK_OTHER;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set I2C Speed														|
//	| @NAME    :  setSpeed															|
//	| @INPUT   :  speed in kbps                                                     |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_I2C::setSpeed(I2CSpeed kbps)
{
	_i2c.speed=kbps;
	_i2c.delay=0;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Make I2C Delay between clocks					                    |
//	| @NAME    :  I2C_Delay															|
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  Used assembler language due speed and compaction                  |
//	+-------------------------------------------------------------------------------+
inline void class_I2C::I2C_Delay()
{
	switch(_i2c.speed)
	{
		case I2CSpeed::CLOCK_100KHZ:
			_delay_us(4);
		break;
		case I2CSpeed::CLOCK_400KHZ:
			_delay_us(2);
		break;
		case I2CSpeed::CLOCK_OTHER:
			for(uint8_t i=0;i<_i2c.delay;i++) _delay_us(1);
		break;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Start I2C START CONTIDION                                        |
//	| @NAME    :  Start									                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+  
//  | Timing
//  |
//  | SDA   .....--------+                  T=~2 uS
//  |                    |
//  |                    +---------......
//  | SCL   .....-----------------+
//  |                             |
//  |                             |......
//  |            \-- T --/\-- T --/
//  +--------------------------------------------------------------------------------
void class_I2C::Start()
{
	//i2c delay
	I2C_Delay();
	//SDA low
	_I2C_PORT_DIR   |=(1<<_I2C_SDA);
	//portOr(this->dir,((uint8_t)1<<this->pinSDA));
	//i2c delay
	I2C_Delay();
	//SCLlow
	_I2C_PORT_DIR   |=(1<<_I2C_SCL);
	//portOrBit(this->dir,this->pinSLC);
	//i2c delay
	I2C_Delay();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Start I2C STOP CONDITION                                         |
//	| @NAME    :  Start									                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//  | Timing
//  |
//  | SDA                +---------.....    T=~2 uS
//  |                    |
//  |       .....________+
//  | SCL        +-----------------.....
//  |            |
//  |            |
//  |       .....\-- T --/\-- T --/
//  +--------------------------------------------------------------------------------
void class_I2C::Stop()
{
	//i2c delay
	I2C_Delay();
	//Put SCL High
	_I2C_PORT_DIR   &=~(1<<_I2C_SCL);
	//i2c delay
	I2C_Delay();
	//Put SDA High
	_I2C_PORT_DIR  &=~(1<<_I2C_SDA);
	//2 i2c delay
	I2C_Delay();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Output I2C Bit				                                    |
//	| @NAME    :  BitOut								                            |
//	| @INPUT   :  true=1 false=0                                                    |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//  | Timing
//  |
//  | SDA   .....+-------------------------+.....   T=~2 uS
//  |            | Data bit stabilished    |
//  |       .....+-------------------------+.....
//  | SCL                +--------+
//  |                    |        |
//  |       .....--------+        +--------+.....
//  |            \-- T --/\-- T --/\-- T --/
//	+--------------------------------------------------------------------------------

void	class_I2C::BitOut(uint8_t bitvalue)
{
	(bitvalue & 1)?_I2C_PORT_DIR&=~(1<<_I2C_SDA):_I2C_PORT_DIR|=(1<<_I2C_SDA);
	//I2C Delay
	I2C_Delay();
	//Time to SCL high
	_I2C_PORT_DIR &=~(1<<_I2C_SCL);
	//I2C Delay
	I2C_Delay();
	//time to SCL low
	_I2C_PORT_DIR|=(1<<_I2C_SCL);
	//I2C delay
	I2C_Delay();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Input I2C Bit					                                    |
//	| @NAME    :  BitOut								                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  True=1 false=0					                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//  | Timing
//  |
//  | SDA   .....+-------------------------+.....   T=~2 uS
//  |            | Data bit stabilished    |
//  |       .....+-------------------------+.....
//  | SCL                +--------+
//  |                    |        |
//  |       .....--------+        +--------+.....
//  |            \-- T --/\-- T --/\-- T --/
//	+--------------------------------------------------------------------------------

uint8_t	class_I2C::BitIn()
{
	uint8_t retBit;
	
	//SCL LOW
	_I2C_PORT_DIR|=(1<<_I2C_SCL);
	//wait t time
	I2C_Delay();
	//set SCL high
	_I2C_PORT_DIR&=~(1<<_I2C_SCL);
	//wait t time
	//I2C_Delay();		//TALVEZ NÃO PRECISE DESTE DELAY
	//get data from input I2C line
	(_I2C_PORT_INPUT & (1<<_I2C_SDA))?retBit=1:retBit=0;
	//wait t time
	I2C_Delay();
	//set SCL low
	_I2C_PORT_DIR|=(1<<_I2C_SCL);
	//wait t time
	I2C_Delay();
	//return bit
	return retBit;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Byte Output					                                    |
//	| @NAME    :  ByteOut								                            |
//	| @INPUT   :  Data to be send                                                   |
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_I2C::ByteOut(uint8_t data)
{
	for(uint8_t i=0;i<8;i++)
	{
		if ((data & 0x80)==0) BitOut(0); else BitOut(1);
		data<<=1;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Byte Input					                                    |
//	| @NAME    :  ByteIn								                            |
//	| @INPUT   :  none			                                                    |
//	| @OUTPUT  :  received Byte						                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint8_t	class_I2C::ByteIn()
{
	uint8_t recByte=0;
	uint8_t	mask=0x80;

	for(uint8_t i=0;i<8;i++)
	{
		if (BitIn()==1)
		{
			recByte|=mask;
		}
		mask>>=1;
	}
	return recByte;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Ack Status				                                    |
//	| @NAME    :  AckIn									                            |
//	| @INPUT   :  none			                                                    |
//	| @OUTPUT  :  0 or 1							                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint8_t class_I2C::AckIn()
{
	//return BitIn();
	uint8_t retBit;
	
	//SCL LOW
	_I2C_PORT_DIR|=(1<<_I2C_SCL);
	//wait t time
	I2C_Delay();
	//set SCL high
	_I2C_PORT_DIR&=~(1<<_I2C_SCL);
	//wait t time
	//I2C_Delay();		//TALVEZ NÃO PRECISE DESTE DELAY
	//get data from input I2C line
	(_I2C_PORT_INPUT & (1<<_I2C_SDA))?retBit=1:retBit=0;
	//wait t time
	I2C_Delay();
	//set SCL low
	_I2C_PORT_DIR|=(1<<_I2C_SCL);
	//wait t time
	I2C_Delay();
	//return bit
	return retBit;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Ack Status				                                    |
//	| @NAME    :  AckIn									                            |
//	| @INPUT   :  none			                                                    |
//	| @OUTPUT  :  0 or 1							                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_I2C::AckOut(uint8_t bitStatus)
{
	BitOut(bitStatus);
}