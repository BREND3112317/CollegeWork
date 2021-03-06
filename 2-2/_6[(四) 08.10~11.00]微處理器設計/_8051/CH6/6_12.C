/********** 6_12.c ****************************
*動作：設定以Timer2計時中斷，若是計時溢位令P0遞加，溢位
*重新載入，若T2EX(P11)腳輸入負緣觸發令P3遞加，強迫重新載入
**********************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
main()
  {
   T2CON = 0x08; /* 0000 1000，由T2EX腳輸入負緣觸發會重新載入
                    bit3:EXEN2=1,使用外部T2EX接腳
			        bit1:C/T=0,內部計時 
			        bit0:CP/RL2=0,重新載入*/
   RCAP2=T2R=65536-50000; //設定Timer2及T2自動載入暫存器
   TR2 = 1;         //啟動Timer2開始計時
   P0=P3=0;         //輸出0
   EA=1;ET2=1;      //致能Timer2中斷
   while (1);       //自我空轉，表示此時可作其它工作
  }
/*****************************************************/
 void T2_int (void) interrupt 5   //Timer2中斷函數
  {
   if (TF2 ==1)  //若是計時溢位令P0遞加，溢位重新載入
     {
       TF2=0;     //清除TF2=0
       P0++;      //P0遞加輸出
     }
   else  /*若是T2EX腳輸入負緣觸發令P3遞加，強迫重新載入*/
    {
      EXF2=0;    //清除EXF2=0
      P3++;      //P3遞加輸出
    }  
 }