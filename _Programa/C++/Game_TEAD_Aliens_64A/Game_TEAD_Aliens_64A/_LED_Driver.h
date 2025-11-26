/*
	//////////////////////////////////////////////////////////////////////////////////////////
 		  _      ___________  ______      _
 		 | |    |  ___|  _  \ |  _  \    (_)
 		 | |    | |__ | | | | | | | |_ __ ___   _____ _ __
 		 | |    |  __|| | | | | | | | '__| \ \ / / _ \ '__|
 		 | |____| |___| |/ /  | |/ /| |  | |\ V /  __/ |
 		 \_____/\____/|___/   |___/ |_|  |_| \_/ \___|_|
 		 
    //////////////////////////////////////////////////////////////////////////////////////////
    ---------------------------------- HEADER FILE (tab 4)-----------------------------------
*/


#ifndef _LED_DRIVER_H_
#define _LED_DRIVER_H_

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
#include <string.h>
#include <stdio.h>
/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_Timer.h"
/*
 +--------------------------------------+
 |        DEFINES						|
 +--------------------------------------+
*/
#define _LED_MATRIX_ROWS	16
#define _LED_MATRIX_COLS	24
#define _LED_CHAR_WIDTH		6
#define _LED_CHAR_HEIGHT	8
#define _LED_CHAR_LITTLE_WIDTH		4
#define _LED_CHAR_LITTLE_HEIGHT		6
/*
 +--------------------------------------+
 |        PORTS AND PIN DEFINITIONS	    |
 +--------------------------------------+
*/

#define	_LED_CPU_PORT_OUTPUT	PORTD
#define _LED_CPU_PORT_DIR		DDRD
#define _LED_CPU_PORT_INPUT		PIND

#define _LED_CPU_PIN			1

#define _LED_ROW_18_PORT_OUTPUT	PORTA
#define _LED_ROW_18_PORT_DIR	DDRA
#define _LED_ROW_18_PORT_INPUT	PINA

#define _LED_ROW_916_PORT_OUTPUT	PORTC	
#define _LED_ROW_916_PORT_DIR		DDRC	
#define _LED_ROW_916_PORT_INPUT		PINC

#define _LED_ROW_1_PIN			0
#define _LED_ROW_2_PIN			1
#define _LED_ROW_3_PIN			2
#define _LED_ROW_4_PIN			3
#define _LED_ROW_5_PIN			4
#define _LED_ROW_6_PIN			5
#define _LED_ROW_7_PIN			6
#define _LED_ROW_8_PIN			7

#define _LED_ROW_9_PIN			0
#define _LED_ROW_10_PIN			1
#define _LED_ROW_11_PIN			3
#define _LED_ROW_12_PIN			2
#define _LED_ROW_13_PIN			4
#define _LED_ROW_14_PIN			5
#define _LED_ROW_15_PIN			6
#define _LED_ROW_16_PIN			7

#define _LED_SHIFT_PORT_OUTPUT	PORTD
#define _LED_SHIFT_PORT_DIR		DDRD
#define _LED_SHIFT_PORT_INPUT	PIND

#define _LED_SHIFT_DATA_PIN			4
#define _LED_SHIFT_CLOCK_PIN		5
#define _LED_SHIFT_LOAD_PIN			6

/*
 +--------------------------------------+
 |        TYPEDEF CLASS DEFINITIONS		|
 +--------------------------------------+
*/

