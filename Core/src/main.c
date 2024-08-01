#include "ti_msp_dl_config.h"
//8000000/200=40000
//8000000/x=cntfre
#define OUTPUT_1W 688// 46541/46090
#define OUTPUT_2W 782// 40927
#define OUTPUT_3W 797// 40160
#define OUTPUT_4W 810// 39514
#define OUTPUT_5W 818//39120
#define OUTPUT_6W 825//38770



int flag = 0;

int scan(void);
int debunce(uint32_t inputpin, uint32_t control);


int main(void)
{
	unsigned int fre=OUTPUT_5W;
	bool changeflag=false;
	bool startflag=false;
	unsigned int status=114514;
    SYSCFG_DL_init();                      //Sysconfig

		//NVIC_EnableIRQ(SWITCH_INT_IRQN);
		DL_Timer_setLoadValue(PWM_0_INST,fre);
		DL_TimerG_setCaptureCompareValue(PWM_0_INST,412,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);		
		DL_TimerG_startCounter(PWM_0_INST);
	
    while(1)
		{
			status=scan();
			if(status!=114514)
			{
				switch (status)
				{
				case 0:startflag=true;break;
				case 1:fre=OUTPUT_1W;changeflag=true;break;
				case 2:fre=OUTPUT_2W;changeflag=true;break;
				case 3:fre=OUTPUT_3W;changeflag=true;break;
				case 4:fre=OUTPUT_4W;changeflag=true;break;
				case 5:fre=OUTPUT_5W;changeflag=true;break;
				case 6:fre=OUTPUT_6W;changeflag=true;break;
				case 7:startflag=false;break;
				default:break;
				}
			}

			if(DL_GPIO_readPins(CTLDE10_PORT, CTLDE10_DE10EN_PIN))//?
			{
				startflag=false;
			}

			if(startflag)
			{
				DL_GPIO_setPins(CTLDE10_PORT,CTLDE10_SW_PIN);
				DL_GPIO_clearPins(LED_PORT,LED_SHOW_PIN);
			}
			else
			{
				DL_GPIO_clearPins(CTLDE10_PORT,CTLDE10_SW_PIN);
				DL_GPIO_setPins(LED_PORT,LED_SHOW_PIN);
			}

			if(changeflag)
			{
				DL_Timer_setLoadValue(PWM_0_INST,fre);
				DL_TimerG_setCaptureCompareValue(PWM_0_INST,412,DL_TIMERG_CAPTURE_COMPARE_1_INDEX);
				DL_TimerG_startCounter(PWM_0_INST);
				changeflag=false;
			}

			//delay_cycles(32000);
			/*if(fre<=190)
				changeflag=true;
			else if(fre>=210)
				changeflag=false;*/
			/*
			if(!changeflag)
				DL_Timer_setLoadValue(PWM_0_INST,fre--);
			else if(changeflag)
				DL_Timer_setLoadValue(PWM_0_INST,fre++);*/
			//DL_TimerG_setCaptureCompareValue(PWM_0_INST, 100,DL_TIMERG_CAPTURE_COMPARE_0_INDEX);
		}
}

/*
void GROUP1_IRQHandler(void){
		switch(DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1))
		{
			case SWITCH_INT_IIDX:	  // GPIO�ж�
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