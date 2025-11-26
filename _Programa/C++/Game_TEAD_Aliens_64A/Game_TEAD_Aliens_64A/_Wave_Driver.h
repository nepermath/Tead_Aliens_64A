/*
	//////////////////////////////////////////////////////////////////////////////////////////	
					 _____ _                 _    _
					/  __ \ |               | |  | |
					| /  \/ | __ _ ___ ___  | |  | | __ ___   _____
					| |   | |/ _` / __/ __| | |/\| |/ _` \ \ / / _ \
					| \__/\ | (_| \__ \__ \ \  /\  / (_| |\ V /  __/
					 \____/_|\__,_|___/___/  \/  \/ \__,_| \_/ \___|
 		
    //////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- HEADER FILE (tab 4)-----------------------------------

*/


#ifndef _WAVE_DRIVER_H_
#define _WAVE_DRIVER_H_

/*
 +--------------------------------------+
 |        HARDWARE DEPENDENT INCLUDES	|
 +--------------------------------------+
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <util/delay.h>

/*
 +--------------------------------------+
 |        C LIBRARY INCLUDES		    |
 +--------------------------------------+
*/
#include <ctype.h>
#include <stdint.h>
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

	//PORTS AND PIN DEFINITIONS
	#define		_WAVE_PORT_OUTPUT		PORTB
	#define		_WAVE_PORT_DIR			DDRB
	#define		_WAVE_PORT_INPUT		PINB

	#define		_WAVE_PIN				7


/*
 +--------------------------------------+
 |        DEFINES						|
 +--------------------------------------+
*/

#define _WAVE_MAX_WAVES	8
/*
 +--------------------------------------+
 |        ENUNS DEFINITIONS		        |
 +--------------------------------------+
*/


/*
 +--------------------------------------+
 |        TYPE DEFINITIONS		        |
 +--------------------------------------+
*/

//--------------------------------------------
//WAVE Play Mode
//--------------------------------------------
typedef enum class PlayMode:uint8_t
{
	ONCE,
	LOOP
}PlayMode;
//--------------------------------------------
//WAVE Channel number
//--------------------------------------------
typedef enum class WaveChannel:uint8_t
{
	CHANNEL_1,
	CHANNEL_2,
	CHANNEL_3,
	CHANNEL_4,
	CHANNEL_5,
	CHANNEL_6,
	CHANNEL_7,
	CHANNEL_8
}WaveChannel;
//--------------------------------------------
//WAVE Status
//--------------------------------------------
typedef enum class WaveStatus:uint8_t
{
	PREPARED,
	STOPPED,
	PLAYING,
	UMPREPARED
}WaveStatus;
//--------------------------------------------
//WAVE
//--------------------------------------------
typedef const uint8_t * WAVE;
/*
 +--------------------------------------+
 |        CONSTANT DEFINITIONS		    |
 +--------------------------------------+
*/


/*
 +--------------------------------------+
 |         SOUND STRUCTS	        	|
 +--------------------------------------+
*/

#define LPWAVE(var) pgm_get_far_address(var)


/*
	+--------------------------------------+
	|       EXTERNAL DECLARATIONS          |
	+--------------------------------------+
*/

						 
/*
        +-------------------------------------------------------+
        |        CLASS			WAVE		                    |
        +-------------------------------------------------------+
        | @PURPOSE      : TO GENERATE AUDIO FROM WAVE FILES		|
        | @OBSERVATIONS :										|
        +-------------------------------------------------------+
*/

class class_Wave
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
		void	UnInitialize(void);
        /*
         +--------------------------------------+
         |        PUBLIC FUNCTIONS		        |
         +--------------------------------------+
        */
