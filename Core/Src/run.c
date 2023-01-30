#include "run.h"
#include "smg.h"
#include "gpio.h"
#include "cmd_link.h"
#include "led.h"
#include "display.h"

RUN_T run_t;


void Power_Off(void);





/**********************************************************************
*
*Functin Name: void Wifi_Receive_Cmd(uint8_t cmd)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/


/**********************************************************************
*
*Functin Name: void Display_DHT11_Value(void)
*Function : Timer of key be pressed handle
*Input Ref:  key of value
*Return Ref: NO
*
**********************************************************************/
void Power_Off(void)
{
    	 if(run_t.gPower_On ==0){

			     run_t.gPower_On =0xff;
			 	  Smg_AllOff();
				
		         run_t.gAi =0;
				
				 run_t.gPlasma=0;
				 run_t.gDry=0;
				
				 run_t.gTemperature =20;
				

				  run_t.gTimer_Cmd=0; //timer of command "1"->timer is start
				  run_t.dispTime_hours=0;
				  run_t.dispTime_minute=0;
				  run_t.gTemperature_timer_flag=0;
			
			
			
				  run_t.gDht11_flag=0; //the first power on display "00"
				  run_t.dispTime_hours=12;

			
				  run_t.gMode_flag =0;
				
				  run_t.gTimer_key_4s=0;
	              run_t.gTimer_key_60s=0;
				  run_t.gTimer_fan_counter=0;
				
				//  SendData_PowerOff(0);//ShutDown_AllFunction();
				  ALL_LED_Off();
				  
                  
		}
		Breath_Led();
		SMG_POWER_OFF()	;
		
	      
}

void DisplayTimer_Timing(void)
{
      static uint8_t m,n,p,q;
      m = run_t.dispTime_hours /10 ;
	  n=  run_t.dispTime_hours %10; 
	  p = run_t.dispTime_minute /10;
	  q=  run_t.dispTime_minute %10;
	  TM1639_Write_4Bit_Time(m,n,p,q,0) ; //timer is default 12 hours "12:00"

  
}
/*******************************************************************************
	*
	*Function Name:void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
	*Function : timing 10ms interrupt call back function 
	*
	*
*******************************************************************************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  static uint8_t tm0;
    
    tm0++;
	run_t.gTimer_led_500ms++;
    if(tm0>99){ //100 *10ms = 1000ms = 1s
		tm0=0;
		
		
		run_t.gTimer_key_4s ++;
		run_t.gTimer_key_60s++;
		run_t.fan_off_60s++;
		
	
	    run_t.gTimes_time_seconds ++;
		 run_t.gTimer_Counter ++;
		 
		
	}
    

 }
	



	
