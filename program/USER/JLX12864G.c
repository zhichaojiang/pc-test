#include "JLX12864G.h"
#include "lcd_char_code.c"
#include "string.h"
#include <stdio.h>

//�á�zimo221.exe��ȡģ�����ĺ��ֵ�16�����룺
unsigned char zhuang1[]={
/*--  ����:  ״  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x08,0x30,0x00,0xFF,0x20,0x20,0x20,0x20,0xFF,0x20,0xE1,0x26,0x2C,0x20,0x20,0x00,
0x04,0x02,0x01,0xFF,0x40,0x20,0x18,0x07,0x00,0x00,0x03,0x0C,0x30,0x60,0x20,0x00};

unsigned char tai1[]={
/*--  ����:  ̬  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x04,0x04,0x04,0x84,0x44,0x34,0x4F,0x94,0x24,0x44,0x84,0x84,0x04,0x00,0x00,
0x00,0x60,0x39,0x01,0x00,0x3C,0x40,0x42,0x4C,0x40,0x40,0x70,0x04,0x09,0x31,0x00};

unsigned char shi1[]={
/*--  ����:  ʹ  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x40,0x20,0xF0,0x1C,0x07,0xF2,0x94,0x94,0x94,0xFF,0x94,0x94,0x94,0xF4,0x04,0x00,
0x00,0x00,0x7F,0x00,0x40,0x41,0x22,0x14,0x0C,0x13,0x10,0x30,0x20,0x61,0x20,0x00};

unsigned char yong1[]={
/*--  ����:  ��  --*/
/*--  ����12;  �������¶�Ӧ�ĵ���Ϊ����x��=16x16   --*/
0x00,0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,
0x80,0x40,0x30,0x0F,0x02,0x02,0x02,0x02,0xFF,0x02,0x02,0x42,0x82,0x7F,0x00,0x00};


/********************************************************************************
//LCD�˿ڳ�ʼ��
// LCD_CS:PB10
// LCD_RST:PB11
// LCD_RS:PB13
// LCD_SDA:PB14
// LCD_SCLK:PA8
// LCD_LED:PA9  �����
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


/*��ʱ*/
void delay(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<110;k++);
}

/*
//����ʱ
void delay_us(int i)               
{
	int j,k;
	for(j=0;j<i;j++)
		for(k=0;k<1;k++);
}
*/


/*дָ�LCDģ��*/
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

/*д���ݵ�LCDģ��*/
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


/*LCDģ���ʼ��*/
void initial_lcd()
{
	LCD_CS_0;
  	LCD_RST_0;        /*�͵�ƽ��λ*/
  	delay(500);
  	LCD_RST_1;		    /*��λ���*/
  	delay(200);        
	transfer_command(0xe2);	 /*��λ*/
	delay(50);
	transfer_command(0x2c);  /*��ѹ����1*/
	delay(50);	
	transfer_command(0x2e);  /*��ѹ����2*/
	delay(50);
	transfer_command(0x2f);  /*��ѹ����3*/
	delay(50);
	transfer_command(0x23);  /*�ֵ��Աȶȣ������÷�Χ0x20��0x27*/
	transfer_command(0x81);  /*΢���Աȶ�*/
	transfer_command(0x28);  /*0x28,΢���Աȶȵ�ֵ�������÷�Χ0x00��0x3f*/
	transfer_command(0xa2);  /*1/9ƫѹ�ȣ�bias��*/
	transfer_command(0xc8);  /*��ɨ��˳�򣺴��ϵ���*/
	transfer_command(0xa0);  /*��ɨ��˳�򣺴�����*/
	transfer_command(0x40);  /*��ʼ�У���һ�п�ʼ*/
	transfer_command(0xaf);  /*����ʾ*/
}


void lcd_address(unsigned char page,unsigned char column)
{
	column=column-1;  							//����ƽ����˵�ĵ�1�У���LCD����IC���ǵ�0�С������������ȥ1.
	page=page-1;
	transfer_command(0xb0+page);   			//����ҳ��ַ��ÿҳ��8�С�һ�������64�б��ֳ�8��ҳ������ƽ����˵�ĵ�1ҳ����LCD����IC���ǵ�0ҳ�������������ȥ1*/
	transfer_command(((column>>4)&0x0f)+0x10);	//�����е�ַ�ĸ�4λ
	transfer_command(column&0x0f);				//�����е�ַ�ĵ�4λ
}

/*ȫ������*/
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




