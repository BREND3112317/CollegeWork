/*******************SEG1B.C***********************
*動作：令兩位數共陽極七段顯示器顯示十進制計數00~99
*接線：P0個位數七段顯示器，P1十位數七段顯示器	
************************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
sfr  Data=0x80;//P0資料BUS輸出
 unsigned char code Table[] //七段顯示器0~F數碼資料
  ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,
    0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71}; 
void main() 
{
  unsigned char i=0;  //計數
  while(1) //重覆執行
   {     
  	 Data=~Table[i % 10];  //十進制的個位數數碼低電位輸出
     P1=~Table[i / 10];    //十進制的十位數數碼低電位輸出
	 Delay_ms(50);  //延時 
	 i++;           //計數遞加 
	 if(i>99) i=0;  //計數超過99，由0開始
   }
}