/*
  ////////////////////////////////////////////////////////////////////////////////
  //        _   _ _____  ___  ______ _____  ______      _                	    //
  //       | | | /  ___|/ _ \ | ___ \_   _| |  _  \    (_)               	    //
  //       | | | \ `--./ /_\ \| |_/ / | |   | | | |_ __ ___   _____ _ __ 	    //
  //       | | | |`--. \  _  ||    /  | |   | | | | '__| \ \ / / _ \ '__|	    //
  //       | |_| /\__/ / | | || |\ \  | |   | |/ /| |  | |\ V /  __/ |   	    //
  //        \___/\____/\_| |_/\_| \_| \_/   |___/ |_|  |_| \_/ \___|_|   	    //
  //                                                                     	    //
  ////////////////////////////////////////////////////////////////////////////////
  // This Drive running on ATMEGA8,ATMEGA162,ATMEGA128 and atmega328p devices   //
  // Global interrupts must enabled to work                                     //
  ----------------------- USART Drive C++ File (tab 4) ---------------------------
*/

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


#include "_USART_Driver.h"


/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS CONSTANTS 	|
 +--------------------------------------+
*/

    //define Virtual Register according selected micro controller
    #if defined(_AVR_IOM64_H_)
        //Define Virtual Registers USART 0
        #define V_UDR0      UDR0
        #define V_UBRR0H    UBRR0H
        #define V_UBRR0L    UBRR0L
        #define V_UCSR0A    UCSR0A
        #define V_UCSR0B    UCSR0B
        #define V_UCSR0C    UCSR0C   
        //Define Virtual Bits USART 0
        #define V_UDRE0     UDRE0
        #define V_RXC0      RXC0
        #define V_FE0       FE0
        #define V_DOR0      DOR0
        #define V_RXCIE0    RXCIE0
        #define V_TXEN0     TXEN0
        #define V_RXEN0     RXEN0
        #define V_UPM01     UPM01
        #define V_UPM00     UPM00
        #define V_USBS0     USBS0
        #define V_UCSZ00    UCSZ00
        #define V_UCSZ01    UCSZ01
        #define V_UCSZ02    UCSZ02
        #define V_UMSEL0    UMSEL0
        #if defined(_AVR_IOM162_H_)
            #define V_URSEL0    URSEL0
        #else
            #define V_URSEL0    0
        #endif
        //Define Virtual Registers USART 1
        #define V_UDR1      UDR1
        #define V_UBRR1H    UBRR1H
        #define V_UBRR1L    UBRR1L
        #define V_UCSR1A    UCSR1A
        #define V_UCSR1B    UCSR1B
        #define V_UCSR1C    UCSR1C
        //Define Virtual Bits USART 1
        #define V_UDRE1     UDRE1
        #define V_RXC1      RXC1
        #define V_FE1       FE1
        #define V_DOR1      DOR1
        #define V_RXCIE1    RXCIE1
        #define V_TXEN1     TXEN1
        #define V_RXEN1     RXEN1
        #define V_UPM11     UPM11
        #define V_UPM10     UPM10
        #define V_USBS1     USBS1
        #define V_UCSZ10    UCSZ10
        #define V_UCSZ11    UCSZ11
        #define V_UCSZ12    UCSZ12
        #define V_UMSEL1    UMSEL1
        #if defined(_AVR_IOM162_H_)
            #define V_URSEL1    URSEL1
        #else
            #define V_URSEL1    0
        #endif
    #elif defined(_AVR_IOM328P_H_)       //ATMEGA328P---------------------------------------------
        //Define Virtual Registers
        #define V_UDR0      UDR0
        #define V_UBRR0H    UBRR0H
        #define V_UBRR0L    UBRR0L
        #define V_UCSR0A    UCSR0A
        #define V_UCSR0B    UCSR0B
        #define V_UCSR0C    UCSR0C
        //Define Virtual Bits USART 0
        #define V_UDRE0     UDRE0
        #define V_RXC0      RXC0
        #define V_FE0       FE0
        #define V_DOR0      DOR0
        #define V_RXCIE0    RXCIE0
        #define V_TXEN0     TXEN0
        #define V_RXEN0     RXEN0
        #define V_UPM01     UPM01
        #define V_UPM00     UPM00
        #define V_USBS0     USBS0
        #define V_UCSZ00    UCSZ00
        #define V_UCSZ01    UCSZ01
        #define V_UCSZ02    UCSZ02
        #define V_UMSEL0    UMSEL00
        #define V_URSEL0    0
    #elif defined(_AVR_IOM8_H_)         //ATMEGA8---------------------------------------------
        //Define Virtual Registers
        #define V_UDR0      UDR
        #define V_UBRR0H    UBRRH
        #define V_UBRR0L    UBRRL
        #define V_UCSR0A    UCSRA
        #define V_UCSR0B    UCSRB
        #define V_UCSR0C    UCSRC
        //Define Virtual Bits USART 0
        #define V_UDRE0     UDRE
        #define V_RXC0      RXC
        #define V_FE0       FE
        #define V_DOR0      DOR
        #define V_RXCIE0    RXCIE
        #define V_TXEN0     TXEN
        #define V_RXEN0     RXEN
        #define V_UPM01     UPM1
        #define V_UPM00     UPM0
        #define V_USBS0     USBS
        #define V_UCSZ00    UCSZ0
        #define V_UCSZ01    UCSZ1
        #define V_UCSZ02    UCSZ2
        #define V_UMSEL0    UMSEL
        #define V_URSEL0    URSEL
    #endif

