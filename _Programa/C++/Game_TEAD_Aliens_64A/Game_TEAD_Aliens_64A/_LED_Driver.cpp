/*
 /////////////////////////////////////////////////////////////////////////////////////////
			 _      ___________  ______      _
			| |    |  ___|  _  \ |  _  \    (_)
			| |    | |__ | | | | | | | |_ __ ___   _____ _ __
			| |    |  __|| | | | | | | | '__| \ \ / / _ \ '__|
			| |____| |___| |/ /  | |/ /| |  | |\ V /  __/ |
			\_____/\____/|___/   |___/ |_|  |_| \_/ \___|_|
			
 /////////////////////////////////////////////////////////////////////////////////////////
  --------------------------------- IO C++ File (tab 4) ----------------------------------
  
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_LED_Driver.h"

/*
 +--------------------------------------+
 |        ASCII TABLE				    |
 +--------------------------------------+
*/
#include "_ASCII_Table_3x5.h"
#include "_ASCII_Table_5x8.h"
/*
 +--------------------------------------+
 |        LOCAL STRUCTURES			    |
 +--------------------------------------+
*/
//LED structure
struct 
{
	bool			fillMode;							//actual false if fill on
	bool			charFill;							//actual true for character fill
	Pen				pen;								//actual Pen
	CharFont		charFont;							//Character font type
	Point<int>		coords;								//last drawer coordinates
	Window<int>		window;
	uint8_t			bufferH[_LED_MATRIX_COLS];			//pixels buffer upper display
	uint8_t			bufferL[_LED_MATRIX_COLS];			//pixels buffer lower display
	uint8_t			refreshBufferH[_LED_MATRIX_COLS];	//pixels when use refresh manual upper display
	uint8_t			refreshBufferL[_LED_MATRIX_COLS];	//pixels when use refresh manual lower display
	uint8_t			bit_mask_L[8];	//bit mask lower
	uint8_t			bit_mask_H[8];	//bit mask upper
	void			(*ReturnCallBack)();					//return callback for time object
	RefreshMode		refreshMode;							//Refresh Mode
	class_Timer		timer;
}_led;
/*
        +-----------------------------------------------+
        |       PRIVATE @FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Initialize LED Drive					                            |
//	| @NAME    :  Initialize                    		                            |
//	| @INPUT   :																	|
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void    class_LED::Initialize()
{
	//Save SREG
	uint8_t sreg=SREG;
	
	//disable interrupts
	cli();
	//Set LED CPU Port Output disable
	_LED_CPU_PORT_OUTPUT|=(1<<_LED_CPU_PIN);
	_LED_CPU_PORT_DIR   |=(1<<_LED_CPU_PIN);
	//Set Rows 1..16 disable
	_LED_ROW_18_PORT_OUTPUT&=~((1<<_LED_ROW_1_PIN)|(1<<_LED_ROW_2_PIN)|(1<<_LED_ROW_3_PIN)|(1<<_LED_ROW_4_PIN)|\
							   (1<<_LED_ROW_5_PIN)|(1<<_LED_ROW_6_PIN)|(1<<_LED_ROW_7_PIN)|(1<<_LED_ROW_8_PIN));
	_LED_ROW_18_PORT_DIR   |= ((1<<_LED_ROW_1_PIN)|(1<<_LED_ROW_2_PIN)|(1<<_LED_ROW_3_PIN)|(1<<_LED_ROW_4_PIN)|\
							   (1<<_LED_ROW_5_PIN)|(1<<_LED_ROW_6_PIN)|(1<<_LED_ROW_7_PIN)|(1<<_LED_ROW_8_PIN));
	_LED_ROW_916_PORT_OUTPUT&=~((1<<_LED_ROW_9_PIN)|(1<<_LED_ROW_10_PIN)|(1<<_LED_ROW_11_PIN)|(1<<_LED_ROW_12_PIN)|\
							    (1<<_LED_ROW_13_PIN)|(1<<_LED_ROW_14_PIN)|(1<<_LED_ROW_15_PIN)|(1<<_LED_ROW_16_PIN));
	_LED_ROW_916_PORT_DIR   |= ((1<<_LED_ROW_9_PIN)|(1<<_LED_ROW_10_PIN)|(1<<_LED_ROW_11_PIN)|(1<<_LED_ROW_12_PIN)|\
							    (1<<_LED_ROW_13_PIN)|(1<<_LED_ROW_14_PIN)|(1<<_LED_ROW_15_PIN)|(1<<_LED_ROW_16_PIN));
	//set shift Clock = low
	_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_CLOCK_PIN);
	_LED_SHIFT_PORT_DIR   |= (1<<_LED_SHIFT_CLOCK_PIN);
	//set shift LOAD = low
	_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_LOAD_PIN);
	_LED_SHIFT_PORT_DIR   |= (1<<_LED_SHIFT_LOAD_PIN);
	//set shift DATA = low
	_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_DATA_PIN);
	_LED_SHIFT_PORT_DIR   |= (1<<_LED_SHIFT_DATA_PIN);
	//
	//test
	//_LED_ROW_18_PORT_OUTPUT|=0xff;//(1<<_LED_ROW_1_PIN)|(1<<_LED_ROW_2_PIN);
	//_LED_ROW_916_PORT_OUTPUT|=0xff;//(1<<_LED_ROW_9_PIN);
	//set windows
	_led.window={.xi=0,.yi=0,.xf=_LED_MATRIX_COLS-1,.yf=_LED_MATRIX_ROWS-1};
	//set refresh mode
	_led.refreshMode=RefreshMode::AUTOMATIC;
	//Set Normal char size
	_led.charFont=CharFont::FONT_5X8;
	//set Fill
	_led.fillMode=false;
	//set Pen
	_led.pen=Pen::FULL;
	//Set Char Fill true
	_led.charFill=true;
	//set bit mask
	for(uint8_t i=0;i<8;i++)
	{
		_led.bit_mask_L[i]=(0x80>>i);
		_led.bit_mask_H[i]=(0x80>>i);
	}
	//correction on lower display
	_led.bit_mask_L[4]=0x04;
	_led.bit_mask_L[5]=0x08;
	//clear screen
	cls();
	//get old timer callback
	_led.ReturnCallBack=_led.timer.getHandleCallBack();
	//Add Call backs
	_led.timer.setHandleCallBack(process);	
	//restore SREG state
	SREG=sreg;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  UnInitialize ZERO Cross Drive			                            |
//	| @NAME    :  UnInitialize                      	                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :  interrupts are disabled and restored				                |
//	+-------------------------------------------------------------------------------+
void    class_LED::UnInitialize()
{
	//Save SREG
	uint8_t sreg=SREG;
	//disable interrupts
	cli();
	//Set LED CPU Port@INPUT high z
	_LED_CPU_PORT_OUTPUT&=~(1<<_LED_CPU_PIN);
	_LED_CPU_PORT_DIR   &=~(1<<_LED_CPU_PIN);	
	//restore SREG
	SREG=sreg;

}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  clear Rows														|
//	| @NAME    :                       												|
//	| @INPUT   :																	|
//	| @OUTPUT  :  																	|
//	| @REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
void class_LED::clearRows()
{
	//Set Rows 1..16 disable
	_LED_ROW_18_PORT_OUTPUT &=~((1<<_LED_ROW_1_PIN)|(1<<_LED_ROW_2_PIN)|(1<<_LED_ROW_3_PIN)|(1<<_LED_ROW_4_PIN)|\
								(1<<_LED_ROW_5_PIN)|(1<<_LED_ROW_6_PIN)|(1<<_LED_ROW_7_PIN)|(1<<_LED_ROW_8_PIN));
	_LED_ROW_916_PORT_OUTPUT&=~((1<<_LED_ROW_9_PIN)|(1<<_LED_ROW_10_PIN)|(1<<_LED_ROW_11_PIN)|(1<<_LED_ROW_12_PIN)|\
								(1<<_LED_ROW_13_PIN)|(1<<_LED_ROW_14_PIN)|(1<<_LED_ROW_15_PIN)|(1<<_LED_ROW_16_PIN));
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw 8 symetric points												|
//	| @NAME    : plotP8                       										|
//	| @INPUT   : xx,yy center x,y coords											|
//	| @OUTPUT  :  																	|
//	| @REMARKS :  																	|
//	+-------------------------------------------------------------------------------+
void class_LED::plotP8(int xx,int yy,int x,int y,Color color)
{
	if (_led.fillMode)
	{
		line(xx-x,yy-y,xx+x,yy-y,color);
		line(xx-x,yy+y,xx+x,yy+y,color);
		line(xx-y,yy-x,xx+y,yy-x,color);
		line(xx-y,yy+x,xx+y,yy+x,color);
	}
	else
	{
		setPixel(xx+y,yy-x,color);
		setPixel(xx+x,yy-y,color);
		setPixel(xx-x,yy-y,color);
		setPixel(xx-y,yy-x,color);
		setPixel(xx-y,yy+x,color);
		setPixel(xx-x,yy+y,color);
		setPixel(xx+x,yy+y,color);
		setPixel(xx+y,yy+x,color);		
	}
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
class_LED::class_LED()
{
	static bool initialize=false;

	//Initialize PID
	if (initialize==false)
	{
		initialize=true;
		Initialize();
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor #2 Initialize with refresh Mode                       |
//	| @NAME    :								  		                            |
//	| @INPUT   :  Refresh Mode                                                      |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_LED::class_LED(RefreshMode	refreshMode)
{
	static bool initialize=false;

	//Initialize PID
	if (initialize==false)
	{
		initialize=true;
		Initialize();
		//set refresh mode
		_led.refreshMode=refreshMode;
	}
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_LED::~class_LED()
{
	//Initialize PID
	UnInitialize();
}
/*
        +-----------------------------------------------+
        |       PUBLIC @FUNCTIONS IMPLEMENTATION         |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  process LED Matrix		                                        |
//	| @NAME    :  process															|
//	| @INPUT   :																	|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::process()
{
	static uint8_t column;
	uint16_t	dataRowL,dataRowH;
	
	//clear rows and columns
	clearRows();
	setColumn(0);
	//pump column
	column++;
	if (column>_LED_MATRIX_COLS-1) column=0;
	//load pixels from buffer  or refresh buffer
	if (_led.refreshMode==RefreshMode::AUTOMATIC)
	{
		dataRowL=_led.bufferL[column];
		dataRowH=_led.bufferH[column];
	}
	else
	{
		dataRowL=_led.refreshBufferL[column];
		dataRowH=_led.refreshBufferH[column];
	}
	//set rows
	_LED_ROW_18_PORT_OUTPUT=dataRowH;
	_LED_ROW_916_PORT_OUTPUT=dataRowL;
	//set columns
	setColumn(column+1);
	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Buffer data directly											|
//	| @NAME    :  setBuffer															|
//	| @INPUT   :  address range 0..23, data bits 0..15                              |
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setBuffer(uint8_t address,uint16_t data,bool lowerDisplay)
{
	//return if invalid address
	if (address>_LED_MATRIX_COLS-1) return;
	//lower display?
	if (lowerDisplay)
	{
		//set data to lower display
		_led.bufferL[address]=data;
	}
	else
	{		//set data to upper display
		_led.bufferH[address]=data;		
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set LED CPU State			                                        |
//	| @NAME    :  setCPUstate								                        |
//	| @INPUT   :  state true=ON false=OFF                                           |
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setCPUState(bool state)
{
	if (state)
		_LED_CPU_PORT_OUTPUT&=~(1<<_LED_CPU_PIN);
	else
		_LED_CPU_PORT_OUTPUT|= (1<<_LED_CPU_PIN);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Swap LED CPU State			                                    |
//	| @NAME    :  swapCPUState								                        |
//	| @INPUT   :  if state is ON then OFF and vice-versa                            |
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::swapCPUState()
{
	if (_LED_CPU_PORT_OUTPUT & (1<<_LED_CPU_PIN))
	{
		_LED_CPU_PORT_OUTPUT&=~(1<<_LED_CPU_PIN);
	}
	else
	{
		_LED_CPU_PORT_OUTPUT|= (1<<_LED_CPU_PIN);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Column					                                    |
//	| @NAME    :  setColumn									                        |
//	| @INPUT   :  column number 1..16												|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setColumn(uint8_t column)
{
	if (column>=1 && column<=24)
	{
		column--;
		column=(_LED_MATRIX_COLS-1)-column;
		for(uint8_t i=0;i<_LED_MATRIX_COLS;i++)
		{
			if (i==column)
			{
				_LED_SHIFT_PORT_OUTPUT|= (1<<_LED_SHIFT_DATA_PIN);
			}
			else
			{
				_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_DATA_PIN);	
			}
			//pulse clock
			_LED_SHIFT_PORT_OUTPUT|=(1<<_LED_SHIFT_CLOCK_PIN);
			_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_CLOCK_PIN);
		}
	}
	else
	{
		//clear columns
		_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_DATA_PIN);
		for(uint8_t i=0;i<_LED_MATRIX_COLS;i++)
		{
			//pulse clock
			_LED_SHIFT_PORT_OUTPUT|=(1<<_LED_SHIFT_CLOCK_PIN);
			_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_CLOCK_PIN);
		}		
	}
	//load
	_LED_SHIFT_PORT_OUTPUT|=(1<<_LED_SHIFT_LOAD_PIN);
	//asm("nop");
	_LED_SHIFT_PORT_OUTPUT&=~(1<<_LED_SHIFT_LOAD_PIN);
	//asm("nop");
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  clear Screen					                                    |
//	| @NAME    :  cls																|
//	| @INPUT   :  pattern bits 														|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::cls(bool setAllLEDS)
{
	_led.coords={.x=0,.y=0};
	//set all leds?
	if (setAllLEDS)
	{
		memset(_led.bufferL,0xff,sizeof(_led.bufferL));
		memset(_led.bufferH,0xff,sizeof(_led.bufferH));
	}
	else
	{
		memset(_led.bufferL,0x00,sizeof(_led.bufferL));
		memset(_led.bufferH,0x00,sizeof(_led.bufferH));
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Char Width				                                    |
//	| @NAME    :  getCharWidth														|
//	| @INPUT   :   																	|
//	| @OUTPUT  : width in pixels									                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_LED::getCharWidth()
{
	switch(_led.charFont)
	{
		case CharFont::FONT_5X8:
			return _LED_CHAR_WIDTH;
		case CharFont::FONT_5X16:
			return _LED_CHAR_WIDTH;
		case CharFont::FONT_10X16:
			return _LED_CHAR_WIDTH*2;
		case CharFont::FONT_3X5:
			return _LED_CHAR_LITTLE_WIDTH;
		default:
			return 0;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Char Height				                                    |
//	| @NAME    :  getCharHeight														|
//	| @INPUT   :   																	|
//	| @OUTPUT  : height in pixels									                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_LED::getCharHeight()
{
	switch(_led.charFont)
	{
		case CharFont::FONT_5X8:
			return _LED_CHAR_HEIGHT;
		case CharFont::FONT_5X16:
			return _LED_CHAR_HEIGHT*2;
		case CharFont::FONT_10X16:
			return _LED_CHAR_HEIGHT*2;
		case CharFont::FONT_3X5:
			return _LED_CHAR_LITTLE_HEIGHT;
		default:
			return 0;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Pixel at coordinates x,y and color		                    |
//	| @NAME    :  setPixel															|
//	| @INPUT   :  x,y coordinates and color 										|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
//	|
//	|	+---------------+---------------+---------------+
//	|	|(0,0)			|(8,0)			|(16,0)			|
//	|	|   region#1	|   region#3	|   region#5	|
//	|	|		   (7,7)|		   (7,7)|		   (7,7)|
//	|	+---------------+---------------+---------------+
//	|	|(0,8)			|(8,8)			|(16,8)			|
//	|	|   region#2	|   region#4	|   region#6	|
//	|	|		  (7,15)|		 (15,15)|		 (23,15)|
//	|	+---------------+---------------+---------------+
//	|
//	|	region#1	address  0.. 7 low  byte
//	|	region#2	address  0.. 7 high byte exchange bit 4,5
//	|	region#3	address  8..15 low  byte
//	|	region#4	address  8..15 high byte exchange bit 4,5
//	|	region#3	address 15..23 low  byte
//	|	region#4	address 15..23 high byte exchange bit 4,5
//	+-------------------------------------------------------------------------------+
void class_LED::setPixel(int x,int y,Color color)
{
	uint8_t addr,*p;
	
	if (x<_led.window.xi || y<_led.window.yi || x>_led.window.xf || y>_led.window.yf) return;
	//compute address
	addr=((uint8_t)x & 0xf8) | ((uint8_t)~y & 0x07);
	//upper display computation
	if (y<8)
	{
		//compute start address
		p=&_led.bufferH[0];
		if (color==Color::BLACK)
		{
			//clear bit
			*(p+addr)&=~_led.bit_mask_H[x & 7];
		}
		else
		{
			//set bit
			*(p+addr)|=_led.bit_mask_H[x & 7];
		}
	}
	else
	{	
		//compute start address
		p=&_led.bufferL[0];
		if (color==Color::BLACK)
		{
			//clear bit
			*(p+addr)&=~_led.bit_mask_L[x & 7];
		}
		else
		{
			//set bit
			*(p+addr)|=_led.bit_mask_L[x & 7];
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Pixel Color at coordinates x,y			                    |
//	| @NAME    :  getPixel															|
//	| @INPUT   :  x,y coordinates and color 										|
//	| @OUTPUT  :  Color Pixel						                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+

Color class_LED::getPixel(int x,int y)
{
	uint8_t addr,*p;
	
	if (x<_led.window.xi || y<_led.window.yi || x>_led.window.xf || y>_led.window.yf) return Color::BLACK;
	//compute address
	addr=((uint8_t)x & 0xf8) | ((uint8_t)~y & 0x07);
	//upper display computation
	if (y<8)
	{
		p=&_led.bufferH[0];
		return (*(p+addr) & _led.bit_mask_H[x & 7])?Color::RED:Color::BLACK;
	}
	else
	{
		p=&_led.bufferL[0];
		return (*(p+addr) & _led.bit_mask_L[x & 7])?Color::RED:Color::BLACK;
	}	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Refresh Mode													|
//	| @NAME    : setRefreshMode														|
//	| @INPUT   : refreshMode AUTOMATIC or MANUAL									|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setRefreshMode(RefreshMode refreshMode/* =RefreshMode::AUTOMATIC */)
{
	_led.refreshMode=refreshMode;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Refresh Screen														|
//	| @NAME    : refresh															|
//	| @INPUT   : 																	|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::refresh()
{
	//copy data from buffer to screen
	memcpy(_led.refreshBufferL,_led.bufferL,sizeof(_led.bufferL));
	memcpy(_led.refreshBufferH,_led.bufferH,sizeof(_led.bufferH));
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Fill Graph Mode												|
//	| @NAME    : setFillMode														|
//	| @INPUT   : true Fill ON , false Fill OFF 										|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setFillMode(bool fillMode/* =true */)
{
	_led.fillMode=fillMode;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Fill Graph Mode												|
//	| @NAME    : getFillMode														|
//	| @INPUT   : 																	|
//	| @OUTPUT  :true Fill ON , false Fill OFF 										|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
bool class_LED::getFillMode()
{
	return _led.fillMode;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Character fill mode Fill										|
//	| @NAME    : setFill															|
//	| @INPUT   : true Fill ON , false Fill OFF 										|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setCharFillMode(bool charFillMode/* =true */)
{
	_led.charFill=charFillMode;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Color															|
//	| @NAME    : setColor															|
//	| @INPUT   : true Fill ON , false Fill OFF 										|
//	| @OUTPUT  :									                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_LED::setPen(Pen pen)
{
	_led.pen=pen;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Draw Line with color and pen                                      |
//	| @NAME    :  Line         	        					                        |
//	| @INPUT   :  xi start,yi start,xf end,yf end,color								|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : using Bresenham algorithm                       		            |
//	+-------------------------------------------------------------------------------+

//get absolute of x
static int absolute(int x)
{
	if (x<0)
		return -x;
	else
		return x;
}
//get signal of a if a>0 return 1 if a=0 return 0 if a<0 return -1
static int sgn(int a)
{
	if (a==0) return 0;
	if (a>0) return 1;
	return -1;
}
char bf[20];
void    class_LED::line(int xi,int yi,int xf,int yf,Color color)
{
	int a,b,t,ct,d,j,k;
	int xn,xd;
	int yn,yd;
	int x,y;
	uint16_t shift;

	_led.coords={.x=xf,.y=yf};

	//prepare for drawing
	a=absolute(xf-xi);
	b=absolute(yf-yi);
	//Set No diagonal moves
	if (a>=b)
	{
		xn=sgn(xf-xi);
		yn=0;
	}
	else
	{
		xn=0;
		yn=sgn(yf-yi);
		t=a;
		a=b;
		b=t;
	}
	//Set diagonal moves
	if (xi>xf) xd=-1; else xd=1;
	if (yi>yf) yd=-1; else yd=1;
	//Set Line length
	ct=a+1;
	//Set Decision variable
 	d=(b*2)-a;
	//set K 
 	k=(b-a)*2;
	//Set J
 	j=b*2;
	//Set Start Point
	x=xi;
	y=yi;
	shift=static_cast<uint16_t>(_led.pen);
	//draw line
	while (ct>0) {
		{
			shift<<=1;
			shift|=(shift>>8);
		}
		//Set a Pixel
		if (color==Color::BLACK)
		{
			setPixel(x,y,(Color)((shift&1)^1));
		}
		else
		{
			setPixel(x,y,(Color)(shift&1));
		}
		ct--;
		//update decision flag
		if (d>0) {
			x+=xd;
			y+=yd;
			d+=k;
		}
		else {
			x+=xn;
			y+=yn;
			d+=j;
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw Line with color and pen										|
//	| @NAME    : Line         	        					                        |
//	| @INPUT   : Window and color													|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : using Bresenham algorithm                       		            |
//	+-------------------------------------------------------------------------------+
void class_LED::line(Window<int> window,Color color/* =Color::RED */)
{
	line(window.xi,window.yi,window.xf,window.yf,color);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Draw Line from last point draw on screen							|
//	| @NAME    :  lineTo         	        					                    |
//	| @INPUT   :  x end,y end,color													|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : using Bresenham algorithm                       		            |
//	+-------------------------------------------------------------------------------+
void class_LED::lineTo(int x,int y,Color color)
{
	line(_led.coords.x,_led.coords.y,x,y,color);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Draw Line from last point draw on screen							|
//	| @NAME    :  lineTo         	        					                    |
//	| @INPUT   :  Point color														|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : using Bresenham algorithm                       		            |
//	+-------------------------------------------------------------------------------+
void class_LED::lineTo(Point<int> point,Color color/* =Color::RED */)
{
	line(_led.coords.x,_led.coords.y,point.x,point.y,color);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Move Graph Cursor to Point x,y									|
//	| @NAME    :  moveTo         	        					                    |
//	| @INPUT   :  x ,y Position														|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                     												|
//	+-------------------------------------------------------------------------------+
void class_LED::moveTo(int x,int y)
{
	_led.coords={.x=x,.y=y};
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Move Graph Cursor to Point x,y									|
//	| @NAME    :  moveTo         	        					                    |
//	| @INPUT   :  Point Position													|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                     												|
//	+-------------------------------------------------------------------------------+
void class_LED::moveTo(Point<int> point)
{
	_led.coords={.x=point.x,.y=point.y};
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw a Circle														|
//	| @NAME    : circle         	        					                    |
//	| @INPUT   : x,y coordinates radius and color									|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : use Bresenham circle algorithm                   					|
//	+-------------------------------------------------------------------------------+
void class_LED::circle(int px,int py,int radius,Color color)
{
	int x,y,d;

	if (radius<0) return;

	x=0;
	y=radius;
	d=3-2*radius;

	while (x<y) {

		plotP8(px,py,x,y,color);
		if (d<0)
		{
			d+=4*x+6;
		}
		else
		{
			d+=4*(x-y)+10;
			y--;
		}
		x++;
	}
	if (x==y)
	{
		plotP8(px,py,x,y,color);
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw a Circle														|
//	| @NAME    : circle         	        					                    |
//	| @INPUT   : Point coordinates radius and color									|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS : use Bresenham circle algorithm                   					|
//	+-------------------------------------------------------------------------------+
void class_LED::circle(Point<int> point,int radius,Color color/* =Color::RED */)
{
	circle(point.x,point.y,radius,color);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw a Rectangle													|
//	| @NAME    : rectangle         	        					                    |
//	| @INPUT   : xi,yi,xf,yf rectangle coordinates and color						|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                													|
//	+-------------------------------------------------------------------------------+
void class_LED::rectangle(int xi,int yi,int width,int height,Color color/* =Color::RED */)
{
	int		xf,yf;
	int		tmp;
	
	//if zero width or height return
	if (width==0 || height==0) return;
	//compute coordinates
	if (width>0)
	{
		xf=xi+width-1;
		yf=yi+height-1;		
	}
	else
	{
		xf=xi+width+1;
		yf=yi+height+1;		
	}
	//fill?	
	if (_led.fillMode)
	{
		//yes, draw fill
		if (yi>yf)
		{
			tmp=yi;
			yi=yf;
			yf=tmp;
		}
		for(int i=yi;i<=yf;i++)
		{
			line(xi,i,xf,i,color);
		}
	}
	else
	{
		//no, draw border
		line(xi,yi,xf,yi,color);
		line(xi,yf,xf,yf,color);
		line(xi,yi,xi,yf,color);
		line(xf,yi,xf,yf,color);
	};
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Draw a Rectangle													|
//	| @NAME    : rectangle         	        					                    |
//	| @INPUT   : rectangle coordinates and color									|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                													|
//	+-------------------------------------------------------------------------------+
void class_LED::rectangle(Rect<int> rect,Color color/* =Color::RED */)
{
	rectangle(rect.x,rect.y,rect.width,rect.height,color);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Set Character Font    											|
//	|@NAME    :  setFont       	        											|
//	|@INPUT   :  charFont															|
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :            															|
//	+-------------------------------------------------------------------------------+
void class_LED::setFont(CharFont charFont)
{
	_led.charFont=charFont;	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Get Character Font    											|
//	|@NAME    :  getFont       	        											|
//	|@INPUT   :																		|
//	|@OUTPUT  :  charFont                                                           |
//	|@REMARKS :            															|
//	+-------------------------------------------------------------------------------+
CharFont class_LED::getFont()
{
	return _led.charFont;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put character on graph matrix at coordinates of moveTo     		|
//	|@NAME    :  putC       	        					                        |
//	|@INPUT   : char ASCII and transparent if true									|
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :            															|
//	+-------------------------------------------------------------------------------+
void  class_LED::putC(char c,Color color)
{

	uint8_t b,mask;
	uint16_t  index;
	int		xb,yb;

	switch(_led.charFont)
	{
		case CharFont::FONT_5X8:
		case CharFont::FONT_5X16:
		case CharFont::FONT_10X16:
			//check if in range
			if (c>=' ' && c<='~')
			{
				//translate ascii to binary
				c-=' ';
				index=(c*8);
				//draw chars
				for(uint8_t j=0;j<_LED_CHAR_HEIGHT;j++)
				{
					mask=0x80;
					b=pgm_read_byte(&_ASCII_Table_5X8[index++]);
					for(uint8_t i=0;i<_LED_CHAR_WIDTH;i++)
					{
						if ((b & mask)!=0)
						{
							switch(_led.charFont)
							{
								case CharFont::FONT_5X8:
									setPixel(_led.coords.x+i,_led.coords.y+j,color);
								break;
								case CharFont::FONT_5X16:
									setPixel(_led.coords.x+i,_led.coords.y+j*2,color);
									setPixel(_led.coords.x+i,_led.coords.y+j*2+1,color);
								break;
								case CharFont::FONT_10X16:
									xb=i*2;
									yb=j*2;
									//this below code is more fast then when use  rectangle
									setPixel(_led.coords.x+xb+0,_led.coords.y+yb+0);
									setPixel(_led.coords.x+xb+0,_led.coords.y+yb+1);
									setPixel(_led.coords.x+xb+1,_led.coords.y+yb+0);
									setPixel(_led.coords.x+xb+1,_led.coords.y+yb+1);
								break;
								case CharFont::FONT_3X5:
								break;
							}
						}
						else
						{
							if (_led.charFill)
							{
								switch(_led.charFont)
								{
									case CharFont::FONT_5X8:
										setPixel(_led.coords.x+i,_led.coords.y+j,Color::BLACK);
									break;
									case CharFont::FONT_5X16:
										setPixel(_led.coords.x+i,_led.coords.y+j*2,Color::BLACK);
										setPixel(_led.coords.x+i,_led.coords.y+j*2+1,Color::BLACK);
									break;
									case CharFont::FONT_10X16:
										xb=i*2;
										yb=j*2;
										//this below code is more fast then when use  rectangle
										setPixel(_led.coords.x+xb+0,_led.coords.y+yb+0,Color::BLACK);
										setPixel(_led.coords.x+xb+0,_led.coords.y+yb+1,Color::BLACK);
										setPixel(_led.coords.x+xb+1,_led.coords.y+yb+0,Color::BLACK);
										setPixel(_led.coords.x+xb+1,_led.coords.y+yb+1,Color::BLACK);
									break;
									case CharFont::FONT_3X5:
									break;
								}
							}
						}
						mask>>=1;
					}
				}
			}
			_led.coords.x+=getCharWidth();
		break;
		case CharFont::FONT_3X5:
			//check if in range
			if (c>=' ' && c<='~')
			{
				//translate ascii to binary
				c-=' ';
				index=((c>>1)*5);
				//check if c is odd or even

				//draw character
				for(uint8_t j=0;j<5;j++)
				{
					//select start bit according ascii(char) is odd or even
					if ((c&1)==0) mask=0x80; else mask=0x04;
					b=pgm_read_byte(&_ASCII_Table_3x5[index++]);
					for(uint8_t i=0;i<3;i++)
					{
						if ((b & mask)!=0)
						{
							setPixel(_led.coords.x+i,_led.coords.y+j,color);
						}
						else
						{
							if (_led.charFill)
							{
								setPixel(_led.coords.x+i,_led.coords.y+j,Color::BLACK);
							}
						}
						mask>>=1;
					}
				}	
			}
			_led.coords.x+=getCharWidth();
		break;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put String on graph matrix at coordinates of moveTo	     		|
//	|@NAME    :  putS       	        					                        |
//	|@INPUT   :  charString String, transparent if true								|
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :            															|
//	+-------------------------------------------------------------------------------+
void class_LED::putS(const char *charString,Color color)
{
	int xInit=_led.coords.x;

	while (*charString!='\0')
	{
		switch (*charString)
		{
			case '\r':
				_led.coords.x=xInit;
			break;
			case '\n':
				_led.coords.y+=getCharHeight();
			break;
			default:
				putC(*charString,color);
		}
		charString++;
	}	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Put a String from FLASH on Display Graph at last row,col position	|
//	|@NAME    :  PutS																|
//	|@INPUT   :  charString a string with valid ASCII character range ' ' to '~'	|
//	|			 and more 32 more characters										|
//	|@OUTPUT  :  																	|
//	|@REMARKS :  check data sheet to seed more 32 characters						|
//	+-------------------------------------------------------------------------------+
void class_LED::putSF(const char *charInFLASH)
{
	int xInit=_led.coords.x;
	char tmp;
	
	for(;;)
	{
		tmp=pgm_read_byte(charInFLASH++);
		switch (tmp)
		{
			case '\0':
			return;
			case '\r':
				_led.coords.x=xInit;
			break;
			case '\n':
				_led.coords.y+=getCharHeight();
			break;
			default:
			putC(tmp);
		}
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get BMP width in Flash												|
//	|@NAME    : bmpWidth    	        					                        |
//	|@INPUT   : bmp in flash										                |
//	|@OUTPUT  :							                                            |
//	|@REMARKS :								                       	                |
//	+-------------------------------------------------------------------------------+
int class_LED::getBMPWidth(BMP bmpInFlash)
{
	int w;
	bmpInFlash+=8;
	w=pgm_read_word(bmpInFlash++);
	//w+=pgm_read_word(bmpInFlash++)<<8;
	return w;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: Get BMP height in Flash												|
//	|@NAME    : bmpHeight    	        					                        |
//	|@INPUT   : bmp in flash										                |
//	|@OUTPUT  :							                                            |
//	|@REMARKS :								                       	                |
//	+-------------------------------------------------------------------------------+
int class_LED::getBMPHeight(BMP bmpInFlash)
{
	int h;
	bmpInFlash+=8;
	h=pgm_read_word(bmpInFlash++);
	//h+=pgm_read_word(bmpInFlash++)<<8;
	return h;
}

//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: Draw BMP on LED Panel Display										|
//	|@NAME    : bmp		    	        					                        |
//	|@INPUT   :	x,y coordinates and bmp in Flash					                |
//	|@OUTPUT  : true if bmp drawn ok                                                |
//	|@REMARKS :								                       	                |
//	+-------------------------------------------------------------------------------+

void class_LED::bmp(int xx,int yy,BMP bmpInFlash,bool invertColor)
{
	//uint32_t ts;		//total bmp size
	int w;				//width
	int h;				//height
	int hs;				//header size
	int wb;				//width in bytes
	int color;			//color
	uint8_t bitMask;	//bit mask
	uint8_t bmpData;	//bmp data
	uint16_t m;			//pixel position

	//below code use read by instead word because i dont know
	//check reader and return false if anything wrong
	
	//check header
	if (pgm_read_byte(bmpInFlash++)!='B') return;
	if (pgm_read_byte(bmpInFlash++)!='M') return;
	//check size
	hs=pgm_read_byte(bmpInFlash++);
	hs+=pgm_read_byte(bmpInFlash++)<<8;
	if (hs!=18) return;
	//check bit deep
	w=pgm_read_byte(bmpInFlash++);
	w+=pgm_read_byte(bmpInFlash++)<<8;
	if (w!=1) return;
	//get Color type
	color=pgm_read_byte(bmpInFlash++);
	color+=pgm_read_byte(bmpInFlash++)<<8;
	if (color!=0) return;
	//get width
	w=pgm_read_byte(bmpInFlash++);
	w+=pgm_read_byte(bmpInFlash++)<<8;
	//get height
	h=pgm_read_byte(bmpInFlash++);
	h+=pgm_read_byte(bmpInFlash++)<<8;
	//get width in bytes
	wb=pgm_read_byte(bmpInFlash++);
	wb+=pgm_read_byte(bmpInFlash++)<<8;
	//get total size not used in this routine
	//ts=pgm_read_dword(bmpInFlash+=4);
	bmpInFlash+=4;	//skip total size
	//start to draw bmp
	for(int8_t y=0;y<h;y++)
	{
		//bit mask start at bit 7
		bitMask=0x80;
		m=y*wb;
		bmpData=pgm_read_byte(&bmpInFlash[m]);
		for(int8_t x=0;x<w;x++)
		{
			//bit 1 or 0
			if (invertColor)
			{
				setPixel(xx+x,yy+y,(bitMask & bmpData)?Color::BLACK:Color::RED);
			}
			else
			{
				setPixel(xx+x,yy+y,(bitMask & bmpData)?Color::RED:Color::BLACK);	
			}
			
			//next bit mask
			bitMask>>=1;
			//bit 0?
			if (bitMask==0)
			{
				//yes, reload bit mask with 0x80 bit 7
				bitMask=0x80;
				//next byte
				m++;
				//get next data in cols (x)
				bmpData=pgm_read_byte(&bmpInFlash[m]);
			}
		}
	}
	//return Ok
	return;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION:  Get Text Width													   	|
//	|@NAME    :  TextWidth    	        					                        |
//	|@INPUT   :                                 			                        |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :	 width in pixels				            		                |
//	+-------------------------------------------------------------------------------+
int16_t		class_LED::getTextWidth(const char *textString)
{
	int16_t ct=0;
	int16_t max=0;

	while (*textString!=0)
	{
		switch (*textString)
		{
			case '\n':
			case '\r':
			if (ct>max) max=ct;
			ct=0;
			default:
			ct++;
		}
		textString++;
	}
	if (ct>max) max=ct;
	
	return getCharWidth()*max;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION:  Get Text Width in pgm string										|
//	|@NAME    :  TextWidth    	        					                        |
//	|@INPUT   :                                 			                        |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :	 width in pixels				            		                |
//	+-------------------------------------------------------------------------------+
int16_t		class_LED::getTextWidthP(const char * textStringInFlash)
{
	int16_t ct=0;
	int16_t max=0;
	
	while (pgm_read_byte(textStringInFlash)!=0)
	{
		switch (pgm_read_byte(textStringInFlash))
		{
			case '\n':
			case '\r':
				if (ct>max) max=ct;
				ct=0;
			break;
			default:
				ct++;
		}
		textStringInFlash++;
	}
	if (ct>max) max=ct;
	
	return getCharWidth()*max;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION:  Get Text Height												   	|
//	|@NAME    :  TextHeight    	        					                        |
//	|@INPUT   :                                 			                        |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :	 height in pixels				            		                |
//	+-------------------------------------------------------------------------------+
int16_t		class_LED::getTextHeight(const char *textString)
{
	int16_t cLF=1;

	while (*textString!=0)
	{
		if (*textString=='\n')
		{
			cLF++;
		}
		textString++;
	}
	return getCharHeight()*cLF;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION:  Get Text Height in pgm memory										|
//	|@NAME    :  TextHeight    	        					                        |
//	|@INPUT   :                                 			                        |
//	|@OUTPUT  :                                                                     |
//	|@REMARKS :	 height in pixels				            		                |
//	+-------------------------------------------------------------------------------+
int16_t		class_LED::getTextHeightP(const  char *textString)
{
	int16_t cLF=1;
	while (pgm_read_byte(textString)!=0)
	{
		if (pgm_read_byte(textString)=='\n')
		{
			cLF++;
		}
		textString++;
	}
	return getCharHeight()*cLF;
}
//	+-------------------------------------------------------------------------------+
//	|@FUNCTION: Set a View Window													|
//	| @NAME    : setViewWindow     	        					                    |
//	| @INPUT   : xi,yi,xf,yi coordinates 											|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                													|
//	+-------------------------------------------------------------------------------+
void class_LED::setViewWindow(int xi,int yi,int xf,int yf)
{
	int tmp;
	
	//first saturate
	if (xi<0) xi=0;
	if (yi<0) yi=0;
	if (xf>_LED_MATRIX_COLS-1) xf=_LED_MATRIX_COLS-1;
	if (yf>_LED_MATRIX_ROWS-1) yf=_LED_MATRIX_ROWS-1;
	
	//second change values
	if (xi>xf)
	{
		tmp=xi;
		xi=xf;
		xf=tmp;
	}
	if (yi>yf)
	{
		tmp=yi;
		yi=yf;
		yf=tmp;
	}
	//Set Window
	_led.window.xi=xi;
	_led.window.yi=yi;
	_led.window.xf=xf;
	_led.window.yf=yf;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set a View Window													|
//	| @NAME    : setViewWindow     	        					                    |
//	| @INPUT   : Window coordiantes 												|
//	| @OUTPUT  :                                                                    |
//	| @REMARKS :                													|
//	+-------------------------------------------------------------------------------+
void class_LED::setViewWindow(Window<int> window)
{
	_led.window=window;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get a View Window													|
//	| @NAME    : getViewWindow     	        					                    |
//	| @INPUT   :					 												|
//	| @OUTPUT  : window                                                             |
//	| @REMARKS :                													|
//	+-------------------------------------------------------------------------------+
Window<int> class_LED::getViewWindow()
{
	return _led.window;
}