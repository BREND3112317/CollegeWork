/************** LCD1.C **********************************
*�ʧ@�G��LCD��ܨ���r,�O��{�{�β���
***********************************************/
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P10 LCD���O/��Ʊ���,RS=0���O�ARS=1���
sbit RW=0x91;  //P11 LCDŪ��/�g�J����,RW=0�g�J�ARW=1Ū��
sbit EN=0x97;  //P12 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
void main(void)
{
   char i;        //��ƭp��
   Delay_ms(40);						//<--
   LCD_init();    //���m�βM��LCD    
   //LCD_Cmd(0x0F);//0000 1111
                   //bit2:D=1,��ܹ�ON
                   //bit1:C=1,��ܴ��
	               //bit0:B=1,��а{�{
  //LCD_Cmd(0x04); //0000 0100,
                   //bit1:I/D=0�A��Х����ϦV���
    
   LCD_Cmd(0x85); //��ХѲĤ@���5�Ӧr�}�l���  
   for(i='0'; i<= '9';i++)//�r��0~9 
    {
	 LCD_Data(i);  //�r���e��LCD���   
     Delay_ms(10);//���ɡA�C�t�E�@���
	}

   LCD_Cmd(0xC5); //��ХѲĤG���5�Ӧr�}�l���   
   for(i='A'; i<= 'J';i++)//LCD��ܦr��A~J 
    {
	 LCD_Data(i);  //�r���e��LCD���   
     Delay_ms(10);//���ɡA�C�t�E�@���
	}

	while(1)   //�������`������
     {  //��ܥH�U�䤤�\��Ӱ���
 	   //LCD_Cmd(0x08); Delay_ms(10);//D=0������ܾ�
       //LCD_Cmd(0x0c); Delay_ms(10);//D=1�}����ܾ�
       //LCD_Cmd(0x1c); Delay_ms(10);//SC=1��RL=1��ܹ��k��
       //LCD_Cmd(0x18); Delay_ms(10);//SC=1��RL=0��ܹ�����
     }  
}
/***********************************************************
*��ƦW��: LCD_Data
*�\��y�z: �ǰe��ƨ��r��LCD
*��J�ѼơGdat
************************************************************/
void LCD_Data(char dat)  //�ǰe��ƨ�LCD
{
    Data=dat; //��ưe��BUS
    RS=1;RW=0;EN=1;//��Ƽg�J��LCD��
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
    RS=0;RW=0;EN=1; //�R�O�g�J��LCD��
    Delay_ms(1);    //LCD���ݼg�J����     
    EN=0;           //�T��LCD
}
/***************************************************************
*��ƦW��: LCD_init
*�\��y�z: �ҩl�Ƥ�r��LCD
*****************************************************************/
void LCD_init(void)    //LCD���ҩl�{��  
{
    LCD_Cmd(0x38);
	Delay_ms(1);
	LCD_Cmd(0x38);
	Delay_ms(1);
	/*0011 1000,8bit�ǿ�,���2��,5*7�r��
                    bit4:DL=1,8bit�ǿ�,
                    bit3:N=1,���2��
                    bit2:F=0,5*7�r��*/    
    LCD_Cmd(0x0c);
	Delay_ms(1);  /*0000 1100,��ܹ�ON,����ܴ��,��Ф��{�{
                    bit2:D=1,��ܹ�ON
                    bit1:C=0,����ܴ��
	                bit0:B=0,��Ф��{�{*/
    LCD_Cmd(0x06);
	Delay_ms(1);  /*0000 0110,//��ܧ���Хk��,��в���T�� 
                    bit1:I/D=1,��ܧ���Хk��,
                    bit0:S=0,��в���T��*/  
    LCD_Cmd(0x01);
	Delay_ms(1); //�M����ܹ�  

    LCD_Cmd(0x02);
	Delay_ms(1); //��Ц^���  
}