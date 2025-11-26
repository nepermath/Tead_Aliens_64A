/*
  ////////////////////////////////////////////////////////////////////////////////////////
  //        	 _   _ _____  ___  ______ _____  ______      _                		    //
  // 	      	| | | /  ___|/ _ \ | ___ \_   _| |  _  \    (_)               		    //
  //       	    | | | \ `--./ /_\ \| |_/ / | |   | | | |_ __ ___   _____ _ __ 		    //
  //       	    | | | |`--. \  _  ||    /  | |   | | | | '__| \ \ / / _ \ '__|		    //
  //       	    | |_| /\__/ / | | || |\ \  | |   | |/ /| |  | |\ V /  __/ |   		    //
  //        	 \___/\____/\_| |_/\_| \_| \_/   |___/ |_|  |_| \_/ \___|_|   		    //
  //                                                                     		        //	
  ////////////////////////////////////////////////////////////////////////////////////////
  // This Drive running on ATMEGA8,ATMEGA162,ATMEGA128 and atmega328p devices           //
  // Global interrupts must enabled to work properly                                    //
  -------------------------- USART Drive C++ File (tab 4) -------------------------------
*/


#ifndef _USART_Driver_H_
#define _USART_Driver_H_


/*
 +--------------------------------------+
 |        HARDWARE DEPENDENT INCLUDES	|
 +--------------------------------------+
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>

/*
	+--------------------------------------+
	|       C LIBRARY INCLUDES			   |
	+--------------------------------------+
*/
#include <string.h>
/*
	+--------------------------------------+
	|       LIBRARY INCLUDES			   |
	+--------------------------------------+
*/

#include "_Circular_Queue.h"
#include "_Timer.h"

/*
	+--------------------------------------+
	|       LOCAL DEFINITIONS		       |
	+--------------------------------------+
*/

#define _USART_DEFAULT_TIMEOUT		150
#define _USART_MAX_PORTS			2

/*
	+--------------------------------------+
	|       TYPEDEF ENUM DEFINITIONS	   |
	+--------------------------------------+
*/

/************************************************************************/
/* Communication Parity                                                 */
/************************************************************************/
typedef enum class UParity
{
	NONE=0,
	INVALID=1,
	EVEN=2,
	ODD=3,
}UParity;

/************************************************************************/
/* Communication Data Bits                                              */
/************************************************************************/
typedef enum class UDataBits
{
	DB_5=5,
	DB_6=6,
	DB_7=7,
	DB_8=8,
	INVALID	
}UDataBits;

/************************************************************************/
/* Communication Stop Bits                                              */
/************************************************************************/
typedef enum class UStopBits
{
	SB_1=1,
	SB_2=2,
	INVALID
}UStopBits;

/************************************************************************/
/* Communication Port                                                   */
/************************************************************************/
typedef enum class UPort:uint8_t
{
	USART_1=0,
	USART_2=1,
	INVALID
}UPort;

/************************************************************************/
/* Communication Status                                                 */
/************************************************************************/
typedef enum class UStatus:uint8_t
{
	OK,
	CLOSED,
	OPENED,
	NOT_OPENED,
	ALREADY_OPEN,
	TIMEOUT,
	INVALID_DATA_BITS,
	INVALID_PARITY,
	INVALID_STOP_BITS,
	INVALID_PORT           
}UStatus;
/*
	+--------------------------------------+
	|       TYPEDEFS		               |
	+--------------------------------------+
*/

//Handle to Device Context.
typedef uint8_t UHDC;
/*
	+--------------------------------------+
	|       DECLARATIONS                   |
	+--------------------------------------+
*/

#if defined(_AVR_IOM328P_H_)
    extern "C" void USART_RX_vect(void) __attribute__ ((signal));
#elif defined(_AVR_IOM128_H_)
    extern "C" void USART0_RX_vect(void) __attribute__ ((signal));
    extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
#elif defined(_AVR_IOM162_H_)
    extern "C" void USART0_RXC_vect(void) __attribute__ ((signal));
    extern "C" void USART1_RXC_vect(void) __attribute__ ((signal));
#elif defined(_AVR_IOM8_H_)
    extern "C" void USART_RXC_vect(void) __attribute__ ((signal));
#elif defined(_AVR_IOM1284P_H_)
	extern "C" void USART0_RX_vect(void) __attribute__ ((signal));
	extern "C" void USART1_RX_vect(void) __attribute__ ((signal));
#endif

/*
	+--------------------------------------+
	|       TYPEDEF			               |
	+--------------------------------------+
*/

/*
        +-------------------------------------------------------+
        |        CLASS USART Drive                              |
        +-------------------------------------------------------+
        | @PURPOSE      : Perform all function to control TX and|
        |                 RX operation well done                |
        | @OBSERVATIONS :                                       |
        +-------------------------------------------------------+
*/

