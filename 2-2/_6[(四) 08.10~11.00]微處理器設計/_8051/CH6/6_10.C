/********** 6_10.c *****************************
*動作：P0遞加，若T2EX(P11)腳輸入負緣觸發捕捉計時器到P2及P3 
***********************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
 void Delay(); //宣告自定函數
main()
{
   T2CON=0x09; /* 0000 1001，T2EX輸入負緣觸發捕捉計時器
                  bit3:EXEN2=1,使用外部T2EX接腳
				  bit1:C/T2=0,內部計時
			      bit0:CP/RL2=1,捕捉計時器 */
   T2R =0;      //設定Timer2=0
   TR2=1;       //啟動Timer2開始計時
   while (1)    //不斷循環執行
   {
     P0++;         //P0遞加輸出
     if(EXF2==1) /*若T2EX腳輸入負緣觸發EXF2==1，則捕捉*/
       {
        EXF2=0;    //清除旗標
        P2=RCAP2L; //捕捉計時器內容到P2及P3
        P3=RCAP2H;
       }
     }
}		   