/*************** 3_16.c, *********************
*動作：複合設定運算子範例(2) 
********************************************/
main()
{
    unsigned char a=0x01;  //宣告輸入變數
    static unsigned char  i;  //宣告輸出變數
     loop:    
      i=0x21; i<<=a;//i=i<<1,      i=0010 0001-->0100 0010=0x42
      i=0x21; i>>=a;//i=i>>1,      i=0010 0001-->0001 0000=0x10
      i=0x21; i&=a; //i=i and 0x01,i=0010 0001-->0000 0001=0x01
      i=0x20; i|=a; //i=i or 0x01, i=0010 0000-->0010 0001=0x21
      i=0x21; i^=a; //i=i xor 0x01,i=0010 0001-->0010 0000=0x20 
     goto loop;  
}

