//*********LED.C*********專案程式執行********************
//功能︰令變數遞加及P2輸出延時
//模擬：開啟Watch及P2視窗，設中斷點，觀察變數的動作
//********************************************************
#include "AT89X52.H"   //暫存器及組態設定

unsigned char code Table[] = {0x11111111, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f, 0x77, 0x7c, 0x39, 0x5e, 0x79, 0x71};
unsigned char code test = 0x10101010 ; 

main()          	//主程式
{              		//主程式開始   
    unsigned char  i=1, j=0;  //計數變數0~255
		P1 = 0xf0;
		loop:         	//標記名稱
		 if(i>=256 || i==0)i=1;
		 if(j>=16) j=0;
     
		 P0=~test;      	//變數i送到P2輸出(設中斷點)
		 P1=~Table[0];
     Delay_ms(500); //延時函數式
		 
     i=i<<1;      	//變數加一  
		 j++;
     goto loop;  	//跳到標記loop
}