public:
		/*
         +--------------------------------------+
         |       PUBBLIC VARIABLES		        |
         +--------------------------------------+
        */
        /*
         +--------------------------------------+
         |       PUBLIC  FUNCTIONS      	    |
         +--------------------------------------+
        */

        /************************************************************************/
        /* Constructor															*/
        /************************************************************************/
        class_Wave(void);
		/************************************************************************/
		/* Destructor                                                           */
		/************************************************************************/
		~class_Wave(void);
		/**************************************************************************/
		/* Main initialization wave function must be called for work appropriately*/
		/**************************************************************************/
		void	Initialize(void);
		/************************************************************************/
		/* Process sounds (used internally)                                     */
		/************************************************************************/
		static void	SoundProcess(void);
		/************************************************************************/
		/* Get maximum waves to play                                            */
		/************************************************************************/
		static uint8_t GetMaxWaves();
		/************************************************************************/
		/* Get State of Playing Wave , return true if playing or false if not   */
		/* Playing or invalid waveIndex											*/
		/************************************************************************/
		static bool Playing(WaveChannel waveChannel);
		/************************************************************************/
		/* Prepare Wave to Play                                                 */
		/* This function only prepare resources to further play a Wave		    */
		/* use Play to play a Wave after use this function						*/
		/* if prepare is true wave is ok to play otherwise still in use			*/
		/* or maximum wave playing is reach										*/
		/* use LPWAVE to get pointer of wave data in flash						*/
		/************************************************************************/
		static bool Prepare(WAVE waveInFlashPtr,WaveChannel waveChannel);
		/************************************************************************/
		/* Play a Wave                                                          */
		/* waveLoop true for playing wave in loop false play one time only		*/
		/************************************************************************/
		static void Play(WaveChannel waveChannel,PlayMode waveMode=PlayMode::ONCE);
		/************************************************************************/
		/* UnPrepare Wave Attached by Prepare function and free this channel    */
		/************************************************************************/
		static void Unprepare(WaveChannel waveChannel);
		/************************************************************************/
		/* Stop Wave To Play, and use play again to replay a wave               */
		/************************************************************************/
		static void Stop(WaveChannel waveChannel);
		/************************************************************************/
		/* UnStop Wave To Play, and use play again to replay a wave             */
		/************************************************************************/
		static void UnStop(WaveChannel waveChannel);
		/************************************************************************/
		/* Play Full i.e. Play, wait to finish and close                        */
		/* if channel in used this function exit with no playing				*/	
		/************************************************************************/
		static void PlayFull(WAVE waveInFlashPtr,WaveChannel waveChannel);
		/************************************************************************/
		/* Set Volume in Percentage 0 = no sound 100 max volume                 */
		/************************************************************************/
		static void SetVolume(int volume);
		/************************************************************************/
		/* Return Number of Available Audio Channels                            */
		/************************************************************************/
		static int getNumberOfChannels(void);
		/************************************************************************/
		/* Get Interrupt Count Value                                            */
		/************************************************************************/
		int getCount();
		/************************************************************************/
		/* Get Wave Number of Samples                                           */
		/************************************************************************/
		uint16_t	getSamples(WaveChannel waveChannel);
		/************************************************************************/
		/* Get Samples per second                                               */
		/************************************************************************/
		uint16_t	getSamplesPerSecond(WaveChannel waveChannel);
		/************************************************************************/
		/* Play Time in milliseconds                                            */
		/************************************************************************/
		uint16_t	getPlayTime(WaveChannel waveChannel);
		/************************************************************************/
		/* Set Tone Generator State ON=true , OFF=false                         */
		/************************************************************************/
		void	setToneGenStatus(bool status);
		/************************************************************************/
		/* Tone with frequency                                                  */
		/************************************************************************/
		void	setToneGen(uint16_t freq,uint16_t duration,uint8_t channel);
		/************************************************************************/
		/* Set Tone Generator Volume in percentage 0% no audio 100% max volume  */
		/************************************************************************/
		void	setToneVolume(uint8_t volumeInPerc);
};//Class
#endif //WAVE_DRIVER