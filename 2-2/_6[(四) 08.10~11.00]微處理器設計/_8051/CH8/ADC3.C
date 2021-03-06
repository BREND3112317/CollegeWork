/**************** ADC3.C ****ADC0804實習板*************
*動作：輸入類比電壓，中斷方式讀取數位資料，在LCD顯示數位資料
*接線： 資料=P2，INTR=P32，RD=P10，WR=P11，CS接地                 
****************************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
sbit  AD_RD=P1^0 ; //P10為讀取控制，RD=0讀取數位資料
sbit  AD_WR=P1^1 ; //P11為寫入轉換控制，WR=0->1開始轉換

sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD

const int8  Table1[]="AN0="; //第一行列表字元
uint8 i; //資料計數

main()
{
  LCD_init();     //重置及清除LCD
  LCD_Cmd(0x80);  //由第一行開始顯示
   for(i=0 ; i< 4 ; i++) 
     LCD_Data(Table1[i]);//讀取列表"AN0="字元到LCD顯示

	EA=1; EX0=1;    //致能外部INT0中斷
	IT0=1;          //設定INT0腳負緣觸發中斷
	AD_WR=0; AD_WR=1;//ADC開始轉換
	while(1);		 //等待轉換完畢
}
void EX0_SUB(void) interrupt 0
{
	AD_RD=0;	 //轉換完畢，讀取數位資料
	LCD_Disp(P2); //LCD顯示ADC的資料
	AD_RD=1;	 //ADC停止讀取
	AD_WR=0; AD_WR=1;//ADC重新開始轉換
}
/********************************************************
*函數名稱: LCD_Disp(unsigned int disp)
*功能描述: LCD顯示3位數十進制數字
*輸入參數：disp
*******************************************************/
void LCD_Disp(unsigned int disp)  // LCD 十進制顯示
{
 LCD_Cmd(0x85);  //由第一行開始顯示
 LCD_Data(disp /100+'0');     //取出百位數字元到LCD顯示
 LCD_Data(disp % 100/10+'0'); //取出十位數字元到LCD顯示
 LCD_Data(disp % 10+'0');     //取出個位數字元到LCD顯示
} 
/***********************************************************
*函數名稱: LCD_Data
*功能描述: 傳送資料到文字型LCD
*輸入參數：dat
************************************************************/
void LCD_Data(char dat)  //傳送資料到LCD
{
    Data=dat; //資料送到BUS
    RS=1;EN=1;//資料寫入到LCD內
    Delay_ms(1);   //LCD等待寫入完成
    EN=0;          //禁能LCD    
}
/***************************************************************
*函數名稱: LCD_Cmd
*功能描述: 傳送命令到文字型LCD
*輸入參數：Cmd
************************************************************/
void LCD_Cmd(unsigned char Cmd) //傳送命令到LCD
{
    Data=Cmd;  //命令送到BUS
    RS=0;EN=1; //命令寫入到LCD內
    Delay_ms(1);    //LCD等待寫入完成     
    EN=0;           //禁能LCD
}
/***************************************************************
*函數名稱: LCD_init
*功能描述: 啟始化文字型LCD
*****************************************************************/
void LCD_init(void)    //LCD的啟始程式  
{
    LCD_Cmd(0x38);/*0011 1000,8bit傳輸,顯示2行,5*7字型
                    bit4:DL=1,8bit傳輸,
                    bit3:N=1,顯示2行
                    bit2:F=0,5*7字型*/    
    LCD_Cmd(0x0c);/*0000 1100,顯示幕ON,不顯示游標,游標不閃爍
                    bit2:D=1,顯示幕ON
                    bit1:C=0,不顯示游標
	                bit0:B=0,游標不閃爍*/
    LCD_Cmd(0x06);/*0000 0110,//顯示完游標右移,游標移位禁能 
                    bit1:I/D=1,顯示完游標右移,
                    bit0:S=0,游標移位禁能*/  
    LCD_Cmd(0x01); //清除顯示幕  
    LCD_Cmd(0x02); //游標回原位  
}