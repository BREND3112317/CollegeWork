/******** KEY5.C******4*5��L��߽d��***************
*�ʧ@�G�bLCD���"KEY="�A�����LCD���4��Ʋ���ʧ@
*���}�G�CROW0=P10,ROW1=P11,ROW2=P12,ROW3=P13,ROW4=P14 
*      ��COL0=P20,COL1=P21,COL2=P22,COL3=P23 
*      P0=LCD��Data�AP16=RS�ARW=GND�AP17=EN
*****************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD

sfr  ROW=0x90;  //P1�����䱽�y��X���}
sbit COL0=P2^0;	//P2�����J���}
sbit COL1=P2^1;
sbit COL2=P2^2;
sbit COL3=P2^3;
char code  Table[]="KEY="; //�Ĥ@��}�C�r��

void dataout(uint8 keyout); //�����ƿ�X
unsigned char i=0;      //LCD��ܦ�m
unsigned long lcd_count;	//LCD��ܼƦr
void main()
{
 char count=0;   //����p��=0
 unsigned char scan=0xfe;  //���䱽�y�OROW0=0�A��l��1
 LCD_init();     	// ���m�βM��LCD
 LCD_Cmd(0x80);     //��ХѲĤ@��}�l���  
 for(i=0; i<4; i++) //Ū���}�C"KEY= "�r����LCD��ܥX�� 
   LCD_Data(Table[i]);   
 LCD_Disp(lcd_count); //LCD���4��ƤQ�i��Ʀr
 while(1)   //���а���
  {
    if(count>19){scan=0xfe;count=0;}//�Y�p��>19�A�q�Y�}�l
    ROW=scan;		  //���y��X
	if(COL0==0) dataout(count);//�ˬdCOL0�C�A�Y�O�p�ƿ�X
    count++; Delay_ms(1);      //�Y���O�A�p��+1
    if(COL1==0) dataout(count);//�ˬdCOL1�C�A�Y�O�p�ƿ�X
    count++; Delay_ms(1);      //�Y���O�A�p��+1
    if(COL2==0) dataout(count);//�ˬdCOL2�C�A�Y�O�p�ƿ�X
    count++; Delay_ms(1);      //�Y���O�A�p��+1
    if(COL3==0) dataout(count);//�ˬdCOL3�C�A�Y�O�p�ƿ�X
    count++; Delay_ms(1);      //�Y���O�A�p��+1
    scan=RL8(scan); //������A�����U�@�C,�OROW0~4���y��0
   }
}
/***********************************************************
*��ƦW��: dataout
*�\��y�z: �����X��ưe��LCD��ܼƦr�A�ˬd�O�_��}����
*��J�ѼơGkeyout
************************************************************/
void dataout(char keyout) 
{   
  LCD_Cmd(0x84);
  if(keyout<=9) //�����J0~9��
   {  
    lcd_count=(lcd_count*10)+keyout;  //�Ʀr�i��
                  //�Y�p�ƶW�L9999����ܫ�|�X
    if(lcd_count>9999) lcd_count=lcd_count % 10000; 
    LCD_Disp(lcd_count); //LCD���4��ƤQ�i��Ʀr
   }

  Delay_ms(1);       	//�B�z������ʤ�����
  while(!(COL0 & COL1 & COL2 & COL3));//�YCOL0~3��1111����}����
  Delay_ms(1);       //�B�z������ʤ�����
}
/*****************************************************
* ��ƦW��: LCD_Disp(unsigned int disp)
* �\��y�z: LCD���4��ƤQ�i��Ʀr
* ��J�ѼơGdisp
*******************************************************/
void LCD_Disp(unsigned int disp)  // LCD���4��ƤQ�i��Ʀr
{
 LCD_Data(disp /1000+'0');        //���X�d��Ʀr����LCD���
 LCD_Data(disp % 1000/100+'0');   //���X�ʦ�Ʀr����LCD���
 LCD_Data(disp % 100/10+'0');     //���X�Q��Ʀr����LCD���
 LCD_Data(disp % 10+'0');     	  //���X�Ӧ�Ʀr����LCD���
}
/***********************************************************
*��ƦW��: LCD_Data
*�\��y�z: �ǰe��ƨ��r��LCD
*��J�ѼơGdat
************************************************************/
void LCD_Data(char dat)  //�ǰe��ƨ�LCD
{
    Data=dat; //��ưe��BUS
    RS=1;EN=1;//��Ƽg�J��LCD��
    Delay_ms(1);   //LCD���ݼg�J����
    EN=0;          //�T��LCD    
}
/***************************************************************
*��ƦW��: LCD_Cmd
*�\��y�z: �ǰe�R�O���r��LCD
*��J�ѼơGCmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //�ǰe�R�O��LCD
{
    Data=Cmd;  //�R�O�e��BUS
    RS=0;EN=1; //�R�O�g�J��LCD��
    Delay_ms(1);    //LCD���ݼg�J����     
    EN=0;           //�T��LCD
}
/***************************************************************
*��ƦW��: LCD_init
*�\��y�z: �ҩl�Ƥ�r��LCD
*****************************************************************/
void LCD_init(void)    //LCD���ҩl�{��  
{
    LCD_Cmd(0x38);/*0011 1000,8bit�ǿ�,���2��,5*7�r��
                    bit4:DL=1,8bit�ǿ�,
                    bit3:N=1,���2��
                    bit2:F=0,5*7�r��*/    
    LCD_Cmd(0x0c);/*0000 1100,��ܹ�ON,����ܴ��,��Ф��{�{
                    bit2:D=1,��ܹ�ON
                    bit1:C=0,����ܴ��
	                bit0:B=0,��Ф��{�{*/
    LCD_Cmd(0x06);/*0000 0110,//��ܧ���Хk��,��в���T�� 
                    bit1:I/D=1,��ܧ���Хk��,
                    bit0:S=0,��в���T��*/  
    LCD_Cmd(0x01); //�M����ܹ�  
    LCD_Cmd(0x02); //��Ц^���  
}

