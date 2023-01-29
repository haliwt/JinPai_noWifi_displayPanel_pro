#include "cmd_link.h"
#include "usart.h"
#include "gpio.h"
#include "run.h"
#include "display.h"

volatile static uint8_t transOngoingFlag; //interrupt Transmit flag bit , 1---stop,0--run
uint8_t outputBuf[8];
static uint8_t transferSize;
static uint8_t state;
uint8_t inputBuf[MAX_BUFFER_SIZE];

/**********************************************************************************************************
**
*Function Name:static void notifyStatusToHost(uint8_t lightNum,uint8_t filterNum,uint8_t unionNum)
*Function : 
*Input Ref:lightNum--LED ,filterNum -filter number, unionNum - smart menu number
*Return Ref:NO
*
*********************************************************************************************************/
void Decode_Function(void)
{
   if(run_t.decodeFlag ==1){
   
       run_t.decodeFlag =0;
     
       Display_DHT11_Value();
    }
}
/****************************************************************************************************
**
*Function Name:static void selectLight(uint8_t index)
*Function: UART2 transmit interrupt process ---4D 58 4C 53 32 30 32 
*Input Ref: LED number 
*Return Ref:NO
*
****************************************************************************************************/
void SendData_PowerOff(uint8_t index)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D //Touch Key
	outputBuf[1]='K'; //58
	outputBuf[2]='P'; //4C	// 'P' power
	outputBuf[3]=index; //53	// 'S' select light command, 'C' close all light command
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}
void SendData_Buzzer(void)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D
	outputBuf[1]='K'; //58
	outputBuf[2]='Z'; //4C	// buzzer
	outputBuf[3]='Z'; //53	// buzzer
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}

void SendData_AI(uint8_t dat)
{
	
   //crc=0x55;
	outputBuf[0]='T'; //4D
	outputBuf[1]='K'; //58
	outputBuf[2]='A'; //4C	// AI 
	outputBuf[3]=dat; //53	//
	
    transferSize=4;
	if(transferSize)
	{
		while(transOngoingFlag);
		transOngoingFlag=1;
		HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
	}
	
}

//void SendData_Timer_Hours(uint8_t hdata)
//{
//	    outputBuf[0]='T'; //4D
//		outputBuf[1]='K'; //58
//		outputBuf[2]='H'; //4C	// AI 
//		outputBuf[3]=hdata; //53	//
//		
//		transferSize=4;
//		if(transferSize)
//		{
//			while(transOngoingFlag);
//			transOngoingFlag=1;
//			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
//		}
//	
//}

void SendData_Set_Timer(uint8_t hdata)
{
	    outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='I'; //4C	// 'I' ->time
		outputBuf[3]=hdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}


void SendData_Set_Temperature(uint8_t hdata)
{
	    outputBuf[0]='T'; //4D
		outputBuf[1]='K'; //58
		outputBuf[2]='T'; //4C	// 'T'->temperature
		outputBuf[3]=hdata; //53	//
		
		transferSize=4;
		if(transferSize)
		{
			while(transOngoingFlag);
			transOngoingFlag=1;
			HAL_UART_Transmit_IT(&huart1,outputBuf,transferSize);
		}
	
}

/********************************************************************************
	**
	*Function Name:void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
	*Function :UART callback function  for UART interrupt for receive data
	*Input Ref: structure UART_HandleTypeDef pointer
	*Return Ref:NO
	*
*******************************************************************************/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    
	if(huart==&huart1) // Motor Board receive data (filter)
	{
		switch(state)
		{
		case 0:  //#0
			if(inputBuf[0]=='M')  //hex :4D - "M" -fixed mainboard
				state=1; //=1
			break;
		case 1: //#1
			if(inputBuf[0]=='A') //hex : 41 -'A'  -fixed master
			{
				state=2; 
			}
			else
				state=0; 
			break;
		case 2://#2
			if(inputBuf[0]=='D' || inputBuf[0]=='W' || inputBuf[0]=='T' \
				|| inputBuf[0]=='P' ||inputBuf[0] =='C' || inputBuf[0] == 'B') //'D'->data , 'W' ->wifi
			{
				state=3;
				if(inputBuf[0]=='D') run_t.single_data=SINGLE_DATA; //receive data is single data
                else if(inputBuf[0]=='W') run_t.single_data = WIFI_INFO; //wifi data
			    else if(inputBuf[0]=='T') run_t.single_data = WIFI_TIME;
                else if(inputBuf[0]=='P') run_t.single_data = WIFI_TEMP;
				else if(inputBuf[0]=='C') run_t.single_data = WIFI_CMD;
				else if(inputBuf[0]=='B') run_t.single_data = WIFI_BEIJING_TIME;
			    
			}
			else
				state=0;
			break;
            
        case 3:
            if(run_t.single_data==SINGLE_DATA)
              run_t.gReal_humtemp[0]=inputBuf[0]; //Humidity
            else
              run_t.gInputCmd[0]=inputBuf[0]; //Humidity
              

			  
             state = 4;        
            
        break;
        
		case 4: //#3  if 'R' = hex:0x52

		 if(run_t.single_data == WIFI_BEIJING_TIME){
						 run_t.gTimes_minutes_temp = inputBuf[0];
						 state =5;
		 }
		 else{
		  if(run_t.single_data==SINGLE_DATA)
               run_t.gReal_humtemp[1]=inputBuf[0]; //temperature value
          else
			   run_t.gInputCmd[1]=inputBuf[0];  //temperature
			
			run_t.decodeFlag=1;
			state=0;
		 }

		 break;
           
       

		
		
		default:
			state=0;
			run_t.decodeFlag=0;  //

		}
		HAL_UART_Receive_IT(&huart1,inputBuf,1);//UART receive data interrupt 1 byte
	}
}

/********************************************************************************
**
*Function Name:void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
*Function :UART callback function  for UART interrupt for transmit data
*Input Ref: structure UART_HandleTypeDef pointer
*Return Ref:NO
*
*******************************************************************************/
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	if(huart==&huart1)
	{
		transOngoingFlag=0; //UART Transmit interrupt flag =0 ,RUN
	}
	
}

