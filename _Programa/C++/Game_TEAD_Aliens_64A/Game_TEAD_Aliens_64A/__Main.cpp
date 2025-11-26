/*
 /////////////////////////////////////////////////////////////////////////////////////
 //        ___  ___      _        ______											//
 //        |  \/  |     (_)       | ___ \											//
 //        | .  . | __ _ _ _ __   | |_/ / __ ___   __ _ _ __ __ _ _ __ ___			//
 //        | |\/| |/ _` | | '_ \  |  __/ '__/ _ \ / _` | '__/ _` | '_ ` _ \			//
 //        | |  | | (_| | | | | | | |  | | | (_) | (_| | | | (_| | | | | | |		//
 //        \_|  |_/\__,_|_|_| |_| \_|  |_|  \___/ \__, |_|  \__,_|_| |_| |_|		//
 //                                                __/ |							//
 //                                               |___/								//
 /////////////////////////////////////////////////////////////////////////////////////
--------------------------------- Main Program (tab 4) C++ ---------------------------
*/

/**
**************************************************************************************
*@brief   username nepermath
*@brief   machine NEPERI75
*@file    Tead Aliens 64A game 
*@Version 3.00 
*@author  Joao Dartagnan A. Oliveira
*@date    29/01/2021
*@brief 
*@copyright GNU Public License.
**************************************************************************************
*/

/*
======================================================================================
@HARDWARE: ATMEGA64A 16MHZ 
@OBSERVAÇÃO:
======================================================================================
______                                      _
| ___ \                                    | |
| |_/ / __ ___   __ _ _ __ __ _ _ __ ___   | |     ___   __ _
|  __/ '__/ _ \ / _` | '__/ _` | '_ ` _ \  | |    / _ \ / _` |
| |  | | | (_) | (_| | | | (_| | | | | | | | |___| (_) | (_| |
\_|  |_|  \___/ \__, |_|  \__,_|_| |_| |_| \_____/\___/ \__, |
                 __/ |                                   __/ |
                 |___/                                   |___/
======================================================================================
DATE		TIME		DESCRIPTION
__________	_____		______________________________________________________________
20/10/2020	19:44		(feito)Projeto iniciado
09/05/2022	23:01		mudei no arquivo _mathI.cpp o calculo na class LineDDA::getNextPoint
28/02/2025	13:43		ultima correcao waitRelease a main setting
						return when clock is set
						return when date is set
			14:10		adicionei waves play Ok and Cancel
						(these comments are incomplete)
*/

/*
+--------------------------------------+
|        AVR/GNU C++ COMPILER	       |
+--------------------------------------+

Symbols		    = -DF_CPU=16000000L
Optimization	= -Os
Miscellaneous	= -std=gnu++11
use eeprom		= yes
*/

/*
+--------------------------------------+
|        HARDWARE DEPENDENT INCLUDES   |
+--------------------------------------+
*/
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include <avr/sleep.h>
#include <util/delay.h>

/*
+--------------------------------------+
|        C LIBRARY INCLUDES		       |
+--------------------------------------+
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdarg.h>

/*
+--------------------------------------+
|        LIBRARY INCLUDES	           |
+--------------------------------------+
*/

//using namespace Neperino;

#include "_TEAD_Aliens.h"

/*
+--------------------------------------+
|        RESOURCES INCLUDES	           |
+--------------------------------------+
*/


int main()
{	
	//Enable Global Interrupts
	sei();
	//main game loop

	for(;;)
	{
		TEAD_MainGame(false);
	}	
}