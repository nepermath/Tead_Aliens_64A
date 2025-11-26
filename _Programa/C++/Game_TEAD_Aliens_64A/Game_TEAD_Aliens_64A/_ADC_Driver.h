/*
	//////////////////////////////////////////////////////////////////////////////////////////
 		 			    ___ ______  _____  ______      _
 		 			   / _ \|  _  \/  __ \ |  _  \    (_)
 		 			  / /_\ \ | | || /  \/ | | | |_ __ ___   _____ _ __
 		 			  |  _  | | | || |     | | | | '__| \ \ / / _ \ '__|
 		 			  | | | | |/ / | \__/\ | |/ /| |  | |\ V /  __/ |
 		 			  \_| |_/___/   \____/ |___/ |_|  |_| \_/ \___|_|

    //////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- HEADER FILE (tab 4)-----------------------------------
*/


#ifndef _ADC_DRIVER_H_
#define _ADC_DRIVER_H_

/*
 +--------------------------------------+
 |        HARDWARE DEPENDENT INCLUDES	|
 +--------------------------------------+
*/

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

/*
 +--------------------------------------+
 |        C LIBRARY INCLUDES		    |
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Timer.h"
/*
 +--------------------------------------+
 |        PORTS AND PIN DEFINITIONS	    |
 +--------------------------------------+
*/

//DEFINITIONS PORTS
#define _ADC_PORT_OUTPUT	PORTF	
#define _ADC_PORT_INPUT		PINF
#define _ADC_PORT_DIR		DDRF

#define _ADC_AXIS_X_PIN		0
#define _ADC_AXIS_Y_PIN		1

#define _ADC_SW_PORT_OUTPUT	PORTB
#define _ADC_SW_PORT_INPUT	PINB
#define _ADC_SW_PORT_DIR	DDRB

#define _ADC_SWITCH_PIN		4

/*
 +--------------------------------------+
 |        TYPEDEF CLASS DEFINITIONS		|
 +--------------------------------------+
*/

typedef enum class ADCChannel:uint8_t
{
	POT_AXIS_Y=0,
	POT_AXIS_X=1,
}ADCChannel;
typedef enum class ADCKeyX:uint8_t
{
	X_NONE,
	X_PLUS,
	X_MINUS,
}ADCKeyX;						 
typedef enum class ADCKeyY:uint8_t
{
	Y_NONE,
	Y_PLUS,
	Y_MINUS,
}ADCKeyY;
typedef enum class ADCKeySW:uint8_t
{
	SW_PRESSED,
	SW_RELESEAD
}ADCKeySW;

/*
        +-------------------------------------------------------+
        |        CLASS			ADC			                    |
        +-------------------------------------------------------+
        | @PURPOSE      : to get ADC Values						|
        | @OBSERVATIONS :										|
        +-------------------------------------------------------+
*/


class class_ADC
{
/*
         +--------------------------------------+
         |       PRIVATE VARIABLES		        |
         +--------------------------------------+
        */
 private:
        /*
         +--------------------------------------+
         |       PRIVATE FUNCTIONS      	    |
         +--------------------------------------+
        */
		void		ADCInitialize(uint8_t prescalerFactor);
		void		Initialize(void);
		void		UnInitialize(void);
        /*
         +--------------------------------------+
         |        PUBLIC FUNCTIONS		        |
         +--------------------------------------+
        */
public:
	
        /************************************************************************/
        /* Constructor                                                          */
        /************************************************************************/
        class_ADC(void);
		/************************************************************************/
		/* Destructor                                                           */
		/************************************************************************/
		~class_ADC(void);
		/************************************************************************/
		/* get Value from ADC channel                                           */
		/************************************************************************/
		int getValue(ADCChannel adcChannel);
		/************************************************************************/
		/* calibrated Joystick                                                  */
		/* this function get average value from joystick axis-x and axis-y		*/
		/* during this procedure joystick must be release in default position	*/
		/************************************************************************/
		void calibrate(void);
		/************************************************************************/
		/* Get Average of Axis-X                                                */
		/************************************************************************/
		int getAverageXAxis(void);
		/************************************************************************/
		/* Get Average of Axis-Y                                                */
		/************************************************************************/
		int getAverageYAxis(void);
		/************************************************************************/
		/* Get X & Y Axis values relative to normal position                    */
		/************************************************************************/
		void getXY(int &x,int &y);
		/************************************************************************/
		/* Get ADC Keys States true=Pressed, false=not pressed                  */
		/* X-axis or Y-axis is considerate pressed if greater than a trigger	*/
		/* value or Joystick SW Switch											*/
		/************************************************************************/
		void getKeys(ADCKeyX &key_x,ADCKeyY &key_y,ADCKeySW &key_sw);
		/************************************************************************/
		/* check if joystick is present  return true if present                 */
		/************************************************************************/
		bool	getJoystickPresence(void);
};

#endif