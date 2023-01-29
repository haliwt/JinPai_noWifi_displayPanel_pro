#ifndef __CMD_LINK_H_
#define __CMD_LINK_H_

#include "main.h"
#define  MAX_BUFFER_SIZE   8

extern uint8_t inputBuf[MAX_BUFFER_SIZE];
extern uint8_t outputBuf[8];

void SendData_ToHost(void);
void SendData_PowerOff(uint8_t index);
//void SendData_Timer_Hours(uint8_t hdata);

void SendData_Set_Temperature(uint8_t hdata);
void SendData_Set_Timer(uint8_t hdata);





void SendData_Buzzer(void);

void SendData_AI(uint8_t dat);
void Decode_Function(void);


#endif 