//------------------------------------------------------------
//Point
//------------------------------------------------------------
template <typename T>
struct Point 
{
	T x,y;
};
//------------------------------------------------------------
//Window
//------------------------------------------------------------
template<typename T>
struct Window
{
	T xi,yi;
	T xf,yf;	
};
//------------------------------------------------------------
//Rectangle
//------------------------------------------------------------
template<typename T>
struct Rect
{
	T x,y;
	T width,height;	
};
//------------------------------------------------------------
//COLORS
//------------------------------------------------------------
typedef enum class Color:uint8_t
{
	BLACK=0,
	RED=1
}Color;
//------------------------------------------------------------
//REFRESH MODES
//------------------------------------------------------------
typedef enum class RefreshMode:uint8_t
{
	AUTOMATIC,
	MANUAL
}RefreshMode;					 
//------------------------------------------------------------
//PENS
//------------------------------------------------------------
typedef enum class enum_Pen
{
	FULL		=0xff,
	DOTS1		=0Xaa,
	DOTS2		=0X55,
	DOT			=0x10,
	DOT_DOT		=0x11,
	DOT_DOT_2	=0x33,
	DOT_DOT_3	=0x77,
	DASH		=0x3c,
	DASH_DOT	=0x72,
	BLACK		=0x00
}Pen;
//------------------------------------------------------------
//CHARACTER SIZE
//------------------------------------------------------------
typedef enum class CharFont:uint8_t
{
	FONT_3X5=1,
	FONT_5X8,
	FONT_5X16,
	FONT_10X16,
}CharFont;
//------------------------------------------------------------
//BMP 
//------------------------------------------------------------
typedef const uint8_t* BMP;
/*
        +-------------------------------------------------------+
        |        CLASS			LED			                    |
        +-------------------------------------------------------+
        | @PURPOSE      : TO CONTROL DISPLAY MATRIX 8X8 2088BS	|
        | @OBSERVATIONS :										|
        +-------------------------------------------------------+
*/


class class_LED
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
		/************************************************************************/
		/* Initialize LED Driver                                                */
		/************************************************************************/
		void			Initialize(void);
		/************************************************************************/
		/* UnInitialize LED Driver                                              */
		/************************************************************************/
		void			UnInitialize(void);
		/************************************************************************/
		/* Clear Display Matrix Rows                                            */
		/************************************************************************/
		static void		clearRows(void);
		/************************************************************************/
		/* Draw 8 symmetric points at center xx,yy                              */
		/************************************************************************/
		static void		plotP8(int xx,int yy,int x,int y,Color color);
        /*
         +--------------------------------------+
         |        PUBLIC FUNCTIONS		        |
         +--------------------------------------+
        */
