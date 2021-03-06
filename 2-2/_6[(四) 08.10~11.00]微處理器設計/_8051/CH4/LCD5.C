/****** LCD5.C ******* LCD顯示中文字型範例*******
*動作：由LCD顯示自創的資工字型 
***********************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
                 //LCD讀取/寫入控制,R/W=GND寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD

unsigned char code Table[]=   //自創資工字型
 {0x00,0x00,0x19,0x02,0x08,0x11,0x07,0x04,//資的左上字
  0x00,0x10,0x1f,0x09,0x14,0x02,0x1c,0x04,//資的右上字
  0x00,0x0f,0x00,0x00,0x00,0x00,0x01,0x01,//工的左上字
  0x00,0x1e,0x08,0x08,0x10,0x10,0x00,0x00,//工的右上字
  0x07,0x04,0x07,0x04,0x07,0x02,0x04,0x00,//資的左下字
  0x1c,0x04,0x1c,0x04,0x1c,0x08,0x04,0x00,//資的右下字
  0x00,0x00,0x00,0x01,0x02,0x02,0x1f,0x00,//工的左下字
  0x10,0x10,0x10,0x00,0x00,0x00,0x1f,0x00 //工的右下字
 };
main()
{   
  unsigned char i;   
    LCD_init();             //重置及清除LCD     
    for(i=0x0;i<=0x3f;i++) //寫入CGRAM位址
     {
       LCD_Cmd(0x40+i);    //指定CGRAM位址  
       LCD_Data(Table[i]); //寫入CGRAM資料  
     }        
    LCD_Cmd(0x80);	//指定第一行顯示的位址
    for(i=0;i<4;i++)   LCD_Data(i);//讀取CGROM位址0-3的自創圖形資料    
     LCD_Cmd(0xc0);	//指定第二行顯示的位址
    for(i=4;i<8;i++)  LCD_Data(i);	//讀取CGROM位址4-7的自創圖形資料   
   while(1);  //停止
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
