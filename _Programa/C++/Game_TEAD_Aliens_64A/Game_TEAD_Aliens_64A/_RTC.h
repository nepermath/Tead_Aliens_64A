/*
	//////////////////////////////////////////////////////////////////////////////////////////
         ______ _____ _____  ______      _
         | ___ \_   _/  __ \ |  _  \    (_)
         | |_/ / | | | /  \/ | | | |_ __ ___   _____ _ __
         |    /  | | | |     | | | | '__| \ \ / / _ \ '__|
         | |\ \  | | | \__/\ | |/ /| |  | |\ V /  __/ |
         \_| \_| \_/  \____/ |___/ |_|  |_| \_/ \___|_|

    //////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- HEADER FILE (tab 4)-----------------------------------
*/
#ifndef _RCT_H_
#define _RCT_H_

/*
 +--------------------------------------+
 |        HARDWARE DEPENDENT INCLUDES	|
 +--------------------------------------+
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/eeprom.h>
#include <avr/pgmspace.h>

/*
 +--------------------------------------+
 |        C LIBRARY INCLUDES		    |
 +--------------------------------------+
*/
#include <stdlib.h>
/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Timer.h"
#include "_I2C_Driver.h"

/*
	+--------------------------------------+
	|       DEFINES					       |
	+--------------------------------------+
*/
#define DS1307_ADDRESS	(0XD0)
/*
	+--------------------------------------+
	|       TYPEDEF					       |
	+--------------------------------------+
*/

//-----------------------------------------
//S1307 BIT FIELDS
//-----------------------------------------
typedef enum
{
	CH=7,
	PM_AM=5,
	H12_24=6,
	OUT=7,
	SQWE=4,
	RS1=1,
	RS0=0
}RTCBitField;
//-----------------------------------------
//DS1307 REGISTERS
//----------------------------------------- 
typedef enum class RTCReg:uint8_t
{
	SECOND=0,
	MINUTE=1,
	HOUR=2,
	DAY_OF_WEEK=3,
	DAY=4,
	MONTH=5,
	YEAR=6,
	CONTROL=7,
	RAM
}RTCReg;
//-----------------------------------------
//DS1307 Error Code
//-----------------------------------------
typedef enum class	RTCError:uint8_t
{
	OK,
	NO_ACK
}RTCError;					 
/*
        +-------------------------------------------------------+
        |        CLASS	RTC(Real Time Clock                     |
        +-------------------------------------------------------+
        | @PURPOSE      : Implements RTC(Real Time Clock)       |
        | @OBSERVATIONS :										|
        +-------------------------------------------------------+
*/

class class_RTC
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
		void	Initialize(void);
		void	UnInitialize(void);
		
        /*
         +--------------------------------------+
         |        PUBLIC FUNCTIONS		        |
         +--------------------------------------+
        */
