/*
 ////////////////////////////////////////////////////////////////////////////////////////////////////////

	___  ___      _   _       _____      _                         _     _ _
	|  \/  |     | | | |     |_   _|    | |                       | |   (_) |
	| .  . | __ _| |_| |__     | | _ __ | |_ ___  __ _  ___ _ __  | |    _| |__  _ __ __ _ _ __ _   _
	| |\/| |/ _` | __| '_ \    | || '_ \| __/ _ \/ _` |/ _ \ '__| | |   | | '_ \| '__/ _` | '__| | | |
	| |  | | (_| | |_| | | |  _| || | | | ||  __/ (_| |  __/ |    | |___| | |_) | | | (_| | |  | |_| |
	\_|  |_/\__,_|\__|_| |_|  \___/_| |_|\__\___|\__, |\___|_|    \_____/_|_.__/|_|  \__,_|_|   \__, |
												  __/ |                                          __/ |
												 |___/											|____/

 /////////////////////////////////////////////////////////////////////////////////////////////////////////
 ------------------------------------- C++ FILE (tab 4)---------------------------------------------------
*/

/*
 +--------------------------------------+
 |        LOCAL LIBRARY INCLUDES	    |
 +--------------------------------------+
*/
#include "_MathI.h"


/*
+--------------------------------------+
|     CONSTANT DEFINITIONS		       |
+--------------------------------------+
*/

/*
 +--------------------------------------+
 |        VARIABLES					 	|
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        STRUCTS               	 	|
 +--------------------------------------+
*/
struct structMathI
{
}_mathI;
/*
 +--------------------------------------+
 |        LOCAL FLASH CONSTANTS		 	|
 +--------------------------------------+
*/
//INTEGER SINE TABLE FOR ANGLES 0..90 DEGREE
//FORMATTED AS FOLLOW
// IFFF
// I INTEGER PART 2 BITS
// F FRACTIONAL PART 14 BITS

const int mathI_SinTable[] PROGMEM =
{
0,
286,
572,
857,
1143,
1428,
1713,
1997,
2280,
2563,
2845,
3126,
3406,
3686,
3964,
4240,
4516,
4790,
5063,
5334,
5604,
5872,
6138,
6402,
6664,
6924,
7182,
7438,
7692,
7943,
8192,
8438,
8682,
8923,
9162,
9397,
9630,
9860,
10087,
10311,
10531,
10749,
10963,
11174,
11381,
11585,
11786,
11982,
12176,
12365,
12551,
12733,
12911,
13085,
13255,
13421,
13583,
13741,
13894,
14044,
14189,
14330,
14466,
14598,
14726,
14849,
14968,
15082,
15191,
15296,
15396,
15491,
15582,
15668,
15749,
15826,
15897,
15964,
16026,
16083,
16135,
16182,
16225,
16262,
16294,
16322,
16344,
16362,
16374,
16382,
16384
};
/*
 +--------------------------------------+
 |        LOCAL FUNCTIONS CONSTANTS 	|
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |        STRUCTS AND UNIONS		    |
 +--------------------------------------+
*/