public:
	
        /************************************************************************/
        /* Constructor                                                          */
        /************************************************************************/
        class_LED(void);
		/************************************************************************/
		/* #2 Constructor with Refresh Mode                                     */
		/************************************************************************/
		class_LED(RefreshMode refreshMode);
		/************************************************************************/
		/* Destructor                                                           */
		/************************************************************************/
		~class_LED(void);
		/************************************************************************/
		/* LED Process                                                          */
		/************************************************************************/
		static void process(void);
		/************************************************************************/
		/* Set LED CPU State true=ON false=OFF                                  */
		/************************************************************************/
		static void setCPUState(bool state);
		/************************************************************************/
		/* Swap State of LED CPU if on turn off and vice-versa                  */
		/************************************************************************/
		static void swapCPUState(void);
		/************************************************************************/
		/* Set LED Matrix columns n on                                          */
		/************************************************************************/
		static void setColumn(uint8_t column);
		/************************************************************************/
		/* Set LED Matrix buffer directly                                       */
		/************************************************************************/
		static void setBuffer(uint8_t address,uint16_t data,bool lowerDisplay);
		/************************************************************************/
		/* Clear Screen                                                         */
		/************************************************************************/
		static void cls(bool setAllLEDs=false);
		/************************************************************************/
		/* Set Pixel at coordinates x,y with pixel=0 OFF !=0 ON                 */
		/************************************************************************/
		static void setPixel(int x,int y,Color color=Color::RED);
		/************************************************************************/
		/* Get Pixel at coordinates x,y if outside screen return black color    */
		/************************************************************************/
		static Color getPixel(int x,int y);
		/************************************************************************/
		/* get screen width in pixels                                           */
		/************************************************************************/
		static inline int getWidth(void) {return _LED_MATRIX_COLS;};
		/************************************************************************/
		/* get screen height in pixels                                          */
		/************************************************************************/
		static inline int getHeight(void) {return _LED_MATRIX_ROWS;};
		/************************************************************************/
		/* Set Refresh Mode                                                     */
		/************************************************************************/
		static void setRefreshMode(RefreshMode refreshMode=RefreshMode::AUTOMATIC);
		/************************************************************************/
		/* Refresh Screen if in refresh mode is manual                          */
		/************************************************************************/
		static void refresh(void);
		/************************************************************************/
		/* Set Fill Mode ON=true, OFF=false                                     */
		/************************************************************************/
		static void setFillMode(bool fillMode=true);
		/************************************************************************/
		/* Get Fill Mode                                                        */
		/************************************************************************/
		static bool getFillMode(void);
		/************************************************************************/
		/* Set Fill Character ON=true, OFF=false                                */
		/************************************************************************/
		static void setCharFillMode(bool charFillMode=true);
		/************************************************************************/
		/* Set Pen                                                              */
		/************************************************************************/
		static void setPen(Pen pen);
		/************************************************************************/
		/*  Draw a Line from point(xi,yi) to Point(xf,yf) with color            */
		/************************************************************************/
		static void line(int xi,int yi,int xf,int yf,Color color=Color::RED);
		static void line(Window<int> window,Color color=Color::RED);
		/************************************************************************/
		/* Draw a Line From the last point drawed                               */
		/************************************************************************/
		static void lineTo(int x,int y,Color color=Color::RED);
		static void lineTo(Point<int> point,Color color=Color::RED);
		/************************************************************************/
		/* Move graph cursor to a Point x,y                                     */
		/************************************************************************/
		static void moveTo(int x,int y);
		static void moveTo(Point<int> point);
		/************************************************************************/
		/* Draw Circle at coordinates x,y with radius and color                 */
		/************************************************************************/
		static void circle(int x,int y,int radius,Color color=Color::RED);
		static void circle(Point<int> point,int radius,Color color=Color::RED);
		/************************************************************************/
		/* Rectangle at coordinates (xi,yi) to (xf,yf) with color               */
		/************************************************************************/
		static void rectangle(int xi,int yi,int width,int height,Color color=Color::RED);
		static void rectangle(Rect<int> rect,Color color=Color::RED);
		/************************************************************************/
		/* Get Character Width                                                  */
		/************************************************************************/
		static int getCharWidth(void);
		/************************************************************************/
		/* Get Character Height                                                 */
		/************************************************************************/
		static int getCharHeight(void);
		/************************************************************************/
		/* Set Character Font                                                   */
		/************************************************************************/
		static void setFont(CharFont charFont);
		/************************************************************************/
		/* Get Character Font                                                   */
		/************************************************************************/
		static CharFont getFont(void);
		/************************************************************************/
		/* Put character on screen at coordinates set by moveTo                 */
		/************************************************************************/
		static void putC(char c,Color color=Color::RED);
		/************************************************************************/
		/* Put String on screen at coordinates set by moveto                    */
		/************************************************************************/
		static void putS(const char *charString,Color color=Color::RED);
		/************************************************************************/
		/* Put String from FLASH on LED Panel                                    */
		/************************************************************************/
		static void putSF(const char *charInFLASH);		
		/************************************************************************/
		/* Get BMP Width in pixels                                              */
		/************************************************************************/
		static int getBMPWidth(BMP bmpInFlash);
		/************************************************************************/
		/* Get BMP Height in pixels                                             */
		/************************************************************************/
		static int getBMPHeight(BMP bmpInFlash);
		/************************************************************************/
		/* Draw BMP                                                             */
		/************************************************************************/
		static void bmp(int x,int y,BMP bmpInFlash,bool invertColor=false);
		static void bmp(Point<int> point,BMP bmpInFlash,bool invertColor=false);
		/************************************************************************/
		/* Get Actual Text Width                                                */
		/************************************************************************/
		int16_t getTextWidth(const char *textString);
		/************************************************************************/
		/* Get Actual Text Width in pgm_memory                                  */
		/************************************************************************/
		int16_t	getTextWidthP(const char *textStringInFlash);
		/************************************************************************/
		/* Get Actual Text Height                                               */
		/************************************************************************/
		int16_t	getTextHeight(const char *textString);
		/************************************************************************/
		/* Get Actual Text Height in pgm_memory                                 */
		/************************************************************************/
		int16_t	getTextHeightP(const char *textStringInFlash);
		/************************************************************************/
		/* Set View Window for start coordinates xi,yi to end coordinates xf,yf */
		/* xi must be lower than xf and yi must be lower than yf				*/
		/************************************************************************/
		void setViewWindow(int xi,int yi,int xf,int yf);
		void setViewWindow(Window<int> window);
		/************************************************************************/
		/* Get Actual View Window                                               */
		/************************************************************************/
		Window<int> getViewWindow(void);
};

#endif