#include "key.h"
#include "gpio.h"
#include "run.h"
#include "smg.h"

key_types key_t;
uint8_t KEY_Scan(void)
{
  uint8_t  reval = 0;
  key_t.read = _KEY_ALL_OFF; //0xFF 
   if(POWER_KEY_VALUE() ==1 )
	{
		key_t.read &= ~0x01; // 0xff & 0xfe =  0xFE
	}

    if(MODE_KEY_VALUE() ==1 )
	{
		key_t.read &= ~0x02; // 0xFf & 0xfd =  0xFD
	}

	
	if(DEC_KEY_VALUE()  ==1 )
	{
		  key_t.read &= ~0x04; // 0xFf & 0xfB =  0xFB
	}

	
	if(ADD_KEY_VALUE() ==1 )
	  {
		  key_t.read &= ~0x08; // 0x1f & 0xf7 =  0xF7
	  }

    //high
	if(FAN_KEY_VALUE()   ==1 )
	{
		  key_t.read &= ~0x10; // 0xFf & 0xEF =  0xEF
	}

	if(STER_KEY_VALUE()   ==1 )
	{
		  key_t.read &= ~0x20; // 0xFf & 0xDF =  0xDF
	}

	if(DRY_KEY_VALUE()  ==1 )
	{
		  key_t.read &= ~0x40; // 0xFf & 0xBF =  0xBF
	}


	if(AI_KEY_VALUE() ==1 )
	{
		key_t.read &= ~0x80; // 0x1f & 0x7F =  0x7F
	 }


 
	
	
	
	switch(key_t.state )
	{
		case start:
		{
			if(key_t.read != _KEY_ALL_OFF)
			{
				key_t.buffer   = key_t.read; //??:key.buffer = 0xFE  POWER KEY 
				key_t.state    = first;
				key_t.on_time  = 0;
				key_t.off_time = 0;
             //   POWER_LED_ON();
                
			}
			break;
		}
		case first:
		{
			if(key_t.read == key_t.buffer) // adjust key be down ->continunce be pressed key
			{
				if(++key_t.on_time> 100) //1000  0.5us
				{
					key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0xFE ^ 0xFF = 0x01
					key_t.on_time = 0;                      //key .value = 0xEF ^ 0XFF = 0X10
                   
					key_t.state   = second;
                   
                    
				}
			}
			else
			{
				key_t.state   = start;
			}
			break;
		}
		case second:
		{
			if(key_t.read == key_t.buffer) //again adjust key if be pressed down 
			{
				if(++key_t.on_time>6000)// 10000 long key be down
				{
					
					key_t.value = key_t.value|0x80; //key.value = 0x01 | 0x80  =0x81  
					key_t.on_time = 0;
					key_t.state   = finish;
                   
				}
			}
			else if(key_t.read == _KEY_ALL_OFF)  // loose hand 
				{
					if(++key_t.off_time>20) //30 don't holding key dithering
					{
						key_t.value = key_t.buffer^_KEY_ALL_OFF; // key.value = 0x1E ^ 0x1f = 0x01
						
						key_t.state   = finish; // loose hand
					}
				}
		   
			break;
		}
		case finish:
		{
			
			reval = key_t.value; // is short time  TIMER_KEY = 0x01  2. long times TIMER_KEY = 0X81
			key_t.state   = end;
         
			break;
		}
		case end:
		{
			if(key_t.read == _KEY_ALL_OFF)
			{
				if(++key_t.off_time>2)//50 //100
				{
					key_t.state   = start;
                  
				}
			}
			break;
		}
		default:
		{
			key_t.state   = start;
         
			break;
		}
	}
	return  reval;


}

