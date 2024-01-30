#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "led.h"
#include "sys.h"
#include "tim.h"
#include "OLED.h"
int main(void)
{
	delay_init(200);
	OLED_Init();
	TIM3_Init(20000,10000);
extern int s;


int m=0;


int h=0;
  while(1)
	{
	OLED_ShowNum(1,1,h,2);
	
	OLED_ShowString(1,3, ":");
	
	OLED_ShowNum(2,1,m,2);
	
	OLED_ShowString(2,3, ":");
	
	OLED_ShowNum(3,1,s,2);
	
	OLED_ShowString(3,3, ":");
	
   for (; s > 59; s = 0) {
    m++;
}

for (; m > 59; m = 0) {
    h++;
}

for (; h > 23; h = 0) {
   
}
}

}
