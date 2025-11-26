/*
	//////////////////////////////////////////////////////////////////////////////////////////
 						  _____ _                 _    _
 						  /  __ \ |               | |  | |
 						  | /  \/ | __ _ ___ ___  | |  | | __ ___   _____
 						  | |   | |/ _` / __/ __| | |/\| |/ _` \ \ / / _ \
 						  | \__/\ | (_| \__ \__ \ \  /\  / (_| |\ V /  __/
 						  \____/_|\__,_|___/___/  \/  \/ \__,_| \_/ \___|
 						  
    //////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- C++ FILE (tab 4)-----------------------------------
*/
/*
 +--------------------------------------+
 |        LOCAL C LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#ifdef ESP32
	#include <pgmspace.h>
#else
	#include <avr/pgmspace.h>
#endif
/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Wave_Driver.h"


/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/


#define WAVE_PCM	1


/*
 +--------------------------------------+
 |        STRUCTURES				 	|
 +--------------------------------------+
*/
struct _wave_Struct
{
	int				waveVolume=4;			//Initial wave volume
	struct  
	{
		WAVE			wavePtr=0;				//Initial wave Pointer
		uint32_t		waveSamples=0;			//Initial wave number of wave Samples
		uint32_t		waveSamplesPerSec=0;	//hold wave samples per second
		uint32_t		waveAvrBytesPerSec=0;	//hold wave average bytes per second
		uint8_t			waveBlockAlign=0;		//Wave Block Alignment
		uint8_t			waveBits=0;				//Wave Sample bits
		WAVE			wavePtrRun=0;			//running wave Pointer (this value is changed during play)
		uint32_t		waveSamplesRun=0;		//running wave Samples (this value is changed during play)
		bool			waveInUse=false;		//wave in use
		bool			wavePlaying=false;		//wave playing
		bool			waveLoop=false;			//true to make a wave playing in loop
	} waves[_WAVE_MAX_WAVES];
	uint16_t		sqrN;						//frequency generator N 16 bits size
	int8_t			sqrAmplitude;				//frequency generator amplitude
	bool			sqrStatus;					//frequency generator State ON of OFF
	int count=0;
	class_Timer		timer;
	void			(*ReturnCallBack)()		=nullptr;				//return callback for time object
}_Wave;

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


