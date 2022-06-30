//sbit rs=P3^7;
//sbit en=P3^6;
//sbit rw=P3^5;

sbit rs=P0^5;
sbit rw=P0^6;
sbit en=P0^7;

void delay(unsigned int i)
{
	while(i--);
}
	
void lcdcmd(unsigned char c)
{
	rs=0;P2=c;
	en=1;delay(20);en=0;
}	

void lcddata(unsigned char d)
{
	rs=1;P2=d;
	en=1;delay(20);en=0;
}	

void lcdinit()
{
	rw=0;
	lcdcmd(0x38);
	lcdcmd(0x80);
	lcdcmd(0x0c);
}

void lcdstr(unsigned char *s)
{
 while(*s)
 	lcddata(*s++);
}

void lcdclr()
{
 lcdcmd(0x01);
 delay(200);
 lcdcmd(0x80);
}