/*
 +--------------------------------------+
 |        STRUCTS AND UNIONS		    |
 +--------------------------------------+
*/

struct portParms
{
	uint32_t	_baudRate;
	UDataBits	_dataBits;
	UParity		_parityType;
	UStopBits	_stopBits;
	uint32_t	_timeoutMilliseconds;
	UStatus		_status;
	bool		_inUse;
};


struct _usartDriveStruct
{
	uint8_t					port;							//0 for port 1, 1 for port 2
	portParms				parms[_USART_MAX_PORTS];		//Port parameters
    usartQueue              RxBuffer0;
    usartQueue              RxBuffer1;
    uint8_t                 Dummy;    
} _usartDriver;

/*
        +-------------------------------------------------------+
        |        CLASS USART DRIVE  IMPLEMENTATION              |
        +-------------------------------------------------------+
        | @PURPOSE      : all function to implement RX and TX   |
        | @OBSERVATIONS :                                       |
        +-------------------------------------------------------+
*/

/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Interrupt Service Routine for USART reception (Central)		    |
//	| @NAME    :  none								                                |
//	| @INPUT   :  none								                                |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+


ISR(USART0_RX_vect)
{
    unsigned char data;
    usartQueue	*p;

    p=&_usartDriver.RxBuffer0;

    //get error status register
    data=V_UCSR0A;
    if ((data & ((1<<V_FE0) | (1<<V_DOR0)))==0)
    {
        data=V_UDR0;
        if (((p->p+1) & USART_QUEUE_MASK)!=p->g)
        {
            //put data queue in buffer
            p->data[p->p]=data;
            //compute next position
            p->p=(p->p+1) & USART_QUEUE_MASK;
            //data counter++
            p->c++;
        }
    }
    else
    {
        data=V_UDR0;
    }
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Interrupt Service Routine for USART reception (Central)		    |
//	| @NAME    :  none								                                |
//	| @INPUT   :  none								                                |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+

ISR(USART1_RX_vect)
{
    unsigned char data;
    usartQueue	*p;

    p=&_usartDriver.RxBuffer1;

    //get error status register
    data=V_UCSR1A;
    if ((data & ((1<<V_FE1) | (1<<V_DOR1)))==0)
    {
        data=V_UDR1;
        if (((p->p+1) & USART_QUEUE_MASK)!=p->g)
        {
            //Put data into queue
            p->data[p->p]=data;
            //compute next position
            p->p=(p->p+1) & USART_QUEUE_MASK;
            //data counter++
            p->c++;
        }
    }
    else
    {
        data=V_UDR1;
    }
}

/*
        +-----------------------------------------------+
        |       CONSTRUCTORS AND DESTRUCTORS            |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor                                                       |
//	| @NAME    :  constructor							                            |
//	| @INPUT   :  usartBaudRate							                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+

class_USART::class_USART()
{
        //set driver ports not in use
		_usartDriver.parms[0]._inUse=false;		//port 1 not in use
		_usartDriver.parms[1]._inUse=false;		//port 2 not in use
		//set time out
		_usartDriver.parms[0]._timeoutMilliseconds=_USART_DEFAULT_TIMEOUT;
		//clear buffer
		memset(&_usartDriver.RxBuffer0,0,sizeof(_usartDriver.RxBuffer0));
		
		//if port 2 defined then initialize then
		
		#if defined(_AVR_IOM128_H_) || defined(_AVR_IOM162_H_) || \
			defined(_AVR_IOM128_H_) || (_AVR_IOM162_H_) || (_AVR_IOM1284P_H_)
			
			_usartDriver.parms[1]._timeoutMilliseconds=_USART_DEFAULT_TIMEOUT;
			memset(&_usartDriver.RxBuffer1,0,sizeof(_usartDriver.RxBuffer1));
		#endif
		
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor                                                        |
//	| @NAME    :  destructor							                            |
//	| @INPUT   :  usartBaudRate							                            |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
class_USART::~class_USART()
{
	
}

/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART port number                         		            |
//	| @NAME    :  Get_usartPort								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  _usartPort							                            |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
// uint8_t class_USART::getUSARTPort()
// {
//     return _usartDriver.port;
// }

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART port number                         		            |
//	| @NAME    :  Set_usartPort								                        |
//	| @INPUT   :  _usartPort 						                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS : This drive use only ports 1 and 2                                  |
//	+-------------------------------------------------------------------------------+
// UStatus class_USART::setUSARTPort(UPort usartPort)
// {
// 	uint8_t p;
// 	
// 	
// 	
// 	//VERIFICAR USE PORTA ESTA EM USO SE SIM NÃO SETAR VALORES , DEVE-SE ENTÃO DAR UM CLOSE , THEN OPEN WITH NEW PORT NUMBER 
// 	//ASSIM PARA O RESTO
//     //check if valid port
//     if (usartPort==UPort::USART_1 || usartPort==UPort::USART_2)
//     {
// 		//set port number
// 		p=(uint8_t)usartPort-1;
// 		//check if already opened
// 		if (_usartDriver.parms[p]._inUse)
// 		{
// 			_usartDriver.port=p;
// 			_usartDriver.parms[p]._status=UStatus::OK;
// 			return UStatus::OK;
// 		}
// 		else
// 		{
// 			_usartDriver.parms[p]._status=UStatus::NOT_OPENED;
// 			return UStatus::NOT_OPENED;			
// 		}
//     }
//     else
//     {
// 		_usartDriver.parms[p]._status=UStatus::INVALID_PORT;
//         return UStatus::INVALID_PORT;
//     }
// }
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART baud rate                              		            |
//	| @NAME    :  GetBaudRate								                        |
//	| @INPUT   :  CommPort							                                |
//	| @OUTPUT  :  baud rate return -1 if port not opened                            |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
uint32_t class_USART::getBaudRate(UHDC hdc)
{
	//YES,check if already opened
	if (_usartDriver.parms[hdc]._inUse)
	{
		_usartDriver.parms[hdc]._status=UStatus::ALREADY_OPEN;
		return -1;
	}
	else
	{
		//return baudrate
		_usartDriver.parms[hdc]._status=UStatus::OK;
		return _usartDriver.parms[_usartDriver.port]._baudRate;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART baud rate                             		            |
//	| @NAME    :  SetBaudRate								                        |
//	| @INPUT   :  baud rate   						                                |
//	| @OUTPUT  :  status							                                |
//	| @REMARKS :                                                                    |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::setBaudRate(UHDC hdc,uint32_t baudRate)
{
    static uint16_t tmp;
	
	//yes,check if port in use
	if (_usartDriver.parms[hdc]._inUse)
	{
		//yes, return already open
		_usartDriver.parms[hdc]._status=UStatus::OK;
		//else, set ok and set baudrate
		_usartDriver.parms[hdc]._baudRate=baudRate;
		//Compute baudrate
		tmp=F_CPU/(16*baudRate)-1;
		//Initialize appropriate registers
		switch (hdc)
		{
			case 0:
				// set Baud rate into UBRR
				V_UBRR0H = (tmp>>8) & 0x7f;
				V_UBRR0L = tmp & 0x00ff;
				break;
			#if (defined(_AVR_IOM128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
			case 1:
				// set Baud rate into UBRR
				V_UBRR1H = (tmp>>8) & 0x7f;
				V_UBRR1L = tmp & 0x00ff;
				break;
			#endif
		}
	}
	else
	{
		//set not opened 
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
	//return status
	return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART status                               		            |
//	| @NAME    :  Status     								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  USART status  					                                |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::status(UHDC hdc)
{
	//else return status
	return _usartDriver.parms[hdc]._status;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART Data Bits Number                       		            |
//	| @NAME    :  GetDataBits								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  DataBits  						                                |
//	| @REMARKS :  Data bits may be 5,6,7 or 8, if in use return -1                  |
//	+-------------------------------------------------------------------------------+
UDataBits class_USART::getDataBits(UHDC hdc)
{
	//check if port is valid
	if (_usartDriver.parms[hdc]._inUse)
	{
		//set ok and return data bits
		_usartDriver.parms[hdc]._status=UStatus::OK;
		//return data bits
		return _usartDriver.parms[hdc]._dataBits;
	}
	else
	{
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
		return UDataBits::INVALID;
	}
	
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART Data Bits number                       		            |
//	| @NAME    :  SetDataBits								                        |
//	| @INPUT   :  DataBits   						                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS : This drive use only ports 1 and 2                                  |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::setDataBits(UHDC hdc,UDataBits dataBits)
{
    uint8_t rTmp;
	
    //yes, check if already open
    if (_usartDriver.parms[hdc]._inUse)
    {
		//yes, return that is opened
		_usartDriver.parms[hdc]._status=UStatus::OK;
        //set data bits
        _usartDriver.parms[hdc]._dataBits=dataBits;
        //set according port
        switch (hdc)
        {
            case 0:
                //Set _usartPort of bits 5...8
                if ((uint8_t)dataBits>=5 && (uint8_t)dataBits<=8)
                {
                    //set size according
                    //UCSZ02=0;UCSZ01=0;UCSZ00=0;
                    V_UCSR0B&=~(1<<V_UCSZ02);
                    rTmp=V_UBRR0H;
                    rTmp=V_UCSR0C;
                    rTmp&=~((1<<V_UCSZ01)|(1<<V_UCSZ00));
                    //Set UCSZ01:UCSZ00=(_usartPortBits)
                    rTmp|=((((uint8_t)dataBits-5) & 0x03)<<V_UCSZ00);
                    //set UCSRC again
                    #if defined(_AVR_IOM328P_H_)||defined(_AVR_IOM1284P_H_)
                        V_UCSR0C=rTmp;
                    #elif defined(_AVR_IOM8_H_)
                        V_UCSR0C=(1<<V_URSEL0) | rTmp;
                    #endif
                }
                else
                {
					_usartDriver.parms[hdc]._status=UStatus::INVALID_DATA_BITS;
                }
                break;
            #if (defined(_AVR_IOM128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
            case 1:
                //Set _usartPort of bits 5...8
                if ((uint8_t)dataBits>=5 && (uint8_t)dataBits<=8)
                {
                    //set size according
                    //UCSZ02=0;UCSZ01=0;UCSZ00=0;
                    V_UCSR1B&=~(1<<V_UCSZ12);
                    rTmp=V_UBRR1H;
                    rTmp=V_UCSR1C;
                    rTmp&=~((1<<V_UCSZ11)|(1<<V_UCSZ10));
                    //Set UCSZ01:UCSZ00=(_usartPortBits)
                    rTmp|=((((uint8_t)dataBits-5) & 0x03)<<V_UCSZ10);
                    //set UCSRC Again
                    V_UCSR1C=(1<<V_URSEL1) | rTmp;
                }
                else
                {
					_usartDriver.parms[hdc]._status=UStatus::INVALID_DATA_BITS;					
                }
                break;
            #endif
        }
    }
	else
	{
		//not open
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
    //return status
    return  _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART parity Type                            		            |
//	| @NAME    :  GetParityType								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  parityType 						                                |
//	| @REMARKS :  parityType may be USART_PARITY_NONE                               |
//	|             parityType may be USART_PARITY_EVEN                               |
//	|             parityType may be USART_PARITY_ODD                                |
//	+-------------------------------------------------------------------------------+
UParity class_USART::getParityType(UHDC hdc)
{
    //yes, check if already open
    if (_usartDriver.parms[hdc]._inUse)
	{
		//yes, return already open
		_usartDriver.parms[hdc]._status=UStatus::OK;
		//return invalid parity
		return _usartDriver.parms[hdc]._parityType;
	}
	else
	{
		//no, set ok
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
		//return parity
		return UParity::INVALID;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART parity Type                           		            |
//	| @NAME    :  SetParityType								                        |
//	| @INPUT   :  parityType  						                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS :  parityType may be USART_PARITY_NONE                               |
//	|             parityType may be USART_PARITY_EVEN                               |
//	|             parityType may be USART_PARITY_ODD                                |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::setParityType(UHDC hdc,UParity parityType)
{
    uint8_t rTmp=0;

    //yes, check if already open
    if (_usartDriver.parms[hdc]._inUse)
    {
		//yes, set ok
        //else check if a valid parity
        if (parityType==UParity::EVEN || parityType==UParity::ODD || parityType==UParity::NONE)
        {
            //yes, set parity and return status ok
            _usartDriver.parms[hdc]._parityType=parityType;
            _usartDriver.parms[hdc]._status=UStatus::OK;
            // according port
            switch (hdc)
            {
                case 0:
                    // set Parity
                    switch (parityType)
                    {
                        case UParity::NONE:
                                //read UCSR0
                                rTmp=V_UBRR0H;
                                rTmp=V_UCSR0C;
                                rTmp&=~((1<<V_UPM01)|(1<<V_UPM00));
                        break;
                        case UParity::EVEN:
                                rTmp=V_UBRR0H;
                                rTmp=V_UCSR0C;
                                rTmp&=~(1<<V_UPM00);
                                rTmp|=(1<<V_UPM01);
                        break;
                        case UParity::ODD:
                                rTmp=V_UBRR0H;
                                rTmp=V_UCSR0C;
                                rTmp|=(1<<V_UPM01)|(1<<V_UPM00);
                        break;
						case UParity::INVALID:
						break;
                    }
                    //set UCSRC
                    #if defined(_AVR_IOM328P_H_)||defined(_AVR_IOM1284P_H_)
                        V_UCSR0C=rTmp;
                    #elif defined(_AVR_IOM8_H_)
                        V_UCSR0C=(1<<V_URSEL0) | rTmp;
                    #endif
                    break;
                #if (defined(_AVR_IOM128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
                case 1:
                    switch (parityType)
                    {
                        case UParity::NONE:
                            //read UCSR0
                            rTmp=V_UBRR1H;
                            rTmp=V_UCSR1C;
                            rTmp&=~((1<<V_UPM11)|(1<<V_UPM10));
                        break;
                        case UParity::EVEN:
                            rTmp=V_UBRR1H;
                            rTmp=V_UCSR1C;
                            rTmp&=~(1<<V_UPM10);
                            rTmp|=(1<<V_UPM11);
                        break;
                        case UParity::ODD:
                            rTmp=V_UBRR1H;
                            rTmp=V_UCSR1C;
                            rTmp|=(1<<V_UPM11)|(1<<V_UPM10);
                        break;
						case UParity::INVALID:
						break;
                    }
                    //set UCSRC
                    V_UCSR1C=(1<<V_URSEL1) | rTmp;
                    break;
                #endif
            }
        }
        else
        {
			//set invalid parity
			_usartDriver.parms[hdc]._status=UStatus::INVALID_PARITY;
        }
    }
	else
	{	
		//set not opened
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
    //return status
    return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART Stop bits                            		            |
//	| @NAME    :  GetStopBits								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  stopBits   						                                |
//	| @REMARKS :  return -1 if invalid	                                            |
//	+-------------------------------------------------------------------------------+
UStopBits class_USART::getStopBits(UHDC hdc)
{
    //yes, check if already open
    if (_usartDriver.parms[hdc]._inUse)
    {
	    //yes, return already open
	    _usartDriver.parms[hdc]._status=UStatus::OK;
	    //return invalid parity
	    return _usartDriver.parms[hdc]._stopBits;
    }
    else
    {
	    //no, set ok
	    _usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	    //return parity
	    return UStopBits::INVALID;
    }
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART stop bits                             		            |
//	| @NAME    :  SetStopBits   							                        |
//	| @INPUT   :  stop bits  						                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS :  Valid stop bits 5,6,7,8                                           |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::setStopBits(UHDC hdc, UStopBits stopBits)
{
    uint8_t rTmp;

    //check if already open
    if (_usartDriver.parms[hdc]._inUse)
    {
        //yes, set already open
		_usartDriver.parms[hdc]._status=UStatus::OK;
        //else check if valid stop bits
        if (stopBits==UStopBits::SB_1 || stopBits==UStopBits::SB_2)
        {
            //yes, set new stop bits
            _usartDriver.parms[hdc]._stopBits=stopBits;
            //Set Stop Bits
            switch (hdc)
            {
                case 0:
                    rTmp=V_UBRR0H;
                    rTmp=V_UCSR0C;
                    rTmp&=~(1<<V_USBS0);
                    #if defined(_AVR_IOM328P_H_)||defined(_AVR_IOM1284P_H_)
                        V_UCSR0C=rTmp;
                    #elif defined(_AVR_IOM8_H_)
                        V_UCSR0C=(1<<V_URSEL0) | rTmp;
                    #endif
                    break;
                #if (defined(_AVR_IOM128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
                case 1:
                    rTmp=V_UBRR1H;
                    rTmp=V_UCSR1C;
                    rTmp|=(1<<V_USBS1);
                    V_UCSR1C=(1<<V_URSEL1) | rTmp;
                    break;
                #endif
            }
            //set status ok
			_usartDriver.parms[hdc]._status=UStatus::OK;
        }
        else
        {   //else invalid stop bits
			_usartDriver.parms[hdc]._status=UStatus::INVALID_STOP_BITS;
        }
    }
	else
	{
		//set not opened
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
    //return status
    return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get USART Timeout                             		            |
//	| @NAME    :  GetTimeout								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :  Timeout in milliseconds   		                                |
//	| @REMARKS :  return 0 if not opened	                                        |
//	+-------------------------------------------------------------------------------+
uint32_t class_USART::getTimeout(UHDC hdc)
{
    //check if already open
    if (_usartDriver.parms[hdc]._inUse)
    {
	    //yes, set ok
	    _usartDriver.parms[hdc]._status=UStatus::OK;
		//return timeout
		return _usartDriver.parms[hdc]._timeoutMilliseconds;	
    }
	else
	{
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
		return 0;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set USART Timeouts                             		            |
//	| @NAME    :  SetTimeout       							                        |
//	| @INPUT   :  Timeout in milliseconds   		                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS :                                                                    |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::setTimeout(UHDC hdc,uint32_t timeout)
{
	//check if already open
	if (_usartDriver.parms[hdc]._inUse)
	{
		//no, set timeout ok
		_usartDriver.parms[hdc]._status=UStatus::OK;
		//set timeout
		_usartDriver.parms[hdc]._timeoutMilliseconds=timeout;
	}
	else
	{
		//set not opened
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
	//return status
	return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Open without parameters (overload1)             		            |
//	| @NAME    :  Open             							                        |
//	| @INPUT   :                               		                                |
//	| @OUTPUT  :    								                                |
//	| @REMARKS :                                                                    |
//	+-------------------------------------------------------------------------------+

UStatus   class_USART::open(UHDC &hdc,UPort usartPort,uint32_t baudRate,UDataBits dataBits,UParity parityType,UStopBits stopBits)
{
	
	//check if valid port
	if (usartPort==UPort::USART_1 || usartPort==UPort::USART_2)
	{
        //yes, create hdc
		hdc=(UHDC)usartPort;
		//set not in use
		_usartDriver.parms[hdc]._inUse=true;
        //else try to open a this port
        if (setBaudRate(hdc,baudRate)!=UStatus::OK)
        {
			//yes, return different status
			_usartDriver.parms[hdc]._inUse=false;
            return _usartDriver.parms[hdc]._status;
        }
        if (setDataBits(hdc,dataBits)!=UStatus::OK)
        {
			//yes, return different status
			_usartDriver.parms[hdc]._inUse=false;
			return _usartDriver.parms[hdc]._status;
        }
        if (setParityType(hdc,parityType)!=UStatus::OK)
        {
			//yes, return different status
			_usartDriver.parms[hdc]._inUse=false;
			return _usartDriver.parms[hdc]._status;
        }
        if (setStopBits(hdc,stopBits)!=UStatus::OK)
        {
			//yes, return different status
			_usartDriver.parms[hdc]._inUse=false;
			return _usartDriver.parms[hdc]._status;
        }
        //set Tx and Rx enable and Rx interrupt too
        switch (usartPort)
        {
            case UPort::USART_1:
                V_UCSR0B|= (1<<V_RXCIE0)|(1<<V_TXEN0)|(1<<V_RXEN0);
                break;
            case UPort::USART_2:
                V_UCSR1B|= (1<<V_RXCIE1)|(1<<V_TXEN1)|(1<<V_RXEN1);
                break;
			case UPort::INVALID:
			break;
        }
        //set port open
        _usartDriver.parms[hdc]._inUse=true;
        //Set status ok
        _usartDriver.parms[hdc]._status=UStatus::OK;
	}
	else
	{
		//no,set invalid port
		return UStatus::INVALID_PORT;
	}
    //return status
    return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Flush receiver buffer and from serial I/O				            |
//	| @NAME    :  usartFlush								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  :									                                |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+

UStatus class_USART::flush(UHDC hdc)
{
    //yes, check if opened
    if (_usartDriver.parms[hdc]._inUse)
    {
	    //yes, flush receiver
        _usartDriver.Dummy=0;
        //flush usart according _usartPort
        switch (hdc)
        {
            case 0:
                // flush usart and external rx buffer
                while ( V_UCSR0A & (1<<V_RXC0) )
                {
                    _usartDriver.Dummy = V_UDR0;
                }
                _usartDriver.RxBuffer0.g=0;
                _usartDriver.RxBuffer0.p=0;
                _usartDriver.RxBuffer0.c=0;
				memset(_usartDriver.RxBuffer0.data,0,sizeof(_usartDriver.RxBuffer0.data));
                break;
            #if (defined(_AVR_IO128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
                case 1:
                    // flush usart and external rx buffer
                    while ( V_UCSR1A & (1<<V_RXC1) )
                    {
                        _usartDriver.Dummy =V_UDR1;
                    }
					_usartDriver.RxBuffer1.g=0;
					_usartDriver.RxBuffer1.p=0;
					_usartDriver.RxBuffer1.c=0;
					memset(_usartDriver.RxBuffer1.data,0,sizeof(_usartDriver.RxBuffer1.data));
                    break;
            #endif
        }
        //set status ok
		_usartDriver.parms[hdc]._status=UStatus::OK;
    }
    //return status
    return _usartDriver.parms[hdc]._status;
}


//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get data from serial I/O with timeout				                |
//	| @NAME    :  usartGetcT								                        |
//	| @INPUT   :  timeout   timeout milliseconds					                |
//	| @OUTPUT  :  Received data							                            |
//	| @REMARKS :  return '\0' if timeout occurs and set TimeoutKey to true          |
//	+-------------------------------------------------------------------------------+

uint8_t class_USART::getC(UHDC hdc)
{
	uint32_t t;
	uint8_t c;
    
	//yes, check if opened
	if (_usartDriver.parms[hdc]._inUse)
	{
		//yes, according hdc
		switch (hdc)
		{
			case 0:
				//clear timeout timer
				_Time.setElapsed(t);
				// wait timeout reach
				while (_Time.getElapsed(t)<_usartDriver.parms[hdc]._timeoutMilliseconds)
				{
					if (cqGet((usartQueue*)&_usartDriver.RxBuffer0,&c)==false)
					{
						//Set return ok
						_usartDriver.parms[hdc]._status=UStatus::OK;
						//return character
						return c;
					}
				}
				_usartDriver.parms[hdc]._status=UStatus::TIMEOUT;
				break;
			#if (defined(_AVR_IO128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
			case 1:
				//clear timeout timer
				_Time.setElapsed(t);
				// wait timeout reach
				while (_Time.getElapsed(t)<_usartDriver.parms[hdc]._timeoutMilliseconds)
				{
					if (cqGet((usartQueue*)&_usartDriver.RxBuffer1,&c)==false)
					{
						//Set return ok
						_usartDriver.parms[hdc]._status=UStatus::OK;
						//return character
						return c;
					}

				}
				_usartDriver.parms[hdc]._status=UStatus::TIMEOUT;
				break;
			#endif
		}
	}
	else
	{
		//set not in use
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
	}
    //return 0
    return 0;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put data at serial I/O						                    |
//	| @NAME    :  usartPutc								                            |
//	| @INPUT   :  usartData	data to be Send		 				                    |
//	| @OUTPUT  :  									                                |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::putC(UHDC hdc,uint8_t usartData)
{
    //yes, check if opened
    if (_usartDriver.parms[hdc]._inUse)
    {
        //Set return ok
		_usartDriver.parms[hdc]._status=UStatus::OK;
        switch (hdc)
        {
            case 0:
                // Wait for empty transmit buffer
                while ( !( V_UCSR0A & (1<<V_UDRE0)) );				// no, sent to Tx line
                // Put data into buffer,
                V_UDR0=usartData;
                break;
            #if (defined(_AVR_IO128_H_) || defined(_AVR_IOM162_H_) || defined(_AVR_IOM1284P_H_))
                case 1:
                    // Wait for empty transmit buffer
                    while ( !( V_UCSR1A & (1<<V_UDRE1)) );				// no, sent to Tx line
                    // Put data into buffer,
                    V_UDR1=usartData;
                    break;
            #endif
        }
    }
    else
    {
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
    }
    //return status
    return _usartDriver.parms[hdc]._status;
}	
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put string data serial I/O		                        	    |
//	| @NAME    :  usartPutS								                            |
//	| @INPUT   :  stringData	data to be Send		 				                |
//	| @OUTPUT  :  									                                |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
UStatus class_USART::putS(UHDC hdc,const char *stringData)
{
    //yes, check if opened
    if (_usartDriver.parms[hdc]._inUse)
    {
            //Set return ok
        while (*stringData!='\0')
        {
            putC(hdc,(uint8_t)*stringData);
            stringData++;
        }
		_usartDriver.parms[hdc]._status=UStatus::OK;
    }
    else
    {
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
    }
    //return status
    return _usartDriver.parms[hdc]._status;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put string data from Flash at serial I/O	                	    |               
//	| @NAME    :  usartPutSF								                        |
//	| @INPUT   :  stringData	data to be Send		 				                |
//	| @OUTPUT  :  									                                |
//	| @REMARKS :  									                                |
//	+-------------------------------------------------------------------------------+
UStatus	class_USART::putSF(UHDC hdc,const char *stringData)
{
    char tmp;

	//yes, check if opened
	if (_usartDriver.parms[hdc]._inUse)
	{
		//loop until reach '\0'
		for(;;)
		{
				tmp=pgm_read_byte(stringData);
				if (tmp=='\0') break;
				putC(hdc,(uint8_t)tmp);
				stringData++;
		}
		//set status ok
		_usartDriver.parms[hdc]._status=UStatus::OK;
	}
    else
    {
        //set not opened
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
    }
    //return status
    return _usartDriver.parms[hdc]._status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get receiver data Size								            |
//	| @NAME    :  getRxDataSize								                        |
//	| @INPUT   :  									                                |
//	| @OUTPUT  : length of data in buffer									        |
//	| @REMARKS : return -1 if error 									            |
//	+-------------------------------------------------------------------------------+

int class_USART::getRxDataSize(UHDC hdc)
{
	//yes, check if opened
	if (_usartDriver.parms[hdc]._inUse)
	{
		//yes,get size
		_usartDriver.parms[hdc]._status=UStatus::OK;
		switch (hdc)
		{
			case 0:
				return cqLen((usartQueue*)&_usartDriver.RxBuffer0);
			break;
			#if (defined(_AVR_IO128_H_) || defined(_AVR_IO162_H_) || defined(_AVR_IOM1284P_H_))
			case 1:
				return cqLen((usartQueue*)&_usartDriver.RxBuffer1);
			break;
			#endif
		}
		//this line is here only to not get error message
		return -1;
	}
	else
	{
		//no, set port not opened
		_usartDriver.parms[hdc]._status=UStatus::NOT_OPENED;
		//return status
		return -1;	
	}	
}