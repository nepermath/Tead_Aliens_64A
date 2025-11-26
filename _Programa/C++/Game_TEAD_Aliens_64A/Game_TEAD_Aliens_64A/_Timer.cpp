/*
	#-------------------------------------------------------------------------------#
 	|																				|
 	|		   _____ _                      ______      _							|
 	|		  |_   _(_)                     |  _  \    (_)							|
 	|			| |  _ _ __ ___   ___ _ __  | | | |_ __ ___   _____ _ __			|
 	|			| | | | '_ ` _ \ / _ \ '__| | | | | '__| \ \ / / _ \ '__|			|
 	|			| | | | | | | | |  __/ |    | |/ /| |  | |\ V /  __/ |				|
 	|			\_/ |_|_| |_| |_|\___|_|    |___/ |_|  |_| \_/ \___|_|				|
 	|																				|
	| Este Drive implementa funções para manipulação de tempo , tais como delay		|
	| time_handle, time measure etc.												|
	#-------------------------------------------------------------------------------#
	| Este documento usa TAB 4 para formatação										|
	#-------------------------------------------------------------------------------#
	| Date: Brasilia ,12 de Agosto de 2016											|
	#-------------------------------------------------------------------------------#
 */


 /*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/

#include "_Timer.h"
/*
 +--------------------------------------+
 |        LOCAL CONSTANTS			    |
 +--------------------------------------+
*/
#define _TIMER_DIV_TO_1KHZ	(_TIMER_INTERRUPT_FREQUENCY/1000)
#define _TIMER_MAX_CALL_BACKS	4
/*
 +--------------------------------------+
 |        LOCAL VARIBLES STRUCT		    |
 +--------------------------------------+
*/

static volatile struct time_Struct
{
	bool		running=true;
	uint8_t		div_to_millisecons=0;							//divisor to obtain 1ms timer count
	uint32_t	millisecondsCount=0;							//milliseconds count	
	void		(*timerHandleCallBack)(void);					//timer handle call back
}_timer;
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize ZERO CROSS Drive		                                |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void    class_Timer::Initialize()
{
	uint8_t sreg=SREG;
// 	//Disable interrupts during initialization
 	cli();

	//CALIBRAT INTERNAL RC
	//OSCCAL=96;

	//set timer 1 to operate as CTC mode 0100 prescaler 8x
	TCCR1A&=~((1<<WGM11)|(1<<WGM10));
	TCCR1B&=~((1<<WGM13)|(1<<WGM12)|(1<<CS12)|(1<<CS11)|(1<<CS10));
	TCCR1B|=(1<<WGM12)|(0<<CS12)|(1<<CS11)|(0<<CS10);
	//set divisor
	OCR1A=(F_CPU/_TIMER_PRESCALER/ _TIMER_INTERRUPT_FREQUENCY)-1;
	//set interrupt
	TIMSK|=(1<<OCIE1A);
	//initialize callbacks
	_timer.timerHandleCallBack=nullptr;
	_timer.running=true;
	_timer.div_to_millisecons=0;
	_timer.millisecondsCount=0;
// 	//restore SREG
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ZERO Cross Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_Timer::UnInitialize()
{
	uint8_t sreg;

	//save SREG
	sreg=SREG;
	//disable interrupts
	cli();
	//stop timer
	TCCR1B&=~((1<<CS22)|(1<<CS21)|(1<<CS20));
	//restore SREG state
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor                                                       |
//	| @NAME    :  constructor							                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+

class_Timer::class_Timer()
{
	//if time not initialize the initialize
	static bool bInit=true;

	if (bInit)
	{
		bInit=false;
		Initialize();
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor                                                        |
//	| @NAME    :  Destructor							                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+

class_Timer::~class_Timer()
{
	//unInitialize Time
	UnInitialize();
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  ISR (Interrupt Service Routine)                                   |
//	| @NAME    :  ISR									                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :														            |
//	+-------------------------------------------------------------------------------+

ISR(TIMER1_COMPA_vect)
{
	//Allow other interrupts occur
	//sei();
	//pump milliseconds divisor
	_timer.div_to_millisecons++;

	//time to pump milliseconds
	if (_timer.div_to_millisecons>=_TIMER_DIV_TO_1KHZ)
	{
		//yes, clear and pump milliseconds
		_timer.div_to_millisecons=0;

		//digitalWrite(15, !digitalRead(15));
		//Pump milliseconds
		if (_timer.running)
		{
			_timer.millisecondsCount++;
		}
	}
	//process call back functions
	if (_timer.timerHandleCallBack!=nullptr) _timer.timerHandleCallBack();
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Stop Timer														|
//	| @NAME    :  Stop																|
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_Timer::stop()
{
	_timer.running=false;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Start Timer														|
//	| @NAME    :  Start																|
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_Timer::start()
{
	_timer.running=true;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Milliseconds since overload #1	                            |
//	| @NAME    :  GetMilliseconds						                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint32_t	class_Timer::getMilliseconds()
{
	uint32_t	tmp1=0,tmp2=0;
	do
	{
		sei();
		//get two sequential time
		tmp1=_timer.millisecondsCount;
		sei();
		tmp2=_timer.millisecondsCount;
	} while (tmp1!=tmp2);
	//return time
	return tmp2;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Elapsed Time to time measuring	                            |
//	| @NAME    :  SetElapsed							                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_Timer::setElapsed(uint32_t &elapsedTimer)
{
	elapsedTimer=this->getMilliseconds();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Elapsed Time to time measuring	                            |
//	| @NAME    :  GetElapsed							                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint32_t	class_Timer::getElapsed(uint32_t &elapsedTimer)
{
	return this->getMilliseconds()-elapsedTimer;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Delay in Milliseconds                                             |
//	| @NAME    :  DelayMilliseconds						                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_Timer::delayMilliseconds(uint32_t milliseconds)
{
	uint32_t	tmp;

	//get actual time
	tmp=this->getMilliseconds();
	//loop until exit
	do
	{
	} while ((this->getMilliseconds()-tmp)<milliseconds);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set IR Handle CallBack							                |
//	| @NAME    :  SetHandleCallBack						                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_Timer::setHandleCallBack(void (*timerHandleCallBack)())
{
	//set new call back
	_timer.timerHandleCallBack=timerHandleCallBack;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get IR Handle CallBack								            |
//	| @NAME    :  GetHandleCallBack						                            |
//	| @INPUT   :  none									                            |
//	| @OUTPUT  :  call back							                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
timerReturnCallBack	class_Timer::getHandleCallBack(int8_t callBackIndex)
{
	//get handle
	return _timer.timerHandleCallBack;
}