//��ʾ16x16����ͼ�񡢺��֡�
//������Ĳ����ֱ��ǣ�ҳ���У���˸��񣬷����������ָ�룩
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
					transfer_data(~*data_temp);	/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				}
				else
				{
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
					transfer_data(~*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
					data_temp++;
				}
			}
			delay(2000);

	   	}
	}
}

//��ʾ16x16����ͼ�񡢺��֡�
//������Ĳ����ֱ��ǣ�ҳ���У����»�����˸��񣬷����������ָ�룩
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
					transfer_data(~*data_temp);	/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				}
				else
				{
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
				transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				data_temp++;
			}
			lcd_address(page+1,column);
			for (i=0;i<16;i++)
			{	
				data1=*data_temp|0x80;
				transfer_data(data1);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				data_temp++;
			}
			delay(2000);


			data_temp=dp;
			for(j=0;j<2;j++)
			{
				lcd_address(page+j,column);
				for (i=0;i<16;i++)
				{	
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
					data_temp++;
				}
			}
			delay(2000);

	   	}
	}
}



//��ʾ16x16����ͼ�񡢺��֡�
//������Ĳ����ֱ��ǣ�ҳ���У��������߹����˸��񣬷����������ָ�룩
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
					transfer_data(~*data_temp);	/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				}
				else
				{
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
				transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
				data_temp++;
			}
			transfer_data(0xff);
			data_temp++;
			lcd_address(page+1,column);
			for (i=0;i<15;i++)
			{	
				transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
					transfer_data(*data_temp);		/*д���ݵ�LCD,ÿд��һ��8λ�����ݺ��е�ַ�Զ���1*/
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
           transfer_data(ascii_table_8x16[j][k+8*n]);/*��ʾ5x7 ��ASCII �ֵ�LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
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
						 transfer_data(ascii_table_8x16[j][k+8*n]);/*��ʾ5x7 ��ASCII �ֵ�LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
					 }else{
						 transfer_data(ascii_table_8x16[j][k+8*n]|0x40);/*��ʾ5x7 ��ASCII �ֵ�LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
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
        transfer_data(ascii_table_5x8[j][k]);/*��ʾ5x7 ��ASCII �ֵ�LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
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
        transfer_data(~ascii_table_5x8[j][k]);/*��ʾ5x7 ��ASCII �ֵ�LCD �ϣ�y Ϊҳ��ַ��x Ϊ�е�ַ�����Ϊ����*/
      }
			transfer_data(0xff);
      i++;
      column+=6;
    }
    else
      i++;
  }
}

/*��ʾ128*64�����ͼ��*/
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


/*��ʾ63*56�����ͼ��*/
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

//�������58
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
//		disp_blink_16x16(5, 1,0,1,zhuang1); 	//��ʾ��������"״". ������Ĳ����ֱ��ǣ�ҳ���У���˸��񣬷����������ָ�룩
//		disp_blink_16x16(5,17,0,0,tai1);		//��ʾ��������"̬",����˸������
//		disp_blink_16x16(5,33,1,0,shi1); 		//��ʾ��������"ʹ",��˸��������
//		disp_blink_16x16(5,49,1,1,yong1);		//��ʾ��������"��",��˸�����ԣ�������˸ʱ�����Բ������ã�
//		//waitkey();
//		delay(20000);
//	//	clear_screen();    						//clear all dots		
//		disp_underline_16x16(5, 1,0,1,zhuang1); //��ʾ��������"״". ������Ĳ����ֱ��ǣ�ҳ���У��Ƿ����»�����˸�������������ָ�룩
//		disp_underline_16x16(5,17,0,0,tai1);	//��ʾ��������"̬"
//		disp_underline_16x16(5,33,1,0,shi1); 	//��ʾ��������"ʹ"
//		disp_underline_16x16(5,49,1,1,yong1);	//��ʾ��������"��"
//		delay(20000);

//	//	clear_screen();    						//clear all dots		
//		disp_cursor_16x16(5, 1,0,1,zhuang1); 	//��ʾ��������"״". ������Ĳ����ֱ��ǣ�ҳ���У��Ƿ������߹����˸�������������ָ�룩
//		disp_cursor_16x16(5,17,0,0,tai1);		//��ʾ��������"̬"
//		disp_cursor_16x16(5,33,1,0,shi1); 		//��ʾ��������"ʹ"
//		disp_cursor_16x16(5,49,1,1,yong1);		//��ʾ��������"��"
//		delay(20000);

//	}
}


