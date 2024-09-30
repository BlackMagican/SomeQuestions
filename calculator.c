#include "reg52.h"			 
#include "stdlib.h"

typedef unsigned int uint;	  //对数据类型进行声明定义
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
sbit k1=P3^1;    //k1是加号
sbit k2=P3^0;    //k2是减号
sbit k3=P3^2;    //k3是等于号
sbit k4=P3^3;    //乘号
uchar code smgduan[17]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
					0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};//显示0~F的值

void delay(uint i)
{
	while(i--);	
}
void choose(uint i);
int getkey();
void ov_judge(uint n);
void sum();
void minus(); 
//void mul();       //因为初期设置按键的问题所以乘法除法只能在机子里实现一个
void division();
uint div_only;   //由于除法特殊性故单独设一个控制变量

void sum()
{
		while(k3)
		{
			ov_judge(count / 10);
			//获取另一个加数
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
			//获取另一个加数
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
			ov_judge(count / 10);   //我也不知道当时咋想的反正就减了一位传进去了
			if(!k2)                 //如果要乘一个负数
				{
					delay(1000);
					if(!k2)
					{
						flag = 1;   //先打开负数显示开关，表明这是一个负数
						total = -total;
					}
				}
			//获取另一个数
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
			ov_judge(count / 10);   //我也不知道当时咋想的反正就减了一位传进去了
			if(!k2)                 //如果要除一个负数
				{
					delay(1000);
					if(!k2)
					{
						flag = 1;   //先打开负数显示开关，表明这是一个负数
						total = -total;
					}
				}
			//获取另一个数
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

void ov_judge(uint n)   //进位后
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
   //获取键值
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

int getkey(void)    //矩阵键盘扫描函数
{
	GPIO_KEY=0x0f;
	if(GPIO_KEY!=0x0f)//读取按键是否按下
	{
		delay(1000);//延时10ms进行消抖
		if(GPIO_KEY!=0x0f)//再次检测键盘是否按下
		{	
			//测试列
			GPIO_KEY=0X0F;
			switch(GPIO_KEY)
			{
				case(0X07):	KeyValue=0;break;
				case(0X0b):	KeyValue=1;break;
				case(0X0d): KeyValue=2;break;
				case(0X0e):	KeyValue=3;break;
			}
			//测试行
			GPIO_KEY=0XF0;
			switch(GPIO_KEY)
			{
				case(0X70):	KeyValue=KeyValue;break;
				case(0Xb0):	KeyValue=KeyValue+4;break;
				case(0Xd0): KeyValue=KeyValue+8;break;
				case(0Xe0):	KeyValue=KeyValue+12;break;
			}
			while((a<50)&&(GPIO_KEY != 0xf0))	 //检测按键松手检测
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
		switch(i)	 //位选，选择点亮的数码管，
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//显示第0位
			case(1):
				LSA=1;LSB=0;LSC=0; break;//显示第1位
			case(2):
				LSA=0;LSB=1;LSC=0; break;//显示第2位
			case(3):
				LSA=1;LSB=1;LSC=0; break;//显示第3位
			case(4):
				LSA=0;LSB=0;LSC=1; break;//显示第4位
			case(5):
				LSA=1;LSB=0;LSC=1; break;//显示第5位
			case(6):
				LSA=0;LSB=1;LSC=1; break;//显示第6位
			case(7):
				LSA=1;LSB=1;LSC=1; break;//显示第7位
		}
}