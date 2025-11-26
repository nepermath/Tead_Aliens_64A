/*
	///////////////////////////////////////////////////////////////////////////////////////////////////////
 			     _____ _____  ___ ______    ___   _     _____ _____ _   _  _____
				|_   _|  ___|/ _ \|  _  \  / _ \ | |   |_   _|  ___| \ | |/  ___|
				  | | | |__ / /_\ \ | | | / /_\ \| |     | | | |__ |  \| |\ `--.
				  | | |  __||  _  | | | | |  _  || |     | | |  __|| . ` | `--. \
				  | | | |___| | | | |/ /  | | | || |_____| |_| |___| |\  |/\__/ /
				  \_/ \____/\_| |_/___/   \_| |_/\_____/\___/\____/\_| \_/\____/
		
							 _____   ___  ___  ___ _____
							|  __ \ / _ \ |  \/  ||  ___|
							| |  \// /_\ \| .  . || |__
							| | __ |  _  || |\/| ||  __|
							| |_\ \| | | || |  | || |___
							 \____/\_| |_/\_|  |_/\____/
	
    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- C FILE (tab 4)------------------------------------------------------
*/

/*	+-----------------------------------------------+
	| [English  ] LOCAL LIBRARY INCLUDES			|
	| [Portugues] BIBLIOTECAS DE INCLUSAO LOCAL		|
	+-----------------------------------------------+
*/

#include "_TEAD_Aliens.h"


/*
	+-------------------------------+
	| [English  ] LOCAL RESOURCES	|
	| [Portugues] RECURSOS LOCAIS	|
	+-------------------------------+
*/

//--------------------------------------------------------
// [English  ] BMP FILES
// [Portugues] ARQUIVOS DE BMP
//--------------------------------------------------------
#include "_Resources/BMP_Mother_Ship.h"
#include "_Resources/BMP_Time_Set.h"
#include "_Resources/BMP_Exit_Only.h"
#include "_Resources/BMP_Ship_1_1.h"
#include "_Resources/BMP_Ship_1_2.h"
#include "_Resources/BMP_Ship_2_1.h"
#include "_Resources/BMP_Ship_2_2.h"
#include "_Resources/BMP_Ship_3_1.h"
#include "_Resources/BMP_Ship_3_2.h"
#include "_Resources/BMP_SHIP_DOT_1.h"
#include "_Resources/BMP_SHIP_DOT_2_1.h"
#include "_Resources/BMP_SHIP_DOT_2_2.h"
#include "_Resources/BMP_SHIP_DOT_2_3.h"
#include "_Resources/BMP_Left_Big.h"
#include "_Resources/BMP_Left_Little.h"
#include "_Resources/BMP_Right_Big.h"
#include "_Resources/BMP_Right_Little.h"
#include "_Resources/BMP_Up_Big.h"
#include "_Resources/BMP_Up_Little.h"
#include "_Resources/BMP_Down_big.h"
#include "_Resources/BMP_Down_Little.h"
#include "_Resources/BMP_clock.h"
#include "_Resources/BMP_clock2.h"
#include "_Resources/BMP_clockSet.h"
#include "_Resources/BMP_Calendar.h"
#include "_Resources/BMP_cobra.h"
#include "_Resources/BMP_Reset.h"
#include "_Resources/BMP_Empty.h"

//--------------------------------------------------------
// [English  ] WAVE FILES
// [Portugues] ARQUIVOS DE WAVES
//--------------------------------------------------------
#include "_Resources/WAVE_tank_moving_2_5000_8.h"
#include "_Resources/WAVE_Canno_Fire_5000_8.h"
#include "_Resources/WAVE_Ship_Explosion_5000_8.h"
#include "_Resources/WAVE_Tik_Tak_1_10000_8.h"
#include "_Resources/WAVE_Alien_Sound_1_5000_8.h"
#include "_Resources/WAVE_Alien_Sound_2_5000_8.h"
#include "_Resources/WAVE_Mother_Ship_Sound_5000_8.h"
#include "_Resources/WAVE_Game_5000_8.h"
#include "_Resources/WAVE_Over_5000_8.h"
#include "_Resources/WAVE_cancel_5000_8.h"
#include "_Resources/WAVE_ok_5000_8.h"
#include "_Resources/WAVE_Resetting_5000_8.h"
#include "_Resources/WAVE_Tead_Aliens_2_5000_8.h"
/*
	+-------------------------------------------------------+
	| [English  ] CONSTANTS DEFINITIONS	OF TEAD ALIENS		|
	| [Portugues] DEFINICAO DE CONSTANTES DO TEAD ALIENS	|
	+-------------------------------------------------------+
*/

	#define SPRINTF_BUFFER_SIZE	50												//buffer used by sprintf function

	#define WAVE_CHANNEL_TANK_MOVING (WaveChannel::CHANNEL_1)					//[English  ] Wave Channel used to make Tank Movement sound
																				//[Portugues] Canal de Wave usado para fazer som do movimento do tanque
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_CANNON_FIRE (WaveChannel::CHANNEL_2)					//[English  ] Wave Channel Used to Make Cannon Fire sound
																				//[Portugues] Canal de Wave usado para fazer som do canhao atirando
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_SHIP_EXPLOSION (WaveChannel::CHANNEL_3)				//[English  ] Wave Channel Used to Make Explosion sound
																				//[Portugues] Canal de Wave usado para fazer som das explosoes
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_ALIEN_SOUND_1 (WaveChannel::CHANNEL_4)					//[English  ] Wave Channel Used to Make Aliens Move Sound #1
																				//[Portugues] Canal de Wave usado para fazer som do movimento dos aliens #1
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_ALIEN_SOUND_2 (WaveChannel::CHANNEL_4)					//[English  ] Wave Channel Used to Make Aliens Move Sound #2
																				//[Portugues] Canal de Wave usado para fazer som do movimento dos aliens #2
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_MOTHER_SHIP (WaveChannel::CHANNEL_5)					//[English  ] Wave Channel Used to Make Mother Ship sound
																				//[Portugues] Canal de Wave usado para fazer som da Nave Mae
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_TIK_TAK (WaveChannel::CHANNEL_6)						//[English  ] Wave Channel Used to Make Clock TickTack sound
																				//[Portugues] Canal de Wave usado para fazer o som de TickTaque to Relogio
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_GAME (WaveChannel::CHANNEL_7)							//[English  ] Wave Channel Used to Speech "Game" 
																				//[Portugues] Canal de som usado para falar "Game"
																				//--------------------------------------------------------------
	#define WAVE_CHANNEL_OVER (WaveChannel::CHANNEL_7)							//[English  ] Wave Channel Used to Speech "Over"
																				//[Portugues] Canal de som usado para falar "Over"

	/*
	    +-------------------------------------------------------+
		| [English  ] All Timers in Milliseconds				|
		| [Portugues] Todos os Tempos em milesegundos			|
		+-------------------------------------------------------+
	*/

	/*
		+----------------------------------------------------------
		|[English  ] LIVES
		|[Portugues] VIDAS
		+----------------------------------------------------------
	*/
	#define LIVES_ROW						15									//[English  ] Lives Row Position on Screen
																				//[Portugues] Posicao na tela das vidas
																				//--------------------------------------------------------------
	#define LIVES_FLASH_ON					450									//[English  ] Lives Time To Show
																				//[Portugues] Tempo de Mostrar as Vidas
																				//--------------------------------------------------------------
	#define LIVES_FLASH_OFF					500									//[English  ] Lives Time To not Show
																				//[Portugues] Tempo para não Mostrar as Vidas 
																				//--------------------------------------------------------------
	#define LEVEL_SHOW_TIME					2000								//[English  ] Time To Show Level
																				//[Portugues] Tempo para mostrar o Nivel do Jogo
																				//--------------------------------------------------------------
	#define TEAD_ALIENS_VERSION				215									//[English  ] TEAD Aliens Version Number
																				//[Portugues] Numero da versão do TEAD Aliens
	/*
		+----------------------------------------------------------
		|[English  ] SHIPS
		|[Portugues] NAVES
		+----------------------------------------------------------
	*/

	//--------------------------------------------------------------
	//[English  ] Max Number of Ships Rows on Screen
	//[Portugues] Numero Maximo de Linhas de Naves na tela						
	//--------------------------------------------------------------
	#define SHIPS_MAX_ROWS					5
	//--------------------------------------------------------------
	//[English  ] Max Number of Ships Columns on Screen
	//[Portugues] Numero Maximo de Columnas de Naves na tela
	//--------------------------------------------------------------
	#define SHIPS_MAX_COLS					10
	//--------------------------------------------------------------
	//[English  ] Max Size of Matrix of Ships
	//[Portugues] Tamanho Maximo da Matriz de Naves
	//--------------------------------------------------------------
	#define SHIPS_MAX						(SHIPS_MAX_ROWS*SHIPS_MAX_COLS)
	//--------------------------------------------------------------
	//[English  ] Define if Ships That not Change Shape
	//[Portugues] Define que as Naves não mudarao de forma
	//--------------------------------------------------------------
	#define SHIPS_MOVE_TYPE_FIXED			1
	//--------------------------------------------------------------
	//[English  ] Define if Ships That Change Shape
	//[Portugues] Define que as Naves mudarao de forma
	//--------------------------------------------------------------
	#define SHIPS_MOVE_TYPE_MOVING			2
	//--------------------------------------------------------------
	//[English  ] Define Max Rows and Columns for Ship Size #1
	//[Portugues] Define Numero Maximo de Linhas e Colunas para a Nave de tamanho #1
	//--------------------------------------------------------------
	#define SHIPS_1_MAX_ROWS				4
	#define SHIPS_1_MAX_COLS				9
	//--------------------------------------------------------------
	//[English  ] Define Max Rows and Columns for Ship Size #2
	//[Portugues] Define Numero Maximo de Linhas e Colunas para a Nave de tamanho #2
	//--------------------------------------------------------------
	#define SHIPS_2_MAX_ROWS				3
	#define SHIPS_2_MAX_COLS				7
	//--------------------------------------------------------------
	//[English  ] Define Max Rows and Columns for Ship Size #3
	//[Portugues] Define Numero Maximo de Linhas e Colunas para a Nave de tamanho #3
	//--------------------------------------------------------------
	#define SHIPS_3_MAX_ROWS				3
	#define SHIPS_3_MAX_COLS				5
	//--------------------------------------------------------------
	//[English  ] Define Explosion Size in Pixels
	//[Portugues] Define Tamanho da Explosao em Pixels
	//--------------------------------------------------------------
	#define SHIP_EXPLOSION_SIZE				2
	//--------------------------------------------------------------
	//[English  ] Define Max of Ships Rows
	//[Portugues] Define Tamanho Maximo de Linhas de Naves
	//--------------------------------------------------------------
	#define SHIP_MAX_ROW					15

	/*
		+----------------------------------------------------------
		|[English  ] BARRIES
		|[Portugues] BARREIRAS
		+----------------------------------------------------------
	*/
	#define BARRIES_MAX_COLS				15
	#define BARRIES_MAX_ROWS				2
	#define BARRIER_MAX_DOTS				BARRIES_MAX_COLS*BARRIES_MAX_ROWS
	#define BARRIES_START_ROW				12
	/*
		+----------------------------------------------------------
		|[English  ] MAX SHIPS THAT ARE IN FRONT
		|[Portugues] MAXIMO DE NAVES QUE ESTAO NA FRENTE
		+----------------------------------------------------------
	*/
	#define FRONT_SHIPS_MAX					9
	/*
		+----------------------------------------------------------
		|[English  ] SCREEN
		|[Portugues] TELA
		+----------------------------------------------------------
	*/
	#define SCREEN_MIN_X					0
	#define SCREEN_MIN_Y					0
	#define SCREEN_MAX_X					23
	#define SCREEN_MAX_Y					15
	/*
		+----------------------------------------------------------
		|[English  ] SPEEDS
		|[Portugues] VELOCIDADES
		+----------------------------------------------------------
	*/
	#define SPEED_CANNON					100
	#define SPEED_SHOT_FROM_CANNON_INITIAL	70
	#define SPEED_SHOT_FROM_CANNON_FINAL	30
	#define SPEED_SHIP_INITIAL				400
	#define SPEED_SHIP_FINAL				100
	#define SPEED_SHIP_2_INITIAL			90 
	#define SPEED_SHIP_2_FINAL				60 
	#define SPEED_SHIP_1_INITIAL			60
	#define SPEED_SHIP_1_FINAL				30
	#define SPEED_EXPLOSION					25
	#define SPEED_END_GAME_SCROLL			70
	#define SPEED_SHOT_FROM_SHIP_INITIAL	200
	#define SPEED_SHOT_FROM_SHIP_FINAL		80
	#define SPEED_TIME_TO_SHOT_FROM_SHIP	800
	#define SPEED_TEAD_ALIENS_TEXT			10
	//#define SPEED_SOUND_ON_OR_OFF			50
	#define SPEED_MOTHER_SHIP				80
	#define SPEED_SHIP_CHANGE				500
	/*
		+----------------------------------------------------------
		|[English  ] CANNON
		|[Portugues] CANHAO
		+----------------------------------------------------------
	*/
	#define CANNON_EXPLOSION_SIZE			7
	#define CANNON_SHOT_START_ROW			14
	#define CANNON_START_ROW				15
	#define CANNON_START_COL				12
	/*
		+----------------------------------------------------------
		|[English  ] SCORES
		|[Portugues] PONTUACAO
		+----------------------------------------------------------
	*/
	#define SCORES_MAX						5
	#define SCORES_SHOW_TIME				1000
	#define SCORES_SCROLL_TIME				100
	#define SCORES_FLASH_ON					250
	#define SCORES_FLASH_OFF				150
	#define SCORES_TIME_TO_EXIT				10000
	/*
		+----------------------------------------------------------
		|[English  ] TIME
		|[Portugues] TEMPO
		+----------------------------------------------------------
	*/
	#define TIME_TO_MOTHER_SHIP_APPEAR		8000
	#define TIME_TO_SHOW_DEMO				40000
/*
	+-------------------------------------------------------+
	| [English  ] CONSTANTS DEFINITIONS	OF COBRA GAME		|
	| [Portugues] DEFINICAO DE CONSTANTES DO JOGO COBRA		|
	+-------------------------------------------------------+
*/
	#define COBRA_MAX_POINTS	128
