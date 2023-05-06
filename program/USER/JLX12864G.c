#include "JLX12864G.h"
#include "lcd_char_code.c"
#include "string.h"
#include <stdio.h>

//用“zimo221.exe”取模出来的汉字的16进制码：
unsigned char zhuang1[]={
/*--  文字:  状  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x08,0x30,0x00,0xFF,0x20,0x20,0x20,0x20,0xFF,0x20,0xE1,0x26,0x2C,0x20,0x20,0x00,
0x04,0x02,0x01,0xFF,0x40,0x20,0x18,0x07,0x00,0x00,0x03,0x0C,0x30,0x60,0x20,0x00};

unsigned char tai1[]={
/*--  文字:  态  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x04,0x04,0x04,0x84,0x44,0x34,0x4F,0x94,0x24,0x44,0x84,0x84,0x04,0x00,0x00,
0x00,0x60,0x39,0x01,0x00,0x3C,0x40,0x42,0x4C,0x40,0x40,0x70,0x04,0x09,0x31,0x00};

unsigned char shi1[]={
/*--  文字:  使  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x40,0x20,0xF0,0x1C,0x07,0xF2,0x94,0x94,0x94,0xFF,0x94,0x94,0x94,0xF4,0x04,0x00,
0x00,0x00,0x7F,0x00,0x40,0x41,0x22,0x14,0x0C,0x13,0x10,0x30,0x20,0x61,0x20,0x00};

unsigned char yong1[]={
/*--  文字:  用  --*/
/*--  宋体12;  此字体下对应的点阵为：宽x高=16x16   --*/
0x00,0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x80,0x40,0x30,0x0F,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x42,0x82,0x7F,0x00,0x00};


/********************************************************************************
//LCD端口初始化
// LCD_CS:PB10
// LCD_RST:PB11
// LCD_RS:PB13
// LCD_SDA:PB14
// LCD_SCLK:PA8
// LCD_LED:PA9  背光灯
*********************************************************************************/

void LCD_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_ResetBits(GPIOA, GPIO_Pin_8 | GPIO_Pin_9 );	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_ResetBits(GPIOB, GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_13 | GPIO_Pin_14 );	

}


/*延时*/
void delay(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<110;k++);
}

/*
//短延时
void delay_us(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<1;k++);
}
*/


/*写指令到LCD模块*/
void transfer_command(int data1)   
{
	char i;
	LCD_CS_0;
	LCD_RS_0 ;
	for(i=0;i<8;i++)
	{
		LCD_SCLK_0;
		if(data1&0x80) LCD_SDA_1;
		else LCD_SDA_0;
		LCD_SCLK_1;
		data1<<=1;
	}
	LCD_CS_1;
}

/*写数据到LCD模块*/
void transfer_data(int data1)
{
	char i;
	LCD_CS_0;
	LCD_RS_1;
	for(i=0;i<8;i++)
	{
		LCD_SCLK_0;
		if(data1&0x80) LCD_SDA_1;
		else LCD_SDA_0;
		LCD_SCLK_1;
		data1<<=1;
	}
	LCD_CS_1;
}


/*LCD模块初始化*/
void initial_lcd()
{
	LCD_CS_0;
  	LCD_RST_0;        /*低电平复位*/
  	delay(500);
  	LCD_RST_1;		    /*复位完毕*/
  	delay(200);        
	transfer_command(0xe2);	 /*软复位*/
	delay(50);
	transfer_command(0x2c);  /*升压步聚1*/
	delay(50);	
	transfer_command(0x2e);  /*升压步聚2*/
	delay(50);
	transfer_command(0x2f);  /*升压步聚3*/
	delay(50);
	transfer_command(0x23);  /*粗调对比度，可设置范围0x20～0x27*/
	transfer_command(0x81);  /*微调对比度*/
	transfer_command(0x28);  /*0x28,微调对比度的值，可设置范围0x00～0x3f*/
	transfer_command(0xa2);  /*1/9偏压比（bias）*/
	transfer_command(0xc8);  /*行扫描顺序：从上到下*/
	transfer_command(0xa0);  /*列扫描顺序：从左到右*/
	transfer_command(0x40);  /*起始行：第一行开始*/
	transfer_command(0xaf);  /*开显示*/
}


