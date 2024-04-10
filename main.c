#include "main.h"

//system timer for 10ms
void timer2_init(void){
	//TCCR2A |=(1<<COM2A1);
	TCCR2A |=(1<<WGM21);
	TCCR2B |=(1<<CS20)|(1<<CS21)|(1<<CS22);
	TIMSK2 |=(1<<OCIE2A);
	OCR2A = 38;//2*1024*(1+38)/8000000=0.01
}
ISR (TIMER2_COMPA_vect){
	if(cnt1) cnt1--;
}
uint8_t e,d,s;


int main(void)
{		cli();
    	LCD_Init();
    	LCD_String("Hello World");
    	LCD_Command(0xC0);
    	LCD_Char(0x35);
		DDRC|=(1<<5);
		timer2_init();
		aaa = 0;
		sei();
		
    while (1) 
    {
		LCD_Command(0x80|0x00);//cursor is in position 0, (0 - F)
		//increasing the number by one		
		if(cnt1==0){
		aaa++;
		e=0;d=0;s=0;
		if(aaa>250) aaa=0;//count up to 250
		e=(aaa%100)%10;// select  single digit
		d=(aaa/10)%10;//select  decimal digit
		s=aaa/100;//select  hundred digit
		LCD_Clear();
		LCD_Char(0x30|s);LCD_Char(0x30|d);LCD_Char(0x30|e);
		cnt1=100;//wait 1s
		}		
    }
}

