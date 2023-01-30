#ifndef __RUN_H_
#define __RUN_H_
#include "main.h"

enum Signal{
   SINGLE_DATA=1,
   MB_CMD
};

enum State{IDLE ,CODE, RUN};


typedef struct __RUN{

   uint8_t keyValue;
   uint8_t power_key;
   uint8_t gTemperature_timer_flag;
   uint8_t gPower_On;
   uint8_t gRun_flag;
   
   uint8_t keyAdd_continue;
   uint8_t keyDec_continue;
  

   uint8_t gDht11_flag;
   uint8_t gTemperature;
 
   uint8_t gTimer_Counter;
   
  
  
  uint8_t gTimer_setup_zero;

  uint8_t gFan_RunContinue;

  uint8_t temperature_flag;
  
   uint8_t usart_flag;
   uint8_t decodeFlag;
   uint8_t gTemp_check;
   uint8_t dec_key_times;
   uint8_t add_key_times;
   
   uint8_t  gTimer_Cmd;
   uint8_t  gPlasma;
 
   uint8_t  gDry;

   uint8_t  gAi;
   uint8_t  gFan;
   uint8_t  gMode_flag;
   
   uint8_t  gFan_off_flag ;
  
   uint8_t  dry_key;
   uint8_t  gTimer_fan_counter;
   uint8_t gTimes_minutes_temp;

  
   uint8_t gTimer_key_4s;
   uint8_t gTimer_key_60s;
   uint8_t gTimer_led_500ms;

   uint8_t single_data;
   uint8_t fan_off_60s;

   uint8_t Timer_mode_flag;
   uint8_t temperature_set_flag;

   uint8_t gTimer_1hour;
	
   uint8_t  gTimer_1_hour_counter;
   uint8_t  gTimes_time_seconds;

   
   
   uint8_t gReal_humtemp[2];
   uint8_t gInputCmd[2];

	int8_t dispTime_minute;

    int8_t dispTime_hours;
   


   
 }RUN_T;

extern RUN_T run_t;



void SplitDispose_Key(uint8_t value);







void Power_Off(void);
void DisplayTimer_Timing(void);



#endif 



