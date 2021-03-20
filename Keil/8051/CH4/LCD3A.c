//************* LCD3A.c *********************
//*�ʧ@�G�bLCD��ܤW�U��12�p�ɹq�l�����ܤ�
//*******************************************
#include "..\AT89X52.H"   //�Ȧs���βպA�w�q
sfr  Data=0x80;//P0���BUS��X
sbit RS=0x96;  //P16 LCD���O/��Ʊ���,RS=0���O�ARS=1���
               //LCDŪ��/�g�J����,R/W=GND�g�J
sbit EN=0x97;  //P17 LCD�P���X,EN=0�T��LCD�AEN=1�P��LCD
main()
{
   char hor=11,min=58,sec=52;//�]�w�ɡB���B����
   LCD_init();           //���m�βM��LCD    
   while(1)
   {
    LCD_Cmd(0x82);        //�ѲĤ@��}�l��� 
	if (hor<12) {LCD_Data('A');LCD_Data('M');}
	else  {LCD_Data('P');LCD_Data('M');}
	LCD_Data(' ');
    LCD_Data(hor%12/10+'0'); //�ɪ��Q��ƨ�LCD���
    LCD_Data(hor%12%10+'0'); //�ɪ��Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(min/10+'0'); //�����Q��ƨ�LCD���
    LCD_Data(min%10+'0'); //�����Ӧ�ƨ�LCD���
    LCD_Data(':');
    
    LCD_Data(sec/10+'0'); //���Q��ƨ�LCD���
    LCD_Data(sec%10+'0'); //���Ӧ�ƨ�LCD���
    
//	Delay_ms(5);
    sec++;              //��[�@
    if (sec < 60) continue; //�Y��p��60��loop�B   
    sec=0; min++;       //����60�h�O��=0�A���[�@
    if (min < 60) continue; //�Y���p��60��loop�B   
    min=0; hor++;       //�Y������60�h�O��=0�A�ɥ[�@
    if (hor <24)  continue; //�Y�ɤp��24��loop�B
    hor=0;min=0; sec=0;//�Y�ɵ���24�h�O�ɡB���B��=0 
	
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