/********************************************************************************************************
 	*
 	* Function Name:void SplitDispose_Key(uint8_t value)
 	* Function : Touch key handler function 
 	* Input Reference:NO
 	* Return Reference:NO
 	* 
*********************************************************************************************************/
void SplitDispose_Key(uint8_t value)
{
    static uint8_t plasma,dry,ai,mode_flag;
	
    
    switch(value){
        
       case 0x80: //Power On
    
          if(run_t.gPower_On == 0 || run_t.gPower_On == 0xff){
			  	  run_t.dispTime_hours=12;
			      run_t.dispTime_minute=0;
		          run_t.gTimes_time_seconds=0;
	              run_t.gPower_On=1;
	          
				  run_t.power_key =1;
				  run_t.gFan_RunContinue=0;
				 
				  run_t.gAi =0; //WT.EDIT 2022.09.01
				  run_t.gPlasma=0;
				  run_t.gDry =0;
				  run_t.gFan = 0;
	              
		  }
		  else{
                  
		  	run_t.power_key =2;
			run_t.gAi =1;//WT.EDIT 2022.11.21
		    run_t.gFan_RunContinue=1;
            run_t.gPower_On=0;
			run_t.fan_off_60s =0;
			run_t.temperature_set_flag =0;
			run_t.gTimer_Cmd = 0;
			run_t.gTimes_time_seconds=0;
            Smg_AllOff();
            }
       
          value = 0xff;
		 run_t.keyValue =0xff;
        
        break;
       
       case 0x40: //Mode On -> set time and timer 
           if(run_t.gPower_On ==1){
				
			mode_flag = mode_flag ^ 0x01; //the same is "0",and differenct is "1"

			if(run_t.gMode_flag  == 0){
                
				run_t.gMode_flag =1;
		    }
            else{
			 
			   run_t.gMode_flag =0;
			 
            }
           run_t.gTimer_key_4s=0;
	     }
		 value = 0xff;
		 run_t.keyValue =0xff;
        break;
        
        case 0x20: //CIN3 -> DEC KEY
             if(run_t.gPower_On ==1){
			
			 	if(run_t.gMode_flag==1){//times, is timer is 

				    run_t.dispTime_minute = run_t.dispTime_minute - 30;

				    if(run_t.dispTime_minute < 0){

				    run_t.dispTime_hours --;
					if(run_t.dispTime_hours < 0){
						run_t.dispTime_hours=23;
				        run_t.dispTime_minute =60;
					   run_t.dispTime_minute = run_t.dispTime_minute - 30;
					}
					else{
					  run_t.dispTime_minute =60;
					  run_t.dispTime_minute = run_t.dispTime_minute - 30;
					}
					
				    }
					run_t.gTimer_key_4s=0;
					 
				 }
				 else{ //setup temperature value 
                    
					 
				    //setup temperature of value,minimum 20,maximum 40
					 run_t.gTemperature --;
					 if(run_t.gTemperature<20) run_t.gTemperature=40;
					
					//  SetUp_Temperature_Value();
					   if(run_t.gTemperature >=20){
					   	    run_t.temperature_set_flag = 1;//run_t.gTemperature_timer_flag =1;
					   	    run_t.set_up_temp_flag = 1;
					   	}
			            else run_t.temperature_set_flag=0;
						
					
				     run_t.gTimer_key_4s=0;
					 run_t.gSet_up_times =0;
						
				 }
              
				
		
             
             }
           
           value = 0xff;   
		   run_t.keyValue =0xff;
         break;
        
        case 0x10: //CIN2 ->ADD KEY
             if(run_t.gPower_On ==1){
			 	  
				if(run_t.gMode_flag==1){ //set up temperature value
                    
				
					// run_t.dispTime_hours++;
				    run_t.dispTime_minute = run_t.dispTime_minute + 30;
				    if(run_t.dispTime_minute > 59){

		                 run_t.dispTime_hours ++;
		                 run_t.dispTime_minute=0;

						 if(run_t.dispTime_hours > 23){
							 
						      run_t.dispTime_hours=0;
							    

						}
						

					}
					run_t.gTimer_key_4s=0;		
					
                 }
				 else{
				      
					  //setup temperature minimum 20, maximum 40
				     run_t.gTemperature ++;
                     if(run_t.gTemperature < 20)run_t.gTemperature= 20;
					 else if(run_t.gTemperature >40) run_t.gTemperature=20;
					
			         if(run_t.gTemperature >=20){
					 	run_t.temperature_set_flag = 1;//run_t.gTemperature_timer_flag =1;
					 	run_t.set_up_temp_flag = 1;
				     }
			         else run_t.temperature_set_flag=0;
					 
					run_t.gTimer_key_4s=0;
					run_t.gSet_up_times =0;
					
				 }

             }
            value = 0xff;
			run_t.keyValue =0xff;
         break;
         //function to mainboard link single
         case 0x08: //Fan KEY 
              if(run_t.gPower_On ==1){
                   
                ai = ai ^ 0x01;
				if(ai==1){
					    if(run_t.gFan==0){
 					       run_t.gFan =1; //tur off fan
 					       run_t.gAi =1;  //turn off Ai
 					       run_t.gDry=1; //tunr off gDry
					    }
                        else
                            run_t.gFan =0;
 					
				  }
				  else{ //turn on AI mode
				        if(run_t.gFan==1){
						   run_t.gFan =0;
				        }
                        else{
                            run_t.gFan =1;
							run_t.gAi =1;  //turn off Ai
							run_t.gDry=1; //tunr off gDry
                        }
	               
				}
				    

				}
		
			 value = 0xff;
		 run_t.keyValue =0xff;
         break;
         
         case 0x04: //CIN5  -> plasma ->STERILIZATION KEY 
             if(run_t.gPower_On ==1){
			
               plasma = plasma ^ 0x01;
			   if(plasma ==1){  //turun off kill 
			   	
			       if(run_t.gPlasma ==1){
				       run_t.gPlasma = 0;
					   run_t.gFan=0;   //WT.EDIT 2023.01.30
			       	}
                   else{
                       run_t.gPlasma = 1;
					   run_t.gAi =1;  //turn off Ai
					   
                   	}
				   
		       }
			   else{
			   	  if(run_t.gPlasma ==1){
				       run_t.gPlasma = 0;
					   run_t.gFan=0;   //WT.EDIT 2023.01.30
			   	  	}
                   else{
                       run_t.gPlasma = 1;
					   run_t.gAi =1;  //turn off Ai
					  
                   	}
			   	}
               
                if( run_t.gPlasma==1 && run_t.gDry ==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		          }
		          else run_t.gFan_RunContinue =0;

			
             
             }
            
             value = 0xff;
		 run_t.keyValue =0xff;
         break;
         
         case 0x02: //CIN6  ->DRY KEY 
               if(run_t.gPower_On ==1){
		
			    dry = dry^ 0x01;
				if(dry==1){ //turn off the first be pressed 
                   if(run_t.gDry== 1){
				       run_t.gDry =0;
					   run_t.gFan=0;   //WT.EDIT 2023.01.30
                   	}
                   else{
                       run_t.gDry =1;
					   run_t.gAi =1;  //turn off Ai
                   	}
				  

				}
				else{ //the second be pressed key
                    
                   if(run_t.gDry== 1){
				       run_t.gDry =0;
					   run_t.gFan=0;   //WT.EDIT 2023.01.30
					   
                   	}
                   else{
                       run_t.gDry =1;
					   run_t.gAi =1;  //turn off Ai
					 
                   	}
                    
					
				}
			    if( run_t.gPlasma==1 && run_t.gDry ==1){
			    	   run_t.gFan_RunContinue =1;
					   run_t.fan_off_60s =0;
		            }
		            else run_t.gFan_RunContinue =0;
			   
				 
               }
           
             value = 0xff;
		 run_t.keyValue =0xff; 
         break;

		  case 0x01: //CIN4 -> AI  KEY ->rat_control
              if(run_t.gPower_On ==1){
                   
                ai = ai ^ 0x01;
				if(ai==1){
					    if(run_t.gAi==0){
 					       run_t.gAi =1; //turon off AI mode
					    }
                        else{
                            run_t.gAi =0;
							run_t.gFan=0;
						    run_t.gPlasma =0;
							run_t.gDry=0;
                        }
 					
				  }
				  else{ //turn on AI mode
				        if(run_t.gAi==1){
						    run_t.gAi =0;
						    run_t.gFan=0;
						    run_t.gPlasma =0;
							run_t.gDry=0;
						   
				        }
                        else
                            run_t.gAi =1;
	               
				}
				    

			 }
		
			 value = 0xff;
		 run_t.keyValue =0xff;	
         break;
         
     
             
         default :
             
           value = 0xff;
		  run_t.keyValue =0xff;
         break;
        
      }

}


