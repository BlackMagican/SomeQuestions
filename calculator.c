#include "reg52.h"			 
#include "stdlib.h"

typedef unsigned int uint;	  //���������ͽ�����������
typedef unsigned char uchar;
#define GPIO_DIG P0
#define GPIO_KEY P1
sbit LSA=P2^2;
sbit LSB=P2^3;
sbit LSC=P2^4;
sbit SPK=P1^5;
uint KeyValue;
int count;
uint total;
uint a;
uint flag = 0;
int c;
float t;
sbit k1=P3^1;    //k1�ǼӺ�
sbit k2=P3^0;    //k2�Ǽ���
sbit k3=P3^2;    //k3�ǵ��ں�
sbit k4=P3^3;    //�˺�
uchar code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//��ʾ0~F��ֵ

void delay(uint i)
{
	while(i--);	
}
void choose(uint i);
int getkey();
void ov_judge(uint n);
void sum();
void minus(); 
//void mul();       //��Ϊ�������ð������������Գ˷�����ֻ���ڻ�����ʵ��һ��
void division();
uint div_only;   //���ڳ��������Թʵ�����һ�����Ʊ���

void sum()
{
		while(k3)
		{
			ov_judge(count / 10);
			//��ȡ��һ������
			if(getkey())
			{
				count *= 10;
				count += KeyValue;
			}
		}
		count += total;
		ov_judge((count / 10));		
}

void minus()
{
	uint temp;
	flag = 0;
	while(k3)
		{
			ov_judge(count / 10);
			//��ȡ��һ������
			if(getkey())
			{
				count *= 10;
				count += KeyValue;
			}
		}
		temp = total;
		total = count;
		count = temp;
		count -= total;
		if(count < 0 )
		{
			flag = 1;
			count = -count;
		}
		ov_judge(count / 10);
}

void mul()
{
	while(k3)
		{
			ov_judge(count / 10);   //��Ҳ��֪����ʱզ��ķ����ͼ���һλ����ȥ��
			if(!k2)                 //���Ҫ��һ������
				{
					delay(1000);
					if(!k2)
					{
						flag = 1;   //�ȴ򿪸�����ʾ���أ���������һ������
						total = -total;
					}
				}
			//��ȡ��һ����
			if(getkey())
			{
				count *= 10;
				count += KeyValue;
			}
		}
		count *= total;
		if(count < 0 )
		{
			count = -count;
		}
		ov_judge((count / 10));
}

void division()
{
	div_only = 1;
	while(k3)
		{
			ov_judge(count / 10);   //��Ҳ��֪����ʱզ��ķ����ͼ���һλ����ȥ��
			if(!k2)                 //���Ҫ��һ������
				{
					delay(1000);
					if(!k2)
					{
						flag = 1;   //�ȴ򿪸�����ʾ���أ���������һ������
						total = -total;
					}
				}
			//��ȡ��һ����
			if(getkey())
			{
				count *= 10;
				count += KeyValue;
			}
		}
		t = total;
		c = count;
		if(c == 0)
		{
			while(1)
			{
				SPK = ~SPK;
				delay(2000);
			}
			
		}
		(double)(t /= c);
		t *= 100;
		c = t;
		count = c;
		if(count < 0 )
		{
			count = -count;
		}
		ov_judge((count / 10));
}

void ov_judge(uint n)   //��λ��
{
			choose(0);
			GPIO_DIG = smgduan[(count % 10)];
			delay(200);
			GPIO_DIG = 0xff;
			choose(1);
			GPIO_DIG = smgduan[(n % 10)];
			n /= 10;
			delay(200);
			GPIO_DIG = 0xff;
			choose(2);
			if(div_only)
			{
				GPIO_DIG = smgduan[(n % 10)];
				delay(200);
				GPIO_DIG = 0xff;
				GPIO_DIG = 0x80;
				delay(200);
				GPIO_DIG = 0xff;
			}
			GPIO_DIG = smgduan[(n % 10)];
			n /= 10;
			delay(200);
			GPIO_DIG = 0xff;
			choose(3);
			GPIO_DIG = smgduan[n];
			delay(200);
			GPIO_DIG = 0xff;
			if(flag)
			{
				choose(4);
				GPIO_DIG = 0x40;
				delay(200);
				GPIO_DIG = 0xff;
			}	
}

void main()
{
	void (*func[])() = {sum, minus, division};
	while(1)
	{
		ov_judge(count / 10);
   //��ȡ��ֵ
		if(getkey())
			{
				count *= 10;
				count += KeyValue;
			}
		if( !k1 || !k2 || !k4)
		{
			delay(1000);
			if(!k1)
			{
				total = count;
				count = 0;
			  (*func[0])();
			}else if(!k2)
			{
				total = count;
				count = 0;
				(*func[1])();
			}else if(!k4)
			{
				total = count;
				count = 0;
				(*func[2])();	
			}
	}
}
}	

int getkey(void)    //�������ɨ�躯��
{
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//��ȡ�����Ƿ���
	{
		delay(1000);//��ʱ10ms��������
		if(GPIO_KEY!=0x0f)//�ٴμ������Ƿ���
		{	
			//������
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//������
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY != 0xf0))	 //��ⰴ�����ּ��
			{
				delay(1000);
				a++;
			}
		}
		a = 0;
		return 1;
	}
	return 0;
}

void choose(uint i)
{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ
		}
}