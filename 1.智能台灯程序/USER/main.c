#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "beep.h"
#include "OLED_I2C.h"
#include "csb.h "
#include "adc.h"
#include "time.h"
#include "button.h" 

float adcx,temp;   
extern u8 Res;
extern int miao,fen,shi;
 int main(void)
 {	
	 float distance;
	 vu8 key=0;  
	 int a=0,flag=0,time_flag=0,level=3;  //a代表按键的值，flag自动手动。time_flag代表开关定时器,计时，level代表灯的亮度等级
	 int miao_flag=0,fen_flag=1,shi_flag=0; //代表计时时间，时间到，报警提示久座
	delay_init();	    //延时函数初始化	 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
	BEEP_Init();		  	//初始化与LED连接的硬件接口
	KEY_Init();         //按键初始化
 
	Adc_Init();		  		//ADC初始化	
	uart_init(9600);               //串口初始化
	Hcsr04Init();        //超声波初始化
	 
	OLED_Init();
	OLED_Fill(0xFF);//全屏点亮
	delay_ms(2);
	OLED_Fill(0x00); 
	delay_ms(2);
	delay_ms(100);
	OLED_CLS(); //清屏
	alarm();
  OLED_SHOW_A();
	 miao=0;fen=0;shi=0;
	while(1)
	{
	 
//光照强度采集
		adcx=Get_Adc_Average(ADC_Channel_1,10);
		temp=(float)adcx*(3.3/4096);   //temp单位为v
		adcx=temp*1000;                //单位为mv
		OLED_ShowNums(40,2,adcx,4,1);
		delay_ms(50);	//延时300ms
  
//蓝牙控制
		if(Res==1)
		{
			a=1;
			Res=0;
				USART_SendData(USART1,'O');//向串口1发送数据给蓝牙模块
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART1,'K');
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
		else if(Res==2)
		{
			a=2;
			Res=0;
				USART_SendData(USART1,'O');//向串口1发送数据给蓝牙模块
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
				USART_SendData(USART1,'K');
				while(USART_GetFlagStatus(USART1,USART_FLAG_TC)!=SET);//等待发送结束
		}
	 
		  
		//显示时间
		OLED_ShowNums(40,6,shi,2,1);
		OLED_ShowChar(60,6,':');
		OLED_ShowNums(70,6,fen,2,1);
		OLED_ShowChar(90,6,':');
		OLED_ShowNums(100,6,miao,2,1);
		if(miao==miao_flag&&fen==fen_flag&&shi==shi_flag)//计时时间到报警
		{
		 //alarm();
		}
	}
 }

