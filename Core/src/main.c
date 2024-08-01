#include "ti_msp_dl_config.h"
//8000000/200=40000

#define OUTPUT_1W// 46541/46090
#define OUTPUT_2W// 40927
#define OUTPUT_3W// 40160
#define OUTPUT_4W// 39514
#define OUTPUT_5W//?
#define OUTPUT_6W//?



int flag = 0;

int scan(void);
int debunce(uint32_t inputpin, uint32_t control);





int main(void)
{
	int fre=200;
	bool changeflag=false;
	unsigned int status=114514;
    SYSCFG_DL_init();                      //Sysconfig

		//NVIC_EnableIRQ(SWITCH_INT_IRQN);
	
		/*DL_TimerG_setCaptureCompareValue(PWM_0_INST,400,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);		
	
		DL_TimerG_startCounter(PWM_0_INST);*/
	
    while(1)
		{
			status=scan();
			
			delay_cycles(32000);
			
			/*if(fre<=190)
				changeflag=true;
			else if(fre>=210)
				changeflag=false;*/
			/*
			if(!changeflag)
				DL_Timer_setLoadValue(PWM_0_INST,fre--);
			else if(changeflag)
				DL_Timer_setLoadValue(PWM_0_INST,fre++);*/
			
			DL_TimerG_setCaptureCompareValue(PWM_0_INST,50,DL_TIMERG_CAPTURE_COMPARE_1_INDEX);	
			//DL_TimerG_setCaptureCompareValue(PWM_0_INST, 100,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
			
			
			DL_TimerG_startCounter(PWM_0_INST);
		}
}

/*
void GROUP1_IRQHandler(void){
		switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
		{
			case SWITCH_INT_IIDX:	  // GPIOÖÐ¶Ï
					flag++;
			break;
			default:break;
		}
}
*/

int scan(void)
{
	int num=114514;
					DL_GPIO_clearPins(MATRIX_PORT,MATRIX_V1_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V2_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V3_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V4_PIN);
						if(debunce(MATRIX_H1_PIN,0))
						{
							num=0;
						}
						if(debunce(MATRIX_H2_PIN,1))
						{
							num=1;
						}
						if(debunce(MATRIX_H3_PIN,0))
						{
							num=2;
						}
						if(debunce(MATRIX_H4_PIN,0))
						{
							num=3;
						}
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V1_PIN);
					DL_GPIO_clearPins(MATRIX_PORT,MATRIX_V2_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V3_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V4_PIN);
						if(debunce(MATRIX_H1_PIN,0))
						{
							num=4;
						}
						if(debunce(MATRIX_H2_PIN,1))
						{
							num=5;
						}
						if(debunce(MATRIX_H3_PIN,0))
						{
							num=6;
						}
						if(debunce(MATRIX_H4_PIN,0))
						{
							num=7;
						}
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V1_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V2_PIN);
					DL_GPIO_clearPins(MATRIX_PORT,MATRIX_V3_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V4_PIN);
    
						if(debunce(MATRIX_H1_PIN,0))
						{
								num=8;
						}
						if(debunce(MATRIX_H2_PIN,1))
						{
							num=9;
						}
						if(debunce(MATRIX_H3_PIN,0))
						{
							num=10;
						}
						if(debunce(MATRIX_H4_PIN,0))
						{
							num=11;
						}
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V1_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V2_PIN);
					DL_GPIO_setPins(MATRIX_PORT,MATRIX_V3_PIN);
					DL_GPIO_clearPins(MATRIX_PORT,MATRIX_V4_PIN);
						if(debunce(MATRIX_H1_PIN,0))
						{
								num=12;
						}
						if(debunce(MATRIX_H2_PIN,1))
						{
							num=13;
						}
						if(debunce(MATRIX_H3_PIN,0))
						{
							num=14;
						}
						if(debunce(MATRIX_H4_PIN,0))
						{
							num=15;
						}
						return num;
}

int debunce(uint32_t inputpin, uint32_t control)
{
	if(!control){
	if(!(DL_GPIO_readPins(MATRIX_PORT, inputpin)))
	{
	for(uint32_t i=0;i<=20000;i++){}
	if(!(DL_GPIO_readPins(MATRIX_PORT, inputpin)))
		return 1;
	else 
		return 0;
	}
	else return 0;
}
	
	else {
		for(uint32_t i=0;i<=10000;i++){}
	if(!(DL_GPIO_readPins(MATRIX_PORT, inputpin)))
	{
	for(uint32_t i=0;i<=20000;i++){}
	if(!(DL_GPIO_readPins(MATRIX_PORT, inputpin)))
		return 1;
	else 
		return 0;
	}
	else return 0;
}
	}