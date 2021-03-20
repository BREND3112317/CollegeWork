/***********3_35.c ********************************
*動作：由P0及P1輸出16-bit的左右移動作
************************************************/
#include "..\AT89X52.H"  //暫存器及組態設定
main() 
{
  unsigned int  i=0x0001; //定義整數
  while(1)    //重覆執行 
   {
     while(i<0x8000)   //判斷是否移到最左邊 
     {
       P0=i>>8;  //高位元組由P0輸出
       P1=i;     //低位元組由P1輸出
       Delay_ms(100); //延時
       i=i << 1 ;     //資料左移
     }               
     while(i >0x0001)  //判斷是否移到最右邊
      {
        P0=i>>8;  //高位元組由P0輸出
        P1=i;     //低位元組由P1輸出
        Delay_ms(100); //延時
        i=i >> 1 ;     //資料右移 
      }
  }
}