/*
 +--------------------------------------+
 |       FORWARDS					    |
 +--------------------------------------+
*/
/*
        +-----------------------------------------------+
        |       PRIVATE FUNCTIONS IMPLEMENTATION        |
        +-----------------------------------------------+
*/


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
class_Math_Integer::class_Math_Integer()
{
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor			                                            |
//	| @NAME    :  										                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Math_Integer::~class_Math_Integer()
{
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Vector Sine														|
//	| @NAME    : vectorSin					  										|
//	| @INPUT   : vector, angle  												    |
//	| @OUTPUT  : vector*sine(angle)							                        |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
int	class_Math_Integer::vectorSin(int vector,int angle)
{
	int sig,signeg,partial;
		
	 signeg=1;
	 //<0?
	 if (angle < 0)
	 {
		//yes,signal =-1 and angle=abs(angle)
		sig = -1;
		angle=-angle;
	 }
	 else
	 {
		//else sig=1
		sig=1;
	 }
	
	 //reduce for 0..360 range
	 while (angle > 360)
	 {
		angle = angle - 360;
	 }
	 //1st quadrant? 
	 if (angle <= 90)
	 {	
			partial =pgm_read_word(&mathI_SinTable[angle]);
	 }
	 else
	 {
		if (angle<=180)
		{
				partial =pgm_read_word(&mathI_SinTable[(180-angle)]);
		}
		else
		{
			if (angle<=270)
			{
					partial=pgm_read_word(&mathI_SinTable[(angle-180)]);
				signeg=-1;
			}
			else
			{
					partial=pgm_read_word(&mathI_SinTable[(360-angle)]);
				signeg=-1;
			}
		}

	 }
	 //compute angle sine
	 partial=((long)partial*vector )>>14;
	 partial*=sig*signeg;

	return partial;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Vector CoSine														|
//	| @NAME    : vectorCos					  										|
//	| @INPUT   : vector, angle  												    |
//	| @OUTPUT  : vector*cosine(angle)							                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
int	class_Math_Integer::vectorCos(int vector,int angle)
{
	return vectorSin(vector,angle+90);
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Constructor														|
//	| @NAME    : rotate						  										|
//	| @INPUT   :																    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
class_Rotate::class_Rotate(void)
{
	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Constructor #2 with initial data									|
//	| @NAME    : rotate						  										|
//	| @INPUT   :																    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
class_Rotate::class_Rotate(int cx,int cy,int angle)
{
	this->rotCenterX=cx;
	this->rotCenterY=cy;
	this->rotAngle=angle;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Destructor															|
//	| @NAME    : rotate						  										|
//	| @INPUT   :																    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
class_Rotate::~class_Rotate()
{
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Rotate Center Point											|
//	| @NAME    : rotateSetCenter			  										|
//	| @INPUT   : cx,cy center of rotation										    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Rotate::setCenter(int cx,int cy)
{
	this->rotCenterX=cx;
	this->rotCenterY=cy;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Rotate Center Point											|
//	| @NAME    : rotateGetCenter			  										|
//	| @INPUT   : cx,cy center of rotation										    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Rotate::getCenter(int &cx,int &cy)
{
	cx=this->rotCenterX;
	cy=this->rotCenterY;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Set Rotate Angle													|
//	| @NAME    : rotateSetAngle				  										|
//	| @INPUT   : angle of rotation												    |
//	| @OUTPUT  :												                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Rotate::setAngle(int angle)
{
	this->rotAngle=angle;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Get Rotate Angle													|
//	| @NAME    : rotateGetAngle				  										|
//	| @INPUT   : 																	|
//	| @OUTPUT  : rotation angle												        |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
int class_Rotate::getAngle()
{
	return this->rotAngle;
}

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Rotate a point														|
//	| @NAME    : rotate						  										|
//	| @INPUT   : x,y coordinates to rotate										    |
//	| @OUTPUT  : x,y coordinates rotated						                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+

void class_Rotate::rotate(int x,int y,int &xRot,int &yRot)
{
	int a=(x-this->rotCenterX);
	int b=(y-this->rotCenterY);
	
	xRot=this->rotCenterX+(class_Math_Integer::vectorCos(a,this->rotAngle)-class_Math_Integer::vectorSin(b,this->rotAngle));
	yRot=this->rotCenterY+(class_Math_Integer::vectorCos(b,this->rotAngle)+class_Math_Integer::vectorSin(a,this->rotAngle));
	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Compute arc rotation												|
//	| @NAME    : rotateArc					  										|
//	| @INPUT   : x,y coordinates and radius and angle							    |
//	| @OUTPUT  : px,py rotated									                    |
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void  class_Math_Integer::rotateArc(int x,int y,int radius_x,int radius_y,int angle,int &px,int &py)
{
	px=x+vectorCos(radius_x,angle);
	py=y-vectorSin(radius_y,angle);
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Fast Square Root Function made in assembler asm for integer 16its	|
//	| INPUT   :  numberValue														|
//	| OUTPUT  :  Square Root of numberValue											|
//	| REMARKS :  average speed at 16mhz 8.3us                                       |
//	+-------------------------------------------------------------------------------+
uint16_t class_Math_Integer::sqrtInt(uint16_t numberValue)
{
	int result=0;
	
	#ifdef ESP32
	#else
		asm volatile(   \
		"push       r0                  \t\n" \
		"push       r1                  \t\n" \
		"movw	    r2,%[inpValue]      \t\n" \
		"clr	    r0                  \t\n" \
		"clr	    r1                  \t\n" \
		"inc	    r1                  \t\n" \
		"add	    r2,r1               \t\n" \
		"adc	    r3,r0               \t\n" \
		"clr	    r4					\t\n" \
		"sec                            \t\n" \
		"ror	    r4                  \t\n" \
		"clr	    r5					\t\n" \
		"_mathDSP_SqrtInt_10%=:         \t\n"\
		"or	    r5,r4					\t\n" \
		"mul	    r5,r5               \t\n" \
		"cp 	    r0,r2               \t\n" \
		"cpc	    r1,r3               \t\n" \
		"brlo	    _mathDSP_SqrtInt_20%=\t\n"\
		"com	    r4					\t\n" \
		"and	    r5,r4               \t\n" \
		"com	    r4                  \t\n" \
		"_mathDSP_SqrtInt_20%=:         \t\n"\
		"lsr	    r4					\t\n" \
		"brcc	    _mathDSP_SqrtInt_10%=\t\n"\
		"clr        r1                  \t\n" \
		"mov        %A[outValue],r5     \t\n" \
		"mov        %B[outValue],r1     \t\n" \
		"pop        r1                  \t\n" \
		"pop        r0                  \t\n" \
		:[outValue] "=d" (result)             \
		:[inpValue] "a" (numberValue)         \
		:"r2","r3","r4","r5"                  \
		);
	#endif
	return result;
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Constructor														|
//	| INPUT   :  lineDDAPrepare														|
//	| OUTPUT  :																		|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
class_LineDDA::class_LineDDA()
{
	
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Constructor with initialization xi,yi,xf,yf						|
//	| INPUT   :  lineDDAPrepare														|
//	| OUTPUT  :																		|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
class_LineDDA::class_LineDDA(int xi,int yi,int xf,int yf)
{
	setCoords(xi,yi,xf,yf);
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Destructor															|
//	| INPUT   :  lineDDAPrepare														|
//	| OUTPUT  :																		|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
class_LineDDA::~class_LineDDA()
{
	
}

//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Prepare Line DDA (Digital Differential Analyzer)					|
//	| INPUT   :  lineDDAPrepare														|
//	| OUTPUT  :																		|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
//get absolute of x
// static int absolute(int x)
// {
// 	if (x<0)
// 		return -x;
// 	else
// 		return x;
// }
//get signal of a if a>0 return 1 if a=0 return 0 if a<0 return -1
static int sgn(int a)
{
	if (a==0) return 0;
	if (a>0) return 1;
	return -1;
}
void class_LineDDA::setCoords(int xi,int yi,int xf,int yf)
{
	int a,b,t;
	
	this->x0=xi;
	this->x1=xf;
	this->y0=yi;
	this->y1=yf;	
	//prepare for drawing
	a=abs(xf-xi);
	b=abs(yf-yi);
	if (a>=b)
	{
		this->xn=sgn(xf-xi);
		this->yn=0;
	}
	else
	{
		this->xn=0;
		this->yn=sgn(yf-yi);
		t=a;
		a=b;
		b=t;
	}
	//check directions
	if (xi>xf) this->xd=-1; else this->xd=1;
	if (yi>yf) this->yd=-1; else this->yd=1;
	this->ct=a+1;
	this->d=(b*2)-a;
	this->k=(b-a)*2;
	this->j=b*2;
	this->x=xi;
	this->y=yi;
	
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Get Line DDA Point													|
//	| INPUT   : lineDDAGetPoint														|
//	| OUTPUT  :	x,y and true if last point											|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
bool class_LineDDA::getPoint(int &x,int &y)
{
	x=this->x;
	y=this->y;
	if (this->ct==0)
		return true;
	else
		return false;
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Get Line DDA Next Point											|
//	| INPUT   :	 lineDDAGetNextPoint												|
//	| OUTPUT  :	 x,y and true if last point											|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
bool class_LineDDA::getNextPoint(int &x,int &y,int step)
{
	//last point
	for(int i=0;i<step;i++)
	{
		//get next point
		x=this->x;
		y=this->y;
		//compute next point
		this->ct--;
		//update decision flags
		if (this->d>0) {
			this->x+=this->xd;
			this->y+=this->yd;
			this->d+=this->k;
		}
		else {
			this->x+=this->xn;
			this->y+=this->yn;
			this->d+=this->j;
		}
	}
	//return true if last point of line dda
	return (ct==0)?true:false;
}
//	+-------------------------------------------------------------------------------+
//	| FUNCTION:  Get Line DDA Next Point											|
//	| INPUT   :	 lineDDAGetNextPoint												|
//	| OUTPUT  :	 x,y and true if last point											|
//	| REMARKS :											                            |
//	+-------------------------------------------------------------------------------+
void class_LineDDA::getCoords(int &xi,int &yi,int &xf,int &yf)
{
	xi=this->x0;
	yi=this->y0;
	xf=this->x1;
	yf=this->y1;
}
/*
        +-----------------------------------------------+
        |       PUBLIC CONSTRUCTORS AND DESTRUCTORS     |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor #1                                                    |
//	| @NAME    :								  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Pump::class_Pump(void)
{
	pMin=1;
	pMax=10;
	pStep=1;
	pValue=1;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Constructor #2                                                    |
//	| @NAME    :								  		                            |
//	| @INPUT   :  initial value,min value,max value and step                        |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+

class_Pump::class_Pump(PumpType pumpType,int initialValue,int minValue,int maxValue,int stepValue)
{
	pPumpType=pumpType;
	pMin=minValue;
	pMax=maxValue;
	pStep=stepValue;
	pValue=initialValue;
	if (pValue<pMin)
		pMin=pValue;
	else
		if (pValue>pMax)
			pMax=pMin;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Destructor														|
//	| @NAME    :								  		                            |
//	| @INPUT   :  none                                                              |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
class_Pump::~class_Pump(void)
{
	
}
/*
        +-----------------------------------------------+
        |       PUBLIC FUNCTIONS					    |
        +-----------------------------------------------+
*/

//	+-------------------------------------------------------------------------------+
//	| @FUNCTION:  Pump Initialize                                                   |
//	| @NAME    :								  		                            |
//	| @INPUT   :  initial value,min value,max value and step                        |
//	| @OUTPUT  :  none								                                |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Pump::init(PumpType pumpType,int initialValue,int minValue,int maxValue,int stepValue)
{
	pPumpType=pumpType;
	pMin=minValue;
	pMax=maxValue;
	pStep=stepValue;
	pValue=initialValue;
	if (pValue<pMin) 
		pMin=pValue;
	else
		if (pValue>pMax)
			pMax=pMin;	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: class_Pump get Minimal Value				                        |
//	| @NAME    :  										                            |
//	| @INPUT   :				                                                    |
//	| @OUTPUT  : Minimal Value								                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_Pump::getMin()
{
	return pMin;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump get Maxium Value				                                |
//	| @NAME    :  										                            |
//	| @INPUT   :				                                                    |
//	| @OUTPUT  : Maximum Value								                        |
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_Pump::getMax()
{
	return pMax;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump get Step Value				                                |
//	| @NAME    :  										                            |
//	| @INPUT   :				                                                    |
//	| @OUTPUT  : Step Value															|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_Pump::getStep()
{
	return pStep;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump get Value														|
//	| @NAME    :  										                            |
//	| @INPUT   :				                                                    |
//	| @OUTPUT  : Value																|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
int class_Pump::getValue()
{
	return pValue;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Set Minimal Value				                                |
//	| @NAME    :  										                            |
//	| @INPUT   : Minimal Value				                                        |
//	| @OUTPUT  : 																	|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Pump::setMin(int minValue)
{
	pMin=minValue;
	if (pValue<pMin) pValue=pMin;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Set Maximum Value				                                |
//	| @NAME    :  										                            |
//	| @INPUT   : Maximum Value				                                        |
//	| @OUTPUT  : 																	|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Pump::setMax(int maxValue)
{
	pMax=maxValue;
	if (pValue>pMax) pValue=pMax;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Set Step Value				                                |
//	| @NAME    :  										                            |
//	| @INPUT   : Step Value															|
//	| @OUTPUT  : 																	|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Pump::setStep(int stepValue)
{
	pStep=stepValue;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Get State														|
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  : State 																|
//	| @REMARKS : State may be:													    |
//	|			 1 if value=minimum value											|
//	|			 2 if value=maximum value											|
//	|			 0 otherwise														|
//	+-------------------------------------------------------------------------------+
PumpState class_Pump::getState(void)
{
	if (pValue==pMin) return PumpState::MINIMUM;
	if (pValue==pMax) return PumpState::MAXIMUM;
	return PumpState::MID;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump 																|
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  : 																	|
//	| @REMARKS : Pump value is incremented to max if step is positive then Pump 	|
//	|			 value is decremented to min value and repeats it cycle				|
//	+-------------------------------------------------------------------------------+
void class_Pump::pump()
{
	//if pump stoped then return
	if (!pbPumping) return;
	//pump according type
	switch (pPumpType)
	{
		//going to min
		case PumpType::TYPE_TO_MIN:
			pValue-=abs(pStep);
			if (pValue<pMin)
			{
				pValue=pMin;
			}
		break;
		//going to max
		case PumpType::TYPE_TO_MAX:
			pValue+=abs(pStep);
			if (pValue>pMax)
			{
				pValue=pMax;
			}
		break;
		//cycling min to max and max to min and repeat
		case PumpType::TYPE_CYCLE:
			pValue+=pStep;
			if (pValue>pMax)
			{
				pValue=pMax;
				pStep=-pStep;
			}
			else
			{
				if (pValue<pMin)
				{
					pValue=pMin;
					pStep=-pStep;
				}
			}
		break;
		//cycling min to max and return to min
		case PumpType::TYPE_CYCLE_TO_MIN:
			pValue+=abs(pStep);
			if (pValue>pMax)
			{
				pValue=pMin;
			}		
		break;
		//cycling max to min and return to max
		case PumpType::TYPE_CYCLE_TO_MAX:
			pValue-=abs(pStep);
			if (pValue<pMin)
			{
				pValue=pMax;
			}		
		break;
	}
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump stop									                        |
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  :					 												|
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Pump::stop()
{
	pbPumping=false;	
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump restart								                        |
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  :					 												|
//	| @REMARKS :																	|
//	+-------------------------------------------------------------------------------+
void class_Pump::restart()
{
	pbPumping=true;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Get Delta from minimum				                        |
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  : Delta from minimum 												|
//	| @REMARKS : Compute value-minimum												|
//	+-------------------------------------------------------------------------------+
int class_Pump::getDeltaMin()
{
	return pValue-pMin;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Get Delta from maximum				                        |
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  : Delta from maximum 												|
//	| @REMARKS : Compute maximum-value												|
//	+-------------------------------------------------------------------------------+
int class_Pump::getDeltaMax()
{
	return pMax-pValue;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump Set Type														|
//	| @NAME    :  										                            |
//	| @INPUT   : Pump Type															|
//	| @OUTPUT  : 																	|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
void class_Pump::setPumpType(PumpType pumpType)
{
	pPumpType=pumpType;
}
//	+-------------------------------------------------------------------------------+
//	| @FUNCTION: Pump get Type														|
//	| @NAME    :  										                            |
//	| @INPUT   : 																	|
//	| @OUTPUT  : Pump Type															|
//	| @REMARKS :													                |
//	+-------------------------------------------------------------------------------+
PumpType class_Pump::getPumpType()
{
	return pPumpType;
}
