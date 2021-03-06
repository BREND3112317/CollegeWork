/**********UART6.C ******UART與LCD傳輸**********
*動作：接收個人電腦的資料，送到LCD顯示
************************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
sbit RS=0x96;  //P16 LCD指令/資料控制,RS=0指令，RS=1資料
               //LCD讀取/寫入控制,R/W=0寫入
sbit EN=0x97;  //P17 LCD致能輸出,EN=0禁能LCD，EN=1致能LCD
char code Table1[] = "COUNT="; //第一行陣列字元
main()
{   
	char i;         //計數值
	LCD_init();   	//LCD啟始程式
	LCD_Cmd(0x80);        //游標由第一行開始顯示     
	for(i=0 ; i< 6 ; i++)   
      LCD_Data(Table1[i]);//讀取陣列文字送到LCD顯示      
	LCD_Cmd(0x86);        //游標由第一行第6字開始顯示        
	UART_init(9600);      //設定串列環境及鮑率   
	EA=1;ES=1;            //致能串列中斷   
	while(1);   	//自我空轉，表示可做其它工作
}
/*****************************************************/
void SCON_int(void)  interrupt 4  //串列中斷函數  
{  
  RI=0;             //接收完畢，令RI=0      
  LCD_Data(SBUF);  //將接收到的字元由LCD顯示    
}
/***********************************************************
*函數名稱: UART_init
*功能描述: UART啟始程式
*輸入參數：bps
************************************************************/
void UART_init(unsigned int bps)  //UART啟始程式
{
   SCON = 0x50;     //設定UART串列傳輸為MODE1及致能接收
   TMOD = 0x20;     //設定TIMER1為MODE2
   TH1 = 256-(28800/bps);  //設計時器決定串列傳輸鮑率
   TR1 = 1;          //開始計時
}
/***********************************************************
*函數名稱: LCD_Data
*功能描述: 傳送資料到文字型LCD
*輸入參數：dat
************************************************************/
void LCD_Data(char dat)  //傳送資料到LCD
{
 	Data=dat; //資料送到BUS   
	P0_7=0;    //過濾顯示字型資料
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