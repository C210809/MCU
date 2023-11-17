/* ͷ�ļ��� */
#include <STC15F2K60S2.H>
#include <INIT.H>
#include <SEG.H>
#include <AT24C02.H>

/* ������ */
unsigned char Seg_Pos;
unsigned char Seg_Buf[8] = {10, 10, 10, 10, 10, 10, 10, 10};
unsigned char addr, dat;

/* ��ʱ��0��ʼ������ */
void Timer0_Init()		//1����@12.000MHz
{
	AUXR &= 0x7F;			//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x18;				//���ö�ʱ��ʼֵ
	TH0 = 0xFC;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
	EA = 1;
}


/* ��ʱ��0�жϷ�����*/
void Timer0_Isr() interrupt 1 
{
	if ( ++ Seg_Pos == 8) Seg_Pos = 0;
	Seg_Disp(Seg_Pos, Seg_Buf[Seg_Pos], 0);
	
	
}

/* Main */
void main() 
{
	Sys_Init();
	Timer0_Init();
	addr = 0x00;
	dat = At24c02_Byte_Read(addr);
	At24c02_Byte_Write(addr, dat + 1);
	Seg_Buf[5] = (dat / 100) % 10;
	Seg_Buf[6] = (dat / 10) % 10;
	Seg_Buf[7] = dat % 10;
	while (1) 
	{
		;
	}
}