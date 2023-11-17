#include <STC15F2K60S2.H>

unsigned char Seg_Tab[] = {0xc0, 0xf9, 0xa4, 0xb0, 0x99, 0x92, 0x82, 0xf8, 0x80, 0x90, 0xff};
unsigned char Seg_Buf[8];

void Seg_Buf_Change(unsigned char _0, _1, _2, _3, _4, _5, _6, _7)
{
	Seg_Buf[0] = _0;
	Seg_Buf[1] = _1;
	Seg_Buf[2] = _2;
	Seg_Buf[3] = _3;
	Seg_Buf[4] = _4;
	Seg_Buf[5] = _5;
	Seg_Buf[6] = _6;
	Seg_Buf[7] = _7;
}

void disp()
{
	static unsigned char Seg_Pos = 0;
	P2 = (P2 & 0x1F) | 0xE0;
	P0 = 0xFF;
	P2 = (P2 & 0x1F) | 0xC0;
	P0 = 1 << Seg_Pos;
	P2 = (P2 & 0x1F) | 0xE0;
	P0 = Seg_Buf[Seg_Pos];
	Seg_Pos = (Seg_Pos + 1) % 8;
}
	
void Timer0_Isr() interrupt 1
{
	disp();
}

void Timer0_Init()		//2����@12.000MHz
{
	AUXR |= 0x80;			//��ʱ��ʱ��1Tģʽ
	TMOD &= 0xF0;			//���ö�ʱ��ģʽ
	TL0 = 0x40;				//���ö�ʱ��ʼֵ
	TH0 = 0xA2;				//���ö�ʱ��ʼֵ
	TF0 = 0;				//���TF0��־
	TR0 = 1;				//��ʱ��0��ʼ��ʱ
	ET0 = 1;				//ʹ�ܶ�ʱ��0�ж�
	EA = 1;
}

void main()
{
	Timer0_Init();
	Seg_Buf_Change(Seg_Tab[8], Seg_Tab[7], Seg_Tab[6], Seg_Tab[5], Seg_Tab[4], Seg_Tab[3], Seg_Tab[2], Seg_Tab[1]);
	while (1)
	{
		;
	}
}