/*
  ////////////////////////////////////////////////////////////////////////////////////////
  //       _____ _                _              _____                       		    //
  //      /  __ (_)              | |            |  _  |                      		    //
  //      | /  \/_ _ __ ___ _   _| | __ _ _ __  | | | |_   _  ___ _   _  ___ 		    //
  //      | |   | | '__/ __| | | | |/ _` | '__| | | | | | | |/ _ \ | | |/ _ \		    //
  //      | \__/\ | | | (__| |_| | | (_| | |    \ \/' / |_| |  __/ |_| |  __/		    //
  //       \____/_|_|  \___|\__,_|_|\__,_|_|     \_/\_\\__,_|\___|\__,_|\___|		    //
  //											                                        //
  ////////////////////////////////////////////////////////////////////////////////////////
  ---------------------- Circular Queue Functions C++ File (tab 4) -----------------------
*/


/*
 +--------------------------------------+
 |        HARDWARE DEPENDENT INCLUDES	|
 +--------------------------------------+
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
/*
 +--------------------------------------+
 |        C LIBRARY INCLUDES		    |
 +--------------------------------------+
*/
#include "_Circular_Queue.h"

/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS CONSTANTS	    |
 +--------------------------------------+
*/


/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS VARIABLES	    |
 +--------------------------------------+
*/


/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS STRUCTS	    |
 +--------------------------------------+
*/


/*
 +--------------------------------------+
 |					                    |
 |        QUEUE FUNCTIONS		        |
 |					                    |
 +--------------------------------------+
*/


//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Initialize Circular Queue											|
//	| NAME    :  cqInit																|
//	| INPUT   :  none																|
//	| OUTPUT  :  none																|
//	| REMARKS :  interrupts are disabled and restored								|
//	+-------------------------------------------------------------------------------+
void	cqInit(usartQueue *queue)
{
 	unsigned char sreg;

	sreg=SREG;							//save SREG state
	cli();								//disable interrupts
	queue->g=0;
	queue->p=0;
	queue->c=0;
	memset(queue->data,0,sizeof(queue->data));
	SREG=sreg;							//restore SREG state
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Put data into queue												|
//	| NAME    :  cqPut																|
//	| INPUT   :  usartQueue	-->queue of data										|
//	|	     cqData	data to be inserted on queue									|
//	| OUTPUT  :  true if queue is full false otherwise									|
//	| REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
unsigned char cqPut(usartQueue *queue,bool cqData)
{
	if (((queue->p+1) & USART_QUEUE_MASK)!=queue->g)
	{
		queue->data[queue->p]=cqData;		//put data into queue
		queue->p=(queue->p+1) & USART_QUEUE_MASK;		//next position to put
		queue->c++;				//data counter++
		return false;				//set queue not full
	}
	else
	{
		return true;				//set queue  full
	}	
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Get data from queue												|
//	| NAME    :  cqGet																|
//	| INPUT   :  usartQueue	-->queue of data										|
//	| OUTPUT  :  true if queue is empty false otherwise									|
//	|	     cqData	data retrieved from queue										|
//	| REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
bool cqGet(usartQueue *queue,unsigned char *cqData)
{
	if (queue->p==queue->g)
	{
		return true;				//set queue is empty
	}
	else
	{
		*cqData=queue->data[queue->g];		//get data into queue
		queue->g=(queue->g+1) & USART_QUEUE_MASK;		//next position to get
		queue->c--;				//data counter--
		return false;				//set queue not empty	
	}
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Check if quequeu is empty											|
//	| NAME    :  cqEmpty															|
//	| INPUT   :  usartQueue	-->queue of data										|
//	| OUTPUT  :  ON if queue is empty												|
//	| REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
bool cqEmpty(usartQueue *queue)
{
	if (queue->p==queue->g)
	{
		return true;				//return empty
	}
	else
	{
		return false;				//return not empty
	}
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Check if quequeu is full											|
//	| NAME    :  cqFull																|
//	| INPUT   :  usartQueue	-->queue of data										|
//	| OUTPUT  :  true if queue is Full												|
//	| REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
bool cqFull(usartQueue *queue)
{
	if (((queue->p+1) & USART_QUEUE_MASK)==queue->g)
	{
		return true;				//return full
	}
	else
	{
		return false;				//return not full
	}
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Get queue Length													|
//	| NAME    :  cqLen																|
//	| INPUT   :  usartQueue	-->queue of data										|
//	| OUTPUT  :  Quantity of data into queue										|
//	| REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
uint8_t	cqLen(usartQueue *queue)
{
	return queue->c;
}

