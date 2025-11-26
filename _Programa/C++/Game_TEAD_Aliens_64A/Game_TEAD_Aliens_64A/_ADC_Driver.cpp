/*
 /////////////////////////////////////////////////////////////////////////////////////////
			  ___ ______  _____  ______      _
			 / _ \|  _  \/  __ \ |  _  \    (_)
			/ /_\ \ | | || /  \/ | | | |_ __ ___   _____ _ __
			|  _  | | | || |     | | | | '__| \ \ / / _ \ '__|
			| | | | |/ / | \__/\ | |/ /| |  | |\ V /  __/ |
			\_| |_/___/   \____/ |___/ |_|  |_| \_/ \___|_|

 /////////////////////////////////////////////////////////////////////////////////////////
  --------------------------------- IO C++ File (tab 4) ----------------------------------
  
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_ADC_Driver.h"

/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/

#define _ADC_DEFAULT_AVERAGE_X 512
#define _ADC_DEFAULT_AVERAGE_Y 512
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
struct  
{
	int				midX;				//mid value of joystick when released
	int				midY;				//mid value of joystick when released
	class_Timer		timer;
}_adc;

/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize ADC					                                |
//	| @NAME    :  InitializeADC		              		                            |
//	| @INPUT   :  ADC prescaler  													|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  prescaler must be 2,4,8,16,32,64 or 128							|
//	+-------------------------------------------------------------------------------+
void	class_ADC::ADCInitialize(uint8_t prescalerFactor)
{
	uint8_t sreg,prescalerLog;
	//save SREG
	sreg=SREG;
	//disable interrupts
	cli();
	//set ADC input with high z
	_ADC_PORT_OUTPUT|=((1<<_ADC_AXIS_X_PIN)|(1<<_ADC_AXIS_Y_PIN));
	_ADC_PORT_DIR&=~((1<<_ADC_AXIS_X_PIN)|(1<<_ADC_AXIS_Y_PIN));
	//set ADC switch input to input with pull up
	_ADC_SW_PORT_OUTPUT |= (1<<_ADC_SWITCH_PIN);
	_ADC_SW_PORT_DIR	&=~(1<<_ADC_SWITCH_PIN);
	//set reference to analog AVCC
	ADMUX&=~((1<<REFS1)|(1<<REFS0));
	ADMUX|=(1<<REFS0);
	//no left adjust
	ADMUX|=(1<<ADLAR);
	//select channel 0
	ADMUX&=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
	//first compute log2(prescalerFactor)
	prescalerLog=7;
	if (prescalerFactor==0) prescalerFactor=1;
	for(;;)
	{
		//exit if log computed checking bit 7
		if ((prescalerFactor & (1<<7))!=0) break;
		//shift value
		prescalerFactor<<=1;
		//compute log
		prescalerLog--;
	}
	//Set prescaler
	if ((prescalerLog & (1<<0))==0)	ADCSRA&=~(1<<ADPS0); else ADCSRA|=(1<<ADPS0);
	if ((prescalerLog & (1<<1))==0)	ADCSRA&=~(1<<ADPS1); else ADCSRA|=(1<<ADPS1);
	if ((prescalerLog & (1<<2))==0)	ADCSRA&=~(1<<ADPS2); else ADCSRA|=(1<<ADPS2);
	//start first conversion
	ADCSRA|=(1<<ADEN)|(1<<ADSC);
	do {
		
	} while ((ADCSRA & (1<<ADSC))!=0);
	//restore SREG
	SREG=sreg;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize ADC Driver												|
//	| @NAME    :  Initialize                      									|
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_ADC::Initialize()
{
	uint8_t sreg=SREG;
	
	//disable interrupts
	cli();
	//initialize adc
	ADCInitialize(64);
	//set default mid values
	_adc.midX=_ADC_DEFAULT_AVERAGE_X;
	_adc.midY=_ADC_DEFAULT_AVERAGE_Y;
	//Set ADC Switch input pull up
	_ADC_SW_PORT_OUTPUT|= (1<<_ADC_SWITCH_PIN);
	_ADC_SW_PORT_DIR   &=~(1<<_ADC_SWITCH_PIN);
	//restore SREG state
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ADC Driver											|
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_ADC::UnInitialize()
{
	uint8_t sreg=SREG;
	cli();
	//Set ADC Switch input hi-z
	_ADC_SW_PORT_OUTPUT&=~(1<<_ADC_SWITCH_PIN);
	_ADC_SW_PORT_DIR   &=~(1<<_ADC_SWITCH_PIN);	
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
class_ADC::class_ADC()
{
	static bool initialize=false;

	//Initialize ADC
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
class_ADC::~class_ADC()
{
	//UnInitialize ADC
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get ADC Value from a specific channel				                |
//	| @NAME    : getValue                   										|
//	| @INPUT   : ADC Channel														|
//	| @OUTPUT  : ADC Value								                            |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
int class_ADC::getValue(ADCChannel adcChannel)
{
	//select ADC channel
	ADMUX&=~((1<<MUX3)|(1<<MUX2)|(1<<MUX1)|(1<<MUX0));
	//no left adjust
	//ADMUX|=(1<<ADLAR);
	ADMUX&=~(1<<ADLAR);

	switch(adcChannel)
	{
		case ADCChannel::POT_AXIS_X:
			ADMUX|=(uint8_t)ADCChannel::POT_AXIS_X;
		break;
		case ADCChannel::POT_AXIS_Y:
			ADMUX|=(uint8_t)ADCChannel::POT_AXIS_Y;
		break;
	}
	//start conversion
	ADCSRA|=(1<<ADSC);
	//wait finish
	do{
		
	} while ((ADCSRA & (1<<ADSC))!=0);
	//return value
	return 1023-ADC;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: calibrated joysticke												|
//	| @NAME    : calibrate			                   								|
//	| @INPUT   : 																	|
//	| @OUTPUT  : 																	|
//	| @REMARKS : this function get average value from joystick axis-x and axis-y	|
//	|			 during this procedure joystick must be release in default position	|
//	+-------------------------------------------------------------------------------+
#define _ADC_CAL_MAX_PASSES	16

void class_ADC::calibrate()
{
	int32_t averageX,averageY;
	
	//get average value from X axis
	averageX=0;
	for(uint8_t i=0;i<_ADC_CAL_MAX_PASSES;i++)
	{
		averageX+=getValue(ADCChannel::POT_AXIS_X);
		_delay_ms(30);
	}
	averageX/=_ADC_CAL_MAX_PASSES;
	//get average value from Y axis
	averageY=0;
	for(uint8_t i=0;i<_ADC_CAL_MAX_PASSES;i++)
	{
		averageY+=getValue(ADCChannel::POT_AXIS_Y);
		_delay_ms(30);
	}
	averageY/=_ADC_CAL_MAX_PASSES;
	//set mid points
	_adc.midX=averageX;
	_adc.midY=averageY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Joystick Presence												|
//	| @NAME    : getJoystickPresence                   								|
//	| @INPUT   : 																	|
//	| @OUTPUT  : true if present								                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
bool class_ADC::getJoystickPresence()
{
	uint8_t	jValueX,jValueY;
	uint8_t countX,countY;
	
	//make a loop of 500ms to check joystick presence
	//AXIS X
	countX=0;
	countY=0;
	for(uint8_t i=0;i<10;i++)
	{
		//check if joystick value of AXIS X and AXIS Y
		jValueX=getValue(ADCChannel::POT_AXIS_X);
		jValueY=getValue(ADCChannel::POT_AXIS_Y);
		//pump counts if  values =255
		if (jValueX==255) countX++;
		if (jValueY==255) countY++;
		_adc.timer.delayMilliseconds(2);
	}
	//return joy presence state
	if (countX==10 && countY==10) 
		return false;
	else
		return true;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Average Value of X-Axis of Joystick 							|
//	| @NAME    : getAverageXAxis                  									|
//	| @INPUT   : 																	|
//	| @OUTPUT  : Average X-Axis value							                    |
//	| @REMARKS : use calibrate function to get correctly result of this function	|
//	+-------------------------------------------------------------------------------+
int class_ADC::getAverageXAxis()
{
	return _adc.midX;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Average Value of X-Axis of Joystick 							|
//	| @NAME    : getAverageXAxis                  									|
//	| @INPUT   : 																	|
//	| @OUTPUT  : Average X-Axis value							                    |
//	| @REMARKS : use calibrate function to get correctly result of this function	|
//	+-------------------------------------------------------------------------------+
int class_ADC::getAverageYAxis()
{
	return _adc.midY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get X Y Axis values 												|
//	| @NAME    : getXY                  											|
//	| @INPUT   : 																	|
//	| @OUTPUT  : X-Axis value,Y-Axis value						                    |
//	| @REMARKS : use calibrate function to get correctly result of this function	|
//	+-------------------------------------------------------------------------------+
void class_ADC::getXY(int &x,int &y)
{
	x=getValue(ADCChannel::POT_AXIS_X)-_adc.midX;
	y=getValue(ADCChannel::POT_AXIS_Y)-_adc.midY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Joystick Keys													|
//	| @NAME    : getKeys                  											|
//	| @INPUT   : 																	|
//	| @OUTPUT  : key X, key Y, Key SW												|
//	| @REMARKS : States true=Pressed, false=not pressed								|
//	|			 X-axis or Y-axis is considerate pressed if greater than a trigger	|
//	|			 value or Joystick SW Switch											|
//	+-------------------------------------------------------------------------------+
void class_ADC::getKeys(ADCKeyX &key_x,ADCKeyY &key_y,ADCKeySW &key_sw)
{
	int x,y;
	
	//get X Y Axis values
	getXY(x,y);
	//check X value
	if (x>250)
	{
		key_x=ADCKeyX::X_PLUS;
	}
	else
	{
		if (x<-250)
		{
			key_x=ADCKeyX::X_MINUS;
		}
		else
		{
			key_x=ADCKeyX::X_NONE;
		}
	}
	//check Y value
	if (y>200)
	{
		key_y=ADCKeyY::Y_PLUS;
	}
	else
	{
		if (y<-200)
		{
			key_y=ADCKeyY::Y_MINUS;
		}
		else
		{
			key_y=ADCKeyY::Y_NONE;
		}
	}
	if (_ADC_SW_PORT_INPUT & (1<<_ADC_SWITCH_PIN))
	{
		key_sw=ADCKeySW::SW_RELESEAD;
	}
	else
	{
		key_sw=ADCKeySW::SW_PRESSED;
	}
}	