public:
	
        /************************************************************************/
        /* Constructor                                                          */
        /************************************************************************/
        class_RTC(void);
		/************************************************************************/
		/* Destructor                                                           */
		/************************************************************************/
		~class_RTC(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Process RTC                                                       |
		//	| @NAME    :  RTC_Process								  		                |
		//	| @INPUT   :  none                                                              |
		//	| @OUTPUT  :  none								                                |
		//	| @REMARKS :  Update Time second elapsed and call alarm callback and time		|
		//	|			  callback if true													|
		//	+-------------------------------------------------------------------------------+
		static void	 RTC_Process();
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Reset Time to 0:0:0	                                            |
		//	| @NAME    :  resetClock					  		                            |
		//	| @INPUT   :																	|
		//	| @OUTPUT  : 																	|
		//	| @REMARKS :																	|
		//	+-------------------------------------------------------------------------------+
		static void	resetClock(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Stop clock	                                                    |
		//	| @NAME    :  stopClock						  		                            |
		//	| @INPUT   :																	|
		//	| @OUTPUT  : 																	|
		//	| @REMARKS : When clock in stopped state time not change						|
		//	+-------------------------------------------------------------------------------+
		 static void	stopClock(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Start clock	                                                    |
		//	| @NAME    :  startClock						  		                        |
		//	| @INPUT   :																	|
		//	| @OUTPUT  : 																	|
		//	| @REMARKS :																	|
		//	+-------------------------------------------------------------------------------+
		 static void	startClock(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Get Time	                                                        |
		//	| @NAME    :  GetTime						  		                            |
		//	| @INPUT   :  none                                                              |
		//	| @OUTPUT  :  hour,minute,second				                                |
		//	| @REMARKS :													                |
		//	+-------------------------------------------------------------------------------+
		 static void	 GetTime(uint8_t &hour,uint8_t &minute,uint8_t &second,bool fromRTC=false);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Set Time	                                                        |
		//	| @NAME    :  SetTime						  		                            |
		//	| @INPUT   :  hour,minute,second                                                |
		//	| @OUTPUT  :									                                |
		//	| @REMARKS :													                |
		//	+-------------------------------------------------------------------------------+
		 static void	 SetTime(uint8_t hour,uint8_t minute,uint8_t second,bool toRTC=false);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Get Second	                                                    |
		//	| @NAME    :  GetSecond						  		                            |
		//	| @INPUT   :																	|
		//	| @OUTPUT  :  Second									                        |
		//	| @REMARKS :													                |
		//	+-------------------------------------------------------------------------------+
		 static uint8_t 	GetSecond(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Get Minute	                                                    |
		//	| @NAME    :  GetMinute						  		                            |
		//	| @INPUT   :																	|
		//	| @OUTPUT  :  Minute									                        |
		//	| @REMARKS :													                |
		//	+-------------------------------------------------------------------------------+
		 static uint8_t	 GetMinute(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Get Hour															|
		//	| @NAME    :  GetHour						  		                            |
		//	| @INPUT   :																	|
		//	| @OUTPUT  :  Hour																|
		//	| @REMARKS :													                |
		//	+-------------------------------------------------------------------------------+
		 static uint8_t	 GetHour(void);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Set Alarm Call Back Function                                      |
		//	| @NAME    :  SetAlarmTime					  		                            |
		//	| @INPUT   :  hour,minute,second, function callback                             |
		//	| @OUTPUT  :  											                        |
		//	| @REMARKS :  set AlarmCallBack to null to disable this callback function		|
		//	+-------------------------------------------------------------------------------+
		 static void	SetALarmTime(uint8_t hour,uint8_t minute,uint8_t second,void (*AlarmCallBack)());
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Set RTC Call Back Function                                        |
		//	| @NAME    :  SetRTC					  										|
		//	| @INPUT   :  hour,minute,second, function callback                             |
		//	| @OUTPUT  :  											                        |
		//	| @REMARKS : set RTCCallBack to null to disable this callback function			|
		//	+-------------------------------------------------------------------------------+
		static void	SetRTCCallback(void (*RTCCallBack)(uint8_t hour,uint8_t minute,uint8_t second));
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Write DS1307 RTC register                                         |
		//	| @NAME    :  writeReg					  										|
		//	| @INPUT   :  Register, data												    |
		//	| @OUTPUT  :  											                        |
		//	| @REMARKS :																	|
		//	+-------------------------------------------------------------------------------+
		static RTCError writeReg(RTCReg reg,uint8_t data,bool disableInt=false);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Read DS1307 RTC register                                          |
		//	| @NAME    :  readReg					  										|
		//	| @INPUT   :  Register														    |
		//	| @OUTPUT  :  data										                        |
		//	| @REMARKS :																	|
		//	+-------------------------------------------------------------------------------+
		static RTCError readReg(RTCReg reg,uint8_t &data,bool disableInt=false);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  convert Binary to BCD												|
		//	| @NAME    :  binToBCD					  										|
		//	| @INPUT   :  int binary number													|
		//	| @OUTPUT  :  bcd 5 digits formated number										|
		//	| @REMARKS :  bcd output bit 15=0 positive number else negative  				|
		//	+-------------------------------------------------------------------------------+
		static uint16_t binToBCD(int number);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  convert BCD to Binary												|
		//	| @NAME    :  bcdToBin					  										|
		//	| @INPUT   :  3 digits BCD number												|
		//	| @OUTPUT  :  binary number														|
		//	| @REMARKS :  bcd output bit 15=0 positive number else negative  				|
		//	+-------------------------------------------------------------------------------+
		static int8_t bcdToBin(uint16_t bcd);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Set Date															|
		//	| @NAME    :  setDate					  										|
		//	| @INPUT   :  Year,Month,Day,DayOfWeek, write date into rtc if toRTC is true	|
		//	| @OUTPUT  :  																	|
		//	| @REMARKS :											 						|
		//	+-------------------------------------------------------------------------------+		
		static void setDate(uint8_t year,uint8_t month,uint8_t day,uint8_t dayOfWeek,bool toRTC=false);
		//	+-------------------------------------------------------------------------------+
		//	| @FUNCTION:  Get Date															|
		//	| @NAME    :  getDate					  										|
		//	| @INPUT   :  Year,Month,Day,DayOfWeek, get date from rtc if fromRTC is true	|
		//	| @OUTPUT  :  																	|
		//	| @REMARKS :											 						|
		//	+-------------------------------------------------------------------------------+
		static void GetDate(uint8_t &year,uint8_t &month,uint8_t &day,uint8_t &dayOfWeek,bool fromRTC=false);
		
		static void writeSRAM(uint8_t addr,uint8_t data);
		static uint8_t readSRAM(uint8_t addr);
};

#endif