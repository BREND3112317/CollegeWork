/************** 3_39.c ************************
*動作：用while指令，由P0-P2輸出24小時電子鐘的變化
************************************************/
#include "..\AT89X52.H"  //暫存器及組態設定
main()
{
  char hor=23,min=58,sec=58;//設定時、分、秒變數及時間
  while(1)   //重覆執行
   {
    P0=(sec/10<<4)+(sec%10); //秒十進位輸出
	P1=(min/10<<4)+(min%10); //分十進位輸出
	P2=(hor/10<<4)+(hor%10); //時十進位輸出
    Delay_ms(100);  //延時
     sec++;           //秒加一   
     while(sec>59)    //若秒大於59往下執行
       { 
         sec=0; min++; //若秒大於59則令秒=0，分+1
         while(min>59) //若分大於59往下執行
          { 
            min=0; hor++; //若分大於59則令分=0，時+1
            while(hor>23) hor=0; //若時大於23，則時=0
          }
       }
   }
} 