void lcd_address(unsigned char page,unsigned char column)
{
	column=column-1;  							//我们平常所说的第1列，在LCD驱动IC里是第0列。所以在这里减去1.
	page=page-1;
	transfer_command(0xb0+page);   			//设置页地址。每页是8行。一个画面的64行被分成8个页。我们平常所说的第1页，在LCD驱动IC里是第0页，所以在这里减去1*/
	transfer_command(((column>>4)&0x0f)+0x10);	//设置列地址的高4位
	transfer_command(column&0x0f);				//设置列地址的低4位
}

/*全屏清屏*/
void clear_screen()
{
	unsigned char i,j;
 	for(i=0;i<9;i++)
	{
		lcd_address(1+i,1);
		for(j=0;j<132;j++)
		{
			transfer_data(0x00);
		}
	}
}




//显示16x16点阵图像、汉字。
//括号里的参数分别是（页，列，闪烁与否，反显与否，数据指针）
void disp_blink_16x16(unsigned char page,unsigned char column,unsigned char blink,unsigned char reverse,unsigned char *dp)
{
	unsigned char i,j,k,*data_temp;
	if(blink==0)
	{
		data_temp=dp;
		for(j=0;j<2;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<16;i++)
			{	
				if(reverse==1)
				{
					transfer_data(~*data_temp);	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				else
				{
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				data_temp++;
			}
		}
	}

	else
	{
		for(k=0;k<10;k++)
		{
			data_temp=dp;
			for(j=0;j<2;j++)
			{
				lcd_address(page+j,column);
				for (i=0;i<16;i++)
				{	
					transfer_data(~*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
					data_temp++;
				}
			}
			delay(2000);
			data_temp=dp;
			for(j=0;j<2;j++)
			{
				lcd_address(page+j,column);
				for (i=0;i<16;i++)
				{	
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
					data_temp++;
				}
			}
			delay(2000);

	   	}
	}
}

//显示16x16点阵图像、汉字。
//括号里的参数分别是（页，列，带下划线闪烁与否，反显与否，数据指针）
void disp_underline_16x16(unsigned char page,unsigned char column,unsigned char under,unsigned char reverse,unsigned char *dp)
{
	unsigned char i,j,k,*data_temp,data1;
	if(under==0)
	{
		data_temp=dp;
		for(j=0;j<2;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<16;i++)
			{	
				if(reverse==1)
				{
					transfer_data(~*data_temp);	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				else
				{
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				data_temp++;
			}
		}
	}

	else
	{
		for(k=0;k<10;k++)
		{
			data_temp=dp;
	
			lcd_address(page,column);
			for (i=0;i<16;i++)
			{	
				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
			lcd_address(page+1,column);
			for (i=0;i<16;i++)
			{	
				data1=*data_temp|0x80;
				transfer_data(data1);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
			delay(2000);


			data_temp=dp;
			for(j=0;j<2;j++)
			{
				lcd_address(page+j,column);
				for (i=0;i<16;i++)
				{	
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
					data_temp++;
				}
			}
			delay(2000);

	   	}
	}
}



//显示16x16点阵图像、汉字。
//括号里的参数分别是（页，列，带右竖线光标闪烁与否，反显与否，数据指针）
void disp_cursor_16x16(unsigned char page,unsigned char column,unsigned char cursor,unsigned char reverse,unsigned char  *dp)
{
	unsigned char i,j,k,*data_temp;
	if(cursor==0)
	{
		data_temp=dp;
		for(j=0;j<2;j++)
		{
			lcd_address(page+j,column);
			for (i=0;i<16;i++)
			{	
				if(reverse==1)
				{
					transfer_data(~*data_temp);	/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				else
				{
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				}
				data_temp++;
			}
		}
	}

	else
	{
		for(k=0;k<10;k++)
		{
			data_temp=dp;
	
			lcd_address(page,column);
			for (i=0;i<15;i++)
			{	
				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
			transfer_data(0xff);
			data_temp++;
			lcd_address(page+1,column);
			for (i=0;i<15;i++)
			{	
				transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
				data_temp++;
			}
			transfer_data(0xff);
			data_temp++;
			delay(2000);


			data_temp=dp;
			for(j=0;j<2;j++)
			{
				lcd_address(page+j,column);
				for (i=0;i<16;i++)
				{	
					transfer_data(*data_temp);		/*写数据到LCD,每写完一个8位的数据后列地址自动加1*/
					data_temp++;
				}
			}
			delay(2000);

	   	}
	}
}


void display_string_8x16(unsigned int page,unsigned int column,char  *text)
{
  unsigned int i=0,j,k,n;
  LCD_CS_0;
  while(text[i]>0x00)
  {
    if((text[i]>=0x20)&&(text[i]<=0x7e))
    {
      j=text[i]-0x20;
      for(n=0;n<2;n++)
      {
        lcd_address(page+n,column);
        for(k=0;k<8;k++)
        {
           transfer_data(ascii_table_8x16[j][k+8*n]);/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
        }
      }
      i++;
      column+=8;
    }
    else
      i++;
  }
}

void display_string_8x16_under(unsigned int page,unsigned int column,char  *text)
{
  unsigned int i=0,j,k,n;
  LCD_CS_0;
  while(text[i]>0x00)
  {
    if((text[i]>=0x20)&&(text[i]<=0x7e))
    {
      j=text[i]-0x20;
      for(n=0;n<2;n++)
      {
        lcd_address(page+n,column);
        for(k=0;k<8;k++)
        {
					 if(n==0){
						 transfer_data(ascii_table_8x16[j][k+8*n]);/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
					 }else{
						 transfer_data(ascii_table_8x16[j][k+8*n]|0x40);/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
					 }
           
        }
      }
      i++;
      column+=8;
    }
    else
      i++;
  }
}


void display_string_5x8(unsigned int page,unsigned int column,char *text)
{
  unsigned int i=0,j,k;
  LCD_CS_0;
  while(text[i]>0x00)
  {
    if((text[i]>=0x20)&&(text[i]<0x7e))
    {
      j=text[i]-0x20;
      lcd_address(page,column);
      for(k=0;k<5;k++)
      {
        transfer_data(ascii_table_5x8[j][k]);/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
      }
			transfer_data(0);
      i++;
      column+=6;
    }
    else
      i++;
  }
}

void display_string_5x8_r(unsigned int page,unsigned int column,char *text)
{
  unsigned int i=0,j,k;
  LCD_CS_0;
  while(text[i]>0x00)
  {
    if((text[i]>=0x20)&&(text[i]<0x7e))
    {
      j=text[i]-0x20;
      lcd_address(page,column);
      for(k=0;k<5;k++)
      {
        transfer_data(~ascii_table_5x8[j][k]);/*显示5x7 的ASCII 字到LCD 上，y 为页地址，x 为列地址，最后为数据*/
      }
			transfer_data(0xff);
      i++;
      column+=6;
    }
    else
      i++;
  }
}

/*显示128*64点阵的图像*/
void disp_128x64(int x,int y,uint8_t const *dp)
{
	int i,j;
	//lcd_address(x,y);
	for(i=0;i<8;i++)	  
	{
		lcd_address(x++,y);
		for(j=0;j<128;j++)  
		{
			transfer_data(*dp);
			dp++;
		}
	}
}


/*显示63*56点阵的图像*/
void disp_63x56(int x,int y,uint8_t const *dp)
{
	int i,j;
	//lcd_address(x,y);
	for(i=0;i<7;i++)	  
	{
		lcd_address(x++,y);
		for(j=0;j<63;j++)  
		{
			transfer_data(*dp);
			dp++;
		}
	}
}


unsigned char  dis_ico(unsigned char data)
{
	switch(data){
		case 0:
			disp_63x56(1,1,gImage_pulse_ico0);			
		  display_string_5x8(8, 1,"                        ");
		break;
		case 1:
			disp_63x56(1,1,gImage_pulse_ico1);	
		  display_string_5x8(8, 1,"TURN OFF OUT            ");
		break;
		case 2:
			disp_63x56(1,1,gImage_pulse_ico2);	
		  display_string_5x8(8, 1,"ALL-DAY OUT WORK        ");
		break;
		case 3:
			disp_63x56(1,1,gImage_pulse_ico3);	
		  display_string_5x8(8, 1,"NIGHT OUT WORK          ");
		break;
		case 4:
			disp_63x56(1,1,gImage_pulse_ico4);
      display_string_5x8(8, 1,"DAY OUT WORK            ");		
		break;	
		case 5:
			disp_63x56(1,1,gImage_pulse_ico0);
		  display_string_5x8_r(8, 1,"!");	
		  display_string_5x8_r(8, 2,"SET LIGHT DATA        ");		
		break;	
		case 6:
			disp_63x56(1,1,gImage_pulse_ico0);
		  display_string_5x8_r(8, 1,"!");	
		  display_string_5x8_r(8, 2,"SET INPUT VOLTAGE     ");		
		break;	
		
		case 7:
			disp_63x56(1,1,gImage_pulse_ico0);
		  display_string_5x8_r(8, 1,"!");	
		  display_string_5x8_r(8, 2,"SET OUT VOLTAGE       ");		
		break;	
		
	}
	return 0xff;
	
}

void dis_intput_voltage(float voltage)
{
	char   lcd_string[24];
	sprintf(&lcd_string[0],"%-.1fV",voltage);	
	sprintf(&lcd_string[0],"%5s",lcd_string);
	display_string_8x16_under(6, 74,lcd_string);	
}


void dis_light_num(uint8_t light_data)
{
	char   lcd_string[24];
	sprintf(&lcd_string[0],"LIGHT:%-3d",light_data);	
	display_string_5x8(3,70,lcd_string);	
}

//最大数据58
#define MAX_BAR   58
void dis_bar(uint8_t bar_data)
{
	uint8_t i;
  if(bar_data>MAX_BAR)bar_data=MAX_BAR;
	for(i=0;i<MAX_BAR;i++)
	{
		lcd_address(2,67+i);
		if(i<bar_data){
			transfer_data(0x7f);
		}else{
			transfer_data(0x41);
		}		
	}
}


void dis_alarm_point(uint8_t alarm_data)
{
	uint8_t i;
  if(alarm_data>MAX_BAR)alarm_data=MAX_BAR;
	for(i=0;i<MAX_BAR+4;i++)
	{
		lcd_address(1,65+i);
		transfer_data(0x01);
	}
	
	lcd_address(1,67+alarm_data);
	transfer_data(0x71);
	lcd_address(1,67+alarm_data-1);
	transfer_data(0x31);
	lcd_address(1,67+alarm_data+1);
	transfer_data(0x31);
	lcd_address(1,67+alarm_data-2);
	transfer_data(0x11);
	lcd_address(1,67+alarm_data+2);
	transfer_data(0x11);
}




void sub_main(void)
{ 
	initial_lcd();
	clear_screen();
	//while(1)
	//{
		
   //  clear_screen();
    //display_string_8x16(1, 1,"0123456789012345");
		//display_string_5x8(3, 1,"0123456789012345");
		disp_128x64(1,1,gImage_pulse1);
		
		display_string_5x8(5, 80,"POWER");
		//display_string_8x16_under(6, 74,"12.5V");
//		display_string_8x16(2, 3,0,">Sensor Setting         ");
//		delay(20000);
//		delay(20000);
//		delay(20000);
////		clear_screen();    						//clear all dots		
//		disp_blink_16x16(5, 1,0,1,zhuang1); 	//显示单个汉字"状". 括号里的参数分别是（页，列，闪烁与否，反显与否，数据指针）
//		disp_blink_16x16(5,17,0,0,tai1);		//显示单个汉字"态",不闪烁，反显
//		disp_blink_16x16(5,33,1,0,shi1); 		//显示单个汉字"使",闪烁，不反显
//		disp_blink_16x16(5,49,1,1,yong1);		//显示单个汉字"用",闪烁，反显（当有闪烁时，反显不起作用）
//		//waitkey();
//		delay(20000);
//	//	clear_screen();    						//clear all dots		
//		disp_underline_16x16(5, 1,0,1,zhuang1); //显示单个汉字"状". 括号里的参数分别是（页，列，是否有下划线闪烁，反显与否，数据指针）
//		disp_underline_16x16(5,17,0,0,tai1);	//显示单个汉字"态"
//		disp_underline_16x16(5,33,1,0,shi1); 	//显示单个汉字"使"
//		disp_underline_16x16(5,49,1,1,yong1);	//显示单个汉字"用"
//		delay(20000);

//	//	clear_screen();    						//clear all dots		
//		disp_cursor_16x16(5, 1,0,1,zhuang1); 	//显示单个汉字"状". 括号里的参数分别是（页，列，是否右竖线光标闪烁，反显与否，数据指针）
//		disp_cursor_16x16(5,17,0,0,tai1);		//显示单个汉字"态"
//		disp_cursor_16x16(5,33,1,0,shi1); 		//显示单个汉字"使"
//		disp_cursor_16x16(5,49,1,1,yong1);		//显示单个汉字"用"
//		delay(20000);

//	}
}