/*
	+-------------------------------------------------------------------------
	|[English  ] TYPEDEF STRUCTS
	|[Portugues] ESTRUTURAS TYPEDEF "DEFINICAO DE TIPOS"
	+-------------------------------------------------------------------------
*/
	
	//-------------------------------------------------------------------------
	// [English  ] SCORES STRUCTUCTURES TO HOLD NAME AND VALUE
	// [Portugues] ESTRUTURA DE PONTUACAO QUE GUARDA NOME E VALOR
	//-------------------------------------------------------------------------
	typedef struct
	{
		char		name[3];	//[Portugues] NOME
		uint16_t	value;		//[Portugues] VALOR
	}struct_Scores;
	//-------------------------------------------------------------------------
	//[English  ] SHIPS DIRECTION
	//[Portugues] DIRECAO DAS NAVES
	//-------------------------------------------------------------------------
	typedef enum class ShipsDirection:uint8_t
	{
		RIGHT,		//[Portugues] DIREITA
		LEFT		//[Portugues] ESQUERDA
	}ShipsDirection;
	//-------------------------------------------------------------------------
	//[English  ] SHAPE OF SHIPS
	//[Portugues] FORMA DAS NAVES
	//-------------------------------------------------------------------------
	typedef enum class ShipShape:uint8_t
	{
		M_SHAPE,	//[Portugues] FORMA M
		H_SHAPE,	//[Portugues] FORMA H
		A_SHAPE,	//[Portugues] FORMA A
	}ShipShape;
	//-------------------------------------------------------------------------
	//[English  ] COBRA DIRECTIONS
	//[Portugues] COBRA DIREÇOES 
	//-------------------------------------------------------------------------
	typedef enum class Dir:uint8_t	
	{
		UP,		//[Portugues] CIMA
		DOWN,	//[Portugues] BAIXO
		LEFT,	//[Portugues] ESQUERDA
		RIGHT	//[Portugues] DIREITA
	}Dir;
	//-------------------------------------------------------------------------
	//[English  ] SCORES STORED IN EEPROM
	//[Portugues] PONTUACAO ARMAZENADA NA EEPROM
	//-------------------------------------------------------------------------
	struct_Scores e_Scores[] EEMEM=
	{
		{"A ",100},{"B ",80},{"C ",60},{"D ",40},{"E ",20},{"  ",0}
	};
	//-------------------------------------------------------------------------
	//CLASSES
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	//[English  ] Class With Time Functions 
	//[Portugues] Classe com funçoes de Tempo
	//-------------------------------------------------------------------------
	class_Timer		timer;				
	//-------------------------------------------------------------------------
	//[English  ] Class With LED Matrix Screen Display Functions
	//[Portugues] Classe com Funcoes para a Tela de Matrix de LEDs
	//-------------------------------------------------------------------------
	class_LED		led(RefreshMode::MANUAL);
	//-------------------------------------------------------------------------
	//[English  ] Class With Keyboard Functions
	//[Portugues] Classe com Funcoes do Teclado
	//-------------------------------------------------------------------------
	class_KBD		kbd;
	//-------------------------------------------------------------------------
	//[English  ] Class With Wave Generator and Tone Generator Functions
	//[Portugues] Classe com Funcoes para Geracao de Wave e Tons
	//-------------------------------------------------------------------------
	class_Wave		wave;
	//-------------------------------------------------------------------------
	//[English  ] Class With Real Time Clock Functions
	//[Portugues] Classe com Funcoes para o Relogio de tempo real
	//-------------------------------------------------------------------------
	class_RTC		rtc;
	//-------------------------------------------------------------------------
	//[English  ] Class With Analog to Digital Conversion Function
	//[Portugues] Classe com funçoes para acesso ao conversor analogico digital
	//-------------------------------------------------------------------------
	class_ADC		adc;


