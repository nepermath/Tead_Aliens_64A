/*
 /////////////////////////////////////////////////////////////////////////////////////////
    ______ _____ _____  ______      _
	| ___ \_   _/  __ \ |  _  \    (_)
	| |_/ / | | | /  \/ | | | |_ __ ___   _____ _ __
	|    /  | | | |     | | | | '__| \ \ / / _ \ '__|
	| |\ \  | | | \__/\ | |/ /| |  | |\ V /  __/ |
	\_| \_| \_/  \____/ |___/ |_|  |_| \_/ \___|_|

 /////////////////////////////////////////////////////////////////////////////////////////
  --------------------------------- IO C++ File (tab 4) ----------------------------------
*/


/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/

#include "_RTC.h"

/*
	+--------------------------------------+
	|     FORWARD FUNCTION DEFINITIONS     |
	+--------------------------------------+
*/

void	_RTC_Handle_CallBack(void);

/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/


/*
 +--------------------------------------+
 |        STRUCTS               	 	|
 +--------------------------------------+
*/

struct rtcStruct
{
	uint8_t		second;
	uint8_t		minute;
	uint8_t		hour;
	uint8_t		dayOfWeek;
	uint8_t		day;
	uint8_t		month;
	uint8_t		year;
	uint8_t		alarmSecond;
	uint8_t		AlarmMinute;
	uint8_t		AlarmHour;
	uint16_t	div1Second;
	bool		running;
	void		(*ReturnCallBack)();				//return callback for time object
	void		(*AlarmCallBack)();					//Function called by alarm
	void		(*RTCCallBack)(uint8_t hour,uint8_t minute,uint8_t second);	//Call each second
	class_Timer	timer;								//time manipulator object
	class_I2C	i2c;
	uint8_t		days[13];							//number of months, 13 because first index is 1
}_RTC;

/*
 +--------------------------------------+
 |        LOCAL FLASH CONSTANTS		 	|
 +--------------------------------------+
*/

/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize INFRARED Drive			                                |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+