void    class_Wave::Initialize()
{
	static bool initialize=false;
	
	uint8_t sreg;
	
	if (initialize==false)
	{
		initialize=true;
		
		//save SREG
		sreg=SREG;
		//disable interrupts
		cli();
		//program sound pin as output
		_WAVE_PORT_OUTPUT|=(1<<_WAVE_PIN);
		_WAVE_PORT_DIR|=(1<<_WAVE_PIN);
		//program timer 1 to FAST PWM 8 Bits
		TCCR2=(1<<COM21)|(0<<COM20)|(1<<WGM21)|(1<<WGM20)|(0<<CS22)|(0<<CS21)|(1<<CS20);
		//half duty cycle
		OCR2=0x7f;
		//set volume
		SetVolume(25);
		//wave generator amplitude
		setToneVolume(25);
		//wave generator off
		setToneGenStatus(false);
		//Wave  N generator =0 "no sound"
		_Wave.sqrN=0;
		//get old timer callback
		_Wave.ReturnCallBack=_Wave.timer.getHandleCallBack();
		//Add Call backs
		_Wave.timer.setHandleCallBack(SoundProcess);
		//restore SREG state
		SREG=sreg;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ZERO Cross Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_Wave::UnInitialize()
{
	uint8_t sreg;

	//save SREG
	sreg=SREG;
	//disable interrupts
	cli();
	//program sound pin as output
	_WAVE_PORT_OUTPUT&=~(1<<_WAVE_PIN);
	_WAVE_PORT_DIR&=~(1<<_WAVE_PIN);
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
class_Wave::class_Wave()
{
	Initialize();
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   : string in flash                                                    |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Wave::~class_Wave()
{
	//Initialize PID
	UnInitialize();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Send Data to Wave Out device                                       |
//	| @NAME    : DataOut								                            |
//	| @INPUT   : data to be output                                                  |
//	| @OUTPUT  : none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
static inline void dacOut(uint8_t dataOut)
{
	OCR2=dataOut;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Wave Interrupt Process	                                            |
//	| @NAME    : SoundProcess							                            |
//	| @INPUT   : none			                                                    |
//	| @OUTPUT  : none								                                |
//	| @REMARKS : return value from -127 to 127						                |
//	+-------------------------------------------------------------------------------+
static int8_t getWaveData(uint8_t waveChannel)
{
	uint8_t wData;
	
	if (_Wave.waves[waveChannel].wavePlaying)
	{
		//yes, send data to audio output
		wData=pgm_read_byte(_Wave.waves[waveChannel].wavePtrRun)-127;
		//decrement wave sample
		_Wave.waves[waveChannel].waveSamplesRun--;
		//next data address, in this library i assume that samples bits is one and one channel
		_Wave.waves[waveChannel].wavePtrRun++;
		//check if data end
		if (_Wave.waves[waveChannel].waveSamplesRun<1)
		{
			//reload wave to play if in loop
			if (_Wave.waves[waveChannel].waveLoop)
			{
				//reload wave
				_Wave.waves[waveChannel].wavePtrRun=_Wave.waves[waveChannel].wavePtr;
				_Wave.waves[waveChannel].waveSamplesRun=_Wave.waves[waveChannel].waveSamples;
			}
			else
			{
				//stop playing and in use
				_Wave.waves[waveChannel].wavePlaying=false;
			}
		}
	}
	else
	{
		wData=0;
	}
	//return wave dta
	return wData;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Wave Interrupt Process	                                            |
//	| @NAME    : SoundProcess							                            |
//	| @INPUT   : none			                                                    |
//	| @OUTPUT  : none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//	f=n/m*fs
//
//	fs =sample frequency
//	m  =bit size 2^nbit
//	n  =frequency number
//	f  =frequency
// nbit= numero de bits
//
// for 16 bits solving for n for 16 bits and 5000Hz sample rate
//
//	 (65536)*f/5000=n


void class_Wave::SoundProcess()
{
	int16_t dataW;
	//Square Wave Level
	static int8_t	squareWave=0;
	//Square Wave N Counter
	static uint16_t  sqrP=0;
	
	//pump wave counter
	//_Wave.count++;
	
	//square wave generator on?
	if (_Wave.sqrStatus)
	{
		//Pump Wave generator number
		sqrP+=_Wave.sqrN;
	
		//change level
		if (sqrP&0x8000)
		{
			squareWave=_Wave.sqrAmplitude;
		}
		else
		{
			squareWave=-_Wave.sqrAmplitude;
		}		
	}
	else
	{
		squareWave=0;
	}
	
	//compute Wave Data Output
	dataW=((int)getWaveData(0)+(int)getWaveData(1)+
		   (int)getWaveData(2)+(int)getWaveData(3)+
		   (int)getWaveData(4)+(int)getWaveData(5)+
		   (int)getWaveData(6)+(int)getWaveData(7)+
		   (int)squareWave+
		   squareWave)*_Wave.waveVolume;
	//dataW=getWaveData(0);
	if (dataW>127) dataW=127;
	if (dataW<-127) dataW=-127;
		
	//Output a Wave
	dacOut(dataW+127);
	
	//process handle callback
	if (_Wave.ReturnCallBack!=nullptr) _Wave.ReturnCallBack();
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Sound ISR															|
//	| @NAME    :  Sound_ISR				       										|
//	| @INPUT   :  none																|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
// void _Wave_Handle_CallBack(void)
// {
// 	
// 	//Process RTC
// 	class_Wave::SoundProcess();
// 	//Call old callback
// 	if (_Wave.ReturnCallBack!=nullptr) _Wave.ReturnCallBack();
// }
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Return maxium waves played by this drive							|
//	| @NAME    :  getMaxWaves			       										|
//	| @INPUT   :  none																|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
uint8_t class_Wave::GetMaxWaves()
{
	return _WAVE_MAX_WAVES;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Return Playing State												|
//	| @NAME    :  Playing				       										|
//	| @INPUT   :  none																|
//	| @OUTPUT  :  true if Playing or false if no Playing o invalid waveChannel		|                        |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
bool class_Wave::Playing(WaveChannel waveChannel)
{
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1)) return false;
	return _Wave.waves[(uint8_t)waveChannel].wavePlaying;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Prepare															|
//	| @NAME    :  Prepare				       										|
//	| @INPUT   :  none																|
//	| @OUTPUT  :  true if prepare is ok								                |
//	| @REMARKS :  This function only prepare resources to further play a Wave		|
//	|			  use Play function to play a wave after use this function			|
//	|			  this function return true if wave is ok to play otherwise still	|
//	|			  in use or maximum wave playing is reach							|
//	|			  first wave index is 0,next 1 and etc until MAX_WAVE-1				|
//	|			  use LPWAVE to get pointer of wave data in flash					|
//	+-------------------------------------------------------------------------------+
bool class_Wave::Prepare(WAVE waveInFlashPtr,WaveChannel waveChannel)
{
	uint8_t	 sreg;
	uint8_t	 nChannels;			//number of wave channels
	uint32_t nSamplesPerSec;	//Samples Per Second
	uint32_t nAvrBytesPerSec;	//Average Bytes Per Second
	uint8_t	 nBlockAlign;		//Block Alignment
	uint8_t	 nBits;				//Number of bits sample
	uint32_t nSamples;			//Number of Samples
	
	//save SREG State
	sreg=SREG;
	//disable interrupts
	cli();
	//return false if waveChannel>MAX_WAVE-1
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1))
	{
		//restore SREG state
		SREG=sreg;
		return false;
	}
	//return false if wavechannel is in use
// 	if (_Wave.waves[(uint8_t)waveChannel].waveInUse)
// 	{
// 		//restore SREG state
// 		SREG=sreg;
// 		return false;
// 	}
	//return false if not PCM wave
	if (pgm_read_byte(waveInFlashPtr)!=WAVE_PCM)
	{
		//restore SREG state
		SREG=sreg;		
		return false;
	}
	waveInFlashPtr+=1;
	//get number of channels
	nChannels=pgm_read_byte(waveInFlashPtr);
	waveInFlashPtr+=1;
	//get samples per second
	nSamplesPerSec=pgm_read_dword(waveInFlashPtr);
	waveInFlashPtr+=4;
	//get average bytes per second
	nAvrBytesPerSec=pgm_read_dword(waveInFlashPtr);
	waveInFlashPtr+=4;
	//get Block alignment size
	nBlockAlign=pgm_read_byte(waveInFlashPtr);
	waveInFlashPtr+=1;
	//get Sample bits
	nBits=pgm_read_byte(waveInFlashPtr);
	waveInFlashPtr+=1;
	//get wave number of samples
	nSamples=pgm_read_dword(waveInFlashPtr);
	waveInFlashPtr+=4;
	//now waveinFlashPtr has a data pointer
	//return false if nChannels > 1
	if (nChannels>1) return false;
	//return false if SamplesPerSec=0 or greater 44100
	if (nSamplesPerSec==0 || nSamplesPerSec>44100)
	{
		//restore SREG state
		SREG=sreg;		
		return false;
	}
	//return false if AverageBytesPerSec=0 or greater 
	if (nAvrBytesPerSec==0 || nAvrBytesPerSec>88200)
	{
		//restore SREG state
		SREG=sreg;
		return false;
	}
	//return false if block alignment is 0
	if (nBlockAlign==0)
	{
		//restore SREG state
		SREG=sreg;		
		return false;
	}
	//return false if nBits =0 
	if (nBits==0)
	{
		//restore SREG state
		SREG=sreg;	
		return false;
	}
	//return false if nBits not 0
	if (nBits!=8)
	{
		//restore SREG state
		SREG=sreg;		
		return false;
	}
	//return if number of samples > 32767-16
	//if (nSamples>(32767-16)) return false; //<=used only in atmega128p
	//set value indexes
	_Wave.waves[(uint8_t)waveChannel].waveSamplesPerSec=nSamplesPerSec;
	_Wave.waves[(uint8_t)waveChannel].waveAvrBytesPerSec=nAvrBytesPerSec;
	_Wave.waves[(uint8_t)waveChannel].waveBlockAlign=nBlockAlign;
	_Wave.waves[(uint8_t)waveChannel].waveSamplesRun=nSamples;
	_Wave.waves[(uint8_t)waveChannel].waveSamples=nSamples;
	_Wave.waves[(uint8_t)waveChannel].wavePtr=waveInFlashPtr;
	_Wave.waves[(uint8_t)waveChannel].wavePtrRun=waveInFlashPtr;
	_Wave.waves[(uint8_t)waveChannel].waveInUse=true;
	//restore SREG State
	SREG=sreg;
	return true;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Play wave in flash data											|
//	| @NAME    :  Play					       										|
//	| @INPUT   :  WaveIndex to play 0..1											|
//	|			  PlayMode may be ONCE or LOOP										|
//	| @OUTPUT  :  none												                |
//	| @REMARKS :  If WaveIndex>WAVE_MAX then  none occurs							|
//	|			  if this function called before wave reach the end the wave is		|
//	|			  reload and played from the beginning again						|
//	+-------------------------------------------------------------------------------+
void class_Wave::Play(WaveChannel waveChannel,PlayMode wavePlayMode)
{
	#ifdef ESP32
	#else
		//save SREG
		uint8_t sreg=SREG;
	#endif
	//disable interrupts during play preparing

	//If waveIndex > _WAVE_MAX_WAVES-1 then return
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1)) return;
	//if Wave not in use then return
	if (!_Wave.waves[(uint8_t)waveChannel].waveInUse) return;
	//disable interrupt 
	#ifdef ESP32
		noInterrupts();
	#else
		cli();
	#endif
	//if waveChannel playing then restart a play
	//_Wave.waves[(uint8_t)waveChannel].waveInUse=true;
	//if wave in playing mode then restart play
	_Wave.waves[(uint8_t)waveChannel].wavePtrRun=_Wave.waves[(uint8_t)waveChannel].wavePtr;
	_Wave.waves[(uint8_t)waveChannel].waveSamplesRun=_Wave.waves[(uint8_t)waveChannel].waveSamples;
	_Wave.waves[(uint8_t)waveChannel].wavePlaying=true;
	//set play mode
	switch(wavePlayMode)
	{
		case PlayMode::ONCE:
			_Wave.waves[(uint8_t)waveChannel].waveLoop=false;
		break;
		case PlayMode::LOOP:
			_Wave.waves[(uint8_t)waveChannel].waveLoop=true;
		break;
	}
	//restore interrupts 
	#ifdef ESP32
		interrupts();
	#else
		SREG=sreg;
	#endif
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Unprepare wave attached by Prepare function						|
//	| @NAME    :  Play					       										|
//	| @INPUT   :  waveChannel														|
//	| @OUTPUT  :  none												                |
//	| @REMARKS :  This function release a waveChannel for another wave to play		|
//	+-------------------------------------------------------------------------------+
void class_Wave::Unprepare(WaveChannel waveChannel)
{
	#ifdef ESP32
	#else
		//save SREG state
		uint8_t sreg=SREG;
	#endif
	//exit if invalid waveChannel
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1)) return;
	//disable interrupts and release channel
	#ifdef ESP32
		noInterrupts();
	#else
		cli();
	#endif
	//set wave use and playing to false
	_Wave.waves[(uint8_t)waveChannel].waveInUse=false;
	_Wave.waves[(uint8_t)waveChannel].wavePlaying=false;
	#ifdef ESP32
		interrupts();
	#else
		//restore sreg state
		SREG=sreg;
	#endif
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Stop Wave to Play													|
//	| @NAME    :  Stop					       										|
//	| @INPUT   :  waveChannel														|
//	| @OUTPUT  :  none												                |
//	| @REMARKS :  This function Stop a wave to play, use Play again to play from	|
//	|			  the begining														|		
//	+-------------------------------------------------------------------------------+
void class_Wave::Stop(WaveChannel waveChannel)
{
	//exit if invalid waveChannel
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1)) return;
	//stop to play
	_Wave.waves[(uint8_t)waveChannel].wavePlaying=false;	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnStop Wave to Play												|
//	| @NAME    :  UnStop				       										|
//	| @INPUT   :  waveChannel														|
//	| @OUTPUT  :  none												                |
//	| @REMARKS :  This function Stop a wave to play, use Play again to play from	|
//	|			  the begining														|
//	+-------------------------------------------------------------------------------+
void class_Wave::UnStop(WaveChannel waveChannel)
{
	//exit if invalid waveChannel
	if ((uint8_t)waveChannel>(_WAVE_MAX_WAVES-1)) return;
	//stop to play
	_Wave.waves[(uint8_t)waveChannel].wavePlaying=true;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Play Full Wave Play,Wait and Release channel						|
//	| @NAME    :  PlayFull				       										|
//	| @INPUT   :  waveChannel														|
//	| @OUTPUT  :  none												                |
//	| @REMARKS : this function not released until play finished						|
//	|			 if channel in used this function exit without play					|
//	+-------------------------------------------------------------------------------+
void class_Wave::PlayFull(WAVE waveInFlashPtr,WaveChannel waveChannel)
{
	if (Prepare(waveInFlashPtr,waveChannel)==false) return;
	Play(waveChannel,PlayMode::ONCE);
	do {} while (Playing(waveChannel));
	Unprepare(waveChannel);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Wave Volume													|
//	| @NAME    :  setVolume				       										|
//	| @INPUT   :  volume in percentage												|
//	| @OUTPUT  :  none												                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Wave::SetVolume(int volume)
{
	//saturate volume if <0 or >=8
	if (volume<0) volume=0;
	if (volume>=100) volume=100;
	//set volume
	_Wave.waveVolume=volume*8/100;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  get available audio channels										|
//	| @NAME    :  getCount				       										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  Count												                |
//	| @REMARKS :  if counting then interrupts ok									|
//	+-------------------------------------------------------------------------------+
int	class_Wave::getNumberOfChannels()
{
	return _WAVE_MAX_WAVES;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  used to check if sound interrupts is ok							|
//	| @NAME    :  getCount				       										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  Count												                |
//	| @REMARKS :  if counting then interrupts ok									|
//	+-------------------------------------------------------------------------------+

int class_Wave::getCount()
{
	return _Wave.count;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get number of Samples of wave										|
//	| @NAME    :  getSamples			       										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  number of samples									                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
uint16_t	class_Wave::getSamples(WaveChannel waveChannel)
{
	//if channel > num channesl return 0
	if ((uint8_t)waveChannel>_WAVE_MAX_WAVES-1) return 0;
	//return samples
	return _Wave.waves[(uint8_t)waveChannel].waveSamples;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  get Samples Per Second											|
//	| @NAME    :  getSamplesPerSecond       										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  Samples per second								                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
uint16_t	class_Wave::getSamplesPerSecond(WaveChannel waveChannel)
{
	//if channel > num channesl return 0
	if ((uint8_t)waveChannel>_WAVE_MAX_WAVES-1) return 0;
	//return samples
	return _Wave.waves[(uint8_t)waveChannel].waveSamplesPerSec;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  get Play Time in milliseconds										|
//	| @NAME    :  getPlayTime			       										|
//	| @INPUT   :																	|
//	| @OUTPUT  :  Playing timing in milliseconds					                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
uint16_t	class_Wave::getPlayTime(WaveChannel waveChannel)
{
	//if channel > num channesl return 0
	if ((uint8_t)waveChannel>_WAVE_MAX_WAVES-1) return 0;
	//return samples
	return (_Wave.waves[(uint8_t)waveChannel].waveSamplesPerSec*1000L)/_Wave.waves[(uint8_t)waveChannel].waveSamples;	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Tone Generatore a Tone State									|
//	| @NAME    :  setToneGenStatus			       									|
//	| @INPUT   :  status ON=true OFF=false											|
//	| @OUTPUT  :													                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Wave::setToneGenStatus(bool status)
{
	_Wave.sqrStatus=status;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Generate a Tone with specific frequency							|
//	| @NAME    :  setToneGen			       										|
//	| @INPUT   :  frequency															|
//	| @OUTPUT  :													                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Wave::setToneGen(uint16_t freq,uint16_t duration,uint8_t channel)
{
	_Wave.sqrN=((long)freq<<16)/_TIMER_INTERRUPT_FREQUENCY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Tone Generator Volume											|
//	| @NAME    :  setToneVolume			       										|
//	| @INPUT   :  Volume															|
//	| @OUTPUT  :													                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Wave::setToneVolume(uint8_t volumeInPerc)
{
	_Wave.sqrAmplitude=volumeInPerc*32/100;
}