/*
	+-------------------------------------------------------------------------
	|[English  ] TEAD ALIENS STRUCT THAT HOLD ALL VARIABLES USED
	|[Portugues] TEAD ALIENS ESTRUTURA QUE MANTEM TODAS AS VARIAVES USADA
	+-------------------------------------------------------------------------	
*/
	struct  
	{
		//-------------------------------------------------------------------------
		// [English  ] SHIPS STRUCT
		// [Portugues] ESTRUTURA DAS NAVES
		//-------------------------------------------------------------------------	
		struct structShips
		{
			ShipShape		s;					//[English  ] Ship Shap			[Portugues] Forma do Ship
			Point<int8_t>	p;					//[English  ] Ship Coordinate	[Portugues] Coordenada da Nave
			int8_t			w;					//[English  ] Ship width		[Portugues] Largura da Nave
			int8_t			h;					//[English  ] Ship height		[Portugues] Altura da Nave
			bool			visible;			//[English  ] Ship Visibility	[Portugues] Visibilidade da Nave
			uint8_t			*shipStyleOn;		//[English  ] Ship Style ON		[Portugues] Estilo da Nave quando ligada
			uint8_t			*shipStyleOFF;		//[English  ] Ship Style OFF	[Portugues] Estilo da Nave quando desligada
		}spaceShips[SHIPS_MAX];					//[English  ] Array of Ships	[Portugues] Matriz de Naves
		//-------------------------------------------------------------------------
		// [English  ] BARRIES STRUCT
		// [Portugues] ESTRUTURA DAS BARREIRAS
		//-------------------------------------------------------------------------	
		struct structBarries
		{
			Point<int8_t> p;					//[English  ] Ship Coordinate	[Portugues] Coordenada da Barreira
			bool visible;						//[English  ] Ship Visibility	[Portugues] Visibilidade da Barreira
		}barrier[BARRIER_MAX_DOTS];				//[English  ] Array of Barries	[Portugues] Matriz de Pontos da Barreira
												//			  Dots
		//-------------------------------------------------------------------------
		// [English  ] FRONT SHIPS STRUCT
		// [Portugues] ESTRUTURA DOS SHIPS FRONTAIS
		//-------------------------------------------------------------------------
		struct structFrontShip
		{
			int8_t	count;						//[English  ] Front Ships Count		[Portugues] Quantidade de Naves na frente
			struct
			{
				Point<int8_t> p;				//[English  ] Front Ship Coordinates[Portugues] Coordenada das Naves da Frente
			}Coords[FRONT_SHIPS_MAX];			//[English  ] Array of Front Ships  [Portugues] Matriz das Naves da Frente
		}frontShips;
		//-------------------------------------------------------------------------
		// [English  ] TEAD ALIENS VARIABLES
		// [Portugues] VARIAVEIS DO TEAD ALIENS
		//-------------------------------------------------------------------------
		uint32_t		tCannonSpeed;
		uint32_t		tShotSpeed;
		uint32_t		tShipSpeed;
		uint32_t		tShotSpeedShip;
		uint32_t		tTimeToShotFromShip;
		uint32_t		tMotherShipAppear;
		uint32_t		tMotherShipSpeed;
		uint32_t	    tShipChange;
		int16_t			shipSpeedVar;
		char			bf[SPRINTF_BUFFER_SIZE];
		char			bfVersion[SPRINTF_BUFFER_SIZE];
		int				TEAD_Aliens_text_size;
		char			TEAD_Aliens_Text[16];//="TEAD Aliens Game";
		bool			bTimeInit=true;
		int				score;
		uint8_t			level;
		uint8_t			lives;
		Point<int8_t>	cannon;
		bool			bShotCannon;
		bool			bSoundON=true;
		bool			bMotherShipApper=false;
		bool			bShipStyle=true;
		bool			bInDemo=false;
		Point<int8_t>	mother;
		Point<int8_t>	shotCannon;
		ShipsDirection	shipDir;
		bool			bShotShip;
		Point<int8_t>	shotShip;
		struct_Scores	scores[SCORES_MAX+1];
		//------------------------------------------------------------------------------------------
		//ships_move_type must be FIXED or MOVING
		//------------------------------------------------------------------------------------------
		uint8_t			ships_move_type=SHIPS_MOVE_TYPE_FIXED;
		//------------------------------------------------------------------------------------------
		//size must be 1 to 3
		//size 1 ship is only a dot
		//size 2 ship is square of 2x2 dot
		//size 3 ship is bmp defined
		//------------------------------------------------------------------------------------------
		uint8_t			ships_size=3;						
		//------------------------------------------------------------------------------------------
		//change ships_cols and ships_rows according ships_size
		//if size is 1 then ships_cols=SHIPS_1_MAX_COLS and ships_rows=SHIPS_1_MAX_SIZE_ROWS
		//if size is 2 then ships_cols=SHIPS_2_MAX_COLS and ships_rows=SHIPS_1_MAX_SIZE_ROWS
		//if size is 3 then ships_cols=SHIPS_3_MAX_COLS and ships_rows=SHIPS_1_MAX_SIZE_ROWS
		//------------------------------------------------------------------------------------------
		uint8_t			ships_cols=SHIPS_3_MAX_COLS;
		uint8_t			ships_rows=SHIPS_3_MAX_ROWS;
		uint8_t			ships_max=ships_cols*ships_rows;
	}_tead;
	//-------------------------------------------------------------------------
	//[English  ] COBRA STRUCT THAT HOLD ALL VARIABLES USED
	//[Portugues] COBRA ESTRUTURA QUE MANTEM TODAS AS VARIAVES USADA
	//-------------------------------------------------------------------------
	struct
	{
		//-------------------------------------------------------------------------
		// [English  ] COBRA Points Coordinates
		// [Portugues] COBRA Coordenadas dos Pontos
		//-------------------------------------------------------------------------
		struct  
		{
			struct  
			{
				int8_t x;
				int8_t y;
			}coords[COBRA_MAX_POINTS];
			int	Count=0;						//points count
		}points;
	}_cobra;
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Initialize TEAD Aliens Game								|
//	| @brief Name		: TEAD_initializeGame						                |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Inicializa TEAD Aliens Game								|
//	| @brief Nome		: TEAD_initializeGame						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_initializeGame(bool initScore,bool initLevel,bool initLives)
{
	int			majorV,minorV;
	CharFont	font;	
	static		bool bOnlyOnTime=true;
	
	//save Font
	font=led.getFont();
	
	//initialize Version String
	if (bOnlyOnTime)
	{
		bOnlyOnTime=false;
		majorV=TEAD_ALIENS_VERSION/100;
		minorV=TEAD_ALIENS_VERSION-majorV*100;
		strcpy(_tead.TEAD_Aliens_Text,"TEAD Aliens Game(just say TED!)");
		sprintf(_tead.bfVersion,"%s Version %1d.%02d",_tead.TEAD_Aliens_Text,majorV,minorV);
		_tead.TEAD_Aliens_text_size=led.getTextWidth(_tead.bfVersion);		
	}

	led.setFont(CharFont::FONT_3X5);
	wave.SetVolume(50);
	wave.Prepare((WAVE)Wave_tank_moving_2,WAVE_CHANNEL_TANK_MOVING);
	wave.Prepare((WAVE)Wave_Canno_Fire,WAVE_CHANNEL_CANNON_FIRE);
	wave.Prepare((WAVE)Wave_Ship_Explosion,WAVE_CHANNEL_SHIP_EXPLOSION);
	wave.Prepare((WAVE)Wave_Alien_Sound_1,WAVE_CHANNEL_ALIEN_SOUND_1);
	wave.Prepare((WAVE)Wave_Mother_Ship_Sound,WAVE_CHANNEL_MOTHER_SHIP);
	wave.Prepare((WAVE)Wave_Tik_Tak_1,WAVE_CHANNEL_TIK_TAK);
	wave.Prepare((WAVE)Wave_Game,WAVE_CHANNEL_GAME);
	_tead.mother={.x=-8,.y=0};
	_tead.bMotherShipApper=false;
	_tead.cannon={.x=CANNON_START_COL,.y=CANNON_START_ROW};
	_tead.bShotCannon=false;
	_tead.shotCannon={.x=_tead.cannon.x,.y=CANNON_SHOT_START_ROW};
	_tead.shipDir=ShipsDirection::LEFT;
	_tead.bShotShip=false;
	//Init Score?
	if (initScore)
	{
		//Below code must be unremarked to show score value
// 		if (_tead.bInDemo==false)
// 		{
// 			led.cls();
// 			sprintf(_tead.bf,"%d",_tead.score);
// 			led.putS(_tead.bf);
// 			led.refresh();
// 			timer.delayMilliseconds(2000);
// 			TEAD_insertNewScore(_tead.score);
// 		}

		//yes,insert new score
// 		if (_tead.score>0 && _tead.bInDemo==false)
// 		{
// 			TEAD_insertNewScore(_tead.score);	
// 		}
		//clear score
		_tead.score=0;
	}
	//Init Level?
	if (initLevel)
	{
		//yes, set level to 1
		_tead.level=1;
	}
	//Init Lives?
	if (initLives)
	{
		//yes, set lives to 3
		_tead.lives=3;
	}
	//Initialize ship speed
	//max speed occur when level=50
	_tead.shipSpeedVar=SPEED_SHIP_INITIAL-(SPEED_SHIP_INITIAL-SPEED_SHIP_FINAL)*(_tead.level-1)/50;
	//saturate to max speed if level > 50
	if (_tead.level>50) _tead.shipSpeedVar=SPEED_SHIP_FINAL;
	TEAD_initSpaceShips();
	TEAD_initBarriers();
	TEAD_updateScreen();
	timer.setElapsed(_tead.tCannonSpeed);
	timer.setElapsed(_tead.tShotSpeed);
	timer.setElapsed(_tead.tShipSpeed);
	timer.setElapsed(_tead.tShotSpeedShip);
	timer.setElapsed(_tead.tTimeToShotFromShip);
	timer.setElapsed(_tead.tMotherShipAppear);
	timer.setElapsed(_tead.tShipChange);
	//restore font
	
	led.setFont(font);
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Play Cancel Sound											|
//	| @brief Name		: playCancel												|
//	| @parm [in]		: None														|
//	| @parm [out]		: None														|
//	| @remarks			: Prepares and plays the cancel sound on channel 8.			|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Reproduzir Som de Cancelamento							|
//	| @brief Nome		: playCancel												|
//	| @parm Entrada [in]: Nenhum													|
//	| @parm Saida [out] : Nenhum													|
//	| @remarks comentario :	Prepara e toca o som de cancelamento no canal 8.		|
//	+-------------------------------------------------------------------------------+
static void playCancel()
{
	wave.Prepare((WAVE)Wave_cancel,WaveChannel::CHANNEL_8);
	wave.Play(WaveChannel::CHANNEL_8);
}

//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Play OK Sound												|
//	| @brief Name		: playOk													|
//	| @parm [in]		: None														|
//	| @parm [out]		: None														|
//	| @remarks			: Prepares and plays the OK sound on channel 8.				|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Reproduzir Som de Confirmação								|
//	| @brief Nome		: playOk													|
//	| @parm Entrada [in]: Nenhum													|
//	| @parm Saida [out] : Nenhum													|
//	| @remarks comentario :	Prepara e toca o som de confirmação no canal 8.			|
//	+-------------------------------------------------------------------------------+
static void playOk()
{
	wave.Prepare((WAVE)Wave_ok,WaveChannel::CHANNEL_8);
	wave.Play(WaveChannel::CHANNEL_8);
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Play Resetting Sound										|
//	| @brief Name		: playResetting												|
//	| @parm [in]		: None														|
//	| @parm [out]		: None														|
//	| @remarks			: Prepares and plays the resetting sound on channel 8.		|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Reproduzir Som de Reinicialização							|
//	| @brief Nome		: playResetting												|
//	| @parm Entrada [in]: Nenhum													|
//	| @parm Saida [out] : Nenhum													|
//	| @remarks comentario :	Prepara e toca o som de reinicialização no canal 8.		|
//	+-------------------------------------------------------------------------------+
static void playResetting()
{
	wave.Prepare((WAVE)Wave_Resetting,WaveChannel::CHANNEL_8);
	wave.Play(WaveChannel::CHANNEL_8);
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Play TEAD Aliens Game Sound								|
//	| @brief Name		: playTEADAliensGame										|
//	| @parm [in]		: None														|
//	| @parm [out]		: None														|
//	| @remarks			: Prepares and plays the TEAD Aliens game sound on channel 8.|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Reproduzir Som do Jogo TEAD Aliens						|
//	| @brief Nome		: playTEADAliensGame										|
//	| @parm Entrada [in]: Nenhum													|
//	| @parm Saida [out] : Nenhum													|
//	| @remarks comentario :	Prepara e toca o som do jogo TEAD Aliens no canal 8.	|
//	+-------------------------------------------------------------------------------+
static void playTEADAliansGame()
{
	wave.Prepare((WAVE)Wave_Tead_Aliens_2,WaveChannel::CHANNEL_8);
	wave.Play(WaveChannel::CHANNEL_8);
}

//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Delay and Key												|
//	| @brief Name		: TEAD_delayKey												|
//	| @parm [in]		: Delay in milliseconds										|
//	| @parm [out]		: 															|
//	| @remarks			: Make a Delay but return immediately if any key pressed	|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Retardos e Teclas											|
//	| @brief Nome		: TEAD_delayKey								                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	Faz um Retardo de tempo, mas retorna imediatamente se	|
//	|						alguma	tecla for pressionada							|
//	+-------------------------------------------------------------------------------+
bool TEAD_delayKey(uint16_t delayMilliseconds)
{
	uint32_t	t;
	
	//mark new timer
	timer.setElapsed(t);
	//main loop until timer greater delay
	do 
	{
		//exit if any key pressed
		if (kbd.getKbdState()!=Kbd::NONE)
		{
			//return true, i.e. keyboard pressed
			return true;
		}
	} while (timer.getElapsed(t)<delayMilliseconds);
	//return false, keyboard not pressed turing delay
	return false;
}

//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Initialize TEAD Aliens Barriers							|
//	| @brief Name		: initBarries								                |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Initialize barriers into your respective positions		|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Inicializa as barreiras TEAD Aliens 						|
//	| @brief Nome		: TEAD_initBarriers							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	Inicializa as Barreiras nas suas respectivas posicoes	|
//	+-------------------------------------------------------------------------------+
void TEAD_initBarriers()
{
	int8_t d;
	
	//clear barrier dots
	memset(&_tead.barrier,0,sizeof(_tead.barrier));
		
	for(uint8_t j=0;j<BARRIES_MAX_ROWS;j++)
	{
		d=j*BARRIES_MAX_COLS;
		for(uint8_t i=0;i<3;i++)
		{
			_tead.barrier[d+i].p={.x=(int8_t)(i+1),.y=(int8_t)(BARRIES_START_ROW+j)};
			_tead.barrier[d+i].visible=true;
			
			_tead.barrier[d+i+3].p={.x=(int8_t)(i+6),.y=(int8_t)(BARRIES_START_ROW+j)};
			_tead.barrier[d+i+3].visible=true;
			
			_tead.barrier[d+i+6].p={.x=(int8_t)(i+11),.y=(int8_t)(BARRIES_START_ROW+j)};
			_tead.barrier[d+i+6].visible=true;
			
			_tead.barrier[d+i+9].p={.x=(int8_t)(i+16),.y=(int8_t)(BARRIES_START_ROW+j)};
			_tead.barrier[d+i+9].visible=true;
			
			_tead.barrier[d+i+12].p={.x=(int8_t)(i+21),.y=(int8_t)(BARRIES_START_ROW+j)};
			_tead.barrier[d+i+12].visible=true;
		}		
	}
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Initialize TEAD Aliens Ships								|
//	| @brief Name		: TEAD_initSpaceShips						                |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Initialize Ships into your respective initial positions	|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Inicializa TEAD Aliens Ships		 						|
//	| @brief Nome		: TEAD_initSpaceShips						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	Inicializa as naves nas suas respectivas posicoes		|
//	|						iniciais												|
//	+-------------------------------------------------------------------------------+
void TEAD_initSpaceShips()
{
	int8_t h,w,index;
	
	//First clear space ships
	memset(_tead.spaceShips,0,sizeof(_tead.spaceShips));
	//SHIPS MAX ROW MUST BE EQUAL J CASES
	for(uint8_t j=0;j<_tead.ships_rows;j++)
	{
		for(uint8_t i=0;i<_tead.ships_cols;i++)
		{
			index=i+j*_tead.ships_cols;
			_tead.spaceShips[index].visible=true;
			//set ships parameters according dot size wide
			switch(_tead.ships_size)
			{
				case 1:
					//set ships of 2 dot wide
					w=led.getBMPWidth(BMP_SHIP_DOT_1);
					h=led.getBMPHeight(BMP_SHIP_DOT_1);
					_tead.spaceShips[index].s=ShipShape::A_SHAPE;
					_tead.spaceShips[index].w=w;
					_tead.spaceShips[index].h=h;
					_tead.spaceShips[index].p={.x=(int8_t)(i*(w+1)),.y=(int8_t)(j*(h+1))};
					_tead.spaceShips[index].shipStyleOn=(uint8_t*)BMP_SHIP_DOT_1;
					_tead.spaceShips[index].shipStyleOFF=(uint8_t*)BMP_SHIP_DOT_1;
				break;
				case 2:
					//set ships of 2 dot wide
					_tead.spaceShips[index].s=ShipShape::H_SHAPE;
					w=led.getBMPWidth(BMP_SHIP_DOT_2_1);
					h=led.getBMPHeight(BMP_SHIP_DOT_2_1);
					_tead.spaceShips[index].w=w;
					_tead.spaceShips[index].h=h;
					_tead.spaceShips[index].p={.x=(int8_t)(i*(w+1)),.y=(int8_t)(j*(h+1))};
					_tead.spaceShips[index].shipStyleOn=(_tead.ships_move_type==SHIPS_MOVE_TYPE_FIXED)?(uint8_t*)BMP_SHIP_DOT_2_3:(uint8_t*)BMP_SHIP_DOT_2_1;
					_tead.spaceShips[index].shipStyleOFF=(_tead.ships_move_type==SHIPS_MOVE_TYPE_FIXED)?(uint8_t*)BMP_SHIP_DOT_2_3:(uint8_t*)BMP_SHIP_DOT_2_2;
				break;
				case 3:
					//set ship of more one dot
					w=led.getBMPWidth(BMP_Ship_1_1);
					h=led.getBMPHeight(BMP_Ship_1_1);
					_tead.spaceShips[index].w=w;
					_tead.spaceShips[index].h=h;
					_tead.spaceShips[index].p={.x=(int8_t)(i*(w+1)),.y=(int8_t)(j*(h))};
					//set ships on or off according row
					switch(j)
					{
						case 0:
							_tead.spaceShips[index].shipStyleOn=(uint8_t *)BMP_Ship_1_1;
							_tead.spaceShips[index].shipStyleOFF=(_tead.ships_move_type==SHIPS_MOVE_TYPE_FIXED)?(uint8_t*)BMP_Ship_1_1:(uint8_t*)BMP_Ship_1_2;
							_tead.spaceShips[index].s=ShipShape::M_SHAPE;
						break;
						case 1:
							_tead.spaceShips[index].shipStyleOn=(uint8_t *)BMP_Ship_2_1;
							_tead.spaceShips[index].shipStyleOFF=(_tead.ships_move_type==SHIPS_MOVE_TYPE_FIXED)?(uint8_t*)BMP_Ship_2_1:(uint8_t*)BMP_Ship_2_2;
							_tead.spaceShips[index].s=ShipShape::H_SHAPE;
						break;
						case 2:
							_tead.spaceShips[index].shipStyleOn=(uint8_t *)BMP_Ship_3_1;
							_tead.spaceShips[index].shipStyleOFF=(_tead.ships_move_type==SHIPS_MOVE_TYPE_FIXED)?(uint8_t*)BMP_Ship_3_1:(uint8_t*)BMP_Ship_3_2;
							_tead.spaceShips[index].s=ShipShape::A_SHAPE;
						break;
					}				
				break;
			}
		}
	}
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Draw TEAD Aliens Ships									|
//	| @brief Name		: TEAD_drawSpaceShips						                |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Desenha as Naves to TEAD Aliens	 						|
//	| @brief Nome		: TEAD_drawSpacShips							            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawSpaceShips(bool shipOnStyle)
{
	//-------------------------------------------------------------------------
	//[English  ] For All Ships
	//[Portugues] Para Todas as Naves
	//-------------------------------------------------------------------------
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		// [English  ] Only Ships with visible attribute is draw
		// [Portugues] Apenas as Naves com atributo de visivel sera desenhada
		if (_tead.spaceShips[i].visible)
		{
			// [English  ] Draw a Ships
			// [Portugues] Desenha a Nave
			led.bmp(_tead.spaceShips[i].p.x,_tead.spaceShips[i].p.y,
					_tead.bShipStyle?_tead.spaceShips[i].shipStyleOn:_tead.spaceShips[i].shipStyleOFF);	
		}
	}
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Draw Mother Ship											|
//	| @brief Name		: TEAD_drawMotherShip										|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Desenha a Nave Mae					 					|
//	| @brief Nome		: TEAD_drawMotherShip						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawMotherShip()
{
	// [English  ] Draw Mother Ship
	// [Portugues] Desenha a Nave Mae
	led.bmp(_tead.mother.x,_tead.mother.y,BMP_Mother_Ship);	
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Draw Cannon												|
//	| @brief Name		: drawCannon												|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Desenha a o Canhao					 					|
//	| @brief Nome		: TEAD_drawCannon							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawCannon(Color color)
{
	//draw cannon
	//
	//     #
	//    ###
	
	led.setPixel(_tead.cannon.x,_tead.cannon.y-1,color);
	led.setPixel(_tead.cannon.x-1,_tead.cannon.y,color);
	led.setPixel(_tead.cannon.x,_tead.cannon.y,color);
	led.setPixel(_tead.cannon.x+1,_tead.cannon.y,color);	
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Draw Remainder Livesof TEAD Aliens						|
//	| @brief Name		: TEAD_drawLives											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Desenha as Vidas Restantes do TEAD Aliens					|
//	| @brief Nome		: TEAD_drawLives								            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawLives()
{
	static uint32_t tFlash;
	
	if (timer.getElapsed(tFlash)>LIVES_FLASH_ON)
	{
		led.line(24-_tead.lives,LIVES_ROW,23,LIVES_ROW);	
	}
	if (timer.getElapsed(tFlash)>LIVES_FLASH_OFF)
	{
		timer.setElapsed(tFlash);
		led.line(24-_tead.lives,LIVES_ROW,23,LIVES_ROW,Color::BLACK);	
	}
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Insert a New Score										|
//	| @brief Name		: TEAD_insertNewScore						                |
//	| @parm [in]		: score	:new score value									|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Insere um Novo Score				 						|
//	| @brief Nome		: TEAD_insertNewScore						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
//
//	0 - A - 100
//	1 - B -  80
//	2 - C -  60
//	3 - D -  40
//	4 - E -  20

void	TEAD_insertNewScore(uint16_t scoreValue)
{
	CharFont	font;
	Kbd			key;
	uint32_t	tFlash;
	uint32_t	tExit;
	bool		bFlash=true;
	int8_t		sel=0;
	
	//save font
	font=led.getFont();
	//set new font
	led.setFont(CharFont::FONT_3X5);
	//Get Scores from EEPROM
	SCORES_getFromEEPROM();
	//set flash time
	timer.setElapsed(tFlash);
	//set Time to exit
	timer.setElapsed(tExit);	
	//Search where newScoreValue is inserted
	for(int8_t i=0;i<SCORES_MAX;i++)
	{
		//check if new Score if > old Score
		if (scoreValue>_tead.scores[i].value)
		{
			//yes, insert new value
			//shift values down to insert new value
			for(int8_t j=5;j>i;j--)
			{
				_tead.scores[j]=_tead.scores[j-1];
			}
			//insert new value
			_tead.scores[i].value=scoreValue;
			//save new values into eeprom
			SCORES_saveIntoEEPROM();
			//show curtain
			TEAD_showCurtain();		
			//show message new score
			for(uint8_t j=0;j<5;j++)
			{
				if (_tead.bSoundON)
				{
					wave.Play(WAVE_CHANNEL_MOTHER_SHIP);
				}
				led.cls();
				led.moveTo(6,0);
				led.putSF(PSTR("NEW"));
				led.moveTo(2,8);
				led.putSF(PSTR("SCORE"));
				led.refresh();
				timer.delayMilliseconds(SCORES_FLASH_ON);
				led.cls();
				led.refresh();
				timer.delayMilliseconds(SCORES_FLASH_OFF);
			}
			//edit new score name
			for(;;)
			{
				
				sprintf(_tead.bf,"%2s%4d",_tead.scores[i].name,_tead.scores[i].value);
				led.cls();
				led.putS(_tead.bf);
				led.bmp(3,8,(BMP)BMP_Left_Little);
				led.bmp(7,5,(BMP)BMP_Up_Little);
				led.bmp(7,11,(BMP)BMP_Down_Little);
				led.bmp(11,8,(BMP)BMP_Right_Little);
				led.circle(19,10,2);
				//Get Key States
				key=kbd.getKbdState();				
				//Left?
				if ((uint8_t)key & (uint8_t)Kbd::LEFT)
				{
					//yes, draw Left
					led.bmp(3,8,(BMP)BMP_Left_Big);
					sel=0;
					//set Time to exit
					timer.setElapsed(tExit);
				}
				//Right?
				if ((uint8_t)key & (uint8_t)Kbd::RIGHT)
				{
					//yes, draw Right
					led.bmp(11,8,(BMP)BMP_Right_Big);
					sel=1;
					//set Time to exit
					timer.setElapsed(tExit);
				}
				//Up?
				if ((uint8_t)key & (uint8_t)Kbd::UP)
				{
					//yes, draw Up
					led.bmp(7,5,(BMP)BMP_Up_Big);
					_tead.scores[i].name[sel]++;
					if (_tead.scores[i].name[sel]>'Z')
					{
						_tead.scores[i].name[sel]='Z';	
					}
					//set Time to exit
					timer.setElapsed(tExit);
				}
				//Down?
				if ((uint8_t)key & (uint8_t)Kbd::DOWN)
				{
					//yes, draw Down
					led.bmp(7,11,(BMP)BMP_Down_big);
					_tead.scores[i].name[sel]--;
					if (_tead.scores[i].name[sel]<'A')
					{
						_tead.scores[i].name[sel]='A';
					}
					//set Time to exit
					timer.setElapsed(tExit);
				}
				//Enter ?
				if ((uint8_t)key & (uint8_t)Kbd::ENTER)
				{
					//yes, save new  data into eeprom
					SCORES_saveIntoEEPROM();
					//draw a full circle meaning enter button pressed
					led.setFillMode(true);
					led.circle(19,10,2);
					led.setFillMode(false);
					led.refresh();
					//play a tick sound
					if (_tead.bSoundON)
					{
						wave.Play(WAVE_CHANNEL_TIK_TAK);
					}					
					//wait 500 milliseconds to exit
					timer.delayMilliseconds(500);
					//restore font
					led.setFont(font);
					return;
				}
				//Time to Exit?
				if (timer.getElapsed(tExit)>SCORES_TIME_TO_EXIT)
				{
					//draw a full circle meaning enter button pressed
					led.setFillMode(true);
					led.circle(19,10,2);
					led.setFillMode(false);
					led.refresh();
					//play a tick sound
					if (_tead.bSoundON)
					{
						wave.Play(WAVE_CHANNEL_TIK_TAK);
					}
					//wait 500 milliseconds to exit
					timer.delayMilliseconds(500);
					//restore font
					led.setFont(font);
					return;					
				}
				if (timer.getElapsed(tFlash)>SCORES_FLASH_ON)
				{
					timer.setElapsed(tFlash);
					bFlash=!bFlash;
				}
				if (bFlash)
				{
					switch(sel)
					{
						case 0:led.line(0,6,3,6);break;
						case 1:led.line(4,6,7,6);break;
					}
					
				}
				led.refresh();
				if (!(key==Kbd::NONE))
				{
					if (_tead.bSoundON)
					{
						wave.Play(WAVE_CHANNEL_TIK_TAK);
					}
					timer.delayMilliseconds(250);
				}
			}
			//restore old font
			led.setFont(font);
			return;
		}
	}
	//restore font
	led.setFont(font);
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Update Screen of TEAD Aliens	 							|
//	| @brief Name		: TEAD_updateScreen							                |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Atualiza a tela do TEAD Aliens	 						|
//	| @brief Nome		: TEAD_updateScreen							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_updateScreen()
{
	//CharFont	font;
	
	//font=led.getFont();
	
	led.cls();
	//draw cannon
	TEAD_drawCannon();		
	//draw shot from ships or from cannon
	if (_tead.bShotCannon)
	{
		led.setPixel(_tead.shotCannon.x,_tead.shotCannon.y);
	}
	//take care to correctly below coordinates according ship style changed
	if (_tead.bShotShip)
	{
		led.setPixel(_tead.shotShip.x,_tead.shotShip.y);
	}
	//draw barriers
	TEAD_drawBarriers();
	//draw space ships
	TEAD_drawSpaceShips(true);
	//draw mother ship
	TEAD_drawMotherShip();
	//Draw Lives
	TEAD_drawLives();
	
//	led.setFont(CharFont::FONT_3X5);
//	sprintf(_tead.bf,"%d",_tead.score);
//	led.moveTo(0,0);
//	led.putS(_tead.bf);

	//refresh screen
	led.refresh();
	
	//led.setFont(font);
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Process Cannon Movement 									|
//	| @brief Name		: TEAD_processCannonMovement							    |
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Get Keyboard State end if joystick is positionated on LEFT|
//	|					  or RIGHT the Cannon will move to this direction using		|
//	|					  actual Cannon Speed										|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Processa o Movimento deo Canhao	 						|
//	| @brief Nome		: TEAD_processCannonMovement					            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	Le o Estado do Teclado e se o Joystick estever posicio-	|
//	|						nado para ESQUERDA ou DIREITA o Canhao moventa-ra para	|
//	|						esta direcao usando	a velocidade atual do Canhao.		|
//	+-------------------------------------------------------------------------------+
void TEAD_processCannonMove()
{
	Kbd key;
	static int8_t pCount=0;
	static int8_t pCountComp=2;

	if (timer.getElapsed(_tead.tCannonSpeed)>SPEED_CANNON)
	{
		timer.setElapsed(_tead.tCannonSpeed);
		key=kbd.getKbdState();
		//in demo
		if (_tead.bInDemo)
		{
			pCount++;
			if (pCount>pCountComp)
			{
				pCount=0;
				pCountComp=rand()%7;
				if ((rand()%2)==1) key=Kbd::LEFT; else key=Kbd::RIGHT;
			}
		}
		//cannon move to left?
		if ((uint8_t)key & (uint8_t)Kbd::LEFT)
		{
			_tead.cannon.x--;
			if (_tead.cannon.x<1)
			{
				_tead.cannon.x=1;
			}
			if (!_tead.bShotCannon)
			{
				_tead.shotCannon.x=_tead.cannon.x;
			}
			if (_tead.bSoundON)
				{
				if (wave.Playing(WAVE_CHANNEL_TANK_MOVING)==false)
				{
					wave.Play(WAVE_CHANNEL_TANK_MOVING);
				}
			}
		}
		//cannon move to right
		if ((uint8_t)key & (uint8_t)Kbd::RIGHT)
		{
			_tead.cannon.x++;
			if (_tead.cannon.x>SCREEN_MAX_X-1)
			{
				_tead.cannon.x=SCREEN_MAX_X-1;
			}
			if (!_tead.bShotCannon)
			{
				_tead.shotCannon.x=_tead.cannon.x;
			}
			if (_tead.bSoundON)
			{
				if (wave.Playing(WAVE_CHANNEL_TANK_MOVING)==false)
				{
					wave.Play(WAVE_CHANNEL_TANK_MOVING);
				}
			}
		}
	}
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Get Number of Remainder Ships								|
//	| @brief Name		: TEAD_getShipsAlive										|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Obtem o Numero de Naves Sobrando	 						|
//	| @brief Nome		: TEAD_getShipsAlive							            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
int8_t TEAD_getShipsAlives()
{
	int8_t		count=0;
	CharFont	font;
	bool		fillMode;
	
	//Save actual fillMode
	fillMode=led.getFillMode();
	//save actual font
	font=led.getFont();
	//check how many ships in screen
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible) count++;
	}
	
	//count=0;
	//if number of ships equal zero ?
	if (count==0)
	{
		//yes, than next level
		_tead.level++;
		//Show Curtain
		TEAD_showCurtain();
		//show next level number
		if (_tead.bSoundON)
		{
			wave.Play(WAVE_CHANNEL_MOTHER_SHIP);	
		}
		led.setFont(CharFont::FONT_3X5);
		led.cls();
		led.moveTo(2,2);
		led.putS("LEVEL");
		led.moveTo(9,8);
		sprintf(_tead.bf,"%02d",_tead.level);
		led.putS(_tead.bf);
		led.refresh();
		//wait 2 seconds
		timer.delayMilliseconds(LEVEL_SHOW_TIME);
		//initialize game for next level
		TEAD_initializeGame(false,false,false);
	}
	//restore font
	led.setFont(font);
	//restore fillMode
	led.setFillMode(fillMode);
	//return number of ships
	return count;
}
//	+-[English  ]-------------------------------------------------------------------+
//	| @brief Function	: Show Explosion											|
//	| @brief Name		: TEAD_showExplosion										|
//	| @parm [in]		: x,y			:coordinates of explosion center			|
//	|					  size			:size of explosion							|
//	|					  refreshScreen	:redraw screen if true						|
//	|					  times			:how many times explosion occur				|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-[Portugues]-------------------------------------------------------------------+
//	| @brief Funcao		: Mostra Explosao					 						|
//	| @brief Nome		: TEAD_showExplosion							            |
//	| @parm Entrada [in]: x,y			:coordenadas do centro da explosao			|
//	|					  size			:Tamanho da Explosao						|
//	|					  refreshSCreen :redesenha a tela se verdadeira				|
//	|					  timers		:numero de vezes que a esplosao ocorre		|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_showExplosion(int8_t x,int8_t y,int8_t size,bool refreshScreen,int8_t times)
{
	Color color=Color::RED;
	uint8_t c=1;
	
	for(int8_t j=0;j<times;j++)
	{
		//play explosion
		if (_tead.bSoundON)
		{
			wave.Play(WAVE_CHANNEL_SHIP_EXPLOSION);
		}
		//show explosion
		for(int8_t i=0;i<size;i++)
		{
			if (refreshScreen)
			{
				TEAD_updateScreen();
			}
			else
			{
				led.cls();
			}
			led.line(x-i,y-i,x+i,y+i,color);
			led.line(x+i,y-i,x-i,y+i,color);
			led.line(x,y,x,y-i,color);
			led.line(x,y,x,y+i,color);
			if (_tead.bSoundON)
			{
				wave.setToneGen(340+i*100,50,2);
			}
			c^=1;
			color=(Color)c;
			led.refresh();
			timer.delayMilliseconds(SPEED_EXPLOSION);
		}
		for(int8_t i=(size-1);i>=0;i--)
		{
			if (refreshScreen)
			{
				TEAD_updateScreen();
			}
			else
			{
				led.cls();
			}
			led.line(x-i,y-i,x+i,y+i,color);
			led.line(x+i,y-i,x-i,y+i,color);
			if (_tead.bSoundON)
			{
				wave.setToneGen(340+i*100,50,2);
			}
			c^=1;
			color=(Color)c;			
			led.refresh();
			timer.delayMilliseconds(SPEED_EXPLOSION);
		}		
	}
	
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Process Cannon Fire										|
//	| @brief Name		: TEAD_processCannonFire									|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Fire a Cannon Shot if key Enter pressed					|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Processa o Tiro do Canhao			 						|
//	| @brief Nome		: TEAD_processFireFromCannon					            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Dispara o Projetil do Canhao se a Tecla Enter for pres-	|
//	|						sionada													|
//	+-------------------------------------------------------------------------------+
void TEAD_processFireFromCannon()
{
	Kbd		key;
	uint16_t	shoot_cannon_speed;
	
	//max speed reached at level 50
	shoot_cannon_speed=SPEED_SHOT_FROM_CANNON_INITIAL-(SPEED_SHOT_FROM_CANNON_INITIAL-SPEED_SHOT_FROM_CANNON_FINAL)*(_tead.level-1)/50;
	//if level > 50 set max speed of  shoot
	if (_tead.level>50) shoot_cannon_speed=SPEED_SHOT_FROM_CANNON_FINAL;
	//Time to move cannon shoot
	if (timer.getElapsed(_tead.tShotSpeed)>shoot_cannon_speed)
	{
		//clear shot speed
		timer.setElapsed(_tead.tShotSpeed);
		//firing?
		if (_tead.bShotCannon)
		{
			//move cannon shoot
			_tead.shotCannon.y--;
			//make a 8bit sound if enabled
			if (_tead.shotCannon.y>6)
			{
				if (_tead.bSoundON)
				{
					wave.setToneGen(2000*_tead.shotCannon.y*200,SPEED_SHOT_FROM_CANNON_INITIAL,1);	
				}
			}
			
			//check if cannon shoot hit some think
			if (led.getPixel(_tead.shotCannon.x,_tead.shotCannon.y)==Color::RED ||
				led.getPixel(_tead.shotCannon.x,_tead.shotCannon.y-1)==Color::RED ||
				led.getPixel(_tead.shotCannon.x,_tead.shotCannon.y+1)==Color::RED)
			{
				//yes, check if cannon shoot hit a space ship
				for(uint8_t i=0;i<_tead.ships_max;i++)
				{
					//hit space ship only if it is visible
					if (_tead.spaceShips[i].visible)
					{
						//if (shotCannonX<(spaceShips[i].x+3) && shotCannonX>=spaceShips[i].x && spaceShips[i].y==shotCannonY)
						if (_tead.shotCannon.x<(_tead.spaceShips[i].p.x+_tead.spaceShips[i].w) && _tead.shotCannon.x>=_tead.spaceShips[i].p.x && 
						    _tead.shotCannon.y<(_tead.spaceShips[i].p.y+_tead.spaceShips[i].h) && _tead.shotCannon.y>=_tead.spaceShips[i].p.y)
						{
							//yes, play ship explosion
							if (_tead.bSoundON)
							{
								wave.Play(WAVE_CHANNEL_SHIP_EXPLOSION);
							}
							//TEAD_showExplosion(shotCannonX,shotCannonY,2,true,1);
							TEAD_showExplosion(_tead.spaceShips[i].p.x+1,_tead.spaceShips[i].p.y,2,true,1);//<<==chegar se para tamanho de 1 dot esta ok
							//turn this ship invisible
							_tead.spaceShips[i].visible=false;
							//turn cannon shot off
							_tead.bShotCannon=false;
							//reset cannon shot start position
							_tead.shotCannon.y=CANNON_SHOT_START_ROW;
							//score according type
							switch(_tead.spaceShips[i].s)
							{
								case ShipShape::M_SHAPE:_tead.score+=3;break;
								case ShipShape::H_SHAPE:_tead.score+=2;break;
								case ShipShape::A_SHAPE:_tead.score+=1;break;
							}
							//saturate score
							if (_tead.score>9999) _tead.score=9999;
							//return
							return;
						}
					}
				}
				//find if barrier exploded
				for(uint8_t i=0;i<BARRIER_MAX_DOTS;i++)
				{
					if (_tead.barrier[i].visible)
					{
						if (_tead.barrier[i].p.x==_tead.shotCannon.x	&& _tead.barrier[i].p.y==_tead.shotCannon.y)
						{
							//yes, turn barrier invisible=exploded
							_tead.barrier[i].visible=false;
							_tead.bShotCannon=false;
							_tead.shotCannon.y=CANNON_SHOT_START_ROW;
							TEAD_showExplosion(_tead.shotCannon.x,_tead.shotCannon.y,2,true,1);
							return;
						}
					}
				}
				//check if mother ship is hit
				if (_tead.shotCannon.y<2 &&  _tead.shotCannon.x>=_tead.mother.x && _tead.shotCannon.x<(_tead.mother.x+5))
				{
					//yes, turn cannon fire off
					_tead.bShotCannon=false;
					//set cannon start shoot row
					_tead.shotCannon.y=CANNON_SHOT_START_ROW;
					//Turn Mother ships sound off
					TEAD_showExplosion(_tead.mother.x+2,_tead.mother.y,6,true,3);
					//turn mother ship outside screen
					_tead.mother={.x=-8,.y=0};
					//turn mother ship disabled
					_tead.bMotherShipApper=false;
					//hit mother ship you gain 5 scores
					_tead.score+=15;
					if (_tead.score>9999) _tead.score=9999;			
					//clear time to mother ship appear		
					timer.setElapsed(_tead.tMotherShipAppear);
					return;
				}
			}
			if (_tead.shotCannon.y<-1)
			{
				_tead.bShotCannon=false;
			}
		}
		else
		{
			//-----------------------------------------------------------------
			// Time To Fire From Cannon
			//-----------------------------------------------------------------
			key=kbd.getKbdState();
			//in  demo
			if (_tead.bInDemo)
			{
				if (rand()%5==1) key=Kbd::ENTER;
			}
			//Fire Key Pressed?
			//if (key=='E' || key=='X' || key=='Y')
			if ((uint8_t)key & (uint8_t)Kbd::ENTER)
			{
				//yes, set fire from cannon on
				_tead.bShotCannon=true;
				//_tead.shotCannonX=_tead.cannon.x;
				//_tead.shotCannonY=CANNON_SHOT_START_ROW;
				_tead.shotCannon={.x=_tead.cannon.x,.y=CANNON_SHOT_START_ROW};
				if (_tead.bSoundON)
				{
					wave.Play(WAVE_CHANNEL_CANNON_FIRE);
				}
			}
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Get Ships Max Y coordinate								|
//	| @brief Name		: TEAD_getShipsMaxY											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Y is a coordinate of Ship most close position of the		|
//	|					  cannon													|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Obtem a Maxima Coordenada Y das Naves 					|
//	| @brief Nome		: TEAD_getShipsMaxY											|
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Y é a coordenada da Nave mais proxima da posicao do		|
//	|					    canhao													|
//	+-------------------------------------------------------------------------------+
int8_t TEAD_getShipsMaxY()
{
	int max=0;
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible)
		{
			if (_tead.spaceShips[i].p.y>max) max=_tead.spaceShips[i].p.y;
		}
	}
	return max;
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Get Ships Min Y coordinate								|
//	| @brief Name		: TEAD_getShipsMinY											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Y is a coordinate of ship most close of top				|												        |
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Obtem a Minima Coordenada Y das Naves 					|
//	| @brief Nome		: TEAD_getShipsMinY							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Y é a coordenada da Nave mais proxima da posicao do topo|
//	+-------------------------------------------------------------------------------+
int8_t TEAD_getShipsMinY()
{
	int min=15;
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible)
		{
			if (_tead.spaceShips[i].p.y<min)
			{
				min=_tead.spaceShips[i].p.y;
			}
		}
	}
	return min;
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Get Ships Max X coordinate								|
//	| @brief Name		: TEAD_getShipsMaxX											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: X is a coordinate of ship most closed to right			|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Obtem a Maxima Coordenada X das Naves 					|
//	| @brief Nome		: TEAD_getShipsMaxX							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : x é a coordenada do ship mais proxima da direita		|
//	+-------------------------------------------------------------------------------+
int8_t TEAD_getShipsMaxX()
{
	int max=0;
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible)
		{
			if ((_tead.spaceShips[i].p.x+2)>max) max=_tead.spaceShips[i].p.x+2;
		}
	}
	return max;
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Get Ships Min X coordinate								|
//	| @brief Name		: TEAD_getShipsMinX											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: X is the ship coordinate most close to the left			|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Obtem a Minima X Coordenada X das Naves 					|
//	| @brief Nome		: TEAD_getShipsMinX							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : X é a coordenada da nave mais proxima da esquerda		|
//	+-------------------------------------------------------------------------------+
int8_t TEAD_getShipsMinX()
{
	int8_t min=23;
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible)
		{
			if (_tead.spaceShips[i].p.x<min) min=_tead.spaceShips[i].p.x;
		}
	}
	return min;
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Draw TEAD Aliens barriers									|
//	| @brief Name		: TEAD_drawBarrier											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Desenha as Barreiras do TEAD Aliens						|
//	| @brief Nome		: TEAD_drawBarriers							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawBarriers()
{
	for(uint8_t i=0;i<BARRIER_MAX_DOTS;i++)
	{
		if (_tead.barrier[i].visible) led.setPixel(_tead.barrier[i].p.x,_tead.barrier[i].p.y);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Process TEAD Aliens Ships Movement						|
//	| @brief Name		: TEAD_processShipsMovement									|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: The Ships Start Move Left to Right and when reach most	|
//	|					  right position the Ships start to move Right to Left and  |
//	|					  when reach most left position the Ships move to down and  |
//	|					  repeat a process until reach ground and  game over occur	|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Processa o Movimento das Naves do TEAD Aliens				|
//	| @brief Nome		: TEAD_processShipsMovement					                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	As Naves Comecao o movimento da Esquerda para Direita e |
//	|						quando a posicao mais a Direita e atingida entao as  na-|
//	|						ves comecao o movimento da Direita para Esquerda e quan-|
//	|						do a posicao mais a Esquerda é atingida as Naves  movem	|
//	|						para baixo e o processo	e repetido  ate  que  o  chao  e|
//	|						atingido e ai fim de jogo ocorre						|
//	+-------------------------------------------------------------------------------+
bool TEAD_processShipsMove()
{
	bool		bUpdateY;
	static bool bStepSound=false;
	int16_t		shipSpeedVarTmp;
	int8_t		shipsAlive;
	uint16_t	ship_move_speed;
	
	
	
	shipsAlive=TEAD_getShipsAlives();
	if (shipsAlive==1)
	{
		//max speed reached at level 50
		ship_move_speed=SPEED_SHIP_1_INITIAL-(SPEED_SHIP_1_INITIAL-SPEED_SHIP_1_FINAL)*(_tead.level-1)/50;
		//if level > 50 set max speed of  shoot
		if (_tead.level>50) ship_move_speed=SPEED_SHIP_1_FINAL;
		shipSpeedVarTmp=ship_move_speed;
	}
	else
	{
		if (shipsAlive==2)
		{
			//max speed reached at level 50
			ship_move_speed=SPEED_SHIP_2_INITIAL-(SPEED_SHIP_2_INITIAL-SPEED_SHIP_2_FINAL)*(_tead.level-1)/50;
			//if level > 50 set max speed of  shoot
			if (_tead.level>50) ship_move_speed=SPEED_SHIP_2_FINAL;
			shipSpeedVarTmp=ship_move_speed;
		}
		else
		{
			shipSpeedVarTmp=_tead.shipSpeedVar;
		}
	}
	
	
	if (timer.getElapsed(_tead.tShipSpeed)>(uint16_t)shipSpeedVarTmp)
	{
		timer.setElapsed(_tead.tShipSpeed);
		bStepSound=!bStepSound;
		if (_tead.bSoundON) 
		{
			if (bStepSound)
			{
				wave.setToneGen(440,25,0);
				wave.Unprepare(WAVE_CHANNEL_ALIEN_SOUND_2);
				wave.Prepare(Wave_Alien_Sound_1,WAVE_CHANNEL_ALIEN_SOUND_1);
				if (_tead.bSoundON)
				{
					wave.Play(WAVE_CHANNEL_ALIEN_SOUND_1);
				}
			}
			else
			{
				wave.Unprepare(WAVE_CHANNEL_ALIEN_SOUND_1);
				wave.Prepare((WAVE)Wave_Alien_Sound_2,WAVE_CHANNEL_ALIEN_SOUND_2);
				if (_tead.bSoundON)
				{
					wave.Play(WAVE_CHANNEL_ALIEN_SOUND_2);
				}
				wave.setToneGen(880,25,0);
			}
		}
		bUpdateY=false;
		_tead.bShipStyle=!_tead.bShipStyle;
		switch(_tead.shipDir)
		{
			case  ShipsDirection::RIGHT:
				for(uint8_t i=0;i<_tead.ships_max;i++)
				{
					_tead.spaceShips[i].p.x++;
				}
				if (TEAD_getShipsMaxX()>=SCREEN_MAX_X)
				{
					_tead.shipDir=ShipsDirection::LEFT;
					_tead.shipSpeedVar-=6;
					if (_tead.shipSpeedVar<SPEED_SHIP_FINAL)
					{
						_tead.shipSpeedVar=SPEED_SHIP_FINAL;
					}
				}
			break;
			case ShipsDirection::LEFT:
				for(uint8_t i=0;i<_tead.ships_max;i++)
				{
					_tead.spaceShips[i].p.x--;
				}
				if (TEAD_getShipsMinX()<=SCREEN_MIN_X)
				{
					_tead.shipDir=ShipsDirection::RIGHT;
					bUpdateY=true;
					_tead.shipSpeedVar-=6;
					if (_tead.shipSpeedVar<SPEED_SHIP_FINAL)
					{
						_tead.shipSpeedVar=SPEED_SHIP_FINAL;
					}
				}
			break;
		}
		if (bUpdateY)
		{
			for(uint8_t j=0;j< _tead.ships_max;j++)
			{
				_tead.spaceShips[j].p.y++;
			}
			if (TEAD_getShipsMaxY()==SHIP_MAX_ROW)
			{
				TEAD_initializeGame(true,true,true);
				if (!(_tead.bInDemo))
				{
					TEAD_showGameOverAndMessages(false);
				}
				//TEAD_updateScreen();
				return true;
			}

		}
	}
	return false;
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Show End Game Message										|
//	| @brief Name		: TEAD_showEndGame											|	
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Mostra a mensagem End Game(Fim de Jogo)					|
//	| @brief Nome		: TEAD_showEndGame							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+

void TEAD_showGameOverAndMessages(bool gameStart)
{
#define TIME_TO_SHOW_UP					 4000
#define TIME_TO_SHOW_DOWN				 1500
#define TIME_TO_SHOW_SCORE				 4000
#define TIME_TO_SHOW_TIME				 15000
#define TIME_TO_BEAT_SECOND				 500

	static int8_t		event=3;
	int8_t		y=SCREEN_MAX_X;
	char		key;
	uint8_t		h,m,s;
	int			x=led.getWidth();
	uint32_t	tShowUp;
	uint32_t	tShowDown;
	uint32_t	tShowScore;
	uint32_t	tShow_TEAD_Aliens_Text;
	uint32_t	tShowTime;
	uint32_t	tHalfSecond;
	uint32_t	tShowDemo;
	bool		bhalf=true;
	CharFont	font;
	uint8_t		playCount=0;
	
	
	//save font
	font=led.getFont();
		
	//main show game loop
	timer.setElapsed(tShowUp);
	timer.setElapsed(tShowDown);
	timer.setElapsed(tShowScore);
	timer.setElapsed(tShowTime);
	timer.setElapsed(tHalfSecond);
	timer.setElapsed(tShowTime);
		
	led.setFont(CharFont::FONT_5X16);
	
	led.cls();
	
	for(;;)
	{
		switch (event)
		{
			//GAME OVER TEXT SCROLL UP
			case 0:
				led.cls();
				led.setFont(CharFont::FONT_3X5);
				if (gameStart)
				{
					led.moveTo(0,y+1);
					led.putSF(PSTR(" GAME"));
					led.moveTo(2,y+8+1);
					led.putSF(PSTR("START"));
				}
				else
				{
					playCount++;
					if (playCount==12)
					{
						if (_tead.bSoundON)
						{
							wave.Prepare((WAVE)Wave_Game,WAVE_CHANNEL_GAME);
							wave.Play(WAVE_CHANNEL_GAME);							
						}
					}
					if (playCount==18)
					{
						if (_tead.bSoundON)
						{
							wave.Prepare((WAVE)Wave_Over,WAVE_CHANNEL_OVER);
							wave.Play(WAVE_CHANNEL_OVER);					
						}
					}
					led.moveTo(0,y+1);
					led.putSF(PSTR(" GAME"));
					led.moveTo(0,y+8+1);
					led.putSF(PSTR(" OVER"));
				}
				timer.delayMilliseconds(SPEED_END_GAME_SCROLL);
				y--;
				if (_tead.bSoundON) 
					if (y>0) wave.setToneGen(1000+y*50,SPEED_END_GAME_SCROLL,3);
				if (y<0) y=0;
				if (timer.getElapsed(tShowUp)>TIME_TO_SHOW_UP)
				{
					timer.setElapsed(tShowDown);
					event=1;
				}
			break;
			//GAME OVER TEXT SCROLL DOWN
			case 1:
				led.cls();
				led.setFont(CharFont::FONT_3X5);
				if (gameStart)
				{
					led.moveTo(0,y+1);
					led.putSF(PSTR(" GAME"));
					led.moveTo(2,y+8+1);
					led.putSF(PSTR("START"));
				}
				else
				{
					led.moveTo(0,y+1);
					led.putSF(PSTR(" GAME"));
					led.moveTo(0,y+8+1);
					led.putSF(PSTR(" OVER"));
				}
				timer.delayMilliseconds(SPEED_END_GAME_SCROLL);
				y++;
				if (_tead.bSoundON) 
				{
					if (y>0)
					{
						wave.setToneGen(1000+y*50,SPEED_END_GAME_SCROLL,3);
					}
				}
				if (y>SCREEN_MAX_X) y=SCREEN_MAX_X;
				if (timer.getElapsed(tShowDown)>TIME_TO_SHOW_DOWN)
				{
					timer.setElapsed(tShowScore);
					event=2;
					if (_tead.bSoundON)
					{
						wave.setToneGen(2500,500,3);
					}
				}
			break;
			//GAME OVER SHOW PRESS KEYS
			case 2:
				led.cls();
				led.setFont(CharFont::FONT_3X5);
				if (gameStart)
				{
					led.moveTo(2,1);
					led.putSF(PSTR("PRESS"));
					led.moveTo(4,8+1);
					led.putSF(PSTR("KEYS"));
				}
				else
				{
					TEAD_showScoresAnimation();
				}
				timer.delayMilliseconds(SPEED_END_GAME_SCROLL);
				if (timer.getElapsed(tShowScore)>TIME_TO_SHOW_SCORE)
				{
					led.cls();
					timer.setElapsed(tShow_TEAD_Aliens_Text);
					event=3;
					x=SCREEN_MAX_X;
					if (_tead.bSoundON)
					{
						wave.setToneGen(880,500,3);
					}
				}
			break;
			//GAME OVER SHOW VERSION SCROOLING RIGHT TO LEFT
			case 3:
				led.cls();
				led.setFont(CharFont::FONT_5X16);
				
				if (x==0)
				{
					playTEADAliansGame();
				}
				
				//led.moveTo(x,4);
				led.moveTo(x,1);
				led.putS(_tead.bfVersion);
				timer.delayMilliseconds(SPEED_TEAD_ALIENS_TEXT);
				x--;
				if (x<-_tead.TEAD_Aliens_text_size)
				{
					timer.setElapsed(tShowTime);
					x=SCREEN_MAX_X;
					timer.setElapsed(tShowUp);
					timer.setElapsed(tHalfSecond);
					event=4;
					led.cls();
				}
			break;
			//SHOW TIME
			case 4:
				led.cls();
				led.setFont(CharFont::FONT_5X16);
				if (timer.getElapsed(tHalfSecond)>TIME_TO_BEAT_SECOND)
				{
					timer.setElapsed(tHalfSecond);
					if  (bhalf)
					{
						led.line(9,2,9,3,Color::RED);
						if (_tead.bSoundON)
						{
							wave.setToneGen(1500,125,3);
							if (_tead.bSoundON)
							{
								wave.Play(WAVE_CHANNEL_TIK_TAK);
							}
						}
					}
					bhalf=!bhalf;
				}
				//SHOW TIME
				rtc.GetTime(h,m,s);
				sprintf(_tead.bf,"%02d%02d",h,m);
				//put Time on Screen
				led.moveTo(0,1);
				led.putS(_tead.bf);
				if (bhalf)
				{
					//led.line(0,15,11,15);
					led.line(11,2+1,11,3+1);
					led.line(11,10+1,11,11+1);
					
				}
				else
				{
					//led.line(12,15,23,15);
				}
				timer.delayMilliseconds(SPEED_END_GAME_SCROLL);
				if (timer.getElapsed(tShowTime)>TIME_TO_SHOW_TIME)
				{
					
					timer.setElapsed(tShowDemo);
					x=0;
					event=5;
				}
			break;
			//DEMO
			case 5:
				TEAD_MainGame(true);
				//led.setCharToNormal();
				if (timer.getElapsed(tShowDemo)>TIME_TO_SHOW_DEMO)
				{
					timer.setElapsed(tShowUp);
					event=0;
				}
			break;
		}
		//if key pressed exit
		key=kbd.getKbdASCII();
		if (key!=' ')
		{
			led.cls();
			led.setFont(CharFont::FONT_3X5);
			kbd.waitKbdRelease();
			break;
		}
		timer.delayMilliseconds(SPEED_TEAD_ALIENS_TEXT);
		//refresh screen
		led.refresh();
	}
	//restore font
	led.setFont(font);
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Show Cannon Explosion										|
//	| @brief Name		: TEAD_showCannonExplosion									|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
void TEAD_showCannonExplosion()
{
	//show explosion of cannon
	for(uint8_t j=0;j<3;j++)
	{
		TEAD_showExplosion(_tead.cannon.x,SCREEN_MAX_Y,7,true,1);
		TEAD_drawCannon(Color::RED);
		led.refresh();
		timer.delayMilliseconds(50);
		TEAD_drawCannon(Color::BLACK);
		led.refresh();
		timer.delayMilliseconds(100);
	}
	//decrement lives
	_tead.lives--;
	if (_tead.lives==0)
	{
		//initialize
		TEAD_initializeGame(true,true,true);
		if (!(_tead.bInDemo))
		{
			TEAD_showGameOverAndMessages(false);
		}
	}
}

//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Get Scores From EEPROM									|
//	| @brief Name		: SCORES_getFromEEPROM										|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: The Structure _tead.scores is filled with name and value	|
//	|					  from EEPROM												|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Obtem a Pontuacao da EEPROM		 						|
//	| @brief Nome		: SCORES_getFromEEPROM						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : A Estrutura _tead.cores e preenchida com nome e valor da|
//	|						EEPROM													|
//	+-------------------------------------------------------------------------------+
void SCORES_getFromEEPROM(void)
{
	for(uint8_t i=0;i<SCORES_MAX;i++)
	{
		eeprom_read_block(_tead.scores[i].name,&e_Scores[i].name,sizeof(e_Scores[i].name));
		_tead.scores[i].value=eeprom_read_word(&e_Scores[i].value);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Save Scores Into EEPROM									|
//	| @brief Name		: SCORES_saveIntoEEPROM										|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: The Structure _tead.scores is saved into EEPROM			|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Salva Score dentro da EEPROM		 						|
//	| @brief Nome		: SCORES_saveIntoEEPROM					                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : A Estrutura _tead.cores e salva dentro da EEPROM		|
//	+-------------------------------------------------------------------------------+
void SCORES_saveIntoEEPROM()
{
	struct_Scores score;
	
	for(uint8_t i=0;i<SCORES_MAX;i++)
	{
		//get old values from EEPROM
		eeprom_read_block(score.name,&e_Scores[i].name,sizeof(e_Scores[i].name));
		score.value=eeprom_read_word(&e_Scores[i].value);
		//save new name if is different
		if (strcmp(score.name,_tead.scores[i].name)!=0)
		{
			//write new name
			eeprom_write_block(&_tead.scores[i].name,&e_Scores[i].name,sizeof(score.name));
		}
		//save new value if is different
		if (score.value!=_tead.scores[i].value)
		{
			//write new name
			eeprom_write_word(&e_Scores[i].value,_tead.scores[i].value);
		}
	}	
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Draw Scores on Screen at position x,y						|
//	| @brief Name		: TEAD_drawScores											|
//	| @parm [in]		: x,y		: coordinate x,y								|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Desenha a Pontuacao na Tela na Posicao x,y				|
//	| @brief Nome		: TEAD_drawScores							                |
//	| @parm Entrada [in]: x,y		: coordenada x,y								|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_drawScores(int x,int y)
{
	CharFont	font;
	
	//save Font
	font=led.getFont();
	//set new font
	led.setFont(CharFont::FONT_3X5);
	//draw scores
	led.moveTo(x,y);
	led.putS("SCORES");
	for(uint8_t i=0;i<SCORES_MAX;i++)
	{
		led.moveTo(x,i*led.getCharHeight()+8+y);
		sprintf(_tead.bf,"%2s%4d",_tead.scores[i].name,_tead.scores[i].value);
		led.putS(_tead.bf);
	}	
	//update screen
	led.refresh();
	//restore font
	led.setFont(font);
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Show Game Score Animation									|
//	| @brief Name		: TEAD_showGameScoreAnimation								|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: The Animation Interrupted if any key is pressed 			|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Mostra uma Animacao das PontuacoesObtem 					|
//	| @brief Nome		: TEAD_shoGameScoreAnimation					            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	A Animacao é Interrompida se qualquer tecla for precio-	|
//	|						nada													|
//	+-------------------------------------------------------------------------------+
void TEAD_showScoresAnimation()
{
	CharFont	font;

	//save font
	font=led.getFont();
	//set new font
	led.setFont(CharFont::FONT_3X5);
	//get Scores from eeprom
	SCORES_getFromEEPROM();
	//Flash Scores	
	for(uint8_t i=0;i<5;i++)
	{
		if (_tead.bSoundON)
		{
			wave.Play(WAVE_CHANNEL_MOTHER_SHIP);	
		}
		led.cls();
		TEAD_drawScores(0,0);
		if (TEAD_delayKey(SCORES_FLASH_ON))
		{
			//restore font
			led.setFont(font);
			return;
		}
		led.setFillMode(true);
		led.rectangle(0,0,24,8,Color::BLACK);
		led.refresh();
		if (TEAD_delayKey(SCORES_FLASH_OFF))
		{
			//restore font
			led.setFont(font);
			return;
		}
	}
	//clear screen
	led.cls();
	//draw scores at coordinates 0,0
	TEAD_drawScores(0,0);
	//wait a time
	timer.delayMilliseconds(SCORES_SHOW_TIME);
	//show all scores scrolling up
	for(int i=0;i<led.getCharHeight()*4;i+=led.getCharHeight())
	{
		for(int j=i;j<i+led.getCharHeight()-1;j++)
		{
			led.cls();
			TEAD_drawScores(0,-j);
			if (_tead.bSoundON)
			{
				wave.Play(WAVE_CHANNEL_SHIP_EXPLOSION);	
			}
			if (TEAD_delayKey(SCORES_SCROLL_TIME))
			{
				//restore font
				led.setFont(font);
				return;
			}
		}
		if (TEAD_delayKey(SCORES_SHOW_TIME))
		{
			//restore font
			led.setFont(font);
			return;
		}		
	}
	//go back scores scrolling down
	for(int i=led.getCharHeight()*4-1;i>=0;i--)
	{
		led.cls();
		TEAD_drawScores(0,-i);
		if (TEAD_delayKey(SCORES_SCROLL_TIME))
		{
			//restore font
			led.setFont(font);
			return;
		}		
	}
	//show time
	if (TEAD_delayKey(SCORES_SHOW_TIME))
	{
		//restore font
		led.setFont(font);
		return;
	}	
	//restore font
	led.setFont(font);
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Show Curtain												|
//	| @brief Name		: TEAD_showCurtain											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Mostra Cortina						 					|
//	| @brief Nome		: TEAD_showCurtain								            |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void TEAD_showCurtain()
{
	led.setFillMode(true);
	for(int8_t r=0;r<led.getWidth();r++)
	{
		led.circle(led.getWidth()/2,led.getHeight()/2,r);
		led.circle(led.getWidth()/2,led.getHeight()/2,r-led.getWidth()/3,Color::BLACK);
		if (_tead.bSoundON)
		{
			wave.Play(WAVE_CHANNEL_TIK_TAK);
		}
		led.refresh();
		timer.delayMilliseconds(50);
	}
	led.setFillMode(false);	
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function : Process Ships Hits barriers										|
//	| @brief Name    : TEAd_processShipsHitBarriers										|
//	| @parm [in]   :																	|
//	| @parm [out]  : 																	|
//	| @remarks : Process when Ships Hit Barriers then Barriers is vanish	        |
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao  : Processa se Naves Atingem as Barreiras								|
//	| @brief Nome    : TEAD_processShipsHitBarriers				                        |
//	| @parm Entrada [in] :																	|
//	| @parm Saida [out]   : 																	|
//	| @remarks comentario :	Procesa quando as Naves atingem as Barreiras entao as Barreiras	|
//	|				desaparecem														|
//	+-------------------------------------------------------------------------------+
void TEAD_processShipsHitBarriers()
{
	uint8_t s,b;

	for(b=0;b<BARRIER_MAX_DOTS;b++)	
	{
		if (_tead.barrier[b].visible)
		{
			for(s=0;s<_tead.ships_max;s++)
			{
				if (_tead.spaceShips[s].visible)
				{
					//if (barrier[b].x==spaceShips[s].x && barrier[b].y==spaceShips[s].y)
					if (_tead.barrier[b].p.x>=_tead.spaceShips[s].p.x && _tead.barrier[b].p.x<=_tead.spaceShips[s].p.x+2 && 
						_tead.barrier[b].p.y>=_tead.spaceShips[s].p.y && _tead.barrier[b].p.y<=_tead.spaceShips[s].p.y+1)
					{
						_tead.barrier[b].visible=false;
					}					
				}
			}
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function : process Ships Hits Cannon											|
//	| @brief Name    : TEAD_processShipsHitCannon											|
//	| @parm [in]   :																	|
//	| @parm [out]  : 																	|
//	| @remarks : When Ships Hit de Cannon then Cannon Explodes and one Live is      |
//	|			 decremented and if reach zero the game over message appear	and game|
//	|			 will terminated													|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao  : Processa qando as Naves atingem o Canhao							|
//	| @brief Nome    : TEAD_processShipsHitCannon					                        |
//	| @parm Entrada [in] :																	|
//	| @parm Saida [out]   : 																	|
//	| @remarks comentario : Quando as Naves Atingirem o Canhao entao o Canhao ira Explodir	|
//	|				e as Vidas serao decrementadas e se atingir zero a mensagem de	|
//	|				game over aparecera e o Jogo sera encerado						|
//	+-------------------------------------------------------------------------------+
void TEAD_processShipsHitCannon()
{
	for(uint8_t i=0;i<_tead.ships_max;i++)
	{
		if (_tead.spaceShips[i].visible)
		{
			if ((_tead.spaceShips[i].p.x<=_tead.cannon.x && _tead.cannon.x<(_tead.spaceShips[i].p.x+_tead.spaceShips[i].w)) &&
				(_tead.spaceShips[i].p.y<=_tead.cannon.y && _tead.cannon.y<(_tead.spaceShips[i].p.y+_tead.spaceShips[i].h)))
			{
				//turn ship not visible
				_tead.spaceShips[i].visible=false;
				//draw cannon explosion
				TEAD_showCannonExplosion();
			}
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: process Fire from Front Ships								|
//	| @brief Name		: TEAD_processFireFromFrontShips							|
//	| @parm [in]		:															|
//	| @parm [out]		:  															|
//	| @remarks			: Process Which Front Ship i.e. Most closed to Cannon will  |
//	|					  fire														|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Processa Tiro vindo das Naves da Frente					|
//	| @brief Nome		: TEAD_processFireFromFrontShips		                    |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :	Processa qual Nave mais proxima do Canhao ira Disparar	|
//	+-------------------------------------------------------------------------------+

//  0 1 2 3 4 5 6 7 8 9<--ship colum
//  # # #   # # # # # #
//  #   #   #   # # #
//  #       #   # #    < --FRONT SHIPS

void TEAD_processFireFromShips()
{
	int8_t		minPos;
	int8_t		idx;
 	int8_t		randColumn;
	int8_t		frontShipIndex;
	uint16_t	shoot_ship_speed;
	
	
	//ship shooting?
	if (_tead.bShotShip)
	{
		//max speed reached at level 50
		shoot_ship_speed=SPEED_SHOT_FROM_SHIP_INITIAL-(SPEED_SHOT_FROM_SHIP_INITIAL -SPEED_SHOT_FROM_SHIP_FINAL)*(_tead.level-1)/50;
		//if level > 50 set max speed of  shoot
		if (_tead.level>50) shoot_ship_speed=SPEED_SHOT_FROM_SHIP_FINAL;
		//yes, process ship shooting
		if (timer.getElapsed(_tead.tShotSpeedShip)>shoot_ship_speed)
		{
			timer.setElapsed(_tead.tShotSpeedShip);
			_tead.shotShip.y++;
			//check if ships hit any thing
			if (led.getPixel(_tead.shotShip.x,_tead.shotShip.y)==Color::RED ||
				led.getPixel(_tead.shotShip.x,_tead.shotShip.y+1)==Color::RED)
			{
				//check if ship shoot hit a barrier
				for(int8_t i=0;i<BARRIER_MAX_DOTS;i++)
				{
					//barrier visible? not destroyed?
					if (_tead.barrier[i].visible)
					{
						//yes, check if this dot barrier hit?
						if ((_tead.barrier[i].p.x)==_tead.shotShip.x && _tead.barrier[i].p.y==_tead.shotShip.y)
						{
							//show explosion of barrier
							TEAD_showExplosion(_tead.shotShip.x+1,_tead.shotShip.y,2,true,1);													
							//turn invisible
							_tead.barrier[i].visible=false;
							//turn ship firing off
							_tead.bShotShip=false;
							//reset time to fire
							timer.setElapsed(_tead.tTimeToShotFromShip);
							return;
						}
					}
				}
				
				//check if shot hit cannon 
				if ((_tead.shotShip.x==_tead.cannon.x && _tead.shotShip.y==_tead.cannon.y-1) ||
				    (_tead.shotShip.x==_tead.cannon.x-1 && _tead.shotShip.y==_tead.cannon.y) ||
					(_tead.shotShip.x==_tead.cannon.x+1 && _tead.shotShip.y==_tead.cannon.y))
				{				
					//show explosion of cannon				
					TEAD_showCannonExplosion();
					//reset time to fire
					timer.setElapsed(_tead.tTimeToShotFromShip);
					//turn ship firing off
					_tead.bShotShip=false;	
					return;			
				}
				//check if shot ship hit shot cannon
				if (_tead.shotCannon.x==_tead.shotShip.x && _tead.shotCannon.y==_tead.shotShip.y)
				{
					//show explosion of barrier
					TEAD_showExplosion(_tead.shotShip.y,_tead.shotShip.y,2,true,2);
					//reset time to fire
					timer.setElapsed(_tead.tTimeToShotFromShip);
					//turn ship firing off
					_tead.bShotShip=false;
					_tead.bShotCannon=false;
					_tead.shotCannon.x=SCREEN_MAX_Y;
					return;					
				}
			}
			if (_tead.shotShip.y>SCREEN_MAX_Y)
			{
				_tead.bShotShip=false;		
			}
		}
	}
	else
	{
		if (timer.getElapsed(_tead.tTimeToShotFromShip)>SPEED_TIME_TO_SHOT_FROM_SHIP)
		{
			timer.setElapsed(_tead.tTimeToShotFromShip);
			//clear front ships count
			_tead.frontShips.count=0;
			//clear frontShips
			for(uint8_t i=0;i<FRONT_SHIPS_MAX;i++)
			{
				_tead.frontShips.Coords[i].p={.x=0,.y=0};
			}
			//check front ships
			for(int8_t i=0;i<_tead.ships_cols;i++)
			{
				for(int8_t j=_tead.ships_rows-1;j>=0;j--)
				{
					frontShipIndex=i+j*_tead.ships_cols;
					if (_tead.spaceShips[frontShipIndex].visible)
					{
						//add new front ship
						_tead.frontShips.Coords[_tead.frontShips.count].p=_tead.spaceShips[frontShipIndex].p;
						_tead.frontShips.count++;
						//skip to next colum;
						break;
					}
				}
			}
			//random a fire front column if found a front ship
			if (_tead.frontShips.count>0)
			{
				//4/9% of times fire from closed ship
				if ((rand()%10)>3)
				{
					//chose most close
					idx=_tead.frontShips.count-1;
					minPos=SCREEN_MAX_X;
					for(int8_t i=0;i<_tead.frontShips.count;i++)
					{
						if (abs(_tead.frontShips.Coords[i].p.x-_tead.cannon.x)<minPos)
						{
							minPos=abs(_tead.frontShips.Coords[i].p.x-_tead.cannon.x);
							idx=i;
						}
					}
					//set it coordinates
					_tead.shotShip.x=_tead.frontShips.Coords[idx].p.x+1;
					_tead.shotShip.y=_tead.frontShips.Coords[idx].p.y;
				}
				else
				{
					//choose randomly a front ship
					randColumn=rand()%_tead.frontShips.count;
					//set it coordinates
					_tead.shotShip=_tead.frontShips.Coords[randColumn].p;									
				}
				//set firing
				_tead.bShotShip=true;				
			}
		}
	}
}

//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Process Mother Ship Appearance and Move					|
//	| @brief Name		: TEAD_processMotherShipAppearAndMove						|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Process if is time to Mother Ship Appear and make a		|
//	|					  movement from	left to right at top of screen and only if  |
//	|					  a Mother Ship have a space to move, in other world no		|
//	|					  other ship in front of mother	 ship						|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao			: Processa Hora da Nave Mae aparecer					|
//	| @brief Nome			: TEAD_processMotherShipAppearAndMove					|
//	| @parm Entrada [in]	:														|
//	| @parm Saida [out]		: 														|
//	| @remarks comentario	:	Processa se e a hora da Nave Mae aparecer e comecar |
//	|							o movimento da Esquerda para Direita na parte do To-|
//	|							po da tela e somente se	houver espaco para a Nave	|
//	|							Mae, em outras palavras não há naves na frente da	|
//	|							Nave Mae											|
//	+-------------------------------------------------------------------------------+
//	|						##			|
//	|MOST LEFT SCREEN 	   #### ----->	| MOST RIGHT SCREEN 

void TEAD_processMotherShipAppearAndMove()
{
	static int8_t s=0;
	//static int8_t k=1;
	
	if (_tead.bMotherShipApper)
	{
		if (timer.getElapsed(_tead.tMotherShipSpeed)>SPEED_MOTHER_SHIP)
		{
			timer.setElapsed(_tead.tMotherShipSpeed);
			if (_tead.bSoundON)
			{
				 wave.setToneGen(1500+s*300,SPEED_MOTHER_SHIP,3);
				 if (_tead.bSoundON)
				 {
					wave.Play(WAVE_CHANNEL_MOTHER_SHIP);		
				 }
			}
			_tead.mother.x++;
			if (_tead.mother.x>SCREEN_MAX_X)
			{
				_tead.bMotherShipApper=false;
				timer.setElapsed(_tead.tMotherShipAppear);
			}
		}
	}
	else
	{
		if (timer.getElapsed(_tead.tMotherShipAppear)>TIME_TO_MOTHER_SHIP_APPEAR)
		{
			timer.setElapsed(_tead.tMotherShipSpeed);
			if (TEAD_getShipsMinY()>1)
			{
				_tead.bMotherShipApper=true;
				_tead.mother={.x=-8,.y=0};
			}
		}		
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Reset Microcontroller if B keys pressed for more 5 seconds|
//	| @brief Name		: doReset													|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Reseta Microcontrolador se a Tecla B estiver Pressionada	|
//	|					  por mais de 5 segundos									|
//	| @brief Nome		: doReset									                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
static void Reset()
{
	//clear screen
	led.cls();
	//set font
	led.setFont(CharFont::FONT_3X5);
	//Display message Reset
	led.putS("RESET");
	//play resetting
	playResetting();
	//draw bar indicating reset
	for(int w=0;w<24;w++)
	{
		//draw bar
		led.rectangle(0,12,w,4,Color::RED);
		//update  screen
		led.refresh();
		//delay
		timer.delayMilliseconds(84);
	}
	while (wave.Playing(WaveChannel::CHANNEL_8));
	//reset
	asm volatile("jmp 0");
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Reset Microcontroller if B keys pressed for more 5 seconds|
//	| @brief Name		: doReset													|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Reseta Microcontrolador se a Tecla B estiver Pressionada	|
//	|					  por mais de 5 segundos									|
//	| @brief Nome		: doReset									                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
static void	doReset()
{
	int16_t cReset;				//Reset Counter
	//set font
	led.setFont(CharFont::FONT_3X5);
	//clear tReset
	cReset=0;
	//loop forever
	for(;;)
	{
		//delay one millisecond
		timer.delayMilliseconds(1);
		//if key B pressed during some time reset
		if (kbd.getKbdState()==Kbd::B)
		{
			//pump reset time
			cReset++;
			//reset in 5 seconds
			if (cReset>4000)
			{
				//Reset
				Reset();
			}
		}
		else
		{
			//clear exit time
			cReset=0;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Set RTC Time and Date										|
//	| @brief Name		: SetRTCTimeAndDate											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Set Time and Date to RTC									|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao			: Ajusta Data e Horario no RTC							|
//	| @brief Nome			: SetRTCTimeAndDate										|
//	| @parm Entrada [in]	:														|
//	| @parm Saida [out]		: 														|
//	| @remarks comentario	:	Ajusta Data e Horario no RTC						|
//	+-------------------------------------------------------------------------------+
static void	ShowClock(uint8_t clockNumber)
{
	uint8_t	h,m,s,sa;
	int8_t p=0;
	uint32_t	tBlink;
	Color		cBlink;

	//play in
	wave.Play(WAVE_CHANNEL_CANNON_FIRE);
	//only to update time blinck block
	sa=255;
	//set initialize blink color
	cBlink=Color::RED;
	//set timers
	timer.setElapsed(tBlink);
	//Main Loop
	for(;;)
	{
		//Get Time
		rtc.GetTime(h,m,s);
		//Clear Screen
		led.cls();
		//set Big font to Hours
		led.setFont(CharFont::FONT_5X16);
		//Print Hour
		sprintf(_tead.bf,"%02d",h);
		led.moveTo(0,1);
		led.putS(_tead.bf);
		//Set Normal Font to Minute and Second
		switch(clockNumber)
		{
			case 1:
				led.setFont(CharFont::FONT_5X8);
				//Print Minute and Hour
				sprintf(_tead.bf,"%02d",m);
				led.moveTo(13,0);
				led.putS(_tead.bf);
				sprintf(_tead.bf,"%02d",s);
				led.moveTo(13,9);
				led.putS(_tead.bf);
			break;
			case 2:
				//print only big minute
				sprintf(_tead.bf,"%02d",m);
				led.moveTo(13,1);
				led.putS(_tead.bf);
			break;
		}
		//Time to Flash Blinck Block?
		if  (timer.getElapsed(tBlink)>100)
		{
			//yes, clear blink timer
			timer.setElapsed(tBlink);
			//change color of Block Blink
			if (cBlink==Color::RED)
			{
				cBlink=Color::BLACK;
			}
			else
			{
				cBlink=Color::RED;
			}
		}
		//Draw Blocks Blinkers
		led.rectangle(11,p,2,2,cBlink);
		led.rectangle(11,15-p,2,2,cBlink);
		//update block position if second change
		if (sa!=s)
		{
			//update last second
			sa=s;
			//pump coordinates
			p--;
			if (p<0) p=14;
			//Play tick
			wave.Play(WAVE_CHANNEL_TIK_TAK);
		}
		//refresh Screen
		led.refresh();
		//return if B key pressed
		if (kbd.getKbdState()==Kbd::B)
		{
			//wait keyboard release
			kbd.waitKbdRelease();
			//return
			return;
		}
		//Refresh time
		timer.delayMilliseconds(20);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Set RTC Time and Date										|
//	| @brief Name		: SetRTCTimeAndDate											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Set Time and Date to RTC									|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao			: Ajusta Data e Horario no RTC							|
//	| @brief Nome			: SetRTCTimeAndDate										|
//	| @parm Entrada [in]	:														|
//	| @parm Saida [out]		: 														|
//	| @remarks comentario	:	Ajusta Data e Horario no RTC						|
//	+-------------------------------------------------------------------------------+

static void setRTCTime()
{
#define RTC_CHOICE_TIME_HOUR	0
#define RTC_CHOICE_TIME_MINUTE	1
#define RTC_CHOICE_TIME_SECOND	2

	CharFont	font;
	Kbd			key;
	uint8_t		d,m,y,dw;
	uint8_t		hh,mm,ss;
	int8_t		choiceTime=0;	//0 set hour 1 set Minute 2 second
	uint32_t	tBlink;
	bool		bBlink=false;

	//play in
	wave.Play(WAVE_CHANNEL_CANNON_FIRE);
	//clear screen
	led.cls();
	//Save Actual font
	font=led.getFont();
	//clear screen again
	led.cls();
	//and refresh again
	led.refresh();
	//Set New Font
	led.setFont(CharFont::FONT_5X8);
	//get current time and date
	rtc.GetDate(y,m,d,dw,true);
	rtc.GetTime(hh,mm,ss,true);
	//wait key release
	kbd.waitKbdRelease();
	//Set Timers
	timer.setElapsed(tBlink);
	//Main Loop
	for(;;)
	{
		//clear Screen
		led.cls();
		//+----------------------------------------------------------------------
		//|	PROCESS TIME SETTING
		//+----------------------------------------------------------------------
		//Show Clock 
		led.bmp(16,8,(BMP)BMP_clock);
		//Show Time
		led.moveTo(0,0);
		sprintf(_tead.bf,"%02d%02d\n\r%02d",hh,mm,ss);
		led.putS(_tead.bf);
		//time to blink?
		if (timer.getElapsed(tBlink)>250)
		{
			//reload timer
			timer.setElapsed(tBlink);
			//change blink state
			bBlink=!bBlink;
		}
		//blink?
		if (bBlink)
		{
			//Show Selection Bar
			switch(choiceTime)
			{
				case RTC_CHOICE_TIME_HOUR:
					led.rectangle(0,7,12,1,Color::RED);
				break;
				case RTC_CHOICE_TIME_MINUTE:
					led.rectangle(12,7,12,1,Color::RED);
				break;
				case RTC_CHOICE_TIME_SECOND:
					led.rectangle(0,15,12,1,Color::RED);
				break;
			}
		}

		//update screen
		led.refresh();
		//Get kbd state
		key=kbd.getKbdState();
		//Process Key according
		switch(key)
		{
			case Kbd::UP:
				switch(choiceTime)
				{
					case RTC_CHOICE_TIME_HOUR:
						hh++;
						if (hh>23) hh=0;
					break;
					case RTC_CHOICE_TIME_MINUTE:
						mm++;
						if (mm>59) mm=0;
					break;
					case RTC_CHOICE_TIME_SECOND:
						ss++;
						if (ss>59) ss=0;
					break;					
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				timer.delayMilliseconds(250);
			break;
			case Kbd::DOWN:
				switch(choiceTime)
				{
					case RTC_CHOICE_TIME_HOUR:
						if (hh!=0) hh--; else hh=23;
					break;
					case RTC_CHOICE_TIME_MINUTE:
						if (mm!=0)	mm--; else mm=59;
					break;
					case RTC_CHOICE_TIME_SECOND:
						if (ss!=0) ss--; else ss=59;
					break;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				timer.delayMilliseconds(250);
			break;
			case Kbd::A:
			break;
			case Kbd::B:
				playCancel();
				kbd.waitKbdRelease();
				led.setFont(font);
				return;
			break;
			case Kbd::LEFT:
				choiceTime--;
				if (choiceTime<RTC_CHOICE_TIME_HOUR)
				{
					choiceTime=RTC_CHOICE_TIME_SECOND;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::RIGHT:
				choiceTime++;
				if (choiceTime>RTC_CHOICE_TIME_SECOND)
				{
					choiceTime=RTC_CHOICE_TIME_HOUR;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::ENTER:
				rtc.SetTime(hh,mm,ss,true);
				playOk();
				kbd.waitKbdRelease();
				led.setFont(font);
				return;
			break;
			case Kbd::NONE:
			break;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Set RTC Time and Date										|
//	| @brief Name		: SetRTCTimeAndDate											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Set Time and Date to RTC									|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao			: Ajusta Data e Horario no RTC							|
//	| @brief Nome			: SetRTCTimeAndDate										|
//	| @parm Entrada [in]	:														|
//	| @parm Saida [out]		: 														|
//	| @remarks comentario	:	Ajusta Data e Horario no RTC						|
//	+-------------------------------------------------------------------------------+

const char weekDays[]="SMTWTFS";
//  no ja fe ma ab mo ju jl ag se ot no dz
//  0  1  2  3  4  5  6  7  8  9  10 11 12
uint8_t dayOfMonth[]={00,31,28,31,30,31,30,31,31,30,31,30,31};

static void setRTCDate()
{
	#define RTC_CHOICE_DATE_YEAR	0
	#define RTC_CHOICE_DATE_MONTH	1
	#define RTC_CHOICE_DATE_DAY		2
	#define RTC_CHOICE_DATE_DAYWEEK	3


	CharFont	font;
	Kbd			key;
	uint8_t		d,m,y,dw;
	uint8_t		hh,mm,ss;
	int8_t		choiceDate=0;	//0 set year 1 set month 2 set day 3 set day of week
	uint32_t	tBlink;
	bool		bBlink=false;

	//play in
	wave.Play(WAVE_CHANNEL_CANNON_FIRE);
	//clear screen
	led.cls();
	//Save Actural font
	font=led.getFont();
	//clear screen again
	led.cls();
	//and refresh again
	led.refresh();
	//Set New Font
	led.setFont(CharFont::FONT_5X8);
	//get current time and date
	rtc.GetDate(y,m,d,dw,true);
	rtc.GetTime(hh,mm,ss,true);
	//wait key release
	kbd.waitKbdRelease();
	//Set Timers
	timer.setElapsed(tBlink);
	//Main Loop
	for(;;)
	{
		//clear Screen
		led.cls();
		//+----------------------------------------------------------------------
		//|	PROCESS DATE SETTING
		//+----------------------------------------------------------------------
		//Show date
		led.moveTo(0,0);
		//get date
		sprintf(_tead.bf,"%02d%02d\n\r%02d %c",y,m,d,weekDays[dw-1]);
		led.putS(_tead.bf);
		//time to blink?
		if (timer.getElapsed(tBlink)>250)
		{
			//reload timer
			timer.setElapsed(tBlink);
			//change blink state
			bBlink=!bBlink;
		}
		//blink?
		if (bBlink)
		{
			//Show Selection Bar
			switch(choiceDate)
			{
				case RTC_CHOICE_DATE_YEAR:
					led.rectangle(0,7,12,1,Color::RED);
				break;
				case RTC_CHOICE_DATE_MONTH:
					led.rectangle(12,7,12,1,Color::RED);
				break;
				case RTC_CHOICE_DATE_DAY:
					led.rectangle(0,15,12,1,Color::RED);
				break;
				case RTC_CHOICE_DATE_DAYWEEK:
					led.rectangle(16,15,8,1,Color::RED);
				break;
			}
		}

		//update screen
		led.refresh();
		//quit check if step year
		if ((y%4)==0) dayOfMonth[2]=29; else dayOfMonth[2]=28;
		//Get kbd state
		key=kbd.getKbdState();
		//Process Key according
		switch(key)
		{
			case Kbd::UP:
				switch(choiceDate)
				{
					case RTC_CHOICE_DATE_YEAR:
						y++;
						if (y>99) y=0;
					break;
					case RTC_CHOICE_DATE_MONTH:
						m++;
						if (m>12) m=1;
					break;
					case RTC_CHOICE_DATE_DAY:
						d++;
						if (d>dayOfMonth[m]) d=1;
					break;
					case RTC_CHOICE_DATE_DAYWEEK:
						dw++;
						if (dw>7) dw=1;
					break;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				timer.delayMilliseconds(250);
			break;
			case Kbd::DOWN:
				switch(choiceDate)
				{
					case RTC_CHOICE_DATE_YEAR:
						if (y!=0) y--; else y=99;
					break;
					case RTC_CHOICE_DATE_MONTH:
						m--;
						if (m<1) m=12;
					break;
					case RTC_CHOICE_DATE_DAY:
						d--;
						if (d<1) d=dayOfMonth[m];
					break;
					case RTC_CHOICE_DATE_DAYWEEK:
						dw--;
						if (dw<1) dw=7;
					break;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				timer.delayMilliseconds(250);
			break;
			case Kbd::A:
			break;
			case Kbd::B:
				//wave.Play(WAVE_CHANNEL_MOTHER_SHIP);
				playCancel();
				kbd.waitKbdRelease();
				led.setFont(font);
				return;
			break;
			case Kbd::LEFT:
				choiceDate--;
				if (choiceDate<RTC_CHOICE_DATE_YEAR)
				{
					choiceDate=RTC_CHOICE_DATE_DAYWEEK;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::RIGHT:
				choiceDate++;
				if (choiceDate>RTC_CHOICE_DATE_DAYWEEK)
				{
					choiceDate=RTC_CHOICE_DATE_YEAR;
				}
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::ENTER:
				rtc.setDate(y,m,d,dw,true);
				playOk();
				kbd.waitKbdRelease();
				led.setFont(font);
				return;				
			break;
			case Kbd::NONE:
			break;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Set Clock Date & Time or Play Cobra Game					|
//	| @brief Name		: SetTimeOrPlayCobraGame()									|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Set Time and Date or Play Cobra Game						|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao			: Ajusta Data e Hora ou Joga o Jogo Cobra				|
//	| @brief Nome			: SetTimeOrPLayCobraGame()								|
//	| @parm Entrada [in]	:														|
//	| @parm Saida [out]		: 														|
//	| @remarks comentario	:	Ajusta Data e Hora ou Jogoa o Jogo Cobra			|
//	+-------------------------------------------------------------------------------+
static void	Settings()
{
	CharFont	font;
	Kbd			key;
	int			x=0,y=0;
	uint32_t	tBlink;
	bool		bBlink=false;

	//save font
	font=led.getFont();
	//Set New Font
	led.setFont(font);
	//clear timers
	timer.setElapsed(tBlink);
	//Main Loop
	for(;;)
	{
		//Clear Screen
		led.cls();
		//Display Icons to Select
		led.bmp(0,0,(BMP)BMP_clockSet);
		led.bmp(8,0,(BMP)BMP_Calendar);
		led.bmp(16,0,(BMP)BMP_cobra);
		led.bmp(0,8,(BMP)BMP_clock);
		led.bmp(8,8,(BMP)BMP_Clock2);
		led.bmp(16,8,(BMP)BMP_Reset);
		//Time to Blink
		if (timer.getElapsed(tBlink)>250)
		{
			//clear this timer
			timer.setElapsed(tBlink);
			//pump refresh flag
			bBlink=!bBlink;
		}
		//blink?
		if (bBlink)
		{
			//yes, draw empty rectangle at selected icon
			led.setFillMode(true);
			led.rectangle(x,y,8,8,Color::BLACK);
			led.setFillMode(false);
		}
		//Update Screen
		led.refresh();
		//Get Key
		key=kbd.getKbdState();
		//Process Key According
		switch(key)
		{
			case Kbd::A:
			case Kbd::B:
				//restore font
				led.setFont(font);
				//(missing this line until 25/02/28)
				kbd.waitKbdRelease();
				//return
				return;
			break;
			case Kbd::DOWN:
				y=8;
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::UP:
				y=0;
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::LEFT:
				x-=8;
				if (x<0) x=16;
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::RIGHT:
				x+=8;
				if (x>16) x=0;
				wave.Play(WAVE_CHANNEL_TIK_TAK);
				kbd.waitKbdRelease();
			break;
			case Kbd::ENTER:
				if (x==0  && y==0) setRTCTime();
				if (x==8  && y==0) setRTCDate();
				if (x==16 && y==0) COBRA_MainGame();
				if (x==0  && y==8) ShowClock(1);
				if (x==8  && y==8) ShowClock(2);
				if (x==16 && y==8) Reset();
			case Kbd::NONE:
			break;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Scroll Message from Right to Left at Pos Y coordinates	|
//	| @brief Name		: scrollMessage												|
//	| @parm [in]		: message message to show									|
//	|					  pos Y position message on screen							|
//	|					  speed in milliseconds										|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Desloca Mensagem da Direita para Esquerda na coordenada	|
//	|					  pos Y														|
//	| @brief Nome		: scrollMessage								                |
//	| @parm Entrada [in]: message mensagem a mostrar								|
//	|					  pos Y posicão da mensagem na tela							|
//	|					  speed em milesegundos										|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
static void	scrollMessage(const char *message,int pos,int speed=55)
{
	int w;

	w=led.getTextWidth(message);

	for(int i=24;i>=-w;i--)
	{
		led.moveTo(i,pos);
		led.putS(message);
		led.refresh();
		timer.delayMilliseconds(speed);
		if (kbd.getKbdState()==Kbd::B) 
		{
			Reset();
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Check Keys During Boot to Show Secret Messages			|
//	| @brief Name		: checkKeysDuringBoot										|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Check if Keys pressed during boot and show Secret			|
//	|					  Messages.													|
//	|					  'B' turn all screen leds on								|
//	|					  'Enter' Show My Name, child s, and wife					|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Checa Teclas durante o Boot e mostra mensagens secretas	|
//	| @brief Nome		: checkKeysDuringBoot						                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Checa se Teclas pressionadas durante o Boot e mostra	|
//	|						mensagens secretas										|
//	|						'B' Liga todas as leds da Tela							|
//	|						'Enter' Mostra meu Nome dos meus Filhos e esposa		|
//	+-------------------------------------------------------------------------------+
static void	checkKeysDuringBoot()
{
	Kbd			key;
	//Check if key pressed during boot
	//if B key pressed during boot set screen in test mode i.e. all led on

	key=kbd.getKbdState();

	switch(key)
	{
		case Kbd::ENTER:
			//message loop
			for(;;)
			{
				//show messages
				scrollMessage("Jogo Feito Por Joao Dartagnan A. Oliveira",0);
				scrollMessage("em Homenagem aos meus Filhos",8);
				scrollMessage("Dadazinho",0);
				scrollMessage("Tatiana",8);
				scrollMessage("Elizabeth",0);
				scrollMessage("Ada",8);
				scrollMessage("e minha esposa",0);
				scrollMessage("Christiane",8);
				scrollMessage("em Brasilia, Brasil na data de 20/10/2020",0);
			}
		break;
		case Kbd::B:
			//set font
			led.setFont(CharFont::FONT_3X5);
			//set fill mode on
			led.setFillMode(true);
			//turn all leds on
			led.rectangle(0,0,24,16,Color::RED);
			//refresh
			led.refresh();
			//wait key release
			kbd.waitKbdRelease();
			//do reset
			doReset();
		break;
		case Kbd::UP:
		case Kbd::DOWN:
		case Kbd::LEFT:
		case Kbd::RIGHT:
		case Kbd::A:
		case Kbd::NONE:
		break;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Main Program Entry Point of TEAD Aliens					|
//	| @brief Name		: TEAD_MainGame												|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Process Main TEAD Aliens Loop of Procedures and if Demo is|
//	|					  true a Demo o Game is Showed on Screen of if Demo is False|
//	|					  the Game will Start										|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Ponto de Entrada Principal do TEAD Aliens					|
//	| @brief Nome		: TEAD_mainGame								                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Processa o Laco Principal do Jogo TEAD Aliens e se Demo |
//	|					    for verdadeira uma demonstracao do jogo aparece-ra na	|
//	|						tela and se Demo for false o Jogo Iniciará				|
//	+-------------------------------------------------------------------------------+
void  TEAD_MainGame(bool demo)
{
	//time to show demo
	uint32_t	tShowDemo;
	//set Demo State
	_tead.bInDemo=demo;

	//Calibrate Keys
	adc.calibrate();

	//Check Keys
	checkKeysDuringBoot();

	//Initialize Game
	TEAD_initializeGame(true,true,true);	

	//rtc.SetTime(17,28,30,true);
	//wave.setToneGenStatus(true);


	if (!demo)
	{
		TEAD_showGameOverAndMessages(false);
	}
	timer.setElapsed(tShowDemo);
	//-------------------------------------------------------------------------
	//MAIN TEAD ALIENS LOOP
	//-------------------------------------------------------------------------
	for(;;)
	{
		TEAD_processMotherShipAppearAndMove();
		TEAD_processCannonMove();
		TEAD_processShipsMove();
		TEAD_processFireFromCannon();
		TEAD_processFireFromShips();
		TEAD_processShipsHitBarriers();
		TEAD_processShipsHitCannon();
		TEAD_getShipsAlives();
		TEAD_updateScreen();
		//to turn sound on or off
		if (kbd.getKbdState()==Kbd::B)
		{
			//wait kbd release
			kbd.waitKbdRelease();
			//Settings
			Settings();
			//SetTimeOrPlayCobraGame();
		}
		//check if demo end?
		if (demo)
		{
			if (timer.getElapsed(tShowDemo)>TIME_TO_SHOW_DEMO)
			{
				//set normal game
				//TEAD_initializeGame(false,false,false);
				_tead.bInDemo=false;
				return;
			}
			if (kbd.getKbdASCII()!=' ')
			{
				//set normal game
				//TEAD_initializeGame(false,false,false);
				_tead.bInDemo=false;
				return;					
			}
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Main Program Entry Point of Cobra Game					|
//	| @brief Name		: COBRA_plotNewDot											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			: Process Main TEAD Aliens Loop of Procedures and if Demo is|
//	|					  true a Demo o Game is Showed on Screen of if Demo is False|
//	|					  the Game will Start										|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Ponto de Entrada Principal do TEAD Aliens					|
//	| @brief Nome		: COBRA_ploNewDot							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario : Processa o Laco Principal do Jogo TEAD Aliens e se Demo |
//	|					    for verdadeira uma demonstracao do jogo aparece-ra na	|
//	|						tela and se Demo for false o Jogo Iniciará				|
//	+-------------------------------------------------------------------------------+
void COBRA_plotNewDot(int8_t &x,int8_t &y)
{
	int8_t	px,py;
	bool	colid;
	
	for(;;)
	{
		px=(rand()%(led.getWidth()-2))+1;
		py=(rand()%(led.getHeight()-2))+1;
		colid=false;
		for(uint8_t i=1;i<_cobra.points.Count;i++)
		{
			if (_cobra.points.coords[i].x==px && _cobra.points.coords[i].y==py)
			{
				colid=true;
				break;
			}
		}
		if (!colid)
		{
			x=px;
			y=py;
			return;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @brief Function	: Main Program Entry Point of Cobra Game					|
//	| @brief Name		: COBRA_MainGame											|
//	| @parm [in]		:															|
//	| @parm [out]		: 															|
//	| @remarks			:															|
//	+-------------------------------------------------------------------------------+
//	| @brief Funcao		: Ponto de Entrada Principal do Jogo Cobra					|
//	| @brief Nome		: COBRA_MainGame							                |
//	| @parm Entrada [in]:															|
//	| @parm Saida [out] : 															|
//	| @remarks comentario :															|
//	+-------------------------------------------------------------------------------+
void COBRA_MainGame()
{
#define		COBRA_TIME_TO_BLINK_HEAD	50
#define		COBRA_TIME_TO_EXIT			15000
#define		COBRA_DELAY_TO_EXIT			2000
#define		COBRA_TIME_TO_READ_KBD		50
#define		COBRA_TIME_TO_MOVE			200
#define		COBRA_TIME_BORDER_BLINK		50
#define		COBRA_TIME_BITE				100

	int8_t		nx,ny;
	int			px,py;
	Kbd			key;
	Dir			dir=Dir::RIGHT,dirL=Dir::RIGHT;
	uint32_t	tShift;
	uint32_t	tFlash;
	uint32_t	tRead;
	uint32_t	tExit;
	bool		bFlash=true;
	bool		bExit=false;
	int			score=0;
	CharFont	font;
	
	//Prepare sound
	wave.Prepare((WAVE)Wave_Mother_Ship_Sound,WaveChannel::CHANNEL_1);
	
	//play in
	wave.Play(WAVE_CHANNEL_CANNON_FIRE);

	//Reserve space for cobra game point
	memset(_cobra.points.coords,0,sizeof(_cobra.points.coords));
	//Generate a Randomic Number Based in Time
	srand(rtc.GetMinute()*60L+rtc.GetSecond());
	//Initial point equal 5
	_cobra.points.Count=5;
	//Initial Coordinates Center of Screen
	px=_cobra.points.coords[0].x=led.getWidth()/2;
	py=_cobra.points.coords[0].y=led.getHeight()/2;
	//Save Actual Font
	font=led.getFont();
	//set new Font
	led.setFont(CharFont::FONT_3X5);
	//Set Fill mode on
	led.setCharFillMode(true);
	//Prepare waves
	wave.Prepare((WAVE)Wave_Tik_Tak_1,WaveChannel::CHANNEL_1);
	wave.Prepare((WAVE)Wave_Ship_Explosion,WaveChannel::CHANNEL_2);
	wave.Prepare((WAVE)Wave_Canno_Fire,WaveChannel::CHANNEL_3);
	wave.Prepare((WAVE)Wave_Mother_Ship_Sound,WaveChannel::CHANNEL_4);
	//plot new dot
	COBRA_plotNewDot(nx,ny);
	//Initialize Timers

	timer.setElapsed(tShift);
	timer.setElapsed(tFlash);
	timer.setElapsed(tExit);

	//Cobra Main Loop
	for(;;)	
	{
		//Clear screen
		led.cls();
		//Draw Screen Border
		led.rectangle(0,0,led.getWidth(),led.getHeight());	
		//Draw Cobra Points
		for(uint8_t i=0;i<_cobra.points.Count;i++)
		{
			led.setPixel(_cobra.points.coords[i].x,_cobra.points.coords[i].y);
		}
		//Check if time to flash cobra head
		if (timer.getElapsed(tFlash)>COBRA_TIME_TO_BLINK_HEAD)
		{
			timer.setElapsed(tFlash);
			bFlash=!bFlash;
		}
		//Blink Cobra Head
		if (bFlash)
		{
			led.setPixel(nx,ny);
		}
		//Exit from Cobra Game if none Key pressed by a time or bExit is true
		if (timer.getElapsed(tExit)>COBRA_TIME_TO_EXIT || bExit)
		{
			//wait key release
			kbd.waitKbdRelease();
			for(;;)
			{
				//clear screen
				led.cls();
				//set message coordinates
				led.moveTo(2,0);
				//draw exit
				led.putS("SCORE");
				//set score coordinates
				led.moveTo(2,9);
				sprintf(_tead.bf,"%5d",score);
				led.putS(_tead.bf);
				//refresh screen
				led.refresh();
				//time to exit
				if (kbd.getKbdState()==Kbd::B || (kbd.getKbdState()==Kbd::ENTER))
				{
					//Play exit
					wave.Play(WaveChannel::CHANNEL_4);
					//restore font
					led.setFont(font);
					//wait key release
					kbd.waitKbdRelease();
					return;
				}
				//timer
				timer.delayMilliseconds(20);
			} 
		}
		//Time to Read Keyboard and choose movements?
		if (timer.getElapsed(tRead)>COBRA_TIME_TO_READ_KBD)
		{
			//realod timer
			timer.setElapsed(tRead);
			//read keyboard
			key=kbd.getKbdState();
			//UP is pressed?
			if ((uint8_t)key == (uint8_t)Kbd::UP)
			{
				if (dirL!=Dir::DOWN) dir=Dir::UP;
				//clear time to exit
				timer.setElapsed(tExit);
			}
			//DONW is pressed?
			if ((uint8_t)key == (uint8_t)Kbd::DOWN)
			{
				if (dirL!=Dir::UP) dir=Dir::DOWN;
				//clear time to exit
				timer.setElapsed(tExit);
			}
			//LEFT is pressed?
			if ((uint8_t)key == (uint8_t)Kbd::LEFT)
			{
				if (dirL!=Dir::RIGHT) dir=Dir::LEFT;
				//clear time to exit
				timer.setElapsed(tExit);
			}
			//RIGHT is pressed?
			if ((uint8_t)key == (uint8_t)Kbd::RIGHT)
			{
				if (dirL!=Dir::LEFT) dir=Dir::RIGHT;
				//clear time to exit
				timer.setElapsed(tExit);
			}
			//B pressed?
			if ((uint8_t)key == (uint8_t)Kbd::B)
			{
				//exit from Cobra Game
				bExit=true;
			}
			//update last direction if diferent of previous direction
			if (dir!=dirL)
			{
				dirL=dir;
				wave.Play(WaveChannel::CHANNEL_1);
			}
		}
		//Time to Move Cobra?
		if (timer.getElapsed(tShift)>COBRA_TIME_TO_MOVE)
		{
			//clear time
			timer.setElapsed(tShift);

			//Which direction to go?
			switch(dir)
			{
				//UP?
				case Dir::UP:
					//y--
					py--;
					//reach top border
					if (py<1)
					{
						//set to bottom border
						py=led.getHeight()-2;
						//play
						wave.Play(WaveChannel::CHANNEL_3);
					}
				break;
				//DOWN?
				case Dir::DOWN:
					//y++
					py++;
					//reach bottom border?
					if (py>led.getHeight()-2)
					{
						//set top border
						py=1;
						//play
						wave.Play(WaveChannel::CHANNEL_3);
					}
				break;
				//LEFT?
				case Dir::LEFT:
					//x--
					px--;
					//reach border left
					if (px<1)
					{
						//set boarder right
						px=led.getWidth()-2;
						//play
						wave.Play(WaveChannel::CHANNEL_3);
					}
				break;
				//RIGHT?
				case Dir::RIGHT:
					//x++
					px++;
					//reach right border?
					if (px>led.getWidth()-2)
					{
						//yes, set border left
						px=1;
						//play
						wave.Play(WaveChannel::CHANNEL_3);
					}
				break;
			}
			//Move all Cobra Points
			for(uint8_t i=_cobra.points.Count-1;i>0;i--)
			{
				_cobra.points.coords[i]=_cobra.points.coords[i-1];
			}
			//Set new Point
			_cobra.points.coords[0].x=px;
			_cobra.points.coords[0].y=py;
			//
			if (px==nx && py==ny)
			{
				wave.Play(WaveChannel::CHANNEL_2);
				_cobra.points.Count++;
				if (_cobra.points.Count>COBRA_MAX_POINTS)
				{
					//yes, fim de jogo
				}
				COBRA_plotNewDot(nx,ny);
				score+=5;
				sprintf(_tead.bf,"%04d",score);
				for(uint8_t i=0;i<2;i++)
				{
					//Flash Border if i eat dot
					led.setPen(Pen::DOTS1);
					led.rectangle(0,0,24,16);
					led.setPixel(_cobra.points.coords[0].x,_cobra.points.coords[0].y);
					//update screen
					led.refresh();
					wave.Play(WaveChannel::CHANNEL_2);
					timer.delayMilliseconds(COBRA_TIME_BORDER_BLINK);
					led.setPen(Pen::DOTS2);
					led.rectangle(0,0,24,16);
					led.setPixel(_cobra.points.coords[0].x,_cobra.points.coords[0].y,Color::BLACK);
					//update screen
					led.refresh();
					timer.delayMilliseconds(COBRA_TIME_BORDER_BLINK);
				}
				led.setPen(Pen::FULL);
			}
			//check if cobra bite yourself
			for(uint8_t i=1;i<_cobra.points.Count;i++)
			{
				//bite?
				if (_cobra.points.coords[0].x==_cobra.points.coords[i].x && 
				    _cobra.points.coords[0].y==_cobra.points.coords[i].y)
				{
					//set fill mode true
					led.setFillMode(true);
					//flash bite point 5 times
					for(uint8_t j=0;j<5;j++)
					{
						//mark bit point
						led.setPixel(_cobra.points.coords[0].x,_cobra.points.coords[0].y);
						led.circle(_cobra.points.coords[i].x,_cobra.points.coords[i].y,2);
						led.refresh();
						wave.Play(WaveChannel::CHANNEL_3);
						timer.delayMilliseconds(100);
						led.setPixel(_cobra.points.coords[0].x,_cobra.points.coords[0].y,Color::BLACK);
						led.circle(_cobra.points.coords[i].x,_cobra.points.coords[i].y,2,Color::BLACK);
						led.refresh();
						timer.delayMilliseconds(COBRA_TIME_BITE);
					}
					//set fill mode to false
					led.setFillMode(false);
					//set exit
					bExit=true;
					//return;
				}
			}
		}
		//refresh screen
		led.refresh();
	}
}

