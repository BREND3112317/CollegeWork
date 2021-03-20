/********** EEPROM4.C *****"EEPROM 93C66實習板******
*動作：讀取16-bit陣列資料寫入EEPROM，再重覆讀取到P0/P1輸出
*接腳：CS=P27,SK=P26,DI=P25,DO=P24,ORG=開路
***********************************************/
#include "..\AT89X52.H"   //暫存器及組態定義
sfr LED=0x80;   //LED由P0輸出
sbit CS=P2 ^7 ;	//EEPROM 93C66接線
sbit SK=P2 ^6 ;
sbit DI=P2 ^5 ;
sbit DO=P2 ^4 ;

unsigned int code Table[] 
 ={0x1111,0x2222,0x3333,0x4444,0x5555,0x6666,0x7777,0x8888}; 
main()
{
	unsigned char i;//資料計數
	DI=1; DO=1; CS=0; SK=0;//設定初值
    EWEN();             //致能EEPROM寫入及清除
	ERAL();             //EEPROM清除全部記憶體
	for(i=0;i<8;i++)    //寫入8筆資料
   	  WRITE_16(i,Table[i]); //寫入位址及資料
    EWDS();    //禁能EEPROM寫入及清除
    while(1)   //不斷重覆讀取EEPROM的資料
    {  
      for(i=0;i<8;i++) //讀取8筆資料
      {
        LED=READ_16(i);    //讀取EEPROM的16-bit資料低位元組輸出
		P1=READ_16(i)>>8; //讀取EEPROM的16-bit資料高位元組輸出
	    Delay_ms(100);    //延時
      }
   }
}
/****************************************************
 函數名稱: Clock
 功能描述:送入串列EEPROM時脈信號
*****************************************************/
void Clock(void)
 {
  SK=1;  SK=0;
 }
/****************************************************
 函數名稱: SEND
 功能描述:送入EEPROM串列1-bit位址或資料
 輸入參數：flag
*****************************************************/
void SEND(bit flag)
 {
   DI=flag; Clock();
 } 
/*****************************************************
 函數名稱: SEND8
 功能描述: 串列EEPROM送入8-bit
 輸入參數：Addr
******************************************************/
void SEND8(unsigned char Addr) 
{
  char i;   
  for(i=0;i<8;i++)         //bit7~0 
   {
     if(Addr & 0x80) DI=1; //若bit7=1，則DI=1
       else DI= 0;         //若bit7=0，則DI=0
     Clock();              //串列時脈，bit送入EEPROM
     Addr= Addr << 1;      //位址左移
   }
}
/********************************************
 函數名稱:WRITE_16
 功能描述:93C66串列EEPROM送入位址及16-bit資料
 輸入參數：Addr,ch
*********************************************/
void WRITE_16(unsigned char Addr,unsigned int ch)
{ 
  CS=1;     //開啟EEPROM晶片
  SEND(1);          //啟始位元 
  SEND(0); SEND(1);	//操作碼01   
  SEND8(Addr);      //送入位址  
  SEND8(ch>>8);     //寫入高位元組資料
  SEND8(ch);        //寫入低位元組資料
  CS=0;             //關閉EEPROM晶片 
  CS=1; while(!DO) Clock(); CS=0;//等待寫入完畢	 
}
/*************************************************
 函數名稱: READ_16
 功能描述: 讀取93C66串列EEPROM資料
 輸入參數：Addr
 輸出參數：ch
**************************************************/
unsigned int READ_16(unsigned char Addr)
{
  char i;
  unsigned int ch;   //16-bit資料
  CS=1;              //開啟EEPROM晶片  
  SEND(1);           //啟始位元 
  SEND(1); SEND(0);	 //操作碼10   
  SEND8(Addr);       //送入位址  
  
  if(DO==0)
  {
	ch=0;  //資料=0
	for(i=0; i < 16; i++)//讀取16-bit資料
	 {
	   Clock();         //串列資料由DO輸出
	   ch=ch << 1;      //資料位元左移
	   if(DO== 1) ch++; //若DO=1，則ch資料bit0=1
	 }
   }
  CS=0;       //關閉EEPROM晶片 
  return ch;  //將16-bit資料送回主程式
}
/****************************************************
 函數名稱: EWEN
 功能描述: 93C66串列EEPROM寫入及清除致能
****************************************************/
void EWEN(void)   //EEPROM寫入及清除致能
{
  CS=1;             //開啟EEPROM晶片
  SEND(1);          //啟始位元
  SEND(0); SEND(0);	//操作碼00
  SEND8(0xc0);      //送入指令，致能抹除/寫入動作
  CS=0;             //關閉EEPROM晶片
}
/************************************************
 函數名稱: EWDS
 功能描述: 93C66串列EEPROM寫入及清除禁能
***********************************************/
void EWDS(void)  //EEPROM寫入及清除禁能
{
  CS=1;             //開啟EEPROM晶片
  SEND(1);          //啟始位元
  SEND(0); SEND(0);	//操作碼00	    
  SEND8(0x00);      //送入指令，禁能抹除/寫入動作
  CS=0;             //關閉EEPROM晶片
} 
/*************************************************
 函數名稱: ERAL
 功能描述: 93C66串列EEPROM清除全部記憶體
**************************************************/
void ERAL(void) //EEPROM清除全部記憶體
{
  CS=1;        //開啟EEPROM晶片
  SEND(1);     //啟始位元
  SEND(0); SEND(0);  //送入操作碼00
  SEND8(0x80); //送入指令，禁能抹除/寫入動作
  CS=0;        //關閉EEPROM晶片
}