class class_USART
{
        /*
         +--------------------------------------+
         |       PRIVATE VARIABLES		        |
         +--------------------------------------+
        */
 private:
//         uint8_t                 _usartPort;
//         uint32_t                _baudRate;
//         uint8_t                 _dataBits;
//         uint8_t                 _parityType;
//         uint8_t                 _stopBits;
//         uint32_t                _timeoutMilliseconds;
//         uint8_t                 _usartStatus;
        class_Timer             _Time;
        /*
         +--------------------------------------+
         |       PRIVATE FUNCTIONS      	    |
         +--------------------------------------+
        */
		#if defined(_AVR_IOM328P_H_)
		  friend void    USART0_RX_vect(void);
        #elif defined(_AVR_IOM128_H_)
          friend void    USART0_RX_vect(void);
          friend void    USART1_RX_vect(void);
        #elif defined(_AVR_IOM162_H_)
          friend void    USART0_RXC_vect(void);
          friend void    USART1_RXC_vect(void);
        #elif defined(_AVR_IOM8_H_)
          friend void    USART_RXC_vect(void);
        #elif defined(_AVR_IOM1284P_H_)
	        friend void    USART0_RX_vect(void);
			friend void    USART1_RX_vect(void);
        #endif
        /*
         +--------------------------------------+
         |        PUBLIC FUNCTIONS		        |
         +--------------------------------------+
        */
public:
        
        /************************************************************************/
        /* Constructor #1                                                       */
        /************************************************************************/
        class_USART(void);
		/************************************************************************/
		/* Destructor                                                           */
		/************************************************************************/
		~class_USART(void);
        /************************************************************************/
        /* Prepare USART Drive for Sleep                                        */
        /************************************************************************/
		void			prepareForSleep(void);
		/************************************************************************/
		/* Restore USART Drive from Sleep                                       */
		/************************************************************************/
		void			restoreFromSleep(void);
		/************************************************************************/
		/* Get/Set USART Port USART_1 OR USART_2                                */
		/************************************************************************/
        //uint8_t         getUSARTPort(void);
        //UStatus         setUSARTPort(UPort usartPort);
		/************************************************************************/
		/* Get/Set USART Baudrate                                               */
		/************************************************************************/
        uint32_t        getBaudRate(UHDC hdc);
        UStatus         setBaudRate(UHDC hdc,uint32_t baudRate);
		/************************************************************************/
		/* Get/Set USART Number of Data Bits                                    */
		/************************************************************************/
        UDataBits       getDataBits(UHDC hdc);
        UStatus         setDataBits(UHDC hdc,UDataBits dataBits);
		/************************************************************************/
		/* Get/Set USART Parity Type                                            */
		/************************************************************************/
        UParity         getParityType(UHDC hdc);
        UStatus         setParityType(UHDC hdc,UParity parityType);
		/************************************************************************/
		/* Get/Set USART Number of Stop Bits                                    */
		/************************************************************************/
        UStopBits       getStopBits(UHDC hdc);
        UStatus         setStopBits(UHDC hdc,UStopBits stopBits);
		/************************************************************************/
		/* Get/Set USART TimeOut for Reception                                  */
		/************************************************************************/
        uint32_t        getTimeout(UHDC hdc);
        UStatus         setTimeout(UHDC hdc,uint32_t timeoutMilliseconds);
		/************************************************************************/
		/* Get USART Status                                                     */
		/************************************************************************/
        UStatus         status(UHDC hdc);
		/************************************************************************/
		/* Open USART USART_1 or USART_2                                        */
		/************************************************************************/
        UStatus         open(UHDC &hdc,UPort usartPort,uint32_t baudRate,UDataBits dataBits,UParity parityType,UStopBits stopBits);
		/************************************************************************/
		/* Close USART Port                                                     */
		/************************************************************************/
        void            close(UHDC hdc);
		/************************************************************************/
		/* Flush USART                                                          */
		/************************************************************************/
        UStatus         flush(UHDC hdc);
		/************************************************************************/
		/* Get Character from USART                                             */
		/************************************************************************/
        uint8_t 	    getC(UHDC hdc);
		/************************************************************************/
		/* Put Character into USART                                             */
		/************************************************************************/
        UStatus		    putC(UHDC hdc,uint8_t usartData);
		/************************************************************************/
		/* Put String into USART                                                 */
		/************************************************************************/
        UStatus	        putS(UHDC hdc,const char *stringData);
		/************************************************************************/
		/* Put STring from FLASH into USART                                     */
		/************************************************************************/
        UStatus	        putSF(UHDC hdc,const char *stringData);
		/************************************************************************/
		/* Get Rx data size                                                     */
		/************************************************************************/
		int				getRxDataSize(UHDC hdc);
};

#endif //#define _USART_Drive_H_