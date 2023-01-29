#ifndef __SINGLE_MODE_
#define __SINGLE_MODE_
#include "main.h"

extern void (*single_ai_fun)(uint8_t cmd);
extern void (*single_add_fun)(void);
extern void (*sendAi_usart_fun)(uint8_t senddat);
extern void (*dispose_key)(uint8_t dsdat);


void Scan_KeyMode(void);
void Single_RunCmd(void);


void RunReference_Fun(void);

void Single_AI_RunCmd(void (*singlaieHandler)(uint8_t dat));

void Single_Add_RunCmd(void(*addHandler)(void));

void Single_SendBuzzer_RunCmd(void(*buzzerHandler)(void));

void Single_SendAi_Usart_RunCmd(void(*sendaiHandler)(uint8_t seddat));

void SplitDispose_Key_RunCmd(void(*keyHandler)(uint8_t dat));


#endif 

