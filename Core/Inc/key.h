#ifndef __KEY_H_
#define __KEY_H_
#include "main.h"


#define		_KEY_ALL_OFF				 0XFF

//normal times be pressed key
#define		_KEY_TRG_1_POWER     		0x01  //WK_UP
#define		_KEY_TRG_2_MODE     		0x02  //??????--???
#define		_KEY_TRG_3_DEC     			0x04  //????
#define		_KEY_TRG_4_ADD     			0x08

#define		_KEY_TRG_5_FAN     			0x10  //WK_UP
#define		_KEY_TRG_6_STER     		0x20  //??????--???
#define		_KEY_TRG_7_DRY    			0x40   //????
#define		_KEY_TRG_8_AI     			0x80




// combination of buttons 
#define		_KEY_TRG_1_WINDTI   			0x11   //?????
#define		_KEY_TRG_2_WINDTI   			0x12   //?????
#define		_KEY_TRG_3_WINDTI   			0x14   //?????
#define		_KEY_TRG_4_WINDTI   			0x18   //?????

//long times be pressed
#define		_KEY_CONT_1_POWER     	     0x81    //??????--???
#define		_KEY_CONT_2_MODE   		     0x82    //??????--???
#define		_KEY_CONT_3_DEC    	         0x84    //?????? ?????
#define		_KEY_CONT_4_ADD     	     0x88    //??? --?????

#define		_KEY_CONT_5_FAN     		 0x90
#define		_KEY_CONT_6_STER     		 0xA0
#define     _KEY_CONT_7_DRY              0XC0 
#define     _KEY_CONT_8_DRY              0X100 




#define		_KEY_CONT_1     	    0x81    //?????
#define		_KEY_CONT_2     		0x82
#define		_KEY_CONT_3     		0x84
#define		_KEY_CONT_4     	    0x88

#define		_KEY_COM_1    		    0x91
#define		_KEY_COM_2    		    0x92
#define		_KEY_COM_3    		    0x94
#define		_KEY_COM_4    		    0x98

#define HIGH_LEVEL                   1  /* 根据原理图设计，KEY1按下时引脚为低电平，所以这里设置为0 */

typedef enum
{
  KEY_UP   = 0,
  KEY_DOWN = 1,
}KEYState_TypeDef;


typedef  struct  _state_
{
 unsigned char         read;
 unsigned char         buffer;
 unsigned long          value;
 unsigned char        off_time;
 unsigned long        on_time;

 enum{
  start  = 0,
  first  = 1,
  second = 2,
  cont   = 3,
  end    = 4,
  finish = 5,
 }state;
}key_types;

extern key_types key_t;

uint8_t KEY_Scan(void);




void SplitDispose_Key(uint8_t value);



#endif 


