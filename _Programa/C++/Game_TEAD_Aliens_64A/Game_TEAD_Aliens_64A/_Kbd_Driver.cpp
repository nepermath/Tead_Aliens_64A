/*
 /////////////////////////////////////////////////////////////////////////////////////////

						 _   __            ______      _
						| | / /            |  _  \    (_)
						| |/ /  ___ _   _  | | | |_ __ ___   _____
						|    \ / _ \ | | | | | | | '__| \ \ / / _ \
						| |\  \  __/ |_| | | |/ /| |  | |\ V /  __/
						\_| \_/\___|\__, | |___/ |_|  |_| \_/ \___|
									 __/ |
									|___/

 /////////////////////////////////////////////////////////////////////////////////////////
  --------------------------------- IO C++ File (tab 4) ----------------------------------
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Kbd_Driver.h"


/*
 +--------------------------------------+
 |        STRUCTS AND UNIONS		    |
 +--------------------------------------+
*/
struct structKbd
{
	class_ADC	adc;
}_Kbd;
/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/


//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize ZERO CROSS Drive		                                |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+


void    class_KBD::Initialize()
{
	uint8_t sreg;

	//save SREG
	sreg=SREG;
	//Define KEYBOARD input with pull up
	_KEY_PORT_OUTPUT|=(1<<_KEY_A_PIN)|(1<<_KEY_B_PIN);
	_KEY_PORT_DIR&=~((1<<_KEY_A_PIN)|(1<<_KEY_B_PIN));
	//portOr(this->PortOut,(1<<this->BitAKey)|(1<<this->BitBKey));
	//portAnd(this->PortDir,(1<<this->BitAKey)|(1<<this->BitBKey));
	//restore SREG state
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ZERO Cross Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_KBD::UnInitialize()
{
	uint8_t sreg;

	//save SREG
	sreg=SREG;
	//disable interrupts
	cli();
	//Define KEYBOARD input hi-z
	_KEY_PORT_OUTPUT&=~((1<<_KEY_A_PIN)|(1<<_KEY_B_PIN));
	_KEY_PORT_DIR&=~((1<<_KEY_A_PIN)|(1<<_KEY_B_PIN));
	//portAnd(this->PortOut,(1<<this->BitAKey)|(1<<this->BitAKey));
	//portAnd(this->PortDir,(1<<this->BitAKey)|(1<<this->BitAKey));
	//restore SREG state
	SREG=sreg;
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
class_KBD::class_KBD()
{
	//set default ports bits
	/*
	this->PortOut=&_KEY_PORT_OUTPUT;
	this->PortIn=&_KEY_PORT_INPUT;
	this->PortDir=&_KEY_PORT_DIR;
	this->BitAKey=_KEY_A_PIN;
	this->BitBKey=_KEY_B_PIN;
	*/
	//Initialize Keyboard
    Initialize();
	//portOr(this->PortOut,(1<<this->BitAKey)|(1<<this->BitBKey));
	//portAnd(this->PortDir,(1<<this->BitAKey)|(1<<this->BitBKey));	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor #2 with port and bits for A key and B key             |
//	| @NAME    :								  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
// class_KBD::class_KBD(PORT kbdPortOut,PORT kbdPortIn,PORT kbdPortDir,uint8_t bitKbdA/* =6 */,uint8_t bitKbdB/* =5 */)
// {
// 	this->PortOut=kbdPortOut;
// 	this->PortIn=kbdPortIn;
// 	this->PortDir=kbdPortDir;
// 	this->BitAKey=bitKbdA;
// 	this->BitBKey=bitKbdB;
// 	//initialize key
// 	//Initialize();
// 	portOr(this->PortOut,(1<<this->BitAKey)|(1<<this->BitBKey));
// 	portAnd(this->PortDir,(1<<this->BitAKey)|(1<<this->BitBKey));
// 
// }
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_KBD::~class_KBD()
{
	//Initialize Keyboard
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: return Kbd state													|
//	|@NAME    : getKbdtate    	        					                        |
//	|@INPUT   :														                |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :								                       	                |
//	+-------------------------------------------------------------------------------+
Kbd class_KBD::getKbdState()
{
	uint8_t		tmpKey,tmp;
	ADCKeyX		kx;
	ADCKeyY		ky;
	ADCKeySW	ksw;
	//assume none keys pressed
	tmpKey=0;
	//get Key State
	//tmp=portRead(_Kbd.PortIn);
	tmp=_KEY_PORT_INPUT;
	//get key from joystick
	_Kbd.adc.getKeys(kx,ky,ksw);
	//return code
	if ((tmp & (1<<_KEY_A_PIN))==0)		tmpKey|=(uint8_t)Kbd::ENTER;
	if ((tmp & (1<<_KEY_B_PIN))==0)		tmpKey|=(uint8_t)Kbd::B;
	if (kx==ADCKeyX::X_MINUS)		    tmpKey|=(uint8_t)Kbd::LEFT;
	if (kx==ADCKeyX::X_PLUS)		    tmpKey|=(uint8_t)Kbd::RIGHT;
	if (ky==ADCKeyY::Y_MINUS)		    tmpKey|=(uint8_t)Kbd::UP;
	if (ky==ADCKeyY::Y_PLUS)		    tmpKey|=(uint8_t)Kbd::DOWN;
	if (ksw==ADCKeySW::SW_PRESSED)	    tmpKey|=(uint8_t)Kbd::A;
	//no key return none
	return (Kbd)tmpKey;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: Wait Key release													|
//	|@NAME    : waitKeyRelease 	        					                        |
//	|@INPUT   :														                |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :								                       	                |
//	+-------------------------------------------------------------------------------+
void class_KBD::waitKbdRelease()
{	
	do
	{
		_delay_ms(50);
	} while (getKbdState()!=Kbd::NONE);
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: return Kbd ASCII code												|
//	|@NAME    : getKeyASCII    	        					                        |
//	|@INPUT   :														                |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :								                       	                |
//  +-------------------------------------------------------------------------------+
// | Get Keys State ASCII															|
// | NORMAL KEYS																	|
// |  0 - key NONE  ' ' SPACE														|
// |  1 - key LEFT  'L' LEFT														|
// |  2 - key ENTER 'E' ENTER														|
// |  4 - key RIGHT 'R' RIGHT														|
// |  8 - key UP    'U' UP															|
// | 16 - key DOWN  'D' DOWN														|
// |  3 - Key LEFT+ENTER  'X' DOWN													|
// |  6 - Key RIGHT+ENTER 'Y' DOWN													|
// | 10 - Key UP+ENTER    'T' DOWN													|
// | 18 - Key DOWN+ENTER  'Y' DOWN													|
// | 31 - ALL KEYS PRESSED 'A'														|
// | 32 - Key A 'A'																	|
// | 64 - Key B 'B'																	|		
// |																				|
// | DIAGONAL KEYS																	|
// |																				|
// |   +----------+-----+----------+												|
// |   | UP LEFT  |  UP | UP RIGHT |												|
// |   |    7     |   8 |    9     |												|
// |   +----------+-----+----------+												|
// |   |  LEFT    |ENTER|  RIGHT   |												|
// |   |    4     |  5  |    6     |												|
// |   +----------+-----+----------+												|
// |   |DOWN LEFT |DONW |DONW RIGHT|												|
// |   |    1     |  2  |     3    |												|
// |   +----------+-----+----------+												|
// |   Key A 'A'																	|
// |   Key B 'B'																	|
// |																				|
//+---------------------------------------------------------------------------------+
char class_KBD::getKbdASCII(bool diagonals)
{
	Kbd kb=getKbdState();
	
	if (diagonals)
	{
		switch((uint8_t)kb)
		{
			case (uint8_t)Kbd::NONE:return ' ';
			case (uint8_t)Kbd::UP:return '8';
			case (uint8_t)Kbd::DOWN:return '2';
			case (uint8_t)Kbd::LEFT:return '4';
			case (uint8_t)Kbd::RIGHT:return '6';
			case (uint8_t)Kbd::ENTER:return 'E';
			case (uint8_t)Kbd::A:return 'A';
			case (uint8_t)Kbd::B:return 'B';			
			case (uint8_t)Kbd::LEFT+(uint8_t)Kbd::DOWN:return '1';	
			case (uint8_t)Kbd::LEFT+(uint8_t)Kbd::UP:return '7';	
			case (uint8_t)Kbd::RIGHT+(uint8_t)Kbd::DOWN:return '3';	
			case (uint8_t)Kbd::RIGHT+(uint8_t)Kbd::UP:return '9';	
		}
	}
	else
	{
		switch ((uint8_t)kb)
		{
			case (uint8_t)Kbd::NONE:return ' ';
			case (uint8_t)Kbd::A:return 'A';
			case (uint8_t)Kbd::B:return 'B';
			case (uint8_t)Kbd::LEFT:return 'L';
			case (uint8_t)Kbd::ENTER:return 'E';
			case (uint8_t)Kbd::RIGHT:return 'R';
			case (uint8_t)Kbd::UP:return 'U';
			case (uint8_t)Kbd::DOWN:return 'D';
			case (uint8_t)Kbd::LEFT+(uint8_t)Kbd::ENTER:return 'X';
			case (uint8_t)Kbd::RIGHT+(uint8_t)Kbd::ENTER:return 'Y';
			case (uint8_t)Kbd::UP+(uint8_t)Kbd::ENTER:return 'T';
			case (uint8_t)Kbd::DOWN+(uint8_t)Kbd::ENTER:return 'V';
			default:
			return ' ';
		}		
	}
	//this return if put here only to avoid compiler warning message
	return '0';
}