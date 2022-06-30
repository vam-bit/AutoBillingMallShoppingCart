#include <REGX52.H>
#include <string.H>
#include "lcd.c"

sbit dev=P0^0;

sbit ir_in=P3^0;
sbit ir_out=P3^1;

bit dev_stat = 0;

unsigned int counter;

void intro()
{
	lcdclr();
	lcdinit();
	lcdstr("Auto Billing Mal ");
	lcdcmd(0xc0);
	lcdstr(" Shopping Cart ");
	delay(65000);delay(65000);
	lcdclr();
}	

void convert(unsigned int g)
{
	unsigned char temp,i=0,j=0;
	unsigned int x=10000;
	if(g==0)
	{
		lcddata('0');
	}
	else
	{
	 while(x)
	 {
		temp=g/x;
		if((temp!=0)&&(i==0))
			i++;
		if((temp!=0)||(i!=0))
			lcddata(temp+0x30);
		g-=(x*temp);
		x/=10;
	 }
	}
	lcdstr("   ");
}

void main()
{
// 	unsigned char check,i,pass[5],status,temp;
	dev=0;
	intro();
	lcdcmd(0x80);
	lcdstr("Counter: 0      ");
	lcdcmd(0xc0);
	lcdstr(" Waiting For Product");
	delay(65000);delay(65000);
	while(1)
	{
		while((ir_in) && (ir_out));
		if(!ir_in)
		{
		 counter++;
		 lcdcmd(0x89);
		 convert(counter);
		 lcdcmd(0xc0);
		 lcdstr("   Product Add   ");
		 dev=1;
		 delay(6000);
		 while(!ir_in);
		}
		else if((!ir_out) && (counter!=0))
		{
		 counter--;
		 lcdcmd(0x89);
		 convert(counter);
		 if (!counter)
		 {	 
			dev=0; 
		  lcdcmd(0xc0);
		  lcdstr(" Product Remove ");
		  delay(6000);
		 } 
		 while(!ir_out);
		}
	}
}
