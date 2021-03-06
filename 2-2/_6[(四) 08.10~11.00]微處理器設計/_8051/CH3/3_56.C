/********** 3_56.C ****位元函數範例************
*動作：位元函數應用輸出
***********************************************/
#include "..\AT89X52.H" //暫存器及組態定義 
void SEND(bit flag);	//宣告位元函數
bit NOT(bit b1);      //宣告位元函數
main()
{
    bit b0=0;      //宣告位元變數b0=0
  loop:
    SEND(0);     //P00=0
    SEND(1);     //P00=1 
	b0=NOT(b0);//b0反相由P01輸出
   goto loop;
} 
//******************************************************* 
void SEND(bit flag)	//宣告位元函數，函數中有位元變數flag
{ 
  P0_0=flag;     //位元變數由P00輸出
}
//******************************************************* 
bit NOT(bit b1) //宣告位元函數，函數中有位元變數b1
{
  P0_1=b1;       //位元變數由P01輸出
  b1=!b1;		 //位元變數b1反相
  return b1;    //回傳位元變數b1
}