void    class_RTC::Initialize()
{
    uint8_t sreg;

    //save SREG
    sreg=SREG;
	//set speed
	_RTC.i2c.setSpeed(I2CSpeed::CLOCK_100KHZ);
	//set RTC struct
	_RTC={.second=0		,.minute=0		,.hour=0,
		  .dayOfWeek=0	,.day=0,.month=0,.year=22,
		  .alarmSecond=0,.AlarmMinute=0	,.AlarmHour=0,
		  .div1Second=0,
		  .running=true};		  
	_RTC.days[0]=0;
	_RTC.days[1]=31;
	_RTC.days[2]=28;
	_RTC.days[3]=31;
	_RTC.days[4]=30;
	_RTC.days[5]=31;
	_RTC.days[6]=30;
	_RTC.days[7]=31;
	_RTC.days[8]=31;
	_RTC.days[9]=30;
	_RTC.days[10]=31;
	_RTC.days[11]=30;
	_RTC.days[12]=31;
	//Get old callback function address
	_RTC.RTCCallBack=nullptr;
	//Program INT5 interrupt to activated low to high transition
	EICRB=(1<<ISC51)|(1<<ISC50);
	//enable int5 interrupt
	EIMSK|=(1<<INT5);
//	_RTC.ReturnCallBack=_RTC.timer.getHandleCallBack();
	//set call back function
//	_RTC.timer.setHandleCallBack(_RTC_Handle_CallBack);
    //restore SREG state
    SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize INFRARED Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_RTC::UnInitialize()
{
    uint8_t sreg;

    //save SREG
    sreg=SREG;
    //disable interrupts
    cli();
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
class_RTC::class_RTC()
{
	static bool initialize=true;
	uint8_t sec,h,m,s;
	uint8_t	y,mo,d,dw;
	
	if (initialize)
	{
		initialize=false;
		//Initialize PID
		Initialize();		
		//Enable RTC Clock 
		readReg(RTCReg::SECOND,sec);
		sec&=~(1<<RTCBitField::CH);
		writeReg(RTCReg::SECOND,sec);
		//enable 1 second interrupt from ds1307 rtc
		writeReg(RTCReg::CONTROL,(1<<RTCBitField::SQWE));
		//read time from rtc
		GetTime(h,m,s,true);
		//read date from rtc
		GetDate(y,mo,d,dw,true);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_RTC::~class_RTC()
{
	//Initialize RTC
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Process RTC                                                       |
//	| @NAME    :  RTC_Process					  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  Update Time second elapsed and call alarm callback and time		|
//	|			  callback if true													|
//	+-------------------------------------------------------------------------------+
//void	class_RTC::RTC_Process()
ISR(INT5_vect)
{
	//yes, clear divisor
	_RTC.div1Second=0;
	//if clock not running return
	if (!_RTC.running) return;
	//pump second
	_RTC.second++;
	//sec>59
	if (_RTC.second>59)
	{
		_RTC.second=0;
		//pump minute
		_RTC.minute++;
		//min>59
		if (_RTC.minute>59)
		{
			_RTC.minute=0;
			//pump hour
			_RTC.hour++;
			if (_RTC.hour>23)
			{
				_RTC.hour=0;
				//check if leap year
				if ((_RTC.year%4)==0)
				{
					_RTC.days[2]=29;
				}
				else
				{
					_RTC.days[2]=28;
				}
				//pump day
				_RTC.day++;
				if (_RTC.day>_RTC.days[_RTC.month])
				{
					_RTC.day=1;
					//pump month
					_RTC.month++;
					if (_RTC.month>12)
					{
						_RTC.month=1;
						//pump year
						_RTC.year++;
						if (_RTC.year>99)
						{
							_RTC.year=0;
						}
					}
				}
			}
		}
	}
	//call RTC callback
	if (_RTC.RTCCallBack!=nullptr) _RTC.RTCCallBack(_RTC.hour,_RTC.minute,_RTC.second);
	//check if need alarm
	if (_RTC.second==_RTC.alarmSecond && _RTC.minute==_RTC.AlarmMinute && _RTC.hour==_RTC.AlarmHour)
	{
		//check if has callback function the call
		if (_RTC.AlarmCallBack!=nullptr) _RTC.AlarmCallBack();
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  IR Handle CallBack function to process IR Data                    |
//	| @NAME    :  _IR_Handdle_CallBack		       		                            |
//	| @INPUT   :  none																|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void	_RTC_Handle_CallBack(void)
{
	//Process RTC
	class_RTC::RTC_Process();
	//Call old callback
	if (_RTC.ReturnCallBack!=nullptr) _RTC.ReturnCallBack();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Time	                                                        |
//	| @NAME    :  GetTime						  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  hour,minute,second				                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_RTC::GetTime(uint8_t &hour,uint8_t &minute,uint8_t &second,bool fromRTC)
{
	uint8_t h1,m1,s1,h2,m2,s2;

	//get time from rtc?
	if (fromRTC)
	{
		cli();
		//yes, get time from rtc clock
		readReg(RTCReg::SECOND,s1);
		readReg(RTCReg::MINUTE,m1);
		readReg(RTCReg::HOUR,h1);
		//convert to binary
		second=bcdToBin(s1);
		minute=bcdToBin(m1);
		hour=bcdToBin(h1);
		//set clock
		_RTC.second=second;
		_RTC.minute=minute;
		_RTC.hour=hour;
		sei();
	}
	else
	{
		//get rtc time
		do
		{
			s1=_RTC.second;
			m1=_RTC.minute;
			h1=_RTC.hour;
			sei();
			s2=_RTC.second;
			m2=_RTC.minute;
			h2=_RTC.hour;
			sei();
		} while (!(s1==s2 && m1==m2 && h1==h2));		
		//return time
		second=s2;
		minute=m2;
		hour=h2;		
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Time	                                                        |
//	| @NAME    :  SetTime						  		                            |
//	| @INPUT   :  hour,minute,second                                                |
//	| @OUTPUT  :									                                |
//	| @REMARKS :  interrupts are disabled during set				                |
//	+-------------------------------------------------------------------------------+
void	class_RTC::SetTime(uint8_t hour,uint8_t minute,uint8_t second,bool toRTC)
{
	uint8_t	sreg;

	//save SREG
	sreg=SREG;

	//disable interrupts
	cli();
	//set time
	_RTC.second=second;
	_RTC.minute=minute;
	_RTC.hour=hour;	
	//write into RTC too?
	if (toRTC)
	{
		//convert to bcd
		hour=binToBCD(hour);
		minute=binToBCD(minute);
		second=binToBCD(second);
		//set time into rtc
		writeReg(RTCReg::SECOND,second);
		writeReg(RTCReg::MINUTE,minute);
		writeReg(RTCReg::HOUR,hour);		
	}
	//restore SREG
	SREG=sreg;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Second                                                        |
//	| @NAME    :  GetSecond						  		                            |
//	| @INPUT   :					                                                |
//	| @OUTPUT  :  Second							                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint8_t	class_RTC::GetSecond()
{
	return _RTC.second;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Minute                                                        |
//	| @NAME    :  GetMinute						  		                            |
//	| @INPUT   :					                                                |
//	| @OUTPUT  :  Minute							                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint8_t	class_RTC::GetMinute()
{
	return _RTC.minute;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Hour                                                          |
//	| @NAME    :  GetHour						  		                            |
//	| @INPUT   :					                                                |
//	| @OUTPUT  :  Hour								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint8_t	class_RTC::GetHour()
{
	return _RTC.hour;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  reset Clock														|
//	| @NAME    :  resetClock					  		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  											                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_RTC::resetClock()
{
	uint8_t sreg=SREG;
	cli();
	_RTC.hour=_RTC.minute=_RTC.second=0;
	SREG=sreg;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  stop Clock														|
//	| @NAME    :  stopClock					  										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  											                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_RTC::stopClock()
{
	_RTC.running=false;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  start Clock														|
//	| @NAME    :  startClock					  									|
//	| @INPUT   :																	|
//	| @OUTPUT  :  											                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void	class_RTC::startClock()
{
	_RTC.running=true;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Alarm Call Back Function                                      |
//	| @NAME    :  SetAlarmTime					  		                            |
//	| @INPUT   :  hour,minute,second, function callback                             |
//	| @OUTPUT  :  											                        |
//	| @REMARKS :  set AlarmCallBack to null to disable this callback function		|
//	+-------------------------------------------------------------------------------+
void	class_RTC::SetALarmTime(uint8_t hour,uint8_t minute,uint8_t second,void (*AlarmCallBack)())
{
	uint8_t	 sreg;

	//save SREG;
	sreg=SREG;
	//disable interrupts
	cli();
	//set alarm time
	_RTC.alarmSecond=second;
	_RTC.AlarmMinute=minute;
	_RTC.AlarmHour=hour;
	_RTC.AlarmCallBack=AlarmCallBack;
	//restore SREG
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set RTC Call Back Function                                        |
//	| @NAME    :  SetRTC					  										|
//	| @INPUT   :  hour,minute,second, function callback                             |
//	| @OUTPUT  :  											                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//
void	class_RTC::SetRTCCallback(void (*RTCCallBack)(uint8_t hour,uint8_t minute,uint8_t second))
{
	_RTC.RTCCallBack=RTCCallBack;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Write DS1307 RTC Register		                                    |
//	| @NAME    :  writeReg					  										|
//	| @INPUT   :  Reg Register,Data-->, size (length of data)                       |
//	| @OUTPUT  :  Error code								                        |
//	| @REMARKS :  Error may by Ok,No_Ack							                |
//	+-------------------------------------------------------------------------------+
RTCError class_RTC::writeReg(RTCReg reg,uint8_t data,bool disableInt)
{
	uint8_t sreg=SREG;

	//disable interrupts?
	if (disableInt) 
	{
		//save SREG;
		sreg=SREG;
		//Disable Interrupts
		cli();
	}
	//start I2C Transfer
	_RTC.i2c.Start();
	//send ISC Device Address for write
	_RTC.i2c.ByteOut(DS1307_ADDRESS);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}
	//Send Register
	_RTC.i2c.ByteOut((uint8_t)reg);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}
	//send data
	_RTC.i2c.ByteOut(data);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}		
	//Stop i2c transmission
	_RTC.i2c.Stop();
	//restore interrupts
	if (disableInt)
	{
		SREG=sreg;
	}
	//return transfer ok
	return RTCError::OK;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  read DS1307 RTC Register		                                    |
//	| @NAME    :  readeReg					  										|
//	| @INPUT   :  Reg Register,Data-->, size (length of data)                       |
//	| @OUTPUT  :  Error code								                        |
//	| @REMARKS :  Error may by Ok,No_Ack							                |
//	+-------------------------------------------------------------------------------+
RTCError class_RTC::readReg(RTCReg reg,uint8_t &data,bool disableInt)
{
	uint8_t sreg=SREG;

	//disable interrupts?
	if (disableInt)
	{
		//save SREG;
		sreg=SREG;
		//Disable Interrupts
		cli();
	}	
	//start i2c transfer
	_RTC.i2c.Start();
	//send i2c device address for write
	_RTC.i2c.ByteOut(DS1307_ADDRESS);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}
	//Send reg
	_RTC.i2c.ByteOut((uint8_t)reg);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}
	//stop I2C set reg transfer
	_RTC.i2c.Stop();
	//Start i2c transfer
	_RTC.i2c.Start();
	//send i2c device address for read
	_RTC.i2c.ByteOut(DS1307_ADDRESS|1);
	//check Ack from slave
	if (_RTC.i2c.AckIn())
	{
		//no, ack then stop
		_RTC.i2c.Stop();
		//restore interrupts
		if (disableInt)
		{
			SREG=sreg;
		}
		//return error code no_ack
		return RTCError::NO_ACK;
	}
	//Read data from ds1307 device
	data=_RTC.i2c.ByteIn();	
	//send no ack to master at last reception
	_RTC.i2c.AckOut(1);
	//Stop I2C Transfer
	_RTC.i2c.Stop();
	//restore interrupts
	if (disableInt)
	{
		SREG=sreg;
	}
	return RTCError::OK;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Convert binary value to BCD digits                                |
//	| @NAME    :  binToBCD					  										|
//	| @INPUT   :  input number 16 bits								                |
//	| @OUTPUT  :  output BCD codec							                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
uint16_t class_RTC::binToBCD(int number)
{
	uint8_t	digits[3];	
	int		factor;
	uint8_t	index,c;
	int16_t result=0;
	bool	sig;
	
	sig=0;
	if (number<0)
	{
		number=-number;
		sig=1;
	}
	factor=100;
	index=0;
	c=0;
	//convert tenth of thousand digits
	for(;;)
	{
		//digit found?
		number-=factor;
		//yes
		if (number<0)
		{
			//restore factor
			number+=factor;
			//divide factor by 10
			factor/=10;
			digits[index]=c;
			c=0;
			if (index>=2)
			{
				break;
			}
			index++;
		}
		else
		{
			c++;	
		}
	}
	//store into result bcd digits
	result|=((uint16_t)sig<<15)|(digits[0]<<8)|(digits[1]<<4)|(digits[2]);
			
	return result;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Convert BCD to Binary					                            |
//	| @NAME    :  bcdToBin					  										|
//	| @INPUT   :  3 digit bcd										                |
//	| @OUTPUT  :  binary output								                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int8_t	 result;
int8_t class_RTC::bcdToBin(uint16_t bcd)
{
	//int8_t result;
	
	result=((bcd & 0x0f00)>>8)*100+((bcd & 0x00f0)>>4)*10+((bcd & 0x000f));
	
	return (bcd & 0x8000)?-result:result;
	
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Date															|
//	| @NAME    :  setDate					  										|
//	| @INPUT   :  Year,Month,Day,DayOfWeek, write date into rtc if toRTC is true	|
//	| @OUTPUT  :  																	|
//	| @REMARKS :											 						|
//	+-------------------------------------------------------------------------------+
void class_RTC::setDate(uint8_t year,uint8_t month,uint8_t day,uint8_t dayOfWeek,bool toRTC/* =false */)
{
	uint8_t	sreg;

	//save SREG
	sreg=SREG;

	//disable interrupts
	cli();
	//set time
	_RTC.year=year;
	_RTC.month=month;
	_RTC.day=day;
	_RTC.dayOfWeek=dayOfWeek;
	//write into RTC too?
	if (toRTC)
	{
		//convert to bcd
		year=binToBCD(year);
		month=binToBCD(month);
		day=binToBCD(day);
		//set time into rtc
		writeReg(RTCReg::YEAR,year);
		writeReg(RTCReg::MONTH,month);
		writeReg(RTCReg::DAY,day);
		writeReg(RTCReg::DAY_OF_WEEK,dayOfWeek);
	}
	//restore SREG
	SREG=sreg;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Date															|
//	| @NAME    :  getDate					  										|
//	| @INPUT   :  Year,Month,Day,DayOfWeek, get date from rtc if fromRTC is true	|
//	| @OUTPUT  :  																	|
//	| @REMARKS :											 						|
//	+-------------------------------------------------------------------------------+
void class_RTC::GetDate(uint8_t &year,uint8_t &month,uint8_t &day,uint8_t &dayOfWeek,bool fromRTC/* =false */)
{
	uint8_t y1,m1,d1,dw1;
	uint8_t y2,m2,d2,dw2;

	//get time from rtc?
	if (fromRTC)
	{
		cli();
		//yes, get time from rtc clock
		readReg(RTCReg::YEAR,year);
		readReg(RTCReg::MONTH,month);
		readReg(RTCReg::DAY,day);
		readReg(RTCReg::DAY_OF_WEEK,dayOfWeek);
		//convert to binary
		year=bcdToBin(year);
		month=bcdToBin(month);
		day=bcdToBin(day);
		dayOfWeek=bcdToBin(dayOfWeek);
		//set clock date
		_RTC.year=year;
		_RTC.month=month;
		_RTC.day=day;
		_RTC.dayOfWeek=dayOfWeek;
		sei();
	}
	else
	{
		//get rtc date
		do
		{
			y1=_RTC.year;
			m1=_RTC.month;
			d1=_RTC.day;
			dw1=_RTC.dayOfWeek;

			y2=_RTC.year;
			m2=_RTC.month;
			d2=_RTC.day;
			dw2=_RTC.dayOfWeek;
			sei();
		} while (!(y1==y2 && m1==m2 && d1==d2 && dw1==dw2));
		//return time
		year=y2;
		month=m2;
		day=d2;
		dayOfWeek=dw2;
	}	
}