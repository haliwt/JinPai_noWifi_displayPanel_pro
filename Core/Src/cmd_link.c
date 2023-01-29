#include "cmd_link.h"
#include "usart.h"
#include "gpio.h"
#include "run.h"
#include "display.h"
#include "led.h"

volatile static uint8_t transOngoingFlag; //interrupt Transmit flag bit , 1---stop,0--run
uint8_t outputBuf[8];
static uint8_t transferSize;
static uint8_t state;
uint8_t inputBuf[MAX_BUFFER_SIZE];

static void Decode_Rx_Data(void);
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

   
       Decode_Rx_Data();
      // Display_DHT11_Value();
    }
}

static void Decode_Rx_Data(void)
{
   switch(run_t.single_data){

    case SINGLE_DATA:

	     Display_DHT11_Value();

    break;


	case MB_CMD:

	   if(run_t.gInputCmd[0]==0x01){
	   	   run_t.gFan_off_flag = 1;
           LED_FAN_OFF();
		  
        }


	break;




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
			if(inputBuf[0]=='D' || inputBuf[0] =='C' ) //'D'->data , 'W' ->wifi
			{
				state=3;
				if(inputBuf[0]=='D') run_t.single_data=SINGLE_DATA; //receive data is single data
				else if(inputBuf[0]=='C') run_t.single_data = MB_CMD;
				
			    
			}
			else
				state=0;
			break;
            
        case 3:
            if(run_t.single_data==SINGLE_DATA){
			   state = 4;     
              run_t.gReal_humtemp[0]=inputBuf[0]; //Humidity
            }
            else if(run_t.single_data ==MB_CMD){
              run_t.gInputCmd[0]=inputBuf[0]; // Fan of value is 0x01 ->tunr off fan
              run_t.decodeFlag=1;
			  state=0;
            }
			else
				state=0;
		       
            
        break;
        
		case 4: //#3  if 'R' = hex:0x52

		  if(run_t.single_data==SINGLE_DATA){
             run_t.gReal_humtemp[1]=inputBuf[0]; //temperature value
         
			run_t.decodeFlag=1;
			state=0;
		  	}
		    else
				state = 0;
		

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

